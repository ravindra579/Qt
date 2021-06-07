#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <vector>
#include <string>
#include<QString>
#include <iostream>
#include <unordered_map>
#include <sstream>
using namespace std;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
   setCentralWidget(ui->textEdit);

   m_path = "";
   m_changed = false;
   newFile();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionNew_triggered()
{
    checksave();
    ui->textEdit->clear();
    newFile();
}

void MainWindow::on_actionOpen_triggered()
{
    checksave();
    openFile();
}

void MainWindow::on_actionSave_triggered()
{
    saveFile(m_path);
}

void MainWindow::on_actionSave_As_triggered()
{
    saveFileAs();
}

void MainWindow::on_actionExit_triggered()
{
    close();
}

void MainWindow::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}

void MainWindow::on_actionCut_triggered()
{
    ui->textEdit->cut();
}

void MainWindow::on_actionPaste_triggered()
{
    ui->textEdit->paste();
}

void MainWindow::on_actionUndo_triggered()
{
    ui->textEdit->undo();
}

void MainWindow::on_actionRedo_triggered()
{
    ui->textEdit->redo();
}


void MainWindow::on_actionFind_triggered()
{
    FindDialog *dlg = new FindDialog(this);
    if(!dlg->exec()) return;

    QTextDocument::FindFlags flags;
    if(dlg->caseSensitive()) flags = flags | QTextDocument::FindFlag::FindCaseSensitively;
    if(dlg->wholeWords()) flags = flags | QTextDocument::FindFlag::FindWholeWords;
    if(dlg->backwards()) flags = flags | QTextDocument::FindFlag::FindBackward;

    bool value = ui->textEdit->find(dlg->text(),flags);
    if(!value) QMessageBox::information(this,"Not Found","Was not able to find: " + dlg->text());
}

void MainWindow::on_actionReplace_triggered()
{
    ReplaceDialog *dlg = new ReplaceDialog(this);
    if(!dlg->exec()) return;

    if(dlg->all())
    {
        //Replace all
        QString text = ui->textEdit->toHtml();
        text = text.replace(dlg->text(), dlg->replaceText());
        ui->textEdit->setHtml(text);
        m_changed = true;
    }
    else
    {
        //Replace one
        bool value = ui->textEdit->find(dlg->text());
        QTextCursor cursor = ui->textEdit->textCursor();
        cursor.insertHtml(dlg->replaceText());
        if(!value) QMessageBox::information(this,"not Found","Was not able to find " + dlg->text());
        m_changed = true;
    }
}

void MainWindow::on_actionSelect_All_triggered()
{
    ui->textEdit->selectAll();
}

void MainWindow::on_actionZoom_in_triggered()
{
    ui->textEdit->zoomIn(1);
}

void MainWindow::on_actionZoom_out_triggered()
{
    ui->textEdit->zoomOut(1);
}

void MainWindow::on_actionBold_triggered()
{
    QFont font = ui->textEdit->currentFont();
    font.bold() ? font.setBold(false) : font.setBold(true);
    ui->textEdit->setCurrentFont(font);
    m_changed = true;
}

void MainWindow::on_actionItalic_triggered()
{
    QFont font = ui->textEdit->currentFont();
    font.italic() ? font.setItalic(false) : font.setItalic(true);
    ui->textEdit->setCurrentFont(font);
    m_changed = true;
}

void MainWindow::on_actionUnderline_triggered()
{
    QFont font = ui->textEdit->currentFont();
    font.underline() ? font.setUnderline(false) : font.setUnderline(true);
    ui->textEdit->setCurrentFont(font);
    m_changed = true;
}

void MainWindow::on_actionStrike_triggered()
{
    QFont font = ui->textEdit->currentFont();
    font.strikeOut() ? font.setStrikeOut(false) : font.setStrikeOut(true);
    ui->textEdit->setCurrentFont(font);
    m_changed = true;
}

void MainWindow::on_actionColor_triggered()
{
    QColor current = ui->textEdit->currentCharFormat().foreground().color();
    QColor color = QColorDialog::getColor(current,this,"Select a color");

    ui->textEdit->setTextColor(color);
    m_changed = true;
}

void MainWindow::on_actionFont_triggered()
{
    bool ok;
    QFont font = QFontDialog::getFont(&ok,ui->textEdit->currentFont(),this,"Choose a font");
    if(ok) ui->textEdit->setCurrentFont(font);
}

void MainWindow::on_actionHelp_triggered()
{

}

