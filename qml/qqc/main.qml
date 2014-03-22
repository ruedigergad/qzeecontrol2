import QtQuick 2.2
import QtQuick.Controls 1.1
import QZeeControl 2.0

ApplicationWindow {
    title: qsTr("QZeeControl 2")
    width: 640
    height: 480

//    menuBar: MenuBar {
//        Menu {
//            title: qsTr("File")
//            MenuItem {
//                text: qsTr("Exit")
//                onTriggered: Qt.quit();
//            }
//        }
//    }

    StackView {
        id: mainStackView

        initialItem: TabView {
            id: mainTabView

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

    UinputAdapter {
        id: globalUinputAdapter

        Component.onCompleted: {
            createDevice("qzeecontrol2_global")
        }
    }

}
