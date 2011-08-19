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


#include "QtZeitgeist/DataModel/Subject"


namespace QtZeitgeist
{

namespace DataModel
{

class SubjectPrivate
{
public :
    QString uri;
    QString origin;
    QString mimeType;
    QString text;
    QString storage;
    QString interpretation;
    QString manifestation;
};

Subject::Subject(QObject *parent)
    : d(new SubjectPrivate())
{
    Q_ASSERT(d);
}

Subject::Subject(const Subject & source, QObject *parent)
    : d(new SubjectPrivate())
{
    Q_ASSERT(d);

    // Copy the source attribute's value.
    d->uri = source.d->uri;
    d->origin = source.d->origin;
    d->mimeType = source.d->mimeType;
    d->text = source.d->text;
    d->storage = source.d->storage;
    d->interpretation = source.d->interpretation;
    d->manifestation = source.d->manifestation;
}

Subject::~Subject()
{
    delete d;
}

QString Subject::uri() const
{
    return d->uri;
}

void Subject::setUri(const QString &uri)
{
    d->uri = uri;
}

QString Subject::interpretation() const
{
    return d->interpretation;
}

void Subject::setInterpretation(const QString &interpretation)
{
    d->interpretation = interpretation;
}

QString Subject::manifestation() const
{
    return d->manifestation;
}

void Subject::setManifestation(const QString &manifestation)
{
    d->manifestation = manifestation;
}

QString Subject::origin() const
{
    return d->origin;
}

void Subject::setOrigin(const QString &origin)
{
    d->origin = origin;
}

QString Subject::mimeType() const
{
    return d->mimeType;
}

void Subject::setMimeType(const QString &mimeType)
{
    d->mimeType = mimeType;
}

QString Subject::text() const
{
    return d->text;
}

void Subject::setText(const QString &text)
{
    d->text = text;
}

QString Subject::storage() const
{
    return d->storage;
}

void Subject::setStorage(const QString &storage)
{
    d->storage = storage;
}

Subject &Subject::operator = (const Subject & source)
{
    // Copy the source attribute's value.
    if (this != &source) {
        d->uri = source.d->uri;
        d->interpretation = source.d->interpretation;
        d->manifestation = source.d->manifestation;
        d->origin = source.d->origin;
        d->mimeType = source.d->mimeType;
        d->text = source.d->text;
        d->storage = source.d->storage;
    }

    return *this;
}

};

};
