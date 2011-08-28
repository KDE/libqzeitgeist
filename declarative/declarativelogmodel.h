#ifndef DECLARATIVE_LOGMODEL_H
#define DECLARATIVE_LOGMODEL_H

#include "logmodel.h"
#include <QtDeclarative/QDeclarativeParserStatus>

namespace QZeitgeist
{
namespace Declarative
{

class Event;

class LogModel : public QZeitgeist::LogModel, public QDeclarativeParserStatus
{
    Q_OBJECT
    Q_INTERFACES(QDeclarativeParserStatus)
    Q_PROPERTY(QZeitgeist::Declarative::Event* templateEvent READ templateEvent WRITE setTemplateEvent NOTIFY templateEventChanged);
    public:
        LogModel(QObject *parent = 0);
        QVariant data(const QModelIndex &idx, int role = Qt::DisplayRole) const;
        QZeitgeist::Declarative::Event *templateEvent() const;
        void setTemplateEvent(QZeitgeist::Declarative::Event *evt);

        void componentComplete();
        void classBegin();

    signals:
        void templateEventChanged();
};

} // namespace Declarative
} // namespace QZeitgeist

#endif // DECLARATIVE_LOGMODEL_H
