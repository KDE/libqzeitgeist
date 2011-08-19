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


#include "QtZeitgeist/DataSourceRegistry"
#include "datasourceregistryinterface.h"

namespace QtZeitgeist
{

// DataSourceRegistry's DBus Object Path.
const QString objectPath = "/org/gnome/zeitgeist/data_source_registry";

// DataSourceRegistry's DBus Service Name.
const QString serviceName = "org.gnome.zeitgeist.Engine";

class DataSourceRegistryPrivate
{
public :
    DataSourceRegistryPrivate()
    {
        // Create the needed DBus DataSourceRegistry Interface.
        registryInterface = new org::gnome::zeitgeist::DataSourceRegistry(
                serviceName, objectPath, QDBusConnection::sessionBus());

    }

    ~DataSourceRegistryPrivate()
    {
        // Free the interface.
        delete registryInterface;
    }

    org::gnome::zeitgeist::DataSourceRegistry *registryInterface;
};

DataSourceRegistry::DataSourceRegistry(QObject *parent)
    : d(new DataSourceRegistryPrivate())
{
    Q_ASSERT(d);

    connect(d->registryInterface,
        SIGNAL(DataSourceDisconnected(const QtZeitgeist::DataModel::DataSource&)),
        SIGNAL(dataSourceDisconnected(const QtZeitgeist::DataModel::DataSource&)));
    connect(d->registryInterface,
        SIGNAL(DataSourceEnabled(const QString &, bool)),
        SIGNAL(dataSourceEnabled(const QString &, bool)));
    connect(d->registryInterface,
        SIGNAL(DataSourceRegistered(const QtZeitgeist::DataModel::DataSource &)),
        SIGNAL(dataSourceRegistered(const QtZeitgeist::DataModel::DataSource &)));
}

DataSourceRegistry::~DataSourceRegistry()
{
    delete d;
}

QDBusPendingReply<bool> DataSourceRegistry::registerDataSource(const QString &id,
    const QString &name, const QString &description,
    DataModel::EventList &event_templates)
{
    Q_ASSERT(!id.isEmpty());

    return d->registryInterface->RegisterDataSource(id, name, description,
        event_templates);
}

QDBusPendingReply<QtZeitgeist::DataModel::DataSourceList>
    DataSourceRegistry::getDataSources()
{
    return d->registryInterface->GetDataSources();
}

void DataSourceRegistry::setDataSourceEnabled(const QString &unique_id,
    bool enabled)
{
    d->registryInterface->SetDataSourceEnabled(unique_id, enabled);
}

};
