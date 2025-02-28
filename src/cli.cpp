#include "qtollamafrontend.h"
#include <QCommandLineParser>
#include <QCoreApplication>
#include <QDebug>
#include <iostream>

void setupCliParser(QCommandLineParser &parser, QtOllamaFrontend &frontend) {
    parser.setApplicationDescription("CLI for QtOllamaFrontend");
    parser.addHelpOption();
    parser.addVersionOption();

    // --- API Options ---
    QCommandLineOption hostOption("host", "Ollama API host.", "host", frontend.host());
    parser.addOption(hostOption);

    QCommandLineOption portOption("port", "Ollama API port.", "port", QString::number(frontend.port()));
    parser.addOption(portOption);

    QCommandLineOption modelOption("model", "Ollama model name.", "model", frontend.modelName());
    parser.addOption(modelOption);

    QCommandLineOption streamOption("stream", "Enable streaming.", "stream", frontend.stream() ? "true" : "false");
    parser.addOption(streamOption);

    // --- Settings ---
    QCommandLineOption showLogOption("show-log", "Show log output.", "show-log", frontend.showLog() ? "true" : "false");
    parser.addOption(showLogOption);

    QCommandLineOption outputTtsOption("output-tts", "Enable text-to-speech output.", "output-tts",
                                       frontend.outputTts() ? "true" : "false");
    parser.addOption(outputTtsOption);

    QCommandLineOption textMessageMultilineOption("multiline", "Enable multiline text messages.", "multiline",
                                                  frontend.textMessageMultiline() ? "true" : "false");
    parser.addOption(textMessageMultilineOption);

    QCommandLineOption scaledImageWidthOption("image-width", "Scaled image width.", "image-width",
                                              QString::number(frontend.scaledImageWidth()));
    parser.addOption(scaledImageWidthOption);

    QCommandLineOption scaledImageHeightOption("image-height", "Scaled image height.", "image-height",
                                               QString::number(frontend.scaledImageHeight()));
    parser.addOption(scaledImageHeightOption);

    // --- Model Options ---
    QCommandLineOption seedOption("seed", "Random seed.", "seed", QString::number(frontend.seed()));
    parser.addOption(seedOption);

    QCommandLineOption numKeepOption("num-keep", "Number of tokens to keep.", "num-keep", QString::number(frontend.numKeep()));
    parser.addOption(numKeepOption);

    QCommandLineOption numPredictOption("num-predict", "Number of tokens to predict.", "num-predict",
                                        QString::number(frontend.numPredict()));
    parser.addOption(numPredictOption);

    QCommandLineOption topKOption("top-k", "Top-k sampling.", "top-k", QString::number(frontend.topK()));
    parser.addOption(topKOption);

    QCommandLineOption topPOption("top-p", "Top-p sampling.", "top-p", QString::number(frontend.topP()));
    parser.addOption(topPOption);

    QCommandLineOption minPOption("min-p", "Min-p sampling.", "min-p", QString::number(frontend.minP()));
    parser.addOption(minPOption);

    QCommandLineOption tfsZOption("tfs-z", "Tail-free sampling.", "tfs-z", QString::number(frontend.tfsZ()));
    parser.addOption(tfsZOption);

    QCommandLineOption typicalPOption("typical-p", "Typical-p sampling.", "typical-p", QString::number(frontend.typicalP()));
    parser.addOption(typicalPOption);

    QCommandLineOption repeatLastNOption("repeat-last-n", "Repeat last N tokens.", "repeat-last-n",
                                         QString::number(frontend.repeatLastN()));
    parser.addOption(repeatLastNOption);

    QCommandLineOption temperatureOption("temperature", "Temperature.", "temperature", QString::number(frontend.temperature()));
    parser.addOption(temperatureOption);

    QCommandLineOption repeatPenaltyOption("repeat-penalty", "Repeat penalty.", "repeat-penalty",
                                           QString::number(frontend.repeatPenalty()));
    parser.addOption(repeatPenaltyOption);

    QCommandLineOption presencePenaltyOption("presence-penalty", "Presence penalty.", "presence-penalty",
                                             QString::number(frontend.presencePenalty()));
    parser.addOption(presencePenaltyOption);

    QCommandLineOption frequencyPenaltyOption("frequency-penalty", "Frequency penalty.", "frequency-penalty",
                                              QString::number(frontend.frequencyPenalty()));
    parser.addOption(frequencyPenaltyOption);

    QCommandLineOption mirostatOption("mirostat", "Mirostat sampling.", "mirostat", QString::number(frontend.mirostat()));
    parser.addOption(mirostatOption);

    QCommandLineOption mirostatTauOption("mirostat-tau", "Mirostat tau.", "mirostat-tau", QString::number(frontend.mirostatTau()));
    parser.addOption(mirostatTauOption);

    QCommandLineOption mirostatEtaOption("mirostat-eta", "Mirostat eta.", "mirostat-eta", QString::number(frontend.mirostatEta()));
    parser.addOption(mirostatEtaOption);

    QCommandLineOption penalizeNewlineOption("penalize-newline", "Penalize newline.", "penalize-newline",
                                             frontend.penalizeNewline() ? "true" : "false");
    parser.addOption(penalizeNewlineOption);

    QCommandLineOption stopOption("stop", "Stop sequence.", "stop", frontend.stop());
    parser.addOption(stopOption);

    QCommandLineOption numaOption("numa", "Enable NUMA.", "numa", frontend.numa() ? "true" : "false");
    parser.addOption(numaOption);

    QCommandLineOption numCtxOption("num-ctx", "Number of context tokens.", "num-ctx", QString::number(frontend.numCtx()));
    parser.addOption(numCtxOption);

    QCommandLineOption numBatchOption("num-batch", "Batch size.", "num-batch", QString::number(frontend.numBatch()));
    parser.addOption(numBatchOption);

    QCommandLineOption numGpuOption("num-gpu", "Number of GPUs.", "num-gpu", QString::number(frontend.numGpu()));
    parser.addOption(numGpuOption);

    QCommandLineOption mainGpuOption("main-gpu", "Main GPU.", "main-gpu", QString::number(frontend.mainGpu()));
    parser.addOption(mainGpuOption);

    QCommandLineOption lowVramOption("low-vram", "Low VRAM mode.", "low-vram", frontend.lowVram() ? "true" : "false");
    parser.addOption(lowVramOption);

    QCommandLineOption vocabOnlyOption("vocab-only", "Vocab only mode.", "vocab-only", frontend.vocabOnly() ? "true" : "false");
    parser.addOption(vocabOnlyOption);

    QCommandLineOption useMmapOption("use-mmap", "Use mmap.", "use-mmap", frontend.useMmap() ? "true" : "false");
    parser.addOption(useMmapOption);

    QCommandLineOption useMlockOption("use-mlock", "Use mlock.", "use-mlock", frontend.useMlock() ? "true" : "false");
    parser.addOption(useMlockOption);

    QCommandLineOption numThreadOption("num-thread", "Number of threads.", "num-thread", QString::number(frontend.numThread()));
    parser.addOption(numThreadOption);

    // --- Actions ---
    QCommandLineOption sendOption("send", "Send a message to the model.", "message");
    parser.addOption(sendOption);

    QCommandLineOption sendMessagesOption("send-messages", "Send a JSON array of messages to the model.", "messages");
    parser.addOption(sendMessagesOption);

    QCommandLineOption imageFileOption("image", "Path to an image file to include with the message.", "path");
    parser.addOption(imageFileOption);

    QCommandLineOption listModelsOption("list-models", "List available models.");
    parser.addOption(listModelsOption);

    QCommandLineOption pullModelOption("pull", "Pull a model.", "model-name");
    parser.addOption(pullModelOption);

    QCommandLineOption deleteModelOption("delete", "Delete a model.", "model-name");
    parser.addOption(deleteModelOption);

    QCommandLineOption startChat("start-chat", "Starts new chat.");
    parser.addOption(startChat);

    QCommandLineOption getModelsDb("get-models-db", "Get models from database.");
    parser.addOption(getModelsDb);

    QCommandLineOption exportChatOption("export-chat", "Export the chat messages.");
    parser.addOption(exportChatOption);

    QCommandLineOption exportFilePathOption("export-file", "File path for export.", "filepath");
    parser.addOption(exportFilePathOption);

    QCommandLineOption exportFormatOption("export-format", "Export format (json or plaintext).", "format", "json");
    parser.addOption(exportFormatOption);

    QCommandLineOption exportMessageSelectionOption("export-selection", "Message selection for export (all, user, or assistant).",
                                                    "selection", "all");
    parser.addOption(exportMessageSelectionOption);
}

