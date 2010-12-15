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


#include "QtZeitgeist/Log"

#include "_gen/LogInterface"

#include <QDebug>

namespace QtZeitgeist
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

    org::gnome::zeitgeist::Log *logInterface;
};

Log::Log(QObject *parent)
    : d(new LogPrivate())
{
    Q_ASSERT(d);
}

Log::~Log()
{
    delete d;
}

QDBusPendingReply<QtZeitgeist::DataModel::EventIdList> Log::insertEvents(
        const QtZeitgeist::DataModel::EventList events)
{
    Q_ASSERT(events.size() > 0);

    QtZeitgeist::DataModel::EventIdList ids;

    return d->logInterface->InsertEvents(events);
}

void Log::deleteLog()
{
    d->logInterface->DeleteLog();
}

QDBusPendingReply<QStringList> Log::findRelatedUris(
        QtZeitgeist::DataModel::TimeRange timeRange,
        QtZeitgeist::DataModel::EventList eventTemplateList,
        QtZeitgeist::DataModel::EventList resultEventTemplateList,
        StorageState state, uint maxEvents, ResultType type)
{
    Q_ASSERT(eventTemplateList.size() > 0);
    Q_ASSERT(resultEventTemplateList.size() > 0);

    return d->logInterface->FindRelatedUris(timeRange, eventTemplateList,
            resultEventTemplateList, state, maxEvents, type);
}

};
