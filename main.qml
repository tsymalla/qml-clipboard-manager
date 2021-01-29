import QtQuick 2.15
import QtQuick.Controls 2.15

ApplicationWindow {
    width: 640
    height: 480
    visible: true
    title: qsTr("Clipboard Manager")

    ScrollView {
        anchors.fill: parent

        ListView {
            id: listView
            width: parent.width
            model: clipboard.content
            delegate: ItemDelegate {
                text: "Clipboard entry #" + (clipboard.content.length - index) + ": " + clipboard.content[index]
                width: listView.width
            }
        }
    }
}
