#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <mainwidget.h>
#include <QFileDialog>
#include<QMessageBox>
#include<QFile>
#include<QTime>
#include<QDateTime>
#include <QTableWidget>
#include<QKeyEvent>
#include<QChart>
#include<QChartView>
#include<QBarSet>
#include<QBarSeries>
#include<QBarCategoryAxis>
#include<QtDebug>
#include<QValueAxis>
#include<QLineSeries>
#include<QPieSeries>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include "customslice.h"
#include <fstream>
#include "pentool.h"
#include "brushtool.h"
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QFontDialog>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QCheckBox>
#include <iostream>
#include <string>
#include<chartview.h>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
  \
 timer=new QTimer(this);
 connect(timer,SIGNAL(timeout()),SLOT(myfunction()));
 timer->start(100);
ui->tableWidget->setColumnCount(10);
ui->tableWidget->setRowCount(6100);
connect(ui->tableWidget,SIGNAL(cellEntered()),this,SLOT(insertRow()));

QBarSet *set0 = new QBarSet("Bob");


*set0 << 30 << 40 << 10 << 20 << 10 << 60;
set0->append(70);


QBarSeries *series = new QBarSeries();
series->append(set0);


QChart *chart = new QChart();
chart->addSeries(series);
chart->setTitle("BarChart Example In Qt5 C++ ");
chart->setAnimationOptions(QChart::SeriesAnimations);


QStringList categories;
categories << "Jan" << "Feb" << "Mar" << "Apr" << "May" << "Jun";
QBarCategoryAxis *axis = new QBarCategoryAxis();
axis->append(categories);
chart->createDefaultAxes();



ChartView *chartView = new ChartView(chart);
 chartView->resize(800,500);
chartView->setParent(ui->gridFrame);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionOpen_triggered()
{

    QString file_name=QFileDialog::getOpenFileName(this,"open a file","C://");
    file_path=file_name.toStdString();
    std::string filename=file_name.toStdString();
    ui->plainTextEdit_3->setPlainText("File Name :-"+file_name);
    if(file_path.substr(file_path.find_last_of(".")+1)=="csv")
    Dataset *dataset= readCSV(filename);
}
Dataset* MainWindow::readCSV(std::string fileName)
{
    on_pushButton_4_clicked();
    // create dataset
    Dataset *dataset = new Dataset();

    // message window
    MessageWindow *messageWindow = new MessageWindow();

    // open the file
    std::ifstream input(fileName, std::ifstream::in);
    //input.clear();

    if (!input)
    {
        // error
        messageWindow->printError("CSV Reader",
                                  "Cannot open file",
                                  fileName);
        return nullptr;
    }


    // temporary container for strings
    std::string tmpStr = "";

    // read the file structure: comments, header and number of lines
    std::string headerStr = "";
    unsigned int nbLines = 0;
    while (getline(input, tmpStr))
    {
        // skip comments and empty lines
        if ( (tmpStr[0] != '#') && (!tmpStr.empty()) )
        {
            if (headerStr == "")
            {
                // header: supposed to be the first line after comments
                headerStr = tmpStr;
            }
            else
            {
                // new line of data
                nbLines += 1;
            }

        }
    }


    // the end of the file has been reached -> remove eof flag
    input.clear();

    // process header to get fields names
    std::vector<std::string> initHeaderFields = split(headerStr, ',');
    std::vector<std::string> headerFields = renameDuplicates(initHeaderFields);
    std::cout << "'" << headerStr << "'" << std::endl;
    for (unsigned int i=0; i<headerFields.size(); ++i)
    {
        std::cout << headerFields[i] << "   " << i << std::endl;
        headerFields[i] = strip(removeQuotes(headerFields[i]));
    }

    // create fields and dataset
    unsigned int nbFields = 0;
    dataset->setSize(nbLines);

    for (std::string str : headerFields)
    {
        Field newField;
        newField.setSize(nbLines);
        newField.setName(str);

        dataset->addField(newField);
        nbFields ++;
    }
    vector<string> *z[2];

    // go back to header and skip header
    input.clear();
    input.seekg(input.beg);
    input >> tmpStr;

    // read the data part line by line
    std::vector<std::string> splitStr;
    std::string fieldName;
    unsigned int lineNumber = 0;
    double value;
    Field tmpField;
int j=0;
    while (getline(input, tmpStr))
    {
        // skip comments and empty lines
        if ( (tmpStr[0] != '#') && (!tmpStr.empty()) )
        {
            // split the line and store pieces in the corresponding fields
            splitStr = split(tmpStr, ',');

            if (splitStr.size() != nbFields)
            {
                messageWindow->printError("CSV Reader",
                                          "Wrong number of columns");
                return nullptr;
            }
            if(splitStr.size()>m){
                ui->tableWidget->setColumnCount(splitStr.size());
                m=splitStr.size();
            }
            for (unsigned int i=0; i<splitStr.size(); ++i)
            {

                try
                {
                    value = std::stof(splitStr[i]);
                   // z[i]->push_back(to_string(value));
                    QTableWidgetItem *item = ui->tableWidget->item(j, i);
                    item = new QTableWidgetItem();
                    item->setText(QString::fromStdString(to_string(value)));
                    ui->tableWidget->setItem(j,i,item);


                }
                catch (invalid_argument)
                {
                    messageWindow->printError("CSV Reader","Cannot convert line data",splitStr[i]);
                    return nullptr;
                }
                dataset->setValue(headerFields[i], value, lineNumber);

            }
              cout<<j<<" "<<endl;;
            // increment line number
            lineNumber ++;
             j++;
        }

    }


    // set title
    std::string title;
    title = getBaseName(fileName);
    dataset->setTitle(title);
    cout<<j;

    // output
    return dataset;
}
void MainWindow::on_pushButton_clicked()
{

    QFile file(QString::fromStdString(file_path));
    if(!file.open(QFile::ReadOnly | QFile::Text)){
       QMessageBox::warning(this,"title","file not opened");

    }
    QTextStream in(&file);
    QString text=in.readAll();
    ui->plainTextEdit->setPlainText(text);
    file.close();
}
void MainWindow::myfunction(){
    QTime time=QTime::currentTime();
    QString time_text=time.toString("hh:mm:ss");
    ui->label_2->setText(time_text);
}

