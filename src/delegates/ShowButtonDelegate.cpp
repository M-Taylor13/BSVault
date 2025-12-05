#include "ShowButtonDelegate.h"
#include <QApplication>
#include <qevent.h>

ShowButtonDelegate::ShowButtonDelegate(QObject *parent)
    : QStyledItemDelegate(parent) {}

void ShowButtonDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {
    QStyleOptionButton button;
    button.rect = option.rect;
    button.text = "show";
    button.state = QStyle::State_Enabled;
    button.features = QStyleOptionButton::Flat;
    QApplication::style()->drawControl(QStyle::CE_PushButton, &button, painter);
}
bool ShowButtonDelegate::editorEvent(QEvent *event, QAbstractItemModel *model,
                 const QStyleOptionViewItem &option, const QModelIndex &index) {
    QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
    if (option.rect.contains(mouseEvent->pos())) {
        if (event->type() == QEvent::MouseButtonRelease) {
          emit showBtnClicked(index);
        }
        return true;
    }
    return false;

}

