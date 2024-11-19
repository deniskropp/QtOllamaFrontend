import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtOllamaFrontend.QtOllamaFrontend 1.0

Dialog {
    id: dialog
    property var models: [
        {"description": "Moondream 2", "parameter_size": "1.4B", "size": "829 MB", "name": "moondream", "pulled": false},
        {"description": "Llama 3.2", "parameter_size": "3B", "size": "2.0 GB", "name": "llama3.2", "pulled": false},
        {"description": "Llama 3.2", "parameter_size": "1B", "size": "1.3 GB", "name": "llama3.2:1b", "pulled": false},
        {"description": "Llama 3.2 Vision", "parameter_size": "11B", "size": "7.9 GB", "name": "llama3.2-vision", "pulled": false},
        {"description": "Llama 3.2 Vision", "parameter_size": "90B", "size": "55 GB", "name": "llama3.2-vision:90b", "pulled": false},
        {"description": "Llama 3.1", "parameter_size": "8B", "size": "4.7 GB", "name": "llama3.1", "pulled": false},
        {"description": "Llama 3.1", "parameter_size": "70B", "size": "40 GB", "name": "llama3.1:70b", "pulled": false},
        {"description": "Llama 3.1", "parameter_size": "405B", "size": "231 GB", "name": "llama3.1:405b", "pulled": false},
        {"description": "Phi 3 Mini", "parameter_size": "3.8B", "size": "2.3 GB", "name": "phi3", "pulled": false},
        {"description": "Phi 3 Medium", "parameter_size": "14B", "size": "7.9 GB", "name": "phi3:medium", "pulled": false},
        {"description": "Gemma 2", "parameter_size": "2B", "size": "1.6 GB", "name": "gemma2:2b", "pulled": false},
        {"description": "Gemma 2", "parameter_size": "9B", "size": "5.5 GB", "name": "gemma2", "pulled": false},
        {"description": "Gemma 2", "parameter_size": "27B", "size": "16 GB", "name": "gemma2:27b", "pulled": false},
        {"description": "Mistral", "parameter_size": "7B", "size": "4.1 GB", "name": "mistral", "pulled": false},
        {"description": "Neural Chat", "parameter_size": "7B", "size": "4.1 GB", "name": "neural-chat", "pulled": false},
        {"description": "Starling", "parameter_size": "7B", "size": "4.1 GB", "name": "starling-lm", "pulled": false},
        {"description": "Code Llama", "parameter_size": "7B", "size": "3.8 GB", "name": "codellama", "pulled": false},
        {"description": "Llama 2 Uncensored", "parameter_size": "7B", "size": "3.8 GB", "name": "llama2-uncensored", "pulled": false},
        {"description": "LLaVA", "parameter_size": "7B", "size": "4.5 GB", "name": "llava", "pulled": false},
        {"description": "Solar", "parameter_size": "10.7B", "size": "6.1 GB", "name": "solar", "pulled": false}
    ]
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

        qtOllamaFrontend.getModels();
    }
    Connections {
        target: qtOllamaFrontend
        ignoreUnknownSignals: true
        function onReceivedModels(result) {
            const pulledModels = JSON.parse(result);
            const allModels = models.map((model) => model.name);

            // set the already pulled models as "pulled"
            pulledModels.models.forEach((pulledModel) => {
                const index = allModels.indexOf(pulledModel.name.split(":latest")[0]);

                if (index >= 0) {
                    models[index].pulled = true;
                }
            });

            // show already pulled models first
            models.sort((a, b) => parseInt(b.pulled ? 1 : 0) - parseInt(a.pulled ? 1 : 0));

            listViewModels.addModels(models);
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
                        "pulled": model.pulled
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
                id: itemDelegate
                width: listViewModels.width - scrollBarEntries.width
                height: itemDelegateColumn.height
                ColumnLayout {
                    id: itemDelegateColumn
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
                        Rectangle {
                            Layout.preferredWidth: 10
                            Layout.preferredHeight: 10
                            Layout.alignment: Qt.AlignVCenter
                            color: buttonPullDelete.pulled ? "lightgreen" : "transparent"
                        }
                        // pull / delete
                        CustomButton {
                            id: buttonPullDelete
                            property bool pulled: model.pulled
                            Layout.leftMargin: 10
                            Layout.rightMargin: 10
                            Layout.bottomMargin: 10
                            enabled: !qtOllamaFrontend.loading
                            text: pulled ? qsTr("Delete") : qsTr("Pull")
                            onClicked: {
                                if (pulled) {
                                    qtOllamaFrontend.deleteModel(model.name);
                                } else {
                                    qtOllamaFrontend.pullModel(model.name);
                                }
                            }
                        }
                        ProgressBar {
                            id: progressBar
                            Layout.fillWidth: true
                            Layout.leftMargin: 10
                            Layout.rightMargin: 30
                            Layout.bottomMargin: 10
                            from: 0
                            to: 100
                            value: 0
                            visible: value > 0
                        }
                    }
                    CustomLabel {
                        id: labelProgress
                        Layout.fillWidth: true
                        Layout.bottomMargin: 10
                        Layout.leftMargin: 10
                        Layout.rightMargin: 10
                        visible: progressBar.value > 0
                    }
                }
                Connections {
                    target: qtOllamaFrontend
                    ignoreUnknownSignals: true
                    function onReceivedPullModelProgress(modelName, status, bytesReceived, bytesTotal) {
                        if (model.name === modelName) {
                            var percentage = parseInt((parseFloat(bytesReceived) / parseFloat(bytesTotal)) * 100.0);
                            progressBar.value = percentage;
                            labelProgress.text = qsTr("%1: %2 %, %3 / %4").arg(status).arg(percentage).arg(listViewModels.getPrettyPrintedSize(bytesReceived)).arg(listViewModels.getPrettyPrintedSize(bytesTotal));
                        }
                    }
                    function onReceivedPullModel(result) {
                        result = JSON.parse(result);

                        if (result.model == model.name) {
                            if (result.success) {
                                buttonPullDelete.pulled = true;
                            }

                            progressBar.value = 0;
                        }
                    }
                    function onReceivedDeleteModel(result) {
                        result = JSON.parse(result);

                        if (result.model == model.name) {
                            if (result.success) {
                                buttonPullDelete.pulled = false;
                            }
                        }
                    }
                }
            }
        }
    }
}
