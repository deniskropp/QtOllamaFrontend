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
    // api
    Q_PROPERTY(QString host READ host WRITE setHost NOTIFY hostChanged)
    Q_PROPERTY(int port READ port WRITE setPort NOTIFY portChanged)
    Q_PROPERTY(QString modelName READ modelName WRITE setModelName NOTIFY modelNameChanged)
    // settings
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
    // options
    Q_PROPERTY(int seed READ seed WRITE setSeed NOTIFY seedChanged)
    Q_PROPERTY(int numKeep READ numKeep WRITE setNumKeep NOTIFY numKeepChanged)
    Q_PROPERTY(int numPredict READ numPredict WRITE setNumPredict NOTIFY numPredictChanged)
    Q_PROPERTY(int topK READ topK WRITE setTopK NOTIFY topKChanged)
    Q_PROPERTY(double topP READ topP WRITE setTopP NOTIFY topPChanged)
    Q_PROPERTY(double minP READ minP WRITE setMinP NOTIFY minPChanged)
    Q_PROPERTY(double tfsZ READ tfsZ WRITE setTfsZ NOTIFY tfsZChanged)
    Q_PROPERTY(double typicalP READ typicalP WRITE setTypicalP NOTIFY typicalPChanged)
    Q_PROPERTY(int repeatLastN READ repeatLastN WRITE setRepeatLastN NOTIFY repeatLastNChanged)
    Q_PROPERTY(double temperature READ temperature WRITE setTemperature NOTIFY temperatureChanged)
    Q_PROPERTY(double repeatPenalty READ repeatPenalty WRITE setRepeatPenalty NOTIFY repeatPenaltyChanged)
    Q_PROPERTY(double presencePenalty READ presencePenalty WRITE setPresencePenalty NOTIFY presencePenaltyChanged)
    Q_PROPERTY(double frequencyPenalty READ frequencyPenalty WRITE setFrequencyPenalty NOTIFY frequencyPenaltyChanged)
    Q_PROPERTY(int mirostat READ mirostat WRITE setMirostat NOTIFY mirostatChanged)
    Q_PROPERTY(double mirostatTau READ mirostatTau WRITE setMirostatTau NOTIFY mirostatTauChanged)
    Q_PROPERTY(double mirostatEta READ mirostatEta WRITE setMirostatEta NOTIFY mirostatEtaChanged)
    Q_PROPERTY(bool penalizeNewline READ penalizeNewline WRITE setPenalizeNewline NOTIFY penalizeNewlineChanged)
    Q_PROPERTY(QString stop READ stop WRITE setStop NOTIFY stopChanged)
    Q_PROPERTY(bool numa READ numa WRITE setNuma NOTIFY numaChanged)
    Q_PROPERTY(int numCtx READ numCtx WRITE setNumCtx NOTIFY numCtxChanged)
    Q_PROPERTY(int numBatch READ numBatch WRITE setNumBatch NOTIFY numBatchChanged)
    Q_PROPERTY(int numGpu READ numGpu WRITE setNumGpu NOTIFY numGpuChanged)
    Q_PROPERTY(int mainGpu READ mainGpu WRITE setMainGpu NOTIFY mainGpuChanged)
    Q_PROPERTY(bool lowVram READ lowVram WRITE setLowVram NOTIFY lowVramChanged)
    Q_PROPERTY(bool vocabOnly READ vocabOnly WRITE setVocabOnly NOTIFY vocabOnlyChanged)
    Q_PROPERTY(bool useMmap READ useMmap WRITE setUseMmap NOTIFY useMmapChanged)
    Q_PROPERTY(bool useMlock READ useMlock WRITE setUseMlock NOTIFY useMlockChanged)
    Q_PROPERTY(int numThread READ numThread WRITE setNumThread NOTIFY numThreadChanged)
    Q_PROPERTY(bool seedApplied READ seedApplied WRITE setSeedApplied NOTIFY seedAppliedChanged)
    Q_PROPERTY(bool numKeepApplied READ numKeepApplied WRITE setNumKeepApplied NOTIFY numKeepAppliedChanged)
    Q_PROPERTY(bool numPredictApplied READ numPredictApplied WRITE setNumPredictApplied NOTIFY numPredictAppliedChanged)
    Q_PROPERTY(bool topKApplied READ topKApplied WRITE setTopKApplied NOTIFY topKAppliedChanged)
    Q_PROPERTY(bool topPApplied READ topPApplied WRITE setTopPApplied NOTIFY topPAppliedChanged)
    Q_PROPERTY(bool minPApplied READ minPApplied WRITE setMinPApplied NOTIFY minPAppliedChanged)
    Q_PROPERTY(bool tfsZApplied READ tfsZApplied WRITE setTfsZApplied NOTIFY tfsZAppliedChanged)
    Q_PROPERTY(bool typicalPApplied READ typicalPApplied WRITE setTypicalPApplied NOTIFY typicalPAppliedChanged)
    Q_PROPERTY(bool repeatLastNApplied READ repeatLastNApplied WRITE setRepeatLastNApplied NOTIFY repeatLastNAppliedChanged)
    Q_PROPERTY(bool temperatureApplied READ temperatureApplied WRITE setTemperatureApplied NOTIFY temperatureAppliedChanged)
    Q_PROPERTY(bool repeatPenaltyApplied READ repeatPenaltyApplied WRITE setRepeatPenaltyApplied NOTIFY repeatPenaltyAppliedChanged)
    Q_PROPERTY(bool presencePenaltyApplied READ presencePenaltyApplied WRITE setPresencePenaltyApplied NOTIFY presencePenaltyAppliedChanged)
    Q_PROPERTY(bool frequencyPenaltyApplied READ frequencyPenaltyApplied WRITE setFrequencyPenaltyApplied NOTIFY frequencyPenaltyAppliedChanged)
    Q_PROPERTY(bool mirostatApplied READ mirostatApplied WRITE setMirostatApplied NOTIFY mirostatAppliedChanged)
    Q_PROPERTY(bool mirostatTauApplied READ mirostatTauApplied WRITE setMirostatTauApplied NOTIFY mirostatTauAppliedChanged)
    Q_PROPERTY(bool mirostatEtaApplied READ mirostatEtaApplied WRITE setMirostatEtaApplied NOTIFY mirostatEtaAppliedChanged)
    Q_PROPERTY(bool penalizeNewlineApplied READ penalizeNewlineApplied WRITE setPenalizeNewlineApplied NOTIFY penalizeNewlineAppliedChanged)
    Q_PROPERTY(bool stopApplied READ stopApplied WRITE setStopApplied NOTIFY stopAppliedChanged)
    Q_PROPERTY(bool numaApplied READ numaApplied WRITE setNumaApplied NOTIFY numaAppliedChanged)
    Q_PROPERTY(bool numCtxApplied READ numCtxApplied WRITE setNumCtxApplied NOTIFY numCtxAppliedChanged)
    Q_PROPERTY(bool numBatchApplied READ numBatchApplied WRITE setNumBatchApplied NOTIFY numBatchAppliedChanged)
    Q_PROPERTY(bool numGpuApplied READ numGpuApplied WRITE setNumGpuApplied NOTIFY numGpuAppliedChanged)
    Q_PROPERTY(bool mainGpuApplied READ mainGpuApplied WRITE setMainGpuApplied NOTIFY mainGpuAppliedChanged)
    Q_PROPERTY(bool lowVramApplied READ lowVramApplied WRITE setLowVramApplied NOTIFY lowVramAppliedChanged)
    Q_PROPERTY(bool vocabOnlyApplied READ vocabOnlyApplied WRITE setVocabOnlyApplied NOTIFY vocabOnlyAppliedChanged)
    Q_PROPERTY(bool useMmapApplied READ useMmapApplied WRITE setUseMmapApplied NOTIFY useMmapAppliedChanged)
    Q_PROPERTY(bool useMlockApplied READ useMlockApplied WRITE setUseMlockApplied NOTIFY useMlockAppliedChanged)
    Q_PROPERTY(bool numThreadApplied READ numThreadApplied WRITE setNumThreadApplied NOTIFY numThreadAppliedChanged)

    DatabaseComponent *m_databaseComponent = nullptr;
    QNetworkAccessManager *m_networkAccessManager = nullptr;

    // chat history
    QJsonArray m_messages;

    // constants:
    // api
    const QString API_HOST = "127.0.0.1";
    const int API_PORT = 11434;
    const QString API_CHAT_URI = "/api/chat";
    const QString API_TAGS_URI = "/api/tags";
    const QString API_GENERATE_URI = "/api/generate";
    const QString API_PS_URI = "/api/ps";
    const QString API_PULL_URI = "/api/pull";
    const QString API_DELETE_URI = "/api/delete";
    const QString API_MODEL_NAME = "llama3.2:latest";
    // settings
    const bool SHOW_LOG = true;
    const bool OUTPUT_TTS = true;
    const bool TEXT_MESSAGE_MULTILINE = false;
    const int SCALED_IMAGE_WIDTH = 1500;
    const int SCALED_IMAGE_HEIGHT = 1500;
    const double TTS_VOLUME = 1.0;
    const double TTS_RATE = 0.7;
    const double TTS_PITCH = 0.0;
    // options
    const int SEED = 42;
    const int NUM_KEEP = 5;
    const int NUM_PREDICT = 100;
    const int TOP_K = 20;
    const double TOP_P = 0.9;
    const double MIN_P = 0.0;
    const double TFS_Z = 0.5;
    const double TYPICAL_P = 0.7;
    const int REPEAT_LAST_N = 33;
    const double TEMPERATURE = 0.8;
    const double REPEAT_PENALTY = 1.2;
    const double PRESENCE_PENALTY = 1.5;
    const double FREQUENCY_PENALTY = 1.0;
    const int MIROSTAT = 1;
    const double MIROSTAT_TAU = 0.8;
    const double MIROSTAT_ETA = 0.6;
    const bool PENALIZE_NEWLINE = true;
    const QString STOP = "[\"\\n\", \"user:\"]";
    const bool NUMA = false;
    const int NUM_CTX = 1024;
    const int NUM_BATCH = 2;
    const int NUM_GPU = 1;
    const int MAIN_GPU = 0;
    const bool LOW_VRAM = false;
    const bool VOCAB_ONLY = false;
    const bool USE_MMAP = true;
    const bool USE_MLOCK = false;
    const int NUM_THREAD = 8;
    // attributes:
    bool m_loading = false;
    // api
    QString m_host = "127.0.0.1";
    int m_port = 11434;
    QString m_modelName = "llama3.2:latest";
    // settings
    bool m_showLog = false;
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
    // options
    int m_seed = SEED;
    int m_numKeep = NUM_KEEP;
    int m_numPredict = NUM_PREDICT;
    int m_topK = TOP_K;
    double m_topP = TOP_P;
    double m_minP = MIN_P;
    double m_tfsZ = TFS_Z;
    double m_typicalP = TYPICAL_P;
    int m_repeatLastN = REPEAT_LAST_N;
    double m_temperature = TEMPERATURE;
    double m_repeatPenalty = REPEAT_PENALTY;
    double m_presencePenalty = PRESENCE_PENALTY;
    double m_frequencyPenalty = FREQUENCY_PENALTY;
    int m_mirostat = MIROSTAT;
    double m_mirostatTau = MIROSTAT_TAU;
    double m_mirostatEta = MIROSTAT_ETA;
    bool m_penalizeNewline = PENALIZE_NEWLINE;
    QString m_stop = STOP;
    bool m_numa = NUMA;
    int m_numCtx = NUM_CTX;
    int m_numBatch = NUM_BATCH;
    int m_numGpu = NUM_GPU;
    int m_mainGpu = MAIN_GPU;
    bool m_lowVram = LOW_VRAM;
    bool m_vocabOnly = VOCAB_ONLY;
    bool m_useMmap = USE_MMAP;
    bool m_useMlock = USE_MLOCK;
    int m_numThread = NUM_THREAD;
    bool m_seedApplied = false;
    bool m_numKeepApplied = false;
    bool m_numPredictApplied = false;
    bool m_topKApplied = false;
    bool m_topPApplied = false;
    bool m_minPApplied = false;
    bool m_tfsZApplied = false;
    bool m_typicalPApplied = false;
    bool m_repeatLastNApplied = false;
    bool m_temperatureApplied = false;
    bool m_repeatPenaltyApplied = false;
    bool m_presencePenaltyApplied = false;
    bool m_frequencyPenaltyApplied = false;
    bool m_mirostatApplied = false;
    bool m_mirostatTauApplied = false;
    bool m_mirostatEtaApplied = false;
    bool m_penalizeNewlineApplied = false;
    bool m_stopApplied = false;
    bool m_numaApplied = false;
    bool m_numCtxApplied = false;
    bool m_numBatchApplied = false;
    bool m_numGpuApplied = false;
    bool m_mainGpuApplied = false;
    bool m_lowVramApplied = false;
    bool m_vocabOnlyApplied = false;
    bool m_useMmapApplied = false;
    bool m_useMlockApplied = false;
    bool m_numThreadApplied = false;
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
    QJsonObject getSelectedOptions();
    QByteArray prepareJsonForLogOutput(const QJsonObject &jsonObject);
    QStringList extractJsonStrings(const QString &string);
