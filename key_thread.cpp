

#include <sys/ioctl.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>
#include <stdint.h>
#include <sys/stat.h>

#include <QDebug>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <QMutex>
#include <QQueue>
#include <QTime>
#include <QTimer>
#include <QProcess>
#include "cJSON.h"
#include "sqlite3QT.h"
#include "key_thread.h"

#define CH455_BIT_ENABLE	0x03		       // 开启/关闭位
#define CH455_BIT_SLEEP		0x04		      // 睡眠控制位
 
#define CH455_SYSOFF        0x0400                             // 关闭显示、关闭键盘
#define CH455_SYSON         (CH455_SYSOFF|CH455_BIT_ENABLE)   // 开启显示、键盘
#define CH455_SLEEPOFF	    CH455_SYSOFF	// 关闭睡眠
#define CH455_SLEEPON	    (CH455_SYSOFF|CH455_BIT_SLEEP)	// 开启睡眠


static int fd;
static void ch455_write(unsigned char *Data,unsigned char len)
{
	write(fd,Data,len);
}
 
static unsigned char ch455_read(unsigned char Data)
{
	read(fd, &Data, 1);
	return Data;
}

//PCF8563写数据
static void pcf8563_write(unsigned char *Data,unsigned char len)
{
	write(fd,Data,len);
}
//PCF8563读数据
static unsigned char pcf8563_read(unsigned char Data)
{
	read(fd, &Data, 1);
	return Data;
}

KEY_THREAD::KEY_THREAD(QObject *parent)
{
    int Data;
    unsigned char test_val = 0;
    unsigned char read_val;
	int ret;

    fd = open("/dev/ch455", O_RDWR);
	if (fd < 0)
	{
		printf("can't open!\n");
		return ;
	}	
	qDebug() << "/dev/keyBoard_rtc open";
	Data = (unsigned short)CH455_SYSON;
	ch455_write((unsigned char*)(&Data), sizeof(Data));  //抗干扰，定时刷新CH455寄存器

}

KEY_THREAD::~KEY_THREAD()
{

}

// void KEY_THREAD::MainWindow_Receive_Handler()
// {
//     printf("接收主窗口发过来的数据\n");
// }

void KEY_THREAD::run()
{
    // int Data;
    // unsigned char test_val = 0;
    // unsigned char read_val;
	// int ret;

    // fd = open("/dev/keyBoard_rtc", O_RDWR);
	// if (fd < 0)
	// {
	// 	printf("can't open!\n");
	// 	return ;
	// }	
	// Data = (unsigned short)CH455_SYSON;
	// ch455_write((unsigned char*)(&Data), sizeof(Data));  //抗干扰，定时刷新CH455寄存器
    
    // while (1)
    // {
    //    	read_val = 0xff;
	// 	read_val = ch455_read();
	// 	if(read_val != 28)
	// 	{
    //        // qDebug() << "get key value" << read_val;
	// 	}
	// 	usleep(50 *1000);
    // }
}
