#include <QZeitgeist/Log>
#include <QtCore/QTextStream>
#include <stdio.h>

using namespace QZeitgeist;

int main(int argc, char** argv)
{
    QTextStream cout(stdout, QIODevice::WriteOnly);
    Log *log = new Log();
    
    // An empty time range matches anything
    DataModel::TimeRange timeRange;

    // Same for an empty event template
    DataModel::EventList eventTemplates;
    eventTemplates << DataModel::Event();

    // Query the log for 10 results
    DataModel::EventList events = log->findEvents(timeRange, eventTemplates, Log::Any, 10, Log::MostRecentEvents).value();

    // Print out all the attributes
    foreach (const DataModel::Event &evt, events) {
        cout << "Event #" << evt.id() << ":" << "\n";
        cout << "\tWhen: " << evt.timestamp().toString() << "\n";
        cout << "\tActor: " << evt.actor() << "\n";
        cout << "\tOrigin: " << evt.origin() << "\n";
        cout << "\tInterpretaton: " << evt.interpretation() << "\n";
        cout << "\tManifestation: " << evt.manifestation() << "\n";
        foreach (const DataModel::Subject &subj, evt.subjects()) {
            cout << "\tText: " << subj.text() << "\n";
            cout << "\tURI: " << subj.uri() << "\n";
            cout << "\tInterpretaton: " << subj.interpretation() << "\n";
            cout << "\tManifestation: " << subj.manifestation() << "\n";
            cout << "\tMime type: " << subj.mimeType() << "\n";
        }
    }

    return 0;
}
