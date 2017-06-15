#include <QMessageBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QStackedWidget>
#include <QCalendarWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QGroupBox>
#include <QButtonGroup>
#include <QRadioButton>

#include "adddialog.h"

AddStudentDialog::AddStudentDialog(const StudentDatabase& db, DatabaseManager* mng, QWidget* parent)
    : QDialog(parent), database(db)
{
    setManager(mng);

    firstNameInput = new QLineEdit(this);
    firstNameInput->setPlaceholderText(tr("Введите имя..."));
    secondNameInput = new QLineEdit(this);
    secondNameInput->setPlaceholderText(tr("Введите фамилию..."));
    middleNameInput = new QLineEdit(this);
    middleNameInput->setPlaceholderText(tr("Введите отчество..."));

    birthDateInput = new QCalendarWidget(this);
    birthDateInput->setGridVisible(true);
    birthDateInput->setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader);
    enrollDateInput = new QCalendarWidget(this);
    enrollDateInput->setGridVisible(true);
    enrollDateInput->setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader);
    graduateDateInput = new QCalendarWidget(this);
    graduateDateInput->setGridVisible(true);
    graduateDateInput->setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader);

    manageButtons();
    manageDateSwitcher();
    manageLayouts();

    connect(&database, SIGNAL(invalidInsertion()), this, SLOT(notifyInvalidInput()));
    connect(&database, SIGNAL(duplicateInsertion()), this, SLOT(notifyDuplication()));
}

void AddStudentDialog::addStudentToDatabase()
{
    QString first = firstNameInput->text();
    QString second = secondNameInput->text();
    QString middle = middleNameInput->text();

    QDate birth = birthDateInput->selectedDate();
    QDate enroll = enrollDateInput->selectedDate();
    QDate graduate = graduateDateInput->selectedDate();

    if (manager)
    {
        manager->addStudent(first, second, middle, birth, enroll, graduate);
    }
}

void AddStudentDialog::notifyInvalidInput()
{
    QMessageBox::warning(this,
                         tr("Ошибка"),
                         tr("Введены некорректные сведения!"),
                         QMessageBox::Ok);
}

void AddStudentDialog::notifyDuplication()
{
    QMessageBox::warning(this,
                         tr("Ошибка"),
                         tr("Запись о таком студенте уже существует!"),
                         QMessageBox::Ok);
}

void AddStudentDialog::manageButtons()
{
    ok = new QPushButton(tr("Добавить"), this);
    connect(ok, SIGNAL(clicked(bool)), this, SLOT(addStudentToDatabase()));
    ok->setDefault(true);

    cancel = new QPushButton(tr("Отмена"), this);
    connect(cancel, SIGNAL(clicked(bool)), this, SLOT(reject()));
}

void AddStudentDialog::manageLayouts()
{
    QVBoxLayout* verticalMain = new QVBoxLayout();
    QVBoxLayout* verticalTop = new QVBoxLayout();
    QHBoxLayout* horizontalBottom = new QHBoxLayout();
    QHBoxLayout* buttonsLayout = new QHBoxLayout();

    verticalTop->addWidget(firstNameInput);
    verticalTop->addWidget(secondNameInput);
    verticalTop->addWidget(middleNameInput);
    verticalTop->addWidget(dateSwitcher);

    horizontalBottom->addWidget(dates);

    buttonsLayout->addWidget(ok);
    buttonsLayout->addWidget(cancel);

    verticalMain->addLayout(verticalTop);
    verticalMain->addLayout(horizontalBottom);
    verticalMain->addLayout(buttonsLayout);

    setLayout(verticalMain);
}

void AddStudentDialog::manageDateSwitcher()
{
    dateSwitcher = new QGroupBox(tr("Выберите дату:"), this);
    QRadioButton* birthDateButton = new QRadioButton(tr("дата рождения"));
    QRadioButton* enrollDateButton = new QRadioButton(tr("дата поступления"));
    QRadioButton* graduateDateButton = new QRadioButton(tr("дата окончания"));

    QHBoxLayout* groupBoxLayout = new QHBoxLayout();
    groupBoxLayout->addWidget(birthDateButton);
    groupBoxLayout->addWidget(enrollDateButton);
    groupBoxLayout->addWidget(graduateDateButton);
    dateSwitcher->setLayout(groupBoxLayout);

    QButtonGroup* radioButtons = new QButtonGroup();
    radioButtons->addButton(birthDateButton, 0);
    radioButtons->addButton(enrollDateButton, 1);
    radioButtons->addButton(graduateDateButton, 2);
    birthDateButton->setChecked(true);

    dates = new QStackedWidget(this);
    dates->addWidget(birthDateInput);
    dates->addWidget(enrollDateInput);
    dates->addWidget(graduateDateInput);
    dates->setCurrentIndex(0);

    connect(radioButtons, SIGNAL(buttonToggled(int, bool)), dates, SLOT(setCurrentIndex(int)));
}

void AddStudentDialog::setManager(DatabaseManager* value)
{
    manager = value;
}
