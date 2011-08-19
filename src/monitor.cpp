/*
 * This file is part of QZeitgeist.
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


#include "QZeitgeist/Monitor"

#include "monitor_p.h"
#include "monitoradaptor.h"

namespace QZeitgeist
{

// Monitor's DBus Object Path.
const QString objPath = "/org/gnome/zeitgeist/monitor";

// Monitor's DBus Service Name.
const QString serviceName = "org.gnome.zeitgeist.Monitor";


// Implements the private section. D pointer.
MonitorPrivate::MonitorPrivate(quint64 monitorId,
        QZeitgeist::DataModel::TimeRange monitorTimeRange,
        QZeitgeist::DataModel::EventList monitorTemplates,
        Monitor *parent)
    : QObject(parent),
    id(monitorId),
    timeRange(monitorTimeRange),
    eventTemplates(monitorTemplates),
    q(parent)
{
    // Create the needed DBus Monitor Adaptor.
    monitorAdaptor = new MonitorAdaptor(this);

    regObjPath = QString(objPath + "/%1").arg(id);

    QDBusConnection connection = QDBusConnection::sessionBus();
    connection.registerService(serviceName);
    connection.registerObject(regObjPath, this);
}

MonitorPrivate::~MonitorPrivate()
{
    // Free the interface.
    delete monitorAdaptor;
}

void MonitorPrivate::NotifyDelete(
        const QZeitgeist::DataModel::TimeRange &timeRange,
        const QZeitgeist::DataModel::EventIdList &eventIds)
{
    emit q->eventsDeleted(timeRange, eventIds);
}

void MonitorPrivate::NotifyInsert(
        const QZeitgeist::DataModel::TimeRange &timeRange,
        const QZeitgeist::DataModel::EventList &events)
{
    emit q->eventsInserted(timeRange, events);
}

// Implements the Monitor class.
Monitor::Monitor(quint64 id,
        QZeitgeist::DataModel::TimeRange timeRange,
        QZeitgeist::DataModel::EventList templates,
        QObject *parent)
    : QObject(parent),
    d(new MonitorPrivate(id, timeRange, templates, this))
{
    Q_ASSERT(d);
}

Monitor::~Monitor()
{
    delete d;
}

QString Monitor::objectPath() const
{
    return d->regObjPath;
}

quint64 Monitor::id() const
{
    return d->id;
}

QZeitgeist::DataModel::TimeRange Monitor::timeRange() const
{
    return d->timeRange;
}

QZeitgeist::DataModel::EventList Monitor::eventTemplates() const
{
    return d->eventTemplates;
}

};
