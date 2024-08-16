import QtQuick 2.9
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3

import "." as Controls

import Vtk 1.0 as Vtk

Item {
    required property var window



    QtObject {
        id: internal
        property var selectedItem: undefined

        function onClicked(sender) {
            [faceMode, skullMode, jawMode, settingsMode].forEach(t => t.deselect());
            sender.select();
            window.visible = (sender === settingsMode) && !window.visible;
        }
    }

    Rectangle {
        anchors.fill: parent
        color: "#3B3D3F"
        radius: 4

        RowLayout {
            anchors.fill: parent
            spacing: 0

            Controls.ToolButton {
                id: faceMode
                Layout.alignment: Qt.AlignVCenter
                Layout.preferredWidth: 34
                Layout.preferredHeight: 34
                iconSource: "qrc:/Assets/face.png"
                action: function() {
                    internal.onClicked(this);
                    sceneItem.OnSkinConfigClicked();
                }
                deselectIfSelected: false
            }

            Controls.ToolButton {
                id: skullMode
                Layout.alignment: Qt.AlignVCenter
                Layout.preferredWidth: 34
                Layout.preferredHeight: 34
                iconSource: "qrc:/Assets/skull.png"
                action: function() {
                    internal.onClicked(this);
                    sceneItem.OnSolidConfigClicked();
                }
                deselectIfSelected: false
            }

            Controls.ToolButton {
                id: jawMode
                Layout.alignment: Qt.AlignVCenter
                Layout.preferredWidth: 34
                Layout.preferredHeight: 34
                iconSource: "qrc:/Assets/jaw.png"
                action: function() {
                    internal.onClicked(this);
                    sceneItem.OnTeethConfigClicked();
                }
                deselectIfSelected: false
            }

            Rectangle {
                width: 1
                height: 32
                color: "#494B4C"
            }

            Controls.ToolButton {
                id: settingsMode
                Layout.alignment: Qt.AlignVCenter
                Layout.preferredWidth: 21
                Layout.preferredHeight: 34
                iconSource: "qrc:/Assets/arrow.png"
                action: function() {
                    internal.onClicked(this);
                }
                deselectIfSelected: false
            }
        }
    }
}
