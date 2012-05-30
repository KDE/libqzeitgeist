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

#ifndef LOGBROWSER_H
#define LOGBROWSER_H

#include <QtGui/QWidget>
#include "DataModel/event.h"

class QAbstractButton;
class QAction;
class QAbstractItemView;
class QHBoxLayout;
class QSignalMapper;
class QCheckBox;
class QModelIndex;

namespace QZeitgeist
{

class LogModel;

typedef struct {
  QZeitgeist::DataModel::EventList events;
  QAbstractButton *button;
  QAction *action;
  QString *name;
} LogFilter;

class QZEITGEIST_EXPORT LogBrowser : public QWidget {
    Q_OBJECT

    public:
      LogBrowser(QWidget *parent = 0);
      virtual ~LogBrowser();

      QAction *addEventFilter(const QZeitgeist::DataModel::EventList &templates, const QString &name);
      void setApplicationActor(const QString &actor, const QString &name);

    signals:
      void activated(const QZeitgeist::DataModel::Event &event);

    private slots:
      void updateFilter();
      void applyFilter(int id);
      void applyActorFilter(bool yes);
      void handleActivation(const QModelIndex &idx);

    private:
      int m_nextID;
      QAbstractItemView *m_logView;
      LogModel *m_log;
      QMap<int, LogFilter> m_filters;
      QZeitgeist::DataModel::EventList m_activeFilter;
      QHBoxLayout *m_filterLayout;
      QSignalMapper *m_actionMapper;
      QString m_appActor;
      bool m_actorFilterActive;
      QCheckBox *m_actorFilterCheck;
};

} // namespace QZeitgeist

#endif // LOGBROWSER_H
