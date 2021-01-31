import QtQuick 2.15
import QtQuick.Controls 2.15

ApplicationWindow {
    id: window

    width: 400
    height: 300
    visible: true
    title: qsTr("Clipboard Manager")

    ScrollView {
        anchors.fill: parent

        ListView {
            id: listView
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

            delegate: Row  {
                required property string type
                required property string content
                required property string dateTime

                width: parent.width

                padding: {
                    left: 14
                }

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
                    width: parent.width

                    leftPadding: 14

                    Label {
                        visible: (type != "image")
                        text: content.trim()
                    }

                    Image {
                        height: 64
                        width: 64
                        visible: (type == "image")
                        source: (type == "image" ? "data:image/png;base64," + content : "")
                    }

                    Label {
                        topPadding: 14
                        font.italic: true
                        font.pixelSize: 14
                        color: "gray"
                        text: "Created on: " + dateTime
                    }

                    Button {
                        onClicked: {
                            clipboard.setClipboardEntry(index)
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
}
