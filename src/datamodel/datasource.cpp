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


#include "QtZeitgeist/DataModel/DataSource"

#include <QMetaType>
#include <QDBusMetaType>


namespace QtZeitgeist
{

namespace DataModel
{

class DataSourcePrivate
{
public :
    QString uniqueId;
    QString name;
    QString description;
    EventList eventTemplates;
    bool running;
    QDateTime lastSeen;
    bool enabled;
};

DataSource::DataSource(QObject *parent)
    : d(new DataSourcePrivate())
{
    Q_ASSERT(d);

    // Initialize the last seen time.
    d->lastSeen.setTime_t(0);
}

DataSource::DataSource(const DataSource & source, QObject *parent)
    : d(new DataSourcePrivate())
{
    Q_ASSERT(d);

    // Copy the source attribute's value.
    d->uniqueId = source.d->uniqueId;
    d->name = source.d->name;
    d->description = source.d->description;
    d->eventTemplates = source.d->eventTemplates;
    d->running = source.d->running;
    d->lastSeen = source.d->lastSeen;
    d->enabled = source.d->enabled;
}

DataSource::~DataSource()
{
    delete d;
}

QString DataSource::uniqueId() const
{
    return d->uniqueId;
}

QString DataSource::name() const
{
    return d->name;
}

QString DataSource::description() const
{
    return d->description;
}

EventList DataSource::eventTemplates() const
{
    return d->eventTemplates;
}

bool DataSource::running() const
{
    return d->running;
}

QDateTime DataSource::lastSeen() const
{
    return d->lastSeen;
}

bool DataSource::enabled() const
{
    return d->enabled;
}

DataSource &DataSource::operator = (const DataSource & source)
{
    // Copy the source attribute's value.
    if (this != &source) {
        d->uniqueId = source.d->uniqueId;
        d->name = source.d->name;
        d->description = source.d->description;
        d->eventTemplates = source.d->eventTemplates;
        d->running = source.d->running;
        d->lastSeen = source.d->lastSeen;
        d->enabled = source.d->enabled;
    }

    return *this;
}

QDBusArgument & operator << (QDBusArgument &argument, const DataSource &datasource)
{
    argument.beginStructure();
    argument
        << datasource.d->uniqueId
        << datasource.d->name
        << datasource.d->description
        << datasource.d->eventTemplates
        << datasource.d->running
        << datasource.d->lastSeen.toMSecsSinceEpoch()
        << datasource.d->enabled;

    argument.endStructure();

    return argument;
}

const QDBusArgument & operator >> (const QDBusArgument &argument,
    DataSource &datasource)
{
    argument.beginStructure();
    qint64 lastSeenMSecs;

    argument
        >> datasource.d->uniqueId
        >> datasource.d->name
        >> datasource.d->description
        >> datasource.d->eventTemplates
        >> datasource.d->running
        >> lastSeenMSecs
        >> datasource.d->enabled;

    // Translate the last seen string
    datasource.d->lastSeen.setMSecsSinceEpoch(lastSeenMSecs);

    argument.endStructure();

    return argument;
}

};

};
