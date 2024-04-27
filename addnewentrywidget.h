#ifndef ADDNEWENTRYWIDGET_H
#define ADDNEWENTRYWIDGET_H

#include <QDialog>
#include <QString>
#include <QMessageBox>

#include "EnumWidgets.h"
#include "NodeData.h"
#include "databasecontroller.h"

namespace Ui {
class AddNewEntryWidget;
}

class AddNewEntryWidget : public QDialog
{
    Q_OBJECT

public:
    AddNewEntryWidget(DataBaseController *dbc, QWidget *parent = nullptr);
    ~AddNewEntryWidget();

signals:
    void transmitChangeToMainWindow(int index);

private slots:
    void on_buttonBox_rejected();
    void on_buttonBox_accepted();
    void clearAll();

    void on_chooseGroup_currentIndexChanged(int index);

private:
    Ui::AddNewEntryWidget *ui;
    QString noteName;
    QString userName;
    QString url;
    QString passwordEntry;
    QString otherNotes;
    DataBaseController *dbc;
    NoteData nd;

};

#endif // ADDNEWENTRYWIDGET_H
