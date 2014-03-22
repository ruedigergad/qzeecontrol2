import QtQuick 2.2
import QtQuick.Controls 1.1
import QZeeControl 2.0

Tab {
    id: zeeControlTab

    property string address
    property bool debugOutput: false
    property int n: 1

    property QtObject uinputAdapter: null

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

    Rectangle {
        anchors.fill: parent

        color: "lightgray"

        function setKeyCodes() {
            var suffix = useAlternateMappingCheckBox.checked ? "_alternateMapping" : ""
            keyCodeA = settingsAdapter.readInt("zeemote_" + n + "_keycode_A" + suffix, UinputAdapter.A)
            keyCodeB = settingsAdapter.readInt("zeemote_" + n + "_keycode_B" + suffix, UinputAdapter.B)
            keyCodeC = settingsAdapter.readInt("zeemote_" + n + "_keycode_C" + suffix, UinputAdapter.C)
            keyCodeD = settingsAdapter.readInt("zeemote_" + n + "_keycode_D" + suffix, UinputAdapter.D)
            keyCodeUp = settingsAdapter.readInt("zeemote_" + n + "_keycode_UP" + suffix, UinputAdapter.UP)
            keyCodeDown = settingsAdapter.readInt("zeemote_" + n + "_keycode_DOWN" + suffix, UinputAdapter.DOWN)
            keyCodeLeft = settingsAdapter.readInt("zeemote_" + n + "_keycode_LEFT" + suffix, UinputAdapter.LEFT)
            keyCodeRight = settingsAdapter.readInt("zeemote_" + n + "_keycode_RIGHT" + suffix, UinputAdapter.RIGHT)
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
                            text = "Connecting..."
                        } else {
                            btConnector.disconnect()
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

            Row {
                id: configRow1
                anchors.horizontalCenter: parent.horizontalCenter

                spacing: 20

                CheckBox {
                    id: useGlobalUinputCheckBox
                    text: "Global Uinput"
                    onCheckedChanged: {
                        if (checked) {
                            uinputAdapter = globalUinputAdapter
                        } else {
                            if (uinputAdapter === globalUinputAdapter) {
                                uinputAdapter = null
                            }
                        }
                        settingsAdapter.setBoolean("zeemote_" + n + "_useGlobalUinput", checked)
                    }
                }

                CheckBox {
                    id: useLocalUinputCheckBox
                    text: "Local Uinput"
                    onCheckedChanged: {
                        if (checked) {
                            localUinputAdapter.createDevice("Zeemote_" + n)
                            uinputAdapter = localUinputAdapter
                        } else {
                            if (uinputAdapter === localUinputAdapter) {
                                uinputAdapter = null
                                localUinputAdapter.destroyDevice()
                            }
                        }
                        settingsAdapter.setBoolean("zeemote_" + n + "_useLocalUinput", checked)
                    }
                }

                CheckBox {
                    id: useAlternateMappingCheckBox
                    text: "Alternate Mapping"
                    onCheckedChanged: {
                        settingsAdapter.setBoolean("zeemote_" + n + "_useAlternateMapping", checked)
                    }
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

            onAChanged: if (uinputAdapter !== null) uinputAdapter.emitClick(keyCodeA, val)
            onBChanged: if (uinputAdapter !== null) uinputAdapter.emitClick(keyCodeB, val)
            onCChanged: if (uinputAdapter !== null) uinputAdapter.emitClick(keyCodeC, val)
            onDChanged: if (uinputAdapter !== null) uinputAdapter.emitClick(keyCodeD, val)
            onUpChanged: if (uinputAdapter !== null) uinputAdapter.emitClick(keyCodeUp, val)
            onDownChanged: if (uinputAdapter !== null) uinputAdapter.emitClick(keyCodeDown, val)
            onLeftChanged: if (uinputAdapter !== null) uinputAdapter.emitClick(keyCodeLeft, val)
            onRightChanged: if (uinputAdapter !== null) uinputAdapter.emitClick(keyCodeRight, val)

            onStickMoved: {
                if (debugOutput) {
                    console.log("x: " + x + "   y: " + y)
                }

                if (uinputAdapter !== null) {
                    if (useAlternateMappingCheckBox.checked) {
                        uinputAdapter.emitRxRyEvent(x, y)
                    } else {
                        uinputAdapter.emitXYEvent(x, y)
                    }
                }
            }
        }

        SettingsAdapter {
            id: settingsAdapter

            Component.onCompleted: {
                zeeControlTab.address = readString("ZeemoteAddress_" + n, "")
                useLocalUinputCheckBox.checked = readBoolean("zeemote_" + n + "_useLocalUinput", false)
                useGlobalUinputCheckBox.checked = readBoolean("zeemote_" + n + "_useGlobalUinput", true)
                useAlternateMappingCheckBox.checked = readBoolean("zeemote_" + n + "_useAlternateMapping", false)
                setKeyCodes()
            }
        }

        UinputAdapter {
            id: localUinputAdapter
        }
    }
}
