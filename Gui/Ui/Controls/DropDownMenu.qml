import QtQuick 2.9
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3

Item {
    id: root

    required property var menuModel
    required property string modelTextRole
    required property string modelCallbackRole
    required property int menuItemWidth
    required property int menuItemHeight
    required property bool useIndicator

    readonly property string backgroundColor: "#45484A"
    readonly property string fontFamily: "Segoe Fluent Icons"
    readonly property int fontSize: 20
    readonly property int fontWeight: Font.Normal
    readonly property string fontColor: "#FFFFFF"

    function open() {
        menu.open();
    }

    Menu {
        id: menu
        width: menuItemWidth
        height: (menuItemHeight + 1) * menuModel.length
        background: Rectangle {
            color: "#3B3D3F"
            radius: 7
        }

        Repeater {
            model: menuModel
            delegate: MenuItem {
                id: menuItem
                height: menuItemHeight
                highlighted: menu.currentIndex === -2
                onTriggered: modelData[root.modelCallbackRole]()
                contentItem: Rectangle {
                    anchors {
                        fill: menuItem
                        leftMargin: menuItemWidth * 17 / 160
                    }
                    color: "transparent"

                    Text {
                        anchors {
                            fill: parent
                            verticalCenter: parent.verticalCenter
                        }
                        text: modelData[root.modelTextRole]
                        font {
                            family: "Segoe UI Variable Text"
                            pixelSize: 15
                        }
                        color: "#FFFFFF"
                        elide: Text.ElideRight
                        verticalAlignment: Text.AlignVCenter
                   }
                }

                indicator: Rectangle {
                    anchors {
                        fill: menuItem
                        leftMargin: menuItemWidth * 5 / 160
                        rightMargin: menuItemWidth * 5 / 160
                        verticalCenter: menuItem.verticalCenter
                    }
                    visible: menuItem.hovered
                    radius: 8
                    color: "#626365"

                    Rectangle {
                        height: menuItemHeight * 16 / 36
                        width: menuItemWidth * 3 / 160
                        anchors {
                            left: parent.left
                            verticalCenter: parent.verticalCenter
                        }
                        visible: useIndicator
                        color: "#0EB56F"
                        radius: 8
                    }
                }
            }
        }
    }
}
