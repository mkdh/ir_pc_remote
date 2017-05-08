import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import QtQuick.Window 2.2

ApplicationWindow {
    id: root_app

    visible: true
    property real root_width: width
    property real root_height: height
    width: 640
    height: Screen.height * 0.8
    title: qsTr("Hello World")

    Connections {
        target: g_cls_thread_serial_port_ir
        onSignal_send_to_qml: {
            root_app.title = "<" + msg + ">"
        }
    }
    Component.onCompleted: {
        g_cls_thread_serial_port_ir.slot_open_serial_port();
    }

    property variant list_commands: []

    SwipeView {
        id: swipeView
        anchors.fill: parent
        currentIndex: tabBar.currentIndex

        Page {
            Button {
                id: btn_open_serial_port
                text: "btn_open_serial_port"
                onClicked: {
                    g_cls_thread_serial_port_ir.slot_open_serial_port();
                }
            }
            Button {
                text: "btn_test"

                anchors.left: btn_open_serial_port.right
                onClicked: {

                }
            }
            ListModel {
                id: contactModel
                ListElement {
                    cmd_name: " other"
                    key_press: ""
                }
                ListElement {
                    cmd_name: " FORWARD"
                    key_press: "Up"
                }
                ListElement {
                    cmd_name: ""
                    key_press: ""
                }
                ListElement {
                    cmd_name: " LEFT"
                    key_press: "Left"
                }
                ListElement {
                    cmd_name: " -OK-"
                    key_press: "Enter"
                }
                ListElement {
                    cmd_name: " RIGHT"
                    key_press: "Right"
                }

                ListElement {
                    cmd_name: ""
                    key_press: ""
                }
                ListElement {
                    cmd_name: " REVERSE"
                    key_press: "Down"
                }
                ListElement {
                    cmd_name: ""
                    key_press: ""
                }
                ListElement {
                    cmd_name: " 1"
                    key_press: ""
                }
                ListElement {
                    cmd_name: " 2"
                    key_press: "PgUp"
                }
                ListElement {
                    cmd_name: " 3"
                    key_press: ""
                }
                ListElement {
                    cmd_name: " 4"
                    key_press: "Left"
                }
                ListElement {
                    cmd_name: " 5"
                    key_press: "PgDn"
                }
                ListElement {
                    cmd_name: " 6"
                    key_press: "Right"
                }
                ListElement {
                    cmd_name: " 7"
                    key_press: ""
                }
                ListElement {
                    cmd_name: " 8"
                    key_press: ""
                }
                ListElement {
                    cmd_name: " 9"
                    key_press: ""
                }
                ListElement {
                    cmd_name: " *"
                    key_press: "Space"
                }
                ListElement {
                    cmd_name: "0"
                    key_press: ""
                }
                ListElement {
                    cmd_name: " #"
                    key_press: ""
                }
            }
            Flickable {
                id: flickable
                anchors.top: btn_open_serial_port.bottom
                height: root_app.root_height - gv_remote.y - tabBar.height
                anchors.left:gv_remote.right
                width: root_app.root_width - gv_remote.width

                TextArea.flickable: TextArea {

                    text: {
                        var str_test = "This is the test text. "
                        var str_content = ""
                        for(var i = 0 ; i< 500 ; i++ )
                        {
                            str_content += str_test
                        }
                        return str_content
                    }
                    wrapMode: Text.Wrap

                }

                ScrollBar.vertical: ScrollBar { }
            }


            GridView {
                id: gv_remote

                anchors.top: btn_open_serial_port.bottom
//                anchors.bottom: tabBar.top
                width: 300;
                height: root_app.root_height - gv_remote.y - tabBar.height
                cellWidth : width * 0.333
                cellHeight: height / 7
                model: contactModel
                delegate: Rectangle {
                    id: rect_remote_btn
                    width: gv_remote.cellWidth
                    height: gv_remote.cellHeight
                    color: "green"
                    border.width: 1
                    property string str_cmd: txt_cmd.text
                    property string str_key_press: txt_key_press.text
                    Column {
                        anchors.centerIn: parent
                        Text {
                            id:txt_cmd ;
                            text: cmd_name;
                            onTextChanged: {
                                str_cmd = txt_cmd.text

                            }

                            anchors.horizontalCenter: parent.horizontalCenter
                        }
                        Text {
                            id:txt_key_press ;
                            color: "yellow"
                            text: key_press;
                            onTextChanged: {
                                str_key_press = txt_key_press.text
                                console.log("sdfsdfsd " + str_key_press)
                            }

                            anchors.horizontalCenter: parent.horizontalCenter
                        }
                    }
                    MouseArea {
                        anchors.fill: rect_remote_btn
                        onClicked: {
                            rect_select_menu.visible = true

                        }
                    }

                    Rectangle {
                        id: rect_select_menu
                        width: gv_remote.cellWidth
                        height: gv_remote.cellHeight
                        color:"red"
                        visible: false
                        border.width: 1
                        GridView {
                            anchors.fill: rect_select_menu
                            cellWidth : gv_remote.cellWidth / 2
                            cellHeight:rect_select_menu.height / list_key_press_menu.count * 2
                            model:  ListModel {
                                id: list_key_press_menu
                                ListElement {
                                    txt_key_board:"Up"
                                }
                                ListElement {
                                    txt_key_board:"Down"
                                }
                                ListElement {
                                    txt_key_board:"Right"
                                }
                                ListElement {
                                    txt_key_board:"Left"
                                }
                                ListElement {
                                    txt_key_board:"Space"
                                }
                                ListElement {
                                    txt_key_board:"Enter"
                                }
                                ListElement {
                                    txt_key_board:"PgUp"
                                }
                                ListElement {
                                    txt_key_board:"PgDn"
                                }

                                ListElement {
                                    txt_key_board:""
                                }
                            }

                            delegate: Rectangle {
                                width: rect_select_menu.width / 2;
                                height: rect_select_menu.height / list_key_press_menu.count * 2
                                color: "yellow"
                                border.width: 1
                                Text {
                                    id: txt_key_press_menu
                                    text: qsTr(txt_key_board)
                                }
                                MouseArea{
                                    anchors.fill: parent
                                    onClicked: {
                                        rect_select_menu.visible = false
                                        if(txt_key_board != "")
                                        {
                                            txt_key_press.text = txt_key_board
                                        }
                                        root_app.list_commands = []
                                        for(var i = 0; i < gv_remote.count ; i++ )
                                        {
                                            var _cmd = gv_remote.contentItem.children[i].str_cmd
                                            var _key_press = gv_remote.contentItem.children[i].str_key_press
                                            if(_cmd != "")
                                            {
                                                root_app.list_commands.push(_cmd)
                                                root_app.list_commands.push(_key_press)
                                            }
                                        }
                                        g_cls_thread_serial_port_ir.slot_set_command(root_app.list_commands)
                                    }
                                }
                            }
                        }
                    }
                }
            }


        }

        Page {
            Label {
                id: lbl_message
                text: qsTr("OK --> Enter\r\n* ---> Space")
                anchors.centerIn: parent
            }
        }
    }

    footer: TabBar {
        id: tabBar
        currentIndex: swipeView.currentIndex
        TabButton {
            text: qsTr("First")
        }
        TabButton {
            text: qsTr("Second")
        }
    }
}
