#ifndef ICD_H
#define ICD_H

#include <QString>

struct Question{
    QString desc;//问题描述
    QString a;
    QString b;
    QString c;
    QString d;
    QString answer;
    QString explain;

    bool isEmpty(){
        return (desc.isEmpty() && a.isEmpty() && b.isEmpty()
                && c.isEmpty() && d.isEmpty() && answer.isEmpty()
                && explain.isEmpty());
    }
};

#endif // ICD_H
