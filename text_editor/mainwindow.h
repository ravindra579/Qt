#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCloseEvent>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QFileDialog>
#include <QColorDialog>
#include <QFontDialog>
#include "finddialog.h"
#include "replacedialog.h"
#include <string>
#include <vector>
#include <iostream>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void on_actionNew_triggered();
    void on_actionOpen_triggered();
    void on_actionSave_triggered();
    void on_actionSave_As_triggered();
    void on_actionExit_triggered();
    void on_actionCopy_triggered();
    void on_actionCut_triggered();
    void on_actionPaste_triggered();
    void on_actionFind_triggered();
    void on_actionReplace_triggered();
    void on_actionSelect_All_triggered();
    void on_actionZoom_in_triggered();
    void on_actionZoom_out_triggered();
    void on_actionBold_triggered();
    void on_actionItalic_triggered();
    void on_actionUnderline_triggered();
    void on_actionStrike_triggered();
    void on_actionColor_triggered();
    void on_actionFont_triggered();
    void on_actionHelp_triggered();
    void on_actionAbout_triggered();

    void on_textEdit_textChanged();

    void on_actionUndo_triggered();

    void on_actionRedo_triggered();

    void on_actionAnalyse_triggered();

private:
    Ui::MainWindow *ui;

    bool m_changed;
    QString m_path;

    void newFile();
    void openFile();
    void saveFile(QString path);
    void saveFileAs();
    void checksave();
    int bintodec(QString a);
    // QWidget interface
protected:
    void closeEvent(QCloseEvent *event) override;
};
#endif // MAINWINDOW_H
