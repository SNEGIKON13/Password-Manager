#ifndef WELCOMEWIDGET_H
#define WELCOMEWIDGET_H

#include <QWidget>

#include "EnumWidgets.h"

namespace Ui {
class WelcomeWidget;
}

class WelcomeWidget : public QWidget
{
    Q_OBJECT

public:
    explicit WelcomeWidget(QWidget *parent = nullptr);
    ~WelcomeWidget();

signals:
    void trasmitUnlockBase(int index);
    void trasmitCreateBase(int index);

private slots:

    void on_openExistBaseButton_clicked();

    void on_createBaseButton_clicked();

private:
    Ui::WelcomeWidget *ui;
};

#endif // WELCOMEWIDGET_H