signals:
    void loadingChanged();
    // api
    void hostChanged();
    void portChanged();
    void modelNameChanged();
    // settings
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
    // options
    void seedChanged();
    void numKeepChanged();
    void numPredictChanged();
    void topKChanged();
    void topPChanged();
    void minPChanged();
    void tfsZChanged();
    void typicalPChanged();
    void repeatLastNChanged();
    void temperatureChanged();
    void repeatPenaltyChanged();
    void presencePenaltyChanged();
    void frequencyPenaltyChanged();
    void mirostatChanged();
    void mirostatTauChanged();
    void mirostatEtaChanged();
    void penalizeNewlineChanged();
    void stopChanged();
    void numaChanged();
    void numCtxChanged();
    void numBatchChanged();
    void numGpuChanged();
    void mainGpuChanged();
    void lowVramChanged();
    void vocabOnlyChanged();
    void useMmapChanged();
    void useMlockChanged();
    void numThreadChanged();
    void seedAppliedChanged();
    void numKeepAppliedChanged();
    void numPredictAppliedChanged();
    void topKAppliedChanged();
    void topPAppliedChanged();
    void minPAppliedChanged();
    void tfsZAppliedChanged();
    void typicalPAppliedChanged();
    void repeatLastNAppliedChanged();
    void temperatureAppliedChanged();
    void repeatPenaltyAppliedChanged();
    void presencePenaltyAppliedChanged();
    void frequencyPenaltyAppliedChanged();
    void mirostatAppliedChanged();
    void mirostatTauAppliedChanged();
    void mirostatEtaAppliedChanged();
    void penalizeNewlineAppliedChanged();
    void stopAppliedChanged();
    void numaAppliedChanged();
    void numCtxAppliedChanged();
    void numBatchAppliedChanged();
    void numGpuAppliedChanged();
    void mainGpuAppliedChanged();
    void lowVramAppliedChanged();
    void vocabOnlyAppliedChanged();
    void useMmapAppliedChanged();
    void useMlockAppliedChanged();
    void numThreadAppliedChanged();
    // other
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
    QString getDefaultSetting(int key);
    void resetSetting(int key);
    void resetSettings(QVariantList keys);
