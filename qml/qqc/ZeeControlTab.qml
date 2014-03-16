import QtQuick 2.2
import QtQuick.Controls 1.1

Tab {
    id: zeeControlTab

    property int n: 1

    anchors.fill: parent
    title: "Zee " + n

    Rectangle {
        anchors.fill: parent

        color: "green"
    }
}
