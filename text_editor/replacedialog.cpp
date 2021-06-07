#include "replacedialog.h"
#include "ui_replacedialog.h"

ReplaceDialog::ReplaceDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ReplaceDialog)
{
    ui->setupUi(this);

    init();
    save();
}

ReplaceDialog::~ReplaceDialog()
{
    delete ui;
}

void ReplaceDialog::on_buttonBox_rejected()
{
    reject();
}

void ReplaceDialog::replace()
{
    save();
    accept();
}

void ReplaceDialog::replaceAll()
{
    save();
    m_all = true;
    accept();
}

void ReplaceDialog::init()
{
    QPushButton *btnReplace = new QPushButton("Replace", this);
    QPushButton *btnAll = new QPushButton("Replace All", this);

    ui->buttonBox->addButton(btnReplace,QDialogButtonBox::ButtonRole::ActionRole);
    ui->buttonBox->addButton(btnAll,QDialogButtonBox::ButtonRole::ActionRole);

    connect(btnAll,&QPushButton::clicked,this,&ReplaceDialog::replaceAll);
    connect(btnReplace,&QPushButton::clicked,this,&ReplaceDialog::replace);
}

void ReplaceDialog::save()
{
    m_text = ui->txtFind->text();
    m_replaceText = ui->txtReplace->text();
    m_all  = false;
}

QString ReplaceDialog::replaceText() const
{
    return m_replaceText;
}

QString ReplaceDialog::text() const
{
    return m_text;
}

bool ReplaceDialog::all() const
{
    return m_all;
}
