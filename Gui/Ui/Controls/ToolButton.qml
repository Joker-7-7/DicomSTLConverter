import QtQuick 2.9
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3

Item {
    id: root

    required property string iconSource
    required property var action
    required property bool deselectIfSelected

    readonly property string backgroundColor: "#3B3D3F"

    function select() {
        internal.checked = true;
        root.state = "checked";
    }

    function deselect() {
        internal.checked = false;
        root.state = "unchecked";
    }

    function emulateClick() {
        button.onClicked(null);
    }

    QtObject {
        id: internal
        property bool checked: false
    }

    Rectangle {
        id: container
        anchors.fill: parent
        radius: 4

        MouseArea {
            id: button
            hoverEnabled: true

            anchors.fill: parent
            onClicked: {
                if (internal.checked) {
                    root.state = deselectIfSelected ? "unchecked" : "checked";
                    internal.checked = !deselectIfSelected;
                } else {
                    root.state = "checked";
                    internal.checked = true;
                }
                root.action();
            }
            onEntered: root.state = internal.checked ? root.state : "hovered"
            onExited: root.state = internal.checked ? root.state : "unchecked"
        }

        Image {
            source: iconSource
            width: Math.min(parent.width, parent.height) / 2
            height: Math.min(parent.width, parent.height) / 2
            anchors.centerIn: parent
        }
    }

    states: [
        State {
            name: "unchecked"
            PropertyChanges {
                target: container
                color: backgroundColor
                opacity: 1
            }
        },
        State {
            name: "hovered"
            PropertyChanges {
                target: container
                color: "#FFFFFF"
                opacity: 0.5
            }
        },
        State {
            name: "checked"
            PropertyChanges {
                target: container
                color: "#0EB56F"
                opacity: 1
            }
        }
    ]

    state: "unchecked"
}
