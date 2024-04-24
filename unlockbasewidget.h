#ifndef UNLOCKBASEWIDGET_H
#define UNLOCKBASEWIDGET_H

#include <QDialog>
#include <QMessageBox>

#include "EnumWidgets.h"

namespace Ui {
class UnlockBaseWindow;
}

class UnlockBaseWindow : public QDialog
{
    Q_OBJECT

public:
    explicit UnlockBaseWindow(QWidget *parent = nullptr);
    ~UnlockBaseWindow();

signals:
    void transmitMainWindow(int index);

private slots:
    void on_unlockBaseButton_clicked();

private:
    Ui::UnlockBaseWindow *ui;
};

#endif // UNLOCKBASEWIDGET_H
