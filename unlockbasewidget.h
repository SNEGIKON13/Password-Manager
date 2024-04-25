#ifndef UNLOCKBASEWIDGET_H
#define UNLOCKBASEWIDGET_H

#include <QDialog>
#include <QMessageBox>

#include "databasecontroller.h"
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

public slots:
    void receiveFilePath(const QString& filePath);

signals:
    void transmitChangeToMainWindow(int index);
    void transmitDataBasePath(QString filePath);

private slots:
    void on_unlockBaseButton_clicked();
    void clear_all();

private:
    Ui::UnlockBaseWindow *ui;
    QString filePath, passwordEntry;
};

#endif // UNLOCKBASEWIDGET_H
