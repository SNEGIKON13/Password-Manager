#ifndef ADDNEWENTRYWIDGET_H
#define ADDNEWENTRYWIDGET_H

#include <QDialog>
#include <QString>
#include <QMessageBox>

#include "EnumWidgets.h"
#include "NodeData.h"
#include "dbmanagement/databasenotescreator.h"

namespace Ui {
class AddNewEntryWidget;
}

class AddNewEntryWidget : public QDialog
{
    Q_OBJECT

public:
    AddNewEntryWidget(DatabaseNotesCreator *databaseNotesCreator, QWidget *parent = nullptr);
    ~AddNewEntryWidget();

public slots:
    void populateGroupComboBox();

signals:
    void transmitChangeToMainWindow(int index);

private slots:
    void on_buttonBox_rejected();
    void on_buttonBox_accepted();
    void on_chooseGroup_currentIndexChanged(int index);
    void clearUiText();
    void clearStruct();
    void clearAll();

private:
    Ui::AddNewEntryWidget *ui;
    QString noteName;
    QString userName;
    QString url;
    QString passwordEntry;
    QString otherNotes;
    DatabaseNotesCreator *databaseNotesCreator;
    NoteData nd;

};

#endif // ADDNEWENTRYWIDGET_H
