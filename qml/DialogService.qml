import QtQuick
import QtQuick.Dialogs
import QtQuick.Controls
import QtQuick.Layouts
import QtOllamaFrontend.QtOllamaFrontend 1.0

Dialog {
    id: dialog
    title: qsTr("Service Settings")
    standardButtons: Dialog.Close
    modal: true
    closePolicy: Popup.CloseOnEscape
    x: (appWindow.width - width) / 2
    y: (appWindow.height - height) / 2
    width: 400
    height: 400
    clip: true
    contentItem: GridLayout {
        columns: 2
        Label {
            Layout.fillWidth: true
            Layout.margins: 20
            Layout.columnSpan: parent.columns
            wrapMode: Text.WordWrap
            text: qsTr("These settings can be used if the service is configured to listen on a non-default host or port.")
        }
        // host
        CustomLabel {
            Layout.leftMargin: 10
            Layout.alignment: Qt.AlignRight
            text: qsTr("host")
        }
        CustomTextField {
            id: customTextFieldHost
            Layout.fillWidth: true
            Layout.rightMargin: 10
            text: qtOllamaFrontend.host
            onTextChanged: {
                qtOllamaFrontend.host = text;
            }
        }
        // port
        CustomLabel {
            Layout.leftMargin: 10
            Layout.alignment: Qt.AlignRight
            text: qsTr("port")
        }
        CustomTextField {
            id: customTextFieldPort
            Layout.fillWidth: true
            Layout.rightMargin: 10
            text: qtOllamaFrontend.port
            onTextChanged: {
                qtOllamaFrontend.port = text;
            }
        }
        // button
        Item {}
        CustomButton {
            Layout.topMargin: 20
            Layout.rightMargin: 10
            Layout.alignment: Qt.AlignRight
            text: qsTr("Reset Default")
            onClicked: {
                qtOllamaFrontend.resetSettings();
                customTextFieldHost.text = qtOllamaFrontend.host;
                customTextFieldPort.text = qtOllamaFrontend.port;
            }
        }
    }
}
