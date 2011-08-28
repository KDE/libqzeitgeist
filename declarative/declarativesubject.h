#ifndef DECLARATIVESUBJECT_H
#define DECLARATIVESUBJECT_H

#include <QtCore/QObject>
#include "DataModel/subject.h"

namespace QZeitgeist
{
namespace Declarative
{

class Subject : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString interpretation READ interpretation WRITE setInterpretation NOTIFY interpretationChanged);
    Q_PROPERTY(QString text READ text WRITE setText NOTIFY textChanged);
    public:
        Subject(QObject *parent = 0);
        Subject(const QZeitgeist::DataModel::Subject &subject, QObject *parent = 0);
        QString interpretation() const;
        void setInterpretation(const QString &interp);
        QZeitgeist::DataModel::Subject subject() const;

        QString text() const;
        void setText(const QString &text);

    signals:
        void interpretationChanged();
        void textChanged();

    private:
        QZeitgeist::DataModel::Subject m_subject;
};

} // namespace Declarative
} // namespace QZeitgeist

#endif // DECLARATIVESUBJECT_H
