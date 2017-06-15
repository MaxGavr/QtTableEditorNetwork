#include "searchwidget.h"

StudentSearchWidget::StudentSearchWidget(QWidget *parent)
    : QWidget(parent)
{
    manageNameFields();
    manageDateFields();
    manageLayouts();
}

StudentSearchPattern StudentSearchWidget::createPattern() const
{
    StudentSearchPattern pattern;

    if (firstNameCheckBox->isChecked())
        pattern.setFirstName(firstNameInput->text());
    if (secondNameCheckBox->isChecked())
        pattern.setSecondName(secondNameInput->text());
    if (middleNameCheckBox->isChecked())
        pattern.setMiddleName(middleNameInput->text());
    if (birthDateCheckBox->isChecked())
        pattern.setBirthDateBounds(birthDateLowerBound->date(), birthDateHigherBound->date());
    if (enrollDateCheckBox->isChecked())
        pattern.setEnrollDateBounds(enrollDateLowerBound->date(), enrollDateHigherBound->date());
    if (graduateDateCheckBox->isChecked())
        pattern.setEnrollDateBounds(graduateDateLowerBound->date(), graduateDateHigherBound->date());

    return pattern;
}

void StudentSearchWidget::manageNameFields()
{
    firstNameCheckBox = new QCheckBox(tr("Имя"), this);
    firstNameInput = new QLineEdit(this);
    firstNameInput->setPlaceholderText(tr("Введите имя..."));

    secondNameCheckBox = new QCheckBox(tr("Фамилия"), this);
    secondNameInput = new QLineEdit(this);
    secondNameInput->setPlaceholderText(tr("Введите фамилию..."));

    middleNameCheckBox = new QCheckBox(tr("Отчество"), this);
    middleNameInput = new QLineEdit(this);
    middleNameInput->setPlaceholderText(tr("Введите отчество..."));
}

void StudentSearchWidget::manageDateFields()
{
    birthDateCheckBox = new QCheckBox(tr("Дата рождения"), this);

    birthDateLowerBound = new QDateEdit();
    birthDateLowerBound->setDisplayFormat(Student::DATE_FORMAT);
    birthDateLowerBoundCalendar = new QCalendarWidget();
    birthDateLowerBoundCalendar->setGridVisible(true);
    birthDateLowerBoundCalendar->setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader);
    birthDateLowerBound->setCalendarPopup(true);
    birthDateLowerBound->setCalendarWidget(birthDateLowerBoundCalendar);

    birthDateHigherBound = new QDateEdit();
    birthDateHigherBound->setDisplayFormat(Student::DATE_FORMAT);
    birthDateHigherBoundCalendar = new QCalendarWidget();
    birthDateHigherBoundCalendar->setGridVisible(true);
    birthDateHigherBoundCalendar->setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader);
    birthDateHigherBound->setCalendarPopup(true);
    birthDateHigherBound->setCalendarWidget(birthDateHigherBoundCalendar);

    enrollDateCheckBox = new QCheckBox(tr("Дата поступления"), this);

    enrollDateLowerBound = new QDateEdit();
    enrollDateLowerBound->setDisplayFormat(Student::DATE_FORMAT);
    enrollDateLowerBoundCalendar = new QCalendarWidget();
    enrollDateLowerBoundCalendar->setGridVisible(true);
    enrollDateLowerBoundCalendar->setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader);
    enrollDateLowerBound->setCalendarPopup(true);
    enrollDateLowerBound->setCalendarWidget(enrollDateLowerBoundCalendar);

    enrollDateHigherBound = new QDateEdit();
    enrollDateHigherBound->setDisplayFormat(Student::DATE_FORMAT);
    enrollDateHigherBoundCalendar = new QCalendarWidget();
    enrollDateHigherBoundCalendar->setGridVisible(true);
    enrollDateHigherBoundCalendar->setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader);
    enrollDateHigherBound->setCalendarPopup(true);
    enrollDateHigherBound->setCalendarWidget(enrollDateHigherBoundCalendar);

    graduateDateCheckBox = new QCheckBox(tr("Дата окончания"), this);

    graduateDateLowerBound = new QDateEdit();
    graduateDateLowerBound->setDisplayFormat(Student::DATE_FORMAT);
    graduateDateLowerBoundCalendar = new QCalendarWidget();
    graduateDateLowerBoundCalendar->setGridVisible(true);
    graduateDateLowerBoundCalendar->setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader);
    graduateDateLowerBound->setCalendarPopup(true);
    graduateDateLowerBound->setCalendarWidget(graduateDateLowerBoundCalendar);

    graduateDateHigherBound = new QDateEdit();
    graduateDateHigherBound->setDisplayFormat(Student::DATE_FORMAT);
    graduateDateHigherBoundCalendar = new QCalendarWidget();
    graduateDateHigherBoundCalendar->setGridVisible(true);
    graduateDateHigherBoundCalendar->setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader);
    graduateDateHigherBound->setCalendarPopup(true);
    graduateDateHigherBound->setCalendarWidget(graduateDateHigherBoundCalendar);
}

void StudentSearchWidget::manageLayouts()
{
    QHBoxLayout *horizontalMain = new QHBoxLayout();
    QVBoxLayout *namesVerticalLayout = new QVBoxLayout();
    QVBoxLayout *datesVerticalLayout = new QVBoxLayout();

    QHBoxLayout *firstNameLayout = new QHBoxLayout();
    firstNameLayout->addWidget(firstNameCheckBox);
    firstNameLayout->addWidget(firstNameInput, 1, Qt::AlignRight);

    QHBoxLayout *secondNameLayout = new QHBoxLayout();
    secondNameLayout->addWidget(secondNameCheckBox);
    secondNameLayout->addWidget(secondNameInput, 1, Qt::AlignRight);

    QHBoxLayout *middleNameLayout = new QHBoxLayout();
    middleNameLayout->addWidget(middleNameCheckBox);
    middleNameLayout->addWidget(middleNameInput, 1, Qt::AlignRight);

    namesVerticalLayout->addLayout(firstNameLayout);
    namesVerticalLayout->addLayout(secondNameLayout);
    namesVerticalLayout->addLayout(middleNameLayout);


    QHBoxLayout *birthDateLayout = new QHBoxLayout();
    birthDateLayout->addWidget(birthDateCheckBox);
    birthDateLayout->addWidget(birthDateLowerBound, 0, Qt::AlignRight);
    birthDateLayout->addWidget(birthDateHigherBound, 0, Qt::AlignRight);

    QHBoxLayout *enrollDateLayout = new QHBoxLayout();
    enrollDateLayout->addWidget(enrollDateCheckBox);
    enrollDateLayout->addWidget(enrollDateLowerBound, 0, Qt::AlignRight);
    enrollDateLayout->addWidget(enrollDateHigherBound, 0, Qt::AlignRight);

    QHBoxLayout *graduateDateLayout = new QHBoxLayout();
    graduateDateLayout->addWidget(graduateDateCheckBox);
    graduateDateLayout->addWidget(graduateDateLowerBound, 0, Qt::AlignRight);
    graduateDateLayout->addWidget(graduateDateHigherBound, 0, Qt::AlignRight);

    datesVerticalLayout->addLayout(birthDateLayout);
    datesVerticalLayout->addLayout(enrollDateLayout);
    datesVerticalLayout->addLayout(graduateDateLayout);

    horizontalMain->addLayout(namesVerticalLayout, 1);
    horizontalMain->addSpacing(10);
    horizontalMain->addLayout(datesVerticalLayout, 1);

    setLayout(horizontalMain);
}
