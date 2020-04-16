/*
* Copyright (C) 2019 Tianjin KYLIN Information Technology Co., Ltd.
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 3, or (at your option)
* any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; if not, see <http://www.gnu.org/licenses/&gt;.
*
*/
#include "notedata.h"
#include <QDataStream>

NoteData::NoteData(QObject *parent)
    : QObject(parent),
      m_isModified(false),
      m_isSelected(false),
      m_scrollBarPosition(0)
{

}

int NoteData::id() const
{
    return m_id;
}

void NoteData::setId(const int &id)
{
    m_id = id;
}

QString NoteData::fullTitle() const
{
    return m_fullTitle;
}

void NoteData::setFullTitle(const QString &fullTitle)
{
    m_fullTitle = fullTitle;
}

int NoteData::notecolor() const
{
    return m_notecolor;
}

void NoteData::setNoteColor(const int &notecolor)
{
    m_notecolor = notecolor;
}

QDateTime NoteData::lastModificationdateTime() const
{
    return m_lastModificationDateTime;
}

void NoteData::setLastModificationDateTime(const QDateTime &lastModificationdateTime)
{
    m_lastModificationDateTime = lastModificationdateTime;
}

QString NoteData::content() const
{
    return m_content;
}

void NoteData::setContent(const QString &content)
{
    m_content = content;
}

bool NoteData::isModified() const
{
    return m_isModified;
}

void NoteData::setModified(bool isModified)
{
    m_isModified = isModified;
}

bool NoteData::isSelected() const
{
    return m_isSelected;
}

void NoteData::setSelected(bool isSelected)
{
    m_isSelected = isSelected;
}

int NoteData::scrollBarPosition() const
{
    return m_scrollBarPosition;
}

void NoteData::setScrollBarPosition(int scrollBarPosition)
{
    m_scrollBarPosition = scrollBarPosition;
}

QDateTime NoteData::deletionDateTime() const
{
    return m_deletionDateTime;
}

void NoteData::setDeletionDateTime(const QDateTime& deletionDateTime)
{
    m_deletionDateTime = deletionDateTime;
}

QDateTime NoteData::creationDateTime() const
{
    return m_creationDateTime;
}

void NoteData::setCreationDateTime(const QDateTime&creationDateTime)
{
    m_creationDateTime = creationDateTime;
}

QDataStream &operator<<(QDataStream &stream, const NoteData* noteData) {
    return stream << noteData->id() << noteData->fullTitle() << noteData->creationDateTime() \
                  << noteData->lastModificationdateTime() << noteData->content() << noteData->notecolor();
}

QDataStream &operator>>(QDataStream &stream, NoteData* &noteData){
    noteData = new NoteData();
    int id;
    int notecolor;
    QString fullTitle;
    QDateTime lastModificationDateTime;
    QDateTime creationDateTime;
    QString content;
    stream >> id >> fullTitle >> creationDateTime >> lastModificationDateTime >> content;
    noteData->setId(id);
    noteData->setFullTitle(fullTitle);
    noteData->setLastModificationDateTime(lastModificationDateTime);
    noteData->setCreationDateTime(creationDateTime);
    noteData->setContent(content);
    noteData->setNoteColor(notecolor);
    return stream;
}

