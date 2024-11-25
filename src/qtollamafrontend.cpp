#include "qtollamafrontend.h"

QtOllamaFrontend::QtOllamaFrontend(QObject* parent) : QObject(parent) {
    m_databaseComponent = new DatabaseComponent(this);
    m_networkAccessManager = new QNetworkAccessManager(this);
    m_clipboard = appReference->clipboard();

    // update setting
    connect(this, &QtOllamaFrontend::updateSetting, this, [=](QString key, QString value) {
        qDebug() << "update setting" << key << value;
        m_databaseComponent->updateSetting(key, value);
    });

    loadSettings();
}

QtOllamaFrontend::~QtOllamaFrontend() {
}

void QtOllamaFrontend::loadSettings() {
    QList<int> keys;
    keys << Settings::ApiHost
         << Settings::ApiPort
         << Settings::ApiModelName
         << Settings::ScaledImageWidth
         << Settings::ScaledImageHeight
         << Settings::ShowLog
         << Settings::OutputTts
         << Settings::TextMessageMultiline
         << Settings::TtsEngine
         << Settings::TtsLocale
         << Settings::TtsVoice
         << Settings::TtsVolume
         << Settings::TtsRate
         << Settings::TtsPitch
         << Settings::Seed
         << Settings::NumKeep
         << Settings::NumPredict
         << Settings::TopK
         << Settings::TopP
         << Settings::MinP
         << Settings::TfsZ
         << Settings::TypicalP
         << Settings::RepeatLastN
         << Settings::Temperature
         << Settings::RepeatPenalty
         << Settings::PresencePenalty
         << Settings::FrequencyPenalty
         << Settings::Mirostat
         << Settings::MirostatTau
         << Settings::MirostatEta
         << Settings::PenalizeNewline
         << Settings::Stop
         << Settings::Numa
         << Settings::NumCtx
         << Settings::NumBatch
         << Settings::NumGpu
         << Settings::MainGpu
         << Settings::LowVram
         << Settings::VocabOnly
         << Settings::UseMmap
         << Settings::UseMlock
         << Settings::NumThread
         << Settings::SeedApplied
         << Settings::NumKeepApplied
         << Settings::NumPredictApplied
         << Settings::TopKApplied
         << Settings::TopPApplied
         << Settings::MinPApplied
         << Settings::TfsZApplied
         << Settings::TypicalPApplied
         << Settings::RepeatLastNApplied
         << Settings::TemperatureApplied
         << Settings::RepeatPenaltyApplied
         << Settings::PresencePenaltyApplied
         << Settings::FrequencyPenaltyApplied
         << Settings::MirostatApplied
         << Settings::MirostatTauApplied
         << Settings::MirostatEtaApplied
         << Settings::PenalizeNewlineApplied
         << Settings::StopApplied
         << Settings::NumaApplied
         << Settings::NumCtxApplied
         << Settings::NumBatchApplied
         << Settings::NumGpuApplied
         << Settings::MainGpuApplied
         << Settings::LowVramApplied
         << Settings::VocabOnlyApplied
         << Settings::UseMmapApplied
         << Settings::UseMlockApplied
         << Settings::NumThreadApplied;

    for (int key : keys) {
        QString skey = getSettingsKey(key);

        if (!skey.isNull() && !skey.isEmpty()) {
            QString value = getSetting(skey);

            if (value.isNull() || value.isEmpty()) {
                updateSetting(skey, getDefaultSetting(key));
            }
        }
    }

    // set properties
    // api
    m_host = getSetting(getSettingsKey(Settings::ApiHost));
    m_port = getSetting(getSettingsKey(Settings::ApiPort)).toInt();
    m_modelName = getSetting(getSettingsKey(Settings::ApiModelName));
    // settings
    m_scaledImageWidth = getSetting(getSettingsKey(Settings::ScaledImageWidth)).toInt();
    m_scaledImageHeight = getSetting(getSettingsKey(Settings::ScaledImageHeight)).toInt();
    m_showLog = getSetting(getSettingsKey(Settings::ShowLog)) == "1";
    m_outputTts = getSetting(getSettingsKey(Settings::OutputTts)) == "1";
    m_textMessageMultiline = getSetting(getSettingsKey(Settings::TextMessageMultiline)) == "1";
    m_ttsEngine = getSetting(getSettingsKey(Settings::TtsEngine));
    m_ttsLocale = getSetting(getSettingsKey(Settings::TtsLocale));
    m_ttsVoice = getSetting(getSettingsKey(Settings::TtsVoice));
    m_ttsVolume = getSetting(getSettingsKey(Settings::TtsVolume)).toDouble();
    m_ttsRate = getSetting(getSettingsKey(Settings::TtsRate)).toDouble();
    m_ttsPitch = getSetting(getSettingsKey(Settings::TtsPitch)).toDouble();
    // options
    m_seed = getSetting(getSettingsKey(Settings::Seed)).toInt();
    m_numKeep = getSetting(getSettingsKey(Settings::NumKeep)).toInt();
    m_numPredict = getSetting(getSettingsKey(Settings::NumPredict)).toInt();
    m_topK = getSetting(getSettingsKey(Settings::TopK)).toInt();
    m_topP = getSetting(getSettingsKey(Settings::TopP)).toDouble();
    m_minP = getSetting(getSettingsKey(Settings::MinP)).toDouble();
    m_tfsZ = getSetting(getSettingsKey(Settings::TfsZ)).toDouble();
    m_typicalP = getSetting(getSettingsKey(Settings::TypicalP)).toDouble();
    m_repeatLastN = getSetting(getSettingsKey(Settings::RepeatLastN)).toInt();
    m_temperature = getSetting(getSettingsKey(Settings::Temperature)).toDouble();
    m_repeatPenalty = getSetting(getSettingsKey(Settings::RepeatPenalty)).toDouble();
    m_presencePenalty = getSetting(getSettingsKey(Settings::PresencePenalty)).toDouble();
    m_frequencyPenalty = getSetting(getSettingsKey(Settings::FrequencyPenalty)).toDouble();
    m_mirostat = getSetting(getSettingsKey(Settings::Mirostat)).toInt();
    m_mirostatTau = getSetting(getSettingsKey(Settings::MirostatTau)).toDouble();
    m_mirostatEta = getSetting(getSettingsKey(Settings::MirostatEta)).toDouble();
    m_penalizeNewline = getSetting(getSettingsKey(Settings::PenalizeNewline)) == "1";
    m_stop = getSetting(getSettingsKey(Settings::Stop));
    m_numa = getSetting(getSettingsKey(Settings::Numa)) == "1";
    m_numCtx = getSetting(getSettingsKey(Settings::NumCtx)).toInt();
    m_numBatch = getSetting(getSettingsKey(Settings::NumBatch)).toInt();
    m_numGpu = getSetting(getSettingsKey(Settings::NumGpu)).toInt();
    m_mainGpu = getSetting(getSettingsKey(Settings::MainGpu)).toInt();
    m_lowVram = getSetting(getSettingsKey(Settings::LowVram)) == "1";
    m_vocabOnly = getSetting(getSettingsKey(Settings::VocabOnly)) == "1";
    m_useMmap = getSetting(getSettingsKey(Settings::UseMmap)) == "1";
    m_useMlock = getSetting(getSettingsKey(Settings::UseMlock)) == "1";
    m_numThread = getSetting(getSettingsKey(Settings::NumThread)).toInt();
    m_seedApplied = getSetting(getSettingsKey(Settings::SeedApplied)) == "1";
    m_numKeepApplied = getSetting(getSettingsKey(Settings::NumKeepApplied)) == "1";
    m_numPredictApplied = getSetting(getSettingsKey(Settings::NumPredictApplied)) == "1";
    m_topKApplied = getSetting(getSettingsKey(Settings::TopKApplied)) == "1";
    m_topPApplied = getSetting(getSettingsKey(Settings::TopPApplied)) == "1";
    m_minPApplied = getSetting(getSettingsKey(Settings::MinPApplied)) == "1";
    m_tfsZApplied = getSetting(getSettingsKey(Settings::TfsZApplied)) == "1";
    m_typicalPApplied = getSetting(getSettingsKey(Settings::TypicalPApplied)) == "1";
    m_repeatLastNApplied = getSetting(getSettingsKey(Settings::RepeatLastNApplied)) == "1";
    m_temperatureApplied = getSetting(getSettingsKey(Settings::TemperatureApplied)) == "1";
    m_repeatPenaltyApplied = getSetting(getSettingsKey(Settings::RepeatPenaltyApplied)) == "1";
    m_presencePenaltyApplied = getSetting(getSettingsKey(Settings::PresencePenaltyApplied)) == "1";
    m_frequencyPenaltyApplied = getSetting(getSettingsKey(Settings::FrequencyPenaltyApplied)) == "1";
    m_mirostatApplied = getSetting(getSettingsKey(Settings::MirostatApplied)) == "1";
    m_mirostatTauApplied = getSetting(getSettingsKey(Settings::MirostatTauApplied)) == "1";
    m_mirostatEtaApplied = getSetting(getSettingsKey(Settings::MirostatEtaApplied)) == "1";
    m_penalizeNewlineApplied = getSetting(getSettingsKey(Settings::PenalizeNewlineApplied)) == "1";
    m_stopApplied = getSetting(getSettingsKey(Settings::StopApplied)) == "1";
    m_numaApplied = getSetting(getSettingsKey(Settings::NumaApplied)) == "1";
    m_numCtxApplied = getSetting(getSettingsKey(Settings::NumCtxApplied)) == "1";
    m_numBatchApplied = getSetting(getSettingsKey(Settings::NumBatchApplied)) == "1";
    m_numGpuApplied = getSetting(getSettingsKey(Settings::NumGpuApplied)) == "1";
    m_mainGpuApplied = getSetting(getSettingsKey(Settings::MainGpuApplied)) == "1";
    m_lowVramApplied = getSetting(getSettingsKey(Settings::LowVramApplied)) == "1";
    m_vocabOnlyApplied = getSetting(getSettingsKey(Settings::VocabOnlyApplied)) == "1";
    m_useMmapApplied = getSetting(getSettingsKey(Settings::UseMmapApplied)) == "1";
    m_useMlockApplied = getSetting(getSettingsKey(Settings::UseMlockApplied)) == "1";
    m_numThreadApplied = getSetting(getSettingsKey(Settings::NumThreadApplied)) == "1";
}

