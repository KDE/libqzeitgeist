/**
 * Copyright (C) 2011 Trever Fischer <tdfischer@fedoraproject.org>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 */

#ifndef REFRESHJOB_H
#define REFRESHJOB_H

#include <QtCore/QObject>
#include <QtCore/QRunnable>
#include "log.h"
#include "DataModel/timerange.h"
#include "DataModel/event.h"

namespace QZeitgeist
{

class RefreshJob : public QObject, public QRunnable {
    Q_OBJECT

    public:
        RefreshJob(const QZeitgeist::DataModel::TimeRange &range,
                   const QZeitgeist::DataModel::EventList &templates,
                   QZeitgeist::Log::StorageState state,
                   uint maxEvents,
                   QZeitgeist::Log::ResultType type,
                   QZeitgeist::Log *log,
                   QObject *parent = 0);
        ~RefreshJob();
        void run();
    signals:
        void done(const QZeitgeist::DataModel::EventList &results);

    private:
        QZeitgeist::DataModel::TimeRange m_range;
        QZeitgeist::DataModel::EventList m_templates;
        QZeitgeist::Log::StorageState m_state;
        uint m_count;
        QZeitgeist::Log::ResultType m_type;
        QZeitgeist::Log *m_log;
        QDBusPendingReply<QZeitgeist::DataModel::EventList> m_reply;
};
} // namespace QZeitgeist

#endif //REFRESHJOB_H
