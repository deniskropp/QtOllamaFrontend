import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtOllamaFrontend.QtOllamaFrontend 1.0

Dialog {
    id: dialog
    title: qsTr("Model Settings")
    standardButtons: Dialog.Close
    modal: true
    closePolicy: Popup.CloseOnEscape
    x: (appWindow.width - width) / 2
    y: (appWindow.height - height) / 2
    width: 700
    height: 300
    clip: true
    contentItem: GridLayout {
        columns: 3
        // seed
        Item {}
        CustomCheckBoxTextFieldInteger {
            Layout.margins: 10
            labelText: qsTr("seed")
            checked: qtOllamaFrontend.seedApplied
            onCheckedChanged: qtOllamaFrontend.seedApplied = checked
            text: qtOllamaFrontend.seed
            onTextChanged: qtOllamaFrontend.seed = parseInt(text)
        }
        CustomLabel {
            Layout.fillWidth: true
            Layout.margins: 10
            wrapMode: Text.WordWrap
            text: qsTr("Specify a seed greater than 0 if you need reproducible outputs.")
        }
        // scale image
        // scaled image width
        CustomLabel {
            Layout.margins: 10
            Layout.alignment: Qt.AlignRight
            text: qsTr("scaled image width")
        }
        CustomTextField {
            Layout.margins: 10
            validator: RegularExpressionValidator {
                regularExpression: /^[0-9]+$/
            }
            text: qtOllamaFrontend.scaledImageWidth
            onTextChanged: {
                qtOllamaFrontend.scaledImageWidth = parseInt(text);
            }
        }
        CustomLabel {
            Layout.fillWidth: true
            Layout.margins: 10
            Layout.rowSpan: 2
            wrapMode: Text.WordWrap
            text: qsTr("The images are scaled to the specified size keeping the aspect ratio just before they are uploaded to the assistant. If the width or height is 0, the images are not scaled. The smaller the images, the faster is the upload.")
        }
        // scaled image height
        CustomLabel {
            Layout.margins: 10
            Layout.alignment: Qt.AlignRight
            text: qsTr("scaled image height")
        }
        CustomTextField {
            Layout.margins: 10
            validator: RegularExpressionValidator {
                regularExpression: /^[0-9]+$/
            }
            text: qtOllamaFrontend.scaledImageHeight
            onTextChanged: {
                qtOllamaFrontend.scaledImageHeight = parseInt(text);
            }
        }
        // spacer
        Item {
            Layout.fillWidth: true
            Layout.fillHeight: true
        }
    }
}
