import QtQuick 2.15
import QtQuick.Controls 2.15

ApplicationWindow {
    id: window

    width: 400
    height: 300
    visible: true
    title: qsTr("Clipboard Manager")

    ListView {
        id: listView
        model: clipboard.model
        anchors.fill: parent

        flickableDirection: Flickable.HorizontalAndVerticalFlick
        contentWidth: listView.contentItem.childrenRect.width + 16

        ScrollBar.vertical: ScrollBar {
            active: true
        }

        ScrollBar.horizontal: ScrollBar {
            active: true
        }

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

        delegate: Row {
            required property int index
            required property string type
            required property string content
            required property string dateTime

            leftPadding: 14
            id: rowDelegate

            Column {
                Rectangle {
                    id: dataType
                    width: 24
                    height: 24
                    radius: 16
                    border.color: "white"
                    color: (type == "image" ? "green" : "blue")

                    MouseArea {
                        id: dataTypeMouseArea
                        anchors.fill: parent
                        hoverEnabled: true

                        ToolTip {
                            visible: dataTypeMouseArea.containsMouse
                            Text {
                                text: (type == "image" ? "Image file" : "Text")
                            }
                        }
                    }
                }
            }

            Column {
                leftPadding: 14

                Label {
                    width: listView.width
                    visible: (type != "image")
                    text: content.trim()
                    wrapMode: "WordWrap"
                }

                Image {
                    width: 140
                    fillMode: Image.PreserveAspectFit
                    visible: (type == "image")
                    source: (type == "image" ? "data:image/png;base64," + content : "")
                }

                Label {
                    topPadding: 14
                    font.italic: true
                    font.pixelSize: 12
                    color: "silver"
                    text: dateTime
                }

                Button {
                    onClicked: {
                        listView.currentIndex = index
                        clipboard.setClipboardEntry(listView.currentIndex)
                        notifi
                    }

                    width: 130
                    height: 40

                    Label {
                        anchors.centerIn: parent
                        text: "Copy to clipboard"
                    }
                }
            }
        }
    }
}
