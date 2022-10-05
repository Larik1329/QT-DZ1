#include "tableviewmodel.h"
#include "delegatebutton.h"

TableViewModel::TableViewModel(int nCol, QObject *parent)
    :_nCol(nCol), QAbstractItemModel(parent)
{

}

TableViewModel::~TableViewModel()
{

}

//void dataChanged(const QModelIndex &topLeft, const QModelIndex & bottomRight, const QVector<int> & roles)
//{
//    QPushButton *pPushButton = qobject_cast<QPushButton*>(indexWidget(topLeft));
//    if (pPushButton)
//        pPushButton->setText(model()->data(topLeft, Qt::DisplayRole).toString());
//    else
//        QTableView::dataChanged(topLeft, bottomRight, roles);
//}

QVariant TableViewModel::data(const QModelIndex &index, int role) const
{
    if (index.isValid() == false) return QVariant();
    if (role == Qt::DisplayRole) {
        if (_vItems.count()==0) return QVariant();

        const QList<QString> & vItem = _vItems[index.row()];

        switch (index.column()) {
        case 0: return vItem[0];
        case 1: return vItem[1];
        case 2: return vItem[2];
        case 3: return vItem[3];
        case 4: return vItem[4];
        case 5: return vItem[5];
        case 6: return vItem[6];
        }
    }
    return QVariant();
}

QModelIndex TableViewModel::index(int row, int column, const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    int rowMax = _vItems.count();
    if (row < rowMax && row >=0 && column < _nCol && column >=0) {
        return createIndex(row, column);
    }
    return QModelIndex();
}

QModelIndex TableViewModel::parent(const QModelIndex &index) const
{
    Q_UNUSED(index);
    return QModelIndex();
}

QVariant TableViewModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role==Qt::DisplayRole) {
        if(orientation==Qt::Horizontal){
            switch (section) {
            case 0: return "Номер";
            case 1: return "ФИО";
            case 2: return "специальность";
            case 3: return "ЗП";
            case 4: return "пол";
            case 5: return "Изменить строку";
            case 6: return "Удалить строку";
            default: return QAbstractItemModel::headerData(section, orientation, role);
            }
        }
    }
    return QAbstractItemModel::headerData(section, orientation, role);
}

int TableViewModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return _nCol;
}

int TableViewModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return _vItems.count();
}

void TableViewModel::append(const QList<QString>& data)
{
    _vItems.append(data);
}

void TableViewModel::reset()
{
    QAbstractItemModel::beginResetModel();
    QAbstractItemModel::endResetModel();
}

QString TableViewModel::getData(int row, int col)
{
    return _vItems[row][col];
}
