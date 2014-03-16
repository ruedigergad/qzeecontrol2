import QtQuick 2.2
import QtQuick.Controls 1.1

ApplicationWindow {
    title: qsTr("QZeeControl2")
    width: 640
    height: 480

    menuBar: MenuBar {
        Menu {
            title: qsTr("File")
            MenuItem {
                text: qsTr("Exit")
                onTriggered: Qt.quit();
            }
        }
    }

    StackView {
        id: mainStackView

        initialItem: TabView {
            id: mainTabView

            anchors.fill: parent

            ZeeControlTab {
                id: zee1
                n: 1
            }

            ZeeControlTab {
                id: zee2
                n: 2
            }
        }
    }

}
