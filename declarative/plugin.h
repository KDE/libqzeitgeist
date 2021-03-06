/*
 * This file is part of QZeitgeist.
 *
 * Copyright (C) 2011 Trever Fischer <tdfischer@fedoraproject.org>
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

#ifndef PLUGIN_H
#define PLUGIN_H

#include <QtDeclarative/QDeclarativeExtensionPlugin>
#include <QtDeclarative/qdeclarative.h>

namespace QZeitgeist
{
namespace Declarative
{

class Plugin : public QDeclarativeExtensionPlugin {
    Q_OBJECT
public:
    Plugin(QObject *parent = 0);
    void registerTypes(const char *uri);
};

} // namespace Declarative
} // namespace QZeitgeist

Q_EXPORT_PLUGIN2(qzeitgeistdeclarativeplugin, QZeitgeist::Declarative::Plugin);

#endif // PLUGIN_H
