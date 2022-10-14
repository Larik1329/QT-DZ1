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
    workwithtable->DefaultVeiw(ui,_tModel);
    workwithtable->TableRefresh(ui,_tModel);
    ButtonsInTableAdd(GlobalParam::TableData.count());

}
void MainWindow::ButtonsInTableAdd(int rowLenght){
    signalMapper=new QSignalMapper(this);
    signalMapper2=new QSignalMapper(this);
    for( int i=0; i<rowLenght; i++ ) {

        QModelIndex item = _tModel->index(i, 5);
        QPushButton *cartButton = new QPushButton("Edit line");
        ui->tableView->setIndexWidget(item, cartButton);
        connect(cartButton, SIGNAL(clicked()), signalMapper, SLOT(map()));
        signalMapper->setMapping(cartButton, i);

        item = _tModel->index(i, 6);
        cartButton = new QPushButton("Delete line");
        ui->tableView->setIndexWidget(item, cartButton);
        connect(cartButton, SIGNAL(clicked()), signalMapper2, SLOT(map()));
        signalMapper2->setMapping(cartButton, i);
    }
    connect(signalMapper, SIGNAL(mappedInt(int)), this, SLOT(mySlot_Test(int)));
    connect(signalMapper2, SIGNAL(mappedInt(int)), this, SLOT(mySlot_Test2(int)));
}
void MainWindow::mySlot_Test(int i){

}
void MainWindow::mySlot_Test2(int i){

}

void MainWindow::on_OpenFileButton_clicked() //Открытие файла
{
    if (GlobalParam::FileInRam){
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Предупреждение", "Вы действительно хотите открыть новый файл, не сохранив текущий файл?",
                                      QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            _tModel = new TableViewModel(7);
            workwithtable->FileOpen(ui);
            workwithtable->FileOriginDataSaver(ui);
            workwithtable->TableRefresh(ui,_tModel);
    ButtonsInTableAdd(GlobalParam::TableData.count());
        }
    }
    else
    {
        _tModel = new TableViewModel(7);
        workwithtable->FileOpen(ui);
        workwithtable->FileOriginDataSaver(ui);
        workwithtable->TableRefresh(ui,_tModel);
    ButtonsInTableAdd(GlobalParam::TableData.count());
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
            _tModel = new TableViewModel(7);
            workwithtable->DefaultVeiw(ui,_tModel);
            workwithtable->FileOriginDataSaver(ui);
            workwithtable->TableRefresh(ui,_tModel);
    ButtonsInTableAdd(GlobalParam::TableData.count());
        }
    }
    else{
        GlobalParam::FileInRam=true;
        _tModel = new TableViewModel(7);
        ui->label_2->setText("");
        ui->CancelChangesButton->setEnabled(true);
        ui->SaveButton->setEnabled(true);
        workwithtable->DefaultVeiw(ui,_tModel);
        workwithtable->FileOriginDataSaver(ui);
        workwithtable->TableRefresh(ui,_tModel);
    ButtonsInTableAdd(GlobalParam::TableData.count());
    }
}

void MainWindow::on_CancelChangesButton_clicked() //Отмена изменений
{
    _tModel = new TableViewModel(7);
    workwithtable->LoadFileOriginData(ui);
    workwithtable->TableRefresh(ui,_tModel);
    ButtonsInTableAdd(GlobalParam::TableData.count());
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




