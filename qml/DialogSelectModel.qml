import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtOllamaFrontend.QtOllamaFrontend 1.0

Dialog {
    id: dialog
    title: qsTr("Model")
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
    Timer {
        interval: 1500
        repeat: true
        running: parent.visible
        triggeredOnStart: false
        onTriggered: {
            if (!qtOllamaFrontend.loading) {
                qtOllamaFrontend.getLoadedModels();
            }
        }
    }
    Connections {
        target: qtOllamaFrontend
        ignoreUnknownSignals: true
        function onReceivedModels(result) {
            const models = JSON.parse(result);

            listViewModels.addModels(models);
        }
        function onReceivedLoadedModels(result) {
            const models = JSON.parse(result);

            listViewModels.setLoadedModels(models);
        }
        function onReceivedLoadedModel(result) {
            var json = JSON.parse(result);

            if (json.done && (json.done_reason == "load")) {
                for (var i = 0; i < listModelModels.count; i++) {
                    var model = listModelModels.get(i);

                    if (model.name == json.model) {
                        listModelModels.set(i, {
                            "loaded": true
                        });
                    }
                }
            }
        }
        function onReceivedUnloadedModel(result) {
            var json = JSON.parse(result);

            if (json.done && (json.done_reason == "unload")) {
                for (var i = 0; i < listModelModels.count; i++) {
                    var model = listModelModels.get(i);

                    if (model.name == json.model) {
                        listModelModels.set(i, {
                            "loaded": false
                        });
                    }
                }
            }
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

                if (models.models) {
                    models.models.forEach((model) => {
                        listModelModels.append({
                            "name": model.name,
                            "size": getPrettyPrintedSize(model.size),
                            "parameterSize": model.details.parameter_size,
                            "checked": qtOllamaFrontend.modelName == model.name,
                            "loaded": false
                        });
                    });
                }
            }
            function setLoadedModels(models) {
                if (models.models) {
                    var loadedModels = models.models.map((model) => model.name);

                    var modelNames = [];
                    for (var i = 0; i < listModelModels.count; i++) {
                        var model = listModelModels.get(i);

                        modelNames.push(model.name);

                        listModelModels.set(i, {
                            "loaded": false
                        });
                    }

                    loadedModels.forEach((loadedModel) => {
                        var index = modelNames.indexOf(loadedModel);

                        if (index >= 0) {
                            listModelModels.set(index, {
                                "loaded": true
                            });
                        }
                    });
                }
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
                property bool loaded: model.loaded
                id: item
                width: listViewModels.width - scrollBarEntries.width
                height: itemDelegateRow.height
                checked: model.checked
                Rectangle {
                    id: itemDelegateRow
                    width: parent.width
                    height: itemDelegateColumnLayout.height
                    color: checked ? "#cccccc" : "#ffffff";
                    ColumnLayout {
                        id: itemDelegateColumnLayout
                        width: parent.width
                        RowLayout {
                            Layout.fillWidth: true
                            CustomLabel {
                                Layout.fillWidth: true
                                Layout.topMargin: 10
                                text: model.name
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
                                text: qsTr("Select")
                                onClicked: {
                                    qtOllamaFrontend.modelName = model.name;

                                    for (var i = 0; i < listModelModels.count; i++) {
                                        var entry = listModelModels.get(i);

                                        listModelModels.set(i, {
                                            "checked": entry.name == model.name
                                        });
                                    }
                                }
                            }
                            // load / unload
                            CustomButton {
                                Layout.leftMargin: 10
                                Layout.bottomMargin: 10
                                enabled: !qtOllamaFrontend.loading
                                text: item.loaded ? qsTr("UnLoad") : qsTr("Load")
                                onClicked: {
                                    if (item.loaded) {
                                        qtOllamaFrontend.unloadModel(model.name);
                                    } else {
                                        qtOllamaFrontend.loadModel(model.name);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
