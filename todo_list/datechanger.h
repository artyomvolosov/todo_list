#ifndef DATECHANGER_H
#define DATECHANGER_H

#include <QDialog>

namespace Ui {
class dateChanger;
}

class dateChanger : public QDialog
{
    Q_OBJECT

public:
    explicit dateChanger(QWidget *parent = nullptr);
    ~dateChanger();
signals:
    void toRefresh();
private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::dateChanger *ui;
};

#endif // DATECHANGER_H
