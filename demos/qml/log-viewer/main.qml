import Qt 4.7;
import org.gnome.zeitgeist 0.1;

ListView {
    width: 600
    height: 480
    anchors.fill: parent

    Event {
        id: audioFilter
        Subject {
            interpretation: "http://www.semanticdesktop.org/ontologies/2007/03/22/nfo#Audio"
        }
    }

    Event {
        id: videoFilter
        Subject {
            interpretation: "http://www.semanticdesktop.org/ontologies/2007/03/22/nfo#Video"
        }
    }

    model: LogModel {
        templateEvent: videoFilter
    }

    delegate: Item {
        width: childrenRect.width+10
        height: childrenRect.height+10
        Rectangle {
            width: childrenRect.width
            height: childrenRect.height
            anchors.centerIn: parent
            color: "steelblue"
            Column {
                spacing: 5
                Repeater {
                    model: event.subjects
                    delegate: Column {
                        Text {
                            text: modelData.text
                        }
                        Text {
                            text: modelData.interpretation
                        }
                        Text {
                            text: modelData.manifestation
                        }
                    }
                }
            }
        }
    }
}
