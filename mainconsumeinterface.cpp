#include "mainconsumeinterface.h"
#include "ui_mainconsumeinterface.h"
#include <QHBoxLayout>
#include "cJSON.h"
#include "sqlite3QT.h"
#include "setup.h"
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

extern "C"
{
    #include "readWriteCard.h"
    #include  "utils.h"
}


//消费模式
#define MONEY_CONSUME_MODE 0//计算模式
#define AUTO_CONSUME_MODE 1//自动模式
#define PLAN_CONSUME_MODE 2//价格方案

//第一个label的位移
#define FIRST_LABEL_X  20
#define FIRST_LABEL_Y  60
//label的形状大小
#define LABEL_SHAPE_L  80
#define LABEL_SHAPE_H  80
//label横向间隔
#define LABEL_TRANSVERSE_SPACE    150
//label纵向间隔
#define LABEL_VERICAL_SPACE    40
//edit形状大小
#define EDIT_SHAPE_L  250
#define EDIT_SHAPE_H  60
//字体大小
#define FONT_SIZE 40
#define BIG_FONT_SIZE 55
#define SIM_FONT_SIZE 24

//系统时间坐标
#define CONSUME_MODE_X   200
#define CONSUME_MODE_Y   150
//系统时间坐标
#define SYSTIME_X   520
#define SYSTIME_Y   450
//设备号坐标
#define DEV_NUMBER_X   20
#define DEV_NUMBER_Y   450
//版本号坐标
#define VERSION_X   200
#define VERSION_Y   450

static Sqlite3QT mSqliteClass;//sqlite类
static configMsgSt mDevMsg;//设备信息
static int SaveRecordIndex;//存储记录指针

#define PLAY_THREAD_MODE
//#define ALSA_MODE



