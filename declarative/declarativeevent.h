#ifndef DECLARATIVE_EVENT_H
#define DECLARATIVE_EVENT_H

#include <QtCore/QObject>
#include <QtDeclarative/QDeclarativeListProperty>
#include <QtDeclarative>
#include "DataModel/event.h"

namespace QZeitgeist
{
namespace Declarative
{

class Subject;

class Event : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int id READ id CONSTANT);
    Q_PROPERTY(QDateTime timestamp READ timestamp CONSTANT);
    Q_PROPERTY(QDeclarativeListProperty<QZeitgeist::Declarative::Subject> subjects READ subjects NOTIFY subjectsChanged);
    Q_CLASSINFO("DefaultProperty", "subjects");
    public:
        Event(QObject *parent = 0);
        Event(const QZeitgeist::DataModel::Event &event, QObject *parent = 0);
        int id() const;
        QDateTime timestamp() const;
        QDeclarativeListProperty<QZeitgeist::Declarative::Subject> subjects();
        void addSubject(QZeitgeist::Declarative::Subject *s);
        QZeitgeist::DataModel::Event event() const;
        int subjectCount() const;
        QZeitgeist::Declarative::Subject *at(int idx) const;

    signals:
        void subjectsChanged();

    private:
        QList<QZeitgeist::Declarative::Subject*> m_subjects;
        QZeitgeist::DataModel::Event m_event;
};

} // namespace Declarative
} // namespace QZeitgeist

QML_DECLARE_TYPE(QZeitgeist::Declarative::Event);

#endif // DECLARATIVE_EVENT_H
