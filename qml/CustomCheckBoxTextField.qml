import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ColumnLayout {
    id: root
    property alias labelText: checkBox.text
    property alias checked: checkBox.checked
    property alias text: textField.text
    signal onTextChanged()
    signal onCheckedChanged()
    CheckBox {
        id: checkBox
        Layout.fillWidth: true
        onCheckedChanged: root.onCheckedChanged()
    }
    CustomTextField {
        id: textField
        Layout.fillWidth: true
        Layout.topMargin: 10
        enabled: checkBox.checked
        onTextChanged: root.onTextChanged()
    }
}