QString QtOllamaFrontend::convertJsonToString(const QJsonObject &data) {
    QJsonDocument doc(data);
    return QString(doc.toJson(QJsonDocument::Indented));
}

QString QtOllamaFrontend::convertJsonToString(const QJsonArray &data) {
    QJsonDocument doc(data);
    return QString(doc.toJson(QJsonDocument::Indented));
}

QByteArray QtOllamaFrontend::convertToBytes(const QJsonObject &jsonObject) {
    QJsonDocument doc(jsonObject);
    QByteArray jsonBytes = doc.toJson(QJsonDocument::Indented);
    return jsonBytes;
}

QByteArray QtOllamaFrontend::convertToBytes(const QJsonArray &jsonArray) {
    QJsonDocument doc(jsonArray);
    QByteArray jsonBytes = doc.toJson(QJsonDocument::Indented);
    return jsonBytes;
}

QJsonObject QtOllamaFrontend::convertToJsonObject(const QString &jsonString) {
    QJsonDocument doc = QJsonDocument::fromJson(jsonString.toUtf8());
    QJsonObject jsonObject = doc.object();
    return jsonObject;
}

QJsonArray QtOllamaFrontend::convertToJsonArray(const QString &jsonString) {
    QJsonDocument doc = QJsonDocument::fromJson(jsonString.toUtf8());
    QJsonArray jsonArray = doc.array();
    return jsonArray;
}

QByteArray QtOllamaFrontend::getImageBytes(const QString filePath) {
    QByteArray imageData;

    QImage image;
    if (image.load(filePath)) {
        QBuffer buffer(&imageData);
        buffer.open(QIODevice::WriteOnly);
        image.save(&buffer, "PNG");
    }

    return imageData;
}

QByteArray QtOllamaFrontend::getImageBytes(const QImage &image) {
    QByteArray imageData;

    QBuffer buffer(&imageData);
    buffer.open(QIODevice::WriteOnly);
    image.save(&buffer, "PNG");

    return imageData;
}

QString QtOllamaFrontend::convertImageBytesToBase64(const QByteArray &imageData) {
    return QString::fromLatin1(imageData.toBase64().data());
}

void QtOllamaFrontend::outputRequest(const QString request) {
    qDebug().noquote() << "\n" << "jsonRequest:" << "\n" << request;
}

void QtOllamaFrontend::outputResponse(const QString response) {
    QJsonObject jsonObject = convertToJsonObject(QString(response));
    QByteArray bytes = convertToBytes(jsonObject);
    qDebug().noquote() << "\n" << "jsonResponse:" << "\n" << bytes;
}

QByteArray QtOllamaFrontend::prepareJsonForLogOutput(const QJsonObject &jsonObject) {
    QJsonObject copiedObject(jsonObject);

    if (copiedObject.contains("messages")) {
        QJsonArray messages = copiedObject.value("messages").toArray();

        for (int i = 0; i < messages.count(); i++) {
            QJsonObject message = messages.at(i).toObject();

            // remove images (shorten base64-coded string)
            if (message.contains("images")) {
                QJsonArray images = message.value("images").toArray();

                for (int j = 0; j < images.count(); j++) {
                    QString imageData = images.at(j).toString().slice(0, 4) + "...";

                    images.replace(j, QJsonValue(imageData));
                }

                message.insert("images", images);
            }

            messages.replace(i, message);
        }

        copiedObject.insert("messages", messages);
    }

    return convertToBytes(copiedObject);
}

QStringList QtOllamaFrontend::extractJsonStrings(const QString &string) {
    QStringList jsonStrings;

    QString regExpString = "(\\{(\"|:|,|\\w*|\\s*)*\\})";
    QRegularExpression regularExpression(regExpString, QRegularExpression::DotMatchesEverythingOption);

    QRegularExpressionMatchIterator iteratorMatch = regularExpression.globalMatch(string);
    while (iteratorMatch.hasNext()) {
        QRegularExpressionMatch match = iteratorMatch.next();

        jsonStrings << match.captured(1);
    }

    return jsonStrings;
}

QString QtOllamaFrontend::createHttpPostRequest(const QString &apiUri, const QString &jsonString) {
    return "POST " + apiUri + " HTTP/1.1\r\nHost: " + m_host + "\r\nContent-Type: application/json\r\nContent-Length: " + QString::number(jsonString.size()) + "\r\n\r\n" + jsonString + "\r\n";
}

QString QtOllamaFrontend::createHttpDeleteRequest(const QString &apiUri, const QString &jsonString) {
    return "DELETE " + apiUri + " HTTP/1.1\r\nHost: " + m_host + "\r\nContent-Type: application/json\r\nContent-Length: " + QString::number(jsonString.size()) + "\r\n\r\n" + jsonString + "\r\n";
}

QNetworkRequest QtOllamaFrontend::createNetworkRequest(const QUrl &url, const QByteArray &bytes) {
    QByteArray postDataSize = QByteArray::number(bytes.size());

    QNetworkRequest request(url);

    request.setAttribute(QNetworkRequest::RedirectPolicyAttribute, QNetworkRequest::NoLessSafeRedirectPolicy);

    request.setRawHeader("User-Agent", "QtOllamaFrontend");
    request.setRawHeader("X-Custom-User-Agent", "QtOllamaFrontend");
    request.setRawHeader("Content-Type", "application/json");
    request.setRawHeader("Content-Length", postDataSize);

    return request;
}

void QtOllamaFrontend::emitNetworkError(QNetworkReply *reply) {
    qDebug() << "network error:" << reply->errorString();
    emit receivedNetworkError(reply->errorString());
}

void QtOllamaFrontend::emitNetworkError(QTcpSocket *tcpSocket) {
    qDebug() << "network error:" << tcpSocket->errorString();
    emit receivedNetworkError(tcpSocket->errorString());
}

void QtOllamaFrontend::downloadProgress(qint64 bytesReceived, qint64 bytesTotal) {
    emit receivedDownloadProgress(bytesReceived, bytesTotal);
}

void QtOllamaFrontend::uploadProgress(qint64 bytesSent, qint64 bytesTotal) {
    emit receivedUploadProgress(bytesSent, bytesTotal);
}

bool QtOllamaFrontend::loading() {
    return m_loading;
}

void QtOllamaFrontend::setLoading(const bool &loading) {
    if (loading != m_loading) {
        m_loading = loading;
        emit loadingChanged();
    }
}

QString QtOllamaFrontend::host() {
    return m_host;
}

void QtOllamaFrontend::setHost(const QString &host) {
    if (host != m_host) {
        m_host = host;
        updateSetting(getSettingsKey(Settings::ApiHost), host);
        emit hostChanged();
    }
}

int QtOllamaFrontend::port() {
    return m_port;
}

void QtOllamaFrontend::setPort(const int &port) {
    if (port != m_port) {
        m_port = port;
        updateSetting(getSettingsKey(Settings::ApiPort), QString::number(port));
        emit portChanged();
    }
}

QString QtOllamaFrontend::modelName() {
    return m_modelName;
}

void QtOllamaFrontend::setModelName(const QString &modelName) {
    if (modelName != m_modelName) {
        m_modelName = modelName;
        updateSetting(getSettingsKey(Settings::ApiModelName), modelName);
        emit modelNameChanged();
    }
}

int QtOllamaFrontend::scaledImageWidth() {
    return m_scaledImageWidth;
}

void QtOllamaFrontend::setScaledImageWidth(const int &scaledImageWidth) {
    if (scaledImageWidth != m_scaledImageWidth) {
        m_scaledImageWidth = scaledImageWidth;
        updateSetting(getSettingsKey(Settings::ScaledImageWidth), QString::number(scaledImageWidth));
        emit scaledImageWidthChanged();
    }
}

int QtOllamaFrontend::scaledImageHeight() {
    return m_scaledImageHeight;
}

void QtOllamaFrontend::setScaledImageHeight(const int &scaledImageHeight) {
    if (scaledImageHeight != m_scaledImageHeight) {
        m_scaledImageHeight = scaledImageHeight;
        updateSetting(getSettingsKey(Settings::ScaledImageHeight), QString::number(scaledImageHeight));
        emit scaledImageHeightChanged();
    }
}

bool QtOllamaFrontend::showLog() {
    return m_showLog;
}

void QtOllamaFrontend::setShowLog(const bool &showLog) {
    if (showLog != m_showLog) {
        m_showLog = showLog;
        updateSetting(getSettingsKey(Settings::ShowLog), showLog ? "1" : "0");
        emit showLogChanged();
    }
}

bool QtOllamaFrontend::outputTts() {
    return m_outputTts;
}

void QtOllamaFrontend::setOutputTts(const bool &outputTts) {
    if (outputTts != m_outputTts) {
        m_outputTts = outputTts;
        updateSetting(getSettingsKey(Settings::OutputTts), outputTts ? "1" : "0");
        emit outputTtsChanged();
    }
}

bool QtOllamaFrontend::textMessageMultiline() {
    return m_textMessageMultiline;
}