mainConsumeInterface::mainConsumeInterface(QWidget *parent) :
     QDialog(parent),

    ui(new Ui::mainConsumeInterface)
{
    ui->setupUi(this);
    this->setCursor(Qt::BlankCursor);   //隐藏鼠标
    this->setWindowFlags(Qt::FramelessWindowHint);//不显示标题栏
    this->resize(QSize(800, 480));
    this->setGeometry(0, 0, 800, 480);//设置窗口大小
    QPalette pal(this->palette());
    pal.setColor(QPalette::Background, Qt::black); //设置背景黑色
    this->setAutoFillBackground(true);
    this->setPalette(pal);
    this->setCursor(Qt::BlankCursor); //隐藏鼠标

    #ifdef PLAY_THREAD_MODE
        play = new Play();
    #endif
    #ifdef ALSA_MODE
        mcpcm = new MC_multimedia();
    #endif

    //配置数据库读取信息
    mDevMsg = mSqliteClass.Sqlite_read_msg_from_configdb();

    QPalette pa;
    pa.setColor(QPalette::WindowText,Qt::white);
    QFont ft;
    ft.setPointSize(FONT_SIZE);

    //跟设置界面创建信息互联
    setConsumeMode *mainDialog = new setConsumeMode(this);
    connect(mainDialog,SIGNAL(sendConsumeModeSingnals(QString)),this,SLOT(getConsumeModeHandle(QString)));

    //创建闪烁定时器
    twinkleTimer = new QTimer(this);          //  MSG消息队列定时器任务     
    connect(twinkleTimer, SIGNAL(timeout()), this, SLOT(twinkleTimerTimeHandle()));
    //twinkleTimer->start(1000);

    //消费输入GroupBox ，消费控件放入此GroupBox
    //行列布局layout
    inputMoneyGoupBox = new QGroupBox(this);
    inputMoneyGoupBox->move(150,90);
    inputMoneyGoupBox->resize(450, 180);
    inputMoneyGoupBox->setStyleSheet("background-color:rgba(0,0,0); color:rgb(255,255,255);");

    //消费金额 label
    consumeMoneyLabel = new QLabel(this);
    QString currentMoneyStr = "";
    if (mDevMsg.consumeMode == MONEY_CONSUME_MODE )
    {
        currentMoneyStr = "计算模式";
    }
    else if (mDevMsg.consumeMode == AUTO_CONSUME_MODE )
    {
        currentMoneyStr = "自动模式";
        twinkleTimer->start(1000);
    }
    else if (mDevMsg.consumeMode == PLAN_CONSUME_MODE )
    {
        currentMoneyStr = "价格方案";
    }
    else {
        currentMoneyStr = "计算模式";
    }
    consumeMoneyLabel->setText(currentMoneyStr);
    pa.setColor(QPalette::WindowText, QColor(205,205,0));//浅黄色
    consumeMoneyLabel->setPalette(pa);//设置颜色
    QFont modeft;
    modeft.setPointSize(BIG_FONT_SIZE);
    consumeMoneyLabel->setFont(modeft);//设置字体大小

    consumeMoneyEdit = new QLineEdit(this);
    consumeMoneyEdit->installEventFilter(this);//在窗体上为lineEdit1安装过滤器
    consumeMoneyEdit->setObjectName("consumeMoneyEdit");
    consumeMoneyEdit->setPalette(pa);//设置颜色
    ft.setPointSize(BIG_FONT_SIZE);
    consumeMoneyEdit->setFont(ft);//设置字体大小
    consumeMoneyEdit->setCursorPosition(consumeMoneyEdit->text().size()); //设置焦点（光标） 位置，设置在末尾
    consumeMoneyEdit->setAlignment(Qt::AlignHCenter);//居中显示
    if (mDevMsg.consumeMode == MONEY_CONSUME_MODE )//计算模式消费额清零
    {
        consumeMoneyEdit->setText("");
        consumeMoneyEdit->setEnabled(true);
    } else {
        QString money = QString::number(mDevMsg.consumeModeConsumeMoney);
        qDebug() << "money.length() " <<money.length();
        if(money.length()>1)
        {
            QString str1 = money.right(2);  
            QString str = money.mid(0,money.length()-2);  
            str.append(".");   
            str.append(str1);
            str = QString::number(str.toFloat(), 'f', 2);//字符串转float并保留后面两位小数
            consumeMoneyEdit->setText(str);
            consumeMoneyEdit->setEnabled(false);
            qDebug() << "自动模式金额 = " << str<< money;
        } else {
            QString str1 = "0";
            str1.append(money);
            //str1 = money.right(2);  
            QString str = money.mid(0,str1.length()-2);  
            str.append(".");   
            str.append(str1);
            str = QString::number(str.toFloat(), 'f', 2);//字符串转float并保留后面两位小数
            consumeMoneyEdit->setText(str);
            consumeMoneyEdit->setEnabled(false);
            qDebug() << "自动模式金额 = " << str<< money;
        }
    }
    
    QLabel *moneyLabel = new QLabel(this);
    QString str = QString::fromLocal8Bit("金额:");
    moneyLabel->setText(str);
    pa.setColor(QPalette::WindowText, QColor(205,205,0));//浅黄色
    moneyLabel->setFont(ft);//设置字体大小
    moneyLabel->setPalette(pa);//设置颜色
    QLabel *moneyFlagLabel = new QLabel(this);
    moneyFlagLabel->setText("元");
    pa.setColor(QPalette::WindowText, QColor(205,205,0));//浅黄色
    moneyFlagLabel->setFont(ft);//设置字体大小
    moneyFlagLabel->setPalette(pa);//设置颜色

    //行列布局layout
    QGridLayout *inputMoneyLayout = new QGridLayout();
    //设置布局内部四边的空隙 左-上-右-下
    inputMoneyLayout->setRowStretch(1, 2);    //创建5行
    inputMoneyLayout->addWidget(consumeMoneyLabel,0,1,Qt::AlignVCenter);//第0行，第0列开始，占1行3列 居中显示
    inputMoneyLayout->addWidget(moneyLabel,1,0);
    inputMoneyLayout->addWidget(consumeMoneyEdit,1,1);
    inputMoneyLayout->addWidget(moneyFlagLabel,1,2);
    inputMoneyGoupBox->setLayout(inputMoneyLayout);

     //刷卡提示 label
    //pushCardLabel = new QLabel(this);
    pushCardLabel = new QLineEdit(this);
    pushCardLabel->setStyleSheet("QLineEdit{border-width:0;border-style:outset}");
    pushCardLabel->setAlignment(Qt::AlignCenter);
    //pushCardLabel->installEventFilter(this);//在窗体上为lineEdit1安装过滤器
    //pushCardLabel->move(0, CONSUME_MODE_Y+150);//位置
    pa.setColor(QPalette::WindowText, QColor(205,205,0));//浅黄色
    pushCardLabel->setText("请刷卡");
    pushCardLabel->setPalette(pa);//设置颜色
    pushCardLabel->setFont(ft);//设置字体大小
    pushCardLabel->hide();//默认隐藏。等待刷卡时闪烁显示
     //行列布局layout
    twinkleGoupBox = new QGroupBox(this);
    twinkleGoupBox->move(180,300); 
    twinkleGoupBox->resize(500, 80);
    twinkleGoupBox->setStyleSheet("background-color:rgba(0,0,0); color:rgb(205,205,0);");
    QGridLayout *twinkleLayout = new QGridLayout();
     //设置布局内部四边的空隙 左-上-右-下
    twinkleLayout->setRowStretch(1, 1);    //创建1行1列
    twinkleLayout->addWidget(pushCardLabel,0,0);
    twinkleGoupBox->setLayout(twinkleLayout);
    
    //消费输入GroupBox ，消费控件放入此GroupBox
    //行列布局layout
    consumeResultGoupBox = new QGroupBox(this);
    consumeResultGoupBox->move(200,50);
    consumeResultGoupBox->resize(500, 300);
    consumeResultGoupBox->setStyleSheet("background-color:rgba(0,0,0); color:rgb(255,255,255);");

    cardNumberLabel = new QLabel(this);
    cardNumberLabel->setText("卡号：");
    ft.setPointSize(BIG_FONT_SIZE);
    cardNumberLabel->setFont(ft);//设置字体大小
    userNameLabel = new QLabel(this);
    userNameLabel->setText("姓名：");
    userNameLabel->setFont(ft);//设置字体大小
    currentMoneyLabel = new QLabel(this);
    currentMoneyLabel->setText("金额：");
    currentMoneyLabel->setFont(ft);//设置字体大小
    balanceLabel = new QLabel(this);
    balanceLabel->setText("余额：");
    balanceLabel->setFont(ft);//设置字体大小
    //行列布局layout
    QGridLayout *consumeResuleLayout = new QGridLayout();
    //设置布局内部四边的空隙 左-上-右-下
    consumeResuleLayout->setRowStretch(4, 2);    //创建4行
    consumeResuleLayout->addWidget(cardNumberLabel,0,0);//第0行，第0列开始，占1行3列 居中显示
    consumeResuleLayout->addWidget(userNameLabel,1,0);
    consumeResuleLayout->addWidget(currentMoneyLabel,2,0);
    consumeResuleLayout->addWidget(balanceLabel,3,0);
    consumeResultGoupBox->setLayout(consumeResuleLayout);
    consumeResultGoupBox->hide();//默认隐藏。消费成功后显示
   
    //系统时间 label
    //获取当前时间
    QDateTime dateTime(QDateTime::currentDateTime());
	QString qStr = dateTime.toString("yyyy.MM.dd hh:mm:ss");
    sysTimeLabel = new QLabel(this);
    sysTimeLabel->move(SYSTIME_X, SYSTIME_Y);//位置
    sysTimeLabel->setText(qStr);
    sysTimeLabel->setPalette(pa);//设置颜色
    QFont sysTimeft;
    sysTimeft.setPointSize(SIM_FONT_SIZE);
    sysTimeLabel->setFont(sysTimeft);//设置字体大小
  
    //设备号 label
    devNumberLabel = new QLabel(this);
    devNumberLabel->move(DEV_NUMBER_X, DEV_NUMBER_Y);//位置
    qStr = "设备号: ";
    qStr.append(QString::number(mDevMsg.devId));
    devNumberLabel->setText(qStr);
    devNumberLabel->setPalette(pa);//设置颜色
    QFont devNumberLabelft;
    devNumberLabelft.setPointSize(SIM_FONT_SIZE);
    devNumberLabel->setFont(devNumberLabelft);//设置字体大小

    //版本号 label
    versionLabel = new QLabel(this);
    versionLabel->move(VERSION_X, VERSION_Y);//位置
    qStr = "版本号: ";
    qStr.append(mDevMsg.version);
    versionLabel->setText(qStr);
    versionLabel->setPalette(pa);//设置颜色
    versionLabel->setFont(devNumberLabelft);//设置字体大小

    //创建定时更新系统时间定时器
    updateSysTimeTimer = new QTimer(this);          //  MSG消息队列定时器任务     
    connect(updateSysTimeTimer, SIGNAL(timeout()), this, SLOT(updateSysTimeHandle()));
    updateSysTimeTimer->start(1000);

    //创建一个权限为0666（所有用户可读可写，具体查询linux权限相关内容）的消息队列，并返回一个消息队列ID，
    //如果key值已经存在有消息队列了，则直接返回一个消息队列ID。
    //创建消息队列用于接收消费后台信息
    key_Rcv = ftok("/tmp", 88);
    id_Rcv = msgget(key_Rcv, IPC_CREAT|0666);
    if(id_Rcv == -1) {
        printf("create Rcv_msg error ");
    }
    key_Snd = ftok("/tmp", 66);
    id_Snd = msgget(key_Snd, 0666|IPC_CREAT);
    if(id_Snd == -1) {
        printf("create Snd_msg error ");
    }
    Snd_msg.mtype = 66;
    //创建消息队列接收定时器
    Communicate_Msg_QT_Go_Timer = new QTimer(this);          //  MSG消息队列定时器任务     
    connect(Communicate_Msg_QT_Go_Timer, SIGNAL(timeout()), this, SLOT(Communicate_Msg_QT_Go_Handle()));
    Communicate_Msg_QT_Go_Timer->start(100);
    //发送消费模式到golang
    Snd_msg.mtext[0] = 3;
    Snd_msg.mtext[1] = 3;//消费模式命令
    Snd_msg.mtext[2] = mDevMsg.consumeMode;
    Snd_msg.mtext[3] = 0;
    if(msgsnd(id_Snd, (void *)&Snd_msg, 10, 0) == -1) 
    {
        qDebug()<<"Send_Status Response \n";  
    }
    //插入交易记录测试
    // QString nameStr = "张三";
    // mSqliteClass.sqlite3_consume_insert_db(1,100,"2022-04-29","11223344",nameStr);


    //把已采记录搬运到已采消费记录数据库
   // mSqliteClass.sqlite3_move_collection_record_to_collection_db();
}

