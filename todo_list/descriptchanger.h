#ifndef DESCRIPTCHANGER_H
#define DESCRIPTCHANGER_H

#include <QDialog>

namespace Ui {
class DescriptChanger;
}

class DescriptChanger : public QDialog
{
    Q_OBJECT

public:
    explicit DescriptChanger(QWidget *parent = nullptr);
    ~DescriptChanger();
signals:
    void toRefresh();
private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::DescriptChanger *ui;
};

#endif // DESCRIPTCHANGER_H
