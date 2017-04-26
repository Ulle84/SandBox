import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

Item {
    property alias textField1: textField1
    property alias textField2: textField2
    property alias button1: button1


    RowLayout {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.topMargin: 20
        anchors.top: parent.top

        TextField {
            id: textField1
            font.family: "Verdana"
            horizontalAlignment: Text.AlignLeft
            placeholderText: qsTr("Text Field")
        }

        Button {
            id: button1
            text: qsTr("Press Me")
        }

        TextField {
            id: textField2
            text: "text field 2"
            font.pointSize: 13
            horizontalAlignment: Text.AlignLeft
            font.family: "Verdana"
            placeholderText: qsTr("Text Field")
        }
    }

    ColumnLayout {
        id: columnLayout
        x: 105
        y: 124
        width: 227
        height: 212
    }

    RangeSlider {
        id: rangeSlider
        x: 119
        y: 144
        first.value: 0.25
        second.value: 0.75
    }

    Slider {
        id: slider
        x: 119
        y: 190
        value: 0.5
    }

    Switch {
        id: switch1
        x: 150
        y: 249
        text: qsTr("Switch")
    }

    BusyIndicator {
        id: busyIndicator
        x: 404
        y: 163
    }

    TextEdit {
        id: textEdit
        x: 384
        y: 242
        width: 197
        height: 89
        text: qsTr("Text Edit")
        font.pixelSize: 12
    }
}
