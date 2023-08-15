#ifndef MYTABLEWIDGET_H
#define MYTABLEWIDGET_H

#include <QTableWidgetItem>
#include <QMouseEvent>
#include "pakdef.h"

class MyTableWidgetItem : public QTableWidgetItem
{
public:
    explicit MyTableWidgetItem();
    int userId;
    int timestamp;
    char pathBuf[_MAX_SIZE];
    char fileName[50];   //文件名字（这里直接根据路径获取）
    int pause;
public:
    void setInfo(FileInfo* fileInfo);

signals:

public slots:
};

#endif // MYTABLEWIDGET_H
