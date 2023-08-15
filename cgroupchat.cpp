#include "cgroupchat.h"
#include "ui_cgroupchat.h"

CGroupChat::CGroupChat(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CGroupChat)
{
    ui->setupUi(this);
}

CGroupChat::~CGroupChat()
{
    delete ui;
}


void CGroupChat::dealGroupChatInfo(QString text, QString userName)
{
    //显示到浏览器窗口上，格式【ip】时间...
    ui->tb_chathistory->append(QString("【%1】 %2").arg(userName).arg(QTime::currentTime().toString("hh:mm:ss")));  //append()在text edit的最后添加一个新的段落。
    ui->tb_chathistory->append(text);   //insertPlainText()
}

//发送群聊消息的按钮
void CGroupChat::on_pb_send_clicked()
{
    QString text=ui->te_enter->toPlainText();
    ui->te_enter->setText("");
    //判断是否为空
    QString textCopy(text);
    if(textCopy.remove(" ").size() == 0)
    {
        return;
    }
    //发信号通知kernel类
    Q_EMIT SIG_sendGroupChatInfo(text,groupId);

    //将消息设置到聊天窗口上
    dealGroupChatInfo(text,"我");
}
