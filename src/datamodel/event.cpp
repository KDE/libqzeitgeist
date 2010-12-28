/*
 * This file is part of QtZeitgeist.
 *
 * Copyright (C) 2010 Collabora Ltd. <http://www.collabora.co.uk/>
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

namespace QtZeitgeist
{

namespace DataModel
{

class EventPrivate
{
public :
    EventPrivate()
    {
        id = 0;
        timestamp.setTimeSpec(Qt::UTC);
        timestamp.setTime_t(0);
    }

    quint32 id;
    QDateTime timestamp;
    QString interpretation;
    QString manifestation;
    QString actor;
    SubjectList subjects;
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

    // Copy the source attribute's value.
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

quint32 Event::id() const
{
    return d->id;
}

QDateTime Event::timestamp() const
{
    return d->timestamp;
}

void Event::setTimestamp(const QDateTime &timestamp)
{
    d->timestamp = timestamp;
}

QString Event::interpretation() const
{
    return d->interpretation;
}

void Event::setInterpretation(const QString &interpretation)
{
    d->interpretation = interpretation;
}

QString Event::manifestation() const
{
    return d->manifestation;
}

void Event::setManifestation(const QString &manifestation)
{
    d->manifestation = manifestation;
}

QString Event::actor() const
{
    return d->actor;
}

void Event::setActor(const QString &actor)
{
    d->actor = actor;
}

SubjectList Event::subjects() const
{
    return d->subjects;
}

void Event::setSubjects(const SubjectList &subjects)
{
    d->subjects = subjects;
}

QByteArray Event::payload() const
{
    return d->payload;
}

void Event::setPayload(const QByteArray &payload)
{
    d->payload = payload;
}

void Event::addSubject(const Subject &subject)
{
    d->subjects.append(subject);
}

Event &Event::operator = (const Event & source)
{
    // Copy the source attribute's value.
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
    QStringList eventData;

    eventData
        << QString(event.d->id)
        << QString::number(event.d->timestamp.toMSecsSinceEpoch())
        << event.d->interpretation
        << event.d->manifestation
        << event.d->actor;

    QList<QStringList> subjectList;
    uint subjectsSize = event.d->subjects.size();

    for (uint i = 0; i < subjectsSize; ++i) {
        QStringList subjectData;
        Subject subject = event.d->subjects[i];;

        subjectData << subject.uri();
        subjectData << subject.interpretation();
        subjectData << subject.manifestation();
        subjectData << subject.origin();
        subjectData << subject.mimeType();
        subjectData << subject.text();
        subjectData << subject.storage();

        subjectList << subjectData;
    }

    argument.beginStructure();

    argument
        << eventData
        << subjectList
        << event.d->payload;

    argument.endStructure();

    return argument;
}

const QDBusArgument & operator >> (const QDBusArgument &argument, Event &event)
{
    QStringList eventData;
    QList<QStringList> subjectList;

    argument.beginStructure();

    argument
        >> eventData
        >> subjectList
        >> event.d->payload;

    argument.endStructure();

    if (!eventData.isEmpty()) {
        event.d->id = eventData[0].toUInt();

        event.d->timestamp.setMSecsSinceEpoch(eventData[1].toLongLong());

        event.d->interpretation = eventData[2];
        event.d->manifestation = eventData[3];
        event.d->actor = eventData[4];
    }

    if (!subjectList.isEmpty()) {
        uint subjectsSize = subjectList.size();

        for (uint i = 0; i < subjectsSize; ++i) {
            QStringList subjectString = subjectList[i];

            Subject subject;
            subject.setUri(subjectString[0]);
            subject.setInterpretation(subjectString[1]);
            subject.setManifestation(subjectString[2]);
            subject.setOrigin(subjectString[3]);
            subject.setMimeType(subjectString[4]);
            subject.setText(subjectString[5]);
            subject.setStorage(subjectString[6]);

            event.d->subjects << subject;
        }
    }

    return argument;
}

};

};