void MainWindow::on_actionSave_triggered()
{
    try{
    if(file_path.substr(file_path.find_last_of(".")+1)!="csv"){
    QFile file(QString::fromStdString(file_path));
   file.open(QFile::WriteOnly);
    QTextStream out(&file);
    QString text=ui->plainTextEdit->toPlainText();
   out<<text;
   file.flush();
    file.close();
    }
    }

    catch (exception e) {
        qDebug() <<"error";
    }
}


void MainWindow::on_tabWidget_tabCloseRequested(int index)
{
    ui->tabWidget->removeTab(index);
}

void MainWindow::addRowIfLast()
{
    if(ui->tableWidget->currentRow() == ui->tableWidget->rowCount()-1) {
        ui->tableWidget->insertRow(ui->tableWidget->rowCount()+1);
        ui->tableWidget->setCurrentCell(ui->tableWidget->currentRow()+1, ui->tableWidget->currentColumn());

    } else
        ui->tableWidget->setCurrentCell(ui->tableWidget->currentRow()+1, ui->tableWidget->currentColumn());
}

void MainWindow::on_actionNew_triggered()
{
    ui->tabWidget->addTab(new QWidget(),QString("tab %0").arg(ui->tabWidget->count()+1));
    ui->tabWidget->addTab(ui->tab_2,QString("tab %0").arg(ui->tabWidget->count()+1));

}


void MainWindow::on_tableWidget_entered(const QModelIndex &index)
{

}


void MainWindow::on_tableWidget_cellEntered(int row, int column)
{
    ui->tableWidget->insertRow ( ui->tableWidget->rowCount());
}


void MainWindow::on_pushButton_3_clicked()

