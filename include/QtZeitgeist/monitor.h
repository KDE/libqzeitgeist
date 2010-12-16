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


#ifndef QTZEITGEIST_MONITOR_H_
#define QTZEITGEIST_MONITOR_H_

#include <QObject>

#include "QtZeitgeist/Log"
#include "QtZeitgeist/DataModel/Event"
#include "QtZeitgeist/DataModel/TimeRange"

namespace QtZeitgeist
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

protected:

    /**
     * Default constructor.
     */
    explicit Monitor(quint64 id, QObject *parent = 0);

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
    void eventsInserted(const QtZeitgeist::DataModel::TimeRange &timeRange,
            const QtZeitgeist::DataModel::EventList &events);

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
    void eventsDeleted(const QtZeitgeist::DataModel::TimeRange &timeRange,
            const QtZeitgeist::DataModel::EventIdList &eventIds);

private:

    QString objectPath() const;

    friend class Log;
    friend class MonitorPrivate;

    // D Pointer.
    class MonitorPrivate * const d;
};

};

#endif // QTZEITGEIST_MONITOR_H_