void QtOllamaFrontend::setTextMessageMultiline(const bool &textMessageMultiline) {
    if (textMessageMultiline != m_textMessageMultiline) {
        m_textMessageMultiline = textMessageMultiline;
        updateSetting(getSettingsKey(Settings::TextMessageMultiline), textMessageMultiline ? "1" : "0");
        emit textMessageMultilineChanged();
    }
}

QString QtOllamaFrontend::ttsEngine() {
    return m_ttsEngine;
}

void QtOllamaFrontend::setTtsEngine(const QString &ttsEngine) {
    if (ttsEngine != m_ttsEngine) {
        m_ttsEngine = ttsEngine;
        updateSetting(getSettingsKey(Settings::TtsEngine), ttsEngine);
        emit ttsEngineChanged();
    }
}

QString QtOllamaFrontend::ttsLocale() {
    return m_ttsLocale;
}

void QtOllamaFrontend::setTtsLocale(const QString &ttsLocale) {
    if (ttsLocale != m_ttsLocale) {
        m_ttsLocale = ttsLocale;
        updateSetting(getSettingsKey(Settings::TtsLocale), ttsLocale);
        emit ttsLocaleChanged();
    }
}

QString QtOllamaFrontend::ttsVoice() {
    return m_ttsVoice;
}

void QtOllamaFrontend::setTtsVoice(const QString &ttsVoice) {
    if (ttsVoice != m_ttsVoice) {
        m_ttsVoice = ttsVoice;
        updateSetting(getSettingsKey(Settings::TtsVoice), ttsVoice);
        emit ttsVoiceChanged();
    }
}

double QtOllamaFrontend::ttsVolume() {
    return m_ttsVolume;
}

void QtOllamaFrontend::setTtsVolume(const double &ttsVolume) {
    if (ttsVolume != m_ttsVolume) {
        m_ttsVolume = ttsVolume;
        updateSetting(getSettingsKey(Settings::TtsVolume), QString::number(ttsVolume));
        emit ttsVolumeChanged();
    }
}

double QtOllamaFrontend::ttsRate() {
    return m_ttsRate;
}

void QtOllamaFrontend::setTtsRate(const double &ttsRate) {
    if (ttsRate != m_ttsRate) {
        m_ttsRate = ttsRate;
        updateSetting(getSettingsKey(Settings::TtsRate), QString::number(ttsRate));
        emit ttsRateChanged();
    }
}

double QtOllamaFrontend::ttsPitch() {
    return m_ttsPitch;
}

void QtOllamaFrontend::setTtsPitch(const double &ttsPitch) {
    if (ttsPitch != m_ttsPitch) {
        m_ttsPitch = ttsPitch;
        updateSetting(getSettingsKey(Settings::TtsPitch), QString::number(ttsPitch));
        emit ttsPitchChanged();
    }
}

int QtOllamaFrontend::seed() {
    return m_seed;
}

void QtOllamaFrontend::setSeed(const int &seed) {
    if (seed != m_seed) {
        m_seed = seed;
        updateSetting(getSettingsKey(Settings::Seed), QString::number(seed));
        emit seedChanged();
    }
}

int QtOllamaFrontend::numKeep() {
    return m_numKeep;
}

void QtOllamaFrontend::setNumKeep(const int &numKeep) {
    if (numKeep != m_numKeep) {
        m_numKeep = numKeep;
        updateSetting(getSettingsKey(Settings::NumKeep), QString::number(numKeep));
        emit numKeepChanged();
    }
}

int QtOllamaFrontend::numPredict() {
    return m_numPredict;
}

void QtOllamaFrontend::setNumPredict(const int &numPredict) {
    if (numPredict != m_numPredict) {
        m_numPredict = numPredict;
        updateSetting(getSettingsKey(Settings::NumPredict), QString::number(numPredict));
        emit numPredictChanged();
    }
}

int QtOllamaFrontend::topK() {
    return m_topK;
}

void QtOllamaFrontend::setTopK(const int &topK) {
    if (topK != m_topK) {
        m_topK = topK;
        updateSetting(getSettingsKey(Settings::TopK), QString::number(topK));
        emit topKChanged();
    }
}

double QtOllamaFrontend::topP() {
    return m_topP;
}

void QtOllamaFrontend::setTopP(const double &topP) {
    if (topP != m_topP) {
        m_topP = topP;
        updateSetting(getSettingsKey(Settings::TopP), QString::number(topP));
        emit topPChanged();
    }
}

double QtOllamaFrontend::minP() {
    return m_minP;
}

void QtOllamaFrontend::setMinP(const double &minP) {
    if (minP != m_minP) {
        m_minP = minP;
        updateSetting(getSettingsKey(Settings::MinP), QString::number(minP));
        emit minPChanged();
    }
}

double QtOllamaFrontend::tfsZ() {
    return m_tfsZ;
}

void QtOllamaFrontend::setTfsZ(const double &tfsZ) {
    if (tfsZ != m_tfsZ) {
        m_tfsZ = tfsZ;
        updateSetting(getSettingsKey(Settings::TfsZ), QString::number(tfsZ));
        emit tfsZChanged();
    }
}

double QtOllamaFrontend::typicalP() {
    return m_typicalP;
}

void QtOllamaFrontend::setTypicalP(const double &typicalP) {
    if (typicalP != m_typicalP) {
        m_typicalP = typicalP;
        updateSetting(getSettingsKey(Settings::TypicalP), QString::number(typicalP));
        emit typicalPChanged();
    }
}

int QtOllamaFrontend::repeatLastN() {
    return m_repeatLastN;
}

void QtOllamaFrontend::setRepeatLastN(const int &repeatLastN) {
    if (repeatLastN != m_repeatLastN) {
        m_repeatLastN = repeatLastN;
        updateSetting(getSettingsKey(Settings::RepeatLastN), QString::number(repeatLastN));
        emit repeatLastNChanged();
    }
}

double QtOllamaFrontend::temperature() {
    return m_temperature;
}

void QtOllamaFrontend::setTemperature(const double &temperature) {
    if (temperature != m_temperature) {
        m_temperature = temperature;
        updateSetting(getSettingsKey(Settings::Temperature), QString::number(temperature));
        emit temperatureChanged();
    }
}

double QtOllamaFrontend::repeatPenalty() {
    return m_repeatPenalty;
}

void QtOllamaFrontend::setRepeatPenalty(const double &repeatPenalty) {
    if (repeatPenalty != m_repeatPenalty) {
        m_repeatPenalty = repeatPenalty;
        updateSetting(getSettingsKey(Settings::RepeatPenalty), QString::number(repeatPenalty));
        emit repeatPenaltyChanged();
    }
}

double QtOllamaFrontend::presencePenalty() {
    return m_presencePenalty;
}

void QtOllamaFrontend::setPresencePenalty(const double &presencePenalty) {
    if (presencePenalty != m_presencePenalty) {
        m_presencePenalty = presencePenalty;
        updateSetting(getSettingsKey(Settings::PresencePenalty), QString::number(presencePenalty));
        emit presencePenaltyChanged();
    }
}

double QtOllamaFrontend::frequencyPenalty() {
    return m_frequencyPenalty;
}

void QtOllamaFrontend::setFrequencyPenalty(const double &frequencyPenalty) {
    if (frequencyPenalty != m_frequencyPenalty) {
        m_frequencyPenalty = frequencyPenalty;
        updateSetting(getSettingsKey(Settings::FrequencyPenalty), QString::number(frequencyPenalty));
        emit frequencyPenaltyChanged();
    }
}

int QtOllamaFrontend::mirostat() {
    return m_mirostat;
}

void QtOllamaFrontend::setMirostat(const int &mirostat) {
    if (mirostat != m_mirostat) {
        m_mirostat = mirostat;
        updateSetting(getSettingsKey(Settings::Mirostat), QString::number(mirostat));
        emit mirostatChanged();
    }
}

double QtOllamaFrontend::mirostatTau() {
    return m_mirostatTau;
}

void QtOllamaFrontend::setMirostatTau(const double &mirostatTau) {
    if (mirostatTau != m_mirostatTau) {
        m_mirostatTau = mirostatTau;
        updateSetting(getSettingsKey(Settings::MirostatTau), QString::number(mirostatTau));
        emit mirostatTauChanged();
    }
}

double QtOllamaFrontend::mirostatEta() {
    return m_mirostatEta;
}

void QtOllamaFrontend::setMirostatEta(const double &mirostatEta) {
    if (mirostatEta != m_mirostatEta) {
        m_mirostatEta = mirostatEta;
        updateSetting(getSettingsKey(Settings::MirostatEta), QString::number(mirostatEta));
        emit mirostatEtaChanged();
    }
}

bool QtOllamaFrontend::penalizeNewline() {
    return m_penalizeNewline;
}

void QtOllamaFrontend::setPenalizeNewline(const bool &penalizeNewline) {
    if (penalizeNewline != m_penalizeNewline) {
        m_penalizeNewline = penalizeNewline;
        updateSetting(getSettingsKey(Settings::PenalizeNewline), penalizeNewline ? "1" : "0");
        emit penalizeNewlineChanged();
    }
}

QString QtOllamaFrontend::stop() {
    return m_stop;
}

void QtOllamaFrontend::setStop(const QString &stop) {
    if (stop != m_stop) {
        m_stop = stop;
        updateSetting(getSettingsKey(Settings::Stop), stop);
        emit stopChanged();
    }
}

bool QtOllamaFrontend::numa() {
    return m_numa;
}

void QtOllamaFrontend::setNuma(const bool &numa) {
    if (numa != m_numa) {
        m_numa = numa;
        updateSetting(getSettingsKey(Settings::Numa), numa ? "1" : "0");
        emit numaChanged();
    }
}

int QtOllamaFrontend::numCtx() {
    return m_numCtx;
}

