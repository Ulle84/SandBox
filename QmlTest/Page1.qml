import QtQuick 2.7

Page1Form {
    button1.onClicked: {
        console.log("Button Pressed. Entered text 1: " + textField1.text);
        console.log("Button Pressed. Entered text 2: " + textField2.text);
    }
}
