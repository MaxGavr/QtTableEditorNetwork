#include "student.h"

const QString Student::DATE_FORMAT = "dd.MM.yyyy";
const QChar Student::STRING_SEPARATOR = '#';

QString Student::studentsToString(const Student::StudentSet &students)
{
    QString result;
    foreach (const Student& student, students)
    {
        result += Student::toString(student) + '|';
    }
    result.chop(1);
    return result;
}

Student::StudentSet Student::studentsFromString(const QString& str)
{
    QStringList list = str.split(QChar('|'));
    Student::StudentSet students;
    foreach (const QString& s, list)
    {
        students.append(Student::fromString(s));
    }
    return students;
}

QString Student::toString(const_ref student)
{
    QString result;
    result += student.getFirstName() + Student::STRING_SEPARATOR +
              student.getSecondName() + Student::STRING_SEPARATOR +
              student.getMiddleName() + Student::STRING_SEPARATOR +
              student.getBirthDateString() + Student::STRING_SEPARATOR +
              student.getEnrollmentDateString() + Student::STRING_SEPARATOR +
              student.getGraduationDateString();
    return result;
}

Student Student::fromString(const QString &str)
{
    QStringList list = str.split(Student::STRING_SEPARATOR);
    Student student;
    student.setFirstName(list[0]);
    student.setSecondName(list[1]);
    student.setMiddleName(list[2]);
    student.setBirthDate(QDate::fromString(list[3], Student::DATE_FORMAT));
    student.setEnrollmentDate(QDate::fromString(list[4], Student::DATE_FORMAT));
    student.setGraduationDate(QDate::fromString(list[5], Student::DATE_FORMAT));
    return student;
}

Student::Student()
    : Student("---", "---", "---", QDate::currentDate(), QDate::currentDate(), QDate::currentDate())
{
}

Student::Student(const QString &first, const QString &second, const QString &middle,
                 const QDate &birth, const QDate &enrollment, const QDate &graduation)
{
    setFirstName(first);
    setSecondName(second);
    setMiddleName(middle);

    setBirthDate(birth);
    setEnrollmentDate(enrollment);
    setGraduationDate(graduation);
}

Student::Student(Student::const_ref student)
    : Student(student.getFirstName(), student.getSecondName(), student.getMiddleName(),
              student.getBirthDate(), student.getEnrollmentDate(), student.getGraduationDate())
{
}

QString Student::getByKey(KEYS key) const
{
    QString result;
    switch (key)
    {
    case KEYS::FIRST_NAME:
        result = getFirstName();
        break;
    case KEYS::SECOND_NAME:
        result = getSecondName();
        break;
    case KEYS::MIDDLE_NAME:
        result = getMiddleName();
        break;
    case KEYS::BIRTH_DATE:
        result = getBirthDateString();
        break;
    case KEYS::ENROLL_DATE:
        result = getEnrollmentDateString();
        break;
    case KEYS::GRADUATE_DATE:
        result = getGraduationDateString();
        break;
    }
    return result;
}

QString Student::getFirstName() const
{
    return firstName;
}

void Student::setFirstName(const QString &value)
{
    firstName = capitalizeString(value);
}

QString Student::getSecondName() const
{
    return secondName;
}

void Student::setSecondName(const QString &value)
{
    secondName = capitalizeString(value);
}

QString Student::getMiddleName() const
{
    return middleName;
}

void Student::setMiddleName(const QString &value)
{
    middleName = capitalizeString(value);
}

QString Student::getFullName() const
{
    return QString("%1 %2 %3").arg(getSecondName()).arg(getFirstName()).arg(getMiddleName());
}

QDate Student::getBirthDate() const
{
    return birthDate;
}

QString Student::getBirthDateString() const
{
    return getBirthDate().toString(DATE_FORMAT);
}

void Student::setBirthDate(const QDate &value)
{
    if (!value.isValid() || value.isNull())
        birthDate = QDate::currentDate();
    else
        birthDate = value;
}

QDate Student::getEnrollmentDate() const
{
    return enrollmentDate;
}

QString Student::getEnrollmentDateString() const
{
    return getEnrollmentDate().toString(DATE_FORMAT);
}

void Student::setEnrollmentDate(const QDate &value)
{
    if (!value.isValid() || value.isNull())
        enrollmentDate = QDate::currentDate();
    else
        enrollmentDate = value;
}

QDate Student::getGraduationDate() const
{
    return graduationDate;
}

QString Student::getGraduationDateString() const
{
    return getGraduationDate().toString(DATE_FORMAT);
}

void Student::setGraduationDate(const QDate &value)
{
    if (!value.isValid() || value.isNull())
        graduationDate = QDate::currentDate();
    else
        graduationDate = value;
}

bool Student::operator==(const_ref student) const
{
    bool equalNames = (getFullName() == student.getFullName());
    bool equalDates = (getBirthDate() == student.getBirthDate()) &&
                      (getEnrollmentDate() == student.getEnrollmentDate()) &&
                      (getGraduationDate() == student.getGraduationDate());

    return equalNames && equalDates;
}

bool Student::operator!=(Student::const_ref student) const
{
    return !(*this == student);
}

QString Student::capitalizeString(const QString &str)
{
    QString capitalized = str;
    if (!str.isEmpty())
        capitalized[0] = capitalized[0].toUpper();
    return capitalized;
}
