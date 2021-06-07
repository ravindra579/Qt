#include "finddialog.h"
#include "ui_finddialog.h"

FindDialog::FindDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FindDialog)
{
    ui->setupUi(this);

    init();
    save();
}

FindDialog::~FindDialog()
{
    delete ui;
}

void FindDialog::on_buttonBox_accepted()
{
    save();
    accept();
}

void FindDialog::on_buttonBox_rejected()
{
    reject();
}

void FindDialog::goBack()
{
    save();
    m_backwards = true;
    accept();
}

QString FindDialog::text() const
{
    return m_text;
}

bool FindDialog::backwards() const
{
    return m_backwards;
}

bool FindDialog::wholeWords() const
{
    return m_wholeWords;
}

bool FindDialog::caseSensitive() const
{
    return m_caseSensitive;
}

void FindDialog::init()
{
    QPushButton *btnBack = new QPushButton("Back",this);
    connect(btnBack,&QPushButton::clicked,this,&FindDialog::goBack);
    ui->buttonBox->addButton(btnBack,QDialogButtonBox::ActionRole);
}

void FindDialog::save()
{
    m_text = ui->lineEdit->text();
    m_caseSensitive = ui->chkCaseSensitive->isChecked();
    m_wholeWords = ui->chkMatchWholeWord->isChecked();
    m_backwards = false;
}




