import QtQuick 2.2
import QtQuick.Controls 1.1
import QtQuick.Layouts 1.1
import Examples.FizzBuzz 0.1

ApplicationWindow {
    visible: true
    width: 200
    height: 200
    title: "FizzBuzz"

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 10
        TextField {
            placeholderText: "Input"
            text: ""
            id: textField
        }
        Text {
            id: text
            text: "Last result: " + fizzBuzz.result
        }
        Button {
            text: 'Quit'
            onClicked: fizzBuzz.quit()
        }
        Text {
            id: lastFizzBuzz
        }
    }
    FizzBuzz {
        id: fizzBuzz
        input: textField.text
        onInputWasFizzBuzz: lastFizzBuzz.text = "Last FizzBuzz: " + fizzBuzz.input
    }
}
