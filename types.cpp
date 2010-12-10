/*
 *   Copyright (C) 2010 Ivan Cukic <ivan.cukic(at)kde.org>
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License version 2,
 *   or (at your option) any later version, as published by the Free
 *   Software Foundation
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details
 *
 *   You should have received a copy of the GNU General Public
 *   License along with this program; if not, write to the
 *   Free Software Foundation, Inc.,
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#include "types.h"

#include <QMetaType>
#include <QDBusMetaType>

// We need to register meta types for classes we use,
// doing it statically

class StaticTypesRegistration {
public:
    StaticTypesRegistration() {
        qRegisterMetaType < Event > ("Event");
        qDBusRegisterMetaType < Event > ();

        qRegisterMetaType < EventList > ("EventList");
        qDBusRegisterMetaType < EventList > ();

        qRegisterMetaType < EventIdList > ("EventIdList");
        qDBusRegisterMetaType < EventIdList > ();
    }

};

StaticTypesRegistration registration;

// Implementing the classes

// Event

class EventPrivate {
public:
    QStringList arg1;
    QList < QStringList > arg2;
    QByteArray arg3;
};

Event::Event()
    : d(new EventPrivate())
{
}

Event::~Event()
{
    delete d;
}


QDBusArgument & operator << (QDBusArgument & argument, const Event & event)
{
    argument.beginStructure();
    argument
        << event.d->arg1
        << event.d->arg2
        << event.d->arg3
        ;
    argument.endStructure();
    return argument;
}

const QDBusArgument & operator >> (const QDBusArgument & argument, Event & event)
{
    argument.beginStructure();
    argument
        >> event.d->arg1
        >> event.d->arg2
        >> event.d->arg3
        ;
    argument.endStructure();

    return argument;
}

// EventList

class EventListPrivate {
public:
};

EventList::EventList()
    : d(new EventListPrivate())
{
}

EventList::~EventList()
{
    delete d;
}



// EventIdList

class EventIdListPrivate {
public:
};

EventIdList::EventIdList()
    : d(new EventIdListPrivate())
{
}

EventIdList::~EventIdList()
{
    delete d;
}

