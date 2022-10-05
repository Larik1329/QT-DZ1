#ifndef TABLEVIEWMODEL_H
#define TABLEVIEWMODEL_H
#include "qevent.h"
#include <QAbstractItemModel>

class TableViewModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    TableViewModel(int nCol, QObject *parent=Q_NULLPTR);
    ~TableViewModel();      

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;

    QModelIndex parent(const QModelIndex &index) const;

    int columnCount(const QModelIndex &parent = QModelIndex()) const;

    int rowCount(const QModelIndex &parent = QModelIndex()) const;

    void append(const QList<QString>& data);

    void reset();

    QString getData(int row, int col);

private:
    int _nCol;

    QVector <QList<QString>> _vItems;
};

#endif // TABLEVIEWMODEL_H
