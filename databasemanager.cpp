#include "databasemanager.h"

DatabaseManager::DatabaseManager()
{
    myDatabase = QSqlDatabase::addDatabase("QMYSQL");

    myDatabase.setHostName("localhost");
    myDatabase.setDatabaseName("nhl");
    myDatabase.setUserName("root");
    myDatabase.setPassword("everlasting2");
    myDatabase.setPort(3306);
    bool open = myDatabase.open();
    if(open)
        qDebug() << "DB open!";
    else
        qDebug() << "Failed to connect to root mysql admin\n" << myDatabase.lastError() << "\n" << myDatabase.port();
    qDebug() << myDatabase.isValid();
}
