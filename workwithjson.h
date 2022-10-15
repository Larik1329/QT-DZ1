#ifndef WORKWITHJSON_H
#define WORKWITHJSON_H
#include <QJsonObject>

class WorkWithJson
{
public:

    struct Workers
    {
        QString id;
        QString worker;
        QString specialnost;
        QString zp;
        QString pol;
        Workers(QString _id, QString _worker, QString _specialnost, QString _zp, QString _pol )
        {
            id=_id;
            worker=_worker;
            specialnost=_specialnost;
            zp=_zp;
            pol=_pol;
        }
        Workers(){
            this->id="";
            this->pol="";
            this->specialnost="";
            this->worker="";
            this->zp="";
        };
    };
    WorkWithJson();
    QJsonDocument  JsonSerialise(QVector <Workers> FileOriginData);
    QJsonObject JsonDefaultSerialise();
    QVector <Workers> readJsonFile(QString FilePath);
    QVector <Workers> JsonDeserialise(QJsonObject Data);
private:
    QVector <Workers> JsonDeserialise(QString FileOriginData);    
};

#endif // WORKWITHJSON_H
