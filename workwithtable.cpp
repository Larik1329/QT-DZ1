#include "workwithtable.h"
#include "mainwindow.h"
#include "qjsondocument.h"
#include "ui_mainwindow.h"
#include "workwithjson.h"
#include <QFileDialog>
#include <QFile>
#include <tableviewmodel.h>
#include <QString>

QT_BEGIN_NAMESPACE
namespace GlobalParam {
bool FileInRam=false;
QVector <WorkWithJson::Workers> TableData;
QVector <WorkWithJson::Workers> FileOriginData;
}
QT_END_NAMESPACE

WorkWithTable::WorkWithTable(){}

WorkWithTable::~WorkWithTable(){}


void WorkWithTable::LoadFileOriginData(Ui::MainWindow * ui)
{
    GlobalParam::TableData=GlobalParam::FileOriginData;
}

void WorkWithTable::EditRow(Ui::MainWindow * ui, int row){
    ui->lineEdit_Name->setText(GlobalParam::TableData[row].worker);
    ui->lineEdit_Id->setText(GlobalParam::TableData[row].id);
    ui->lineEdit_Pol->setText(GlobalParam::TableData[row].pol);
    ui->lineEdit_Specialnost->setText(GlobalParam::TableData[row].specialnost);
    ui->lineEdit_ZP->setText(GlobalParam::TableData[row].zp);
    ui->AddButton->setText("Изменить строку " + QString::number(row+1));
}

void WorkWithTable::ConfirmEditRow(Ui::MainWindow * ui, int row){
    GlobalParam::TableData[row].worker=ui->lineEdit_Name->text();
    GlobalParam::TableData[row].id=ui->lineEdit_Id->text();
    GlobalParam::TableData[row].pol=ui->lineEdit_Pol->text();
    GlobalParam::TableData[row].specialnost=ui->lineEdit_Specialnost->text();
    GlobalParam::TableData[row].zp=ui->lineEdit_ZP->text();
    ui->lineEdit_Name->setText("");
    ui->lineEdit_Id->setText("");
    ui->lineEdit_Pol->setText("");
    ui->lineEdit_Specialnost->setText("");
    ui->lineEdit_ZP->setText("");
    ui->AddButton->setText("Добавить");
}


void WorkWithTable::AddRow(Ui::MainWindow * ui)
{
    WorkWithJson::Workers newWorker;
    newWorker.worker=ui->lineEdit_Name->text();
    newWorker.id=ui->lineEdit_Id->text();
    newWorker.pol=ui->lineEdit_Pol->text();
    newWorker.specialnost=ui->lineEdit_Specialnost->text();
    newWorker.zp=ui->lineEdit_ZP->text();
    GlobalParam::TableData.append(newWorker);
    ui->lineEdit_Name->setText("");
    ui->lineEdit_Id->setText("");
    ui->lineEdit_Pol->setText("");
    ui->lineEdit_Specialnost->setText("");
    ui->lineEdit_ZP->setText("");

}

void WorkWithTable::DeleteRow(Ui::MainWindow * ui, int row){
    GlobalParam::TableData.remove(row);
}

void WorkWithTable::FileOpen(Ui::MainWindow * ui) //Функция для открытия файла и вывода в таблицу + активация кнопок
{
    //GlobalParam::FileInRam=false;
     QString str = QFileDialog::getOpenFileName(0, "Выбор файла с БД", "","*.json");
    if (str.isEmpty())
        return;

    GlobalParam::FileInRam=true;
    QString FilePath=str;
    ui->label_2->setText(FilePath);
    WorkWithJson *workwithjson = new WorkWithJson();
    GlobalParam::TableData=workwithjson->readJsonFile(FilePath);
    ui->CancelChangesButton->setEnabled(true);
    ui->SaveButton->setEnabled(true);
    ui->AddButton->setEnabled(true);
    //if (!(str=="")){
    //QMessageBox *msgBox = new QMessageBox(0);
    //QMessageBox::about(msgBox, "Предупреждение","Файл не того формата!!!");
    //}


}

void WorkWithTable::DefaultVeiw(Ui::MainWindow * ui,TableViewModel* _tModel) //Добавление двух объектов в таблицу (для примера)
{    
    WorkWithJson *workwithjson = new WorkWithJson();
    GlobalParam::TableData = workwithjson->JsonDeserialise(workwithjson->JsonDefaultSerialise());
    FileOriginDataSaver(ui);
}

void WorkWithTable::TableRefresh(Ui::MainWindow * ui,TableViewModel* _tModel) //Перезапись таблицы из глобальной переменной TableData
{
    //_tModel = new TableViewModel(7);
    ui->tableView->setModel(_tModel);
    QList<QString> tTest;
    foreach (WorkWithJson::Workers worker, GlobalParam::TableData)
    {
        tTest.append(worker.id);
        tTest.append(worker.worker);
        tTest.append(worker.specialnost);
        tTest.append(worker.zp);
        tTest.append(worker.pol);
        tTest.append("");
        tTest.append("");
        _tModel->append(tTest);
        tTest.clear();

    }
    _tModel->reset();

}

void WorkWithTable::FileOriginDataSaver(Ui::MainWindow * ui) //Сохранение начального состояния таблицы (используется Vector)
{
    GlobalParam::FileOriginData=GlobalParam::TableData;
}

bool WorkWithTable::FileSave(Ui::MainWindow * ui)
{
    QString fileName="Default";
    if (ui->label_2->text()!="") {
        fileName=ui->label_2->text();
    }
    else {
        fileName=QFileDialog::getSaveFileName(0,"Выбор/создание файла для сохранения","","*.json");
    }

    if(fileName!="")
     {
        QFile jsonFile(fileName);
        jsonFile.open(QIODevice::WriteOnly);
        WorkWithJson *workwithjson = new WorkWithJson();
        QJsonDocument doc = workwithjson->JsonSerialise(GlobalParam::FileOriginData);
        jsonFile.write(doc.toJson());
        jsonFile.close();
        return true;
    }
    else return false;

}

