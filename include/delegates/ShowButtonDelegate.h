#ifndef SHOWBUTTONDELEGATE_H
#define SHOWBUTTONDELEGATE_H

#include <QStyledItemDelegate>

class ShowButtonDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit ShowButtonDelegate(QObject *parent = nullptr);
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    bool editorEvent(QEvent *event, QAbstractItemModel *model,
                                          const QStyleOptionViewItem &option, const QModelIndex &index) override;
signals:
    void showBtnClicked(const QModelIndex &index) const;
};

#endif // SHOWBUTTONDELEGATE_H
