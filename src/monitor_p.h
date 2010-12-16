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


#ifndef QTZEITGEIST_MONITOR_P_H_
#define QTZEITGEIST_MONITOR_P_H_

#include <QObject>

#include "QtZeitgeist/DataModel/Event"
#include "QtZeitgeist/DataModel/TimeRange"

class MonitorAdaptor;

namespace QtZeitgeist
{

class Monitor;

/*
 * Private.
 *
 * @author Abner Silva <abner@collabora.co.uk>
 */
class MonitorPrivate : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(MonitorPrivate)

public:

    /**
     * Default constructor.
     */
    explicit MonitorPrivate(quint64 monitorId, Monitor* parent = 0);

    /**
     * Destructor.
     */
    virtual ~MonitorPrivate();


public Q_SLOTS:

    // Adaptor slots.
    void NotifyDelete(const QtZeitgeist::DataModel::TimeRange &timeRange,
            const QtZeitgeist::DataModel::EventIdList &eventIds);

    void NotifyInsert(const QtZeitgeist::DataModel::TimeRange &timeRange,
            const QtZeitgeist::DataModel::EventList &events);

public:

    // Monitor id.
    quint64 id;

    // Registered object path.
    QString regObjPath;

    // Pointer to the adaptor.
    MonitorAdaptor *monitorAdaptor;

    // D Pointer.
    class Monitor * const q;
};

};

#endif // QTZEITGEIST_MONITOR_P_H_
