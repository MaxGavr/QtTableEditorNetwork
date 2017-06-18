#include "xmlhandler.h"
#include "database.h"
#include <QIODevice>
#include <QTextStream>

const QString XmlHandler::XML_TAG_STUDENTS = "students";
const QString XmlHandler::XML_TAG_STUDENT = "student";
const QString XmlHandler::XML_TAG_NAME = "name";
const QString XmlHandler::XML_TAG_SURNAME = "surname";
const QString XmlHandler::XML_TAG_MIDDLE_NAME = "middleName";
const QString XmlHandler::XML_TAG_DATES = "dates";
const QString XmlHandler::XML_TAG_BIRTH_DATE = "birth";
const QString XmlHandler::XML_TAG_ENROLL_DATE = "enrollment";
const QString XmlHandler::XML_TAG_GRADUATE_DATE = "graduation";

const QString XmlHandler::FILE_FORMAT = ".xml";


XmlHandler::XmlHandler(StudentDatabase *db)
{
    database = db;
}


bool XmlHandler::readFromFile(QString fileName)
{
    if (!fileName.endsWith(XmlHandler::FILE_FORMAT))
    {
        fileName.append(XmlHandler::FILE_FORMAT);
    }

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;

    database->clear();

    QXmlStreamReader stream(&file);

    Student student;
    while (!stream.atEnd() && !stream.hasError())
    {
        QXmlStreamReader::TokenType token = stream.readNext();
        if (token == QXmlStreamReader::StartElement)
        {

            if (stream.name() == XML_TAG_STUDENT)
                continue;
            else if (stream.name() == XML_TAG_NAME)
                student.setFirstName(stream.readElementText());
            else if (stream.name() == XML_TAG_SURNAME)
                student.setSecondName(stream.readElementText());
            else if (stream.name() == XML_TAG_MIDDLE_NAME)
                student.setMiddleName(stream.readElementText());
            else if (stream.name() == XML_TAG_BIRTH_DATE)
                student.setBirthDate(parseDate(stream.readElementText()));
            else if (stream.name() == XML_TAG_ENROLL_DATE)
                student.setEnrollmentDate(parseDate(stream.readElementText()));
            else if (stream.name() == XML_TAG_GRADUATE_DATE)
                student.setGraduationDate(parseDate(stream.readElementText()));
        }
        if (token == QXmlStreamReader::EndElement)
            if (stream.name() == XML_TAG_STUDENT)
                database->addStudent(student, false);
    }
    file.close();
    if (!database->isEmpty())
        emit database->studentAdded();
    return true;
}

bool XmlHandler::writeToFile(QString fileName)
{
    QDomDocument doc("students");
    QDomElement rootElement = doc.createElement(XML_TAG_STUDENTS);
    doc.appendChild(rootElement);

    foreach (Student::const_ref student, database->students)
    {
        rootElement.appendChild(writeStudent(doc, student));
    }

    if (!fileName.endsWith(XmlHandler::FILE_FORMAT))
    {
        fileName.append(XmlHandler::FILE_FORMAT);
    }
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly))
        return false;
    else
    {
        QTextStream(&file) << doc.toString();
        return true;
    }
}

QDomElement XmlHandler::writeStudent(QDomDocument &doc, const Student &student)
{
    QDomElement element = doc.createElement(XML_TAG_STUDENT);

    QDomElement name = doc.createElement(XML_TAG_NAME);
    name.appendChild(doc.createTextNode(student.getFirstName()));
    element.appendChild(name);

    QDomElement surname = doc.createElement(XML_TAG_SURNAME);
    surname.appendChild(doc.createTextNode(student.getSecondName()));
    element.appendChild(surname);

    QDomElement middleName = doc.createElement(XML_TAG_MIDDLE_NAME);
    middleName.appendChild(doc.createTextNode(student.getMiddleName()));
    element.appendChild(middleName);

    QDomElement dates = doc.createElement(XML_TAG_DATES);

    QDomElement birth = doc.createElement(XML_TAG_BIRTH_DATE);
    birth.appendChild(doc.createTextNode(student.getBirthDateString()));
    dates.appendChild(birth);

    QDomElement enroll = doc.createElement(XML_TAG_ENROLL_DATE);
    enroll.appendChild(doc.createTextNode(student.getEnrollmentDateString()));
    dates.appendChild(enroll);

    QDomElement graduate = doc.createElement(XML_TAG_GRADUATE_DATE);
    graduate.appendChild(doc.createTextNode(student.getGraduationDateString()));
    dates.appendChild(graduate);

    element.appendChild(dates);
    return element;
}

QDate XmlHandler::parseDate(const QString &stringDate)
{
    QStringList list = stringDate.split(".");
    return QDate(list[2].toInt(), list[1].toInt(), list[0].toInt());
}
