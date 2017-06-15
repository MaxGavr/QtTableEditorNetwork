#pragma once

class QString;
class QDate;
class StudentSearchPattern;

class TcpSocketAdapter;

class DatabaseManager
{

public:
    DatabaseManager();

    bool loadDatabaseFromFile(const QString& fileName);
    bool saveDatabaseToFile(const QString& fileName);

    void addStudent(const QString& first, const QString& second, const QString& middle,
                    const QDate& birth, const QDate& enrollment, const QDate& graduation);

    void setSearchPattern(const StudentSearchPattern& pattern);
    void resetSearchPattern();

    void deleteStudents(const StudentSearchPattern& pattern);

private:
    TcpSocketAdapter* m_socket;
};
