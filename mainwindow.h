#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "workwithtable.h"

#include <QMainWindow>
#include <QSignalMapper>
#include <tableviewmodel.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow;     }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT




public:
    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();



    void CreateRowBut();
    void ButtonsInTableAdd(int rowLenght);
signals:
    //void mapped(int i);

private slots:
    void on_OpenFileButton_clicked();

    void on_CreateFileButton_clicked();

    void on_CancelChangesButton_clicked();

    void on_SaveButton_clicked();

    //void map();

    void EditSlot(int i);
    void DeleteSlot(int i);
protected:
    void closeEvent(QCloseEvent *event) override;

private:
    void initModel();

private:
    QSignalMapper *signalMapper;

    QSignalMapper *signalMapper2;

    Ui::MainWindow *ui;

    TableViewModel* _tModel;

    WorkWithTable* workwithtable;
};
#endif // MAINWINDOW_H
