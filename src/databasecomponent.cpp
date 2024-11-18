#include "databasecomponent.h"

DatabaseComponent::DatabaseComponent(QObject* parent) : QObject(parent) {
    if (!QSqlDatabase::isDriverAvailable(DATABASE_DRIVER)) {
        qDebug() << "database driver not available:" << DATABASE_DRIVER;
        emit databaseConnectionError("database driver not available: " + DATABASE_DRIVER);
    }

    setUpDatabase();
}

void DatabaseComponent::setUpDatabase() {
    m_databaseConnection = QSqlDatabase::addDatabase(DATABASE_DRIVER);

    if (m_storeOnlyInMemory) {
        m_databaseConnection.setDatabaseName(":memory:");
        emit setDatabaseLocation("database stored only in memory");
    } else {
        m_databaseConnection.setDatabaseName(DATABASE_FILE);
        emit setDatabaseLocation(QString("database file: %1").arg(DATABASE_FILE));
    }

    if (!m_databaseConnection.open()) {
        qWarning() << "ERROR:" << m_databaseConnection.lastError().text();
        emit databaseConnectionError(QString("database error: %1").arg(m_databaseConnection.lastError().text()));
    }

    // set up database tables
    query(QUERY_CREATE_LOG);
    query(QUERY_CREATE_SETTINGS);
}

void DatabaseComponent::deleteSqliteDatabase() {
    if (m_databaseConnection.isOpen()) {
        m_databaseConnection.close();
    }

    QFile file(DATABASE_FILE);
    bool result = file.remove();
    if (!result) {
        qDebug() << "Deleting the SQLite-Database failed:" << file.errorString();
    }

    setUpDatabase();

    emit deleteSqliteDatabaseResult(result);
}

QString DatabaseComponent::convertJsonToString(const QJsonObject &data) {
    QJsonDocument doc(data);
    return QString(doc.toJson(QJsonDocument::Indented));
}

void DatabaseComponent::outputSqlError(const QSqlQuery &query) {
    qDebug() << "SQLite query failed" << "(" << query.lastError().nativeErrorCode() << "):" << query.lastError().text() << ":" << query.executedQuery();
}

void DatabaseComponent::logJsonData(const QString &data) {
    if (data.isEmpty() || data.isNull()) {
        qDebug() << "no data to log";
        return;
    }

    QSqlQuery query;
    query.prepare("INSERT INTO " + TABLE_LOG + " (text) VALUES (:text)");
    query.bindValue(":text", data);

    bool result = query.exec();
    if (!result) {
        outputSqlError(query);
    }

    emit logJsonDataResult(result, data);
}

void DatabaseComponent::updateSetting(const QString &key, const QString &value) {
    if (key.isEmpty() || key.isNull()) {
        qDebug() << "no valid data to update the settings data";
        return;
    }

    QSqlQuery query;
    query.prepare("INSERT OR REPLACE INTO " + TABLE_SETTINGS + "("
                                                              "key,"
                                                              "value)"
                                                              " VALUES ("
                                                              ":key,"
                                                              ":value)");
    query.bindValue(":key", key);
    query.bindValue(":value", value);

    bool result = query.exec();
    if (!result) {
        outputSqlError(query);
    }

    QJsonObject data;
    data.insert("key", QJsonValue(key));
    data.insert("value", value);

    emit updateSettingResult(result, convertJsonToString(data));
}

int DatabaseComponent::getCount(QString tableName) {
    if (tableName.isEmpty() || tableName.isNull()) {
        return -1;
    }

    QSqlQuery query;
    query.prepare("SELECT COUNT(id) AS count FROM " + tableName);

    bool result = query.exec();
    if (!result) {
        outputSqlError(query);
    }

    if (result) {
        query.first();
        QVariant value = query.value("count");

        return value.toInt();
    }

    return -1;
}

QStringList DatabaseComponent::getColumns(const QString &tableName) {
    if (tableName.isEmpty() || tableName.isNull()) {
        qDebug() << "no table name specified";
        return QStringList();
    }

    QStringList columns;

    QSqlRecord record = m_databaseConnection.record(tableName);
    for (int i = 0; i < record.count(); i++) {
        columns << record.field(i).name();
    }

    return columns;
}

void DatabaseComponent::emptyDatabase() {
    QStringList tableNames = QStringList() << TABLE_LOG;
    for (int i = 0; i < tableNames.count(); i++) {
        QString tableName = tableNames.at(i);

        query("DELETE FROM " + tableName);
        query("UPDATE SQLITE_SEQUENCE SET seq = 0 WHERE name = '" + tableName + "'");
    }
}

