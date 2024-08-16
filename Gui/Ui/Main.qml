import QtQuick 2.9
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import QtMultimedia

import "qrc:/Gui/" as LayoutControls
import "qrc:/Gui/Controls" as Controls

import Vtk 1.0 as Vtk

ApplicationWindow {
    id: root

    readonly property int designHeight: 861
    readonly property int designWidth: 1280

    readonly property string backgroundColor: "#37393B"
    readonly property string fontColor: "#FFFFFF"
    readonly property string iconsFontFamily: "Segoe Fluent Icons"

    property int previousMouseX
    property int previousMouseY


    width: 1280
    height: 861

    visibility: "Windowed"
    flags: Qt.Window | Qt.FramelessWindowHint
    title: qsTr("DICOMrender")


    LayoutControls.TitleBar {
        id: titleBar
        mainWindow: root
        width: parent.width
        height: 32
        backgroundColor: "#151719"
        fontColor: "#ffffff"
    }

    LayoutControls.MenuBar {
        deselectButton: mainToolBar
        progressBar: indicator
        y: 32
        width: parent.width
        height: 50
        backgroundColor: "#151719"
    }

    LayoutControls.ToolBar {
        id: mainToolBar
        progressBar: indicator
        y: 32 + 50
        width: parent.width
        height: 50
        backgroundColor: "#151719"
        sliderWindow: settings
    }

    Rectangle {
        y: 32 + 50 + 50
        height : parent.height - 32 - 50 - 50 - 60
        width: 12
        color: "#151719"
    }

    Vtk.SceneVtkItem {
        id: sceneItem
        x: 12
        y: 32 + 50 + 50
        height: 670
        width: 1280
    }

    BusyIndicator {
        id: indicator
        anchors.centerIn: parent
        width: 100
        height: 80
        visible: true
        running: false
    }

    Rectangle {
        x: parent.width - 12
        y: 32 + 50 + 50
        height : parent.height - 32 - 50 - 50 - 60
        width: 12
        color: "#151719"
    }


    Rectangle {
        y: parent.height - 60
        width: parent.width
        height: 60
        color: "#151719"
    }

    Rectangle {
        id: settings
        x: 100
        y: 128
        width: 206
        height: 156
        color: "#3B3D3F"
        visible: false
        radius: 7

        ColumnLayout {
            spacing: 16

            anchors {
                fill: parent
                topMargin: 10
                bottomMargin: 10
            }

            Rectangle {
                Layout.preferredWidth: parent.width
                Layout.preferredHeight: 20
                Layout.leftMargin: 16
                color: "transparent"

                Text {
                    anchors.verticalCenter: parent.verticalCenter
                    text: "W level"
                    font.pixelSize: 16
                    font.family: "Segoe UI Variable Text"
                    color: "#FFFFFF"
                }
            }

            Rectangle {
                Layout.preferredWidth: parent.width - 32
                Layout.preferredHeight: 24
                Layout.leftMargin: 16
                color: "transparent"

                Controls.Slider {
                    anchors.fill: parent
                    from: 0
                    to: 2700
                    value: 300
                    sliderType: "W"
                }
            }

            Rectangle {
                Layout.preferredWidth: parent.width
                Layout.preferredHeight: 20
                Layout.leftMargin: 16
                color: "transparent"

                Text {
                    anchors.verticalCenter: parent.verticalCenter
                    text: "L level"
                    font.pixelSize: 16
                    font.family: "Segoe UI Variable Text"
                    color: "#FFFFFF"
                }
            }

            Rectangle {
                Layout.preferredWidth: parent.width - 32
                Layout.preferredHeight: 24
                Layout.leftMargin: 16
                color: "transparent"

                Controls.Slider {
                    anchors.fill: parent
                    from: 0
                    to: 2700
                    value: 900
                    sliderType: "L"
                }
            }
        }
    }

    MouseArea {
        id: topArea
        height: 5
        anchors {
            top: parent.top
            left: parent.left
            right: parent.right
        }
        // We set the shape of the cursor so that it is clear that this resizing
        cursorShape: Qt.SizeVerCursor

        onPressed: {
            // We memorize the position along the Y axis
            previousMouseY = mouseY
        }

        // When changing a position, we recalculate the position of the window, and its height
        onMouseYChanged: {
            var dy = mouseY - previousMouseY
            if(root.height - dy > designHeight)
            {
                root.setY(root.y + dy)
                root.setHeight(root.height - dy)
            }
        }
    }

    MouseArea {
        id: bottomArea
        height: 5
        anchors {
            bottom: parent.bottom
            left: parent.left
            right: parent.right
        }
        cursorShape: Qt.SizeVerCursor

        onPressed: {
            previousMouseY = mouseY
        }

        onMouseYChanged: {
            var dy = mouseY - previousMouseY
            if(root.height + dy > designHeight)
                root.setHeight(root.height + dy)
        }
    }

    MouseArea {
        id: leftArea
        width: 5
        anchors {
            top: topArea.bottom
            bottom: bottomArea.top
            left: parent.left
        }
        cursorShape: Qt.SizeHorCursor

        onPressed: {
            previousMouseX = mouseX
        }

        onMouseXChanged: {
            var dx = mouseX - previousMouseX
            if(root.width - dx > designWidth)
            {
                root.setX(root.x + dx)
                root.setWidth(root.width - dx)
            }
        }
    }

    MouseArea {
        id: rightArea
        width: 5
        anchors {
            top: topArea.bottom
            bottom: bottomArea.top
            right: parent.right
        }
        cursorShape:  Qt.SizeHorCursor

        onPressed: {
            previousMouseX = mouseX
        }

        onMouseXChanged: {
            var dx = mouseX - previousMouseX
            if(root.width + dx > designWidth)
                root.setWidth(root.width + dx)
        }
    }


}
