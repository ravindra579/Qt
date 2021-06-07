#ifndef MESSAGEWINDOW_H
#define MESSAGEWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QTextEdit>
#include <QPushButton>
#include <QWidget>
#include <QVBoxLayout>
#include <string>

using namespace std;

class MessageWindow : public QMainWindow
{
    Q_OBJECT

private:
    int m_width;
    int m_infoHeight;
    QLabel *m_mainText;
    QLabel *m_informativeTextIntro;
    QTextEdit *m_informativeText;
    QWidget *m_centralWidget;
    QPushButton *m_closeButton;
    QVBoxLayout *m_mainLayout;

public:
    explicit MessageWindow(QWidget *parent = nullptr);
    void setContent(string content);
    void setInfo(string info);
    void setTitle(string title);
    void printError(string title, string content, string info="");
    void printInfo(string title, string content, string info="");

signals:

public slots:
};

#endif // MESSAGEWINDOW_H
