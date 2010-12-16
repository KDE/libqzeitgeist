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

#include "QtZeitgeist/QtZeitgeist"

#include "QtZeitgeist/DataModel/DataSource"
#include "QtZeitgeist/DataModel/Event"
#include "QtZeitgeist/DataModel/TimeRange"

#include <QDBusMetaType>

namespace QtZeitgeist
{

void init()
{
    static bool registered = false;

    if (!registered) {
        qDBusRegisterMetaType<QtZeitgeist::DataModel::DataSource>();
        qDBusRegisterMetaType<QtZeitgeist::DataModel::DataSourceList>();
        qDBusRegisterMetaType<QtZeitgeist::DataModel::Event>();
        qDBusRegisterMetaType<QtZeitgeist::DataModel::EventList>();
        qDBusRegisterMetaType<QtZeitgeist::DataModel::EventIdList>();
        qDBusRegisterMetaType<QtZeitgeist::DataModel::TimeRange>();

        registered = true;
    }
}

};
