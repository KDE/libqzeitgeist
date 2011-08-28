#include "declarativeevent.h"
#include "declarativesubject.h"

namespace QZeitgeist
{
namespace Declarative
{

Event::Event(QObject *parent)
    : QObject(parent)
{
}

Event::Event(const QZeitgeist::DataModel::Event &event, QObject *parent)
    : QObject(parent)
{
    m_event = event;
    foreach (const QZeitgeist::DataModel::Subject &subject, event.subjects()) {
        m_subjects << new Subject(subject, this);
    }
}

int Event::id() const
{
    return m_event.id();
}

QDateTime Event::timestamp() const
{
    return m_event.timestamp();
}

void appendSubject(QDeclarativeListProperty<QZeitgeist::Declarative::Subject> *property, QZeitgeist::Declarative::Subject *subject)
{
    Event *that = static_cast<Event*>(property->object);
    that->addSubject(subject);
}

int countSubjects(QDeclarativeListProperty<QZeitgeist::Declarative::Subject> *property)
{
    Event *that = static_cast<Event*>(property->object);
    return that->subjectCount();
}

QZeitgeist::Declarative::Subject* getSubject(QDeclarativeListProperty<QZeitgeist::Declarative::Subject> *property, int idx)
{
    Event *that = static_cast<Event*>(property->object);
    return that->at(idx);
}

QDeclarativeListProperty<QZeitgeist::Declarative::Subject> Event::subjects()
{
    return QDeclarativeListProperty<QZeitgeist::Declarative::Subject>(this, 0, appendSubject, countSubjects, getSubject);
}

int Event::subjectCount() const
{
    return m_event.subjects().size();
}

QZeitgeist::Declarative::Subject *Event::at(int idx) const
{
    return m_subjects[idx];
}

QZeitgeist::DataModel::Event Event::event() const
{
    QZeitgeist::DataModel::SubjectList subjects;
    QZeitgeist::DataModel::Event event(m_event);
    foreach (const QZeitgeist::Declarative::Subject *subject, m_subjects) {
        subjects << subject->subject();
    }
    event.setSubjects(subjects);
    return event;
}

void Event::addSubject(QZeitgeist::Declarative::Subject *s)
{
    m_subjects << s;
    emit subjectsChanged();
}

} // namespace Declarative
} // namespace QZeitgeist
