import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtOllamaFrontend.QtOllamaFrontend 1.0

Dialog {
    id: dialog
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
            var modelsFromDb = qtOllamaFrontend.getModelsFromDb();
            var models = [];
            modelsFromDb.forEach((modelFromDb) => {
                models.push({
                    "name": modelFromDb.name,
                    "description": modelFromDb.description,
                    "parameter_size": modelFromDb.parameter_size,
                    "size": modelFromDb.size,
                    "pulled": false
                });
            });

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
