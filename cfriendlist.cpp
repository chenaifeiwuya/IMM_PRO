#include "cfriendlist.h"
#include "ui_cfriendlist.h"
#include <QLabel>
#include <QDebug>
CFriendList::CFriendList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CFriendList)
{
    OnlineNum=0;
    OfflineNum=0;

    ui->setupUi(this);
    //给层new对象
       m_layoutOnline = new QVBoxLayout;
       m_layoutOffline = new QVBoxLayout;
       //设置小控件距离大控件上下左右的间距
       m_layoutOnline->setContentsMargins(0, 0, 0, 0);
       m_layoutOffline->setContentsMargins(0, 0, 0, 0);

       //将布局设置到窗口上
       ui->wdg_online->setLayout(m_layoutOnline);
       ui->wdg_offline->setLayout(m_layoutOffline);

       //添加菜单项，指定父控件，父控件负责子控件的回收
       m_menu = new QMenu(this);
       m_menu->addAction("添加好友");
       m_menu->addAction("添加群组");
       m_menu->addAction("创建群聊");
       //绑定菜单项的点击信号和槽函数
       connect(m_menu,SIGNAL(triggered(QAction*)),   //menu的固定信号，就是点击了哪个菜单项
               this,SLOT(slot_dealMenu(QAction*)));



}

CFriendList::~CFriendList()
{
    delete ui;
    //回收每个好友窗口
    for(auto ite=mapItToFriendItem.begin();ite!=mapItToFriendItem.end();)
    {
        CFriendItem* item=*ite;
        item->hide();
        delete item;
        ite=mapItToFriendItem.erase(ite);
    }
    delete m_layoutOnline;
    delete m_layoutOffline;
}


//更新好友信息
void CFriendList::slot_updataFriendinfo(int id, QString name, int iconid, QString feeling, int status)
{
    //首先判断该好友信息是否已存在
    if(mapItToFriendItem.count(id)>0)
    {
        //如果已存在，则只更新状态
        CFriendItem* item=mapItToFriendItem[id];
        //查看其原状态
        if(item->status == STATUS_ONLINE)
        {
            OnlineNum--;
        }
        else
        {
            OfflineNum--;
        }
        item->updataStatus(status);

        //并且将其从原窗口转移到新窗口中
        item->setParent(NULL);   //将其父窗口设为空即从原窗口移除了（移除不是删除）

        if(status == STATUS_ONLINE)
        {
            //添加到在线窗口
            m_layoutOnline->addWidget(item);
            OnlineNum++;
            ui->sca_inOnline->setMinimumHeight(OnlineNum * (item->height()) + 20);
            ui->sca_inOffline->setMinimumHeight(OfflineNum * (item->height()) + 20);
        }
        else
        {
            //添加到离线窗口
            m_layoutOffline->addWidget(item);
            OfflineNum++;
            qDebug()<<item->sizeHint().height();
            ui->sca_inOnline->setMinimumHeight(OnlineNum * (item->height()) + 20);   //改变scrollArea内部窗口的大小，以适用所有好友窗口
            ui->sca_inOffline->setMinimumHeight(OfflineNum * (item->height()) + 20);
        }

    }
    else   //否则创建新的好友对象，并添加到map中保存
    {

        CFriendItem* item=new CFriendItem(this);

        //绑定信号和槽函数
        QObject::connect(&(item->dialog),SIGNAL(SIG_sendChatMessage(int,QString)), \
                         this,SLOT(slot_sendChatMessage(int ,QString )));
        QObject::connect(&(item->dialog),SIGNAL(SIG_sendFile(int,QString)), \
                         this,SLOT(slot_sendFile(int ,QString )));
        QObject::connect(&(item->dialog),SIGNAL(SIG_sendFileBlockRq(int,int)), \
                         this,SLOT(slot_sendFileBlockRq(int,int)));

        item->updateInfo(status,id,name,iconid,feeling);
        //item->setVisible(true);
           // item->show();
        //如果是在线状态，就添加到在线窗口，否则添加到离线窗口
        if(status == STATUS_ONLINE)
        {

            m_layoutOnline->addWidget(item);
            OnlineNum++;
        }
        else
        {
            m_layoutOffline->addWidget(item);
            OfflineNum++;
        }
        mapItToFriendItem[id]=item;
        ui->sca_inOnline->setMinimumHeight(OnlineNum * (item->height()) + 20); //改变scrollArea内部窗口的大小，以适用所有好友窗口
        ui->sca_inOffline->setMinimumHeight(OfflineNum * (item->height()) + 20);

    }
}

