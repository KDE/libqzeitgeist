/*
 * This file is part of QtZeitgeist.
 *
 * Copyright (C) 2009 Collabora Ltd. <http://www.collabora.co.uk/>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */


#ifndef QTZEITGEIST_EVENT_H_
#define QTZEITGEIST_EVENT_H_

#include <QList>
#include <QDateTime>
#include <QMetaType>
#include <QDBusArgument>

namespace QtZeitgeist
{

namespace DataModel
{

class EventPrivate;

class Q_DECL_EXPORT Event : public QObject
{
Q_OBJECT

public:

    explicit Event(QObject *parent = 0);
    Event(const Event &source, QObject *parent = 0);
    virtual ~Event();

    quint32 id() const;
    void setId(quint32 id);

    QDateTime timestamp() const;
    void setTimestamp(const QDateTime &timestamp);

    QString interpretation() const;
    void setInterpretation(const QString &interpretation);

    QString manifestation() const;
    void setManifestation(const QString &manifestation);

    QString actor() const;
    void setActor(const QString &actor);

    QList<QStringList> subjects() const;
    void setSubjects(const QList<QStringList> &subjects);

    QByteArray payload() const;
    void setPayload(const QByteArray &payload);

    Event & operator = (const Event &source);

private:

    class EventPrivate * const d;

    friend QDBusArgument & operator << (QDBusArgument &argument,
            const Event &event);
    friend const QDBusArgument & operator >> (const QDBusArgument &argument,
            Event &event);
};

typedef QList<Event> EventList;
typedef QList<quint32> EventIdList;

};

};

Q_DECLARE_METATYPE(QtZeitgeist::DataModel::Event)
Q_DECLARE_METATYPE(QtZeitgeist::DataModel::EventList)
Q_DECLARE_METATYPE(QtZeitgeist::DataModel::EventIdList)

#endif // QTZEITGEIST_EVENT_H_
