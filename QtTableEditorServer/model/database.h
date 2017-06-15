#pragma once

#include <QObject>
#include <QVector>
#include <QXmlStreamReader>
#include <QFile>

#include "student.h"
#include "searchpattern.h"
#include "xmlhandler.h"

class StudentDatabase : public QObject
{
    Q_OBJECT
public:
    friend class XmlHandler;

    explicit StudentDatabase(QObject *parent = 0);

    Student getStudent(int index) const;
    Student::StudentSet getSetOfStudents(int index, int amount) const;

    void setSearchPattern(const StudentSearchPattern &pattern);

    void addStudent(Student student, bool notify = true);
    bool removeStudent(Student::const_ref student, bool notify = true);
    void removeStudents(const StudentSearchPattern &pattern);

    bool contains(Student::const_ref student) const;
    bool validateStudent(Student::const_ref student) const;
    bool validatePageBounds(int pageIndex, int studentsPerPage) const;

    bool isEmpty() const;
    int countStudents() const;
    int countPages(int studentsPerPage) const;

    XmlHandler *getXmlHandler();

signals:
    void studentAdded();
    void studentDeleted();
    void studentsDeleted(int amount);
    void invalidInsertion();
    void duplicateInsertion();

private:
    const Student::StudentSet &getStudents() const;

    void filterStudents();
    void clearSearchResult();
    void clear();

    StudentSearchPattern pattern;

    Student::StudentSet filteredStudents;
    Student::StudentSet students;

    XmlHandler xml;

    const int MIN_AGE = 18;
};
