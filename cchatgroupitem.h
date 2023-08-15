#ifndef CCHATGROUPITEM_H
#define CCHATGROUPITEM_H
#include "cgroupchat.h"
#include <QWidget>
#include <QMouseEvent>

namespace Ui {
class CChatGroupItem;
}

class CChatGroupItem : public QWidget
{
    Q_OBJECT

public:
    explicit CChatGroupItem(QWidget *parent = 0);
    ~CChatGroupItem();
    void updateGroupInfo(QString name, int groupId,int iconId);
    void mouseDoubleClickEvent(QMouseEvent* event) override;

private:
    Ui::CChatGroupItem *ui;

public:
    CGroupChat groupChat;
    int groupId;
    QString groupName;
};

#endif // CCHATGROUPITEM_H
