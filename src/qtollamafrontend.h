#ifndef QTOLLAMAFRONTEND_H
#define QTOLLAMAFRONTEND_H

#include <QObject>
#include <QDebug>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QTcpSocket>
#include <QTextToSpeech>
#include <QDomDocument>
#include <QMimeDatabase>
#include <QImage>
#include <QBuffer>
#include "databasecomponent.h"

class QtOllamaFrontend : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool loading READ loading WRITE setLoading NOTIFY loadingChanged)
    Q_PROPERTY(QString host READ host WRITE setHost NOTIFY hostChanged)
    Q_PROPERTY(int port READ port WRITE setPort NOTIFY portChanged)
    Q_PROPERTY(QString modelName READ modelName WRITE setModelName NOTIFY modelNameChanged)
    Q_PROPERTY(int seed READ seed WRITE setSeed NOTIFY seedChanged)
    Q_PROPERTY(bool showLog READ showLog WRITE setShowLog NOTIFY showLogChanged)
    Q_PROPERTY(bool outputTts READ outputTts WRITE setOutputTts NOTIFY outputTtsChanged)
    Q_PROPERTY(bool textMessageMultiline READ textMessageMultiline WRITE setTextMessageMultiline NOTIFY textMessageMultilineChanged)
    Q_PROPERTY(int scaledImageWidth READ scaledImageWidth WRITE setScaledImageWidth NOTIFY scaledImageWidthChanged)
    Q_PROPERTY(int scaledImageHeight READ scaledImageHeight WRITE setScaledImageHeight NOTIFY scaledImageHeightChanged)
    Q_PROPERTY(QString ttsEngine READ ttsEngine WRITE setTtsEngine NOTIFY ttsEngineChanged)
    Q_PROPERTY(QString ttsLocale READ ttsLocale WRITE setTtsLocale NOTIFY ttsLocaleChanged)
    Q_PROPERTY(QString ttsVoice READ ttsVoice WRITE setTtsVoice NOTIFY ttsVoiceChanged)
    Q_PROPERTY(double ttsVolume READ ttsVolume WRITE setTtsVolume NOTIFY ttsVolumeChanged)
    Q_PROPERTY(double ttsRate READ ttsRate WRITE setTtsRate NOTIFY ttsRateChanged)
    Q_PROPERTY(double ttsPitch READ ttsPitch WRITE setTtsPitch NOTIFY ttsPitchChanged)

    DatabaseComponent *m_databaseComponent = nullptr;
    QNetworkAccessManager *m_networkAccessManager = nullptr;

    // chat history
    QJsonArray m_messages;

    // constants:
    const QString API_HOST = "127.0.0.1";
    const int API_PORT = 11434;
    const QString API_CHAT_URI = "/api/chat";
    const QString API_TAGS_URI = "/api/tags";
    const QString API_GENERATE_URI = "/api/generate";
    const QString API_PS_URI = "/api/ps";
    const QString API_PULL_URI = "/api/pull";
    const QString API_DELETE_URI = "/api/delete";
    const QString API_MODEL_NAME = "llama3.2:latest";
    const int API_SEED = 0;
    const int SHOW_LOG = 1;
    const int OUTPUT_TTS = 1;
    const int TEXT_MESSAGE_MULTILINE = 0;
    const int SCALED_IMAGE_WIDTH = 1500;
    const int SCALED_IMAGE_HEIGHT = 1500;
    const double TTS_VOLUME = 1.0;
    const double TTS_RATE = 0.0;
    const double TTS_PITCH = 0.0;
    // attributes:
    bool m_loading = false;
    QString m_host = "127.0.0.1";
    int m_port = 11434;
    bool m_showLog = false;
    QString m_modelName = "llama3.2:latest";
    int m_seed = 0;
    bool m_outputTts = true;
    bool m_textMessageMultiline = false;
    int m_scaledImageWidth = 512;
    int m_scaledImageHeight = 512;
    QString m_ttsEngine = "";
    QString m_ttsLocale = "";
    QString m_ttsVoice = "";
    double m_ttsVolume = 1.0;
    double m_ttsRate = 0.0;
    double m_ttsPitch = 0.0;
    // methods:
    QString createHttpPostRequest(const QString &apiUri, const QString &jsonString);
    QString createHttpDeleteRequest(const QString &apiUri, const QString &jsonString);
    QNetworkRequest createNetworkRequest(const QUrl &url, const QByteArray &bytes = QByteArray());
    QString convertJsonToString(const QJsonObject &data);
    QString convertJsonToString(const QJsonArray &data);
    static QByteArray convertToBytes(const QJsonObject &jsonObject);
    static QJsonObject convertToJsonObject(const QString &jsonString);
    static QJsonArray convertToJsonArray(const QString &jsonString);
    QByteArray getImageBytes(const QString filePath);
    QByteArray getImageBytes(const QImage &image);
    QString convertImageBytesToBase64(const QByteArray &imageData);
    void outputRequest(const QString request);
    void outputResponse(const QString response);
    void emitNetworkError(QNetworkReply *reply);
    void emitNetworkError(QTcpSocket *tcpSocket);
    void loadSettings();
    QByteArray prepareJsonForLogOutput(const QJsonObject &jsonObject);
    QStringList extractJsonStrings(const QString &string);
