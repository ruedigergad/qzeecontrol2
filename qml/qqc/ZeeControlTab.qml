import QtQuick 2.2
import QtQuick.Controls 1.1
import QZeeControl 2.0

Tab {
    id: zeeControlTab

    property string address
    property bool debugOutput: false
    property int n: 1
    property bool useLocalUinput: false
    property bool useGlobalUinput: false
    property bool secondGlobalUinput: false

    property QtObject uinputAdapter

    property int keyCodeA
    property int keyCodeB
    property int keyCodeC
    property int keyCodeD
    property int keyCodeUp
    property int keyCodeDown
    property int keyCodeLeft
    property int keyCodeRight

    anchors.fill: parent
    title: "Zee " + n

    onUseGlobalUinputChanged: if (useGlobalUinput) uinputAdapter = globalUinputAdapter
    onUseLocalUinputChanged: if (useLocalUinput) uinputAdapter = localUinputAdapter

    Rectangle {
        anchors.fill: parent

        color: "lightgray"

        function setKeyCodes() {
            keyCodeA = globalUinputAdapter.keysStringToEnum(settingsAdapter.readString("zeemote_" + n + "_keycode_A", "A"))
            keyCodeB = globalUinputAdapter.keysStringToEnum(settingsAdapter.readString("zeemote_" + n + "_keycode_B", "B"))
            keyCodeC = globalUinputAdapter.keysStringToEnum(settingsAdapter.readString("zeemote_" + n + "_keycode_C", "C"))
            keyCodeD = globalUinputAdapter.keysStringToEnum(settingsAdapter.readString("zeemote_" + n + "_keycode_D", "D"))
            keyCodeUp = globalUinputAdapter.keysStringToEnum(settingsAdapter.readString("zeemote_" + n + "_keycode_UP", "UP"))
            keyCodeDown = globalUinputAdapter.keysStringToEnum(settingsAdapter.readString("zeemote_" + n + "_keycode_DOWN", "DOWN"))
            keyCodeLeft = globalUinputAdapter.keysStringToEnum(settingsAdapter.readString("zeemote_" + n + "_keycode_LEFT", "LEFT"))
            keyCodeRight = globalUinputAdapter.keysStringToEnum(settingsAdapter.readString("zeemote_" + n + "_keycode_RIGHT", "RIGHT"))
        }

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
                    width: zeeControlTab.width * 0.3

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

                Button {
                    id: connectButton

                    enabled: addressTextField.text !== "" && (text === "Connect" || text === "Disconnect")
                    text: "Connect"

                    onClicked: {
                        if (! btConnector.connected) {
                            btConnector.connect(address, 1)
                            if (useLocalUinput) {
                                uinputAdapter.create("zeecontrol_" + n)
                            }
                            text = "Connecting..."
                        } else {
                            btConnector.disconnect()
                            if (useLocalUinput) {
                                uinputAdapter.destroy()
                            }
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
                    width: zeeControlTab.width * 0.3
                }

                Rectangle {
                    id: cursorRectangle
                    width: 10
                    height: 10
                    color: "red"

                    x: moveArea.x + (moveArea.width * 0.5) + (btDataProcessor.x / 256 * moveArea.width) - (cursorRectangle.width * 0.5)
                    y: moveArea.y + (moveArea.height * 0.5) + (btDataProcessor.y / 256 * moveArea.width) - (cursorRectangle.height * 0.5)
                }
            }


            Row {
                id: digitalStickRow
                anchors.horizontalCenter: parent.horizontalCenter

                spacing: 20

                Label {
                    id: labelUp

                    color: btDataProcessor.up ? "red" : "blue"
                    font.pixelSize: 30
                    text: "Up"
                }
                Label {
                    id: labelDown

                    color: btDataProcessor.down ? "red" : "blue"
                    font.pixelSize: 30
                    text: "Down"
                }
                Label {
                    id: labelLeft

                    color: btDataProcessor.left ? "red" : "blue"
                    font.pixelSize: 30
                    text: "Left"
                }
                Label {
                    id: labelRight

                    color: btDataProcessor.right ? "red" : "blue"
                    font.pixelSize: 30
                    text: "Right"
                }
            }
        }

        BtConnector {
            id: btConnector

            onConnectedChanged: {
                connectButton.text = connected ? "Disconnect" : "Connect"
                connectButton.enabled = true
            }

            onDataReceived: btDataProcessor.processData(data)
        }

        BtDataProcessor {
            id: btDataProcessor

            onDataUpdated: {
                if (debugOutput) {
                    console.log(data)
                }
            }

            onAChanged: uinputAdapter.emitClick(keyCodeA, val)
            onBChanged: uinputAdapter.emitClick(keyCodeB, val)
            onCChanged: uinputAdapter.emitClick(keyCodeC, val)
            onDChanged: uinputAdapter.emitClick(keyCodeD, val)
            onUpChanged: uinputAdapter.emitClick(keyCodeUp, val)
            onDownChanged: uinputAdapter.emitClick(keyCodeDown, val)
            onLeftChanged: uinputAdapter.emitClick(keyCodeLeft, val)
            onRightChanged: uinputAdapter.emitClick(keyCodeRight, val)
//            onDChanged: {
//                if (useLocalUinput) {
//                    uinputAdapter.emitClick(UinputAdapter.D, val)
//                }

//                if (useGlobalUinput) {
//                    if (secondGlobalUinput) {
//                        globalUinputAdapter.emitClick(UinputAdapter.H, val)
//                    } else {
//                        globalUinputAdapter.emitClick(UinputAdapter.D, val)
//                    }
//                }
//            }

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
                useLocalUinput = readBoolean("zeemote_" + n + "_useLocalUinput", false)
                useGlobalUinput = readBoolean("zeemote_" + n + "_useGlobalUinput", true)
                setKeyCodes()
            }
        }

        UinputAdapter {
            id: localUinputAdapter
        }
    }
}
