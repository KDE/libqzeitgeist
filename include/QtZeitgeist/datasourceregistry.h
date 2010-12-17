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


#ifndef QTZEITGEIST_DATASOURCEREGISTRY_H_
#define QTZEITGEIST_DATASOURCEREGISTRY_H_

#include <QObject>
#include <QDBusPendingReply>

#include "QtZeitgeist/DataModel/DataSource"
#include "QtZeitgeist/DataModel/Event"

namespace QtZeitgeist
{

class DataSourceRegistryPrivate;

/**
 * @class DataSourceRegistry datasourceregistry.h datasourceregistry.h
 * @brief Primary access point for accessing the Zeitgeist data-sources.
 *
 * @DataSourceRegistry encapsulates the low level access to the Zeitgeist
 * data-sources. You can use it to manage the data-sources by registering
 * a data source, enabling/disabling data-sources and getting all data-sources.
 *
 * It's important to realize that the @DataSourceRegistry class does not expose
 * any API that does synchronous communications with the message bus -
 * everything is asynchronous. Thus, instead of the real result, each
 * asynchronous operation will return a DBus pending reply object, that can
 * be used to watch and fetch the real operation return/result.
 *
 * @see Event
 *
 * @author Jeremy Whiting <jeremy.whiting@collabora.co.uk>
 */
class Q_DECL_EXPORT DataSourceRegistry : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(DataSourceRegistry)

public:

    /**
     * Default constructor.
     */
    explicit DataSourceRegistry(QObject *parent = 0);

    /**
     * Destructor.
     */
    virtual ~DataSourceRegistry();

    /**
     * Asynchronously register a data source.
     *
     * Register a data-source as currently running. If the data-source was
     * already in the database, its metadata (name, description and
     * event_templates) are updated.
     *
     * @param unique_id unique ASCII string identifying the data-source.
     * @param name data-source name (may be translated).
     * @param description data-source description (may be translated).
     * @param event_templates optional templates of events the datasource logs.
     *
     * @returns boolean true if the datasource is enabled, false if it's disabled.
     */
    QDBusPendingReply<bool> registerDataSource(const QString &unique_id,
        const QString &name, const QString &description,
        DataModel::EventList &event_templates);

    /**
     * Asynchronously get the existing data sources.
     *
     * Get the list of known data-sources.
     *
     * @returns a list of data sources.
     */
    QDBusPendingReply<QtZeitgeist::DataModel::DataSourceList> getDataSources();

    /**
     * Asynchronously enable or disable a data source.
     *
     * @param unique_id unique string identifying a data-source.
     * @param enabled whether the data-source is to be enabled or disabled.
     */
    void setDataSourceEnabled(const QString &unique_id, bool enabled);

Q_SIGNALS:
    void dataSourceDisconnected(const QtZeitgeist::DataModel::DataSource&);
    void dataSourceEnabled(const QString &, bool);
    void dataSourceRegistered(const QtZeitgeist::DataModel::DataSource &);

private:

    // D Pointer.
    class DataSourceRegistryPrivate * const d;
};

};

#endif // QTZEITGEIST_DATASOURCEREGISTRY_H_
