#pragma once

#include <QString>
#include <QDate>

class Student
{
public:
    using const_ref = const Student&;

    enum KEYS {FIRST_NAME = 0, SECOND_NAME, MIDDLE_NAME,
               BIRTH_DATE, ENROLL_DATE, GRADUATE_DATE};

    static const QString DATE_FORMAT;

    Student();
    Student(const QString& first, const QString& second, const QString& middle,
            const QDate& birth, const QDate& enrollment, const QDate& graduation);
    Student(const_ref student);

    QString getByKey(KEYS key) const;

    QString getFirstName() const;
    void setFirstName(const QString &value);
    QString getSecondName() const;
    void setSecondName(const QString &value);
    QString getMiddleName() const;
    void setMiddleName(const QString &value);

    QString getFullName() const;

    QDate getBirthDate() const;
    QString getBirthDateString() const;
    void setBirthDate(const QDate &value);
    QDate getEnrollmentDate() const;
    QString getEnrollmentDateString() const;
    void setEnrollmentDate(const QDate &value);
    QDate getGraduationDate() const;
    QString getGraduationDateString() const;
    void setGraduationDate(const QDate &value);

    bool operator== (const_ref student) const;
    bool operator!= (const_ref student) const;

private:
    QString capitalizeString(const QString& str);

    QString firstName;
    QString secondName;
    QString middleName;

    QDate birthDate;
    QDate enrollmentDate;
    QDate graduationDate;
};
