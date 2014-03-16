import QtQuick 2.2
import QtQuick.Controls 1.1

Tab {
    id: zeeControlTab

    property string address
    property int n: 1

    anchors.fill: parent
    title: "Zee " + n

    Rectangle {
        anchors.fill: parent

        color: "green"

        Column {
            anchors.fill: parent

            TextField {
                id: addressTextField

                anchors.horizontalCenter: parent.horizontalCenter
                placeholderText: "Enter Zeemote address or scan."
                text: address
                width: parent.width * 0.5
            }

            Button {
                id: scanButton

                anchors.horizontalCenter: parent.horizontalCenter
                text: "Scan"

                onClicked: {
                    mainStackView.push({item: Qt.resolvedUrl("BtSelectDialog.qml"), properties: {parentTab: zeeControlTab}})
                }
            }
        }
    }
}
