#pragma once

#include "student.h"
#include <QVector>
#include <functional>

class StudentSearchPattern
{
public:
    using Comparator = std::function <bool (QString)>;
    static const int NUMBER_OF_CRITERIA;

    StudentSearchPattern();
    StudentSearchPattern(const StudentSearchPattern &pattern);

    QString toString() const;
    void fromString(const QString& str);

    bool isEmpty() const;
    void reset();

    bool operator() (Student::const_ref student) const;

    void setFirstName(const QString &value);
    void setSecondName(const QString &value);
    void setMiddleName(const QString &value);

    void setBirthDateBounds(const QDate &lower, const QDate &higher);
    void setEnrollDateBounds(const QDate &lower, const QDate &higher);
    void setGraduateDateBounds(const QDate &lower, const QDate &higher);

private:
    QVector <bool> criteria;
    QVector <Comparator> comparators;

    QString firstName;
    QString secondName;
    QString middleName;

    QDate birthDateLowerBound;
    QDate birthDateHigherBound;

    QDate enrollDateLowerBound;
    QDate enrollDateHigherBound;

    QDate graduateDateLowerBound;
    QDate graduateDateHigherBound;
};
