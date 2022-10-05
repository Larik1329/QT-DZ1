#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "workwithtable.h"
#include "delegatebutton.h"
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
    initModel();
    workwithtable = new WorkWithTable();

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
   QStandardItemModel* model = new QStandardItemModel();
    // Определить элемент

    //QStandardItemModel model(4, 2);
   /* QTableView tableView;
    tableView.setModel(_tModel);

    QStandardItem* item = 0;
   for(int i = 0;i < 10;i++){
       item = new QStandardItem(QString("%1").arg(i));
       model->setItem(i,0,item);
       item = new QStandardItem(QString("%1").arg(i*2));
       model->setItem(i,1,item);
       item = new QStandardItem(QString("%1").arg(i*3));
       model->setItem(i,2,item);
    }*/

   //ui->tableView->setModel(model);
    //on_CreateFileButton_clicked();//----



//    //_tModel->reset();
//    //ui->tableView->show();
//    QTableView tableView;
//    tableView.setModel(model);


//DelegateButton delegate= new DelegateButton();
//tableView.setItemDelegate(&delegate);
//for (int row = 0; row < 2; ++row) {
//    for (int column = 0; column < 2; ++column) {
//        QModelIndex index = model->index(row, column, QModelIndex());
//        model->setData(index, QVariant((row + 1) * (column + 1)));
//    }
//}     tableView.setWindowTitle(QObject::tr("Spin Box Delegate"));
//tableView.show();

    //ui->tableView->setItemDelegate(&delegate);

    QSignalMapper *signalMapper = new QSignalMapper(this);


    for( int i=0; i<6; i++ ) { //replace rows.length with your list or vector which consists of the data for your rows.
        //do something with your data for normal cells...
        QModelIndex item = _tModel->index(i, 5);

        //make new button for this row
        item.sibling(1,1);
        QPushButton *cartButton = new QPushButton("Edit line");
        ui->tableView->setIndexWidget(item, cartButton);

        signalMapper->setMapping(cartButton, i);

        connect(cartButton, SIGNAL(clicked(bool)), signalMapper, SLOT(map()));

        item = _tModel->index(i, 6);

        //make new button for this row
        item.sibling(1,1);
        cartButton = new QPushButton("Delete line");
        ui->tableView->setIndexWidget(item, cartButton);

        signalMapper->setMapping(cartButton, i);  // Исправить!!! добавляет в тот же Qmap

        connect(cartButton, SIGNAL(clicked(bool)), signalMapper, SLOT(map()));
    }
    connect(signalMapper, SIGNAL(mapped(int)), this, SLOT(doSomething(int)));
    //_tModel->reset();
}

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




