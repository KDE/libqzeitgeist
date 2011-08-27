/*
 * This file is part of QZeitgeist.
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


#ifndef QZEITGEIST_H_
#define QZEITGEIST_H_

#include <QtGlobal>

#ifndef QZEITGEIST_EXPORT
#   define QZEITGEIST_EXPORT __attribute__ ((visibility ("default")))
#endif

#ifndef QZEITGEIST_DEPRECATED
#define QZEITGEIST_DEPRECATED Q_DECL_DEPRECATED
#endif

namespace QZeitgeist
{

/**
 * Initialize the library.
 *
 * Before start using the QZeitgeist library it's necessary to call the init
 * function. The function  will get the library ready to use, initalizing and
 * registering custom types.
 * Note: It's really important to call this function before using the library.
 */
QZEITGEIST_EXPORT void init();

};
#endif // QZEITGEIST_H_
