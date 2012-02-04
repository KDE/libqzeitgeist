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

#ifndef LOGMODEL_H
#define LOGMODEL_H

#include <QtCore/QAbstractItemModel>
#include <QtDBus/QDBusPendingReply>
#include <QtGui/QIcon>
#include <QtCore/QThreadPool>

#include "DataModel/timerange.h"
#include "DataModel/event.h"
#include "log.h"
#include "monitor.h"
#include "refreshjob.h"
#include "qzeitgeist.h"

namespace QZeitgeist
{

class QZEITGEIST_EXPORT LogModel : public QAbstractItemModel {
    Q_OBJECT

    public:
        enum {
            EventRole = Qt::UserRole+1,
            TimeRole,
            IDRole,
            URLRole,
            MimeRole,
            ActorRole,
            LastRole = ActorRole
        } Roles;
        LogModel(QObject *parent = 0);
        virtual ~LogModel();
        int rowCount(const QModelIndex &idx = QModelIndex()) const;
        int columnCount(const QModelIndex &idx = QModelIndex()) const;
        QVariant data(const QModelIndex &idx, int role = Qt::DisplayRole) const;
        QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;
        QModelIndex parent(const QModelIndex &idx) const;
        QIcon iconForEvent(const QZeitgeist::DataModel::Event &event) const;
        QStringList eventIconOverlays(const QZeitgeist::DataModel::Event &event) const;
        Qt::ItemFlags flags(const QModelIndex &index) const;

        QZeitgeist::DataModel::TimeRange range() const;
        QZeitgeist::Log::ResultType resultType() const;
        QZeitgeist::DataModel::EventList eventTemplates() const;

    public slots:
        void refresh();
        void setRange(const QZeitgeist::DataModel::TimeRange &range);
        void setResultType(QZeitgeist::Log::ResultType type);
        void setEventTemplates(const QZeitgeist::DataModel::EventList &templates);

    private slots:
        void refreshDone(const QZeitgeist::DataModel::EventList &events);
        void eventsInserted(const QZeitgeist::DataModel::TimeRange &range, const QZeitgeist::DataModel::EventList &events);
        void eventsDeleted(const QZeitgeist::DataModel::TimeRange &range, const QZeitgeist::DataModel::EventIdList &events);

    private:
        void diffEvents(const QZeitgeist::DataModel::EventList &events);
        QHash<QString, QString> m_iconCache;
        QZeitgeist::Log *m_log;
        QZeitgeist::DataModel::TimeRange m_range;
        QZeitgeist::DataModel::EventList m_eventTemplates;
        QZeitgeist::Log::StorageState m_storageState;
        QDBusPendingReply<QZeitgeist::DataModel::EventList> m_reply;
        QZeitgeist::DataModel::EventList m_events;
        QZeitgeist::Log::ResultType m_type;
        QThreadPool *m_pool;
        QZeitgeist::Monitor *m_monitor;
};

} // namespace QZeitgeist


#endif // LOGMODEL_H
