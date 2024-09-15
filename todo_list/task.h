#ifndef TASK_H
#define TASK_H
#include "QString"
#include "QDate"
class Task
{
public:
    Task(QString cname, QString cdescript, QDate cdeadline, bool cComplete);
    ~Task();
    QString name;
    QString descript;
    QDate deadline;
    bool complete;
};

#endif // TASK_H
