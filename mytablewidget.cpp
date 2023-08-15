#include "mytablewidget.h"

MyTableWidgetItem::MyTableWidgetItem()
{

}

void MyTableWidgetItem::setInfo(FileInfo *fileInfo)
{
    /*
     *
    int userId;
    int timestamp;
    char pathBuf[_MAX_SIZE];
    char fileName[50];   //文件名字（这里直接根据路径获取）
    *
    */
    userId = fileInfo->userId;
    timestamp = fileInfo->timestamp;
    pause=fileInfo->pause;

}