void MainWindow::on_actionAbout_triggered()
{

}

void MainWindow::on_textEdit_textChanged()
{
    m_changed = true;
}
int MainWindow::bintodec(QString a)
{
    long num = a.toLong();
        int dec_value = 0;
        int base = 1;
        long temp = num;
        while (temp) {
            int last_digit = temp % 10;
            temp = temp / 10;
            dec_value += last_digit * base;
            base = base * 2;
        }
        return dec_value;
}
void MainWindow::newFile()
{
    ui->textEdit->clear();
    ui->statusbar->showMessage("New File");
    m_path = "";
    m_changed = false;
}

void MainWindow::openFile()
{
    ui->textEdit->clear();
    QString path = QFileDialog::getOpenFileName(this,"Open File");
    if(path.isEmpty()) return;

    QFile file(path);
    if(!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::critical(this,"Error", file.errorString());
        return;
    }

    QTextStream stream(&file);
    while(!stream.atEnd()){
        QString line=stream.readLine();
        ui->textEdit->append("10 bit numbers");
        ui->textEdit->append("Threshold - 500");
        int c=bintodec(line);
        ui->textEdit->append(line);
        ui->textEdit->append(QString::number(c));
        if(c>500){
            ui->textEdit->append("Activity found");
        }
        ui->textEdit->append("      ");
    }
/*

    vector<string> a;
    unordered_map<string, int> b;
    unordered_map<string, int> c;
   int n=0;
    vector<double> e;
    int presum=0;
    int sum=0;
    double avg;
    QTextStream stream(&file);
    while(!stream.atEnd()){
        QString line=stream.readLine();
        if(b[line.toStdString()]!=-2){
            presum=sum;
            a.push_back(line.toStdString());

            istringstream ss(line.toStdString());
                string word;
       unordered_map<string, int> temp;
                while (ss >> word)
                {

                    c[word]++;
                    temp[word]++;
                    sum++;
                }


             b[line.toStdString()]=-2;
             if(temp.size()!=0){
             double t=(sum-presum)/temp.size();
             e.push_back(t);
             }
             else{
                 e.push_back(0);
             }
        }

    }
    avg=sum/c.size();
    qDebug() << QString::number(avg);
    qDebug() << QString::number(sum);
    int summ=0;
     if(a.size()<1000){
     for(int i=0;i<a.size();i++){
         unordered_map<string, int> d;
         istringstream ss(a[i]);
             string word;
             summ=0;
             while (ss >> word)
             {
                 d[word]++;
                 summ++;

             }
             qDebug() <<QString::number(summ);
             qDebug() <<"B";
             if(sum!=0 && d.size()!=0){
             if(summ/d.size()<avg){
                 ui->textEdit->append(QString::fromStdString(a[i]));
             }
             }
     }
     }
     else{
         int min=INT_MAX;
         int z=0;
         for(int j=0;j<1000;j++){
             min=INT_MAX;
             for(int i=0;i<a.size();i++){
                if(e[i]<min && e[i]!=0) {
                    min=e[i];
                    z=i;
             }
             }

             e[z]=INT_MAX;
             ui->textEdit->append(QString::fromStdString(a[z]));
         }
    }

*/
    file.close();
   qDebug() <<"A";
    m_path = path;
    ui->statusbar->showMessage(m_path);
    m_changed = false;
}

void MainWindow::saveFile(QString path)
{
    if(path.isEmpty())
    {
        saveFileAs();
        return;
    }

    QFile file(path);
    if(!file.open(QIODevice::WriteOnly))
    {
        QMessageBox::critical(this,"Error", file.errorString());
        ui->statusbar->showMessage("Error could not save file!");
        saveFileAs();
        return;
    }

    QTextStream stream(&file);
    stream << ui->textEdit->toPlainText();
    file.close();

    m_path = path;
    ui->statusbar->showMessage(m_path);
    m_changed = false;
}

void MainWindow::saveFileAs()
{
    QString path = QFileDialog::getSaveFileName(this,"Save File");
    if(path.isEmpty()) return;
    saveFile(path);
}

void MainWindow::checksave()
{
    if(!m_changed) return;

    QMessageBox::StandardButton value = QMessageBox::question(this,"Save File?","You have un-saved changes would you like to save them?");

    if(value != QMessageBox::StandardButton::Yes) return;

    if(m_path.isEmpty())
    {
        saveFileAs();
    }
    else
    {
        saveFile(m_path);
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    event->accept();
}


void MainWindow::on_actionAnalyse_triggered()
{

}