QStringList DatabaseComponent::getTables() {
    return m_databaseConnection.tables();
}

QVariantList DatabaseComponent::getAllRows(const QString &tableName,
                                           const QStringList &selectFields,
                                           const QString &orderBy,
                                           const QString &sortOrder) {
    if (tableName.isEmpty() || tableName.isNull()) {
        qDebug() << "no table name specified";
        return QVariantList();
    } else if (selectFields.count() == 0) {
        qDebug() << "no fields selected";
        return QVariantList();
    }

    QJsonArray rows;

    QSqlQuery query;
    QString queryString = QString("SELECT %4 FROM %1 ORDER BY %2 %3").arg(tableName).arg(orderBy).arg(sortOrder).arg(selectFields.join(","));
    query.prepare(queryString);

    if (query.exec()) {
        while (query.next()) {
            QSqlRecord result = query.record();
            QJsonObject row;
            for (int i = 0; i < result.count(); i++) {
                row.insert(result.fieldName(i), result.value(i).toJsonValue());
            }
            rows.append(row);
        }
    }

    return rows.toVariantList();
}

QJsonObject DatabaseComponent::getSetting(QString key) {
    if (key.isEmpty() || key.isNull()) {
        qDebug() << "no settings key specified";
        return QJsonObject();
    }

    QSqlQuery query;
    query.prepare("SELECT * FROM " + TABLE_SETTINGS + " WHERE key = :key");
    query.bindValue(":key", key);

    QJsonObject row;
    if (query.exec()) {
        while (query.next()) {
            QSqlRecord result = query.record();
            QJsonObject row;
            for (int i = 0; i < result.count(); i++) {
                row.insert(result.fieldName(i), result.value(i).toJsonValue());
            }
            return row;
        }
    }

    return row;
}

QJsonObject DatabaseComponent::getRowById(const QString &tableName, const int &id) {
    if (tableName.isEmpty() || tableName.isNull() || id <= 0) {
        qDebug() << "no table row specified";
        return QJsonObject();
    }

    QSqlQuery query;
    query.prepare("SELECT * FROM " + tableName + " WHERE id = :id");
    query.bindValue(":id", id);

    QJsonObject row;
    if (query.exec()) {
        while (query.next()) {
            QSqlRecord result = query.record();
            QJsonObject row;
            for (int i = 0; i < result.count(); i++) {
                row.insert(result.fieldName(i), result.value(i).toJsonValue());
            }
            return row;
        }
    }

    return row;
}

QVariantList DatabaseComponent::getRows(const QString &tableName,
                                        const QStringList &selectFields,
                                        const int &offset,
                                        const int &limit,
                                        const QString &orderBy,
                                        const QString &sortOrder) {
    if (tableName.isEmpty() || tableName.isNull()) {
        qDebug() << "no table name specified";
        return QVariantList();
    } else if (selectFields.count() == 0) {
        qDebug() << "no fields selected";
        return QVariantList();
    } else if (offset < 0) {
        qDebug() << "invalid offset";
        return QVariantList();
    } else if (limit <= 0) {
        qDebug() << "invalid limit";
        return QVariantList();
    }

    QJsonArray rows;

    QSqlQuery query;
    QString queryString = QString("SELECT %6 FROM %1 ORDER BY %4 %5 LIMIT %2 OFFSET %3").arg(tableName).arg(limit).arg(offset).arg(orderBy).arg(sortOrder).arg(selectFields.join(","));
    query.prepare(queryString);

    if (query.exec()) {
        while (query.next()) {
            QSqlRecord result = query.record();
            QJsonObject row;
            for (int i = 0; i < result.count(); i++) {
                row.insert(result.fieldName(i), result.value(i).toJsonValue());
            }
            rows.append(row);
        }
    }

    return rows.toVariantList();
}

void DatabaseComponent::query(const QString &queryString) {
    if (queryString.isEmpty() || queryString.isNull()) {
        qDebug() << "no query string specified";
        return;
    }

    QSqlQuery query(queryString);
    if (!query.isActive()) {
        qDebug() << QString("ERROR: %1, query string: %2").arg(query.lastError().text()).arg(queryString);
    }
}

void DatabaseComponent::deleteDatabase() {
    if (QFile::exists(DATABASE_FILE)) {
        if (QFile::remove(DATABASE_FILE)) {
            qDebug() << "database deleted";
        }
    }
}

QString DatabaseComponent::getTableSettings() {
    return TABLE_SETTINGS;
}