//16进制字符串转16进制数组
static int HexStringToHexGroup(char *psrc,char *buf,int len)
{
    int i,n = 0;
	char dst[300];
	
	for(i=0;i<len;i++)
	{
		strcpy(dst,"0X");
		strncat(dst,psrc,2);
		buf[i]= strtol(dst,NULL,16);
		psrc+=2;
		//printf("%#X ",buf[i]);
	}	
    return n;
}

/*==================================================================================
* 函 数 名： analyzeConsumptionResults
* 参    数：
* 功能描述:  解析消费结果json数据
* 返 回 值： 
* 备    注： None
* 作    者： lc
* 创建时间： 2022/01/24
==================================================================================*/
void mainConsumeInterface::analyzeConsumptionResults(char *jsonData)
{
    char buffer[20];
    int pcm_fd;
    QStringList consumeCmdList; 
    consumeCmdList << "getBalance" << "consumeResult" << "removeCard";

    cJSON *root ,*parse;
    root = cJSON_Parse(jsonData);
    if(!root)
    {
        cJSON_Delete(root);
        qDebug() << "JSON格式错误";
    } else { // JSON格式正确
        qDebug() << "JSON格式ok：" << root;
        parse = cJSON_GetObjectItem(root, "cmd");
        QString cmd = QString::fromUtf8(parse->valuestring);//char *转 QString
        qDebug() << "cmd = " << cmd ;
        switch(consumeCmdList.indexOf(cmd))
        {
            case 2: //卡片移开
            hideConsumeShowConsumeResult(true);
            if (mDevMsg.consumeMode == MONEY_CONSUME_MODE )//计算模式消费金额清零
            {
                consumeMoneyEdit->setText("");
            }
            break;
            case 0: //查询余额
            case 1: //解析消费结果
                parse = cJSON_GetObjectItem(root, "result");
                QString result = QString::fromUtf8(parse->valuestring);//char *转 QString
                qDebug() << "result = " << parse->valuestring;
                QString name = "";
                if(result == "ok")//消费成功
                {
                    //播放消费成功
                    #ifdef PLAY_THREAD_MODE
                    play->open_and_print_file_params("/root/wav/consumeOk.wav");
                    play->SetWavFileName("/root/wav/consumeOk.wav");
                    play->start();

                    #endif
                    #ifdef ALSA_MODE
                    pcm_fd = mcpcm->open_wav_file("/root/wav/consumeOk.wav");
                    mcpcm->play_wav(pcm_fd);
                    #endif
                    parse = cJSON_GetObjectItem(root, "name");
                    if(parse != NULL)
                    {
                        QTextCodec *utf8 = QTextCodec::codecForName("UTF-8");
                        QTextCodec::setCodecForLocale(utf8);
                        //QTextCodec::setCodecForCStrings(utf8);
                        QTextCodec* gbk = QTextCodec::codecForName("gbk");
                        HexStringToHexGroup(parse->valuestring, buffer, strlen(parse->valuestring));
                        QString strUnicode=gbk->toUnicode(buffer);
                        //2. unicode -> utf-8
                        QByteArray utf8_bytes=utf8->fromUnicode(strUnicode);
                        char *p = utf8_bytes.data(); //获取其char *
                        qDebug() << "用户姓名 = " << p;
                        name = QString::fromUtf8(p);
                        qDebug() << "name = " << name;
                    }
                    
                    parse = cJSON_GetObjectItem(root, "cardNum");
                    QString cardNum = "";
                    if(parse != NULL)
                    {
                        cardNum = QString::fromUtf8(parse->valuestring);//char *转 QString
                        qDebug() << "cardNum = " << cardNum;
                    }
                    
                    parse = cJSON_GetObjectItem(root, "balance");
                    int balance = 0;
                    if(parse != NULL)
                    {
                        qDebug() << "balance = " << parse->valueint;
                        balance = parse->valueint;
                    }

                    parse = cJSON_GetObjectItem(root, "SaveRecordIndex");
                    if(parse != NULL)
                    {
                        qDebug() << "SaveRecordIndex = " << parse->valueint;
                        SaveRecordIndex = parse->valueint;
                    }
                    
                    parse = cJSON_GetObjectItem(root, "currentMoney");
                    int currentMoney  = 0;
                    if(parse != NULL)
                    {
                        qDebug() << "currentMoney = " << parse->valueint;
                        currentMoney = parse->valueint;
                    }
                    
                    QString str = "卡号：";
                    str.append(cardNum);
                    cardNumberLabel->setText(str);
                    str = "姓名：";
                    str.append(name);
                    userNameLabel->setText(str);
                    if(currentMoney == 0)
                    {
                        str = "金额：0.00 元";
                        currentMoneyLabel->setText(str);//设置消费金额
                    } else {
                        str = "金额：";
                        // QString money = QString::number(currentMoney);
                        // money.insert(money.length()-2,".");
                        // qDebug() << "money = " << money;
                        // str.append(money);  

                        QString money = QString::number(currentMoney);
                        if(money.length()>1)
                        {
                            QString str1 = money.right(2);  
                            QString str = money.mid(0,money.length()-2);  
                            str.append(".");   
                            str.append(str1);
                            str = QString::number(str.toFloat(), 'f', 2);//字符串转float并保留后面两位小数
                            qDebug() << "自动模式金额 = " << str<< money;
                            str.append(" 元"); 
                            currentMoneyLabel->setText("金额："+str);//设置消费金额
                        } else {
                            QString str1 = "0";
                            str1.append(money);
                            //str1 = money.right(2);  
                            QString str = money.mid(0,str1.length()-2);  
                            str.append(".");   
                            str.append(str1);
                            str = QString::number(str.toFloat(), 'f', 2);//字符串转float并保留后面两位小数
                            qDebug() << "自动模式金额 = " << str<< money;
                            str.append(" 元"); 
                            currentMoneyLabel->setText("金额："+str);//设置消费金额
                        }
                        // QString str1 = money.right(2);  
                        // str = money.mid(0,money.length()-2);  
                        // str.append(".");   
                        // str.append(str1);
                        // str = QString::number(str.toFloat(), 'f', 2);//字符串转float并保留后面两位小数
                        // str.append(" 元"); 
                        // currentMoneyLabel->setText("金额："+str);//设置消费金额
                    }
                   
                    if(balance == 0 )
                    {
                        str = "余额：0.00";
                    } else {
                        str = "余额：";
                        QString money = QString::number(balance);
                        money.insert(money.length()-2,".");
                        qDebug() << "money = " << money;
                        str.append(money);    
                    }
                    pushCardLabel->hide();
                    twinkleTimer->stop();//停止闪烁
                    balanceLabel->setText(str+" 元");//设置余额显示内容
                    hideConsumeShowConsumeResult(false);//显示消费结果界面
                } else {//消费失败
                    parse = cJSON_GetObjectItem(root, "status");
                    if(parse != NULL)
                    {
                        int consumeStatus = parse->valueint;//char *转 QString
                        printf("错误结果 = %d\n", consumeStatus);
                        //QString consumeStatus(parse->valuestring);//char *转 QString
                        qDebug() << "consumeStatus = " <<consumeStatus;
                        QPalette pa;
                        pa.setColor(QPalette::WindowText,Qt::red);
                        pushCardLabel->setPalette(pa);//设置颜色红
                        twinkleGoupBox->setStyleSheet("background-color:rgba(0,0,0); color:rgb(255,0,0);");
                        pushCardLabel->show();
                        twinkleTimer->stop();//停止闪烁
                        switch(consumeStatus)
                        {	
                            case CARD_BATCH_ERROR:		//批次
                                pushCardLabel->setText("批次错误");
                                #ifdef PLAY_THREAD_MODE
                                play->open_and_print_file_params("/root/wav/batchErr.wav");
                                play->SetWavFileName("/root/wav/batchErr.wav");
                                play->start();
                                #endif
                                #ifdef ALSA_MODE
                                pcm_fd = mcpcm->open_wav_file("/root/wav/batchErr.wav");
                                mcpcm->play_wav(pcm_fd);
                                #endif
                            break;
                            case CARD_NUMBER_ERROR:		//卡号不合法(1.BCD 2.超范围)
                                pushCardLabel->setText("卡号不合法");
                                #ifdef PLAY_THREAD_MODE
                                play->open_and_print_file_params("/root/wav/cardNumErr.wav");
                                play->SetWavFileName("/root/wav/cardNumErr.wav");
                                play->start();
                                #endif
                                #ifdef ALSA_MODE
                                pcm_fd = mcpcm->open_wav_file("/root/wav/cardNumErr.wav");
                                mcpcm->play_wav(pcm_fd);
                                #endif
                            break;
                            case CARD_LOSTCARDNUM:		//挂失卡
                                pushCardLabel->setText("挂失卡"); //查询结果 
                                #ifdef PLAY_THREAD_MODE
                                play->open_and_print_file_params("/root/wav/lossCard.wav");
                                play->SetWavFileName("/root/wav/lossCard.wav");
                                play->start();
                                #endif
                                #ifdef ALSA_MODE
                                pcm_fd = mcpcm->open_wav_file("/root/wav/lossCard.wav");
                                mcpcm->play_wav(pcm_fd);
                                #endif
                            break;
                            case CARD_DATA_ERROR:		//用户数据错误(1.卡数据校验和错2.卡折扣为0)
                                pushCardLabel->setText("用户数据错误"); //查询结果 
                                #ifdef PLAY_THREAD_MODE
                                play->open_and_print_file_params("/root/wav/userDataErr.wav");
                                play->SetWavFileName("/root/wav/userDataErr.wav");
                                play->start();
                                #endif
                                #ifdef ALSA_MODE
                                pcm_fd = mcpcm->open_wav_file("/root/wav/userDataErr.wav");
                                mcpcm->play_wav(pcm_fd);
                                #endif
                            break;
                            case CARD_LITTLEMONEY:		//金额不足
                                pushCardLabel->setText("金额不足"); //查询结果 
                                #ifdef PLAY_THREAD_MODE
                                play->open_and_print_file_params("/root/wav/noMoney.wav");
                                play->SetWavFileName("/root/wav/noMoney.wav");
                                play->start();
                                #endif
                                #ifdef ALSA_MODE
                                pcm_fd = mcpcm->open_wav_file("/root/wav/noMoney.wav");
                                mcpcm->play_wav(pcm_fd);
                                #endif
                            break;
                            case CARD_OVERDATE:			//1.卡过期2.卡未启用3.黑名单有效月4.钱包有效期5.日期格式
                                pushCardLabel->setText("卡过期"); //查询结果 
                                #ifdef PLAY_THREAD_MODE
                                play->open_and_print_file_params("/root/wav/expiredCard.wav");
                                play->SetWavFileName("/root/wav/expiredCard.wav");
                                play->start();
                                #endif
                                #ifdef ALSA_MODE
                                pcm_fd = mcpcm->open_wav_file("/root/wav/expiredCard.wav");
                                mcpcm->play_wav(pcm_fd);
                                #endif
                            break;
                            default :	//
                                pushCardLabel->setText("卡号不合法"); //查询结果 
                                #ifdef PLAY_THREAD_MODE
                                play->open_and_print_file_params("/root/wav/cardNumErr.wav");
                                play->SetWavFileName("/root/wav/cardNumErr.wav");
                                play->start();
                                #endif
                                #ifdef ALSA_MODE
                                pcm_fd = mcpcm->open_wav_file("/root/wav/cardNumErr.wav");
                                mcpcm->play_wav(pcm_fd);
                                #endif
                            break;   
                        }
                    }
                }
            break;
            cJSON_Delete(root);
        } 
    }
}

