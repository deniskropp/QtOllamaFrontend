#!/bin/bash

# Create the directory structure
mkdir -p QtOllamaFrontend/qml/components
mkdir -p QtOllamaFrontend/qml/dialogs
mkdir -p QtOllamaFrontend/src

# Create the files
touch QtOllamaFrontend/qml/resources.js
touch QtOllamaFrontend/qml/AppState.qml
touch QtOllamaFrontend/qml/components/ChatMessageDelegate.qml
touch QtOllamaFrontend/qml/components/LogEntryDelegate.qml
touch QtOllamaFrontend/qml/components/ChatInputArea.qml
touch QtOllamaFrontend/qml/components/LogView.qml
touch QtOllamaFrontend/qml/components/CustomButton.qml
touch QtOllamaFrontend/qml/components/CustomLabel.qml
touch QtOllamaFrontend/qml/components/CustomTextArea.qml
touch QtOllamaFrontend/qml/components/CustomTextField.qml
touch QtOllamaFrontend/qml/Main.qml


# Populate the files with the generated code (using 'cat' and here-documents)

cat << EOF > QtOllamaFrontend/qml/resources.js
// QtOllamaFrontend/qml/resources.js
.pragma library

function roundNumber(number) {
    return (Math.round(parseFloat(number) * 100.0) / 100.0).toFixed(2);
}

function getPrettyPrintedSize(size) {
    if (size >= 1024 * 1024 * 1024 * 1024) {
        return roundNumber(size / (1024 * 1024 * 1024 * 1024)) + " TB";
    } else if (size >= 1024 * 1024 * 1024) {
        return roundNumber(size / (1024 * 1024 * 1024)) + " GB";
    } else if (size >= 1024 * 1024) {
        return roundNumber(size / (1024 * 1024)) + " MB";
    } else if (size >= 1024) {
        return roundNumber(size / 1024) + " kB";
    } else {
        return roundNumber(size) + " B";
    }
}
EOF

cat << EOF > QtOllamaFrontend/qml/AppState.qml
// QtOllamaFrontend/qml/AppState.qml
pragma Singleton
import QtQuick

QtObject {
    id: appState

    property string currentModel: qtOllamaFrontend.modelName
    property bool showLog: qtOllamaFrontend.showLog
    property bool outputTts: qtOllamaFrontend.outputTts
    property bool textMessageMultiline: qtOllamaFrontend.textMessageMultiline
    property bool stream: qtOllamaFrontend.stream
    property var textToSpeech

    signal messageReceived(var message)
    signal newChatStarted()
    signal logEntryAdded(string title, string data)
    signal networkError(string error)

    Connections {
        target: qtOllamaFrontend
        ignoreUnknownSignals: true

        function onSay(text) {
            if (appState.outputTts) {
                appState.textToSpeech.say(text);
            }
        }

        function onReceivedResponse(result) {
            const json = JSON.parse(result);
            if (json.message) {
                appState.messageReceived({
                    "role": json.message.role,
                    "content": json.message.content,
                    "imageUrl": "",
                    "done": json.message.done
                });
            }
        }

        function onReceivedNewChatStarted() {
            appState.newChatStarted();
        }
        function onLog(title, data) {
            var json = {};
            try {
                json = JSON.parse(data);
            } catch (e) {
                json = {
                    "data": data
                }
            }
            appState.logEntryAdded(title, JSON.stringify(json, null, 4));
        }

        function onReceivedNetworkError(result) {
            appState.networkError(qsTr("network error: %1").arg(result));
        }

        function onModelNameChanged() {
            appState.currentModel = qtOllamaFrontend.modelName
        }
        function onShowLogChanged() {
            appState.showLog = qtOllamaFrontend.showLog;
        }
        function onOutputTtsChanged(){
            appState.outputTts = qtOllamaFrontend.outputTts;
        }
        function onTextMessageMultilineChanged(){
            appState.textMessageMultiline = qtOllamaFrontend.textMessageMultiline;
        }
        function onStreamChanged(){
            appState.stream = qtOllamaFrontend.stream
        }
    }
}
EOF

cat << EOF > QtOllamaFrontend/qml/components/ChatMessageDelegate.qml
// QtOllamaFrontend/qml/components/ChatMessageDelegate.qml
import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import "../"

