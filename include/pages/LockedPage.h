#ifndef LOCKEDPAGE_H
#define LOCKEDPAGE_H

#include <QWidget>

namespace Ui {
class LockedPage;
}

class LockedPage : public QWidget
{
    Q_OBJECT

public:
    explicit LockedPage(QWidget *parent = nullptr);
    ~LockedPage();

private:
    Ui::LockedPage *ui;
};

#endif // LOCKEDPAGE_H
