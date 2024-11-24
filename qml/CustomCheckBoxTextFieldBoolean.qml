import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ColumnLayout {
    id: root
    property alias labelText: checkBox.text
    property alias checked: checkBox.checked
    property alias switchChecked: switchControl.checked
    signal onSwitchCheckedChanged()
    signal onCheckedChanged()
    CheckBox {
        id: checkBox
        Layout.fillWidth: true
        onCheckedChanged: root.onCheckedChanged()
    }
    Switch {
        id: switchControl
        Layout.topMargin: 10
        enabled: checkBox.checked
        onCheckedChanged: root.onSwitchCheckedChanged()
    }
}