ItemDelegate {
    id: chatMessageDelegate
    width: ListView.view.width
    height: itemDelegateRow.height

    property alias done: chatMessageDelegate.done
    property alias role: model.role
    property alias content: model.content
    property alias imageUrl: model.imageUrl

    background: Rectangle {
        color: "#eeeeee"
    }

    onClicked: {
        if (AppState.textToSpeech)
            AppState.textToSpeech.say(model.content);
    }

    RowLayout {
        id: itemDelegateRow
        width: parent.width
        ColumnLayout {
            Layout.fillWidth: true
            Layout.margins: 10
            RowLayout {
                Layout.fillWidth: true
                CustomLabel {
                    color: model.role === "user" ? "#77dd77" : "#77dddd"
                    text: model.role === "user" ? qsTr("You") : qsTr("Assistant")
                }
                CustomButton {
                    text: qsTr("Play")
                    onClicked: {
                         if (AppState.textToSpeech)
                            AppState.textToSpeech.say(model.content);
                    }
                }
                CustomButton {
                    text: qsTr("Copy To Clipboard")
                    onClicked: {
                        qtOllamaFrontend.copyTextToClipboard(model.content);
                    }
                }
            }
            CustomTextArea {
                Layout.fillWidth: true
                Layout.fillHeight: true
                readOnly: true
                wrapMode: Text.WordWrap
                text: model.content
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                         if (AppState.textToSpeech)
                            AppState.textToSpeech.say(model.content);
                    }
                }
            }
            Image {
                Layout.leftMargin: 10
                Layout.preferredWidth: 100
                Layout.preferredHeight: 100
                fillMode: Image.PreserveAspectFit
                antialiasing: true
                smooth: true
                sourceSize.width: 100
                sourceSize.height: 100
                visible: model.imageUrl !== ""
                source: model.imageUrl
            }
        }
    }
}
EOF

cat << EOF > QtOllamaFrontend/qml/components/LogEntryDelegate.qml
// QtOllamaFrontend/qml/components/LogEntryDelegate.qml
import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import "../"
ItemDelegate {
    id: logEntryDelegate
    width: ListView.view.width
    height: itemDelegateRowLog.height

    property alias title: model.title
    property alias data: model.data

    background: Rectangle {
        color: "#eeeeee"
    }

    RowLayout {
        id: itemDelegateRowLog
        width: parent.width
        ColumnLayout {
            Layout.fillWidth: true
            Layout.margins: 10
            CustomLabel {
                text: model.title
                color: "#111188"
                visible: model.title !== ""
            }
            CustomTextArea {
                Layout.fillWidth: true
                Layout.fillHeight: true
                readOnly: true
                wrapMode: Text.WordWrap
                text: model.data
                visible: model.data !== ""
            }
        }
    }
}
EOF

cat << EOF > QtOllamaFrontend/qml/components/ChatInputArea.qml
// QtOllamaFrontend/qml/components/ChatInputArea.qml
import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import "../"

