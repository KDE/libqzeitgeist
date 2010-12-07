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

#include <QDBusConnection>
#include <QDBusMessage>
#include <QDBusArgument>
#include <QDBusPendingCall>
#include <QDBusMetaType>
#include <QDBusAbstractInterface>

#include <QDebug>

struct SomeStrangeStructure
{
    QStringList list;
    QList < QStringList > lists;
    QByteArray bytes;
};
Q_DECLARE_METATYPE(SomeStrangeStructure)

/**
 *
 */
class ZeitgeistDBusInterface: public QDBusAbstractInterface {
public:
    ZeitgeistDBusInterface(QObject * parent = NULL)
        : QDBusAbstractInterface(
            "org.gnome.zeitgeist.Engine",
            "/org/gnome/zeitgeist/log/activity",
            "org.gnome.zeitgeist.Log",
            QDBusConnection::sessionBus(),
            parent
        )
    {
    }

    virtual ~ZeitgeistDBusInterface()
    {
    }

private:
    /* data */
};

QDBusArgument & operator << (QDBusArgument & argument, const SomeStrangeStructure & event)
{
    argument.beginStructure();
    argument
        << event.list
        << event.lists
        << event.bytes
        ;
    argument.endStructure();

    return argument;
}

const QDBusArgument & operator >> (const QDBusArgument & argument, SomeStrangeStructure & event)
{
    argument.beginStructure();
    argument
        >> event.list
        >> event.lists
        >> event.bytes
        ;
    argument.endStructure();
    return argument;
}



TestZeitgeist::TestZeitgeist(int argc, char ** argv)
    : QCoreApplication(argc, argv)
{
    qDBusRegisterMetaType < SomeStrangeStructure > ();

    if (arguments().contains("Quit")) {
        Quit();
    } else if (arguments().contains("InsertEvents")) {
        InsertEvents();
    }
}

void TestZeitgeist::Quit() const
{
    qDebug() << "Trying to invoke a method";
    QDBusMessage call = QDBusMessage::createMethodCall(
            "org.gnome.zeitgeist.Engine",
            "/org/gnome/zeitgeist/log/activity",
            "org.gnome.zeitgeist.Log",
            "Quit");
    qDebug() << "err" << call.errorMessage();
    qDebug() << QDBusConnection::sessionBus().call(call);
    qDebug() << "err" << call.errorMessage();

}

void TestZeitgeist::InsertEvents() const
{
    ZeitgeistDBusInterface z;

    QDBusArgument argument;
    argument.beginArray();

    for (int i = 0; i < 10; i++) {
        SomeStrangeStructure event;

        event.list << "asd" << "ASD";
        event.lists << (QStringList() << "asdfgh" << "QWEASD");
        event.bytes = QString("ASDASDASD").toAscii();
    }

    argument.endArray();

    // qDebug() << "Trying to invoke a method";

    // QList < QVariant > list;
    // list << QVariant(argument);

    // qDebug() <<
    // z.callWithArgumentList(QDBus::Block, "InsertEvents", list);


}

TestZeitgeist::~TestZeitgeist()
{
}

#include "test-zeitgeist.moc"

