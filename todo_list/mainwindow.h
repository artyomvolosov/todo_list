#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "taskadd.h"
#include <QTableWidget>
#include "descriptchanger.h"
#include "datechanger.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    taskAdd* taskAddWindow;
    DescriptChanger* descriptChangerWindow;
    dateChanger* dateChangerWindow;
    void dbConnect();
    static QSqlDatabase db;



private slots:
    void on_addButton_clicked();
    void refresh();
    void onItemChanged(QTableWidgetItem *item);
    void on_deleteButton_clicked();
    void on_descriptionButton_clicked();

    void on_changeComplete_clicked();

    void on_changeDate_clicked();

    void on_dateSort_clicked();

    void on_nameSort_clicked();

    void on_completeSort_clicked();

    void on_descriptSort_clicked();

    void on_resetSort_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
