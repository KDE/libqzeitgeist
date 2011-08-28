#include "declarativesubject.h"

namespace QZeitgeist
{
namespace Declarative
{

Subject::Subject(QObject *parent)
    : QObject(parent)
{

}

Subject::Subject(const QZeitgeist::DataModel::Subject &subject, QObject *parent)
    : QObject(parent)
{
    m_subject = subject;
}

QString Subject::interpretation() const
{
    return m_subject.interpretation();
}

void Subject::setInterpretation(const QString &interp)
{
    m_subject.setInterpretation(interp);
    emit interpretationChanged();
}

QZeitgeist::DataModel::Subject Subject::subject() const
{
    return m_subject;
}

void Subject::setText(const QString &text)
{
    m_subject.setText(text);
    emit textChanged();
}

QString Subject::text() const
{
    return m_subject.text();
}

} // namespace Declarative
} // namespace QZeitgeist
