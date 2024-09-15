#include "task.h"

Task::Task(QString cname, QString cdescript, QDate cdeadline, bool cComplete) {
    this->name = cname;
    this->complete = cComplete;
    this->deadline = cdeadline;
    this->descript = cdescript;
}