void processCliOptions(const QCommandLineParser &parser, QtOllamaFrontend &frontend) {
    // --- API Options ---
    if (parser.isSet("host")) {
        frontend.setHost(parser.value("host"));
    }
    if (parser.isSet("port")) {
        frontend.setPort(parser.value("port").toInt());
    }
    if (parser.isSet("model")) {
        frontend.setModelName(parser.value("model"));
    }
    if (parser.isSet("stream")) {
        frontend.setStream(parser.value("stream") == "true");
    }

    // --- Settings ---
    if (parser.isSet("show-log")) {
        frontend.setShowLog(parser.value("show-log") == "true");
    }
    if (parser.isSet("output-tts")) {
        frontend.setOutputTts(parser.value("output-tts") == "true");
    }
    if (parser.isSet("multiline")) {
        frontend.setTextMessageMultiline(parser.value("multiline") == "true");
    }
    if (parser.isSet("image-width")) {
        frontend.setScaledImageWidth(parser.value("image-width").toInt());
    }
    if (parser.isSet("image-height")) {
        frontend.setScaledImageHeight(parser.value("image-height").toInt());
    }

    // --- Model Options ---
    if (parser.isSet("seed")) {
        frontend.setSeed(parser.value("seed").toInt());
    }
    if (parser.isSet("num-keep")) {
        frontend.setNumKeep(parser.value("num-keep").toInt());
    }
    if (parser.isSet("num-predict")) {
        frontend.setNumPredict(parser.value("num-predict").toInt());
    }
    if (parser.isSet("top-k")) {
        frontend.setTopK(parser.value("top-k").toInt());
    }
    if (parser.isSet("top-p")) {
        frontend.setTopP(parser.value("top-p").toDouble());
    }
    if (parser.isSet("min-p")) {
        frontend.setMinP(parser.value("min-p").toDouble());
    }
    if (parser.isSet("tfs-z")) {
        frontend.setTfsZ(parser.value("tfs-z").toDouble());
    }
    if (parser.isSet("typical-p")) {
        frontend.setTypicalP(parser.value("typical-p").toDouble());
    }
    if (parser.isSet("repeat-last-n")) {
        frontend.setRepeatLastN(parser.value("repeat-last-n").toInt());
    }
    if (parser.isSet("temperature")) {
        frontend.setTemperature(parser.value("temperature").toDouble());
    }
    if (parser.isSet("repeat-penalty")) {
        frontend.setRepeatPenalty(parser.value("repeat-penalty").toDouble());
    }
    if (parser.isSet("presence-penalty")) {
        frontend.setPresencePenalty(parser.value("presence-penalty").toDouble());
    }
    if (parser.isSet("frequency-penalty")) {
        frontend.setFrequencyPenalty(parser.value("frequency-penalty").toDouble());
    }
    if (parser.isSet("mirostat")) {
        frontend.setMirostat(parser.value("mirostat").toInt());
    }
    if (parser.isSet("mirostat-tau")) {
        frontend.setMirostatTau(parser.value("mirostat-tau").toDouble());
    }
    if (parser.isSet("mirostat-eta")) {
        frontend.setMirostatEta(parser.value("mirostat-eta").toDouble());
    }
    if (parser.isSet("penalize-newline")) {
        frontend.setPenalizeNewline(parser.value("penalize-newline") == "true");
    }
    if (parser.isSet("stop")) {
        frontend.setStop(parser.value("stop"));
    }
    if (parser.isSet("numa")) {
        frontend.setNuma(parser.value("numa") == "true");
    }
    if (parser.isSet("num-ctx")) {
        frontend.setNumCtx(parser.value("num-ctx").toInt());
    }
    if (parser.isSet("num-batch")) {
        frontend.setNumBatch(parser.value("num-batch").toInt());
    }
    if (parser.isSet("num-gpu")) {
        frontend.setNumGpu(parser.value("num-gpu").toInt());
    }
    if (parser.isSet("main-gpu")) {
        frontend.setMainGpu(parser.value("main-gpu").toInt());
    }
    if (parser.isSet("low-vram")) {
        frontend.setLowVram(parser.value("low-vram") == "true");
    }
    if (parser.isSet("vocab-only")) {
        frontend.setVocabOnly(parser.value("vocab-only") == "true");
    }
    if (parser.isSet("use-mmap")) {
        frontend.setUseMmap(parser.value("use-mmap") == "true");
    }
    if (parser.isSet("use-mlock")) {
        frontend.setUseMlock(parser.value("use-mlock") == "true");
    }
    if (parser.isSet("num-thread")) {
        frontend.setNumThread(parser.value("num-thread").toInt());
    }
}

