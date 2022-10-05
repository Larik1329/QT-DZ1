#ifndef DELEGATEBUTTON_H
#define DELEGATEBUTTON_H


#include "qobject.h"
#include "qpainter.h"
#include "qstyleoption.h"

#include <QItemDelegate>
class DelegateButton : public QItemDelegate
{
    Q_OBJECT

public:
    DelegateButton(QObject *parent = 0);
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index);
};

#endif // DELEGATEBUTTON_H
