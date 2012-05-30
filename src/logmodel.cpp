/**
 * Copyright (C) 2011 Trever Fischer <tdfischer@fedoraproject.org>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the Lesser GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 */

#include "logmodel.h"
#include "refreshjob.h"

#include "DataModel/subject.h"

#include <QtGui/QFileIconProvider>
#include <QtCore/QDebug>
#include <QtCore/QUrl>
#include <QtCore/QDir>
#include <QtCore/QCryptographicHash>

namespace QZeitgeist
{

LogModel::LogModel(QObject *parent)
    : QAbstractItemModel(parent)
    , m_monitor(0)
    , m_iconMode(URIIcons)
{
    m_log = new QZeitgeist::Log(this);
    m_storageState = QZeitgeist::Log::Any;
    m_range = QZeitgeist::DataModel::TimeRange::always();
    m_eventTemplates << QZeitgeist::DataModel::Event();
    m_type = QZeitgeist::Log::MostRecentSubjects;
    m_pool = new QThreadPool(this);
}

LogModel::~LogModel()
{
}

void LogModel::setIconMode(IconMode mode)
{
    m_iconMode = mode;
    emit dataChanged(index(0, 0), index(rowCount(), 0));
}

void LogModel::diffEvents(const QZeitgeist::DataModel::EventList &events)
{
    //TODO: Implement dyanmic programming for a proper diff algorithm.
    //This probably depends on the datamodel objects not being QObjects.
    QZeitgeist::DataModel::EventList newEvents = events;
    QZeitgeist::DataModel::EventList::iterator currentIt = m_events.begin();
    QZeitgeist::DataModel::EventList::iterator newIt = newEvents.begin();
    int currentRow = 0;
    while(currentIt != m_events.end() && newIt != newEvents.end()) {
        if (newIt->id() == currentIt->id()) {
            newIt++;
            currentIt++;
            currentRow++;
        } else if (newIt->timestamp() >= currentIt->timestamp()) {
            beginInsertRows(QModelIndex(), currentRow, currentRow);
            currentIt = m_events.insert(currentIt, *newIt);
            endInsertRows();
            newIt = newEvents.erase(newIt);
            currentIt++;
            currentRow++;
        } else if (newIt->timestamp() < currentIt->timestamp()) {
            beginRemoveRows(QModelIndex(), currentRow, currentRow);
            currentIt = m_events.erase(currentIt);
            endRemoveRows();
        }
    }
    if (newIt != newEvents.end()) {
        beginInsertRows(QModelIndex(), currentRow, currentRow+newEvents.size()-1);
        while(newIt != newEvents.end()) {
            currentIt = m_events.insert(currentIt, *newIt);
            currentRow++;
            currentIt++;
            newIt++;
        }
        endInsertRows();
    }
    if (currentIt != m_events.end()) {
        beginRemoveRows(QModelIndex(), currentRow, m_events.size()-1);
        while(currentIt != m_events.end()) {
            currentIt = m_events.erase(currentIt);
        }
        endRemoveRows();
    }
}

void LogModel::refresh()
{
    RefreshJob *refreshJob = new RefreshJob(m_range,
                                            m_eventTemplates,
                                            m_storageState,
                                            10000,
                                            m_type,
                                            m_log,
                                            this);
    connect(refreshJob, SIGNAL(done(QZeitgeist::DataModel::EventList)), this, SLOT(refreshDone(QZeitgeist::DataModel::EventList)));
    m_pool->start(refreshJob);
    if (m_monitor)
        m_log->removeMonitor(m_monitor);
    m_monitor = m_log->installMonitor(m_range, m_eventTemplates);
    connect(m_monitor, SIGNAL(eventsInserted(QZeitgeist::DataModel::TimeRange,QZeitgeist::DataModel::EventList)), this, SLOT(eventsInserted(QZeitgeist::DataModel::TimeRange,QZeitgeist::DataModel::EventList)));
    connect(m_monitor, SIGNAL(eventsDeleted(QZeitgeist::DataModel::TimeRange,QZeitgeist::DataModel::EventIdList&)), this, SLOT(eventsDeleted(QZeitgeist::DataModel::TimeRange,QZeitgeist::DataModel::EventIdList)));
}

void LogModel::eventsInserted(const QZeitgeist::DataModel::TimeRange &range, const QZeitgeist::DataModel::EventList &events)
{
    QZeitgeist::DataModel::EventList oldEvents = m_events;
    foreach(const QZeitgeist::DataModel::Event &evt, events) {
        oldEvents << evt;
    }
    diffEvents(oldEvents);
}

void LogModel::eventsDeleted(const QZeitgeist::DataModel::TimeRange &range, const QZeitgeist::DataModel::EventIdList &events)
{
    QZeitgeist::DataModel::EventList oldEvents = m_events;
    foreach(int id, events) {
        foreach(const QZeitgeist::DataModel::Event &evt, oldEvents) {
            if (evt.id() == id)
                oldEvents.removeOne(evt);
        }
    }
    diffEvents(oldEvents);
}

void LogModel::refreshDone(const QZeitgeist::DataModel::EventList &results)
{
    diffEvents(results);
}

int LogModel::rowCount(const QModelIndex &idx) const
{
    if (idx.isValid())
        return 0;
    return m_events.size();
}

int LogModel::columnCount(const QModelIndex &idx) const
{
    if (idx.isValid())
        return 0;
    return 1;
}

QModelIndex LogModel::parent(const QModelIndex &idx) const
{
    Q_UNUSED(idx);
    return QModelIndex();
}

QVariant LogModel::data(const QModelIndex &idx, int role) const
{
    if (idx.isValid() && idx.row() >= 0 && idx.row() < rowCount() && idx.column() == 0) {
        QZeitgeist::DataModel::Event event = m_events[idx.row()];
        switch(role) {
            case Qt::DisplayRole:
                return event.subjects()[0].text();
            case Qt::DecorationRole:
                return iconForEvent(event);
            case EventRole:
                return QVariant::fromValue<QZeitgeist::DataModel::Event>(event);
            case TimeRole:
                return event.timestamp();
            case IDRole:
                return event.id();
            case URLRole:
                return event.subjects()[0].uri();
            case MimeRole:
                return event.subjects()[0].mimeType();
            case ActorRole:
                return event.actor();
            case ThumbnailRole:
                return thumbnailForEvent(event);
            default:
                return QVariant();
        }
    }
    return QVariant();
}

QPixmap LogModel::thumbnailForEvent(const QZeitgeist::DataModel::Event &event) const
{
    //FIXME: Implement caching
    QString url(event.subjects()[0].uri());
    QDir thumbDir(QString("%1/.thumbnails/large/").arg(QDir::homePath()));
    QString snapshotName = QString("%1.png").arg(QString(QCryptographicHash::hash(url.toUtf8(), QCryptographicHash::Md5).toHex()));
    if (thumbDir.exists(snapshotName)) {
        return QPixmap(thumbDir.absoluteFilePath(snapshotName), "JPEG");
    }
    return QPixmap();
}

QIcon LogModel::iconForActor(const QString &actor) const
{
    QString desktopFile = QUrl(actor).authority().section('.', 0, 0);
    return QIcon::fromTheme(desktopFile);
}

QIcon LogModel::iconForEvent(const QZeitgeist::DataModel::Event &event) const
{
    QFileIconProvider icons;
    QIcon ret = iconForActor(event.actor());
    if (m_iconMode == ActorIcons)
        return ret;
    foreach(QZeitgeist::DataModel::Subject subject, event.subjects()) {
        QUrl url = subject.uri();
        if (url.scheme() == "file") {
            QFileInfo info(url.path());
            ret = icons.icon(info);
            if (!ret.isNull())
              break;
        }
    }
    if (ret.isNull())
        ret = iconForActor(event.actor());
}

QModelIndex LogModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!parent.isValid() && row >= 0 && row < rowCount() && column == 0)
        return createIndex(row, column);
    return QModelIndex();
}