//更新自己的信息
void CFriendList::slot_updataUserInfo(QString name, QString feeling)
{
    ui->lb_name->setText(name);
    ui->lb_signed->setText(feeling);
    QImage image = QImage(":/tx/0.png");
    ui->lb_icon->setPixmap(QPixmap::fromImage(image));
}


//重写退出事件
void CFriendList::closeEvent(QCloseEvent *event)
{

    //弹出一个窗口询问用户是否关闭
    if(QMessageBox::Yes == QMessageBox::information(this,"提示","是否确认退出？",QMessageBox::Yes | QMessageBox::No))
    {
        //确认退出，发送信号通知kernel，开始回收资源执行退出函数
        Q_EMIT SIG_exit();
    }
    else
    {
        //否则忽视掉这个事件
        event->ignore();
        //关于事件，还需要仔细学习
    }
}

void CFriendList::dealChatRq(int id, QString text)
{
    if(mapItToFriendItem.count(id) > 0)
    {
        //如果存在这个好友
        mapItToFriendItem[id]->dialog.dealChatRq(text);
        //并显示这个聊天窗口
        mapItToFriendItem[id]->dialog.showNormal();
    }
}

void CFriendList::updateProcess(int friendId,FileInfo *fileInfo)
{
    //更新进度条
    if(mapItToFriendItem.count(friendId)>0)
    {
        mapItToFriendItem[friendId]->dialog.updateProcess(fileInfo);
    }
}

//添加群聊到好友列表
void CFriendList::addChatGroup(QString groupName, int groupId)
{
    if(mapIdtoChatGroupItem.count(groupId) == 0)
    {
        CChatGroupItem* item = new CChatGroupItem;
        connect(&(item->groupChat),SIGNAL(SIG_sendGroupChatInfo(QString,int)),this,SLOT(slot_sendGroupChatInfo(QString,int)));
        //设置群聊的信息
        item->updateGroupInfo(groupName,groupId,0);
        //将群聊窗口添加到map中
        mapIdtoChatGroupItem[groupId] = item;
        //然后将群聊添加到列表中
        m_layoutOnline->addWidget(item);
        OnlineNum++;
        ui->sca_inOnline->setMinimumHeight(OnlineNum * (item->height()) + 20);
    }
}

void CFriendList::dealGroupChatInfo(int groupId, QString text, QString userName)
{
    //通过groupId判断当前用户是否存在该群聊
    if(mapIdtoChatGroupItem.count(groupId) > 0)
    {
        //如果存在，将消息显示在窗口上
        //但是不将窗口弹出，只显示，因为群聊消息一般会很多，频繁弹出窗口会很影响使用体验
        mapIdtoChatGroupItem[groupId]->groupChat.dealGroupChatInfo(text,userName);
    }
}

void CFriendList::slot_sendChatMessage(int id, QString text)
{
    Q_EMIT SIG_sendChatMessage( id,text);
}

void CFriendList::slot_sendFile(int id, QString path)
{
    Q_EMIT SIG_sendFile(id,path);
}

//插入文件文件传输信息
void CFriendList::slot_insertFileRows(int friendId, FileInfo *fileInfo)
{





    //根据friendId找到聊天窗口
    if(mapItToFriendItem.count(friendId) > 0)
    {
        //调用聊天窗口的函数
        CFriendItem* item=mapItToFriendItem[friendId];
        item->dialog.insertFileRows(fileInfo);
    }
}