void QtOllamaFrontend::setNumCtx(const int &numCtx) {
    if (numCtx != m_numCtx) {
        m_numCtx = numCtx;
        updateSetting(getSettingsKey(Settings::NumCtx), QString::number(numCtx));
        emit numCtxChanged();
    }
}

int QtOllamaFrontend::numBatch() {
    return m_numBatch;
}

void QtOllamaFrontend::setNumBatch(const int &numBatch) {
    if (numBatch != m_numBatch) {
        m_numBatch = numBatch;
        updateSetting(getSettingsKey(Settings::NumBatch), QString::number(numBatch));
        emit numBatchChanged();
    }
}

int QtOllamaFrontend::numGpu() {
    return m_numGpu;
}

void QtOllamaFrontend::setNumGpu(const int &numGpu) {
    if (numGpu != m_numGpu) {
        m_numGpu = numGpu;
        updateSetting(getSettingsKey(Settings::NumGpu), QString::number(numGpu));
        emit numGpuChanged();
    }
}

int QtOllamaFrontend::mainGpu() {
    return m_mainGpu;
}

void QtOllamaFrontend::setMainGpu(const int &mainGpu) {
    if (mainGpu != m_mainGpu) {
        m_mainGpu = mainGpu;
        updateSetting(getSettingsKey(Settings::MainGpu), QString::number(mainGpu));
        emit mainGpuChanged();
    }
}

bool QtOllamaFrontend::lowVram() {
    return m_lowVram;
}

void QtOllamaFrontend::setLowVram(const bool &lowVram) {
    if (lowVram != m_lowVram) {
        m_lowVram = lowVram;
        updateSetting(getSettingsKey(Settings::LowVram), lowVram ? "1" : "0");
        emit lowVramChanged();
    }
}

bool QtOllamaFrontend::vocabOnly() {
    return m_vocabOnly;
}

void QtOllamaFrontend::setVocabOnly(const bool &vocabOnly) {
    if (vocabOnly != m_vocabOnly) {
        m_vocabOnly = vocabOnly;
        updateSetting(getSettingsKey(Settings::VocabOnly), vocabOnly ? "1" : "0");
        emit vocabOnlyChanged();
    }
}

bool QtOllamaFrontend::useMmap() {
    return m_useMmap;
}

void QtOllamaFrontend::setUseMmap(const bool &useMmap) {
    if (useMmap != m_useMmap) {
        m_useMmap = useMmap;
        updateSetting(getSettingsKey(Settings::UseMmap), useMmap ? "1" : "0");
        emit useMmapChanged();
    }
}

bool QtOllamaFrontend::useMlock() {
    return m_useMlock;
}

void QtOllamaFrontend::setUseMlock(const bool &useMlock) {
    if (useMlock != m_useMlock) {
        m_useMlock = useMlock;
        updateSetting(getSettingsKey(Settings::UseMlock), useMlock ? "1" : "0");
        emit useMlockChanged();
    }
}

int QtOllamaFrontend::numThread() {
    return m_numThread;
}

void QtOllamaFrontend::setNumThread(const int &numThread) {
    if (numThread != m_numThread) {
        m_numThread = numThread;
        updateSetting(getSettingsKey(Settings::NumThread), QString::number(numThread));
        emit numThreadChanged();
    }
}

bool QtOllamaFrontend::seedApplied() {
    return m_seedApplied;
}

void QtOllamaFrontend::setSeedApplied(const bool &seedApplied) {
    if (seedApplied != m_seedApplied) {
        m_seedApplied = seedApplied;
        updateSetting(getSettingsKey(Settings::SeedApplied), seedApplied ? "1" : "0");
        emit seedAppliedChanged();
    }
}

bool QtOllamaFrontend::numKeepApplied() {
    return m_numKeepApplied;
}

void QtOllamaFrontend::setNumKeepApplied(const bool &numKeepApplied) {
    if (numKeepApplied != m_numKeepApplied) {
        m_numKeepApplied = numKeepApplied;
        updateSetting(getSettingsKey(Settings::NumKeepApplied), numKeepApplied ? "1" : "0");
        emit numKeepAppliedChanged();
    }
}

bool QtOllamaFrontend::numPredictApplied() {
    return m_numPredictApplied;
}

void QtOllamaFrontend::setNumPredictApplied(const bool &numPredictApplied) {
    if (numPredictApplied != m_numPredictApplied) {
        m_numPredictApplied = numPredictApplied;
        updateSetting(getSettingsKey(Settings::NumPredictApplied), numPredictApplied ? "1" : "0");
        emit numPredictAppliedChanged();
    }
}

bool QtOllamaFrontend::topKApplied() {
    return m_topKApplied;
}

void QtOllamaFrontend::setTopKApplied(const bool &topKApplied) {
    if (topKApplied != m_topKApplied) {
        m_topKApplied = topKApplied;
        updateSetting(getSettingsKey(Settings::TopKApplied), topKApplied ? "1" : "0");
        emit topKAppliedChanged();
    }
}

bool QtOllamaFrontend::topPApplied() {
    return m_topPApplied;
}

void QtOllamaFrontend::setTopPApplied(const bool &topPApplied) {
    if (topPApplied != m_topPApplied) {
        m_topPApplied = topPApplied;
        updateSetting(getSettingsKey(Settings::TopPApplied), topPApplied ? "1" : "0");
        emit topPAppliedChanged();
    }
}

bool QtOllamaFrontend::minPApplied() {
    return m_minPApplied;
}

void QtOllamaFrontend::setMinPApplied(const bool &minPApplied) {
    if (minPApplied != m_minPApplied) {
        m_minPApplied = minPApplied;
        updateSetting(getSettingsKey(Settings::MinPApplied), minPApplied ? "1" : "0");
        emit minPAppliedChanged();
    }
}

bool QtOllamaFrontend::tfsZApplied() {
    return m_tfsZApplied;
}

void QtOllamaFrontend::setTfsZApplied(const bool &tfsZApplied) {
    if (tfsZApplied != m_tfsZApplied) {
        m_tfsZApplied = tfsZApplied;
        updateSetting(getSettingsKey(Settings::TfsZApplied), tfsZApplied ? "1" : "0");
        emit tfsZAppliedChanged();
    }
}

bool QtOllamaFrontend::typicalPApplied() {
    return m_typicalPApplied;
}

void QtOllamaFrontend::setTypicalPApplied(const bool &typicalPApplied) {
    if (typicalPApplied != m_typicalPApplied) {
        m_typicalPApplied = typicalPApplied;
        updateSetting(getSettingsKey(Settings::TypicalPApplied), typicalPApplied ? "1" : "0");
        emit typicalPAppliedChanged();
    }
}

bool QtOllamaFrontend::repeatLastNApplied() {
    return m_repeatLastNApplied;
}

void QtOllamaFrontend::setRepeatLastNApplied(const bool &repeatLastNApplied) {
    if (repeatLastNApplied != m_repeatLastNApplied) {
        m_repeatLastNApplied = repeatLastNApplied;
        updateSetting(getSettingsKey(Settings::RepeatLastNApplied), repeatLastNApplied ? "1" : "0");
        emit repeatLastNAppliedChanged();
    }
}

bool QtOllamaFrontend::temperatureApplied() {
    return m_temperatureApplied;
}

void QtOllamaFrontend::setTemperatureApplied(const bool &temperatureApplied) {
    if (temperatureApplied != m_temperatureApplied) {
        m_temperatureApplied = temperatureApplied;
        updateSetting(getSettingsKey(Settings::TemperatureApplied), temperatureApplied ? "1" : "0");
        emit temperatureAppliedChanged();
    }
}

bool QtOllamaFrontend::repeatPenaltyApplied() {
    return m_repeatPenaltyApplied;
}

void QtOllamaFrontend::setRepeatPenaltyApplied(const bool &repeatPenaltyApplied) {
    if (repeatPenaltyApplied != m_repeatPenaltyApplied) {
        m_repeatPenaltyApplied = repeatPenaltyApplied;
        updateSetting(getSettingsKey(Settings::RepeatPenaltyApplied), repeatPenaltyApplied ? "1" : "0");
        emit repeatPenaltyAppliedChanged();
    }
}

bool QtOllamaFrontend::presencePenaltyApplied() {
    return m_presencePenaltyApplied;
}

void QtOllamaFrontend::setPresencePenaltyApplied(const bool &presencePenaltyApplied) {
    if (presencePenaltyApplied != m_presencePenaltyApplied) {
        m_presencePenaltyApplied = presencePenaltyApplied;
        updateSetting(getSettingsKey(Settings::PresencePenaltyApplied), presencePenaltyApplied ? "1" : "0");
        emit presencePenaltyAppliedChanged();
    }
}

bool QtOllamaFrontend::frequencyPenaltyApplied() {
    return m_frequencyPenaltyApplied;
}

void QtOllamaFrontend::setFrequencyPenaltyApplied(const bool &frequencyPenaltyApplied) {
    if (frequencyPenaltyApplied != m_frequencyPenaltyApplied) {
        m_frequencyPenaltyApplied = frequencyPenaltyApplied;
        updateSetting(getSettingsKey(Settings::FrequencyPenaltyApplied), frequencyPenaltyApplied ? "1" : "0");
        emit frequencyPenaltyAppliedChanged();
    }
}

bool QtOllamaFrontend::mirostatApplied() {
    return m_mirostatApplied;
}

void QtOllamaFrontend::setMirostatApplied(const bool &mirostatApplied) {
    if (mirostatApplied != m_mirostatApplied) {
        m_mirostatApplied = mirostatApplied;
        updateSetting(getSettingsKey(Settings::MirostatApplied), mirostatApplied ? "1" : "0");
        emit mirostatAppliedChanged();
    }
}

bool QtOllamaFrontend::mirostatTauApplied() {
    return m_mirostatTauApplied;
}

