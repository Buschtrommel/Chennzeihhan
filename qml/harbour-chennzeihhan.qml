import QtQuick 2.0
import Sailfish.Silica 1.0
import "Views"

ApplicationWindow
{
    id: chennzeihhan

    property bool dataBaseExists: dbMan.checkDB()
    property int installedDbRevision: dlMan.getLocalDBVersion()
    property int minimumDbRevision: 3

    Connections {
        target: dlMan
        onDbDownloadFinished: { checkDbTimer.start(); installedDbRevision = dlMan.getLocalDBVersion() }
    }

    Timer {
        id: checkDbTimer; interval: 200; running: false; repeat: false
        onTriggered: dataBaseExists = dbMan.checkDB()
    }

    initialPage: Component { MainView { } }
    cover: Qt.resolvedUrl("Pages/CoverPage.qml")

    QtObject {
        id: coverConnector

        property string country
        property string name
        property string sign
        property string state
        property string mode: "overview"
    }


    Connections {
        target: pageStack
        onCurrentPageChanged: { coverConnector.mode = pageStack.currentPage.objectName === "ItemView" ? "item" : "overview" }
    }
}


