#include "descriptchanger.h"
#include "ui_descriptchanger.h"
#include <QtSql/QSqlError>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QSqlRecord>
#include "mainwindow.h"

DescriptChanger::DescriptChanger(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DescriptChanger)
{
    ui->setupUi(this);
}

DescriptChanger::~DescriptChanger()
{
    delete ui;
}

void DescriptChanger::on_buttonBox_accepted()
{

    QSqlQuery changeDescription(MainWindow::db);
    changeDescription.prepare("UPDATE task SET descript = :text WHERE selected = 1;");
    changeDescription.bindValue(":text", ui->textEdit->toPlainText());
    if (changeDescription.exec()) {
        qDebug() << "запись добавлена";
    } else {
        qDebug() << "ошибка записи " << changeDescription.lastError().text();
    }
    emit(toRefresh());
    DescriptChanger::close();
}


void DescriptChanger::on_buttonBox_rejected()
{
    DescriptChanger::close();
}

