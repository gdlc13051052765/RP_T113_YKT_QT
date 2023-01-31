#include "widget.h"
#include "ui_widget.h"
#include <QtNetwork>
#include <QFileDialog>
//#include <QWSServer>
#include "sqlite3QT.h"
#include <QTest>
#include "setup.h"

static QString displayString, stationcode, maincode,nonet,localip,rometeip;
static int localport,rometeport;

//字体大小
#define FONT_SIZE 40
#define BIG_FONT_SIZE 55
#define SIM_FONT_SIZE 24

//
#define serverStatus_X  60
#define serverStatus_Y  60

static Sqlite3QT mSqliteClass;//sqlite类
static configMsgSt mDevMsg;//设备信息

Widget::Widget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Widget)
{
    //配置数据库读取信息
    mDevMsg = mSqliteClass.Sqlite_read_msg_from_configdb();
    ui->setupUi(this);
    this->setWindowTitle("固件更新");
    connect(&m_tcpServer,SIGNAL(newConnection()),this,SLOT(acceptConnection()));
    connect(ui->startButton,SIGNAL(clicked()),this,SLOT(startBtnClicked()));
    //readTxt();
    ui->serverProgressBar->setValue(0);
    ui->startButton->setEnabled(true);

    //
    QPalette pa;
    pa.setColor(QPalette::WindowText, QColor(205,205,0));//浅黄色
    QFont modeft;
    modeft.setPointSize(SIM_FONT_SIZE);
    ui->serverStatusLabel->move(serverStatus_X, serverStatus_Y);//位置
    ui->serverStatusLabel->setText("aaa");
    ui->serverStatusLabel->setPalette(pa);//设置颜色
    ui->serverStatusLabel->setFont(modeft);//设置字体大小
}

Widget::~Widget()
{
    delete ui;
}

void Widget::start(){
    localip = mDevMsg.localIp;
    qDebug() << "开始监听 = " <<QHostAddress(localip);

    if(!m_tcpServer.listen(QHostAddress(localip),10086)){
        qDebug()<<m_tcpServer.errorString();
        close();
        return;
    }
    
    ui->startButton->setEnabled(false);
    m_totalBytes=0;
    m_bytesReceived=0;
    m_fileNameSize=0;
    ui->serverStatusLabel->setText("监听");
    ui->serverProgressBar->reset();
}
void Widget::acceptConnection(){
    m_tcpServerConnection=m_tcpServer.nextPendingConnection();
    connect(m_tcpServerConnection,SIGNAL(readyRead()),this,SLOT(updateServerProgress()));
    connect(m_tcpServerConnection,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(displayError(QAbstractSocket::SocketError)));
    ui->serverStatusLabel->setText("接受连接");
    //关闭服务器不再监听，直接进入数据收发
    m_tcpServer.close();
}

void Widget::updateServerProgress(){
    QDataStream in(m_tcpServerConnection);

    //in.setVersion(QDataStream::Qt_5_7);
    // 如果接收到的数据小于16个字节，保存到来的文件头结构
    if (m_bytesReceived<=sizeof(qint64)*2){
        if((m_tcpServerConnection->bytesAvailable()>=sizeof(qint64)*2)&&(m_fileNameSize==0)){
            // 接收数据总大小信息和文件名大小信息
            in>>m_totalBytes>>m_fileNameSize;
            m_bytesReceived +=sizeof(qint64)*2;
            qDebug() <<"接收文件大小 = "<<m_totalBytes;
            system("rm -rf ota");
            system("mkdir ota");
        }
        if((m_tcpServerConnection->bytesAvailable()>=m_fileNameSize)&&(m_fileNameSize!=0)){
            // 接收文件名，并建立文件
            in>>m_fileName;
            qDebug() <<"文件名字 ="<<m_fileName;
            ui->serverStatusLabel->setText(tr("接收文件 %1 …").arg(m_fileName));
            m_bytesReceived+=m_fileNameSize;
            m_fileName = "/root/ota/ota.zip";
            m_localFile = new QFile(m_fileName);
            if (!m_localFile->open(QFile::WriteOnly)){
                qDebug() << "server: open file error!";
                return;
            }
        }
        else{
            return;
        }
    }
    // 如果接收的数据小于总数据，那么写入文件
    if(m_bytesReceived<m_totalBytes) {
        m_bytesReceived+=m_tcpServerConnection->bytesAvailable();
        m_inBlock = m_tcpServerConnection->readAll();
        m_localFile->write(m_inBlock);
        m_inBlock.resize(0);
    }
    ui->serverProgressBar->setMaximum(m_totalBytes);
    ui->serverProgressBar->setValue(m_bytesReceived);

    // 接收数据完成时
    if (m_bytesReceived==m_totalBytes){
        qDebug() << "接收数据完成";
        m_tcpServerConnection->close();
        m_localFile->close();
        ui->startButton->setEnabled(true);
        ui->serverStatusLabel->setText(tr("接收文件 %1 成功！").arg(m_fileName));


        system("unzip /root/ota/ota.zip");
        QTest::qSleep(1000);//延时1S
        system("chmod -R 777 /root/ota");
        // system("reboot");
        system("/root/ota/run.sh");
    }
}

void Widget::displayError(QAbstractSocket::SocketError socketError){
    Q_UNUSED(socketError)
    qDebug()<<m_tcpServerConnection->errorString();
    m_tcpServerConnection->close();
    ui->serverProgressBar->reset();
    ui->serverStatusLabel->setText("服务端就绪");
    ui->startButton->setEnabled(true);
}

/*==================================================================================
* 函 数 名： keyPressEvent
* 参    数：
* 功能描述:  获取按键值
* 返 回 值： 
* 备    注： None
* 作    者： lc
* 创建时间： 2021/8/2
==================================================================================*/
//void queryConsumeRecord::keyPressEvent(QKeyEvent *ev)
void Widget::keyReleaseEvent(QKeyEvent *ev)
{

    if (ev->key() == Qt::Key_F3)
    {
        qDebug() << "press key Esc";
        //跳回设置主界面
        this->close();
        // setUp d;
        // d.exec();
        setUp *aw = new setUp();
        aw->show();
        return;
    }
}

void Widget::startBtnClicked(){
    start();
}