{
    try {

    int k=ui->spinBox->value()-1;
    int l=ui->spinBox->value()-1;
    QVector<QString> a;
    a.resize(ui->tableWidget->rowCount());
    QVector<double> b;
    QVector<double> d;
    d.resize(ui->tableWidget->rowCount());
    int c=0;
    b.resize(ui->tableWidget->rowCount());
    if(k==-1){
        for(int i=0;i<ui->tableWidget->rowCount();i++){
         a[i]="1";
         d[i]=1;
        }
    }
        if(l==-1){
            for(int i=0;i<ui->tableWidget->rowCount();i++){
             b[i]=1;
            }
        }

    for(int i=0;i<ui->tableWidget->rowCount();i++){
        if(k!=-1){
       if(ui->tableWidget->item(i,k)){
     a[i]=ui->tableWidget->item(i,k)->text();
     qDebug() <<a[i];
       }

       else
           a[i]=" ";
        }
  if(l!=-1){
   if(ui->tableWidget->item(i,l)){
       if(ui->tableWidget->item(i,l)->text()!=" "){
     QVariant val=ui->tableWidget->item(i,l)->text();
     b[i]=val.toDouble();

     if(c<b[i]){
         c=b[i];
     }
     qDebug()<<b[i];
       }
       else{
           b[i]=0;
           qDebug() <<b[i];
       }
   }
   else{
       b[i]=0;
   qDebug() <<b[i];
    }
}
  if(k!=-1){
   if(ui->tableWidget->item(i,k)){
       if(ui->tableWidget->item(i,k)->text()!=" "){
     QVariant val1=ui->tableWidget->item(i,k)->text();
     d[i]=val1.toDouble();
     qDebug() <<d[i];
       }
       else{
           d[i]=0;
       }
   }
   else{
       d[i]=0;
    }
}
    }
    QLineSeries *seriesl = new QLineSeries();
    for(int i=0;i<ui->tableWidget->rowCount();i++){
        seriesl->append(d[i],b[i]);
    }


     QBarSet *set1 = new QBarSet("A");
     QStringList categories1;
     for(int i=0;i<ui->tableWidget->rowCount();i++){
         qDebug() <<b[i];
     set1->append(b[i]);
     categories1.append(a[i]);
}

     QBarSeries *series1 = new QBarSeries();
     series1->append(set1);


     QChart *chart1 = new QChart();
     QChart *chart2 = new QChart();
     chart2->addSeries(seriesl);
     chart2->setTitle("BarChart Example In Qt5 C++ ");
     chart2->setAnimationOptions(QChart::SeriesAnimations);
     chart1->addSeries(series1);
     chart1->setTitle("BarChart Example In Qt5 C++ ");
     chart1->setAnimationOptions(QChart::SeriesAnimations);



     QBarCategoryAxis *axis1 = new QBarCategoryAxis();
     axis1->append(categories1);
     chart1->addAxis(axis1, Qt::AlignBottom);
     series1->attachAxis(axis1);
     QValueAxis *axisY = new QValueAxis();
     axisY->setRange(0,c);
     chart1->addAxis(axisY, Qt::AlignLeft);
     series1->attachAxis(axisY);
     chart1->legend()->setVisible(true);
     chart1->legend()->setAlignment(Qt::AlignTop);
     chart2->createDefaultAxes();
     QChartView *chartView1 = new QChartView(chart1);
     QChartView *chartView2 = new QChartView(chart2);

     chartView1->setRenderHint(QPainter::Antialiasing);

     QPieSeries *series2 = new QPieSeries();
     for(int i=0;i<ui->tableWidget->rowCount();i++){
     series2->append(a[i], b[i]);
     }
     QChart *chart3= new QChart();
     chart3->addSeries(series2);
     chart3->setTitle("Simple piechart example");
     chart3->legend()->hide();

     QChartView *chartView3 = new QChartView(chart3);
     QWidget *newtab=new QWidget(ui->tabWidget);
     ui->tabWidget->addTab(newtab,QString("tab %0").arg(ui->tabWidget->count()+1));
     QHBoxLayout *hbox=new QHBoxLayout;
     ui->tabWidget->setCurrentWidget(newtab);
     hbox->addWidget(chartView1,30);
     hbox->addSpacing(5);
     hbox->addWidget(chartView2,30);
     hbox->addSpacing(5);
     hbox->addWidget(chartView3,30);
     newtab->setLayout(hbox);
}
 catch (...) {
        qDebug() <<"error";
    }
}



