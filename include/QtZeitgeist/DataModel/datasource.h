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


#ifndef QTZEITGEIST_DATASOURCE_H_
#define QTZEITGEIST_DATASOURCE_H_

#include <QList>
#include <QDateTime>
#include <QMetaType>
#include <QDBusArgument>

#include "event.h"

namespace QtZeitgeist
{

namespace DataModel
{

class DataSourcePrivate;

/**
 * @class DataSource datasource.h datasource.h
 * @brief DataSource object that represents a datasource.
 *
 * @see Event.
 *
 * @author Jeremy Whiting <jeremy.whiting@collabora.co.uk>
 */
class Q_DECL_EXPORT DataSource : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString uniqueId READ uniqueId)
    Q_PROPERTY(QString name READ name)
    Q_PROPERTY(QString description READ description)
    Q_PROPERTY(EventList eventTemplates READ eventTemplates)
    Q_PROPERTY(bool running READ running)
    Q_PROPERTY(QDateTime lastSeen READ lastSeen)
    Q_PROPERTY(bool enabled READ enabled)

public:

    /**
     * Default constructor.
     */
    explicit DataSource(QObject *parent = 0);

    /**
     * Copy constructor.
     */
    DataSource(const DataSource &source, QObject *parent = 0);

    /**
     * Destructor.
     */
    virtual ~DataSource();

    /**
     * Get the datasource id as assigned by the Zeitgeist engine.
     *
     * @return the datasource id or 0 if it's unset. An datasource retrieved from the
     * Zeitgeist engine will always have a datasource id.
     */
    QString uniqueId() const;

    /**
     * The datasource's name is the name of the datasource.
     *
     * @return the datasource name.
     */
    QString name() const;

    /**
     * The datasource's description.
     *
     * @return the datasource interpretation as a URI or empty if unset.
     */
    QString description() const;

    /**
     * Get the event templates.
     *
     * @returns the eventTemplates in use.
     */
    EventList eventTemplates() const;
    /**
     * Get the running value.
     *
     * @return true if this datasource is running.
     */
    bool running() const;

    /**
     * Get the lastseen time.
     *
     * @return the last seen time.
     */
    QDateTime lastSeen() const;

    /**
     * Get the enabled value.
     *
     * @return true if this datasource is enabled, false otherwise.
     */
    bool enabled() const;

    DataSource & operator = (const DataSource &source);

private:

    // D Pointer.
    class DataSourcePrivate * const d;

    // Marshalers operators.
    friend QDBusArgument & operator << (QDBusArgument &argument,
            const DataSource &datasource);
    friend const QDBusArgument & operator >> (const QDBusArgument &argument,
            DataSource &datasource);
};

// Create additional types.
typedef QList<DataSource> DataSourceList;

};

};

// Declare types as Qt Meta Type.
Q_DECLARE_METATYPE(QtZeitgeist::DataModel::DataSource)
Q_DECLARE_METATYPE(QtZeitgeist::DataModel::DataSourceList)

#endif // QTZEITGEIST_DATASOURCE_H_
