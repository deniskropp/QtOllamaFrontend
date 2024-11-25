import QtQuick
import QtQuick.Dialogs
import QtQuick.Controls
import QtQuick.Layouts
import QtOllamaFrontend.QtOllamaFrontend 1.0

Dialog {
    id: dialog
    title: qsTr("New Chat")
    standardButtons: Dialog.Yes|Dialog.No
    modal: true
    closePolicy: Popup.CloseOnEscape
    x: (appWindow.width - width) / 2
    y: (appWindow.height - height) / 2
    width: 400
    height: 150
    clip: true
    contentItem: ColumnLayout {
        Label {
            Layout.fillWidth: true
            Layout.leftMargin: 20
            Layout.rightMargin: 20
            wrapMode: Text.WordWrap
            text: qsTr("If you start a new chat, the previous history will be lost.\nContinue anyway?")
        }
    }
}
