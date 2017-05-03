import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")
    Connections {
        target: g_cls_thread_serial_port_ir
        onSignal_send_to_qml: {
//            console.log(msg)
            lbl_message.text = msg
            //            txt_debug_message.text = msg + "\r\n------------" +  txt_debug_message.text + "\r\n"
            //            txt_debug_message.text = get_short_text(txt_debug_message.text , 1000)
        }
    }



    SwipeView {
        id: swipeView
        anchors.fill: parent
        currentIndex: tabBar.currentIndex

        Page {

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
