/*
    Chennzeihhan - Vehicle Registration Code Database for SailfishOS
    Copyright (C) 2014  Buschtrommel/Matthias Fehring

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/

#include "dbmanager.h"
#include "globals.h"
#include <QDebug>

DbManager::DbManager(QObject *parent) :
    QObject(parent)
{
}


bool DbManager::checkDB()
{
    bool ret;
    QFile dbFile(QDir::homePath().append(DATA_DIR).append("/carplates.sqlite"));
    if (dbFile.exists())
    {
        ret = openDB();
    } else {
        ret = false;
    }

    return ret;
}


bool DbManager::openDB()
{
    db = QSqlDatabase::addDatabase("QSQLITE");

    db.setDatabaseName(QDir::homePath().append(DATA_DIR).append("/carplates.sqlite"));
    db.setConnectOptions("QSQLITE_OPEN_READONLY");

    bool dbStatus = db.open();

    if (dbStatus)
        tables = db.tables(QSql::Tables);

    return dbStatus;
}


bool DbManager::closeDB()
{
    if (db.isOpen())
        db.close();
    return true;
}