RowLayout {
    id: chatInputArea
    property alias textMessageMultiline: checkBoxTextMessageMultiline.checked

    SplitView.preferredHeight: implicitHeight
    SplitView.minimumHeight: implicitHeight
    SplitView.maximumHeight: 0.25 * appWindow.height

    // message text - single line
    CustomTextField {
        id: textField
        Layout.fillWidth: true
        Layout.topMargin: 10
        Layout.bottomMargin: 10
        Layout.leftMargin: 10
        Layout.rightMargin: 10
        font.pointSize: 12
        placeholderText: qsTr("Message Text")
        visible: !checkBoxTextMessageMultiline.checked
        onTextChanged: textArea.text = text
        onAccepted: sendMessage()
    }

    // message text - multiline
    ColumnLayout {
        Layout.fillWidth: true
        visible: checkBoxTextMessageMultiline.checked
        CustomTextArea {
            id: textArea
            Layout.fillWidth: true
            Layout.topMargin: 10
            Layout.bottomMargin: 10
            Layout.leftMargin: 10
            Layout.rightMargin: 10
            font.pointSize: 12
            placeholderText: qsTr("Message Text")
            onTextChanged: textField.text = text
        }
        CustomButton {
            Layout.topMargin: 10
            Layout.bottomMargin: 10
            Layout.leftMargin: 10
            Layout.rightMargin: 10
            text: qsTr("Send Message")
            onClicked: sendMessage()
        }
    }

    CheckBox {
        id: checkBoxTextMessageMultiline
        Layout.topMargin: 10
        Layout.bottomMargin: 10
        Layout.leftMargin: 10
        Layout.rightMargin: 10
        text: qsTr("Multiline")
        checked: AppState.textMessageMultiline
        onClicked: {
            AppState.textMessageMultiline = checked;
        }
    }

    function sendMessage() {
        const messageContent = checkBoxTextMessageMultiline.checked ? textArea.text.trim() : textField.text.trim();

        if (messageContent === "") {
            if (checkBoxTextMessageMultiline.checked) {
                textArea.forceActiveFocus();
            } else {
                textField.forceActiveFocus();
            }
            return;
        }

        if (checkBoxTextMessageMultiline.checked) {
                textArea.text = "";
            } else {
                textField.text = "";
            }

        AppState.messageReceived({
            "role": "user",
            "content": messageContent,
            "imageUrl": "",
            "done": true
        });

        qtOllamaFrontend.sendMessage(messageContent, "");
    }
}
EOF

cat << EOF > QtOllamaFrontend/qml/components/LogView.qml
// QtOllamaFrontend/qml/components/LogView.qml
import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import "../"
import "./"

ScrollView {
    id: logView
    property alias model: listModelLog

    ScrollBar.horizontal.visible: false
    smooth: true

    ListView {
        id: logListView
        Layout.fillHeight: true
        Layout.fillWidth: true

        CustomButton {
            anchors.top: parent.top
            anchors.right: parent.right
            text: qsTr("Clear Log")
            onClicked: listModelLog.clear()
        }

        model: ListModel {
            id: listModelLog
        }
        delegate: LogEntryDelegate {}
    }
    Connections {
        target: AppState
        function onLogEntryAdded(title, data) {
                listModelLog.append({
                    "title": title,
                    "data": data
                });

            logListView.positionViewAtEnd();
        }
    }
}
EOF

cat << EOF > QtOllamaFrontend/qml/components/CustomButton.qml
// QtOllamaFrontend/qml/components/CustomButton.qml
import QtQuick
import QtQuick.Controls

Button {
    // Add any custom styling or properties common to all buttons here
}
EOF

cat << EOF > QtOllamaFrontend/qml/components/CustomLabel.qml
// QtOllamaFrontend/qml/components/CustomLabel.qml
import QtQuick
import QtQuick.Controls

Label{

}
EOF

cat << EOF > QtOllamaFrontend/qml/components/CustomTextArea.qml
// QtOllamaFrontend/qml/components/CustomTextArea.qml
import QtQuick
import QtQuick.Controls

TextArea{

}
EOF
cat << EOF > QtOllamaFrontend/qml/components/CustomTextField.qml
// QtOllamaFrontend/qml/components/CustomTextField.qml
import QtQuick
import QtQuick.Controls

TextField{

}
EOF

cat << EOF > QtOllamaFrontend/qml/Main.qml
// QtOllamaFrontend/qml/Main.qml
import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtTextToSpeech
import QtOllamaFrontend.QtOllamaFrontend 1.0
import "./components"
import "./dialogs"

