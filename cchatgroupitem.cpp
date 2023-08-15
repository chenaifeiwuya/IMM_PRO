#include "cchatgroupitem.h"
#include "ui_cchatgroupitem.h"


CChatGroupItem::CChatGroupItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CChatGroupItem)
{
    ui->setupUi(this);
    this->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
}

CChatGroupItem::~CChatGroupItem()
{
    delete ui;
}

void CChatGroupItem::updateGroupInfo(QString name, int groupId, int iconId)
{
    //为群聊添加信息
    ui->lb_groupId->setText(QString(groupId));
    ui->lb_name->setText(name);
    groupChat.groupId = groupId;
    groupChat.setWindowTitle(name+"群组");
    this->groupId = groupId;
    groupName = QString(name);
}

void CChatGroupItem::mouseDoubleClickEvent(QMouseEvent *event)
{
    groupChat.showNormal();
}
