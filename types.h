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

#ifndef ZEITGEIST_TYPES_H_
#define ZEITGEIST_TYPES_H_

#include <QList>
#include <QMetaType>
#include <QDBusArgument>

class EventPrivate;
class EventListPrivate;
class EventIdListPrivate;

class Event {
public:
    Event();
    virtual ~Event();

private:
    class EventPrivate * const d;

    friend QDBusArgument & operator << (QDBusArgument & argument, const Event & event);
    friend const QDBusArgument & operator >> (const QDBusArgument & argument, Event & event);
};

Q_DECLARE_METATYPE(Event)

class EventList: public QList < Event > {
public:
    EventList();
    virtual ~EventList();

private:
    class EventListPrivate * const d;
};

Q_DECLARE_METATYPE(EventList)

class EventIdList: public QList < quint32 > {
public:
    EventIdList();
    virtual ~EventIdList();

private:
    class EventIdListPrivate * const d;
};

Q_DECLARE_METATYPE(EventIdList)

#endif // ZEITGEIST_TYPES_H_
