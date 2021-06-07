#include "messagewindow.h"

MessageWindow::MessageWindow(QWidget *parent) : QMainWindow(parent)
{
    m_width = 400;
    m_infoHeight = 100;
    this->setMaximumWidth(m_width);
    this->setMinimumWidth(m_width);

    m_mainText = new QLabel();
    m_mainText->setAlignment(Qt::AlignmentFlag::AlignCenter);

    m_informativeTextIntro = new QLabel();
    m_informativeTextIntro->setText("\nMore:");
    m_informativeTextIntro->setVisible(false);

    m_informativeText = new QTextEdit();
    m_informativeText->setReadOnly(true);
    m_informativeText->setMinimumHeight(m_infoHeight);
    m_informativeText->setMaximumHeight(m_infoHeight);
    m_informativeText->setVisible(false);

    m_closeButton = new QPushButton();
    m_closeButton->setText("Close");
    connect(m_closeButton, &QPushButton::clicked, this, &QMainWindow::close);

    m_mainLayout = new QVBoxLayout();
    m_mainLayout->addWidget(m_mainText);
    m_mainLayout->addWidget(m_informativeTextIntro);
    m_mainLayout->addWidget(m_informativeText);
    m_mainLayout->addWidget(m_closeButton);

    m_centralWidget = new QWidget();
    m_centralWidget->setLayout(m_mainLayout);

    this->setCentralWidget(m_centralWidget);
}


void MessageWindow::setContent(string content)
{
    m_mainText->setText(QString::fromStdString(content));
}


void MessageWindow::setInfo(string info)
{
    if (!info.empty())
    {
        m_informativeText->setText(QString::fromStdString(info));
        m_informativeText->setVisible(true);
        m_informativeTextIntro->setVisible(true);
    }
}


void MessageWindow::setTitle(string title)
{
    this->setWindowTitle(QString::fromStdString(title));
}


void MessageWindow::printError(string title, string content, string info)
{
    this->setContent("\nError: " + content);
    m_mainText->setStyleSheet("QLabel { color : red; }");
    this->setInfo(info);
    this->setTitle(title);
    this->show();
}


void MessageWindow::printInfo(string title, string content, string info)
{
    this->setContent("\n" + content);
    this->setInfo(info);
    this->setTitle(title);
    this->show();
}