public:
    // enum
    enum Settings {
        // api
        ApiHost,
        ApiPort,
        ApiModelName,
        // settings
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
        TtsPitch,
        // options
        Seed,
        NumKeep,
        NumPredict,
        TopK,
        TopP,
        MinP,
        TfsZ,
        TypicalP,
        RepeatLastN,
        Temperature,
        RepeatPenalty,
        PresencePenalty,
        FrequencyPenalty,
        Mirostat,
        MirostatTau,
        MirostatEta,
        PenalizeNewline,
        Stop,
        Numa,
        NumCtx,
        NumBatch,
        NumGpu,
        MainGpu,
        LowVram,
        VocabOnly,
        UseMmap,
        UseMlock,
        NumThread,
        SeedApplied,
        NumKeepApplied,
        NumPredictApplied,
        TopKApplied,
        TopPApplied,
        MinPApplied,
        TfsZApplied,
        TypicalPApplied,
        RepeatLastNApplied,
        TemperatureApplied,
        RepeatPenaltyApplied,
        PresencePenaltyApplied,
        FrequencyPenaltyApplied,
        MirostatApplied,
        MirostatTauApplied,
        MirostatEtaApplied,
        PenalizeNewlineApplied,
        StopApplied,
        NumaApplied,
        NumCtxApplied,
        NumBatchApplied,
        NumGpuApplied,
        MainGpuApplied,
        LowVramApplied,
        VocabOnlyApplied,
        UseMmapApplied,
        UseMlockApplied,
        NumThreadApplied
    };
    Q_ENUM(Settings)

    // loading
    bool loading();
    void setLoading(const bool &loading);

    // api
    // host
    QString host();
    void setHost(const QString &host);
    // port
    int port();
    void setPort(const int &port);
    // model name
    QString modelName();
    void setModelName(const QString &modelName);

    // settings
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

    // options
    // seed
    int seed();
    void setSeed(const int &seed);
    // numKeep
    int numKeep();
    void setNumKeep(const int &numKeep);
    // numPredict
    int numPredict();
    void setNumPredict(const int &numPredict);
    // topK
    int topK();
    void setTopK(const int &topK);
    // topP
    double topP();
    void setTopP(const double &topP);
    // minP
    double minP();
    void setMinP(const double &minP);
    // tfsZ
    double tfsZ();
    void setTfsZ(const double &tfsZ);
    // typicalP
    double typicalP();
    void setTypicalP(const double &typicalP);
    // repeatLastN
    int repeatLastN();
    void setRepeatLastN(const int &repeatLastN);
    // temperature
    double temperature();
    void setTemperature(const double &temperature);
    // repeatPenalty
    double repeatPenalty();
    void setRepeatPenalty(const double &repeatPenalty);
    // presencePenalty
    double presencePenalty();
    void setPresencePenalty(const double &presencePenalty);
    // frequencyPenalty
    double frequencyPenalty();
    void setFrequencyPenalty(const double &frequencyPenalty);
    // mirostat
    int mirostat();
    void setMirostat(const int &mirostat);
    // mirostatTau
    double mirostatTau();
    void setMirostatTau(const double &mirostatTau);
    // mirostatEta
    double mirostatEta();
    void setMirostatEta(const double &mirostatEta);
    // penalizeNewline
    bool penalizeNewline();
    void setPenalizeNewline(const bool &penalizeNewline);
    // stop
    QString stop();
    void setStop(const QString &stop);
    // numa
    bool numa();
    void setNuma(const bool &numa);
    // numCtx
    int numCtx();
    void setNumCtx(const int &numCtx);
    // numBatch
    int numBatch();
    void setNumBatch(const int &numBatch);
    // numGpu
    int numGpu();
    void setNumGpu(const int &numGpu);
    // mainGpu
    int mainGpu();
    void setMainGpu(const int &mainGpu);
    // lowVram
    bool lowVram();
    void setLowVram(const bool &lowVram);
    // vocabOnly
    bool vocabOnly();
    void setVocabOnly(const bool &vocabOnly);
    // useMmap
    bool useMmap();
    void setUseMmap(const bool &useMmap);
    // useMlock
    bool useMlock();
    void setUseMlock(const bool &useMlock);
    // numThread
    int numThread();
    void setNumThread(const int &numThread);
    // seedApplied
    bool seedApplied();
    void setSeedApplied(const bool &seedApplied);
    // numKeepApplied
    bool numKeepApplied();
    void setNumKeepApplied(const bool &numKeepApplied);
    // numPredictApplied
    bool numPredictApplied();
    void setNumPredictApplied(const bool &numPredictApplied);
    // topKApplied
    bool topKApplied();
    void setTopKApplied(const bool &topKApplied);
    // topPApplied
    bool topPApplied();
    void setTopPApplied(const bool &topPApplied);
    // minPApplied
    bool minPApplied();
    void setMinPApplied(const bool &minPApplied);
    // tfsZApplied
    bool tfsZApplied();
    void setTfsZApplied(const bool &tfsZApplied);
    // typicalP
    bool typicalPApplied();
    void setTypicalPApplied(const bool &typicalPApplied);
    // repeatLastNApplied
    bool repeatLastNApplied();
    void setRepeatLastNApplied(const bool &repeatLastNApplied);
    // temperatureApplied
    bool temperatureApplied();
    void setTemperatureApplied(const bool &temperatureApplied);
    // repeatPenaltyApplied
    bool repeatPenaltyApplied();
    void setRepeatPenaltyApplied(const bool &repeatPenaltyApplied);
    // presencePenaltyApplied
    bool presencePenaltyApplied();
    void setPresencePenaltyApplied(const bool &presencePenaltyApplied);
    // frequencyPenaltyApplied
    bool frequencyPenaltyApplied();
    void setFrequencyPenaltyApplied(const bool &frequencyPenaltyApplied);
    // mirostatApplied
    bool mirostatApplied();
    void setMirostatApplied(const bool &mirostatApplied);
    // mirostatTauApplied
    bool mirostatTauApplied();
    void setMirostatTauApplied(const bool &mirostatTauApplied);
    // mirostatEtaApplied
    bool mirostatEtaApplied();
    void setMirostatEtaApplied(const bool &mirostatEtaApplied);
    // penalizeNewlineApplied
    bool penalizeNewlineApplied();
    void setPenalizeNewlineApplied(const bool &penalizeNewlineApplied);
    // stopApplied
    bool stopApplied();
    void setStopApplied(const bool &stopApplied);
    // numaApplied
    bool numaApplied();
    void setNumaApplied(const bool &numaApplied);
    // numCtxApplied
    bool numCtxApplied();
    void setNumCtxApplied(const bool &numCtxApplied);
    // numBatchApplied
    bool numBatchApplied();
    void setNumBatchApplied(const bool &numBatchApplied);
    // numGpuApplied
    bool numGpuApplied();
    void setNumGpuApplied(const bool &numGpuApplied);
    // mainGpuApplied
    bool mainGpuApplied();
    void setMainGpuApplied(const bool &mainGpuApplied);
    // lowVramApplied
    bool lowVramApplied();
    void setLowVramApplied(const bool &lowVramApplied);
    // vocabOnlyApplied
    bool vocabOnlyApplied();
    void setVocabOnlyApplied(const bool &vocabOnlyApplied);
    // useMmapApplied
    bool useMmapApplied();
    void setUseMmapApplied(const bool &useMmapApplied);
    // useMlockApplied
    bool useMlockApplied();
    void setUseMlockApplied(const bool &useMlockApplied);
    // numThreadApplied
    bool numThreadApplied();
    void setNumThreadApplied(const bool &numThreadApplied);

    // constructor:
    QtOllamaFrontend(QObject* parent = nullptr);
    // destructor
    ~QtOllamaFrontend();
};

#endif // QTOLLAMAFRONTEND_H
