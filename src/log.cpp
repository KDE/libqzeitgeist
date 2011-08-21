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


#include "log.h"

#include "monitor.h"
#include "loginterface.h"

namespace QZeitgeist
{

// Log's DBus Object Path.
const QString objectPath = "/org/gnome/zeitgeist/log/activity";

// Log's DBus Service Name.
const QString serviceName = "org.gnome.zeitgeist.Engine";

class LogPrivate
{
public :
    LogPrivate()
    {
        // Create the needed DBus Log Interface.
        logInterface = new org::gnome::zeitgeist::Log(
                serviceName, objectPath, QDBusConnection::sessionBus());
    }

    ~LogPrivate()
    {
        // Free the interface.
        delete logInterface;
    }

    static quint64 monitorIdIndex;
    org::gnome::zeitgeist::Log *logInterface;
};

quint64 LogPrivate::monitorIdIndex = 0;

Log::Log(QObject *parent)
    : d(new LogPrivate())
{
    Q_ASSERT(d);
}

Log::~Log()
{
    delete d;
}

QDBusPendingReply<QZeitgeist::DataModel::EventIdList> Log::insertEvents(
        const QZeitgeist::DataModel::EventList events)
{
    Q_ASSERT(events.size() > 0);

    QZeitgeist::DataModel::EventIdList ids;

    return d->logInterface->InsertEvents(events);
}

void Log::deleteLog()
{
    d->logInterface->DeleteLog();
}

QDBusPendingReply<QStringList> Log::findRelatedUris(
        QZeitgeist::DataModel::TimeRange timeRange,
        QZeitgeist::DataModel::EventList eventTemplateList,
        QZeitgeist::DataModel::EventList resultEventTemplateList,
        StorageState state, uint maxEvents, ResultType type)
{
    Q_ASSERT(eventTemplateList.size() > 0);
    Q_ASSERT(resultEventTemplateList.size() > 0);

    return d->logInterface->FindRelatedUris(timeRange, eventTemplateList,
            resultEventTemplateList, state, maxEvents, type);
}

QDBusPendingReply<QZeitgeist::DataModel::EventList> Log::findEvents(
        QZeitgeist::DataModel::TimeRange timeRange,
        QZeitgeist::DataModel::EventList eventTemplateList,
        StorageState state, uint maxEvents, ResultType type)

{
    Q_ASSERT(eventTemplateList.size() > 0);

    return d->logInterface->FindEvents(timeRange, eventTemplateList, state,
            maxEvents, type);
}

QDBusPendingReply<QZeitgeist::DataModel::EventIdList> Log::findEventIds(
        QZeitgeist::DataModel::TimeRange timeRange,
        QZeitgeist::DataModel::EventList eventTemplateList,
        StorageState state, uint maxEvents, ResultType type)

{
    Q_ASSERT(eventTemplateList.size() > 0);

    return d->logInterface->FindEventIds(timeRange, eventTemplateList, state,
            maxEvents, type);
}

void Log::deleteEvents(QZeitgeist::DataModel::EventIdList ids)
{
    Q_ASSERT(ids.size() > 0);

    d->logInterface->DeleteEvents(ids);
}

QDBusPendingReply<QZeitgeist::DataModel::EventList> Log::getEvents(
        QZeitgeist::DataModel::EventIdList ids)
{
    Q_ASSERT(ids.size() > 0);

    return d->logInterface->GetEvents(ids);
}

const QZeitgeist::Monitor *Log::installMonitor(
        QZeitgeist::DataModel::TimeRange timeRange,
        QZeitgeist::DataModel::EventList eventTemplateList)
{
    Q_ASSERT(eventTemplateList.size() > 0);

    LogPrivate::monitorIdIndex++;

    QZeitgeist::Monitor *monitor = new QZeitgeist::Monitor(
            LogPrivate::monitorIdIndex,
            timeRange, eventTemplateList, this);

    d->logInterface->InstallMonitor(QDBusObjectPath(monitor->objectPath()),
            timeRange, eventTemplateList);

    return monitor;
}

void Log::removeMonitor(QZeitgeist::Monitor *monitor)
{
    Q_ASSERT(monitor != 0);

    d->logInterface->RemoveMonitor(QDBusObjectPath(monitor->objectPath()));

    monitor->deleteLater();
}
};
