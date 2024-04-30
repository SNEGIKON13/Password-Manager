#ifndef EDITEXISTENTRYWIDGET_H
#define EDITEXISTENTRYWIDGET_H

#include <QDialog>
#include <QString>
#include <QMessageBox>
#include <QTableWidgetItem>

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
    void setNoteName(const QString &noteName, const QString &groupName);
    void populateGroupComboBox();
    void toFillFields();

signals:
    void transmitChangeToMainWindow(int index);

private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();
    void clearAllExceptId();

private:
    Ui::EditExistEntryWidget *ui;
    QString noteName;
    QString groupName;
    QString userName;
    QString url;
    QString passwordEntry;
    QString otherNotes;
    DataBaseController *dbc;
    NoteData nd;
    QTableWidgetItem *selectedNote;
};

#endif // EDITEXISTENTRYWIDGET_H
