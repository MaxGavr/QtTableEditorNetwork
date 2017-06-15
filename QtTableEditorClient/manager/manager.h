#pragma once

#include "../model/database.h"

class DatabaseManager
{

public:
    DatabaseManager(StudentDatabase *database);

    const StudentDatabase &getDatabase() const;
    void setDatabase(StudentDatabase *value);

    bool loadDatabaseFromFile(const QString &fileName);
    bool saveDatabaseToFile(const QString &fileName);

    void addStudent(const QString &first, const QString &second, const QString &middle,
                    const QDate &birth, const QDate &enrollment, const QDate &graduation);

    void setSearchPattern(const StudentSearchPattern &pattern);
    void resetSearchPattern();

    void deleteStudents(const StudentSearchPattern &pattern);

private:
    StudentDatabase *database;
};
