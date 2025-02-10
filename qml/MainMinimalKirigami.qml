import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtTextToSpeech
import QtOllamaFrontend.QtOllamaFrontend 1.0
import org.kde.kirigami as Kirigami

Kirigami.ApplicationWindow {
    id: appWindow
    width: 600
    height: 400
    visible: true
    title: qsTr("QtOllamaFrontend Minimal (Kirigami)")

    TextToSpeech {
        id: textToSpeech
        Component.onCompleted: {
            if (qtOllamaFrontend.ttsEngine != "") {
                var engines = availableEngines();
                var index = engines.indexOf(qtOllamaFrontend.ttsEngine);
                if (index >= 0) engine = availableEngines()[index];
            }
            if (qtOllamaFrontend.ttsLocale != "") {
                var locales = availableLocales().map((locale) => locale.nativeLanguageName);
                var index = locales.indexOf(qtOllamaFrontend.ttsLocale);
                if (index >= 0) locale = availableLocales()[index];
            }
            if (qtOllamaFrontend.ttsVoice != "") {
                var voices = availableVoices().map((voice) => voice.name);
                var index = voices.indexOf(qtOllamaFrontend.ttsVoice);
                if (index >= 0) voice = availableVoices()[index];
            }
            rate = qtOllamaFrontend.ttsRate;
            pitch = qtOllamaFrontend.ttsPitch;
            volume = qtOllamaFrontend.ttsVolume;
        }
    }

    Connections {
        target: qtOllamaFrontend
        ignoreUnknownSignals: true
        function onSay(text) {
            if (qtOllamaFrontend.outputTts) textToSpeech.say(text);
        }
        function onReceivedResponse(result) {
            const json = JSON.parse(result);
            if (json.message) {
                listModelMessages.append({
                    "role": json.message.role,
                    "content": json.message.content,
                    "done": json.message.done
                });
            }
        }
        function onReceivedNewChatStarted() {
            listModelMessages.clear();
        }
        function onReceivedNetworkError(result) {
            console.log("Network Error:", result); // Minimal error handling
        }
    }

    pageStack.initialPage: Kirigami.ScrollablePage {
        title: 'Chat'

        ColumnLayout {
            anchors.fill: parent

            Kirigami.Action {
                id: newChatAction
                text: qsTr("New Chat")
                onTriggered: {
                    qtOllamaFrontend.startNewChat();
                    qtOllamaFrontend.setStream(true);
                }
            }

            Kirigami.ActionToolBar {
                actions: [ newChatAction ]
                flat: false
            }

            ListView {
                id: listViewMessages
                Layout.fillWidth: true
                Layout.fillHeight: true
                model: ListModel { id: listModelMessages }
                delegate: Kirigami.AbstractCard {
                    width: listViewMessages.width
                    header: Text {
                        text: (model.role === "user" ? "You: " : "Assistant: ")
                        wrapMode: Text.WordWrap
                        color: model.role === "user" ? "green" : "blue"
                    }
                    footer: Text {
                        text: model.content
                        wrapMode: Text.WordWrap
                    }
                }
            }

            RowLayout {
                Layout.fillWidth: true
                CustomTextField {
                    id: messageField
                    Layout.fillWidth: true
                    placeholderText: qsTr("Type your message...")
                    onAccepted: {
                        const messageContent = messageField.text.trim();
                        if (messageContent) {
                            listModelMessages.append({
                                "role": "user",
                                "content": messageContent,
                                "done": true
                            });
                            qtOllamaFrontend.sendMessage(messageContent, "");
                            messageField.text = "";
                        }
                    }
                }
                CustomButton {
                    text: qsTr("Send")
                    onClicked: messageField.accepted()
                }
            }
        }
        //Kirigami.BusyIndicator {
        //    anchors.centerIn: parent
        //    running: qtOllamaFrontend.loading
        //    visible: qtOllamaFrontend.loading
        //}
    }
}