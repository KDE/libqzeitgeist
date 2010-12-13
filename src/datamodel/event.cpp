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


#include "QtZeitgeist/DataModel/Event"

#include <QMetaType>
#include <QDBusMetaType>
#include <QDateTime>


namespace QtZeitgeist
{

namespace DataModel
{

class EventPrivate
{
public :

    quint64 id;
    QDateTime timestamp;
    QString interpretation;
    QString manifestation;
    QString actor;
    QList<QStringList> subjects;
    QByteArray payload;
};

Event::Event(QObject *parent)
    : d(new EventPrivate())
{
    Q_ASSERT(d);
}

Event::Event(const Event & source, QObject *parent)
    : d(new EventPrivate())
{
    Q_ASSERT(d);

    d->id = source.d->id;
    d->timestamp = source.d->timestamp;
    d->interpretation = source.d->interpretation;
    d->manifestation = source.d->manifestation;
    d->actor = source.d->actor;
    d->subjects = source.d->subjects;
    d->payload = source.d->payload;
}

Event::~Event()
{
    delete d;
}

Event &Event::operator = (const Event & source)
{
    if (this != &source) {
        d->id = source.d->id;
        d->timestamp = source.d->timestamp;
        d->interpretation = source.d->interpretation;
        d->manifestation = source.d->manifestation;
        d->actor = source.d->actor;
        d->subjects = source.d->subjects;
        d->payload = source.d->payload;
    }

    return *this;
}


QDBusArgument & operator << (QDBusArgument &argument, const Event &event)
{
    argument.beginStructure();

    argument
        << event.d->id
        << event.d->timestamp
        << event.d->interpretation
        << event.d->manifestation
        << event.d->actor
        << event.d->subjects
        << event.d->payload;

    return argument;
}

const QDBusArgument & operator >> (const QDBusArgument &argument, Event &event)
{
    argument.beginStructure();

    argument
        >> event.d->id
        >> event.d->timestamp
        >> event.d->interpretation
        >> event.d->manifestation
        >> event.d->actor
        >> event.d->subjects
        >> event.d->payload;

    argument.endStructure();

    return argument;
}

};

};
