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

#include "refreshjob.h"

#include <QtCore/QDebug>

namespace QZeitgeist
{

RefreshJob::RefreshJob(const QZeitgeist::DataModel::TimeRange &range,
           const QZeitgeist::DataModel::EventList &templates,
           QZeitgeist::Log::StorageState state,
           uint maxEvents,
           QZeitgeist::Log::ResultType type,
           QZeitgeist::Log *log,
           QObject *parent)
    : QObject(parent)
    , m_range(range)
    , m_templates(templates)
    , m_state(state)
    , m_count(maxEvents)
    , m_type(type)
    , m_log(log)
{
    m_reply = m_log->findEvents(m_range, m_templates, m_state, m_count, m_type);
}

RefreshJob::~RefreshJob()
{
}

void RefreshJob::run()
{
    m_reply.waitForFinished();
    if (m_reply.isValid()) {
        //setFinished(true);
        emit done(m_reply.value());
    } else {
        qDebug() << m_reply.error();
        //setFinished(false);
    }
}
} // namespace QZeitgeist

#include "refreshjob.moc"
