#include "ipinformation.h"
#include <QApplication>
#include <QFontDatabase>
#include <QTextCodec>
#include <QFont>
#include "setup.h"
#include "devmsg.h"
#include "setconsumemode.h"
#include "queryconsumerecord.h"
#include "querydayconsumemoney.h"
#include "modifysystimeui.h"
#include "key_thread.h"
//#include <QWSServer>
//#include <QSound>
#include <alsa/asoundlib.h>
#include <QTest>
#include "play.h"
#include "sqlite3QT.h"


static Sqlite3QT mSqliteClass;//sqlite类
static configMsgSt mDevMsg;//设备信息

//版本号
static QString ver = "YKT-VER-0.0.3";

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8")); 
   // QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));

    system("amixer cset numid=1,iface=MIXER,name='Master Playback Volume' 1");//设置语音音量

    a.setFont(QFont("Droid Sans Fallback", 9));
    // //遍历本地字库
    // foreach (const QString &fontfamily, fontbase.families()) {
    //     qDebug()<<fontfamily;
    // }

     //配置数据库读取信息
    mDevMsg = mSqliteClass.Sqlite_read_msg_from_configdb();
    qDebug() <<"当前版本号 = " << mDevMsg.version;
    if(QString::compare(mDevMsg.version,ver))
    {
        mSqliteClass.Sqlite_update_ver(ver);
    }
    //命令行配置ip地址
    QString str = "ifconfig eth0 ";
    str.append(mDevMsg.localIp);
    QByteArray ba=str.toLatin1();
    char *sql=ba.data();
    qDebug() << str;
    system(sql);
    QTest::qSleep(1000);//延时1s

    mainConsumeInterface w;
    w.show();

    // w.move(0,0);
    // w.resize(800, 480);
    // w.setWindowFlags(Qt::FramelessWindowHint);
    // w.setAttribute(Qt::WA_AcceptTouchEvents, true);
    // w.show();

    // QGraphicsScene *scene = new QGraphicsScene;
    // QGraphicsProxyWidget *g = scene->addWidget(&w);
    // g->setRotation(-90);

    // QGraphicsView *view = new QGraphicsView(scene);
    // view->setWindowFlags(Qt::FramelessWindowHint);//无边框
    // view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    // view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    // view->setFrameStyle(QFrame::NoFrame);//无Frame边框

    // view->setInteractive(true);  //设置场景内的是否允许交互
    // view->resize(600, 1024);
    // view->move(0,0);
    // view->show();

    return a.exec();
}
