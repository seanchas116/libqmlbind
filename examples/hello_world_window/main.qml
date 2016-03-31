import QtQuick 2.2
import QtQuick.Controls 1.4

ApplicationWindow {
    visible: true
    title: "libqmlbind's Example Window"
    width: 600
    height: 400

    Label {
        anchors.centerIn: parent
        id: helloworld
        text: "Hello, World!"
    }
}
