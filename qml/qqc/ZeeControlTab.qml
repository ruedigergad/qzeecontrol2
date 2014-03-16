import QtQuick 2.2
import QtQuick.Controls 1.1
import QZeeControl2 1.0

Tab {
    id: zeeControlTab

    property string address
    property int n: 1

    anchors.fill: parent
    title: "Zee " + n

    Rectangle {
        anchors.fill: parent

        color: "lightgray"

        Column {
            anchors.fill: parent
            spacing: 10

            Row {
                id: addressRow
                anchors.horizontalCenter: parent.horizontalCenter

                spacing: 10

                TextField {
                    id: addressTextField

                    placeholderText: "Please enter a Zeemote address or scan."
                    text: address
                    width: zeeControlTab.width * 0.5
                }

                Button {
                    id: scanButton

                    text: "Scan"

                    onClicked: {
                        mainStackView.push({item: Qt.resolvedUrl("BtSelectDialog.qml"), properties: {parentTab: zeeControlTab}})
                    }
                }
            }

            Button {
                id: connectButton

                anchors.horizontalCenter: parent.horizontalCenter
                enabled: addressTextField.text !== ""
                text: btConnector.connected ? "Disconnect" : "Connect"

                onClicked: {
                    if (! btConnector.connected) {
                        btConnector.connect(address, 1)
                    } else {
                        btConnector.disconnect()
                    }
                }
            }

            Row {
                id: buttonRow
                anchors.horizontalCenter: parent.horizontalCenter

                spacing: 20

                Label {
                    id: labelA

                    color: btConnector.a ? "red" : "blue"
                    font.pixelSize: 30
                    text: "A"
                }
                Label {
                    id: labelB

                    color: btConnector.b ? "red" : "blue"
                    font.pixelSize: 30
                    text: "B"
                }
                Label {
                    id: labelC

                    color: btConnector.c ? "red" : "blue"
                    font.pixelSize: 30
                    text: "C"
                }
                Label {
                    id: labelD

                    color: btConnector.d ? "red" : "blue"
                    font.pixelSize: 30
                    text: "D"
                }
            }

            Item {
                id: testArea
                anchors.horizontalCenter: parent.horizontalCenter
                height: moveArea.height
                width: moveArea.width

                Rectangle {
                    id: moveArea
                    color: "gray"

                    height: width
                    width: zeeControlTab.width * 0.5
                }

                Rectangle {
                    id: cursorRectangle
                    width: 10
                    height: 10
                    color: "red"

                    x: moveArea.x + (moveArea.width * 0.5) + btConnector.x - (cursorRectangle.width * 0.5)
                    y: moveArea.y + (moveArea.height * 0.5) + btConnector.y - (cursorRectangle.height * 0.5)
                }
            }
        }

        BtConnector {
            id: btConnector

            onDataUpdated: {
                console.log(data)
            }
        }
    }
}
