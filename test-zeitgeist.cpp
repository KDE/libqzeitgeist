/*
 * Copyright (c) 2010 Ivan Cukic <ivan.cukic(at)kde.org>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License version 2 as published by the Free Software Foundation.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public License
 * along with this library; see the file COPYING.LIB.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#include "test-zeitgeist.h"
#include "zeitgeist_interface.h"

TestZeitgeist::TestZeitgeist(int argc, char ** argv)
    : QCoreApplication(argc, argv),
      zeitgeist(
              "org.gnome.zeitgeist.Engine",
              "/org/gnome/zeitgeist/log/activity",
              QDBusConnection::sessionBus()
              )
{
    if (arguments().contains("Quit")) {
        Quit();
    } else if (arguments().contains("InsertEvents")) {
        InsertEvents();
    } else {
        qDebug() << "Arguments not valid";
    }
}

void TestZeitgeist::Quit()
{
    qDebug() << "Trying to invoke a method";
    zeitgeist.Quit();
}

void TestZeitgeist::InsertEvents()
{
}

TestZeitgeist::~TestZeitgeist()
{
}

#include "test-zeitgeist.moc"

