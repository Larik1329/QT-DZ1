#include "workwithtable.h"
#include "qjsondocument.h"
#include "ui_mainwindow.h"
#include "workwithjson.h"
#include <QFileDialog>
#include <QFile>
#include <tableviewmodel.h>

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


void WorkWithTable::FileOpen(Ui::MainWindow * ui) //Функция для открытия файла и вывода в таблицу + активация кнопок
{
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

    //if (!(str=="")){
    //QMessageBox *msgBox = new QMessageBox(0);
    //QMessageBox::about(msgBox, "Предупреждение","Файл не того формата!!!");
    //}


}

void WorkWithTable::DefaultVeiw(Ui::MainWindow * ui) //Добавление двух объектов в таблицу (для примера)
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

