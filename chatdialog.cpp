#include "chatdialog.h"
#include "ui_chatdialog.h"
#include <QTime>

chatDialog::chatDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::chatDialog)
{
    ui->setupUi(this);

}

chatDialog::~chatDialog()
{
    delete ui;
}

void chatDialog::setId(int id,QString name)
{
    this->id = id;
    this->name = name;
}

void chatDialog::insertFileRows(FileInfo *fileInfo)
{
    int rows = ui->tb_fileInfo->rowCount();   //获取控件当前行数
    ui->tb_fileInfo->setRowCount(rows+1);     //设置行数加1
    //2:设置这一行的每一列控件（添加对象）
    MyTableWidgetItem *item0 = new MyTableWidgetItem;
    item0->setInfo(fileInfo);
    item0->setText(fileInfo->filePath);
    ui->tb_fileInfo->setItem(rows,0,item0);

    QTableWidgetItem* item1 = new QTableWidgetItem;
    if(fileInfo->userId == id)
    {
        //文件信息发送id 和窗口id相同 ，所以本地用户是接收方
        item1->setText("下载");
    }
    else
    {
        item1->setText("上传");
    }
    ui->tb_fileInfo->setItem(rows,1,item1);

    //进度条
    QProgressBar* progress = new QProgressBar;
    progress->setMaximum(fileInfo->size);
    progress->setValue(fileInfo->cutNow * fileInfo->cutSize);
    ui->tb_fileInfo->setCellWidget(rows, 2, progress);

    //打开文件按钮
    QPushButton* button = new QPushButton;
    ui->tb_fileInfo->setCellWidget(rows,3,button);


}

void chatDialog::updateProcess(FileInfo *fileInfo)
{
    //首先找到这一行控件
    int rows = ui->tb_fileInfo->rowCount();   //获取控件当前行数
    for(int i=0;i<=rows;i++)
    {
        MyTableWidgetItem* item =(MyTableWidgetItem*)ui->tb_fileInfo->item(i,0);
        if(item->userId==fileInfo->userId && item->timestamp==fileInfo->timestamp)
        {
            //更新进度
             QProgressBar* progress =  (QProgressBar*)ui->tb_fileInfo->cellWidget(i,2);
             progress->setValue(fileInfo->cutNow*fileInfo->cutSize + fileInfo->nowSize);
             break;
        }
    }

}

//发送消息函数
void chatDialog::on_pb_send_clicked()
{
    QString text = ui->le_insert->toPlainText();  //获取输入框的文本信息
    if(text.remove(" ").size() == 0)
    {
        //若文本内容为空
        QMessageBox::information(this,"提示","请先输入信息!",QMessageBox::Yes);
        return;
    }
    dealChatRq(text,"我");
     ui->le_insert->setText("");  //发送消息框清空
    //如果不为空，则发信号通知ckernel有数据要发送
    Q_EMIT SIG_sendChatMessage(id,text);
}

//在控件上显示聊天信息
void chatDialog::dealChatRq(QString text, QString defaultName)   //name有一个默认值，默认值为空
{
    if(defaultName == ""){
        //显示到浏览器窗口上，格式【ip】时间...
        ui->tb_chatRecord->append(QString("【%1】 %2").arg(name).arg(QTime::currentTime().toString("hh:mm:ss")));  //append()在text edit的最后添加一个新的段落。
        ui->tb_chatRecord->append(text);   //insertPlainText()
    }
    else
    {
        //显示到浏览器窗口上，格式【ip】时间...
        ui->tb_chatRecord->append(QString("【%1】 %2").arg(defaultName).arg(QTime::currentTime().toString("hh:mm:ss")));  //append()在text edit的最后添加一个新的段落。
        ui->tb_chatRecord->append(text);   //insertPlainText()
    }
}

//重写按键按下事件
void chatDialog::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == QKeyEvent::Enter)
    {
        on_pb_send_clicked();
    }
}

//文件传输按钮
void chatDialog::on_pb_openFile_clicked()
{
    //点击 弹出文件选择对话框  选择路径
    QString path = QFileDialog::getOpenFileName(this,"选择文件夹","./");
    if(path.isEmpty())
    {
        //没有选择文件，则直接退出
        qDebug()<<"your choose is null!";
        return;
    }

    //将文件路径发送给kernel，然后由kernenl发送
    Q_EMIT SIG_sendFile(id,path);
}




void chatDialog::on_tb_fileInfo_cellDoubleClicked(int row, int column)
{
    int rows = ui->tb_fileInfo->rowCount();   //获取控件当前行数
    //判断文件当前的状态
     MyTableWidgetItem* item =(MyTableWidgetItem*)ui->tb_fileInfo->item(row,0);  //我们只需要用到 row参数
     if(item->pause == FILE_IS_STARTED)
     {
         QMessageBox::information(this,"提示","文件zheng'zai 传输中",QMessageBox::Ok);
         return;
     }
     if(item->userId != id)
     {
         QMessageBox::information(this,"提示","您只能在别人再次请求的时候才能继续发送该文件",QMessageBox::Ok);
         return;
     }

     //发送信号通知kernel，让kernel发出文件请求
     Q_EMIT SIG_sendFileBlockRq(item->userId,item->timestamp);
}
