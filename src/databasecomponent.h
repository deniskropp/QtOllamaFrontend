#ifndef DATABASECOMPONENT_H
#define DATABASECOMPONENT_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlField>
#include <QSqlRecord>
#include <QSqlResult>
#include <QStandardPaths>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QByteArray>
#include <QDebug>

class DatabaseComponent : public QObject
{
    Q_OBJECT
    // constants:
    const QString DATABASE_DRIVER = "QSQLITE";
    const QString DATABASE_FILE = "db-queue-downloader.db";
    const QString TABLE_LOG = "log";
    const QString QUERY_CREATE_LOG =
            "CREATE TABLE IF NOT EXISTS " + TABLE_LOG +
            "(id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,"
            "date DEFAULT CURRENT_TIMESTAMP NOT NULL,"
            "text TEXT)";
    const QString TABLE_SETTINGS = "settings";
    const QString QUERY_CREATE_SETTINGS =
        "CREATE TABLE IF NOT EXISTS " + TABLE_SETTINGS +
        "(key TEXT PRIMARY KEY NOT NULL,"
        "value TEXT)";
    // attributes:
    QSqlDatabase m_databaseConnection;
    bool m_storeOnlyInMemory = false;
    // methods:
    void setUpDatabase();
    QString convertJsonToString(const QJsonObject &data);
    void outputSqlError(const QSqlQuery &query);
    int getCount(QString tableName);
signals:
    void databaseConnectionError(QString errorMessage);
    void logJsonDataResult(bool result, QString data);
    void updateSettingResult(bool result, QString data);
    void setDatabaseLocation(QString message);
    void deleteSqliteDatabaseResult(bool result);
public slots:
    void deleteSqliteDatabase();
    void logJsonData(const QString &data);
    void updateSetting(const QString &key,
                       const QString &value);
    void query(const QString &queryString);
    void emptyDatabase();
    QStringList getTables();
    QStringList getColumns(const QString &tableName);
    QVariantList getRows(const QString &tableName,
                         const QStringList &selectFields = QStringList("*"),
                         const int &offset = 0,
                         const int &limit = 0,
                         const QString &orderBy = "id",
                         const QString &sortOrder = "DESC");
    QVariantList getAllRows(const QString &tableName,
                            const QStringList &selectFields = QStringList("*"),
                            const QString &orderBy = "id",
                            const QString &sortOrder = "DESC");
    QJsonObject getRowById(const QString &tableName,
                           const int &id);
    QJsonObject getSetting(QString key);
    void deleteDatabase();
public:
    QString getTableSettings();
    // constructor:
    DatabaseComponent(QObject* parent = nullptr);
};

#endif // DATABASECOMPONENT_H