/*==================================================================================
* 函 数 名： Communicate_Msg_QT_Go_Handle
* 参    数：
* 功能描述:  处理消息队列信息
* 返 回 值： 
* 备    注： None
* 作    者： lc
* 创建时间： 2022/01/24
==================================================================================*/
void mainConsumeInterface::Communicate_Msg_QT_Go_Handle()
{
    //读取队列信息
    memset(Rcv_msg.mtext, 0, 512);
    if(msgrcv(id_Rcv, (void *)&Rcv_msg, 512, 88, IPC_NOWAIT) == -1) {
 
    } else {
        qDebug() << "消息队列接收信息 = "<< Rcv_msg.mtext;
        analyzeConsumptionResults(Rcv_msg.mtext);
    }    
}

/*==================================================================================
* 函 数 名： getConsumeModeHandle
* 参    数：
* 功能描述: 接收设置消费界面传递过来的数据
* 返 回 值： 
* 备    注： None
* 作    者： lc
* 创建时间： 2022/01/24
==================================================================================*/
void mainConsumeInterface::getConsumeModeFromDialog(int mode, QString str)
{
    qDebug() << "getConsumeModeFromDialog = " << str << mode << mDevMsg.consumeMode;
    QString currentMoneyStr = "";
    //配置数据库读取信息
    mDevMsg = mSqliteClass.Sqlite_read_msg_from_configdb();
    
    if (mDevMsg.consumeMode == MONEY_CONSUME_MODE )
    {
        currentMoneyStr = "计算模式";
    }
    else if (mDevMsg.consumeMode == AUTO_CONSUME_MODE )
    {
        currentMoneyStr = "自动模式";
        twinkleTimer->start(1000);
    }
    else if (mDevMsg.consumeMode == PLAN_CONSUME_MODE )
    {
        currentMoneyStr = "价格方案";
    }
    else {
        currentMoneyStr = "计算模式";
    }
    consumeMoneyLabel->setText(currentMoneyStr);
}

