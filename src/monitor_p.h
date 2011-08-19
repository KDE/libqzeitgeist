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


#ifndef QZEITGEIST_MONITOR_P_H_
#define QZEITGEIST_MONITOR_P_H_

#include <QObject>

#include "QZeitgeist/DataModel/Event"
#include "QZeitgeist/DataModel/TimeRange"

class MonitorAdaptor;

namespace QZeitgeist
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
    explicit MonitorPrivate(quint64 monitorId,
            QZeitgeist::DataModel::TimeRange monitorTimeRange,
            QZeitgeist::DataModel::EventList monitorTemplates,
            Monitor* parent = 0);

    /**
     * Destructor.
     */
    virtual ~MonitorPrivate();


public Q_SLOTS:

    // Adaptor slots.
    void NotifyDelete(const QZeitgeist::DataModel::TimeRange &timeRange,
            const QZeitgeist::DataModel::EventIdList &eventIds);

    void NotifyInsert(const QZeitgeist::DataModel::TimeRange &timeRange,
            const QZeitgeist::DataModel::EventList &events);

public:

    // Monitor id.
    quint64 id;

    // Monitor time range.
    QZeitgeist::DataModel::TimeRange timeRange;

    // Monitor templates.
    QZeitgeist::DataModel::EventList eventTemplates;

    // Registered object path.
    QString regObjPath;

    // Pointer to the adaptor.
    MonitorAdaptor *monitorAdaptor;

    // D Pointer.
    class Monitor * const q;
};

};

#endif // QZEITGEIST_MONITOR_P_H_
