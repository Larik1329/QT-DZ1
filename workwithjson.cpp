#include "workwithjson.h"
#include <QVector>
#include <QFileDialog>
#include <QMessageBox>
#include <QCloseEvent>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonArray>

WorkWithJson::WorkWithJson()
{

}



QJsonObject WorkWithJson::JsonDefaultSerialise() //Создание таблицы по умолчанию в json формате
{
    Workers:Workers obj1("1","vova","slesar","12000","m");
    QJsonObject worker1;
    worker1.insert("1id",obj1.id);
    worker1.insert("2worker",obj1.worker);
    worker1.insert("3specialnost",obj1.specialnost);
    worker1.insert("4zp",obj1.zp);
    worker1.insert("5pol",obj1.pol);

    Workers obj2("2","vovan","programmer","14000","m");
    QJsonObject worker2;
    worker2.insert("1id",obj2.id);
    worker2.insert("2worker",obj2.worker);
    worker2.insert("3specialnost",obj2.specialnost);
    worker2.insert("4zp",obj2.zp);
    worker2.insert("5pol",obj2.pol);

    QJsonObject content;
    content.insert( "worker1", worker1 );
    content.insert( "worker2", worker2 );

   /* QJsonDocument document;
    document.setObject( content );
     QByteArray bytes = document.toJson( QJsonDocument::Indented );
      QFile file( path );
       if( file.open( QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate ) )
       {
           QTextStream iStream( &file );
           iStream.setCodec( "utf-8" );
           iStream << bytes;
           file.close();
       }
       else
       {
           cout << "file open failed: " << path.toStdString() << endl;
       }*/
    return content;
}

QVector <WorkWithJson::Workers> WorkWithJson::readJsonFile(QString FilePath) //Считывание данных с json файла
   {    
         QFile file (FilePath);        
         file.open(QIODevice::ReadOnly | QIODevice::Text);
         QString FileOriginData = file.readAll();
         file.close();
         return JsonDeserialise(FileOriginData);
}

QJsonDocument  WorkWithJson::JsonSerialise(QVector <Workers> FileOriginData)
{
    QJsonDocument document;
    int c=0;
    QJsonObject workers;
    //workers.constEnd();
    foreach (const auto& tempFOD, FileOriginData){
        QJsonObject worker;
        workers.end();
            worker.insert("1id",tempFOD.id);
            worker.insert("2worker",tempFOD.worker);
            worker.insert("3specialnost",tempFOD.specialnost);
            worker.insert("4zp",tempFOD.zp);
            worker.insert("5pol",tempFOD.pol);
            workers.insert("Worker"+QString::number(c),worker);///!!!!!!!!!!!!!!!

        c++;
    }
    document.setObject(workers);
    return document;
}



QVector <WorkWithJson::Workers> WorkWithJson::JsonDeserialise(QString FileOriginData)
{

Workers:Workers tempWorkers("","","","","");
    QVector <WorkWithJson::Workers> JsonMainFile;
    QJsonParseError jerror;
    QJsonDocument d = QJsonDocument::fromJson(FileOriginData.toUtf8(),&jerror);
    ////====================Добавить обработку ошибок!!!
    QJsonObject temp1Object = d.object();
    QList<QString> Title =temp1Object.keys();
    int count=Title.count();
    QList<int> structId;
    for (int i = 0; i < count; ++i) {
        structId.append(Title[i].remove("Worker").toInt());
    }
    std::sort(std::begin(structId), std::end(structId)); ///!!!!!!!!!!!!!!!!!!!!!!!
    for (int i = 0; i < count; ++i) {
        QJsonObject temp2Object = temp1Object.value("Worker"+QString::number(structId[i])).toObject();
        tempWorkers.id=temp2Object.value("1id").toString();
        tempWorkers.worker=temp2Object.value("2worker").toString();
        tempWorkers.specialnost=temp2Object.value("3specialnost").toString();
        tempWorkers.zp=temp2Object.value("4zp").toString();
        tempWorkers.pol=temp2Object.value("5pol").toString();

        JsonMainFile.push_back(tempWorkers);
    }
    return JsonMainFile;
}

QVector <WorkWithJson::Workers> WorkWithJson::JsonDeserialise(QJsonObject Data)
{

Workers:Workers tempWorkers("","","","","");
    QVector <WorkWithJson::Workers> JsonMainFile;
    QJsonParseError jerror;
    QJsonDocument d;
    d.setObject(Data);
    ////====================Добавить обработку ошибок!!!
    QJsonObject temp1Object = d.object();
    foreach (const auto& temp1, temp1Object.keys()) {
        QJsonObject temp2Object = temp1Object.value(temp1).toObject();
        tempWorkers.id=temp2Object.value("1id").toString();
        tempWorkers.worker=temp2Object.value("2worker").toString();
        tempWorkers.specialnost=temp2Object.value("3specialnost").toString();
        tempWorkers.zp=temp2Object.value("4zp").toString();
        tempWorkers.pol=temp2Object.value("5pol").toString();

        JsonMainFile.push_back(tempWorkers);
    }
    return JsonMainFile;
}
