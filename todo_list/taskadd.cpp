#include "taskadd.h"
#include "ui_taskadd.h"
#include "mainwindow.h"
#include <QDate>
#include <qsqlquery.h>
#include <qsqlerror.h>

taskAdd::taskAdd(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::taskAdd)
{
    ui->setupUi(this);
    ui->deadline->setDate(QDate::currentDate());
    emit(toRefresh());

}

taskAdd::~taskAdd()
{
    delete ui;
}

void taskAdd::on_okButton_clicked(){

    QSqlQuery query(MainWindow::db);

    query.prepare("INSERT INTO task(name, descript, date, complete) VALUES(:name, :text, :date, :complete)");
    query.bindValue(":name", ui->nameLine->text());
    query.bindValue(":text", ui->descriptionTask->toPlainText());

    QDateTime dateTime = QDateTime::currentDateTime();

    query.bindValue(":date", ui->deadline->date());
    query.bindValue(":complete", ui->checkBox->isChecked());

    qDebug() << "Запрос " << query.lastQuery();
    qDebug() << "name " << ui->nameLine->text();
    qDebug() << "text " << ui->descriptionTask->toPlainText();
    qDebug() << "date " << ui->deadline->date();
    qDebug() << "complete " << ui->checkBox->isChecked();

    if (query.exec()) {
        qDebug() << "запись добавлена";
    } else {
        qDebug() << "ошибка записи " << query.lastError().text();
    }
    emit(toRefresh());
    taskAdd::close();

}