void QtOllamaFrontend::setMirostatTauApplied(const bool &mirostatTauApplied) {
    if (mirostatTauApplied != m_mirostatTauApplied) {
        m_mirostatTauApplied = mirostatTauApplied;
        updateSetting(getSettingsKey(Settings::MirostatTauApplied), mirostatTauApplied ? "1" : "0");
        emit mirostatTauAppliedChanged();
    }
}

bool QtOllamaFrontend::mirostatEtaApplied() {
    return m_mirostatEtaApplied;
}

void QtOllamaFrontend::setMirostatEtaApplied(const bool &mirostatEtaApplied) {
    if (mirostatEtaApplied != m_mirostatEtaApplied) {
        m_mirostatEtaApplied = mirostatEtaApplied;
        updateSetting(getSettingsKey(Settings::MirostatEtaApplied), mirostatEtaApplied ? "1" : "0");
        emit mirostatEtaAppliedChanged();
    }
}

bool QtOllamaFrontend::penalizeNewlineApplied() {
    return m_penalizeNewlineApplied;
}

void QtOllamaFrontend::setPenalizeNewlineApplied(const bool &penalizeNewlineApplied) {
    if (penalizeNewlineApplied != m_penalizeNewlineApplied) {
        m_penalizeNewlineApplied = penalizeNewlineApplied;
        updateSetting(getSettingsKey(Settings::PenalizeNewlineApplied), penalizeNewlineApplied ? "1" : "0");
        emit penalizeNewlineAppliedChanged();
    }
}

bool QtOllamaFrontend::stopApplied() {
    return m_stopApplied;
}

void QtOllamaFrontend::setStopApplied(const bool &stopApplied) {
    if (stopApplied != m_stopApplied) {
        m_stopApplied = stopApplied;
        updateSetting(getSettingsKey(Settings::StopApplied), stopApplied ? "1" : "0");
        emit stopAppliedChanged();
    }
}

bool QtOllamaFrontend::numaApplied() {
    return m_numaApplied;
}

void QtOllamaFrontend::setNumaApplied(const bool &numaApplied) {
    if (numaApplied != m_numaApplied) {
        m_numaApplied = numaApplied;
        updateSetting(getSettingsKey(Settings::NumaApplied), numaApplied ? "1" : "0");
        emit numaAppliedChanged();
    }
}

bool QtOllamaFrontend::numCtxApplied() {
    return m_numCtxApplied;
}

void QtOllamaFrontend::setNumCtxApplied(const bool &numCtxApplied) {
    if (numCtxApplied != m_numCtxApplied) {
        m_numCtxApplied = numCtxApplied;
        updateSetting(getSettingsKey(Settings::NumCtxApplied), numCtxApplied ? "1" : "0");
        emit numCtxAppliedChanged();
    }
}

bool QtOllamaFrontend::numBatchApplied() {
    return m_numBatchApplied;
}

void QtOllamaFrontend::setNumBatchApplied(const bool &numBatchApplied) {
    if (numBatchApplied != m_numBatchApplied) {
        m_numBatchApplied = numBatchApplied;
        updateSetting(getSettingsKey(Settings::NumBatchApplied), numBatchApplied ? "1" : "0");
        emit numBatchAppliedChanged();
    }
}

bool QtOllamaFrontend::numGpuApplied() {
    return m_numGpuApplied;
}

void QtOllamaFrontend::setNumGpuApplied(const bool &numGpuApplied) {
    if (numGpuApplied != m_numGpuApplied) {
        m_numGpuApplied = numGpuApplied;
        updateSetting(getSettingsKey(Settings::NumGpuApplied), numGpuApplied ? "1" : "0");
        emit numGpuAppliedChanged();
    }
}

bool QtOllamaFrontend::mainGpuApplied() {
    return m_mainGpuApplied;
}

void QtOllamaFrontend::setMainGpuApplied(const bool &mainGpuApplied) {
    if (mainGpuApplied != m_mainGpuApplied) {
        m_mainGpuApplied = mainGpuApplied;
        updateSetting(getSettingsKey(Settings::MainGpuApplied), mainGpuApplied ? "1" : "0");
        emit mainGpuAppliedChanged();
    }
}

bool QtOllamaFrontend::lowVramApplied() {
    return m_lowVramApplied;
}

void QtOllamaFrontend::setLowVramApplied(const bool &lowVramApplied) {
    if (lowVramApplied != m_lowVramApplied) {
        m_lowVramApplied = lowVramApplied;
        updateSetting(getSettingsKey(Settings::LowVramApplied), lowVramApplied ? "1" : "0");
        emit lowVramAppliedChanged();
    }
}

bool QtOllamaFrontend::vocabOnlyApplied() {
    return m_vocabOnlyApplied;
}

void QtOllamaFrontend::setVocabOnlyApplied(const bool &vocabOnlyApplied) {
    if (vocabOnlyApplied != m_vocabOnlyApplied) {
        m_vocabOnlyApplied = vocabOnlyApplied;
        updateSetting(getSettingsKey(Settings::VocabOnlyApplied), vocabOnlyApplied ? "1" : "0");
        emit vocabOnlyAppliedChanged();
    }
}

bool QtOllamaFrontend::useMmapApplied() {
    return m_useMmapApplied;
}

void QtOllamaFrontend::setUseMmapApplied(const bool &useMmapApplied) {
    if (useMmapApplied != m_useMmapApplied) {
        m_useMmapApplied = useMmapApplied;
        updateSetting(getSettingsKey(Settings::UseMmapApplied), useMmapApplied ? "1" : "0");
        emit useMmapAppliedChanged();
    }
}

bool QtOllamaFrontend::useMlockApplied() {
    return m_useMlockApplied;
}

void QtOllamaFrontend::setUseMlockApplied(const bool &useMlockApplied) {
    if (useMlockApplied != m_useMlockApplied) {
        m_useMlockApplied = useMlockApplied;
        updateSetting(getSettingsKey(Settings::UseMlockApplied), useMlockApplied ? "1" : "0");
        emit useMlockAppliedChanged();
    }
}

bool QtOllamaFrontend::numThreadApplied() {
    return m_numThreadApplied;
}

void QtOllamaFrontend::setNumThreadApplied(const bool &numThreadApplied) {
    if (numThreadApplied != m_numThreadApplied) {
        m_numThreadApplied = numThreadApplied;
        updateSetting(getSettingsKey(Settings::NumThreadApplied), numThreadApplied ? "1" : "0");
        emit numThreadAppliedChanged();
    }
}

QString QtOllamaFrontend::getSetting(QString key) {
    QJsonObject setting = m_databaseComponent->getSetting(key);

    return setting.value("value").toString();
}

QString QtOllamaFrontend::getSettingsKey(int key) {
    switch (key) {
        // api
        case Settings::ApiHost: return "api_host";
        case Settings::ApiPort: return "api_port";
        case Settings::ApiModelName: return "api_model_name";
        // settings
        case Settings::ScaledImageWidth: return "scaled_image_width";
        case Settings::ScaledImageHeight: return "scaled_image_height";
        case Settings::ShowLog: return "show_log";
        case Settings::OutputTts: return "output_tts";
        case Settings::TextMessageMultiline: return "text_message_multiline";
        case Settings::TtsEngine: return "tts_engine";
        case Settings::TtsLocale: return "tts_locale";
        case Settings::TtsVoice: return "tts_voice";
        case Settings::TtsVolume: return "tts_volume";
        case Settings::TtsRate: return "tts_rate";
        case Settings::TtsPitch: return "tts_pitch";
        // options
        case Settings::Seed: return "seed";
        case Settings::NumKeep: return "num_keep";
        case Settings::NumPredict: return "num_predict";
        case Settings::TopK: return "top_k";
        case Settings::TopP: return "top_p";
        case Settings::MinP: return "min_p";
        case Settings::TfsZ: return "tfs_z";
        case Settings::TypicalP: return "typical_p";
        case Settings::RepeatLastN: return "repeat_last_n";
        case Settings::Temperature: return "temperature";
        case Settings::RepeatPenalty: return "repeat_penalty";
        case Settings::PresencePenalty: return "presence_penalty";
        case Settings::FrequencyPenalty: return "frequency_penalty";
        case Settings::Mirostat: return "mirostat";
        case Settings::MirostatTau: return "mirostat_tau";
        case Settings::MirostatEta: return "mirostat_eta";
        case Settings::PenalizeNewline: return "penalize_newline";
        case Settings::Stop: return "stop";
        case Settings::Numa: return "numa";
        case Settings::NumCtx: return "num_ctx";
        case Settings::NumBatch: return "num_batch";
        case Settings::NumGpu: return "num_gpu";
        case Settings::MainGpu: return "main_gpu";
        case Settings::LowVram: return "low_vram";
        case Settings::VocabOnly: return "vocab_only";
        case Settings::UseMmap: return "use_mmap";
        case Settings::UseMlock: return "use_mlock";
        case Settings::NumThread: return "num_thread";
        case Settings::SeedApplied: return "seed_applied";
        case Settings::NumKeepApplied: return "num_keep_applied";
        case Settings::NumPredictApplied: return "num_predict_applied";
        case Settings::TopKApplied: return "top_k_applied";
        case Settings::TopPApplied: return "top_p_applied";
        case Settings::MinPApplied: return "min_p_applied";
        case Settings::TfsZApplied: return "tfs_z_applied";
        case Settings::TypicalPApplied: return "typical_p_applied";
        case Settings::RepeatLastNApplied: return "repeat_last_n_applied";
        case Settings::TemperatureApplied: return "temperature_applied";
        case Settings::RepeatPenaltyApplied: return "repeat_penalty_applied";
        case Settings::PresencePenaltyApplied: return "presence_penalty_applied";
        case Settings::FrequencyPenaltyApplied: return "frequency_penalty_applied";
        case Settings::MirostatApplied: return "mirostat_applied";
        case Settings::MirostatTauApplied: return "mirostat_tau_applied";
        case Settings::MirostatEtaApplied: return "mirostat_eta_applied";
        case Settings::PenalizeNewlineApplied: return "penalize_newline_applied";
        case Settings::StopApplied: return "stop_applied";
        case Settings::NumaApplied: return "numa_applied";
        case Settings::NumCtxApplied: return "num_ctx_applied";
        case Settings::NumBatchApplied: return "num_batch_applied";
        case Settings::NumGpuApplied: return "num_gpu_applied";
        case Settings::MainGpuApplied: return "main_gpu_applied";
        case Settings::LowVramApplied: return "low_vram_applied";
        case Settings::VocabOnlyApplied: return "vocab_only_applied";
        case Settings::UseMmapApplied: return "use_mmap_applied";
        case Settings::UseMlockApplied: return "use_mlock_applied";
        case Settings::NumThreadApplied: return "num_thread_applied";
        default: return "";
    };

    return "";
}