/*==================================================================================
* 函 数 名： getConsumeModeHandle
* 参    数：
* 功能描述: 接收设置消费界面传递过来的数据
* 返 回 值： 
* 备    注： None
* 作    者： lc
* 创建时间： 2022/01/24
==================================================================================*/
void mainConsumeInterface::getConsumeModeHandle(QString str)
{
    qDebug() << "接收到设置消费模式消息 = " << str;
}

/*==================================================================================
* 函 数 名： Handle_Rfal_Value_Event
* 参    数：
* 功能描述: 接收读卡线程发过来的数据
* 返 回 值： 
* 备    注： None
* 作    者： lc
* 创建时间： 2022/01/24
==================================================================================*/
void mainConsumeInterface::Handle_Rfal_Value_Event(QString str)
{
   // qDebug() << "receive read cad thread data = " << str;
    char*  ch;
    QByteArray ba = str.toUtf8();    
    ch=ba.data();
    analyzeConsumptionResults(ch);
}

/*==================================================================================
* 函 数 名： hideConsumeShowConsumeResult
* 参    数：flag == false显示消费输入隐藏消费结果
* 功能描述: 隐藏消费输入，显示消费结果
* 返 回 值： 
* 备    注： None
* 作    者： lc
* 创建时间： 2022/01/24
==================================================================================*/
void mainConsumeInterface::hideConsumeShowConsumeResult(bool flag)
{
    if(flag == false)
    {
        consumeResultGoupBox->show();//显示消费结果界面
        inputMoneyGoupBox->hide();//隐藏消费输入界面
        pushCardLabel->setText("");
    } else {
        consumeResultGoupBox->hide();//隐藏消费结果界面
        inputMoneyGoupBox->show();//显示消费输入界面
        if (mDevMsg.consumeMode == AUTO_CONSUME_MODE)
        {
            twinkleTimer->start(1000);
            QPalette pa;
            pa.setColor(QPalette::WindowText, QColor(205,205,0));//浅黄色
            pushCardLabel->setPalette(pa);//设置颜色
            twinkleGoupBox->setStyleSheet("background-color:rgba(0,0,0); color:rgb(205,205,0);");
            pushCardLabel->setText("请刷卡");
        }
        if (mDevMsg.consumeMode == MONEY_CONSUME_MODE)
        {
            twinkleTimer->stop();
            QPalette pa;
            pa.setColor(QPalette::WindowText, QColor(205,205,0));//浅黄色
            pushCardLabel->setPalette(pa);//设置颜色
            pushCardLabel->setText("");
        }
    }
}

