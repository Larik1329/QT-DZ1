#ifndef WORKWITHTABLE_H
#define WORKWITHTABLE_H
#include "tableviewmodel.h"
#include "ui_mainwindow.h"
#include "workwithjson.h"
#include <QJsonArray>

QT_BEGIN_NAMESPACE
namespace GlobalParam {
extern  bool FileInRam;
extern  QVector <WorkWithJson::Workers> TableData;
extern  QVector <WorkWithJson::Workers> FileOriginData;
}
QT_END_NAMESPACE
class WorkWithTable
{
public:
    WorkWithTable();
    ~WorkWithTable();

    void LoadFileOriginData(Ui::MainWindow * ui);

    void FileOpen(Ui::MainWindow * ui);

    void DefaultVeiw(Ui::MainWindow * ui,TableViewModel* _tModel);

    void FileOriginDataSaver(Ui::MainWindow * ui);

    bool FileSave(Ui::MainWindow * ui);

    void TableRefresh(Ui::MainWindow *ui, TableViewModel *_tModel);
};

#endif // WORKWITHTABLE_H
