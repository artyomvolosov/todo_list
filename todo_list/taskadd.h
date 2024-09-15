#ifndef TASKADD_H
#define TASKADD_H

#include <QDialog>
#include <QDate>
#include "task.h"
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>


namespace Ui {
class taskAdd;
}

class taskAdd : public QDialog
{
    Q_OBJECT

public:
    explicit taskAdd(QWidget *parent = nullptr);
    ~taskAdd();
    void getData();
signals:
    void toRefresh();
private slots:
    void on_okButton_clicked();

private:
    Ui::taskAdd *ui;
    QString name;
    QDate date;
    QString text;
    bool complete ;
    Task create();
    void db1();
};

#endif // TASKADD_H
