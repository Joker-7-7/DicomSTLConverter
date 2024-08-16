import QtQuick 2.9
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import QtQuick.Templates 2.5 as T


import Vtk 1.0 as Vtk

T.Slider {
    id: root

    required property string sliderType


    onMoved: function() {
        sceneItem.OnSliderChanged(value, sliderType);
    }
    background: Rectangle {
        x: root.leftPadding
        y: root.topPadding + root.availableHeight / 2 - height / 2
        implicitWidth: 200
        implicitHeight: 4
        width: root.availableWidth
        height: implicitHeight
        radius: 2
        color: "#FFFFFF"

        Rectangle {
            width: root.visualPosition * parent.width
            height: parent.height
            color: "#0EB56F"
            radius: 2
        }
    }

    handle: Rectangle {
        x: root.leftPadding + root.visualPosition * (root.availableWidth - width)
        y: root.topPadding + root.availableHeight / 2 - height / 2
        implicitWidth: 12
        implicitHeight: 12
        radius: 999
        color: root.pressed ? "#f0f0f0" : "#f6f6f6"
        border.color: "#bdbebf"
    }
}