int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);
    QCoreApplication::setApplicationName("QtOllamaCLI");
    QCoreApplication::setApplicationVersion("1.0");

    QtOllamaFrontend frontend;
    QCommandLineParser parser;
    setupCliParser(parser, frontend);
    parser.process(app);
    processCliOptions(parser, frontend);

    // --- Actions ---
    if (parser.isSet("send")) {
        QString message = parser.value("send");
        QString imagePath = parser.isSet("image") ? parser.value("image") : "";
        QObject::connect(&frontend, &QtOllamaFrontend::receivedResponse, [&](const QVariant &result) {
            if (result.canConvert<QString>()) {
                std::cout << result.toString().toStdString() << std::endl;
            } else {
                qDebug() << "Received non-string response";
            }
            app.exit(0);
        });
        QObject::connect(&frontend, &QtOllamaFrontend::receivedNetworkError, [&](const QVariant &error) {
            qDebug() << "Network error: " << error;
            app.exit(1);
        });

        qDebug() << "###$$$ message: " << message << "\n\n";
        qDebug() << "###$$$ imagePath: " << imagePath << "\n\n";
        frontend.sendMessage(message, imagePath);
    } else if (parser.isSet("send-messages")) {
        QString messagesString = parser.value("send-messages");
        QJsonDocument doc = QJsonDocument::fromJson(messagesString.toUtf8());
        QJsonArray messages = doc.array();

        QObject::connect(&frontend, &QtOllamaFrontend::receivedResponse, [&](const QVariant &result) {
            if (result.canConvert<QString>()) {
                std::cout << result.toString().toStdString() << std::endl;
            } else {
                qDebug() << "Received non-string response";
            }
            app.exit(0);
        });
        QObject::connect(&frontend, &QtOllamaFrontend::receivedNetworkError, [&](const QVariant &error) {
            qDebug() << "Network error: " << error;
            app.exit(1);
        });

        qDebug() << "###$$$ messages: " << messagesString << "\n\n";

        frontend.sendMessages(messages);
    } else if (parser.isSet("list-models")) {
        QObject::connect(&frontend, &QtOllamaFrontend::receivedModels, [&](const QVariant &result) {
            if (result.canConvert<QString>()) {
                std::cout << result.toString().toStdString() << std::endl;
            }
            app.exit(0);
        });
        QObject::connect(&frontend, &QtOllamaFrontend::receivedNetworkError, [&](const QVariant &error) {
            qDebug() << "Network error: " << error;
            app.exit(1);
        });
        frontend.getModels();
    } else if (parser.isSet("pull")) {
        QString modelName = parser.value("pull");
        QObject::connect(&frontend, &QtOllamaFrontend::receivedPullModelProgress,
                         [&](QString modelName, QString status, qint64 bytesReceived, qint64 bytesTotal) {
                             std::cout << "Pulling " << modelName.toStdString() << ": " << status.toStdString() << " (" << bytesReceived
                                       << "/" << bytesTotal << ")" << std::endl;
                         });
        QObject::connect(&frontend, &QtOllamaFrontend::receivedPullModel, [&](const QVariant &result) {
            if (result.canConvert<QString>()) {
                std::cout << "Successfully pulled: " << result.toString().toStdString() << std::endl;
            }
            app.exit(0);
        });
        QObject::connect(&frontend, &QtOllamaFrontend::receivedNetworkError, [&](const QVariant &error) {
            qDebug() << "Network error: " << error;
            app.exit(1);
        });
        frontend.pullModel(modelName);

    } else if (parser.isSet("delete")) {
        QString modelName = parser.value("delete");
        QObject::connect(&frontend, &QtOllamaFrontend::receivedDeleteModel, [&](const QVariant &result) {
            if (result.canConvert<QString>()) {
                std::cout << "Successfully deleted: " << result.toString().toStdString() << std::endl;
            }
            app.exit(0);
        });
        QObject::connect(&frontend, &QtOllamaFrontend::receivedNetworkError, [&](const QVariant &error) {
            qDebug() << "Network error: " << error;
            app.exit(1);
        });
        frontend.deleteModel(modelName);
    } else if (parser.isSet("start-chat")) {
        QObject::connect(&frontend, &QtOllamaFrontend::receivedNewChatStarted, [&]() {
            std::cout << "New chat started." << std::endl;
            app.exit(0);
        });
        frontend.startNewChat();
    } else if (parser.isSet("get-models-db")) {
        QVariantList models = frontend.getModelsFromDb();
        for (const QVariant &model : models) {
            QVariantMap modelMap = model.toMap();
            std::cout << "Name: " << modelMap["name"].toString().toStdString() << std::endl;
            std::cout << "  Description: " << modelMap["description"].toString().toStdString() << std::endl;
            std::cout << "  Parameter Size: " << modelMap["parameterSize"].toString().toStdString() << std::endl;
            std::cout << "  Size: " << modelMap["size"].toString().toStdString() << std::endl;
        }
        app.exit(0);
    } else if (parser.isSet("export-chat")) {
        QString filePath = parser.value("export-file");
        if (filePath.isEmpty()) {
            std::cerr << "Error: --export-file must be specified." << std::endl;
            app.exit(1);
            return 1; // Return to avoid warnings about unused return value.
        }
        QtOllamaFrontend::ExportFormat format = QtOllamaFrontend::ExportFormatJson;
        if (parser.value("export-format") == "plaintext") {
            format = QtOllamaFrontend::ExportFormatPlainText;
        }
        QtOllamaFrontend::ExportMessageSelection selection = QtOllamaFrontend::ExportMessageSelectionAllMessages;
        if (parser.value("export-selection") == "user") {
            selection = QtOllamaFrontend::ExportMessageSelectionOnlyUserMessages;
        } else if (parser.value("export-selection") == "assistant") {
            selection = QtOllamaFrontend::ExportMessageSelectionOnlyAssistantMessages;
        }

        frontend.exportChatMessages(filePath, format, selection);
        std::cout << "Chat exported to: " << filePath.toStdString() << std::endl;
        app.exit(0);

    } else {
        // If no action specified, print help
        parser.showHelp();
        app.exit(1); // Exit with an error code since no action was taken
    }

    return app.exec();
}