QString QtOllamaFrontend::getDefaultSetting(int key) {
    switch (key) {
        // api
        case Settings::ApiHost: return API_HOST;
        case Settings::ApiPort: return QString::number(API_PORT);
        case Settings::ApiModelName: return API_MODEL_NAME;
        // settings
        case Settings::ScaledImageWidth: return QString::number(SCALED_IMAGE_WIDTH);
        case Settings::ScaledImageHeight: return QString::number(SCALED_IMAGE_HEIGHT);
        case Settings::ShowLog: return SHOW_LOG ? "1" : "0";
        case Settings::OutputTts: return OUTPUT_TTS ? "1" : "0";
        case Settings::TextMessageMultiline: return TEXT_MESSAGE_MULTILINE ? "1" : "0";
        case Settings::TtsEngine: return "";
        case Settings::TtsLocale: return "";
        case Settings::TtsVoice: return "";
        case Settings::TtsVolume: return QString::number(TTS_VOLUME);
        case Settings::TtsRate: return QString::number(TTS_RATE);
        case Settings::TtsPitch: return QString::number(TTS_PITCH);
        // options
        case Settings::Seed: return QString::number(SEED);
        case Settings::NumKeep: return QString::number(NUM_KEEP);
        case Settings::NumPredict: return QString::number(NUM_PREDICT);
        case Settings::TopK: return QString::number(TOP_K);
        case Settings::TopP: return QString::number(TOP_P);
        case Settings::MinP: return QString::number(MIN_P);
        case Settings::TfsZ: return QString::number(TFS_Z);
        case Settings::TypicalP: return QString::number(TYPICAL_P);;
        case Settings::RepeatLastN: return QString::number(REPEAT_LAST_N);
        case Settings::Temperature: return QString::number(TEMPERATURE);
        case Settings::RepeatPenalty: return QString::number(REPEAT_PENALTY);
        case Settings::PresencePenalty: return QString::number(PRESENCE_PENALTY);
        case Settings::FrequencyPenalty: return QString::number(FREQUENCY_PENALTY);
        case Settings::Mirostat: return QString::number(MIROSTAT);
        case Settings::MirostatTau: return QString::number(MIROSTAT_TAU);
        case Settings::MirostatEta: return QString::number(MIROSTAT_ETA);
        case Settings::PenalizeNewline: return PENALIZE_NEWLINE ? "1" : "0";
        case Settings::Stop: return STOP;
        case Settings::Numa: return NUMA ? "1" : "0";
        case Settings::NumCtx: return QString::number(NUM_CTX);
        case Settings::NumBatch: return QString::number(NUM_BATCH);
        case Settings::NumGpu: return QString::number(NUM_GPU);
        case Settings::MainGpu: return QString::number(MAIN_GPU);
        case Settings::LowVram: return LOW_VRAM ? "1" : "0";
        case Settings::VocabOnly: return VOCAB_ONLY ? "1" : "0";
        case Settings::UseMmap: return USE_MMAP ? "1" : "0";
        case Settings::UseMlock: return USE_MLOCK ? "1" : "0";
        case Settings::NumThread: return QString::number(NUM_THREAD);
        case Settings::SeedApplied: return "0";
        case Settings::NumKeepApplied: return "0";
        case Settings::NumPredictApplied: return "0";
        case Settings::TopKApplied: return "0";
        case Settings::TopPApplied: return "0";
        case Settings::MinPApplied: return "0";
        case Settings::TfsZApplied: return "0";
        case Settings::TypicalPApplied: return "0";
        case Settings::RepeatLastNApplied: return "0";
        case Settings::TemperatureApplied: return "0";
        case Settings::RepeatPenaltyApplied: return "0";
        case Settings::PresencePenaltyApplied: return "0";
        case Settings::FrequencyPenaltyApplied: return "0";
        case Settings::MirostatApplied: return "0";
        case Settings::MirostatTauApplied: return "0";
        case Settings::MirostatEtaApplied: return "0";
        case Settings::PenalizeNewlineApplied: return "0";
        case Settings::StopApplied: return "0";
        case Settings::NumaApplied: return "0";
        case Settings::NumCtxApplied: return "0";
        case Settings::NumBatchApplied: return "0";
        case Settings::NumGpuApplied: return "0";
        case Settings::MainGpuApplied: return "0";
        case Settings::LowVramApplied: return "0";
        case Settings::VocabOnlyApplied: return "0";
        case Settings::UseMmapApplied: return "0";
        case Settings::UseMlockApplied: return "0";
        case Settings::NumThreadApplied: return "0";
        default: return "";
    };

    return "";
}

void QtOllamaFrontend::resetSetting(int key) {
    switch (key) {
        // api
        case Settings::ApiHost: setHost(API_HOST); break;
        case Settings::ApiPort: setPort(API_PORT); break;
        case Settings::ApiModelName: setModelName(API_MODEL_NAME); break;
        // settings
        case Settings::ScaledImageWidth: setScaledImageWidth(SCALED_IMAGE_WIDTH); break;
        case Settings::ScaledImageHeight: setScaledImageHeight(SCALED_IMAGE_HEIGHT); break;
        case Settings::ShowLog: setShowLog(SHOW_LOG); break;
        case Settings::OutputTts: setOutputTts(OUTPUT_TTS); break;
        case Settings::TextMessageMultiline: setTextMessageMultiline(TEXT_MESSAGE_MULTILINE); break;
        case Settings::TtsEngine: setTtsEngine(""); break;
        case Settings::TtsLocale: setTtsLocale(""); break;
        case Settings::TtsVoice: setTtsVoice(""); break;
        case Settings::TtsVolume: setTtsVolume(TTS_VOLUME); break;
        case Settings::TtsRate: setTtsRate(TTS_RATE); break;
        case Settings::TtsPitch: setTtsPitch(TTS_PITCH); break;
        // options
        case Settings::Seed: setSeed(SEED); break;
        case Settings::NumKeep: setNumKeep(NUM_KEEP); break;
        case Settings::NumPredict: setNumPredict(NUM_PREDICT); break;
        case Settings::TopK: setTopK(TOP_K); break;
        case Settings::TopP: setTopP(TOP_P); break;
        case Settings::MinP: setMinP(MIN_P); break;
        case Settings::TfsZ: setTfsZ(TFS_Z); break;
        case Settings::TypicalP: setTypicalP(TYPICAL_P); break;
        case Settings::RepeatLastN: setRepeatLastN(REPEAT_LAST_N); break;
        case Settings::Temperature: setTemperature(TEMPERATURE); break;
        case Settings::RepeatPenalty: setRepeatPenalty(REPEAT_PENALTY); break;
        case Settings::PresencePenalty: setPresencePenalty(PRESENCE_PENALTY); break;
        case Settings::FrequencyPenalty: setFrequencyPenalty(FREQUENCY_PENALTY); break;
        case Settings::Mirostat: setMirostat(MIROSTAT); break;
        case Settings::MirostatTau: setMirostatTau(MIROSTAT_TAU); break;
        case Settings::MirostatEta: setMirostatEta(MIROSTAT_ETA); break;
        case Settings::PenalizeNewline: setPenalizeNewline(PENALIZE_NEWLINE); break;
        case Settings::Stop: setStop(STOP); break;
        case Settings::Numa: setNuma(NUMA); break;
        case Settings::NumCtx: setNumCtx(NUM_CTX); break;
        case Settings::NumBatch: setNumBatch(NUM_BATCH); break;
        case Settings::NumGpu: setNumGpu(NUM_GPU); break;
        case Settings::MainGpu: setMainGpu(MAIN_GPU); break;
        case Settings::LowVram: setLowVram(LOW_VRAM); break;
        case Settings::VocabOnly: setVocabOnly(VOCAB_ONLY); break;
        case Settings::UseMmap: setUseMmap(USE_MMAP); break;
        case Settings::UseMlock: setUseMlock(USE_MLOCK); break;
        case Settings::NumThread: setNumThread(NUM_THREAD); break;
        case Settings::SeedApplied: setSeedApplied(false); break;
        case Settings::NumKeepApplied: setNumKeepApplied(false); break;
        case Settings::NumPredictApplied: setNumPredictApplied(false); break;
        case Settings::TopKApplied: setTopKApplied(false); break;
        case Settings::TopPApplied: setTopPApplied(false); break;
        case Settings::MinPApplied: setMinPApplied(false); break;
        case Settings::TfsZApplied: setTfsZApplied(false); break;
        case Settings::TypicalPApplied: setTypicalPApplied(false); break;
        case Settings::RepeatLastNApplied: setRepeatLastNApplied(false); break;
        case Settings::TemperatureApplied: setTemperatureApplied(false); break;
        case Settings::RepeatPenaltyApplied: setRepeatPenaltyApplied(false); break;
        case Settings::PresencePenaltyApplied: setPresencePenaltyApplied(false); break;
        case Settings::FrequencyPenaltyApplied: setFrequencyPenaltyApplied(false); break;
        case Settings::MirostatApplied: setMirostatApplied(false); break;
        case Settings::MirostatTauApplied: setMirostatTauApplied(false); break;
        case Settings::MirostatEtaApplied: setMirostatEtaApplied(false); break;
        case Settings::PenalizeNewlineApplied: setPenalizeNewlineApplied(false); break;
        case Settings::StopApplied: setStopApplied(false); break;
        case Settings::NumaApplied: setNumaApplied(false); break;
        case Settings::NumCtxApplied: setNumCtxApplied(false); break;
        case Settings::NumBatchApplied: setNumBatchApplied(false); break;
        case Settings::NumGpuApplied: setNumGpuApplied(false); break;
        case Settings::MainGpuApplied: setMainGpuApplied(false); break;
        case Settings::LowVramApplied: setLowVramApplied(false); break;
        case Settings::VocabOnlyApplied: setVocabOnlyApplied(false); break;
        case Settings::UseMmapApplied: setUseMmapApplied(false); break;
        case Settings::UseMlockApplied: setUseMlockApplied(false); break;
        case Settings::NumThreadApplied: setNumThreadApplied(false); break;
        default: break;
    };
}

