#pragma once

#include <QWidget>
#include <QDateEdit>
#include <QCalendarWidget>
#include <QLineEdit>
#include <QCheckBox>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include "../model/searchpattern.h"

class StudentSearchWidget : public QWidget
{
    Q_OBJECT
public:
    StudentSearchWidget(QWidget *parent = 0);

    StudentSearchPattern createPattern() const;

private:
    void manageNameFields();
    void manageDateFields();
    void manageLayouts();

    QCheckBox *firstNameCheckBox;
    QLineEdit *firstNameInput;

    QCheckBox *secondNameCheckBox;
    QLineEdit *secondNameInput;

    QCheckBox *middleNameCheckBox;
    QLineEdit *middleNameInput;

    QCheckBox *birthDateCheckBox;
    QDateEdit *birthDateLowerBound;
    QDateEdit *birthDateHigherBound;
    QCalendarWidget *birthDateLowerBoundCalendar;
    QCalendarWidget *birthDateHigherBoundCalendar;

    QCheckBox *enrollDateCheckBox;
    QDateEdit *enrollDateLowerBound;
    QDateEdit *enrollDateHigherBound;
    QCalendarWidget *enrollDateLowerBoundCalendar;
    QCalendarWidget *enrollDateHigherBoundCalendar;

    QCheckBox *graduateDateCheckBox;
    QDateEdit *graduateDateLowerBound;
    QDateEdit *graduateDateHigherBound;
    QCalendarWidget *graduateDateLowerBoundCalendar;
    QCalendarWidget *graduateDateHigherBoundCalendar;
};