/*==================================================================================
* 函 数 名： updateSysTimeHandle
* 参    数：
* 功能描述: 定时更新系统时间
* 返 回 值： 
* 备    注： None
* 作    者： lc
* 创建时间： 2022/01/24
==================================================================================*/
void mainConsumeInterface::updateSysTimeHandle()
{
    //获取当前时间
    QDateTime dateTime(QDateTime::currentDateTime());
	QString qStr = dateTime.toString("yyyy.MM.dd hh:mm:ss ddd");
    sysTimeLabel->setText(qStr);
}

/*==================================================================================
* 函 数 名： twinkleTimerTimeHandle
* 参    数：
* 功能描述: 闪烁定时器
* 返 回 值： 
* 备    注： None
* 作    者： lc
* 创建时间： 2022/01/24
==================================================================================*/
void mainConsumeInterface::twinkleTimerTimeHandle()
{
    if(pushCardLabel->isVisible() == true)
        pushCardLabel->hide();
    else {
        pushCardLabel->show();
        QPalette pa;
        pa.setColor(QPalette::WindowText, QColor(205,205,0));//浅黄色
        twinkleGoupBox->setStyleSheet("background-color:rgba(0,0,0); color:rgb(205,205,0);");
        pushCardLabel->setPalette(pa);//设置颜色
        pushCardLabel->setText("请刷卡");
    }  
}

