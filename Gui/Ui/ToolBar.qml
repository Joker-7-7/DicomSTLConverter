import QtQuick 2.9
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3

import "qrc:/Gui/Controls" as Controls

import Vtk 1.0 as Vtk

Item {
    id: root

    required property string backgroundColor
    required property var sliderWindow
    required property BusyIndicator progressBar

    function deselectAllButton()
    {
        convertButton.deselect();
    }


    Rectangle {
        color: backgroundColor
        anchors.fill: parent

        RowLayout {
            x: 16
            spacing: 6
            height: parent.height

            Controls.VoxelToolButton {
                Layout.alignment: Qt.AlignVCenter
                width: 124
                height: 34
                window: sliderWindow
            }

            Rectangle {
                Layout.alignment: Qt.AlignVCenter
                width: 1
                height: 32
                color: "#3B3D3F"
                radius: 4
            }

            Controls.ToolButton {
                id: convertButton
                Layout.alignment: Qt.AlignVCenter
                Layout.preferredWidth: 34
                Layout.preferredHeight: 34
                iconSource: "qrc:/Assets/smoothing.png"
                action: function() { 
                    progressBar.running = true;
                    sceneItem.OnConvertToSTL();
                    progressBar.running = false
                }
                deselectIfSelected: true
            }

        }
    }
}
