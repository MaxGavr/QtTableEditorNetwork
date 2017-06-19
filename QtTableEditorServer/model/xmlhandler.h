#pragma once

#include <QString>
#include <QDate>
#include <QtXml/QDomDocument>

class StudentDatabase;
class Student;

class XmlHandler
{
public:
    static const QString FILE_FORMAT;

    XmlHandler(StudentDatabase *db);

    bool readFromFile(QString fileName);
    bool writeToFile(QString fileName);

    QStringList getAvailableFiles() const;

private:
    QDomElement writeStudent(QDomDocument &doc, const Student &student);
    QDate parseDate(const QString& stringDate);

    StudentDatabase *database;

    static const QString XML_TAG_STUDENTS;
    static const QString XML_TAG_STUDENT;
    static const QString XML_TAG_NAME;
    static const QString XML_TAG_SURNAME;
    static const QString XML_TAG_MIDDLE_NAME;
    static const QString XML_TAG_DATES;
    static const QString XML_TAG_BIRTH_DATE;
    static const QString XML_TAG_ENROLL_DATE;
    static const QString XML_TAG_GRADUATE_DATE;
};
