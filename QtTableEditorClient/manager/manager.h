#pragma once

#include <QObject>
#include <QAbstractSocket>

#include "../socket/socketadapter.h"
#include "../model/student.h"

class QString;
class QDate;
class StudentSearchPattern;
class QHostAddress;

class DatabaseManager : public QObject
{
    Q_OBJECT
public:
    DatabaseManager(QObject* parent = 0);

    TcpSocketAdapter* getSocket();

    void connectToServer(const QHostAddress& address, int port);

    bool loadDatabaseFromFile(const QString& fileName);
    bool saveDatabaseToFile(const QString& fileName);

    void addStudent(const QString& first, const QString& second, const QString& middle,
                    const QDate& birth, const QDate& enrollment, const QDate& graduation);
    void getPage(int index, int studentsPerPage);

    void countPages(int studentsPerPage);
    void validatePageBounds(int index, int studentsPerPage);

    void setSearchPattern(const StudentSearchPattern& pattern);
    void resetSearchPattern();

    void deleteStudents(const StudentSearchPattern& pattern);

public slots:
    void parseRequest(TcpSocketAdapter::REQUESTS requestId, const QString& data);

signals:
    void databaseUpdated();
    void pageRetrieved(Student::StudentSet page);
    void pageValidated(bool isValid);
    void pageCounted(int pages);

    void invalidStudentInserted();
    void duplicateStudentInserted();

private:
    TcpSocketAdapter* m_socket;
};
