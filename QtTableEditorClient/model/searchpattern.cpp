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

QString StudentSearchPattern::toString(const StudentSearchPattern& pattern)
{
    QString result;
    QChar separator = '#';
    for (int i = 0; i < StudentSearchPattern::NUMBER_OF_CRITERIA; ++i)
    {
        result += QString::number(pattern.criteria[i]) + separator;
    }
    result += pattern.firstName + separator + pattern.secondName + separator + pattern.middleName;
    QList<QDate> dates = {pattern.birthDateLowerBound, pattern.birthDateHigherBound,
                          pattern.enrollDateLowerBound, pattern.enrollDateHigherBound,
                          pattern.graduateDateLowerBound, pattern.graduateDateHigherBound};
    foreach (QDate date, dates)
    {
        result += separator + date.toString(Student::DATE_FORMAT);
    }

    return result;
}

StudentSearchPattern StudentSearchPattern::fromString(const QString &str)
{
    StudentSearchPattern pattern;
    QStringList list = str.split(QChar('#'));
    QStringList::const_iterator it = list.constBegin();
    for (int i = 0; i < StudentSearchPattern::NUMBER_OF_CRITERIA; ++i)
    {
        pattern.criteria[i] = list[i].toInt();
        ++it;
    }
    pattern.firstName = *it++;
    pattern.secondName = *it++;
    pattern.middleName = *it++;

    auto lambda = [&it](){ return QDate::fromString(*it++, Student::DATE_FORMAT); };

    pattern.birthDateLowerBound = lambda();
    pattern.birthDateHigherBound = lambda();
    pattern.enrollDateLowerBound = lambda();
    pattern.enrollDateHigherBound = lambda();
    pattern.graduateDateLowerBound = lambda();
    pattern.graduateDateHigherBound = lambda();

    return pattern;
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

