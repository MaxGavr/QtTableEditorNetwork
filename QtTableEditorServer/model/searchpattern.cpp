#include "searchpattern.h"
#include <algorithm>

const int StudentSearchPattern::NUMBER_OF_CRITERIA = 6;

StudentSearchPattern::StudentSearchPattern()
{
    criteria = QVector<bool>(NUMBER_OF_CRITERIA, false);
    comparators = QVector<Comparator>(NUMBER_OF_CRITERIA);

    comparators[Student::KEYS::FIRST_NAME] = [this](QString name){
        return name == this->firstName;
    };
    comparators[Student::KEYS::SECOND_NAME] = [this](QString name){
        return name == this->secondName;
    };
    comparators[Student::KEYS::MIDDLE_NAME] = [this](QString name){
        return name == this->middleName;
    };

    comparators[Student::KEYS::BIRTH_DATE] = [this](QString dateString){
        QDate date = QDate::fromString(dateString, Student::DATE_FORMAT);
        return (date >= this->birthDateLowerBound) && (date <= this->birthDateHigherBound);
    };
    comparators[Student::KEYS::ENROLL_DATE] = [this](QString dateString){
        QDate date = QDate::fromString(dateString, Student::DATE_FORMAT);
        return (date >= this->enrollDateLowerBound) && (date <= this->enrollDateHigherBound);
    };
    comparators[Student::KEYS::GRADUATE_DATE] = [this](QString dateString){
        QDate date = QDate::fromString(dateString, Student::DATE_FORMAT);
        return (date >= this->graduateDateLowerBound) && (date <= this->graduateDateHigherBound);
    };
}

StudentSearchPattern::StudentSearchPattern(const StudentSearchPattern &pattern)
{
    this->criteria = pattern.criteria;
    this->comparators = pattern.comparators;

    this->firstName = pattern.firstName;
    this->secondName = pattern.secondName;
    this->middleName = pattern.middleName;

    this->birthDateLowerBound = pattern.birthDateLowerBound;
    this->birthDateHigherBound = pattern.birthDateHigherBound;

    this->enrollDateLowerBound = pattern.enrollDateLowerBound;
    this->enrollDateHigherBound = pattern.enrollDateHigherBound;

    this->graduateDateLowerBound = pattern.graduateDateLowerBound;
    this->graduateDateHigherBound = pattern.graduateDateHigherBound;
}

bool StudentSearchPattern::isEmpty() const
{
    return std::all_of(criteria.begin(), criteria.end(), std::logical_not<bool>());
}

void StudentSearchPattern::reset()
{
    criteria.fill(false);
}

bool StudentSearchPattern::operator()(Student::const_ref student) const
{
    for (int i = Student::KEYS::FIRST_NAME; i != Student::KEYS::GRADUATE_DATE; ++i)
    {
        Student::KEYS key = static_cast<Student::KEYS>(i);
        if (criteria[key] && !comparators[key](student.getByKey(key)))
            return false;
    }
    return true;
}

void StudentSearchPattern::setFirstName(const QString &value)
{
    firstName = value;
    criteria[Student::KEYS::FIRST_NAME] = true;
}

void StudentSearchPattern::setSecondName(const QString &value)
{
    secondName = value;
    criteria[Student::KEYS::SECOND_NAME] = true;
}

void StudentSearchPattern::setMiddleName(const QString &value)
{
    middleName = value;
    criteria[Student::KEYS::MIDDLE_NAME] = true;
}

void StudentSearchPattern::setBirthDateBounds(const QDate &lower, const QDate &higher)
{
    birthDateLowerBound = lower;
    birthDateHigherBound = higher;
    criteria[Student::KEYS::BIRTH_DATE] = true;
}

void StudentSearchPattern::setEnrollDateBounds(const QDate &lower, const QDate &higher)
{
    enrollDateLowerBound = lower;
    enrollDateHigherBound = higher;
    criteria[Student::KEYS::ENROLL_DATE] = true;
}

void StudentSearchPattern::setGraduateDateBounds(const QDate &lower, const QDate &higher)
{
    graduateDateLowerBound = lower;
    graduateDateHigherBound = higher;
    criteria[Student::KEYS::GRADUATE_DATE] = true;
}

