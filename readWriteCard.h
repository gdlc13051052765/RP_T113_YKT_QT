#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "iso7816.h"
#include "delay.h"
#include "CalucationFile.h"

////错误信息定义
#define		NO_CARD					0xff
#define		SYS_OK					0
#define		CARD_OK					0
#define		SYS_RC500_ERROR			1//读卡模块 
#define		SYS_FLASH_ERROR			2//FLASH
#define		SYS_24C256_ERROR		3//24C256
#define		SYS_24C64_ERROR			4//24C64
#define		CARD_BATCH_ERROR		5//批次
#define		CARD_NUMBER_ERROR		6//卡号不合法(1.BCD 2.超范围)
#define		CARD_LOSTCARDNUM		7//挂失卡
#define		CARD_DATA_ERROR			8//用户数据错误(1.卡数据校验和错2.卡折扣为0)
#define		CARD_LITTLEMONEY		9//金额不足
#define		CARD_OVERDATE			10//1.卡过期2.卡未启用3.黑名单有效月4.钱包有效期5.日期格式
#define		SYS_SAVERECORDFULL		11//记录满
#define   	SYS_PINCHECK_FAIL   	12//系统校验失败
#define		CARD_LIMIT_NUM			13//限次(1.无匹配方案2.限次)
#define		CARD_CONSUM_OVER		14//超出消费限额(1.单笔2.规划范围3.日限4.月限)
#define		SYS_8563_ERROR			15//上电检测时钟模块
#define		NETCARD_ERROR			16//TCP网卡初试化失败
#define		TIME_ERROR				17//消费中检测合法性
#define		CARD_STATUS_ERROR		18 //卡状态错误
#define     CARD_AUTH_FAIL          19//卡片认证失败
#define     MATCHCODE_ERR           20//匹配字失败

//卡片信息
typedef struct 
{       
	int  status;  //读取卡片状态      
	char  nameBuf[20];//用户名字    
	char  cardIdentity; //卡身份    
	char  cardPrinterNum[4];//卡片印刷号 
	char  cardSerialNum[4];//卡片唯一序列号
    int cardBalance;//卡片余额
	int consumeMoney;//消费额
	int newBalanceMoney;//消费后余额
} cardMsgInfo;
//cardMsgInfo cardInfo;

//时间结构体
struct sTimeStruct
{
	unsigned char	YearChar;
	unsigned char	MonthChar;
	unsigned char	DayChar;
	unsigned char	HourChar;
	unsigned char	MinuteChar;
	unsigned char	SecondChar;
};
union uTimeUnion
{
	unsigned char TimeString[6];
	struct	sTimeStruct	S_Time;
};

//调用so库线初始化库，从配置数据库读取卡配置信息
void init_card_so(void);

//void MFRC522_Initializtion(void) ;//RC522初始化
//测试是否有卡返回卡序列号
cardMsgInfo RequestCard(cardMsgInfo pMsg);

/*=======================================================================================
* 函 数 名： ReadCardCommonDatas_M1
* 参    数： cardSector(扇区号), pMsg消费信息结构体;
* 功能描述:  读取卡片信息结构体
* 返 回 值： 成功返回 卡片信息结构体; 
* 备    注： 
* 作    者： lc
* 创建时间： 2021-12-02
==================================================================================*/
cardMsgInfo ReadCardCommonDatas_M1(char cardSector);

/*=======================================================================================
* 函 数 名： ReadCard_DaySumConsumMoney_M1
* 参    数： pMsg消费信息结构体;
* 功能描述:  读出累计日消费额
* 返 回 值： 成功返回 0; 
* 备    注： 
* 作    者： lc
* 创建时间： 2021-12-02
==================================================================================*/
char ReadCard_DaySumConsumMoney_M1(void);

/*=======================================================================================
* 函 数 名： ReadCardBalanceDatas_M1
* 参    数： RdSector扇区号；pMsg消费信息结构体;
* 功能描述:  读取卡片余额
* 返 回 值： 成功返回 0; 
* 备    注： 
* 作    者： lc
* 创建时间： 2021-12-02
==================================================================================*/
cardMsgInfo ReadCardBalanceDatas_M1(char RdSector);

/*==================================================================================
* 函 数 名： read_balance_from_card
* 参    数： 
* 功能描述:  读取卡片余额
* 返 回 值： 
* 备    注： 创建成功返回0
* 作    者： lc
* 创建时间： 2021-09-27
==================================================================================*/
cardMsgInfo read_balance_from_card(void);

/*=======================================================================================
* 函 数 名： WriteBalanceToCard_M1
* 参    数： bit == 0 消费状态;bit == 1取消消费回写原来金额
			WrSector扇区号; pMsg消费信息结构体;  CurrentConsumMoney消费额; 
* 功能描述:  写入新的卡片余额
* 返 回 值： 成功返回 0; 
* 备    注： 
* 作    者： lc
* 创建时间： 2021-12-02
==================================================================================*/
char WriteBalanceToCard_M1(char bbit,  cardMsgInfo pMsg) ;//;

/*=======================================================================================
* 函 数 名： ReWriteCardSub_M1
* 参    数： bit == 0 消费状态;bit == 1取消消费回写原来金额 pMsg消费信息结构体;  
* 功能描述:  复写新的卡片余额
* 返 回 值： 成功返回 0; 
* 备    注： 
* 作    者： lc
* 创建时间： 2021-12-02
==================================================================================*/
char ReWriteCardSub_M1(char bbit);

/********************************************************
//卡余额诊断
********************************************************/
char CardBalanceDiag(cardMsgInfo pMsg);
/*=======================================================================================
* 函 数 名： sqlite3_insert_consume_record_to_db
* 参    数： 
* 功能描述:  插入消费记录搭配记录数据库
* 返 回 值： 
* 备    注： 
* 作    者： lc
* 创建时间： 2022-01-26 
==========================================================================================*/
int sqlite3_insert_consume_record_to_db(int bbit,int consumeMode,int CurrentConsumMoney,int);
