#include <QMessageBox>
#include "deletedialog.h"

DeleteStudentDialog::DeleteStudentDialog(DatabaseManager *mng, QWidget *parent)
    : QDialog(parent)
{
    setManager(mng);
    searchWidget = new StudentSearchWidget(this);

    manageButtons();
    manageLayouts();

    //connect(&db, SIGNAL(studentsDeleted(int)), this, SLOT(notifyDeletion(int)));
}

DatabaseManager *DeleteStudentDialog::getManager()
{
    return manager;
}

void DeleteStudentDialog::setManager(DatabaseManager *value)
{
    manager = value;
}

void DeleteStudentDialog::deleteStudents()
{
    getManager()->deleteStudents(searchWidget->createPattern());
}

void DeleteStudentDialog::notifyDeletion(int amount)
{
    QString msg;
    if (amount > 0)
        msg = tr("Удалено ") + QString::number(amount) + tr(" записей");
    else
        msg = tr("Записей, удовлетворяющих шаблону, не найдено!");
    QMessageBox::information(this, tr("Результат удаления"), msg, QMessageBox::Ok);
}

void DeleteStudentDialog::manageButtons()
{
    deleteButton = new QPushButton(tr("Удалить"), this);
    connect(deleteButton, SIGNAL(clicked(bool)), this, SLOT(deleteStudents()));
    deleteButton->setDefault(true);

    cancelButton = new QPushButton(tr("Отмена"), this);
    connect(cancelButton, SIGNAL(clicked(bool)), this, SLOT(reject()));
}

void DeleteStudentDialog::manageLayouts()
{
    QVBoxLayout *verticalMain = new QVBoxLayout();
    QHBoxLayout *buttonsLayout = new QHBoxLayout();

    buttonsLayout->addWidget(deleteButton);
    buttonsLayout->addWidget(cancelButton);

    verticalMain->addWidget(searchWidget);
    verticalMain->addLayout(buttonsLayout);

    setLayout(verticalMain);
}
