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


#ifndef QZEITGEIST_MONITOR_H_
#define QZEITGEIST_MONITOR_H_

#include <QObject>

#include "log.h"
#include "DataModel/event.h"
#include "DataModel/timerange.h"

namespace QZeitgeist
{

class MonitorPrivate;

/**
 * @class Monitor monitor.h monitor.h
 * @brief Class for monitoring the Zeitgeist log for certain types of events.
 *
 * @Monitor listens for updates to the Zeitgeist event log  matching a given
 * set of templates and with timestamps in some predefined time range.
 *
 * @see Log
 *
 * @author Abner Silva <abner@collabora.co.uk>
 */
class Q_DECL_EXPORT Monitor : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(Monitor)
    Q_PROPERTY(quint64 id READ id)
    Q_PROPERTY(QZeitgeist::DataModel::TimeRange timeRange READ timeRange)
    Q_PROPERTY(QZeitgeist::DataModel::EventList eventTemplates
            READ eventTemplates)

public:

    /**
     * Return the Monitor ID.
     *
     * Note: The Monitor ID is not related to any data stored or referenced by
     * the Zeitgeist daemon. It's only an unique identification of the monitor
     * instance.
     *
     * @returns An unique ID.
     */
    quint64 id() const;

    /**
     * Return the Monitor Time Range.
     *
     * @returns the time range used to create the monitor.
     */
    QZeitgeist::DataModel::TimeRange timeRange() const;

    /**
     * Return the Monitor Event Templates.
     *
     * @returns the event templates used to create the monitor.
     */
    QZeitgeist::DataModel::EventList eventTemplates() const;

protected:

    /**
     * Default constructor.
     */
    explicit Monitor(quint64 id,
            QZeitgeist::DataModel::TimeRange monitorTimeRange,
            QZeitgeist::DataModel::EventList monitorTemplates,
            QObject *parent = 0);

    /**
     * Destructor.
     */
    virtual ~Monitor();

Q_SIGNALS:

    /**
     * Signal to notify inserted events.
     *
     * Emitted when events matching the event templates and with timestamps
     * within the time range of the monitor has been inserted into the log.
     *
     * @param timeRange a @TimeRange that specifies the minimum and maximum
     * of the timestamps in @events.
     * @param events a @EventList holding the events that have been inserted
     * into the log.
     */
    void eventsInserted(const QZeitgeist::DataModel::TimeRange &timeRange,
            const QZeitgeist::DataModel::EventList &events);

    /**
     * Signal to notify deleted events.
     *
     * Emitted when events with timestamps within the time range of this
     * monitor has been deleted from the log. Note that the deleted events
     * may not match the event templates for the monitor.
     *
     * @param timeRange A @TimeRange that specifies the minimum and maximum
     * timestamps of the deleted events.
     * @param eventIds A @EventIdList holding the ids of the deleted events.
     */
    void eventsDeleted(const QZeitgeist::DataModel::TimeRange &timeRange,
            const QZeitgeist::DataModel::EventIdList &eventIds);

private:

    QString objectPath() const;

    friend class Log;
    friend class MonitorPrivate;

    // D Pointer.
    class MonitorPrivate * const d;
};

};

#endif // QZEITGEIST_MONITOR_H_
