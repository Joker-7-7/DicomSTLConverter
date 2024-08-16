import QtQuick 2.9
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import QtQuick.Dialogs

import "qrc:/Gui/Controls" as Controls
import "qrc:/Gui" as Gui

import Vtk 1.0 as Vtk

Item {
    id: root

    required property string backgroundColor

    readonly property string fontFamily: "Segoe UI Variable Text"
    readonly property int fontSize: 14
    readonly property int fontWeight: Font.Normal
    readonly property string fontColor: "#FFFFFF"
    required property Gui.ToolBar deselectButton
    required property BusyIndicator progressBar


    FileDialog {
        id: fileDialog
        nameFilters: ["*.dcm"]
        onAccepted: function() {
            sceneItem.OnOpenFileClicked(selectedFile);
            
            deselectButton.deselectAllButton();
            progressBar.running = false;
        }
        onRejected: progressBar.running = false;
    }

    FolderDialog {
        id: folderDialog
        onAccepted: function() {
            sceneItem.OnOpenDirectoryClicked(selectedFolder);
            
            deselectButton.deselectAllButton();
            progressBar.running = false;
        }
        onRejected: progressBar.running = false;

    }
   MessageDialog
    {
        id: msgDialog
        title: "Error"
        text: "Cannot confirm"
        informativeText: "The directory does not contain the correct files or the files are corrupted."
        visible: false
        onAccepted: console.log("client clicked ok")
    }

    Connections{
        target: sceneItem
        function onShowMessageBox(){ msgDialog.visible = true;}
    }

    Rectangle {
        color: backgroundColor
        anchors.fill: parent


        RowLayout {
            height: parent.height
            spacing: 10
            x: 16

            MouseArea {
                Layout.preferredWidth: 44
                Layout.preferredHeight: parent.height * 2 / 3
                Layout.alignment: Qt.AlignVCenter
                hoverEnabled: true
                acceptedButtons: Qt.LeftButton

                Rectangle {
                    id: fileWrapper
                    color: "transparent"
                    anchors.fill: parent
                    radius: 4

                    Text {
                       text: "File"
                       anchors.centerIn: parent
                       font {
                           family: fontFamily
                           pixelSize: fontSize
                           weight: fontWeight
                       }
                       color: fontColor
                       horizontalAlignment: Text.AlignHCenter
                       verticalAlignment: Text.AlignVCenter
                   }
                }

               onClicked: fileMenu.open()

               onEntered: {
                   fileWrapper.opacity = 0.5;
                   fileWrapper.color = "#FFFFFF";
               }
               onExited: {
                   fileWrapper.opacity = 1;
                   fileWrapper.color = "transparent";
               }

               Controls.DropDownMenu {
                   id: fileMenu
                   y: parent.height
                   width: root.width / 1280 * 54
                   height: (root.height * 40 / 50 + 1) * fileMenu.menuModel.length

                   menuModel: [
                       { text: "Open single",      onTriggered: function() { progressBar.running = true; fileDialog.open(); } },
                       { text: "Open directory", onTriggered: function() { progressBar.running = true;  folderDialog.open(); } }
                   ]
                   modelTextRole: "text"
                   modelCallbackRole: "onTriggered"
                   menuItemWidth: root.width * 160 / 1280
                   menuItemHeight: root.height * 40 / 50
                   useIndicator: false
               }
            }
        }
    }
}