void CFriendList::slot_sendFileBlockRq(int friendId, int timestamp)
{
    Q_EMIT SIG_sendFileBlockRq(friendId,timestamp);
}

void CFriendList::slot_sendGroupChatInfo(QString text, int groupId)
{
    Q_EMIT SIG_sendGroupChatInfo(text,groupId);
}


void CFriendList::on_pb_addFriend_clicked()
{

    //1:获取鼠标的点击位置
    QPoint p = QCursor::pos();
    //2:计算菜单栏的绝对高度--》所有菜单项添加完以后的高度
    QSize size = m_menu->sizeHint();  //获得菜单项的绝对高度以及宽度

    //3:在点击位置向上显示一个菜单栏
    m_menu->exec(QPoint(p.x() -size.width() ,p.y() /*- size.height()*/));

    /*


    */
}

void CFriendList::slot_dealMenu(QAction *action)
{
    if("添加好友" == action->text())
    {
        //处理添加好友，给kernel发信号
        //弹出窗口让用户输入对方昵称进行添加
        QString name=QInputDialog::getText(this,"添加好友","请输入好友昵称");
        //判断是否为空
        QString copyName(name);
        if(copyName.remove(" ") == "")
        {
            QMessageBox::information(this,"提示","昵称不能为空！");
            return;
        }

        //判断该name是否已经在好友列表里面
        for(auto ite: mapItToFriendItem)
        {
            if(ite->name == name)
            {
                //如果当前添加好友已经在好友列表里面，则弹出消息框提示对方已经是用户的好友
                QMessageBox::information(this,"提示","请勿重复添加好友");
                return;
            }
        }
        //发送信号通知kernel让其发送添加好友请求
        Q_EMIT SIG_addFriend(name);
    }else if("添加群组" == action->text()){
        //添加群组
        //弹出窗口让用户输入对方昵称进行添加
        QString tel=QInputDialog::getText(this,"添加群组","请输入群组号");
        //判断是否为空
        QString copyTel(tel);
        if(copyTel.remove(" ") == "")
        {
            QMessageBox::information(this,"提示","群组号不能为空！");
            return;
        }

        //判断该群组号是否已经在列表里面
        for(auto ite: mapIdtoChatGroupItem)
        {
            if(ite->groupId == atoi(tel.toStdString().c_str()))
            {
                QMessageBox::information(this,"提示","您已经添加此群组了!",QMessageBox::Ok);
                return;
            }
        }
        //发送信号通知kernel让其发送添加群组请求
        Q_EMIT SIG_addGroupChat(tel);
    }
    else if("创建群聊" == action->text())   //创建群聊
    {
        //弹出消息框，让用户输入群聊名称
        QString name=QInputDialog::getText(this,"创建群聊","请输入群聊名称");
        //判断是否为空
        QString copyName(name);
        if(copyName.remove(" ") == "")
        {
            QMessageBox::information(this,"提示","昵称不能为空！");
            return;
        }

        //判断该群组名是否已经在列表里面
        for(auto ite: mapIdtoChatGroupItem)
        {
            if(ite->groupName == name)
            {
                QMessageBox::information(this,"提示","请更换群组名，群组名重复！",QMessageBox::Ok);
                return;
            }
        }

        //判断该群聊名是否已存在于列表中（群聊名不允许重复）
//        for(auto ite: mapItToFriendItem)
//        {
//            if(ite->name == name)
//            {
//                //如果当前添加好友已经在好友列表里面，则弹出消息框提示对方已经是用户的好友
//                QMessageBox::information(this,"提示","请勿重复添加好友");
//                return;
//            }
//        }
        //发消息通知kernel创建群聊
        Q_EMIT SIG_createGroup(name);
    }
}
