import QtQuick
import QtQuick.Dialogs
import QtQuick.Controls
import QtQuick.Layouts
import QtOllamaFrontend.QtOllamaFrontend 1.0

Dialog {
    id: dialog
    property alias modelName: customTextFieldName.text
    property alias modelDescription: customTextFieldDescription.text
    property alias modelParameterSize: customTextFieldParameterSize.text
    property alias modelSize: customTextFieldSize.text
    title: qsTr("Add Model")
    standardButtons: Dialog.Cancel|Dialog.Save
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
            text: qsTr("Add a model found in the Ollama model library.")
        }
        // name
        CustomLabel {
            Layout.leftMargin: 10
            Layout.alignment: Qt.AlignRight
            text: qsTr("name")
        }
        CustomTextField {
            id: customTextFieldName
            Layout.fillWidth: true
            Layout.rightMargin: 10
        }
        // description
        CustomLabel {
            Layout.leftMargin: 10
            Layout.alignment: Qt.AlignRight
            text: qsTr("description")
        }
        CustomTextField {
            id: customTextFieldDescription
            Layout.fillWidth: true
            Layout.rightMargin: 10
        }
        // parameter size
        CustomLabel {
            Layout.leftMargin: 10
            Layout.alignment: Qt.AlignRight
            text: qsTr("parameter size")
        }
        CustomTextField {
            id: customTextFieldParameterSize
            Layout.fillWidth: true
            Layout.rightMargin: 10
        }
        // size
        CustomLabel {
            Layout.leftMargin: 10
            Layout.alignment: Qt.AlignRight
            text: qsTr("size")
        }
        CustomTextField {
            id: customTextFieldSize
            Layout.fillWidth: true
            Layout.rightMargin: 10
        }
    }
}
