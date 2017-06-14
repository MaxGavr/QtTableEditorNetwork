#include "database.h"
#include <math.h>

StudentDatabase::StudentDatabase(QObject *parent)
    : QObject(parent), xml(this)
{
}

Student StudentDatabase::getStudent(int index) const
{
    Student student;
    if (index < countStudents())
        student = students.at(index);
    return student;
}

StudentDatabase::StudentSet StudentDatabase::getSetOfStudents(int index, int amount) const
{
    if (!validatePageBounds(index, amount))
        return StudentSet();

    int initialPosition = index * amount;
    return getStudents().mid(initialPosition, amount);
}

void StudentDatabase::setSearchPattern(const StudentSearchPattern &pattern)
{
    this->pattern = pattern;
    if (!this->pattern.isEmpty())
        filterStudents();
    else
        clearSearchResult();
}

void StudentDatabase::filterStudents()
{
    clearSearchResult();
    foreach (Student::const_ref student, students)
        if (this->pattern(student))
            filteredStudents.append(student);
}

void StudentDatabase::clearSearchResult()
{
    filteredStudents.clear();
}

void StudentDatabase::addStudent(Student student, bool notify)
{
    if (!contains(student))
    {
        if (validateStudent(student))
        {
            students.append(student);
            if (notify)
                emit studentAdded();
        }
        else
            emit invalidInsertion();
    }
    else
        emit duplicateInsertion();
}

bool StudentDatabase::removeStudent(Student::const_ref student, bool notify)
{
    if (contains(student))
    {
        students.removeOne(student);
        if (notify)
            emit studentDeleted();
        return true;
    }
    return false;
}

void StudentDatabase::removeStudents(const StudentSearchPattern &pattern)
{
    setSearchPattern(pattern);
    int deletedStudents = 0;

    foreach (Student::const_ref student, filteredStudents)
        if (removeStudent(student, false))
            deletedStudents++;

    setSearchPattern(StudentSearchPattern());
    emit studentsDeleted(deletedStudents);
}

bool StudentDatabase::contains(Student::const_ref student) const
{
    return students.contains(student);
}

bool StudentDatabase::validateStudent(Student::const_ref student) const
{
    bool hasFirstAndSecondName = !student.getFirstName().isEmpty() &&
                                 !student.getSecondName().isEmpty();

    int studentAge = student.getBirthDate().daysTo(QDate::currentDate());
    bool isMature = (studentAge / 365) >= MIN_AGE;

    bool correctDates = student.getEnrollmentDate() < student.getGraduationDate() &&
                        student.getEnrollmentDate() > student.getBirthDate() &&
                        student.getGraduationDate() > student.getBirthDate();

    return hasFirstAndSecondName && isMature && correctDates;
}

int StudentDatabase::countStudents() const
{
    return getStudents().count();
}

int StudentDatabase::countPages(int studentsPerPage) const
{
    return ceil(countStudents() / (double)studentsPerPage);
}

XmlHandler *StudentDatabase::getXmlHandler()
{
    return &xml;
}

const StudentDatabase::StudentSet &StudentDatabase::getStudents() const
{
    if (this->pattern.isEmpty())
        return students;
    else
        return filteredStudents;
}

void StudentDatabase::clear()
{
    foreach (Student::const_ref student, students)
        removeStudent(student);
}

bool StudentDatabase::validatePageBounds(int pageIndex, int studentsPerPage) const
{
    bool nonNegative = (pageIndex >= 0) && (studentsPerPage >= 0);
    bool zeroPage = (pageIndex == 0);
    return nonNegative && ((pageIndex < countPages(studentsPerPage)) || zeroPage);
}

bool StudentDatabase::isEmpty() const
{
    return countStudents() == 0;
}


