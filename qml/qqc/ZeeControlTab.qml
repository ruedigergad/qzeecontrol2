import QtQuick 2.2
import QtQuick.Controls 1.1
import QZeeControl2 1.0

Tab {
    id: zeeControlTab

    property string address
    property bool debugOutput: false
    property int n: 1
    property bool useLocalUinput: false
    property bool useGlobalUinput: false
    property bool secondGlobalUinput: false

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

                    onTextChanged: {
                        if (text !== "") {
                            console.log("Storing address " + address + " for Zeemote " + n)
                            settingsAdapter.setString("ZeemoteAddress_" + n, address)
                        }
                    }
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
                        if (useLocalUinput) {
                            uinputAdapter.create("zeecontrol_" + n)
                        }
                    } else {
                        btConnector.disconnect()
                        if (useLocalUinput) {
                            uinputAdapter.destroy()
                        }
                    }
                }
            }

            Row {
                id: buttonRow
                anchors.horizontalCenter: parent.horizontalCenter

                spacing: 20

                Label {
                    id: labelA

                    color: btDataProcessor.a ? "red" : "blue"
                    font.pixelSize: 30
                    text: "A"
                }
                Label {
                    id: labelB

                    color: btDataProcessor.b ? "red" : "blue"
                    font.pixelSize: 30
                    text: "B"
                }
                Label {
                    id: labelC

                    color: btDataProcessor.c ? "red" : "blue"
                    font.pixelSize: 30
                    text: "C"
                }
                Label {
                    id: labelD

                    color: btDataProcessor.d ? "red" : "blue"
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

                    x: moveArea.x + (moveArea.width * 0.5) + btDataProcessor.x - (cursorRectangle.width * 0.5)
                    y: moveArea.y + (moveArea.height * 0.5) + btDataProcessor.y - (cursorRectangle.height * 0.5)
                }
            }
        }

        BtConnector {
            id: btConnector

            onDataReceived: btDataProcessor.processData(data)
        }

        BtDataProcessor {
            id: btDataProcessor

            onDataUpdated: {
                if (debugOutput) {
                    console.log(data)
                }
            }

            onAChanged: {
                if (useLocalUinput) {
                    uinputAdapter.emitClick(UinputAdapter.BUTTON_A, val)
                }

                if (useGlobalUinput) {
                    if (secondGlobalUinput) {
                        globalUinputAdapter.emitClick(UinputAdapter.BUTTON_E, val)
                    } else {
                        globalUinputAdapter.emitClick(UinputAdapter.BUTTON_A, val)
                    }
                }
            }
            onBChanged: {
                if (useLocalUinput) {
                    uinputAdapter.emitClick(UinputAdapter.BUTTON_B, val)
                }

                if (useGlobalUinput) {
                    if (secondGlobalUinput) {
                        globalUinputAdapter.emitClick(UinputAdapter.BUTTON_F, val)
                    } else {
                        globalUinputAdapter.emitClick(UinputAdapter.BUTTON_B, val)
                    }
                }
            }
            onCChanged: {
                if (useLocalUinput) {
                    uinputAdapter.emitClick(UinputAdapter.BUTTON_C, val)
                }

                if (useGlobalUinput) {
                    if (secondGlobalUinput) {
                        globalUinputAdapter.emitClick(UinputAdapter.BUTTON_G, val)
                    } else {
                        globalUinputAdapter.emitClick(UinputAdapter.BUTTON_C, val)
                    }
                }
            }
            onDChanged: {
                if (useLocalUinput) {
                    uinputAdapter.emitClick(UinputAdapter.BUTTON_D, val)
                }

                if (useGlobalUinput) {
                    if (secondGlobalUinput) {
                        globalUinputAdapter.emitClick(UinputAdapter.BUTTON_H, val)
                    } else {
                        globalUinputAdapter.emitClick(UinputAdapter.BUTTON_D, val)
                    }
                }
            }

            onStickMoved: {
                if (debugOutput) {
                    console.log("x: " + x + "   y: " + y)
                }

                if (useLocalUinput) {
                    uinputAdapter.emitXYEvent(x, y)
                }

                if (useGlobalUinput) {
                    if (secondGlobalUinput) {
                        globalUinputAdapter.emitRxRyEvent(x, y)
                    } else {
                        globalUinputAdapter.emitXYEvent(x, y)
                    }
                }
            }
        }

        SettingsAdapter {
            id: settingsAdapter

            Component.onCompleted: {
                zeeControlTab.address = readString("ZeemoteAddress_" + n, "")
            }
        }

        UinputAdapter {
            id: uinputAdapter
        }
    }
}
