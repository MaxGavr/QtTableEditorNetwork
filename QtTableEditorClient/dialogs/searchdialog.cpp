#include "searchdialog.h"

SearchStudentDialog::SearchStudentDialog(DatabaseManager *mng, QWidget *parent)
    :QDialog(parent)
{
    setManager(mng);
    table = new MultipageTable(mng, this);
    table->enforceEmpty(true);

    searchWidget = new StudentSearchWidget(this);

    manageButtons();
    manageLayouts();
}

void SearchStudentDialog::manageButtons()
{
    find = new QPushButton(tr("Найти"), this);
    connect(find, SIGNAL(clicked(bool)), this, SLOT(findStudents()));
    find->setDefault(true);

    cancel = new QPushButton(tr("Отмена"), this);
    connect(cancel, SIGNAL(clicked(bool)), this, SLOT(reject()));
}

void SearchStudentDialog::manageLayouts()
{
    QVBoxLayout *verticalMain = new QVBoxLayout();
    QVBoxLayout *verticalTop = new QVBoxLayout();
    QHBoxLayout *buttonsLayout = new QHBoxLayout();

    verticalTop->addWidget(searchWidget);
    verticalTop->addWidget(table);

    buttonsLayout->addWidget(find);
    buttonsLayout->addWidget(cancel);

    verticalMain->addLayout(verticalTop);
    verticalMain->addLayout(buttonsLayout);

    setLayout(verticalMain);
}

DatabaseManager *SearchStudentDialog::getManager()
{
    return manager;
}

void SearchStudentDialog::setManager(DatabaseManager *value)
{
    manager = value;
}

void SearchStudentDialog::reject()
{
    getManager()->resetSearchPattern();
    QDialog::reject();
}

void SearchStudentDialog::findStudents()
{
    table->enforceEmpty(false);
    getManager()->setSearchPattern(searchWidget->createPattern());
    if (!table->isEmpty())
        table->goToFirstPage();
    table->requestPage();
}