/*==================================================================================
* 函 数 名： keyPressEvent
* 参    数：
* 功能描述:  获取按键值
* 返 回 值： 
* 备    注： None
* 作    者： lc
* 创建时间： 2022/2/7
==================================================================================*/
void mainConsumeInterface::keyReleaseEvent(QKeyEvent *ev)
{
    int pcm_fd =-1;
    // char *alarm = "/root/test.wav";
    system("amixer cset numid=17,iface=MIXER,name='Speaker Function' 0");
    // alsa_aplay(alarm);//播放按键音
    //mcpcm->play_wav();
    qDebug() <<"ev->key() = " << ev->key();
    if (ev->key() == Qt::Key_Return || ev->key() == Qt::Key_Enter) 
    {
        qDebug() << "press key enter";
        QString str = consumeMoneyEdit->text();
        str = QString::number(str.toFloat(), 'f', 2);//字符串转float并保留后面两位小数
        consumeMoneyEdit->setText(str);
        twinkleTimer->start(500);
        pushCardLabel->setText("请刷卡");
        qDebug() <<"consumeMoneyEdit->text() " << consumeMoneyEdit->text();

        // play->open_and_print_file_params("/root/wav/pushCard.wav");
        // play->SetWavFileName("/root/wav/pushCard.wav");
        // play->start();
        #ifdef PLAY_THREAD_MODE
        play->open_and_print_file_params("/root/wav/pushCard.wav");
        play->SetWavFileName("/root/wav/pushCard.wav");
        play->start();
        #endif
        #ifdef ALSA_MODE
        pcm_fd = mcpcm->open_wav_file("/root/wav/pushCard.wav");
        mcpcm->play_wav(pcm_fd);
        #endif
        //emit mainConsumeslot("afsafsafsafsafaf");

        if(mDevMsg.consumeMode == MONEY_CONSUME_MODE)//计算模式
        {
            str.replace(QString("."), QString(""));
            int money = str.toInt();
            qDebug() << "money = "<< money;
            //构建json结构体
            cJSON *root; 
            char *out;  
            root=cJSON_CreateObject();     
            cJSON_AddStringToObject(root, "cmd", "setMoney");  //设置消费额命令
            cJSON_AddNumberToObject(root, "currentMoney", money);//设置消费额
            out =cJSON_Print(root);
            //printf("%s\n", out); 
            emit mainConsumeslot(QString::fromUtf8(out));//发送测试数据到主消费界面
            cJSON_Delete(root);
            free(out);	
        }
        return;
    }
    if (ev->key() == Qt::Key_Plus)
    {
        qDebug() << "press key +";
        #ifdef PLAY_THREAD_MODE
        play->open_and_print_file_params("/root/wav/add.wav");
        play->SetWavFileName("/root/wav/add.wav");
        play->start();
        #endif
        #ifdef ALSA_MODE
        pcm_fd = mcpcm->open_wav_file("/root/wav/add.wav");
        mcpcm->play_wav(pcm_fd);
        #endif
        return;
    }
    if (ev->key() == Qt::Key_Period)
    {
        qDebug() << "press key 点";
        #ifdef PLAY_THREAD_MODE
        play->open_and_print_file_params("/root/wav/dian.wav");
        play->SetWavFileName("/root/wav/dian.wav");
        play->start();
        #endif
        #ifdef ALSA_MODE
        pcm_fd = mcpcm->open_wav_file("/root/wav/dian.wav");
        mcpcm->play_wav(pcm_fd);
        #endif
        return;
    }
    if (ev->key() == Qt::Key_0)
    {
        qDebug() << "press key 0";
        #ifdef PLAY_THREAD_MODE
        play->open_and_print_file_params("/root/wav/0.wav");
        play->SetWavFileName("/root/wav/0.wav");
        play->start();
        #endif
        #ifdef ALSA_MODE
        pcm_fd = mcpcm->open_wav_file("/root/wav/0.wav");
        mcpcm->play_wav(pcm_fd);
        #endif
        return;
    }
    if (ev->key() == Qt::Key_1)
    {
        qDebug() << "press key 1";
        #ifdef PLAY_THREAD_MODE
        play->open_and_print_file_params("/root/wav/1.wav");
        play->SetWavFileName("/root/wav/1.wav");
        play->start();
        #endif
        #ifdef ALSA_MODE
        pcm_fd = mcpcm->open_wav_file("/root/wav/1.wav");
        mcpcm->play_wav(pcm_fd);
        #endif
        return;
    }
    if (ev->key() == Qt::Key_2)
    {
        qDebug() << "press key 2";
        #ifdef PLAY_THREAD_MODE
        play->open_and_print_file_params("/root/wav/2.wav");
        play->SetWavFileName("/root/wav/2.wav");
        play->start();
        #endif
        #ifdef ALSA_MODE
        pcm_fd = mcpcm->open_wav_file("/root/wav/2.wav");
        mcpcm->play_wav(pcm_fd);
        #endif
        return;
    }
    if (ev->key() == Qt::Key_3)
    {
        qDebug() << "press key 3";
        #ifdef PLAY_THREAD_MODE
        play->open_and_print_file_params("/root/wav/3.wav");
        play->SetWavFileName("/root/wav/3.wav");
        play->start();
        #endif
        #ifdef ALSA_MODE
        pcm_fd = mcpcm->open_wav_file("/root/wav/3.wav");
        mcpcm->play_wav(pcm_fd);
        #endif
        return;
    }
    if (ev->key() == Qt::Key_4)
    {
        qDebug() << "press key 4";
        #ifdef PLAY_THREAD_MODE
        play->open_and_print_file_params("/root/wav/4.wav");
        play->SetWavFileName("/root/wav/4.wav");
        play->start();
        #endif
        #ifdef ALSA_MODE
        pcm_fd = mcpcm->open_wav_file("/root/wav/4.wav");
        mcpcm->play_wav(pcm_fd);
        #endif
        return;
    }
    if (ev->key() == Qt::Key_5)
    {
        qDebug() << "press key 5";
        #ifdef PLAY_THREAD_MODE
        play->open_and_print_file_params("/root/wav/5.wav");
        play->SetWavFileName("/root/wav/5.wav");
        play->start();
        #endif
        #ifdef ALSA_MODE
        pcm_fd = mcpcm->open_wav_file("/root/wav/5.wav");
        mcpcm->play_wav(pcm_fd);
        #endif
        return;
    }
    if (ev->key() == Qt::Key_6)
    {
        qDebug() << "press key 6";
        #ifdef PLAY_THREAD_MODE
        play->open_and_print_file_params("/root/wav/6.wav");
        play->SetWavFileName("/root/wav/6.wav");
        play->start();
        #endif
        #ifdef ALSA_MODE
        pcm_fd = mcpcm->open_wav_file("/root/wav/6.wav");
        mcpcm->play_wav(pcm_fd);
        #endif
        return;
    }
    if (ev->key() == Qt::Key_7)
    {
        qDebug() << "press key 7";
         #ifdef PLAY_THREAD_MODE
        play->open_and_print_file_params("/root/wav/7.wav");
        play->SetWavFileName("/root/wav/7.wav");
        play->start();
        #endif
        #ifdef ALSA_MODE
        pcm_fd = mcpcm->open_wav_file("/root/wav/7.wav");
        mcpcm->play_wav(pcm_fd);
        #endif
        return;
    }
    if (ev->key() == Qt::Key_8)
    {
        qDebug() << "press key 8";
        #ifdef PLAY_THREAD_MODE
        play->open_and_print_file_params("/root/wav/8.wav");
        play->SetWavFileName("/root/wav/8.wav");
        play->start();
        #endif
        #ifdef ALSA_MODE
        pcm_fd = mcpcm->open_wav_file("/root/wav/8.wav");
        mcpcm->play_wav(pcm_fd);
        #endif
        return;
    }
    if (ev->key() == Qt::Key_9)
    {
        qDebug() << "press key 9";
        #ifdef PLAY_THREAD_MODE
        play->open_and_print_file_params("/root/wav/9.wav");
        play->SetWavFileName("/root/wav/9.wav");
        play->start();
        #endif
        #ifdef ALSA_MODE
        pcm_fd = mcpcm->open_wav_file("/root/wav/9.wav");
        mcpcm->play_wav(pcm_fd);
        #endif
        return;
    }
   
    if (ev->key() == Qt::Key_Up)
    {
        qDebug() << "press key up";
        //this->focusNextPrevChild(false);//按A时焦点切换至上一部件 
        return;
    }
    if (ev->key() == Qt::Key_Down)
    {
        qDebug() << "press key down";
        //this->focusNextPrevChild(false);//按D时焦点切换至下一部件 
        return;
    }
    if (ev->key() == Qt::Key_F1)
    {
        qDebug() << "press key f1";
        play->close_pcm();
        //跳回设置主界面
        this->close();
        setUp d;
        d.exec();
        return;
    }
    if (ev->key() == Qt::Key_F3)//取消键
    {
        qDebug() << "press key Esc";
       #ifdef PLAY_THREAD_MODE
        play->open_and_print_file_params("/root/wav/quxiao.wav");
        play->SetWavFileName("/root/wav/quxiao.wav");
        play->start();
        #endif
        #ifdef ALSA_MODE
        pcm_fd = mcpcm->open_wav_file("/root/wav/quxiao.wav");
        mcpcm->play_wav(pcm_fd);
        #endif
        if (mDevMsg.consumeMode == MONEY_CONSUME_MODE )
        {
            twinkleTimer->stop();
            pushCardLabel->hide();
            consumeMoneyEdit->setText("");
              //构建json结构体
            cJSON *root; 
            char *out;  
            root=cJSON_CreateObject();     
            cJSON_AddStringToObject(root, "cmd", "disableConsume");  //取消消费
            cJSON_AddNumberToObject(root, "currentMoney", 0);//设置消费额
            out =cJSON_Print(root);
            //printf("%s\n", out); 
            emit mainConsumeslot(QString::fromUtf8(out));//发送测试数据到主消费界面
            cJSON_Delete(root);
            free(out);
        }
        // Snd_msg.mtext[0] = 2;
        // Snd_msg.mtext[1] = 2;//消费取消命令
        // Snd_msg.mtext[2] = 0;
        // if(msgsnd(id_Snd, (void *)&Snd_msg, 10, IPC_NOWAIT) == -1) 
        // {
        //     qDebug()<<"Send_Status Response \n";  
        // }
        hideConsumeShowConsumeResult(true);//显示消费输入界面
        return;
    }
}

mainConsumeInterface::~mainConsumeInterface()
{
    delete ui;
}
