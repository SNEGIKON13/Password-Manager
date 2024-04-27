#ifndef EDITEXISTENTRYWIDGET_H
#define EDITEXISTENTRYWIDGET_H

#include <QDialog>
#include <QString>
#include <QMessageBox>

#include "EnumWidgets.h"
#include "NodeData.h"
#include "databasecontroller.h"

namespace Ui {
class EditExistEntryWidget;
}

class EditExistEntryWidget : public QDialog
{
    Q_OBJECT

public:
    explicit EditExistEntryWidget(DataBaseController *dbc, QWidget *parent = nullptr);
    ~EditExistEntryWidget();

signals:
    // void transmitChangeToMainWindow(int index);

private slots:
    // void on_buttonBox_rejected();
    // void on_buttonBox_accepted();
    // void clearAll();
    void toFillFields();

private:
    Ui::EditExistEntryWidget *ui;
    QString noteName;
    QString userName;
    QString url;
    QString passwordEntry;
    QString otherNotes;
    DataBaseController *dbc;
    NoteData nd;
};

#endif // EDITEXISTENTRYWIDGET_H
