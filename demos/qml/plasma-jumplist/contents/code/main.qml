import Qt 4.7
import org.gnome.zeitgeist 0.1
import org.kde.plasma.core 0.1 as PlasmaCore

Item {
    width: 800
    height: 460

    PlasmaCore.DataModel {
        dataSource: PlasmaCore.DataSource {
            engine: "tasks"
        }
        keyRoleFilter: "\\d+"
        id: source
    }

    ListView {
        anchors.fill: parent
        model: source
        delegate: Text {
            text: visibleName
        }
    }
}