void MainWindow::on_actionLine_triggered()
{

    QVector<QString> a;
    a.resize(ui->tableWidget->rowCount());
    QVector<double> b;
    QVector<double> d;
    d.resize(ui->tableWidget->rowCount());
    int c=0;
    b.resize(ui->tableWidget->rowCount());
    for(int i=0;i<ui->tableWidget->rowCount();i++){
       if(ui->tableWidget->item(i,0)){
     a[i]=ui->tableWidget->item(i,0)->text();
     qDebug() <<a[i];
       }
       else
           a[i]=" ";

   if(ui->tableWidget->item(i,1)){
       if(ui->tableWidget->item(i,1)->text()!=" "){
     QVariant val=ui->tableWidget->item(i,1)->text();
     b[i]=val.toDouble();

     if(c<b[i]){
         c=b[i];
     }
     qDebug()<<b[i];
       }
       else{
           b[i]=0;
           qDebug() <<b[i];
       }
   }
   else{
       b[i]=0;
   qDebug() <<b[i];
    }

   if(ui->tableWidget->item(i,0)){
       if(ui->tableWidget->item(i,0)->text()!=" "){
     QVariant val1=ui->tableWidget->item(i,0)->text();
     d[i]=val1.toDouble();
     qDebug() <<d[i];
       }
       else{
           d[i]=0;
       }
   }
   else{
       d[i]=0;
    }

    }
    QLineSeries *seriesl = new QLineSeries();
    for(int i=0;i<ui->tableWidget->rowCount();i++){
        seriesl->append(d[i],b[i]);
    }
     QChart *chart2 = new QChart();
     chart2->addSeries(seriesl);
     chart2->setTitle("BarChart Example In Qt5 C++ ");
     chart2->setAnimationOptions(QChart::SeriesAnimations);
     chart2->createDefaultAxes();
     QChartView *chartView2 = new QChartView(chart2);
     QWidget *newTab = new QWidget(ui->tabWidget);
     ui->tabWidget->addTab(newTab,QString("tab %0").arg(ui->tabWidget->count()+1));
     chartView2->resize(1000,500);
     chartView2->setParent(newTab);
     ui->tabWidget->setCurrentWidget(newTab);
     //qDebug() <<ui->gridFrame->size();
     //QMainWindow window;
     //window.setCentralWidget(chartView2);
     //window.resize(400, 300);
     //window.show();
}


void MainWindow::on_actionBar_Chart_triggered()
{
    QVector<QString> a;
    a.resize(ui->tableWidget->rowCount());
    QVector<double> b;
    QVector<double> d;
    d.resize(ui->tableWidget->rowCount());
    int c=0;
    b.resize(ui->tableWidget->rowCount());
    for(int i=0;i<ui->tableWidget->rowCount();i++){
       if(ui->tableWidget->item(i,0)){
     a[i]=ui->tableWidget->item(i,0)->text();
     qDebug() <<a[i];
       }
       else
           a[i]=" ";

   if(ui->tableWidget->item(i,1)){
       if(ui->tableWidget->item(i,1)->text()!=" "){
     QVariant val=ui->tableWidget->item(i,1)->text();
     b[i]=val.toDouble();

     if(c<b[i]){
         c=b[i];
     }
     qDebug()<<b[i];
       }
       else{
           b[i]=0;
           qDebug() <<b[i];
       }
   }
   else{
       b[i]=0;
   qDebug() <<b[i];
    }

   if(ui->tableWidget->item(i,0)){
       if(ui->tableWidget->item(i,0)->text()!=" "){
     QVariant val1=ui->tableWidget->item(i,0)->text();
     d[i]=val1.toDouble();
     qDebug() <<d[i];
       }
       else{
           d[i]=0;
       }
   }
   else{
       d[i]=0;
    }

    }
     QBarSet *set1 = new QBarSet("A");
     QStringList categories1;
     for(int i=0;i<ui->tableWidget->rowCount();i++){
         qDebug() <<b[i];
     set1->append(b[i]);
     categories1.append(a[i]);
}

     QBarSeries *series1 = new QBarSeries();
     series1->append(set1);
     QChart *chart1 = new QChart();
     chart1->addSeries(series1);
     chart1->setTitle("BarChart Example In Qt5 C++ ");
     chart1->setAnimationOptions(QChart::SeriesAnimations);
     QBarCategoryAxis *axis1 = new QBarCategoryAxis();
     axis1->append(categories1);
     chart1->addAxis(axis1, Qt::AlignBottom);
     series1->attachAxis(axis1);
     QValueAxis *axisY = new QValueAxis();
     axisY->setRange(0,c);
     chart1->addAxis(axisY, Qt::AlignLeft);
     series1->attachAxis(axisY);
     chart1->legend()->setVisible(true);
     chart1->legend()->setAlignment(Qt::AlignTop);

     QChartView *chartView1 = new QChartView(chart1);

     qDebug() <<ui->gridFrame->size();
     chartView1->setRenderHint(QPainter::Antialiasing);
     QWidget *newTab = new QWidget(ui->tabWidget);
     ui->tabWidget->addTab(newTab,QString("tab %0").arg(ui->tabWidget->count()+1));
     chartView1->resize(1000,500);
     ui->tabWidget->setCurrentWidget(newTab);
     chartView1->setParent(newTab);

}


