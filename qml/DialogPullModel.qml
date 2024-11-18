import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtOllamaFrontend.QtOllamaFrontend 1.0

Dialog {
    id: dialog
    property var models: [
        {"description": "Llama 3.2", "parameter_size": "3B", "size": "2.0 GB", "name": "llama3.2"},
        {"description": "Llama 3.2", "parameter_size": "1B", "size": "1.3 GB", "name": "llama3.2:1b"},
        {"description": "Llama 3.2 Vision", "parameter_size": "11B", "size": "7.9 GB", "name": "llama3.2-vision"},
        {"description": "Llama 3.2 Vision", "parameter_size": "90B", "size": "55 GB", "name": "llama3.2-vision:90b"},
        {"description": "Llama 3.1", "parameter_size": "8B", "size": "4.7 GB", "name": "llama3.1"},
        {"description": "Llama 3.1", "parameter_size": "70B", "size": "40 GB", "name": "llama3.1:70b"},
        {"description": "Llama 3.1", "parameter_size": "405B", "size": "231 GB", "name": "llama3.1:405b"},
        {"description": "Phi 3 Mini", "parameter_size": "3.8B", "size": "2.3 GB", "name": "phi3"},
        {"description": "Phi 3 Medium", "parameter_size": "14B", "size": "7.9 GB", "name": "phi3:medium"},
        {"description": "Gemma 2", "parameter_size": "2B", "size": "1.6 GB", "name": "gemma2:2b"},
        {"description": "Gemma 2", "parameter_size": "9B", "size": "5.5 GB", "name": "gemma2"},
        {"description": "Gemma 2", "parameter_size": "27B", "size": "16 GB", "name": "gemma2:27b"},
        {"description": "Mistral", "parameter_size": "7B", "size": "4.1 GB", "name": "mistral"},
        {"description": "Moondream 2", "parameter_size": "1.4B", "size": "829 MB", "name": "moondream"},
        {"description": "Neural Chat", "parameter_size": "7B", "size": "4.1 GB", "name": "neural-chat"},
        {"description": "Starling", "parameter_size": "7B", "size": "4.1 GB", "name": "starling-lm"},
        {"description": "Code Llama", "parameter_size": "7B", "size": "3.8 GB", "name": "codellama"},
        {"description": "Llama 2 Uncensored", "parameter_size": "7B", "size": "3.8 GB", "name": "llama2-uncensored"},
        {"description": "LLaVA", "parameter_size": "7B", "size": "4.5 GB", "name": "llava"},
        {"description": "Solar", "parameter_size": "10.7B", "size": "6.1 GB", "name": "solar"}
    ]
    property int pullingModelIndex: -1
    title: qsTr("Pull Model")
    standardButtons: Dialog.Close
    modal: true
    closePolicy: Popup.CloseOnEscape
    x: (appWindow.width - width) / 2
    y: (appWindow.height - height) / 2
    width: 500
    height: 500
    clip: true
    onVisibleChanged: {
        if (!visible) {
            return;
        }

        listViewModels.addModels(models);
    }
    Connections {
        target: qtOllamaFrontend
        ignoreUnknownSignals: true
        function onReceivedDownloadProgress(bytesReceived, bytesTotal) {
            //console.log("bytes downloaded:", bytesReceived + " / " + bytesTotal);

            listModelModels.set(pullingModelIndex, {
                "downloadedBytes": listViewModels.getPrettyPrintedSize(bytesReceived)
            });
        }
    }
    contentItem: ColumnLayout {
        width: parent.width
        ListView {
            id: listViewModels
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.topMargin: 10
            Layout.bottomMargin: 10
            Layout.leftMargin: 10
            Layout.rightMargin: 10
            function addModels(models) {
                listModelModels.clear();

                models.forEach((model) => {
                    listModelModels.append({
                        "description": model.description,
                        "name": model.name,
                        "size": model.size,
                        "parameterSize": model.parameter_size,
                        "downloadedBytes": ""
                    });
                });
            }
            function roundNumber(number) {
                return (Math.round(parseFloat(number) * 100.0) / 100.0).toFixed(2);
            }
            function getPrettyPrintedSize(size) {
                var output = "";

                if (size >= 1024*1024*1024*1024) {
                    var size_tb = parseFloat(size) / parseFloat(1024*1024*1024*1024);
                    output = roundNumber(size_tb) + " TB";
                } else if (size >= 1024*1024*1024) {
                    var size_gb = parseFloat(size) / parseFloat(1024*1024*1024);
                    output = roundNumber(size_gb) + " GB";
                } else if (size >= 1024*1024) {
                    var size_mb = parseFloat(size) / parseFloat(1024*1024);
                    output = roundNumber(size_mb) + " MB";
                } else if (size >= 1024) {
                    var size_kb = parseFloat(size) / parseFloat(1024);
                    output = roundNumber(size_kb) + " kB";
                } else {
                    var size_b = parseFloat(size);
                    output = roundNumber(size_b)  + " B";
                }

                return output;
            }
            ScrollBar.vertical: ScrollBar {
                id: scrollBarEntries
                width: 10
                anchors.top: parent.top
                anchors.right: parent.right
                anchors.bottom: parent.bottom
            }
            model: ListModel {
                id: listModelModels
            }
            delegate: ItemDelegate {
                id: item
                width: listViewModels.width - scrollBarEntries.width
                height: itemDelegateRow.height
                Rectangle {
                    id: itemDelegateRow
                    width: parent.width
                    height: itemDelegateColumnLayout.height
                    ColumnLayout {
                        id: itemDelegateColumnLayout
                        width: parent.width
                        RowLayout {
                            Layout.fillWidth: true
                            CustomLabel {
                                Layout.fillWidth: true
                                Layout.topMargin: 10
                                wrapMode: Text.WordWrap
                                text: model.description + "  (" + model.name + ")"
                            }
                            CustomLabel {
                                Layout.preferredWidth: 0.2 * parent.width
                                Layout.topMargin: 10
                                text: model.parameterSize
                            }
                            CustomLabel {
                                Layout.preferredWidth: 0.2 * parent.width
                                Layout.topMargin: 10
                                Layout.alignment: Qt.AlignRight
                                text: model.size
                            }
                        }
                        RowLayout {
                            Layout.fillWidth: true
                            // select
                            CustomButton {
                                Layout.leftMargin: 10
                                Layout.bottomMargin: 10
                                enabled: !qtOllamaFrontend.loading
                                text: qsTr("Pull")
                                onClicked: {
                                    pullingModelIndex = model.index;

                                    qtOllamaFrontend.pullModel(model.name);
                                }
                            }
                            CustomLabel {
                                Layout.fillWidth: true
                                Layout.leftMargin: 10
                                text: model.downloadedBytes
                            }
                        }
                    }
                }
            }
        }
    }
}
