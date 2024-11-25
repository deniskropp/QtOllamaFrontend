import QtCore
import QtQuick
import QtQuick.Dialogs
import QtQuick.Controls
import QtQuick.Layouts
import QtOllamaFrontend.QtOllamaFrontend 1.0

Dialog {
    id: dialog
    property int exportFormat: QtOllamaFrontend.ExportFormatJson
    property int exportMessageSelection: QtOllamaFrontend.ExportMessageSelectionAllMessages
    title: qsTr("Export Messages")
    standardButtons: Dialog.Cancel|Dialog.Save
    modal: true
    closePolicy: Popup.CloseOnEscape
    x: (appWindow.width - width) / 2
    y: (appWindow.height - height) / 2
    width: 400
    height: 400
    clip: true
    FileDialog {
        id: fileDialog
        fileMode: FileDialog.SaveFile
        currentFolder: StandardPaths.standardLocations(StandardPaths.DocumentsLocation)[0]
        onAccepted: qtOllamaFrontend.exportChatMessages(fileDialog.selectedFile, exportFormat, exportMessageSelection)
    }
    onAccepted: {
        if (exportFormat == QtOllamaFrontend.ExportFormatJson) {
            fileDialog.nameFilters = ["json (*.json)"];
            fileDialog.defaultSuffix = "json";
            fileDialog.selectedFile = "chat.json";
        } else if (exportFormat == QtOllamaFrontend.ExportFormatPlainText) {
            fileDialog.nameFilters = ["text (*.txt)"];
            fileDialog.defaultSuffix = "txt";
            fileDialog.selectedFile = "chat.txt";
        }

        fileDialog.open();
    }
    contentItem: ColumnLayout {
        Label {
            Layout.fillWidth: true
            Layout.margins: 10
            wrapMode: Text.WordWrap
            text: qsTr("Export chat messages as a file.")
        }
        // message selection
        CustomLabel {
            Layout.leftMargin: 10
            text: qsTr("select messages")
        }
        ButtonGroup {
            id: buttonGroupMessageSelection
        }
        RadioButton {
            Layout.fillWidth: true
            Layout.leftMargin: 10
            Layout.topMargin: 10
            checked: true
            ButtonGroup.group: buttonGroupMessageSelection
            text: qsTr("all messages")
            onCheckedChanged: {
                if (checked) {
                    exportMessageSelection = QtOllamaFrontend.ExportMessageSelectionAllMessages;
                }
            }
        }
        RadioButton {
            Layout.fillWidth: true
            Layout.leftMargin: 10
            Layout.topMargin: 10
            ButtonGroup.group: buttonGroupMessageSelection
            text: qsTr("only user messages")
            onCheckedChanged: {
                if (checked) {
                    exportMessageSelection = QtOllamaFrontend.ExportMessageSelectionOnlyUserMessages;
                }
            }
        }
        RadioButton {
            Layout.fillWidth: true
            Layout.leftMargin: 10
            Layout.topMargin: 10
            ButtonGroup.group: buttonGroupMessageSelection
            text: qsTr("only assistant messages")
            onCheckedChanged: {
                if (checked) {
                    exportMessageSelection = QtOllamaFrontend.ExportMessageSelectionOnlyAssistantMessages;
                }
            }
        }
        // format
        CustomLabel {
            Layout.leftMargin: 10
            Layout.topMargin: 20
            text: qsTr("format")
        }
        ButtonGroup {
            id: buttonGroupFormat
        }
        RadioButton {
            Layout.fillWidth: true
            Layout.leftMargin: 10
            Layout.topMargin: 10
            checked: true
            ButtonGroup.group: buttonGroupFormat
            text: qsTr("json")
            onCheckedChanged: {
                if (checked) {
                    exportFormat = QtOllamaFrontend.ExportFormatJson;
                }
            }
        }
        RadioButton {
            Layout.fillWidth: true
            Layout.leftMargin: 10
            Layout.topMargin: 10
            ButtonGroup.group: buttonGroupFormat
            text: qsTr("plain text")
            onCheckedChanged: {
                if (checked) {
                    exportFormat = QtOllamaFrontend.ExportFormatPlainText;
                }
            }
        }
        // spacer
        Item {
            Layout.fillHeight: true
        }
    }
}
