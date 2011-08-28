#include "declarativelogmodel.h"
#include "declarativeevent.h"

namespace QZeitgeist
{
namespace Declarative
{

LogModel::LogModel(QObject *parent)
    : QZeitgeist::LogModel(parent)
{
    QHash<int, QByteArray> roles;
    roles[EventRole] = "event";
    setRoleNames(roles);
}

QVariant LogModel::data(const QModelIndex &idx, int role) const
{
    if (role == EventRole) {
        QZeitgeist::DataModel::Event evt = QZeitgeist::LogModel::data(idx, role).value<QZeitgeist::DataModel::Event>();
        return QVariant::fromValue<QZeitgeist::Declarative::Event*>(new QZeitgeist::Declarative::Event(evt));
    }
    return QZeitgeist::LogModel::data(idx, role);
}

QZeitgeist::Declarative::Event *LogModel::templateEvent() const
{
    return new QZeitgeist::Declarative::Event(eventTemplates()[0]);
}

void LogModel::setTemplateEvent(QZeitgeist::Declarative::Event *evt)
{
    QZeitgeist::DataModel::EventList list;
    list << evt->event();
    setEventTemplates(list);
    emit templateEventChanged();
}

void LogModel::componentComplete()
{
    refresh();
}

void LogModel::classBegin()
{

}

} // namespace Declarative
} // namespace QZeitgeist
