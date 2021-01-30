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
            model: clipboard.model

            header: Label {
                font.pixelSize: 16
                font.bold: true
                elide: Label.ElideRight
                width: ListView.view.width
                padding: {
                    left: 14
                }

                text: "Number of entries in clipboard: " + clipboard.entryCount
            }

            delegate: ItemDelegate {
                required property string type
                required property string data
                required property string dateTime

                text: (type == "image" ? "Image" : data) + "\n" + "Created: " + dateTime
                width: listView.width

            }
        }
    }
}
