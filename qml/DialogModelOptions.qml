import QtQuick
import QtQuick.Dialogs
import QtQuick.Controls
import QtQuick.Layouts
import QtOllamaFrontend.QtOllamaFrontend 1.0

Dialog {
    id: dialog
    title: qsTr("")
    standardButtons: Dialog.Close
    modal: true
    closePolicy: Popup.CloseOnEscape
    x: (appWindow.width - width) / 2
    y: (appWindow.height - height) / 2
    width: 700
    height: 600
    clip: true
    contentItem: ScrollView {
        ScrollBar.horizontal.visible: false
        smooth: true
        GridLayout {
            width: dialog.width - 30
            columns: 4
            columnSpacing: 0
            rowSpacing: 20
            Label {
                Layout.columnSpan: parent.columns
                Layout.fillWidth: true
                Layout.margins: 10
                wrapMode: Text.WordWrap
                text: qsTr("With these settings you can change the model parameters at runtime if you do not want to change the model file. All checked parameters are applied.")
            }
            // ssed
            CustomCheckBoxTextFieldInteger {
                Layout.fillWidth: true
                Layout.leftMargin: 10
                Layout.rightMargin: 10
                labelText: qsTr("seed")
                checked: qtOllamaFrontend.seedApplied
                onCheckedChanged: qtOllamaFrontend.seedApplied = checked
                text: qtOllamaFrontend.seed
                onTextChanged: qtOllamaFrontend.seed = parseInt(text)
            }
            // num_keep
            CustomCheckBoxTextFieldInteger {
                Layout.fillWidth: true
                Layout.leftMargin: 10
                Layout.rightMargin: 10
                labelText: qsTr("num_keep")
                checked: qtOllamaFrontend.numKeepApplied
                onCheckedChanged: qtOllamaFrontend.numKeepApplied = checked
                text: qtOllamaFrontend.numKeep
                onTextChanged: qtOllamaFrontend.numKeep = parseInt(text)
            }
            // num_predict
            CustomCheckBoxTextFieldInteger {
                Layout.fillWidth: true
                Layout.leftMargin: 10
                Layout.rightMargin: 10
                labelText: qsTr("num_predict")
                checked: qtOllamaFrontend.numPredictApplied
                onCheckedChanged: qtOllamaFrontend.numPredictApplied = checked
                text: qtOllamaFrontend.numPredict
                onTextChanged: qtOllamaFrontend.numPredict = parseInt(text)
            }
            // top_k
            CustomCheckBoxTextFieldInteger {
                Layout.fillWidth: true
                Layout.leftMargin: 10
                Layout.rightMargin: 10
                labelText: qsTr("top_k")
                checked: qtOllamaFrontend.topKApplied
                onCheckedChanged: qtOllamaFrontend.topKApplied = checked
                text: qtOllamaFrontend.topK
                onTextChanged: qtOllamaFrontend.topK = parseInt(text)
            }
            // top_p
            CustomCheckBoxTextFieldDouble {
                Layout.fillWidth: true
                Layout.leftMargin: 10
                Layout.rightMargin: 10
                labelText: qsTr("top_p")
                checked: qtOllamaFrontend.topPApplied
                onCheckedChanged: qtOllamaFrontend.topPApplied = checked
                text: qtOllamaFrontend.topP
                onTextChanged: qtOllamaFrontend.topP = parseFloat(text)
            }
            // min_p
            CustomCheckBoxTextFieldDouble {
                Layout.fillWidth: true
                Layout.leftMargin: 10
                Layout.rightMargin: 10
                labelText: qsTr("min_p")
                checked: qtOllamaFrontend.minPApplied
                onCheckedChanged: qtOllamaFrontend.minPApplied = checked
                text: qtOllamaFrontend.minP
                onTextChanged: qtOllamaFrontend.minP = parseFloat(text)
            }
            // tfs_z
            CustomCheckBoxTextFieldDouble {
                Layout.fillWidth: true
                Layout.leftMargin: 10
                Layout.rightMargin: 10
                labelText: qsTr("tfs_z")
                checked: qtOllamaFrontend.tfsZApplied
                onCheckedChanged: qtOllamaFrontend.tfsZApplied = checked
                text: qtOllamaFrontend.tfsZ
                onTextChanged: qtOllamaFrontend.tfsZ = parseFloat(text)
            }
            // typical_p
            CustomCheckBoxTextFieldDouble {
                Layout.fillWidth: true
                Layout.leftMargin: 10
                Layout.rightMargin: 10
                labelText: qsTr("typical_p")
                checked: qtOllamaFrontend.typicalPApplied
                onCheckedChanged: qtOllamaFrontend.typicalPApplied = checked
                text: qtOllamaFrontend.typicalP
                onTextChanged: qtOllamaFrontend.typicalP = parseFloat(text)
            }
            // repeat_last_n
            CustomCheckBoxTextFieldInteger {
                Layout.fillWidth: true
                Layout.leftMargin: 10
                Layout.rightMargin: 10
                labelText: qsTr("repeat_last_n")
                checked: qtOllamaFrontend.repeatLastNApplied
                onCheckedChanged: qtOllamaFrontend.repeatLastNApplied = checked
                text: qtOllamaFrontend.repeatLastN
                onTextChanged: qtOllamaFrontend.repeatLastN = parseInt(text)
            }
            // temperature
            CustomCheckBoxTextFieldDouble {
                Layout.fillWidth: true
                Layout.leftMargin: 10
                Layout.rightMargin: 10
                labelText: qsTr("temperature")
                checked: qtOllamaFrontend.temperatureApplied
                onCheckedChanged: qtOllamaFrontend.temperatureApplied = checked
                text: qtOllamaFrontend.temperature
                onTextChanged: qtOllamaFrontend.temperature = parseFloat(text)
            }
            // repeat_penalty
            CustomCheckBoxTextFieldDouble {
                Layout.fillWidth: true
                Layout.leftMargin: 10
                Layout.rightMargin: 10
                labelText: qsTr("repeat_penalty")
                checked: qtOllamaFrontend.repeatPenaltyApplied
                onCheckedChanged: qtOllamaFrontend.repeatPenaltyApplied = checked
                text: qtOllamaFrontend.repeatPenalty
                onTextChanged: qtOllamaFrontend.repeatPenalty = parseFloat(text)
            }
            // presence_penalty
            CustomCheckBoxTextFieldDouble {
                Layout.fillWidth: true
                Layout.leftMargin: 10
                Layout.rightMargin: 10
                labelText: qsTr("presence_penalty")
                checked: qtOllamaFrontend.presencePenaltyApplied
                onCheckedChanged: qtOllamaFrontend.presencePenaltyApplied = checked
                text: qtOllamaFrontend.presencePenalty
                onTextChanged: qtOllamaFrontend.presencePenalty = parseFloat(text)
            }
            // frequency_penalty
            CustomCheckBoxTextFieldDouble {
                Layout.fillWidth: true
                Layout.leftMargin: 10
                Layout.rightMargin: 10
                labelText: qsTr("frequency_penalty")
                checked: qtOllamaFrontend.frequencyPenaltyApplied
                onCheckedChanged: qtOllamaFrontend.frequencyPenaltyApplied = checked
                text: qtOllamaFrontend.frequencyPenalty
                onTextChanged: qtOllamaFrontend.frequencyPenalty = parseFloat(text)
            }
            // mirostat
            CustomCheckBoxTextFieldInteger {
                Layout.fillWidth: true
                Layout.leftMargin: 10
                Layout.rightMargin: 10
                labelText: qsTr("mirostat")
                checked: qtOllamaFrontend.mirostatApplied
                onCheckedChanged: qtOllamaFrontend.mirostatApplied = checked
                text: qtOllamaFrontend.mirostat
                onTextChanged: qtOllamaFrontend.mirostat = parseInt(text)
            }
            // mirostat_tau
            CustomCheckBoxTextFieldDouble {
                Layout.fillWidth: true
                Layout.leftMargin: 10
                Layout.rightMargin: 10
                labelText: qsTr("mirostat_tau")
                checked: qtOllamaFrontend.mirostatTauApplied
                onCheckedChanged: qtOllamaFrontend.mirostatTauApplied = checked
                text: qtOllamaFrontend.mirostatTau
                onTextChanged: qtOllamaFrontend.mirostatTau = parseFloat(text)
            }
            // mirostat_eta
            CustomCheckBoxTextFieldDouble {
                Layout.fillWidth: true
                Layout.leftMargin: 10
                Layout.rightMargin: 10
                labelText: qsTr("mirostat_eta")
                checked: qtOllamaFrontend.mirostatEtaApplied
                onCheckedChanged: qtOllamaFrontend.mirostatEtaApplied = checked
                text: qtOllamaFrontend.mirostatEta
                onTextChanged: qtOllamaFrontend.mirostatEta = parseFloat(text)
            }
            // penalize_newline
            CustomCheckBoxTextFieldBoolean {
                Layout.fillWidth: true
                Layout.leftMargin: 10
                Layout.rightMargin: 10
                labelText: qsTr("penalize_newline")
                checked: qtOllamaFrontend.penalizeNewlineApplied
                onCheckedChanged: qtOllamaFrontend.penalizeNewlineApplied = checked
                switchChecked: qtOllamaFrontend.penalizeNewline
                onSwitchCheckedChanged: qtOllamaFrontend.penalizeNewline = switchChecked
            }
            // stop
            CustomCheckBoxTextField {
                Layout.fillWidth: true
                Layout.leftMargin: 10
                Layout.rightMargin: 10
                labelText: qsTr("stop")
                checked: qtOllamaFrontend.stopApplied
                onCheckedChanged: qtOllamaFrontend.stopApplied = checked
                text: qtOllamaFrontend.stop
                onTextChanged: qtOllamaFrontend.stop = text
            }
            // numa
            CustomCheckBoxTextFieldBoolean {
                Layout.fillWidth: true
                Layout.leftMargin: 10
                Layout.rightMargin: 10
                labelText: qsTr("numa")
                checked: qtOllamaFrontend.numaApplied
                onCheckedChanged: qtOllamaFrontend.numaApplied = checked
                switchChecked: qtOllamaFrontend.numa
                onSwitchCheckedChanged: qtOllamaFrontend.numa = switchChecked
            }
            // num_ctx
            CustomCheckBoxTextFieldInteger {
                Layout.fillWidth: true
                Layout.leftMargin: 10
                Layout.rightMargin: 10
                labelText: qsTr("num_ctx")
                checked: qtOllamaFrontend.numCtxApplied
                onCheckedChanged: qtOllamaFrontend.numCtxApplied = checked
                text: qtOllamaFrontend.numCtx
                onTextChanged: qtOllamaFrontend.numCtx = parseInt(text)
            }
            // num_batch
            CustomCheckBoxTextFieldInteger {
                Layout.fillWidth: true
                Layout.leftMargin: 10
                Layout.rightMargin: 10
                labelText: qsTr("num_batch")
                checked: qtOllamaFrontend.numBatchApplied
                onCheckedChanged: qtOllamaFrontend.numBatchApplied = checked
                text: qtOllamaFrontend.numBatch
                onTextChanged: qtOllamaFrontend.numBatch = parseInt(text)
            }
            // num_gpu
            CustomCheckBoxTextFieldInteger {
                Layout.fillWidth: true
                Layout.leftMargin: 10
                Layout.rightMargin: 10
                labelText: qsTr("num_gpu")
                checked: qtOllamaFrontend.numGpuApplied
                onCheckedChanged: qtOllamaFrontend.numGpuApplied = checked
                text: qtOllamaFrontend.numGpu
                onTextChanged: qtOllamaFrontend.numGpu = parseInt(text)
            }
            // main_gpu
            CustomCheckBoxTextFieldInteger {
                Layout.fillWidth: true
                Layout.leftMargin: 10
                Layout.rightMargin: 10
                labelText: qsTr("main_gpu")
                checked: qtOllamaFrontend.mainGpuApplied
                onCheckedChanged: qtOllamaFrontend.mainGpuApplied = checked
                text: qtOllamaFrontend.mainGpu
                onTextChanged: qtOllamaFrontend.mainGpu = parseInt(text)
            }
            // low_vram
            CustomCheckBoxTextFieldBoolean {
                Layout.fillWidth: true
                Layout.leftMargin: 10
                Layout.rightMargin: 10
                labelText: qsTr("low_vram")
                checked: qtOllamaFrontend.lowVramApplied
                onCheckedChanged: qtOllamaFrontend.lowVramApplied = checked
                switchChecked: qtOllamaFrontend.lowVram
                onSwitchCheckedChanged: qtOllamaFrontend.lowVram = switchChecked
            }
            // vocab_only
            CustomCheckBoxTextFieldBoolean {
                Layout.fillWidth: true
                Layout.leftMargin: 10
                Layout.rightMargin: 10
                labelText: qsTr("vocab_only")
                checked: qtOllamaFrontend.vocabOnlyApplied
                onCheckedChanged: qtOllamaFrontend.vocabOnlyApplied = checked
                switchChecked: qtOllamaFrontend.vocabOnly
                onSwitchCheckedChanged: qtOllamaFrontend.vocabOnly = switchChecked
            }
            // use_mmap
            CustomCheckBoxTextFieldBoolean {
                Layout.fillWidth: true
                Layout.leftMargin: 10
                Layout.rightMargin: 10
                labelText: qsTr("use_mmap")
                checked: qtOllamaFrontend.useMmapApplied
                onCheckedChanged: qtOllamaFrontend.useMmapApplied = checked
                switchChecked: qtOllamaFrontend.useMmap
                onSwitchCheckedChanged: qtOllamaFrontend.useMmap = switchChecked
            }
            // use_mlock
            CustomCheckBoxTextFieldBoolean {
                Layout.fillWidth: true
                Layout.leftMargin: 10
                Layout.rightMargin: 10
                labelText: qsTr("use_mlock")
                checked: qtOllamaFrontend.useMlockApplied
                onCheckedChanged: qtOllamaFrontend.useMlockApplied = checked
                switchChecked: qtOllamaFrontend.useMlock
                onSwitchCheckedChanged: qtOllamaFrontend.useMlock = switchChecked
            }
            // num_thread
            CustomCheckBoxTextFieldInteger {
                Layout.fillWidth: true
                Layout.leftMargin: 10
                Layout.rightMargin: 10
                labelText: qsTr("num_thread")
                checked: qtOllamaFrontend.numThreadApplied
                onCheckedChanged: qtOllamaFrontend.numThreadApplied = checked
                text: qtOllamaFrontend.numThread
                onTextChanged: qtOllamaFrontend.numThread = parseInt(text)
            }

            // button
            CustomButton {
                Layout.columnSpan: parent.columns
                Layout.topMargin: 20
                Layout.rightMargin: 10
                Layout.alignment: Qt.AlignHCenter
                text: qsTr("Reset Default")
                onClicked: {
                    qtOllamaFrontend.resetSettings([
                        QtOllamaFrontend.Seed,
                        QtOllamaFrontend.NumKeep,
                        QtOllamaFrontend.NumPredict,
                        QtOllamaFrontend.TopK,
                        QtOllamaFrontend.TopP,
                        QtOllamaFrontend.MinP,
                        QtOllamaFrontend.TfsZ,
                        QtOllamaFrontend.TypicalP,
                        QtOllamaFrontend.RepeatLastN,
                        QtOllamaFrontend.Temperature,
                        QtOllamaFrontend.RepeatPenalty,
                        QtOllamaFrontend.PresencePenalty,
                        QtOllamaFrontend.FrequencyPenalty,
                        QtOllamaFrontend.Mirostat,
                        QtOllamaFrontend.MirostatTau,
                        QtOllamaFrontend.MirostatEta,
                        QtOllamaFrontend.PenalizeNewline,
                        QtOllamaFrontend.Stop,
                        QtOllamaFrontend.Numa,
                        QtOllamaFrontend.NumCtx,
                        QtOllamaFrontend.NumBatch,
                        QtOllamaFrontend.NumGpu,
                        QtOllamaFrontend.MainGpu,
                        QtOllamaFrontend.LowVram,
                        QtOllamaFrontend.VocabOnly,
                        QtOllamaFrontend.UseMmap,
                        QtOllamaFrontend.UseMlock,
                        QtOllamaFrontend.NumThread,
                        QtOllamaFrontend.SeedApplied,
                        QtOllamaFrontend.NumKeepApplied,
                        QtOllamaFrontend.NumPredictApplied,
                        QtOllamaFrontend.TopKApplied,
                        QtOllamaFrontend.TopPApplied,
                        QtOllamaFrontend.MinPApplied,
                        QtOllamaFrontend.TfsZApplied,
                        QtOllamaFrontend.TypicalPApplied,
                        QtOllamaFrontend.RepeatLastNApplied,
                        QtOllamaFrontend.TemperatureApplied,
                        QtOllamaFrontend.RepeatPenaltyApplied,
                        QtOllamaFrontend.PresencePenaltyApplied,
                        QtOllamaFrontend.FrequencyPenaltyApplied,
                        QtOllamaFrontend.MirostatApplied,
                        QtOllamaFrontend.MirostatTauApplied,
                        QtOllamaFrontend.MirostatEtaApplied,
                        QtOllamaFrontend.PenalizeNewlineApplied,
                        QtOllamaFrontend.StopApplied,
                        QtOllamaFrontend.NumaApplied,
                        QtOllamaFrontend.NumCtxApplied,
                        QtOllamaFrontend.NumBatchApplied,
                        QtOllamaFrontend.NumGpuApplied,
                        QtOllamaFrontend.MainGpuApplied,
                        QtOllamaFrontend.LowVramApplied,
                        QtOllamaFrontend.VocabOnlyApplied,
                        QtOllamaFrontend.UseMmapApplied,
                        QtOllamaFrontend.UseMlockApplied,
                        QtOllamaFrontend.NumThreadApplied
                    ]);
                }
            }
        }
    }
}
