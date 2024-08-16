import QtQuick 2.9
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3

Item {
    id: root

    required property string backgroundColor
    required property string fontColor

    readonly property string iconsFontFamily: "Segoe Fluent Icons"

    required property ApplicationWindow mainWindow

    Rectangle {
        anchors.fill: parent
        color: backgroundColor

        MouseArea {
            anchors {fill: parent
                     right: buttonsForWindow.left
            }

            onPressed: {
                previousMouseX = mouseX
                previousMouseY = mouseY
            }

            onMouseXChanged: {
               var dx = mouseX - previousMouseX
               if(mainWindow.x + mouseX > screen.width*0.98)
               {
                   mainWindow.setX(screen.width - mainWindow.width);
               }
               else
               {
                   mainWindow.setX(mainWindow.x + dx)
               }
            }

            onMouseYChanged: {
                var dy = mouseY - previousMouseY
                if(mainWindow.y + mouseY > screen.height*0.96)
                {
                    mainWindow.setY(screen.height - mainWindow.height);
                }
                else
                {
                    mainWindow.setY(mainWindow.y + dy)
                }
            }
        }

        Rectangle {
            width: 72
            height: parent.height
            x: 40
            color: "transparent"
            Text {
                anchors.centerIn: parent
                text: "DicomSTLConverter"
                color: "#FFFFFF"
                font.pixelSize: 14
            }
        }

        Rectangle {
            id: buttonsForWindow
            anchors.right: parent.right
            height: parent.height
            width: 123
            color: "transparent"

            MouseArea {
                width: parent.width / 3
                height: parent.height
                hoverEnabled: true
                Rectangle {
                    id: minimizeWrapper
                    anchors.fill: parent
                    color: "transparent"
                    Text {
                        anchors.fill: parent
                        text: "\ue921"
                        color: fontColor
                        font.family: iconsFontFamily
                        fontSizeMode: Text.Fit
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter
                    }
                }

                onEntered: {
                    minimizeWrapper.opacity = 0.5;
                    minimizeWrapper.color = "#FFFFFF";
                }
                onExited: {
                    minimizeWrapper.opacity = 1;
                    minimizeWrapper.color = "transparent";
                }
                onClicked: Window.window.showMinimized();
            }

            MouseArea {
                x: parent.width / 3
                width: parent.width / 3
                height: parent.height
                hoverEnabled: true

                Rectangle {
                    id: collapseWrapper
                    anchors.fill: parent
                    color: "transparent"
                    Text {
                        anchors.fill: parent
                        text: Window.window.visibility === Window.Windowed ? "\ue922" : "\ue923"
                        color: fontColor
                        font.family: iconsFontFamily
                        fontSizeMode: Text.Fit
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter
                    }
                }

                onEntered: {
                    collapseWrapper.opacity = 0.5;
                    collapseWrapper.color = "#FFFFFF";
                }
                onExited: {
                    collapseWrapper.opacity = 1;
                    collapseWrapper.color = "transparent";
                }
                onClicked: Window.window.visibility = Window.window.visibility === Window.Windowed ? Window.FullScreen : Window.Windowed;
            }

            MouseArea {
                x: parent.width * 2 / 3
                width: parent.width / 3
                height: parent.height
                hoverEnabled: true

                Rectangle {
                    id: closeWrapper
                    anchors.fill: parent
                    color: "transparent"
                    Text {
                        anchors.fill: parent
                        text: "\ue8bb"
                        color: fontColor
                        font.family: iconsFontFamily
                        fontSizeMode: Text.Fit
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter
                    }
                }

                onEntered: {
                    closeWrapper.opacity = 0.5;
                    closeWrapper.color = "#FFFFFF";
                }
                onExited: {
                    closeWrapper.opacity = 1;
                    closeWrapper.color = "transparent";
                }
                onClicked: Qt.quit();
            }
        }
    }
}