void MainWindow::on_actionPie_Chart_triggered()
{

    QVector<QString> a;
    a.resize(ui->tableWidget->rowCount());
    QVector<double> b;
    QVector<double> d;
    d.resize(ui->tableWidget->rowCount());
    int c=0;
    b.resize(ui->tableWidget->rowCount());
    for(int i=0;i<ui->tableWidget->rowCount();i++){
       if(ui->tableWidget->item(i,0)){
     a[i]=ui->tableWidget->item(i,0)->text();
     qDebug() <<a[i];
       }
       else
           a[i]=" ";

   if(ui->tableWidget->item(i,1)){
       if(ui->tableWidget->item(i,1)->text()!=" "){
     QVariant val=ui->tableWidget->item(i,1)->text();
     b[i]=val.toDouble();

     if(c<b[i]){
         c=b[i];
     }
     qDebug()<<b[i];
       }
       else{
           b[i]=0;
           qDebug() <<b[i];
       }
   }
   else{
       b[i]=0;
   qDebug() <<b[i];
    }

   if(ui->tableWidget->item(i,0)){
       if(ui->tableWidget->item(i,0)->text()!=" "){
     QVariant val1=ui->tableWidget->item(i,0)->text();
     d[i]=val1.toDouble();
     qDebug() <<d[i];
       }
       else{
           d[i]=0;
       }
   }
   else{
       d[i]=0;
    }

    }
    QPieSeries *series2 = new QPieSeries();
    for(int i=0;i<ui->tableWidget->rowCount();i++){
    series2->append(a[i], b[i]);
    }
    QChart *chart3= new QChart();
    chart3->addSeries(series2);
    chart3->setTitle("Simple piechart example");
    chart3->legend()->hide();

    QChartView *chartView3 = new QChartView(chart3);
    QWidget *newTab = new QWidget(ui->tabWidget);
    ui->tabWidget->addTab(newTab,QString("tab %0").arg(ui->tabWidget->count()+1));
    chartView3->resize(1000,500);
    ui->tabWidget->setCurrentWidget(newTab);
    chartView3->setParent(newTab);
    chartView3->setRenderHint(QPainter::Antialiasing);

   // QWidget *newTab = new QWidget(ui->tabWidget);
    //ui->tabWidget->addTab(newTab,QString("tab %0").arg(ui->tabWidget->count()+1));
     //connect(newTab,this)
    //MainWidget(this);
}

void MainWindow::on_pushButton_4_clicked()
{
    for(int i=0;i<ui->tableWidget->rowCount();i++){
        for(int j=0;j<ui->tableWidget->columnCount();j++){
            QTableWidgetItem *item = ui->tableWidget->item(i, j);
            item = new QTableWidgetItem();
            item->setText(QString::fromStdString(" "));
            ui->tableWidget->setItem(i,j,item);
        }
    }
}


void MainWindow::on_pushButton_2_clicked()
{
    QFile file(QString::fromStdString(file_path));
   file.open(QFile::WriteOnly);
    QTextStream out(&file);
    QString text=ui->plainTextEdit->toPlainText();
   out<<text;
   file.flush();
    file.close();
    Dataset *dataset= readCSV(file_path);
}


