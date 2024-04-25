#include "createbasewidget.h"
#include "ui_createbasewidget.h"

CreateBaseWidget::CreateBaseWidget(DataBaseController *dbc, QWidget* parent)
    : QDialog(parent), ui(new Ui::CreateBaseWidget), dbc(dbc)
{
    ui->setupUi(this);
}

CreateBaseWidget::~CreateBaseWidget()
{
    delete ui;
}

void CreateBaseWidget::clear_all()
{
    baseName.clear();
    basePassword.clear();
    ui->baseName->clear();
    ui->basePassword->clear();
}

void CreateBaseWidget::on_buttonBox_accepted()
{
    baseName = ui->baseName->text();
    basePassword = ui->basePassword->text();
    if (!baseName.isEmpty() && !basePassword.isEmpty()) {
        QString filePath = QFileDialog::getSaveFileName(this, "Сохранить базу данных",
            QDir::homePath() + QDir::separator() + baseName, "База данных (*.db)");
        if (!filePath.isEmpty()) {
            dbc->createDatabase(filePath);
        } else {
            QMessageBox::warning(this, "Ошибка", "Ошибка при открытии базы данных");
        }
        clear_all();
        close();
    }
}

void CreateBaseWidget::on_buttonBox_rejected()
{
    clear_all();
}