signals:
    void loadingChanged();
    void hostChanged();
    void portChanged();
    void modelNameChanged();
    void seedChanged();
    void showLogChanged();
    void outputTtsChanged();
    void textMessageMultilineChanged();
    void scaledImageWidthChanged();
    void scaledImageHeightChanged();
    void ttsEngineChanged();
    void ttsLocaleChanged();
    void ttsVoiceChanged();
    void ttsVolumeChanged();
    void ttsRateChanged();
    void ttsPitchChanged();

    void log(const QString title, const QVariant data);
    void say(const QString text);
    void receivedNetworkError(const QVariant result);
    void receivedDownloadProgress(qint64 bytesReceived, qint64 bytesTotal);
    void receivedUploadProgress(qint64 bytesSent, qint64 bytesTotal);
    void updateSetting(QString key, QString value);
    void receivedResponse(const QVariant result);
    void receivedNewChatStarted();
    void receivedModels(const QVariant result);
    void receivedLoadedModels(const QVariant result);
    void receivedLoadedModel(const QVariant result);
    void receivedUnloadedModel(const QVariant result);
    void receivedPullModelProgress(QString modelName, QString status, qint64 bytesReceived, qint64 bytesTotal);
    void receivedPullModel(const QVariant result);
    void receivedDeleteModel(const QVariant result);
public slots:
    bool addModelToDb(QString name, QString description, QString parameterSize, QString size);
    QVariantList getModelsFromDb();
    void loadModel(QString modelName);
    void unloadModel(QString modelName);
    void getLoadedModels();
    void getModels();
    void pullModel(QString modelName);
    void deleteModel(QString modelName);
    void startNewChat();
    void sendMessage(QString content, QString jsonImageFilePaths);
    void downloadProgress(qint64 bytesReceived, qint64 bytesTotal);
    void uploadProgress(qint64 bytesSent, qint64 bytesTotal);
    QString getSetting(QString key);
    QString getSettingsKey(int key);
    void resetSettings();
public:
    // enum
    enum Settings {
        ApiHost,
        ApiPort,
        ApiModelName,
        ApiSeed,
        ScaledImageWidth,
        ScaledImageHeight,
        ShowLog,
        OutputTts,
        TextMessageMultiline,
        TtsEngine,
        TtsLocale,
        TtsVoice,
        TtsVolume,
        TtsRate,
        TtsPitch
    };
    Q_ENUM(Settings)
    // loading
    bool loading();
    void setLoading(const bool &loading);
    // host
    QString host();
    void setHost(const QString &host);
    // port
    int port();
    void setPort(const int &port);
    // model name
    QString modelName();
    void setModelName(const QString &modelName);
    // seed
    int seed();
    void setSeed(const int &seed);
    // show log
    bool showLog();
    void setShowLog(const bool &showLog);
    // output tts
    bool outputTts();
    void setOutputTts(const bool &outputTts);
    // text message multiline
    bool textMessageMultiline();
    void setTextMessageMultiline(const bool &textMessageMultiline);
    // sclaed image width
    int scaledImageWidth();
    void setScaledImageWidth(const int &scaledImageWidth);
    // sclaed image height
    int scaledImageHeight();
    void setScaledImageHeight(const int &scaledImageHeight);
    // tts engine
    QString ttsEngine();
    void setTtsEngine(const QString &ttsEngine);
    // tts locale
    QString ttsLocale();
    void setTtsLocale(const QString &ttsLocale);
    // tts voice
    QString ttsVoice();
    void setTtsVoice(const QString &ttsVoice);
    // tts volume
    double ttsVolume();
    void setTtsVolume(const double &ttsVolume);
    // tts rate
    double ttsRate();
    void setTtsRate(const double &ttsRate);
    // tts pitch
    double ttsPitch();
    void setTtsPitch(const double &ttsPitch);
    // constructor:
    QtOllamaFrontend(QObject* parent = nullptr);
    // destructor
    ~QtOllamaFrontend();
};

#endif // QTOLLAMAFRONTEND_H