void QtOllamaFrontend::resetSettings(QVariantList keys) {
    for (int i = 0; i < keys.size(); i++) {
        int key = keys[i].toInt();
        resetSetting(key);
    }
}

void QtOllamaFrontend::copyTextToClipboard(QString text) {
    qDebug() << "copy to cliepboard:" << text;
    m_clipboard->setText(text);
}

QJsonObject QtOllamaFrontend::getSelectedOptions() {
    QJsonObject options;

    if (m_seedApplied) {
        options.insert("seed", QJsonValue(m_seed));
    }
    if (m_numKeepApplied) {
        options.insert("num_keep", QJsonValue(m_numKeep));
    }
    if (m_numPredictApplied) {
        options.insert("num_predict", QJsonValue(m_numPredict));
    }
    if (m_topKApplied) {
        options.insert("top_k", QJsonValue(m_topK));
    }
    if (m_topPApplied) {
        options.insert("top_p", QJsonValue(m_topP));
    }
    if (m_minPApplied) {
        options.insert("min_p", QJsonValue(m_minP));
    }
    if (m_tfsZApplied) {
        options.insert("tfs_z", QJsonValue(m_tfsZ));
    }
    if (m_typicalPApplied) {
        options.insert("typical_p", QJsonValue(m_typicalP));
    }
    if (m_repeatLastNApplied) {
        options.insert("repeat_last_n", QJsonValue(m_repeatLastN));
    }
    if (m_temperatureApplied) {
        options.insert("temperature", QJsonValue(m_temperature));
    }
    if (m_repeatPenaltyApplied) {
        options.insert("repeat_penalty", QJsonValue(m_repeatPenalty));
    }
    if (m_presencePenaltyApplied) {
        options.insert("presence_penalty", QJsonValue(m_presencePenalty));
    }
    if (m_frequencyPenaltyApplied) {
        options.insert("frequency_penalty", QJsonValue(m_frequencyPenalty));
    }
    if (m_mirostatApplied) {
        options.insert("mirostat", QJsonValue(m_mirostat));
    }
    if (m_mirostatTauApplied) {
        options.insert("mirostat_tau", QJsonValue(m_mirostatTau));
    }
    if (m_mirostatEtaApplied) {
        options.insert("mirostat_eta", QJsonValue(m_mirostatEta));
    }
    if (m_penalizeNewlineApplied) {
        options.insert("penalize_newline", QJsonValue(m_penalizeNewline));
    }
    if (m_stopApplied) {
        options.insert("stop", QJsonValue(m_stop));
    }
    if (m_numaApplied) {
        options.insert("numa", QJsonValue(m_numa));
    }
    if (m_numCtxApplied) {
        options.insert("num_ctx", QJsonValue(m_numCtx));
    }
    if (m_numBatchApplied) {
        options.insert("num_batch", QJsonValue(m_numBatch));
    }
    if (m_numGpuApplied) {
        options.insert("num_gpu", QJsonValue(m_numGpu));
    }
    if (m_mainGpuApplied) {
        options.insert("main_gpu", QJsonValue(m_mainGpu));
    }
    if (m_lowVramApplied) {
        options.insert("low_vram", QJsonValue(m_lowVram));
    }
    if (m_vocabOnlyApplied) {
        options.insert("vocab_only", QJsonValue(m_vocabOnly));
    }
    if (m_useMmapApplied) {
        options.insert("use_mmap", QJsonValue(m_useMmap));
    }
    if (m_useMlockApplied) {
        options.insert("use_mlock", QJsonValue(m_useMlock));
    }
    if (m_numThreadApplied) {
        options.insert("num_thread", QJsonValue(m_numThread));
    }

    return options;
}

void QtOllamaFrontend::sendMessage(QString content, QString jsonImageFilePaths) {
    if (content.isNull() || content.isEmpty()) {
        return;
    }

    setLoading(true);

    // add new message to message history
    QJsonObject message;
    message.insert("role", "user");
    message.insert("content", QJsonValue(content));

    // process json string of file paths to images
    QJsonArray imageFilePaths;
    if (!jsonImageFilePaths.isNull() && !jsonImageFilePaths.isEmpty()) {
        imageFilePaths = convertToJsonArray(jsonImageFilePaths);
    }
    QJsonArray images;
    for (int i = 0; i < imageFilePaths.count(); i++) {
        QString imageFilePath = imageFilePaths[i].toString();

        if (imageFilePath.startsWith("file:///")) {
            for (int j = 0; j < QString("file:///").size(); j++) {
                imageFilePath.removeFirst();
            }
        }

        if (imageFilePath.isNull() || imageFilePath.isEmpty()) {
            continue;
        }

        QImage image(imageFilePath);
        if ((m_scaledImageWidth > 0) && (m_scaledImageHeight > 0)) {
            // scale image down
            image = image.scaled(QSize(m_scaledImageWidth, m_scaledImageHeight), Qt::KeepAspectRatio);
        }
        QByteArray imageData = getImageBytes(image);
        QString imageBase64 = convertImageBytesToBase64(imageData);

        images.append(QJsonValue(imageBase64));
    }
    if (images.count() > 0) {
        message.insert("images", images);
    }

    m_messages.append(QJsonValue(message));

    // form json object for parameters
    QJsonObject params;
    params.insert("model", QJsonValue(m_modelName));
    params.insert("messages", m_messages);
    //params.insert("format", QJsonValue("json"));
    params.insert("stream", QJsonValue(false));

    // options
    QJsonObject options = getSelectedOptions();
    if (options.keys().size() > 0) {
        params.insert("options", options);
    }

    // convert json object to QByteArray
    QByteArray jsonBytes = convertToBytes(params);
    outputRequest(prepareJsonForLogOutput(params));

    // form url
    QUrl url("http://" + m_host + ":" + QString::number(m_port) + API_CHAT_URI);

    // form request object
    QNetworkRequest request = createNetworkRequest(url, jsonBytes);

    // output log
    emit log("json sent message", prepareJsonForLogOutput(params));

    // send request
    QNetworkReply* reply = m_networkAccessManager->post(request, jsonBytes);
    connect(reply, SIGNAL(downloadProgress(qint64,qint64)),
            this, SLOT(downloadProgress(qint64,qint64)));
    connect(reply, SIGNAL(uploadProgress(qint64,qint64)),
            this, SLOT(uploadProgress(qint64,qint64)));
    connect(reply, &QNetworkReply::finished, [this, reply]() {
        setLoading(false);

        if (reply->error() != QNetworkReply::NoError) {
            emitNetworkError(reply);
            return;
        }

        QByteArray data = reply->readAll();
        outputResponse(data);

        // add new message to message history
        QJsonObject receivedMessage = convertToJsonObject(data);
        QJsonObject extractedMessage = receivedMessage.value("message").toObject();

        // output log
        emit log("json response", prepareJsonForLogOutput(receivedMessage));

        QJsonObject message;
        message.insert("role", "assistant");
        message.insert("content", QJsonValue(extractedMessage.value("content")));
        m_messages.append(QJsonValue(message));

        // output received message
        emit receivedResponse(data);

        // output tts
        if (m_outputTts) {
            emit say(message.value("content").toString());
        }
    });
}

void QtOllamaFrontend::startNewChat() {
    m_messages = QJsonArray();
    emit receivedNewChatStarted();
}

void QtOllamaFrontend::exportChatMessages(QString targetFilePath, ExportFormat format, ExportMessageSelection messageSelection) {
    qDebug() << targetFilePath << format << messageSelection;

    // remove "file:///" from file path
    if (targetFilePath.startsWith("file:///")) {
        for (int j = 0; j < QString("file:///").size(); j++) {
            targetFilePath.removeFirst();
        }
    }

    QJsonArray exportMessages;

    for (QJsonValue jsonValue : m_messages) {
        QJsonObject message = jsonValue.toObject();

        if (messageSelection == ExportMessageSelectionAllMessages
         || ((messageSelection == ExportMessageSelectionOnlyUserMessages) && (message.value("role").toString() == "user"))
         || ((messageSelection == ExportMessageSelectionOnlyAssistantMessages) && (message.value("role").toString() == "assistant"))) {
            exportMessages.append(QJsonObject(message));
        }
    }

    // save to file
    QString fileContent = "";
    if (format == ExportFormatJson) {
        fileContent = convertToBytes(exportMessages);
    } else if (format == ExportFormatPlainText) {
        for (QJsonValue jsonValue : exportMessages) {
            QJsonObject message = jsonValue.toObject();
            fileContent += message.value("role").toString() + ":\n" + message.value("content").toString() + "\n\n--------------------------------------------------\n\n";
        }
    }

    QFile file(targetFilePath);
    if (!file.open(QFile::WriteOnly)) {
        qDebug() << "cannot write to file" << targetFilePath;
        return;
    }

    file.write(fileContent.toUtf8());

    file.close();
}