void MainWindow::on_pushButton_5_clicked()
{
    ui->plainTextEdit->clear();
    a_.clear();
    b_.clear();
    d_.clear();
   //QString path = QFileDialog::getOpenFileName(this,"Open File");
   //if(path.isEmpty()) return;

   QFile file(QString::fromStdString(file_path));
    if(!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::critical(this,"Error", file.errorString());
        return;
    }
    thresh=500;
  //vector<int> a_;
  //vector<int> b_;
  //vector<int> d_;
    QTextStream stream(&file);
    while(!stream.atEnd()){
        QString line=stream.readLine();
        ui->plainTextEdit->insertPlainText("10 bit numbers");
        ui->plainTextEdit->insertPlainText("\n");
        ui->plainTextEdit->insertPlainText("Threshold - 500");
        ui->plainTextEdit->insertPlainText("\n");
        int c=bintodec(line);
        ui->plainTextEdit->insertPlainText(line);
        ui->plainTextEdit->insertPlainText("\n");
        ui->plainTextEdit->insertPlainText(QString::number(c));
        a_.push_back(c);
        ui->plainTextEdit->insertPlainText("\n");
        if(c>500){
            ui->plainTextEdit->insertPlainText("Activity found");
            ui->plainTextEdit->insertPlainText("\n");
            b_.push_back(c);
            d_.push_back(c);
        }
        else{
            b_.push_back(thresh);
        }
        ui->plainTextEdit->insertPlainText("\n");
    }
    file.close();
    line_graph(a_,b_,d_);

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

void MainWindow::line_graph(vector<int> a,vector<int> b,vector<int> d)
{
/*
    QVector<QString> a;
    a.resize(ui->tableWidget->rowCount());
    QVector<double> b;
    QVector<double> d;
    d.resize(ui->tableWidget->rowCount());
    int c=0;
    b.resize(ui->tableWidget->rowCount());
    for(int i=0;i<ui->tableWidget->rowCount();i++){
       if(ui->tableWidget->item(i,0)){
     a[i]=ui->tableWidget->item(i,0)->text();
     qDebug() <<a[i];
       }
       else
           a[i]=" ";

   if(ui->tableWidget->item(i,1)){
       if(ui->tableWidget->item(i,1)->text()!=" "){
     QVariant val=ui->tableWidget->item(i,1)->text();
     b[i]=val.toDouble();

     if(c<b[i]){
         c=b[i];
     }
     qDebug()<<b[i];
       }
       else{
           b[i]=0;
           qDebug() <<b[i];
       }
   }
   else{
       b[i]=0;
   qDebug() <<b[i];
    }

   if(ui->tableWidget->item(i,0)){
       if(ui->tableWidget->item(i,0)->text()!=" "){
     QVariant val1=ui->tableWidget->item(i,0)->text();
     d[i]=val1.toDouble();
     qDebug() <<d[i];
       }
       else{
           d[i]=0;
       }
   }
   else{
       d[i]=0;
    }

    }
    */
    QLineSeries *seriesl = new QLineSeries();
    for(int i=0;i<a.size();i++){
        seriesl->append(i,a[i]);
    }
    QLineSeries *series2=new QLineSeries();
    for(int i=0;i<a.size();i++){
        series2->append(i,b[i]);
    }
    QPen pen("red");
    pen.setWidth(3);
    seriesl->setPen(pen);
    QPen pen1("green");
    pen1.setWidth(4);
    series2->setPen(pen1);
    QChart *chart2 = new QChart();
    QLineSeries *series3=new QLineSeries();
    for(int i=0;i<a.size();i++){
      series3->append(i,500);
    }
    QPen pen2("blue");
     series3->setPen(pen2);
     seriesl->setName("Total");
     series2->setName("Active");
     series3->setName("Threshold");
     chart2->addSeries(seriesl);
     chart2->addSeries(series2);
     chart2->addSeries(series3);
     chart2->setTitle("BarChart Example In Qt5 C++ ");
     chart2->setAnimationOptions(QChart::SeriesAnimations);
     chart2->createDefaultAxes();
     ChartView *chartView2 = new ChartView(chart2);
     QWidget *newTab = new QWidget(ui->tabWidget);
     QVBoxLayout *vbox = new QVBoxLayout;
     vbox->addSpacing(10);
     QPushButton *button=new QPushButton(QObject::tr("&RESET"), newTab);
     button->setStyleSheet("background:blue;color:white;font:20px;border-radius:4px;padding-left:5px;padding-right:5px");
     if(imp[1]<=0){
     ui->tabWidget->addTab(newTab,QString("tab %0").arg(ui->tabWidget->count()+1));
     imp[1]=ui->tabWidget->count();
     }
     else{
         ui->tabWidget->removeTab(imp[1]-1);
         ui->tabWidget->addTab(newTab,QString("tab %0").arg(ui->tabWidget->count()+1));
         imp[1]=ui->tabWidget->count();
     }

     ui->tabWidget->setCurrentWidget(newTab);
    // QPushButton *button_=new QPushButton;
     chartView2->resize(1000,500);
     vbox->addWidget(chartView2);
     QHBoxLayout *hbox=new QHBoxLayout;
     hbox->addSpacing(20);
     hbox->addWidget(button);
     hbox->addSpacing(10);
     QLabel *ql =new QLabel(QObject::tr(
                                "<b style=color:Green><h2>Active</h2></b>"), newTab);
     hbox->addWidget(ql);
     hbox->addSpacing(10);
     QTextEdit *ac=new QTextEdit;
     ac->setMaximumHeight(button->height());
     hbox->addWidget(ac);
     hbox->addSpacing(10);
     QLabel *ql1 =new QLabel(QObject::tr("<b style=color:red><h2>Total</h2></b>"), newTab);
     hbox->addWidget(ql1);
     hbox->addSpacing(10);
     QTextEdit *ac1=new QTextEdit;
     ac1->setMaximumHeight(button->height());
     hbox->addWidget(ac1);
     hbox->addSpacing(10);
     QLabel *ql2 =new QLabel(QObject::tr("<b style=color:blue><h2>Threshold</h2></b>"), newTab);
     hbox->addWidget(ql2);
     hbox->addSpacing(10);
     QTextEdit *ac2=new QTextEdit;
     ac2->setMaximumHeight(button->height());
     hbox->addWidget(ac2);
     hbox->addSpacing(10);
     QLabel *ql3 =new QLabel(QObject::tr("<b style=color:blue><h2>Select Points</h2></b>"), newTab);
     hbox->addWidget(ql3);
     hbox->addSpacing(5);
     QComboBox *cb=new QComboBox();
    cb->addItem(">");
    cb->addItem("<");
    cb->addItem("=");
     hbox->addWidget(cb);
      hbox->addSpacing(10);
      QTextEdit *ac3=new QTextEdit();
     ac3->setMaximumHeight(button->height());
     hbox->addWidget(ac3);
     hbox->addSpacing(10);
     vbox->addItem(hbox);
     newTab->setLayout(vbox);
     ac->setPlainText(QString::number(d.size()));
     ac1->setPlainText(QString::number(a.size()));
     ac2->setPlainText(QString::number(thresh));
     index=ui->tabWidget->indexOf(newTab);
     x=ac3->toPlainText().toInt();
     ui->tabWidget->setCurrentWidget(newTab);
     y=cb->currentIndex();
     connect(button, &QPushButton::clicked, this, &MainWindow::onButtonClicked);
      connect(ac3, &QTextEdit::textChanged, this, &MainWindow::textchanged);
}
void MainWindow::textchanged(){
    compare(x,y);
}
void MainWindow::textchangedd(){
    compare(y,x);
}
void MainWindow::onButtonClicked(){

    line_graph(a_,b_,d_);
}
void MainWindow::mousePressEvent (QMouseEvent * e) {
    if(chartView2->chart()->isEnabled()) {
        auto curPoint = QCursor::pos();
        curPoint = chartView2->mapFromGlobal(curPoint);
        auto pickVal = chartView2->mapToScene(curPoint);
        pickVal = chartView2->chart()->mapFromScene(curPoint);
        pickVal = chartView2->chart()->mapToValue(curPoint,chartView2->chart()->series().at(0));
        qDebug() << "Diagram Picked Value : " << pickVal;
    }
}

void MainWindow::compare(int n,int n1)
{
    x=n;
    y=n1;
    QLineSeries *seriesl = new QLineSeries();
    int k=0;
    e_.clear();
    if(n1==0){
    for(int i=0;i<a_.size();i++){
        if(a_[i]>n){
            e_.push_back(a_[i]);
        seriesl->append(i,a_[i]);
        k++;
        }
    }
    }
    else if(n1==1){
        for(int i=0;i<a_.size();i++){
            if(a_[i]<n){
                e_.push_back(a_[i]);
            seriesl->append(i,a_[i]);
            k++;
            }
        }
    }
    else if(n1==2){
        for(int i=0;i<a_.size();i++){
            if(a_[i]==n){
                e_.push_back(a_[i]);
            seriesl->append(i,a_[i]);
            k++;
            }
        }
    }
    QPen pen("green");
    pen.setWidth(3);
    seriesl->setPen(pen);
     QChart *chart2 = new QChart();
     chart2->addSeries(seriesl);
     chart2->setTitle("BarChart Example In Qt5 C++ ");
     chart2->setAnimationOptions(QChart::SeriesAnimations);
     chart2->createDefaultAxes();
     ChartView *chartView2 = new ChartView(chart2);
     QWidget *newTab = new QWidget(ui->tabWidget);
     QVBoxLayout *vbox = new QVBoxLayout;
     vbox->addSpacing(10);
     QPushButton *button=new QPushButton(QObject::tr("&RESET"), newTab);
     button->setStyleSheet("background:blue;color:white;font:20px;border-radius:4px;padding-left:5px;padding-right:5px");
     if(imp[2]<=0){
     ui->tabWidget->addTab(newTab,QString("tab %0").arg(ui->tabWidget->count()+1));
     imp[2]=ui->tabWidget->count();
     }
     else{
         ui->tabWidget->removeTab(imp[2]-1);
         ui->tabWidget->addTab(newTab,QString("tab %0").arg(ui->tabWidget->count()+1));
         imp[2]=ui->tabWidget->count();
     }
    // QPushButton *button_=new QPushButton;
     chartView2->resize(1000,500);
     vbox->addWidget(chartView2);
     //ui->tabWidget->setCurrentWidget(newTab);
     QHBoxLayout *hbox=new QHBoxLayout;
     hbox->addSpacing(20);
     hbox->addWidget(button);
     hbox->addSpacing(10);
     QLabel *ql =new QLabel(QObject::tr(
                                "<b style=color:Green><h2>Active</h2></b>"), newTab);
     hbox->addWidget(ql);
     hbox->addSpacing(10);
     QTextEdit *ac=new QTextEdit;
     ac->setMaximumHeight(button->height());
     hbox->addWidget(ac);
     hbox->addSpacing(10);
     QLabel *ql1 =new QLabel(QObject::tr("<b style=color:red><h2>Total</h2></b>"), newTab);
     hbox->addWidget(ql1);
     hbox->addSpacing(10);
     QTextEdit *ac1=new QTextEdit;
     ac1->setMaximumHeight(button->height());
     hbox->addWidget(ac1);
     hbox->addSpacing(10);
     QLabel *ql2 =new QLabel(QObject::tr("<b style=color:blue><h2>Threshold</h2></b>"), newTab);
     hbox->addWidget(ql2);
     hbox->addSpacing(10);
     QTextEdit *ac2=new QTextEdit;
     ac2->setMaximumHeight(button->height());
     hbox->addWidget(ac2);
     hbox->addSpacing(10);
     QPushButton *button1=new QPushButton(QObject::tr("&Compare With Original graph"), newTab);
     button1->setStyleSheet("background:blue;color:white;font:20px;border-radius:4px;padding-left:5px;padding-right:5px");
     hbox->addWidget(button1);
     vbox->addItem(hbox);
     newTab->setLayout(vbox);
     ac->setPlainText(QString::number(k));
     ac1->setPlainText(QString::number(a_.size()));
     ac2->setPlainText(QString::number(thresh));
     int z=ndigits(n);
     connect(button1, &QPushButton::clicked, this, &MainWindow::comparee);

}
void MainWindow::comparee(){
    QLineSeries *series1 = new QLineSeries();
    QLineSeries *series2 = new QLineSeries();
    QLineSeries *series3 = new QLineSeries();
    QLineSeries *series4 = new QLineSeries();
    for(int i=0;i<a_.size();i++){
        series1->append(i,a_[i]);
    }
    for(int i=0;i<b_.size();i++){
        series2->append(i,b_[i]);
    }
    for(int i=0;i<a_.size();i++){
      series3->append(i,500);
    }
    for(int i=0;i<e_.size();i++){
      series4->append(i,e_[i]);
    }
    QPen pen1("red");
    pen1.setWidth(2);
    series1->setPen(pen1);
    QPen pen2("green");
    pen2.setWidth(2);
    series2->setPen(pen2);
    QPen pen3("blue");
    pen3.setWidth(2);
    series3->setPen(pen3);
    QPen pen4("green");
    pen4.setWidth(2);
    series4->setPen(pen4);
    series1->setName("Total");
    series2->setName("Active");
    series3->setName("Threshold");
    series4->setName("Based on Condition");
    QChart *chart1 = new QChart();
    QChart *chart2 = new QChart();
    QChart *chart3 = new QChart();
    chart1->addSeries(series1);
    chart1->addSeries(series2);
    chart1->addSeries(series3);
    chart2->addSeries(series4);
    chart1->setAnimationOptions(QChart::SeriesAnimations);
    chart1->createDefaultAxes();
    chart2->createDefaultAxes();
    ChartView *chartView1 = new ChartView(chart1);
    ChartView *chartView2 = new ChartView(chart2);
    QWidget *newTab = new QWidget(ui->tabWidget);
    ui->tabWidget->addTab(newTab,QString("tab %0").arg(ui->tabWidget->count()+1));
    QHBoxLayout *hbox=new QHBoxLayout;
    ui->tabWidget->setCurrentWidget(newTab);
    hbox->addWidget(chartView1);
    hbox->addSpacing(5);
    hbox->addWidget(chartView2);
    newTab->setLayout(hbox);
}
int MainWindow::ndigits(int a){
  int k=0;
  for(;a>0;k++){
      a=a/10;
  }
  return k;
}
