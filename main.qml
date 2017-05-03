import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

ApplicationWindow {
    id: root_app
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")
    Connections {
        target: g_cls_thread_serial_port_ir
        onSignal_send_to_qml: {
            root_app.title = msg
            lbl_message.text = lbl_message.text + "\r\n" + msg
            //            txt_debug_message.text = msg + "\r\n------------" +  txt_debug_message.text + "\r\n"
            //            txt_debug_message.text = get_short_text(txt_debug_message.text , 1000)
        }
    }
    Component.onCompleted: {
        g_cls_thread_serial_port_ir.slot_open_serial_port();
    }


    SwipeView {
        id: swipeView
        anchors.fill: parent
        currentIndex: tabBar.currentIndex

        Page {
            Button {
                onClicked: {
                    g_cls_thread_serial_port_ir.slot_open_serial_port();
                }
            }

            Label {
                id: lbl_message
                text: qsTr("First page")
                anchors.centerIn: parent
            }

        }

        Page {
            Label {
                text: qsTr("Second page")
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
