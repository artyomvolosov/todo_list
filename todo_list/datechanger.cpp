#include "datechanger.h"
#include "ui_datechanger.h"
#include <QtSql/QSqlError>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QSqlRecord>
#include "mainwindow.h"

dateChanger::dateChanger(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::dateChanger)
{
    ui->setupUi(this);
    ui->dateEdit->setDate(QDate::currentDate());
}

dateChanger::~dateChanger()
{
    delete ui;
}

void dateChanger::on_buttonBox_accepted()
{
    QSqlQuery changeDate(MainWindow::db);
    changeDate.prepare("UPDATE task SET date = :date WHERE selected = 1;");
    changeDate.bindValue(":date", ui->dateEdit->date());
    if (changeDate.exec()) {
        qDebug() << "запись добавлена";
    } else {
        qDebug() << "ошибка записи " << changeDate.lastError().text();
    }
    emit(toRefresh());
    dateChanger::close();
}


void dateChanger::on_buttonBox_rejected()
{
    dateChanger::close();
}

