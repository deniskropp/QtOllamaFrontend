import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtOllamaFrontend.QtOllamaFrontend 1.0

Dialog {
    id: dialog
    property var textToSpeech: null
    title: qsTr("Text to Speech Settings")
    standardButtons: Dialog.Close
    modal: true
    closePolicy: Popup.CloseOnEscape
    x: (appWindow.width - width) / 2
    y: (appWindow.height - height) / 2
    width: 400
    height: 600
    clip: true
    function updateComboBoxLocale() {
        let allLocales = textToSpeech.availableLocales().map((locale) => locale.nativeLanguageName);
        let currentLocaleIndex = allLocales.indexOf(textToSpeech.locale.nativeLanguageName);
        customComboBoxLocale.model = allLocales;
        customComboBoxLocale.currentIndex = currentLocaleIndex;
    }
    function updateComboBoxVoice() {
        customComboBoxVoice.model = textToSpeech.availableVoices().map((voice) => voice.name);
        let indexOfVoice = textToSpeech.availableVoices().indexOf(textToSpeech.voice);
        customComboBoxVoice.currentIndex = indexOfVoice;
    }
    onVisibleChanged: {
        if (!visible) {
            return
        }

        updateComboBoxLocale();
        updateComboBoxVoice();
    }
    contentItem: ColumnLayout {
        Label {
            Layout.fillWidth: true
            Layout.margins: 20
            wrapMode: Text.WordWrap
            text: qsTr("These settings are used to select a TTS engine and voice and to set parameters.")
        }
        GridLayout {
            Layout.fillWidth: true
            columns: 3
            // engines
            CustomLabel {
                Layout.topMargin: 10
                Layout.bottomMargin: 10
                Layout.leftMargin: 10
                Layout.rightMargin: 10
                Layout.alignment: Qt.AlignRight
                text: qsTr("engine")
            }
            CustomComboBox {
                id: customComboBoxEngine
                Layout.fillWidth: true
                Layout.topMargin: 10
                Layout.bottomMargin: 10
                Layout.leftMargin: 10
                Layout.rightMargin: 10
                model: textToSpeech.availableEngines()
                onCurrentIndexChanged: {
                    var engine = textAt(currentIndex);
                    textToSpeech.engine = engine;
                    qtOllamaFrontend.ttsEngine = engine;
                    updateComboBoxLocale();
                    updateComboBoxVoice();
                }
            }
            Item {}
            // locale
            CustomLabel {
                Layout.topMargin: 10
                Layout.bottomMargin: 10
                Layout.leftMargin: 10
                Layout.rightMargin: 10
                Layout.alignment: Qt.AlignRight
                text: qsTr("locale")
            }
            CustomComboBox {
                id: customComboBoxLocale
                Layout.fillWidth: true
                Layout.topMargin: 10
                Layout.bottomMargin: 10
                Layout.leftMargin: 10
                Layout.rightMargin: 10
                onActivated: {
                    let locales = textToSpeech.availableLocales();
                    textToSpeech.locale = locales[currentIndex];
                    qtOllamaFrontend.ttsLocale = locales[currentIndex].nativeLanguageName;
                    updateComboBoxVoice();
                }
            }
            Item {}
            // voice
            CustomLabel {                Layout.topMargin: 10
                Layout.bottomMargin: 10
                Layout.leftMargin: 10
                Layout.rightMargin: 10
                Layout.alignment: Qt.AlignRight
                text: qsTr("voice")
            }
            CustomComboBox {
                id: customComboBoxVoice
                Layout.fillWidth: true
                Layout.topMargin: 10
                Layout.bottomMargin: 10
                Layout.leftMargin: 10
                Layout.rightMargin: 10
                onCurrentIndexChanged: {
                    let voices = textToSpeech.availableVoices();
                    qtOllamaFrontend.ttsVoice = voices[currentIndex].name;
                }
            }
            Item {}
            // rate
            CustomLabel {
                Layout.topMargin: 10
                Layout.bottomMargin: 10
                Layout.leftMargin: 10
                Layout.rightMargin: 10
                Layout.alignment: Qt.AlignRight
                text: qsTr("rate")
            }
            Slider {
                id: sliderRate
                Layout.fillWidth: true
                Layout.topMargin: 10
                Layout.bottomMargin: 10
                Layout.leftMargin: 10
                Layout.rightMargin: 10
                from: -1.0
                to: 1.0
                value: qtOllamaFrontend.ttsRate
                stepSize: 0.1
                onValueChanged: {
                    textToSpeech.rate = value;
                    qtOllamaFrontend.ttsRate = value;
                }
            }
            Label {
                Layout.topMargin: 10
                Layout.bottomMargin: 10
                Layout.leftMargin: 10
                Layout.rightMargin: 10
                text: {
                    return Math.round(sliderRate.value * 10.0);
                }
            }
            // volume
            CustomLabel {
                Layout.topMargin: 10
                Layout.bottomMargin: 10
                Layout.leftMargin: 10
                Layout.rightMargin: 10
                Layout.alignment: Qt.AlignRight
                text: qsTr("volume")
            }
            Slider {
                id: sliderVolume
                Layout.fillWidth: true
                Layout.topMargin: 10
                Layout.bottomMargin: 10
                Layout.leftMargin: 10
                Layout.rightMargin: 10
                from: 0.0
                to: 1.0
                value: qtOllamaFrontend.ttsVolume
                stepSize: 0.1
                onValueChanged: {
                    textToSpeech.volume = value;
                    qtOllamaFrontend.ttsVolume = value;
                }
            }
            Label {
                Layout.topMargin: 10
                Layout.bottomMargin: 10
                Layout.leftMargin: 10
                Layout.rightMargin: 10
                text: {
                    return Math.round(sliderVolume.value * 10.0);
                }
            }
            // pitch
            CustomLabel {
                Layout.topMargin: 10
                Layout.bottomMargin: 10
                Layout.leftMargin: 10
                Layout.rightMargin: 10
                Layout.alignment: Qt.AlignRight
                text: qsTr("pitch")
            }
            Slider {
                id: sliderPitch
                Layout.fillWidth: true
                Layout.topMargin: 10
                Layout.bottomMargin: 10
                Layout.leftMargin: 10
                Layout.rightMargin: 10
                from: -1.0
                to: 1.0
                value: qtOllamaFrontend.ttsPitch
                stepSize: 0.1
                onValueChanged: {
                    textToSpeech.pitch = value;
                    qtOllamaFrontend.ttsPitch = value;
                }
            }
            Label {
                Layout.topMargin: 10
                Layout.bottomMargin: 10
                Layout.leftMargin: 10
                Layout.rightMargin: 10
                text: {
                    return Math.round(sliderPitch.value * 10.0);
                }
            }
            // button
            Item {}
            CustomButton {
                id: customButtonTest
                Layout.topMargin: 10
                Layout.bottomMargin: 10
                Layout.leftMargin: 10
                Layout.rightMargin: 10
                Layout.alignment: Qt.AlignRight
                text: qsTr("Play Test Message")
                onClicked: {
                    if (textToSpeech.voice.locale.name == "de_DE") {
                        qtOllamaFrontend.say("Dies ist eine Testnachricht. Verstehst du, was ich sage?");
                    } else {
                        qtOllamaFrontend.say("This is a test message. Do you understand what i'm saying?");
                    }
                }
            }
        }
    }
}
