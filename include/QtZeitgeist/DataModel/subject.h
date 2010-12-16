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


#ifndef QTZEITGEIST_SUBJECT_H_
#define QTZEITGEIST_SUBJECT_H_

#include <QList>
#include <QObject>

namespace QtZeitgeist
{

namespace DataModel
{

class SubjectPrivate;

/**
 * @class Subject subject.h subject.h
 * @brief The Subject objects abstract subjects returned from Zeitgeist queries.
 *
 * The Subject class is one of the primary elements for communicating  with the
 * Zeitgeist daemon.
 *
 * @see Event.
 *
 * @author Jeremy Whiting <jeremy.whiting@collabora.co.uk>
 */
class Q_DECL_EXPORT Subject : public QObject
{
Q_OBJECT
    Q_PROPERTY(QString uri READ uri WRITE setUri)
    Q_PROPERTY(QString interpretation READ interpretation WRITE setInterpretation)
    Q_PROPERTY(QString manifestation READ manifestation WRITE setManifestation)
    Q_PROPERTY(QString origin READ origin WRITE setOrigin)
    Q_PROPERTY(QString mimeType READ mimeType WRITE setMimeType)
    Q_PROPERTY(QString text READ text WRITE setText)
    Q_PROPERTY(QString storage READ storage WRITE setStorage)

public:

    /**
     * Default constructor.
     */
    explicit Subject(QObject *parent = 0);

    /**
     * Copy constructor.
     */
    Subject(const Subject &source, QObject *parent = 0);

    /**
     * Destructor.
     */
    virtual ~Subject();

    /**
     * The URI of the subject.
     *
     * @returns the URI of the subject.
     */
    QString uri() const;

    /**
     * Set the subject URI.
     *
     * @param uri the new URI of the subject.
     */
    void setUri(const QString &uri);

    /**
     * The subject interpretation represents what type of subject it is.
     *
     * @return the subject interpretation as a URI or empty if unset.
     */
    QString interpretation() const;

    /**
     * Set the subject interpretation.
     *
     * @param interpretation the URI designating the interpretation type of
     * the subject.
     */
    void setInterpretation(const QString &interpretation);

    /**
     * The subject manifestation represents how did it happen.
     *
     * @return the subject interpretation as a URI or empty if unset.
     */
    QString manifestation() const;

    /**
     * Set the subject manifestation.
     *
     * @param manifestation the URI designating the manifestation type of
     * the subject.
     */
    void setManifestation(const QString &manifestation);

    /**
     * The origin of the subject.
     *
     * @returns the origin of the subject.
     */
    QString origin() const;

    /**
     * Set the origin of the subject.
     *
     * @param origin the new origin of theh subject.
     */
    void setOrigin(const QString &origin);

    /**
     * The mime-type of the subject.
     *
     * @returns the mime-type of the subject.
     */
    QString mimeType() const;

    /**
     * Set the mime-type of the subject.
     *
     * @param mimeType the new mime-type of the subject.
     */
    void setMimeType(const QString &mimeType);

    /**
     * The text of the subject.
     *
     * @returns the text of the subject.
     */
    QString text() const;

    /**
     * Set the text of the subject.
     *
     * @param text the new text of the subject.
     */
    void setText(const QString &text);

    /**
     * The storage of the subject.
     *
     * @returns the storage of the subject.
     */
    QString storage() const;

    /**
     * Set the storage of the subject.
     *
     * @param storage the new storage of the subject.
     */
    void setStorage(const QString &storage);

    Subject & operator = (const Subject &source);

private:

    // D Pointer.
    class SubjectPrivate * const d;
};

// Create additional types.
typedef QList<Subject> SubjectList;

};

};

#endif // QTZEITGEIST_SUBJECT_H_
