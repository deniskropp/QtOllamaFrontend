import QtCore
import QtQuick
import QtQuick.Dialogs
import QtQuick.Controls
import QtQuick.Layouts
import QtOllamaFrontend.QtOllamaFrontend 1.0

Dialog {
    id: dialog
    property string messageText: ""
    property var images: []
    title: qsTr("Send a Message with Images")
    standardButtons: Dialog.Close
    modal: true
    closePolicy: Popup.CloseOnEscape
    x: (appWindow.width - width) / 2
    y: (appWindow.height - height) / 2
    width: 500
    height: 500
    clip: true
    FileDialog {
        id: fileDialog
        fileMode: FileDialog.OpenFiles
        currentFolder: StandardPaths.standardLocations(StandardPaths.PicturesLocation)[0]
        nameFilters: ["JPEG (*.jpeg *.jpg)", "PNG (*.png)"]
        onAccepted: {
            var imagePaths = [];

            for (var i = 0; i < selectedFiles.length > 0; i++) {
                imagePaths.push(selectedFiles[i]);
            }

            listViewImages.processImagePaths(imagePaths);
        }
    }
    contentItem: ColumnLayout {
        ListView {
            id: listViewImages
            Layout.fillWidth: true
            Layout.fillHeight: true
            function processImagePaths(imagePaths) {
                imagePaths.forEach((imagePath) => {
                    listModelImages.append({
                        "imagePath": imagePath,
                    });
                });
            }
            ScrollBar.vertical: ScrollBar {
                id: scrollBarEntries
                width: 25
                anchors.top: parent.top
                anchors.right: parent.right
                anchors.bottom: parent.bottom
            }
            model: ListModel {
                id: listModelImages
            }
            header: CustomLabel {
                width: listViewImages.width
                text: qsTr("Write a message and attach images to the message.")
            }
            footer: ColumnLayout {
                width: listViewImages.width - scrollBarEntries.width
                RowLayout {
                    Layout.fillWidth: true
                    BusyIndicator {
                        id: busyIndicator
                        Layout.topMargin: 10
                        Layout.bottomMargin: 10
                        running: qtOllamaFrontend.loading
                    }
                    CustomButton {
                        Layout.topMargin: 10
                        Layout.bottomMargin: 10
                        Layout.leftMargin: 10
                        Layout.rightMargin: 10
                        text: qsTr("Add Image")
                        onClicked: {
                            fileDialog.open();
                        }
                    }
                    CustomButton {
                        Layout.topMargin: 10
                        Layout.bottomMargin: 10
                        Layout.leftMargin: 10
                        Layout.rightMargin: 10
                        text: qsTr("Send Message")
                        onClicked: {
                            var imagePaths = [];

                            for (var i = 0; i < listModelImages.count; i++) {
                                var image = listModelImages.get(i);

                                imagePaths.push(image.imagePath);
                            }

                            messageText = textArea.text;
                            images = JSON.stringify(imagePaths);

                            dialog.accept();
                        }
                    }
                }
                CustomTextArea {
                    id: textArea
                    Layout.fillWidth: true
                    Layout.preferredHeight: 100
                    Layout.topMargin: 10
                    Layout.bottomMargin: 10
                    Layout.leftMargin: 10
                    Layout.rightMargin: 10
                    placeholderText: qsTr("Message Text")
                }
            }
            delegate: ItemDelegate {
                id: item
                width: listViewImages.width - scrollBarEntries.width
                height: itemDelegateRow.height
                RowLayout {
                    id: itemDelegateRow
                    width: parent.width
                    Image {
                        Layout.topMargin: 10
                        Layout.bottomMargin: 10
                        Layout.leftMargin: 10
                        Layout.rightMargin: 10
                        fillMode: Image.PreserveAspectFit
                        antialiasing: true
                        smooth: true
                        sourceSize.width: 50
                        sourceSize.height: 50
                        source: model.imagePath
                    }
                    CustomButton {
                        Layout.topMargin: 10
                        Layout.bottomMargin: 10
                        Layout.leftMargin: 10
                        Layout.rightMargin: 10
                        text: qsTr("Remove")
                        onClicked: {
                            listModelImages.remove(model.index);
                        }
                    }
                    Item {
                        Layout.fillWidth: true
                    }
                }
            }
        }
    }
}
