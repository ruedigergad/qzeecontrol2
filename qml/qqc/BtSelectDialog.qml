import QtQuick 2.2
import QtQuick.Controls 1.1
import QtBluetooth 5.2
import QZeeControl 2.0

Rectangle {
    id: btSelectDialog

    property Item parentTab

    Column {
        anchors.fill: parent

        Button {
            id: scanButton

            anchors.horizontalCenter: parent.horizontalCenter
            text: btDiscoveryModel.running ? "Scanning..." : "Scan"

            onClicked: {
                btDiscoveryModel.running = !btDiscoveryModel.running
            }
        }

        ListView {
            id: zeeControlsListView

            anchors.horizontalCenter: parent.horizontalCenter
            height: parent.height * 0.5
            width: parent.width

            model: listModel

            delegate: Rectangle {
                color: delegateMouseArea.pressed ? "gray" : "white"
                height: delegateText.height
                width: parent.width

                Text {
                    id: delegateText

                    horizontalAlignment: Text.AlignHCenter
                    text: address
                    width: parent.width
                }

                MouseArea {
                    id: delegateMouseArea

                    anchors.fill: parent

                    onClicked: {
                        console.log("Clicked index: " + index)
                        zeeControlsListView.currentIndex = index
                    }

                    onDoubleClicked: {
                        console.log("Selected Zeemote address: " + address)
                        parentTab.address = address
                        bluez5BtAdapter.stopDiscovery()
                        mainStackView.pop()
                    }
                }
            }

            highlight: Rectangle {
                color: "gray"
                opacity: 0.5
            }
        }

        Button {
            id: cancelButton

            anchors.horizontalCenter: parent.horizontalCenter
            text: "Cancel"

            onClicked: {
                bluez5BtAdapter.stopDiscovery()
                mainStackView.pop()
            }
        }
    }

    ListModel {
        id: listModel
    }

    BluetoothDiscoveryModel {
        id: btDiscoveryModel

        discoveryMode: BluetoothDiscoveryModel.MinimalServiceDiscovery

        onDeviceDiscovered: {
            console.log("Device discovered: " + device)
        }

        onErrorChanged: {
            console.log("Error while scanning: " + error)
            switch (error) {
            case BluetoothDiscoveryModel.InputOutputError:
                console.log("I/O Error")
                console.log("Trying Bluez5...")
                listModel.clear()
                bluez5BtAdapter.startDiscovery()
                break;
            default:
                console.log("Unknown error code: " + error)
            }
        }

        onRunningChanged: {
            if(running) {
                console.log("Scanning for a Zeemote...")
                listModel.clear()
            } else {
                console.log("Scanning finished.")
            }
        }

        onServiceDiscovered: {
            console.log("Service " + service.serviceName + " found on "
                        + service.deviceName + " at address " + service.deviceAddress
                        + " on port " + service.servicePort + ".")

            if(service.serviceName !== "Zeemote")
                return

            console.log("Found Zeemote. :)")

            listModel.append({address: service.deviceAddress})
        }
    }

    Bluez5BtAdapter {
        id: bluez5BtAdapter

        onDeviceFound: listModel.append({address: address})
    }
}
