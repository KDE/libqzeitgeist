/**
 * Copyright (C) 2012 Trever Fischer <tdfischer@fedoraproject.org>
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
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 */

#include "logbrowser.h"
#include "DataModel/event.h"
#include "logmodel.h"
#include "interpretation.h"

#include <QtGui/QVBoxLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QListView>
#include <QtGui/QAction>
#include <QtGui/QRadioButton>
#include <QtCore/QSignalMapper>
#include <QtGui/QCheckBox>
#include <QtGui/QSortFilterProxyModel>
#include <QtGui/QLineEdit>

#include <QtCore/QDebug>

namespace QZeitgeist 
{

LogBrowser::LogBrowser(QWidget *parent)
  : QWidget(parent)
  , m_nextID(0)
  , m_actorFilterActive(false)
  , m_actorFilterCheck(0)
{
    m_log = new LogModel(this);
    m_log->setResultType(Log::MostRecentSubjects);

    QSortFilterProxyModel *filter = new QSortFilterProxyModel(this);
    filter->setSourceModel(m_log);
    filter->setSortCaseSensitivity(Qt::CaseInsensitive);
    filter->setDynamicSortFilter(true);
    filter->setFilterKeyColumn(0);

    QLineEdit *searchBox = new QLineEdit(this);
    searchBox->setPlaceholderText(tr("Search"));
    connect(searchBox, SIGNAL(textEdited(QString)), filter, SLOT(setFilterFixedString(QString)));


    QListView *view = new QListView(this);
    view->setResizeMode(QListView::Adjust);
    connect(view, SIGNAL(activated(QModelIndex)), this, SLOT(handleActivation(QModelIndex)));

    m_logView = view;
    m_logView->setModel(filter);


    QVBoxLayout *layout = new QVBoxLayout(this);
    m_filterLayout = new QHBoxLayout(this);
    layout->addWidget(searchBox);
    layout->addLayout(m_filterLayout);
    layout->addWidget(m_logView);

    m_actionMapper = new QSignalMapper(this);
    connect(m_actionMapper, SIGNAL(mapped(int)), this, SLOT(applyFilter(int)));

    DataModel::Event emptyEvent;
    addEventFilter(DataModel::EventList() << emptyEvent, "All")->setChecked(true);
}

LogBrowser::~LogBrowser()
{
}

QAction* LogBrowser::addEventFilter(const QZeitgeist::DataModel::EventList &templates, const QString &name)
{
    LogFilter filter;
    filter.events = templates;
    filter.button = new QRadioButton(name, this);
    filter.button->setCheckable(true);
    filter.action = new QAction(name, this);
    filter.action->setCheckable(true);

    connect(filter.button, SIGNAL(toggled(bool)), filter.action, SLOT(setChecked(bool)));

    m_actionMapper->setMapping(filter.action, m_nextID);
    connect(filter.action, SIGNAL(toggled(bool)), m_actionMapper, SLOT(map()));
    connect(filter.action, SIGNAL(toggled(bool)), filter.button, SLOT(setChecked(bool)));

    m_filters[m_nextID] = filter;
    m_filterLayout->addWidget(filter.button);
    m_nextID++;
    return filter.action;
}

void LogBrowser::setApplicationActor(const QString &actor, const QString &name)
{
     m_appActor = actor;
     if (m_actorFilterCheck == 0) {
          m_actorFilterCheck = new QCheckBox(tr("Only show events from %1").arg(name), this);
          connect(m_actorFilterCheck, SIGNAL(toggled(bool)), this, SLOT(applyActorFilter(bool)));
          m_actorFilterCheck->setChecked(true);
          m_filterLayout->addWidget(m_actorFilterCheck);
          m_actorFilterActive = true;
     }
    updateFilter();
}

void LogBrowser::applyFilter(int id)
{
    Q_ASSERT(m_filters.contains(id));
    LogFilter filter = m_filters[id];
    if (filter.action->isChecked()) {
      m_activeFilter = filter.events;
      updateFilter();
    }
}

void LogBrowser::updateFilter()
{
    DataModel::EventList events = m_activeFilter;
    if (m_actorFilterActive) {
        DataModel::Event actorTemplate;
        actorTemplate.setActor(m_appActor);
        events.append(actorTemplate);
    }
    if (events.size() == 0) {
      DataModel::Event blankEvent;
      events << blankEvent;
    }
    if (m_actorFilterActive) {
        DataModel::EventList newEvents;
        foreach(DataModel::Event e, events) {
            e.setActor(m_appActor);
            newEvents << e;
        }
        events = newEvents;
    }
    m_log->setEventTemplates(events);
}

void LogBrowser::applyActorFilter(bool yes)
{
    m_actorFilterActive = yes;
    updateFilter();
}

void LogBrowser::handleActivation(const QModelIndex &idx)
{
    DataModel::Event event = idx.data(LogModel::EventRole).value<DataModel::Event>();
    emit activated(event);
}

} // namespace QZeitgeist

#include "logbrowser.moc"