void QtOllamaFrontend::getModels() {
    setLoading(true);

    // form url
    QUrl url("http://" + m_host + ":" + QString::number(m_port) + API_TAGS_URI);

    // form request object
    QNetworkRequest request = createNetworkRequest(url);

    // output log
    emit log("sent GET request:", url.toString());

    // send request
    QNetworkReply* reply = m_networkAccessManager->get(request);
    connect(reply, SIGNAL(downloadProgress(qint64,qint64)),
            this, SLOT(downloadProgress(qint64,qint64)));
    connect(reply, SIGNAL(uploadProgress(qint64,qint64)),
            this, SLOT(uploadProgress(qint64,qint64)));
    connect(reply, &QNetworkReply::finished, [this, reply]() {
        setLoading(false);

        if (reply->error() != QNetworkReply::NoError) {
            emitNetworkError(reply);
            return;
        }

        QByteArray data = reply->readAll();
        outputResponse(data);

        QJsonObject models = convertToJsonObject(data);

        // output log
        emit log("received models", convertToBytes(models));

        // output received models
        emit receivedModels(data);
    });
}

void QtOllamaFrontend::getLoadedModels() {
    setLoading(true);

    // form url
    QUrl url("http://" + m_host + ":" + QString::number(m_port) + API_PS_URI);

    // form request object
    QNetworkRequest request = createNetworkRequest(url);

    // output log
    emit log("sent GET request:", url.toString());

    // send request
    QNetworkReply* reply = m_networkAccessManager->get(request);
    connect(reply, SIGNAL(downloadProgress(qint64,qint64)),
            this, SLOT(downloadProgress(qint64,qint64)));
    connect(reply, SIGNAL(uploadProgress(qint64,qint64)),
            this, SLOT(uploadProgress(qint64,qint64)));
    connect(reply, &QNetworkReply::finished, [this, reply]() {
        setLoading(false);

        if (reply->error() != QNetworkReply::NoError) {
            emitNetworkError(reply);
            return;
        }

        QByteArray data = reply->readAll();
        outputResponse(data);

        QJsonObject loadedModels = convertToJsonObject(data);

        // output log
        emit log("received loaded models", convertToBytes(loadedModels));

        // output received loaded models
        emit receivedLoadedModels(data);
    });
}

bool QtOllamaFrontend::addModelToDb(QString name, QString description, QString parameterSize, QString size) {
    return m_databaseComponent->addModel(name, description, parameterSize, size);
}

QVariantList QtOllamaFrontend::getModelsFromDb() {
    return m_databaseComponent->getAllRows(m_databaseComponent->getTableModel(), QStringList() << "*", "name", "ASC");
}

void QtOllamaFrontend::loadModel(QString modelName) {
    setLoading(true);

    // form json object for parameters
    QJsonObject params;
    params.insert("model", QJsonValue(modelName));

    // convert json object to QByteArray
    QByteArray jsonBytes = convertToBytes(params);
    outputRequest(QString(jsonBytes));

    // form url
    QUrl url("http://" + m_host + ":" + QString::number(m_port) + API_GENERATE_URI);

    // form request object
    QNetworkRequest request = createNetworkRequest(url, jsonBytes);

    // output log
    emit log("json sent load model request", jsonBytes);

    // send request
    QNetworkReply* reply = m_networkAccessManager->post(request, jsonBytes);
    connect(reply, SIGNAL(downloadProgress(qint64,qint64)),
            this, SLOT(downloadProgress(qint64,qint64)));
    connect(reply, SIGNAL(uploadProgress(qint64,qint64)),
            this, SLOT(uploadProgress(qint64,qint64)));
    connect(reply, &QNetworkReply::finished, [this, reply]() {
        setLoading(false);

        if (reply->error() != QNetworkReply::NoError) {
            emitNetworkError(reply);
            return;
        }

        QByteArray data = reply->readAll();
        outputResponse(data);

        // output log
        emit log("load model response", data);

        // output received loaded model
        emit receivedLoadedModel(data);
    });
}

void QtOllamaFrontend::unloadModel(QString modelName) {
    setLoading(true);

    // form json object for parameters
    QJsonObject params;
    params.insert("model", QJsonValue(modelName));
    params.insert("keep_alive", QJsonValue(0));

    // convert json object to QByteArray
    QByteArray jsonBytes = convertToBytes(params);
    outputRequest(QString(jsonBytes));

    // form url
    QUrl url("http://" + m_host + ":" + QString::number(m_port) + API_GENERATE_URI);

    // form request object
    QNetworkRequest request = createNetworkRequest(url, jsonBytes);

    // output log
    emit log("json sent unload model request", jsonBytes);

    // send request
    QNetworkReply* reply = m_networkAccessManager->post(request, jsonBytes);
    connect(reply, SIGNAL(downloadProgress(qint64,qint64)),
            this, SLOT(downloadProgress(qint64,qint64)));
    connect(reply, SIGNAL(uploadProgress(qint64,qint64)),
            this, SLOT(uploadProgress(qint64,qint64)));
    connect(reply, &QNetworkReply::finished, [this, reply]() {
        setLoading(false);

        if (reply->error() != QNetworkReply::NoError) {
            emitNetworkError(reply);
            return;
        }

        QByteArray data = reply->readAll();
        outputResponse(data);

        // output log
        emit log("unload model response", data);

        // output received unloaded model
        emit receivedUnloadedModel(data);
    });
}

void QtOllamaFrontend::deleteModel(QString modelName) {
    setLoading(true);

    // form json object for parameters
    QJsonObject params;
    params.insert("model", QJsonValue(modelName));

    // convert json object to QByteArray
    QByteArray jsonBytes = convertToBytes(params);
    outputRequest(QString(jsonBytes));

    // output log
    emit log("json sent delete model request", jsonBytes);

    // send request and receive streaming response
    QTcpSocket *tcpSocket = new QTcpSocket(this);
    tcpSocket->connectToHost(QHostAddress(m_host), m_port, QIODevice::ReadWrite);
    if (!tcpSocket->waitForConnected()) {
        emitNetworkError(tcpSocket);
    }

    QString httpDeleteRequest = createHttpDeleteRequest(API_DELETE_URI, jsonBytes);
    emit log("sent HTTP DELETE request", httpDeleteRequest);

    // send request
    tcpSocket->write(httpDeleteRequest.toUtf8());
    if (!tcpSocket->waitForBytesWritten()) {
        emitNetworkError(tcpSocket);
    }

    connect(tcpSocket, &QIODevice::readyRead, [this, tcpSocket, modelName]() {
        setLoading(false);

        QString data(tcpSocket->readAll());
        qDebug() << "received data:" << data;

        // check if delete was successful
        bool success = false;
        if (data.startsWith("HTTP/1.1 200 OK")) {
            success = true;
            qDebug() << "received HTTP DELETE response 200 OK";
            emit log("received HTTP DELETE response 200 OK", data);
        } else {
            qDebug() << "received HTTP DELETE response error code";
            emit log("received HTTP DELETE response error code", data);
        }

        QJsonObject result;
        result.insert("model", QJsonValue(modelName));
        result.insert("success", QJsonValue(success));

        emit receivedDeleteModel(convertToBytes(result));
    });
}

void QtOllamaFrontend::pullModel(QString modelName) {
    setLoading(true);

    // form json object for parameters
    QJsonObject params;
    params.insert("model", QJsonValue(modelName));
    params.insert("stream", QJsonValue(true));

    // convert json object to QByteArray
    QByteArray jsonBytes = convertToBytes(params);
    outputRequest(QString(jsonBytes));

    // output log
    emit log("json data for pull model request", jsonBytes);

    // send request and receive streaming response
    QTcpSocket *tcpSocket = new QTcpSocket(this);
    tcpSocket->connectToHost(QHostAddress(m_host), m_port, QIODevice::ReadWrite);
    if (!tcpSocket->waitForConnected()) {
        emitNetworkError(tcpSocket);
    }

    QString httpPostRequest = createHttpPostRequest(API_PULL_URI, jsonBytes);
    emit log("sent HTTP POST request", httpPostRequest);

    // send request
    tcpSocket->write(httpPostRequest.toUtf8());
    if (!tcpSocket->waitForBytesWritten()) {
        emitNetworkError(tcpSocket);
    }

    connect(tcpSocket, &QIODevice::readyRead, [this, tcpSocket, modelName]() {
        QString data(tcpSocket->readAll());

        // check if post was successful
        if (data.startsWith("HTTP/1.1 200 OK")) {
            qDebug() << "received HTTP POST response 200 OK";
            emit log("received HTTP POST response 200 OK", data);
        } else if (data.startsWith("HTTP/1.1")) {
            qDebug() << "received HTTP POST response error code";
            emit log("received HTTP POST response error code", data);
        } else {
            // process status json object
            QStringList jsonStrings = extractJsonStrings(data);

            for (QString jsonString : jsonStrings) {
                QJsonObject jsonObject = convertToJsonObject(jsonString);

                if (jsonObject.value("status").toString() == "success") {
                    setLoading(false);

                    QJsonObject result;
                    result.insert("model", QJsonValue(modelName));
                    result.insert("success", QJsonValue(true));

                    emit receivedPullModel(convertToBytes(result));
                } else {
                    emit receivedPullModelProgress(modelName, jsonObject.value("status").toString(), jsonObject.value("completed").toInteger(), jsonObject.value("total").toInteger());
                }
            }
        }
    });
}
