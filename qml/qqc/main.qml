import QtQuick 2.2
import QtQuick.Controls 1.1
import QZeeControl2 1.0

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

            ZeeControlTab {
                id: zee1
                n: 1
                useGlobalUinput: true
            }

            ZeeControlTab {
                id: zee2
                n: 2
                useGlobalUinput: true
                secondGlobalUinput: true
            }
        }
    }

    UinputAdapter {
        id: globalUinputAdapter

        Component.onCompleted: {
            create("qzeecontrol2_global")
        }
    }

    Bluez5BtConnector {
        id: testBluez
    }

}
