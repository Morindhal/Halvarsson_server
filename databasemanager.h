#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QtSql>
#include <QtSql/QSqlDriver>

class DatabaseManager
{
public:
    DatabaseManager();
    QSqlDatabase myDatabase;

signals:

public slots:
private:
};

#endif // DATABASEMANAGER_H
