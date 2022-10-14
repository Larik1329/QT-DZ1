#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "workwithtable.h"
#include <QVector>
#include <QFileDialog>
#include <QMessageBox>
#include <QCloseEvent>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonArray>
#include <QStandardItemModel>
#include <QMainWindow>
#include <QSignalMapper>

MainWindow::MainWindow(QWidget *parent):QMainWindow(parent), ui(new Ui::MainWindow)
{    
    ui->setupUi(this);
    signalMapper = new QSignalMapper(this);
    workwithtable = new WorkWithTable();
    initModel();
}

MainWindow::~MainWindow()
{    
    delete ui;    
}


void  MainWindow::initModel(){
   _tModel = new TableViewModel(7);//NNAADDAA
    ui->tableView->setModel(_tModel);//NNAADDAA
   workwithtable->DefaultVeiw(ui);
    workwithtable->TableRefresh(ui,_tModel);

signalMapper=new QSignalMapper(this);



    for( int i=0; i<6; i++ ) { //replace rows.length with your list or vector which consists of the data for your rows.
        //do something with your data for normal cells...
        QModelIndex item = _tModel->index(i, 5);

        //make new button for this row
        //item.sibling(1,1);
        QPushButton *cartButton = new QPushButton("Edit line");
        ui->tableView->setIndexWidget(item, cartButton);


        connect(cartButton, SIGNAL(clicked(bool)), signalMapper, SLOT(map()));
        signalMapper->setMapping(cartButton, i);
       /*  item = _tModel->index(i, 6);

        //make new button for this row
       item.sibling(1,1);
        cartButton = new QPushButton("Delete line");
        ui->tableView->setIndexWidget(item, cartButton);

        signalMapper->setMapping(cartButton, i);  // Исправить!!! добавляет в тот же Qmap

        connect(cartButton, SIGNAL(clicked()), signalMapper, SLOT(map()));*/
    }
    connect(signalMapper, SIGNAL(mappedInt(int)), this, SLOT(mySlot_Test(int)));
    //_tModel->reset();
}
void MainWindow::mySlot_Test(int i){

}
/*void MainWindow::map(){
    emit mapped(1);
}*/


void MainWindow::on_OpenFileButton_clicked() //Открытие файла
{
    if (GlobalParam::FileInRam){
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Предупреждение", "Вы действительно хотите открыть новый файл, не сохранив текущий файл?",
                                      QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            workwithtable->FileOpen(ui);
            workwithtable->FileOriginDataSaver(ui);
            workwithtable->TableRefresh(ui,_tModel);
        }
    }
    else
    {
        workwithtable->FileOpen(ui);
        workwithtable->FileOriginDataSaver(ui);
        workwithtable->TableRefresh(ui,_tModel);
    }
}

void MainWindow::on_CreateFileButton_clicked() //Создание нового файла, только в оперативке
{
    if (GlobalParam::FileInRam) {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Предупреждение", "Вы действительно хотите создать новый файл, не сохранив текущий файл?",
                                      QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            ui->label_2->setText("");
            workwithtable->DefaultVeiw(ui);
            workwithtable->FileOriginDataSaver(ui);
            workwithtable->TableRefresh(ui,_tModel);
        }
    }
    else{
        GlobalParam::FileInRam=true;
        ui->label_2->setText("");
        ui->CancelChangesButton->setEnabled(true);
        ui->SaveButton->setEnabled(true);
        workwithtable->DefaultVeiw(ui);
        workwithtable->FileOriginDataSaver(ui);
        workwithtable->TableRefresh(ui,_tModel);
    }
}

void MainWindow::on_CancelChangesButton_clicked() //Отмена изменений
{
    workwithtable->LoadFileOriginData(ui);
    workwithtable->TableRefresh(ui,_tModel);
}

void MainWindow::on_SaveButton_clicked() //Сохранение файла
{
    workwithtable->FileOriginDataSaver(ui);
    workwithtable->FileSave(ui);
}

void MainWindow::closeEvent (QCloseEvent *event) //Сохранение при закрытии, если открыто
{
    if(GlobalParam::FileInRam){
        QMessageBox::StandardButton resBtn=  QMessageBox::question( this,tr("Редактор БД"),
                                                                   tr("Вы хотите сохранить внесенные изменения?"),
                                                                   QMessageBox::Cancel |QMessageBox::No | QMessageBox::Yes
                                                                   );

        if (resBtn != QMessageBox::Yes) {
            if(resBtn==QMessageBox::No){
                event->accept();
            }
            else
                event->ignore();
        } else {
            workwithtable->FileOriginDataSaver(ui);
            if(workwithtable->FileSave(ui))
            event->accept();
            else event->ignore();
        }
    }
    else
        event->accept();
}