ApplicationWindow {
    id: appWindow
    width: 800
    height: 700
    visible: true
    title: qsTr("QtOllamaFrontend")

     TextToSpeech {
        id: textToSpeech
        Component.onCompleted: {
            if (qtOllamaFrontend.ttsEngine != "") {
                var engines = availableEngines();
                var index = engines.indexOf(qtOllamaFrontend.ttsEngine);

                if (index >= 0) {
                    console.log("selected engine:", availableEngines()[index]);
                    engine = availableEngines()[index];
                }
            }

            if (qtOllamaFrontend.ttsLocale != "") {
                var locales = availableLocales().map((locale) => locale.nativeLanguageName);
                var index = locales.indexOf(qtOllamaFrontend.ttsLocale);

                if (index >= 0) {
                    console.log("selected locale:", availableLocales()[index].nativeLanguageName);
                    locale = availableLocales()[index];
                }
            }

            if (qtOllamaFrontend.ttsVoice != "") {
                var voices = availableVoices().map((voice) => voice.name);
                var index = voices.indexOf(qtOllamaFrontend.ttsVoice);

                if (index >= 0) {
                    console.log("selected voice:", availableVoices()[index].name);
                    voice = availableVoices()[index];
                }
            }

            rate = qtOllamaFrontend.ttsRate;
            pitch = qtOllamaFrontend.ttsPitch;
            volume = qtOllamaFrontend.ttsVolume;
        }
    }

    Component.onCompleted: {
        AppState.textToSpeech = textToSpeech
    }

    SplitView {
        anchors.fill: parent
        orientation: Qt.Vertical
        SplitView {
            SplitView.fillHeight: true
            orientation: Qt.Horizontal

            // Chat Message View
            ScrollView {
                SplitView.fillWidth: true
                ScrollBar.horizontal.visible: false
                smooth: true

                ListView {
                    id: messageListView
                    Layout.fillHeight: true
                    Layout.fillWidth: true

                    CustomButton {
                        anchors.top: parent.top
                        anchors.right: parent.right
                        text: qsTr("Clear Chat")
                        onClicked: listModelMessages.clear()
                    }
                    Connections {
                        target: AppState
                        function onNewChatStarted() {
                            listModelMessages.clear()
                        }
                        function onMessageReceived(message) {
                            if (message.done) {
                                // add new message list item
                                listModelMessages.append({
                                    "role": message.role,
                                    "content": message.content,
                                    "imageUrl": message.imageUrl !== "" ? message.imageUrl : "",
                                    "done": message.done
                                });
                            } else {
                                // stream
                                var index = listModelMessages.count - 1;
                                var lastMessage = listModelMessages.get(index);

                                if (lastMessage.done) {
                                    // add new message list item
                                    listModelMessages.append({
                                        "role": message.role,
                                        "content": message.content,
                                        "imageUrl": message.imageUrl !== "" ? message.imageUrl : "",
                                        "done": message.done
                                    });
                                } else {
                                    // update last message list item
                                    listModelMessages.set(index, {
                                        "content": message.content,
                                        "done": message.done
                                    });
                                }
                            }
                            messageListView.positionViewAtEnd()
                        }

                    }
                    model: ListModel {
                        id: listModelMessages
                    }
                    delegate: ChatMessageDelegate {}
                }
            }

            // Log View
            LogView {
                id: logArea
                SplitView.preferredWidth: 0.5 * appWindow.width
                SplitView.minimumWidth: 0.1 * appWindow.width
                SplitView.maximumWidth: 0.9 * appWindow.width
                visible: AppState.showLog
            }
        }

        // Chat Input Area
        ChatInputArea {
            id: chatInput
        }
    }

    menuBar: MenuBar {
       Menu {
            title: qsTr("&Chat")
            DialogNewChat {
                id: dialogNewChat
                onAccepted: qtOllamaFrontend.startNewChat()
            }
            Action {
                id: actionNewChat
                shortcut: "Ctrl+N"
                text: qsTr("&New Chat")
                onTriggered: dialogNewChat.open()
            }
            MenuSeparator { }
            DialogImage {
                id: dialogImage
                onAccepted: {
                    var jsonImages = images.length > 0 ? JSON.parse(images) : "";

                    AppState.messageReceived({
                        "role": "user",
                        "content": messageText,
                        "imageUrl": images.length > 0 ? jsonImages[0] : "",
                        "done": true
                    });

                    qtOllamaFrontend.sendMessage(messageText, images);
                }
            }
            Action {
                id: actionImage
                text: qsTr("&Message with Image")
                onTriggered: dialogImage.open()
            }
            DialogExportMessages {
                id: dialogExportMessages
            }
            Action {
                shortcut: "Ctrl+S"
                text: qsTr("&Export Chat Messages")
                onTriggered: dialogExportMessages.open()
            }
            MenuSeparator { }
            Action {
                id: actionTextMessageMultiline
                text: qsTr("&Multiline Text Field")
                checkable: true
                checked: AppState.textMessageMultiline
                onTriggered: {
                    AppState.textMessageMultiline = checked;
                }
            }
            MenuSeparator { }
            Action {
                text: qsTr("&Quit")
                onTriggered: appWindow.close()
            }
        }
        Menu {
            title: qsTr("&Model")
            DialogSelectModel {
                id: dialogSelectModel
            }
            Action {
                shortcut: "Ctrl+M"
                text: qsTr("&Select Model")
                onTriggered: dialogSelectModel.open()
            }
            DialogPullModel {
                id: dialogPullModel
            }
            Action {
                text: qsTr("&Pull Model")
                onTriggered: dialogPullModel.open()
            }
            DialogAddModel {
                id: dialogAddModel
                onAccepted: {
                    qtOllamaFrontend.addModelToDb(modelName, modelDescription, modelParameterSize, modelSize);
                }
            }
            Action {
                text: qsTr("&Add Model")
                onTriggered: dialogAddModel.open()
            }
            DialogModelOptions {
                id: dialogModelOptions
            }
            Action {
                text: qsTr("Model &Options")
                onTriggered: dialogModelOptions.open()
            }
            MenuSeparator { }
            Action {
                id: actionStream
                text: qsTr("S&tream Responses")
                checkable: true
                checked: AppState.stream
                onTriggered: {
                    AppState.stream = checked;
                }
            }
        }
        Menu {
            title: qsTr("&Settings")
            DialogModelSettings {
                id: dialogModelSettings
            }
            Action {
                text: qsTr("&Model")
                onTriggered: dialogModelSettings.open()
            }
            DialogService {
                id: dialogService
            }
            Action {
                text: qsTr("&Service")
                onTriggered: dialogService.open()
            }
            DialogTextToSpeech {
                id: dialogTextToSpeech
                textToSpeech: textToSpeech
            }
            Action {
                shortcut: "Ctrl+T"
                text: qsTr("&Text to Speech")
                onTriggered: dialogTextToSpeech.open()
            }
            MenuSeparator { }
            Action {
                id: actionShowLog
                text: qsTr("Show &Log")
                checkable: true
                checked: AppState.showLog
                onTriggered: {
                    AppState.showLog = checked
                }
            }
            Action {
                id: actionOutputTts
                text: qsTr("&Output TTS")
                checkable: true
                checked: AppState.outputTts
                onTriggered: {
                    AppState.outputTts = checked
                }
            }
        }
        Menu {
            title: qsTr("&Help")
            DialogAbout {
                id: dialogAbout
            }
            Action {
                text: qsTr("&About")
                onTriggered: dialogAbout.open()
            }
        }
    }

    footer: ToolBar {
        RowLayout {
            anchors.fill: parent
            BusyIndicator {
                id: busyIndicator
                Layout.topMargin: 10
                Layout.bottomMargin: 10
                running: qtOllamaFrontend.loading
            }

            CheckBox {
                id: checkBoxStream
                Layout.topMargin: 10
                Layout.bottomMargin: 10
                Layout.leftMargin: 10
                Layout.rightMargin: 10
                text: qsTr("Stream")
                checked: AppState.stream
                onClicked: {
                    AppState.stream = checked
                }
            }

            CustomButton {
                text: qsTr("New Chat")
                onClicked: {
                    actionNewChat.trigger();
                }
            }
            CustomButton {
                text: qsTr("Image")
                onClicked: {
                    actionImage.trigger();
                }
            }
            CustomButton {
                text: qsTr("Text to Speech")
                onClicked: {
                    dialogTextToSpeech.open();
                }
            }
            CustomButton {
                text: qsTr("Stop Playback")
                onClicked: {
                    // workaround - stop() method causes crash
                    if (AppState.textToSpeech)
                        AppState.textToSpeech.say(" ");
                }
            }
            Item {
                Layout.fillWidth: true
            }
            CustomButton {
                text: qsTr("Select Model")
                onClicked: {
                    dialogSelectModel.open();
                }
            }
            CustomLabel {
                Layout.topMargin: 10
                Layout.bottomMargin: 10
                Layout.leftMargin: 10
                Layout.rightMargin: 10
                text: AppState.currentModel
            }
        }
    }
}
EOF
