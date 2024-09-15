#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QtSql/QSqlError>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QSqlRecord>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    taskAddWindow = new taskAdd();
    descriptChangerWindow = new DescriptChanger();
    dateChangerWindow = new dateChanger();
    dbConnect();
    refresh();
    connect(taskAddWindow,SIGNAL(toRefresh()), this, SLOT(refresh()));
    connect(descriptChangerWindow,SIGNAL(toRefresh()), this, SLOT(refresh()));
    connect(dateChangerWindow,SIGNAL(toRefresh()), this, SLOT(refresh()));
}

MainWindow::~MainWindow()
{
    delete ui;
    db.close();
}


QSqlDatabase MainWindow::db;

void MainWindow::on_addButton_clicked()
{
    taskAddWindow->show();
}

void MainWindow::dbConnect()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("tasks.db");

    if (db.open()) {
        qDebug() << "Подключение к бд успешно";
    } else {
        qDebug() << "Ошибка подключения к бд: " << db.lastError().text();
    }
}
void MainWindow::refresh() {
    ui->taskTable->setRowCount(0);
    QSqlQuery queryGet(db);
    queryGet.prepare("select * from task");

    if (queryGet.exec()) {
        int columns = queryGet.record().count();
        int rows = 0;

        while (queryGet.next()) {
            ui->taskTable->insertRow(rows);

            for (int i = 0; i < columns; ++i) {
                QTableWidgetItem *item = new QTableWidgetItem();
                item->setText(queryGet.value(i).toString());
                ui->taskTable->setItem(rows, i, item);
            }
            QTableWidgetItem *checkboxItem = new QTableWidgetItem();
            checkboxItem->setFlags(checkboxItem->flags() | Qt::ItemIsUserCheckable);
            checkboxItem->setCheckState(queryGet.value("selected").toBool() ? Qt::Checked : Qt::Unchecked);
            ui->taskTable->setItem(rows, 4, checkboxItem);

            rows++;
            qDebug() << "строка " + std::to_string(rows) + " добавлена";
        }
        connect(ui->taskTable, &QTableWidget::itemChanged, this, &MainWindow::onItemChanged);
        qDebug() << "обновление завершено";
    } else {
        qDebug() << "Ошибка: " << queryGet.lastError().text();
    }
}
void MainWindow::onItemChanged(QTableWidgetItem *item) {
    if (item->column() == 4) {
        int row = item->row();
        bool isChecked = (item->checkState() == Qt::Checked);


        QString taskName = ui->taskTable->item(row, 0)->text();

        QSqlQuery queryUpdate(db);
        queryUpdate.prepare("UPDATE task SET selected = :selected WHERE name = :name");
        queryUpdate.bindValue(":selected", isChecked);
        queryUpdate.bindValue(":name", taskName);

        if (!queryUpdate.exec()) {
            qDebug() << "Ошибка: " << queryUpdate.lastError().text();
        }
    }
}

void MainWindow::on_deleteButton_clicked()
{
    QSqlQuery deleteQuery(db);
    deleteQuery.prepare("DELETE FROM task WHERE selected = 1;");
    if(deleteQuery.exec()){
        qDebug()<<"Удаление строки успешно";
    }
    else{
        qDebug()<<"Ошибка удаления строки " << deleteQuery.lastError().text();;
    }
    refresh();
}


void MainWindow::on_descriptionButton_clicked()
{
    descriptChangerWindow->show();
}


void MainWindow::on_changeComplete_clicked()
{
    QSqlQuery complete (db);
    complete.prepare("UPDATE task SET complete = 1 WHERE selected = 1;");
    if (complete.exec()) {
        qDebug() << "задача выполнена";
    } else {
        qDebug() << "ошибка " << complete.lastError().text();
    }
    refresh();
}


void MainWindow::on_changeDate_clicked()
{
    dateChangerWindow->show();
}


void MainWindow::on_dateSort_clicked()
{
    ui->taskTable->sortItems(2);
}


void MainWindow::on_nameSort_clicked()
{
    ui->taskTable->sortItems(0);
}


void MainWindow::on_completeSort_clicked()
{
    ui->taskTable->sortItems(3);
}


void MainWindow::on_descriptSort_clicked()
{
    ui->taskTable->sortItems(1);
}


void MainWindow::on_resetSort_clicked()
{
    refresh();
}