void LogModel::setRange(const QZeitgeist::DataModel::TimeRange &range)
{
    m_range = range;
    refresh();
}

Qt::ItemFlags LogModel::flags(const QModelIndex &index) const
{
    if (index.isValid() && index.row() >= 0 && index.row() < rowCount() && index.column() == 0)
        return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
    return 0;
}

QStringList LogModel::eventIconOverlays(const QZeitgeist::DataModel::Event &event) const
{
    QStringList overlays;
    QZeitgeist::DataModel::Subject subject = event.subjects()[0];
    /*switch(subject.interpretation()) {
        case QZeitgeist::Interpretation::Subject::NFOAudio:
            overlays << "applications-m
    }*/
    QString mime = subject.mimeType();
    overlays << mime.replace('/', '-');
    return overlays;
}

QZeitgeist::DataModel::TimeRange LogModel::range() const
{
    return m_range;
}

void LogModel::setResultType(QZeitgeist::Log::ResultType type)
{
    m_type = type;
    refresh();
}

QZeitgeist::Log::ResultType LogModel::resultType() const
{
    return m_type;
}

void LogModel::setEventTemplates(const QZeitgeist::DataModel::EventList &templates)
{
    m_eventTemplates = templates;
    refresh();
}

DataModel::EventList LogModel::eventTemplates() const
{
    return m_eventTemplates;
}

} // namespace QZeitgeist

#include "logmodel.moc"
