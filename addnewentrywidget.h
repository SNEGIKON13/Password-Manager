#ifndef ADDNEWENTRYWIDGET_H
#define ADDNEWENTRYWIDGET_H

#include <QDialog>

namespace Ui {
class AddNewEntryWidget;
}

class AddNewEntryWidget : public QDialog
{
    Q_OBJECT

public:
    explicit AddNewEntryWidget(QWidget *parent = nullptr);
    ~AddNewEntryWidget();

private:
    Ui::AddNewEntryWidget *ui;
};

#endif // ADDNEWENTRYWIDGET_H
