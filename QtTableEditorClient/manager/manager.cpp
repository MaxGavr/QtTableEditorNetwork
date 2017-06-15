#include "manager.h"

DatabaseManager::DatabaseManager(StudentDatabase *database)
{
    setDatabase(database);
}

void DatabaseManager::setDatabase(StudentDatabase *value)
{
    database = value;
}

bool DatabaseManager::saveDatabaseToFile(const QString &fileName)
{
    return database->getXmlHandler()->writeToFile(fileName);
}

bool DatabaseManager::loadDatabaseFromFile(const QString &fileName)
{
    return database->getXmlHandler()->readFromFile(fileName);
}

void DatabaseManager::addStudent(const QString &first, const QString &second, const QString &middle,
                                 const QDate &birth, const QDate &enrollment, const QDate &graduation)
{
    database->addStudent(Student(first, second, middle, birth, enrollment, graduation));
}

void DatabaseManager::setSearchPattern(const StudentSearchPattern &pattern)
{
    database->setSearchPattern(pattern);
}

void DatabaseManager::deleteStudents(const StudentSearchPattern &pattern)
{
    database->removeStudents(pattern);
}

void DatabaseManager::resetSearchPattern()
{
    database->setSearchPattern(StudentSearchPattern());
}

const StudentDatabase &DatabaseManager::getDatabase() const
{
    if (database)
        return *database;
    else
        throw std::logic_error("Controller exception: database wasn't set!");
}
