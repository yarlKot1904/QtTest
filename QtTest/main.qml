import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.2

Window {
    visible: true
    width: 640
    height: 480
    title: "QtTest"

    Column {
        anchors.centerIn: parent
        spacing: 10

        TextField {
            id: inputMask
            placeholderText: "Input mask"
            text: "*.txt" 
        }

        CheckBox {
            id: deleteInputFiles
            text: "Delete input files"
            checked: false 
        }

        TextField {
            id: outputPath
            placeholderText: "Output path"
            text: "output"
        }

        CheckBox {
            id: overwriteOutput
            text: "Overwrite output files"
            checked: true 
        }

        TextField {
            id: periodicity
            placeholderText: "Periodicity (ms)"
            text: "1000"
        }

        TextField {
            id: binaryValue
            placeholderText: "Binary value (8 bytes, hex format)"
            inputMask: "HHHHHHHHHHHHHHHH"
            text: "1122334455667788"
        }

        ComboBox {
            id: runMode
            model: ["Run Once", "Run Periodically"]
            currentIndex: 0
        }

        Button {
            text: "Start"
            onClicked: {
                modifier.setInputMask(inputMask.text)
                modifier.setDeleteInputFiles(deleteInputFiles.checked)
                modifier.setOutputPath(outputPath.text)
                modifier.setOverwriteOutput(overwriteOutput.checked)
                modifier.setPeriodicity(parseInt(periodicity.text))
                modifier.setBinaryValue(binaryValue.text)
                modifier.setRunOnce(runMode.currentIndex === 0)
                modifier.start()
            }
        }
    }
}