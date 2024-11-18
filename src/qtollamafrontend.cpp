#include "qtollamafrontend.h"

QtOllamaFrontend::QtOllamaFrontend(QObject* parent) : QObject(parent) {
    m_databaseComponent = new DatabaseComponent(this);
    m_networkAccessManager = new QNetworkAccessManager(this);

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
    // set default settings if necessary

    // host
    QString keyHost = getSettingsKey(Settings::ApiHost);

    if (!keyHost.isNull() && !keyHost.isEmpty()) {
        QString apiHost = getSetting(keyHost);

        if (apiHost.isNull() || apiHost.isEmpty()) {
            updateSetting(keyHost, API_HOST);
        }
    }

    // port
    QString keyPort = getSettingsKey(Settings::ApiPort);

    if (!keyPort.isNull() && !keyPort.isEmpty()) {
        QString apiPort = getSetting(keyPort);

        if (apiPort.isNull() || apiPort.isEmpty()) {
            updateSetting(keyPort, QString::number(API_PORT));
        }
    }

    // model name
    QString keyModelName = getSettingsKey(Settings::ApiModelName);

    if (!keyModelName.isNull() && !keyModelName.isEmpty()) {
        QString apiModelName = getSetting(keyModelName);

        if (apiModelName.isNull() || apiModelName.isEmpty()) {
            updateSetting(keyModelName, API_MODEL_NAME);
        }
    }

    // seed
    QString keySeed = getSettingsKey(Settings::ApiSeed);

    if (!keySeed.isNull() && !keySeed.isEmpty()) {
        QString apiSeed = getSetting(keySeed);

        if (apiSeed.isNull() || apiSeed.isEmpty()) {
            updateSetting(keySeed, QString::number(API_SEED));
        }
    }

    // scaled image width
    QString keyScaledImageWidth = getSettingsKey(Settings::ScaledImageWidth);

    if (!keyScaledImageWidth.isNull() && !keyScaledImageWidth.isEmpty()) {
        QString apiScaledImageWidth = getSetting(keyScaledImageWidth);

        if (apiScaledImageWidth.isNull() || apiScaledImageWidth.isEmpty()) {
            updateSetting(keyScaledImageWidth, QString::number(SCALED_IMAGE_WIDTH));
        }
    }

    // scaled image height
    QString keyScaledImageHeight = getSettingsKey(Settings::ScaledImageHeight);

    if (!keyScaledImageHeight.isNull() && !keyScaledImageHeight.isEmpty()) {
        QString apiScaledImageHeight = getSetting(keyScaledImageHeight);

        if (apiScaledImageHeight.isNull() || apiScaledImageHeight.isEmpty()) {
            updateSetting(keyScaledImageHeight, QString::number(SCALED_IMAGE_HEIGHT));
        }
    }

    // show log
    QString keyShowLog = getSettingsKey(Settings::ShowLog);

    if (!keyShowLog.isNull() && !keyShowLog.isEmpty()) {
        QString showLog = getSetting(keyShowLog);

        if (showLog.isNull() || showLog.isEmpty()) {
            updateSetting(keyShowLog, QString::number(SHOW_LOG));
        }
    }

    // output tts
    QString keyOutputTts = getSettingsKey(Settings::OutputTts);

    if (!keyOutputTts.isNull() && !keyOutputTts.isEmpty()) {
        QString outputTts = getSetting(keyOutputTts);

        if (outputTts.isNull() || outputTts.isEmpty()) {
            updateSetting(keyOutputTts, QString::number(OUTPUT_TTS));
        }
    }

    // text message multiline
    QString keyTextMessageMultiline = getSettingsKey(Settings::TextMessageMultiline);

    if (!keyTextMessageMultiline.isNull() && !keyTextMessageMultiline.isEmpty()) {
        QString textMessageMultiline = getSetting(keyTextMessageMultiline);

        if (textMessageMultiline.isNull() || textMessageMultiline.isEmpty()) {
            updateSetting(keyTextMessageMultiline, QString::number(TEXT_MESSAGE_MULTILINE));
        }
    }

    // tts engine
    QString keyTtsEngine = getSettingsKey(Settings::TtsEngine);

    if (!keyTtsEngine.isNull() && !keyTtsEngine.isEmpty()) {
        QString ttsEngine = getSetting(keyTtsEngine);

        if (ttsEngine.isNull() || ttsEngine.isEmpty()) {
            updateSetting(keyTtsEngine, "");
        }
    }

    // tts locale
    QString keyTtsLocale = getSettingsKey(Settings::TtsLocale);

    if (!keyTtsLocale.isNull() && !keyTtsLocale.isEmpty()) {
        QString ttsLocale = getSetting(keyTtsLocale);

        if (ttsLocale.isNull() || ttsLocale.isEmpty()) {
            updateSetting(keyTtsLocale, "");
        }
    }

    // tts voice
    QString keyTtsVoice = getSettingsKey(Settings::TtsVoice);

    if (!keyTtsVoice.isNull() && !keyTtsVoice.isEmpty()) {
        QString ttsVoice = getSetting(keyTtsVoice);

        if (ttsVoice.isNull() || ttsVoice.isEmpty()) {
            updateSetting(keyTtsVoice, "");
        }
    }

    // tts volume
    QString keyTtsVolume = getSettingsKey(Settings::TtsVolume);

    if (!keyTtsVolume.isNull() && !keyTtsVolume.isEmpty()) {
        QString ttsVolume = getSetting(keyTtsVolume);

        if (ttsVolume.isNull() || ttsVolume.isEmpty()) {
            updateSetting(keyTtsVolume, QString::number(TTS_VOLUME));
        }
    }

    // tts rate
    QString keyTtsRate = getSettingsKey(Settings::TtsRate);

    if (!keyTtsRate.isNull() && !keyTtsRate.isEmpty()) {
        QString ttsRate = getSetting(keyTtsRate);

        if (ttsRate.isNull() || ttsRate.isEmpty()) {
            updateSetting(keyTtsRate, QString::number(TTS_RATE));
        }
    }

    // tts pitch
    QString keyTtsPitch = getSettingsKey(Settings::TtsPitch);

    if (!keyTtsPitch.isNull() && !keyTtsPitch.isEmpty()) {
        QString ttsPitch = getSetting(keyTtsPitch);

        if (ttsPitch.isNull() || ttsPitch.isEmpty()) {
            updateSetting(keyTtsPitch, QString::number(TTS_PITCH));
        }
    }

    // set properties
    m_host = getSetting(getSettingsKey(Settings::ApiHost));
    m_port = getSetting(getSettingsKey(Settings::ApiPort)).toInt();
    m_modelName = getSetting(getSettingsKey(Settings::ApiModelName));
    m_seed = getSetting(getSettingsKey(Settings::ApiSeed)).toInt();
    m_scaledImageWidth = getSetting(getSettingsKey(Settings::ScaledImageWidth)).toInt();
    m_scaledImageHeight = getSetting(getSettingsKey(Settings::ScaledImageHeight)).toInt();
    m_showLog = getSetting(getSettingsKey(Settings::ShowLog)) == "1" ? true : false;
    m_outputTts = getSetting(getSettingsKey(Settings::OutputTts)) == "1" ? true : false;
    m_textMessageMultiline = getSetting(getSettingsKey(Settings::TextMessageMultiline)) == "1" ? true : false;
    m_ttsEngine = getSetting(getSettingsKey(Settings::TtsEngine));
    m_ttsLocale = getSetting(getSettingsKey(Settings::TtsLocale));
    m_ttsVoice = getSetting(getSettingsKey(Settings::TtsVoice));
    m_ttsVolume = getSetting(getSettingsKey(Settings::TtsVolume)).toDouble();
    m_ttsRate = getSetting(getSettingsKey(Settings::TtsRate)).toDouble();
    m_ttsPitch = getSetting(getSettingsKey(Settings::TtsPitch)).toDouble();

    // debug output settings
    qDebug()
        << "debug: settings values:"
        << "host" << m_host
        << "port" << m_port
        << "model name" << m_modelName
        << "seed" << m_seed
        << "scaled image width" << m_scaledImageWidth
        << "scaled image height" << m_scaledImageHeight
        << "show log" << m_showLog
        << "output tts" << m_outputTts
        << "text message multiline" << m_textMessageMultiline
        << "tts engine" << m_ttsEngine
        << "tts locale" << m_ttsLocale
        << "tts voice" << m_ttsVoice
        << "tts volum" << m_ttsVolume
        << "tts rate" << m_ttsRate
        << "tts pitch" << m_ttsPitch;
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

void QtOllamaFrontend::emitNetworkError(QNetworkReply* reply) {
    qDebug() << "network error:" << reply->errorString();
    emit receivedNetworkError(reply->errorString());
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

int QtOllamaFrontend::seed() {
    return m_seed;
}

void QtOllamaFrontend::setSeed(const int &seed) {
    if (seed != m_seed) {
        m_seed = seed;
        updateSetting(getSettingsKey(Settings::ApiSeed), QString::number(seed));
        emit seedChanged();
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

QString QtOllamaFrontend::getSetting(QString key) {
    QJsonObject setting = m_databaseComponent->getSetting(key);

    return setting.value("value").toString();
}

QString QtOllamaFrontend::getSettingsKey(int key) {
    switch (key) {
    case Settings::ApiHost: return "api_host";
    case Settings::ApiPort: return "api_port";
    case Settings::ApiModelName: return "api_model_name";
    case Settings::ApiSeed: return "api_seed";
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
    default: return "";
    };

    return "";
}

void QtOllamaFrontend::resetSettings() {
    setHost(API_HOST);
    setPort(API_PORT);
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

    // check if seed is specified for reproducible outputs
    if (m_seed > 0) {
        QJsonObject options;
        options.insert("seed", QJsonValue(m_seed));
        options.insert("temperature", QJsonValue(0));

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

void QtOllamaFrontend::pullModel(QString modelName) {
    setLoading(true);

    // form json object for parameters
    QJsonObject params;
    params.insert("model", QJsonValue(modelName));
    params.insert("stream", QJsonValue(true));

    // convert json object to QByteArray
    QByteArray jsonBytes = convertToBytes(params);
    outputRequest(QString(jsonBytes));

    // form url
    QUrl url("http://" + m_host + ":" + QString::number(m_port) + API_PULL_URI);

    // form request object
    QNetworkRequest request = createNetworkRequest(url, jsonBytes);

    // output log
    emit log("json sent pull model request", jsonBytes);

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

        // output received pull model
        emit receivedPullModel(data);
    });
}
