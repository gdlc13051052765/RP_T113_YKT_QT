#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <qfile.h>
#include <qfileinfo.h>
#include <QList>
#include <QDebug>
#include <unistd.h>
#include <fcntl.h>      /*文件控制定义*/ 
#include "play.h"

#define u32 unsigned int
#define u8  unsigned char
#define u16 unsigned short
/*wav文件头格式*/
typedef  struct	{
	u8    	RiffID [4];
	u32     RiffSize;
	u8    	WaveID[4];
	u8    	FmtID[4];
	u32     FmtSize;
	u16   	wFormatTag;
	u16   	nChannels;
	u32 	nSamplesPerSec;  /*采样频率*/
	u32 	nAvgBytesPerSec; /*每秒所需字节数*/
	u16		nBlockAlign; /*数据块对齐单位,每个采样需要的字节数*/
	u16		wBitsPerSample;/*每个采样需要的bit数*/
	u8		DataID[4];
	u32 	nDataBytes;
} WAVE_HEADER;

WAVE_HEADER g_wave_header;

QList<QString> wavlist;//语音播放列表
int playNumber = 0;//播放序号

/*读取wav文件头格式*/
int Play:: open_and_print_file_params(char *file_name)
{
	FILE * fp = fopen(file_name, "r");
	if (fp == NULL)
	{
		printf("can't open wav file\n");
		return NULL;
	}
	
	memset(&g_wave_header, 0, sizeof(g_wave_header));
	fread(&g_wave_header, 1, sizeof(g_wave_header), fp);
	
	printf("RiffID:%c%c%c%c\n", g_wave_header.RiffID[0], g_wave_header.RiffID[1], g_wave_header.RiffID[2], g_wave_header.RiffID[3]);
	printf("RiffSize:%d\n", g_wave_header.RiffSize);
	printf("WaveID:%c%c%c%c\n", g_wave_header.WaveID[0], g_wave_header.WaveID[1], g_wave_header.WaveID[2], g_wave_header.WaveID[3]);
	printf("FmtID:%c%c%c%c\n", g_wave_header.FmtID[0], g_wave_header.FmtID[1], g_wave_header.FmtID[2], g_wave_header.FmtID[3]);
	printf("FmtSize:%d\n", g_wave_header.FmtSize);
	printf("wFormatTag:%d\n", g_wave_header.wFormatTag);
	printf("nChannels:%d\n", g_wave_header.nChannels);

	channels = g_wave_header.nChannels;

	printf("nSamplesPerSec:%d\n", g_wave_header.nSamplesPerSec);
	printf("nAvgBytesPerSec:%d\n", g_wave_header.nAvgBytesPerSec);
	printf("nBlockAlign:%d\n", g_wave_header.nBlockAlign);
	printf("wBitsPerSample:%d\n", g_wave_header.wBitsPerSample);
	printf("DataID:%c%c%c%c\n", g_wave_header.DataID[0], g_wave_header.DataID[1], g_wave_header.DataID[2], g_wave_header.DataID[3]);
	printf("nDataBytes:%d\n", g_wave_header.nDataBytes);
	fclose(fp);
	return 0;
}
Play::Play()
{
	channels 	= 1;
	samplesize 	= 2;
    framesize   = 1048576;
	rate		= 16000;
	//rate		= 44100;
	periods		= 16;
	periodsize	= 1024*2;
	qWarning("pcmName = %s \n\n",pcmName);
	pcmName = "hw:0,0";
    play_handle = NULL;

	play_handle = open_pcm();
    if(play_handle != NULL)
    {
        doPlay = true;
    }
    else
    {
        doPlay = false;
        qWarning("Error can't open pcm device for play.");
    }
}

Play::~Play()
{
	doPlay = false;
	if(play_handle)
	{
        snd_pcm_close(play_handle);
        play_handle = NULL;
	}
}
void Play::close_pcm()
{
	snd_pcm_close(play_handle);
    play_handle = NULL;
}

snd_pcm_t *Play::open_pcm()
{
	snd_pcm_t *pcm_handle;
	snd_pcm_hw_params_t *hwparams;
	snd_pcm_uframes_t tmpbuffersize;
	snd_pcm_uframes_t frames;
	unsigned int tmprate;
	int err;
	

	system("amixer cset numid=17,iface=MIXER,name='Speaker Function' 0");
	
	if(play_handle !=NULL) 
		return(NULL);
	//err = snd_pcm_open(&pcm_handle, qPrintable(pcmName), SND_PCM_STREAM_PLAYBACK, 0); 
	err = snd_pcm_open(&pcm_handle, "hw:0,0", SND_PCM_STREAM_PLAYBACK, 0); 
	if (err < 0) {
		qWarning("Error opening PCM device %s (%s) for play", qPrintable(pcmName), snd_strerror(err));
		fclose(pWavFile);
    	snd_pcm_close(pcm_handle);
    	play_handle = NULL;
		pcm_handle = NULL;
		snd_pcm_open(&pcm_handle, "hw:0,0", SND_PCM_STREAM_PLAYBACK, 0); 
		
		//return(NULL);
	}
	//分配一个硬件参数对象
	snd_pcm_hw_params_alloca(&hwparams);
	//向对象填充默认值
    err = snd_pcm_hw_params_any(pcm_handle, hwparams);
	if (err < 0) {
		qWarning("Can not configure this PCM device (%s) for play.", snd_strerror(err));
		snd_pcm_close(pcm_handle);
		return(NULL);
	}
	//设置交错模式
	err = snd_pcm_hw_params_set_access(pcm_handle, hwparams, SND_PCM_ACCESS_RW_INTERLEAVED);
	if (err < 0) {
       	qWarning("Error setting access (%s) interleaved for play.", snd_strerror(err));
        snd_pcm_close(pcm_handle);
        return(NULL);
    }
	//设置格式
	//if(samplesize == 2)
	{
		err = snd_pcm_hw_params_set_format(pcm_handle, hwparams, SND_PCM_FORMAT_S16_LE);	
		if (err < 0) {
            qWarning("Error setting format (%s) for play.", snd_strerror(err));
			snd_pcm_close(pcm_handle);
            return(NULL);
        }		
	}
	// else
	// {
	// 	err = snd_pcm_hw_params_set_format(pcm_handle, hwparams, SND_PCM_FORMAT_S32_LE);
	// 	if (err < 0) {
    //         qWarning("Error setting format (%s) for play.", snd_strerror(err));
	// 		snd_pcm_close(pcm_handle);
    //         return(NULL);
    //     }		
	// }
	 /* 设置采样率 */
    err = snd_pcm_hw_params_set_rate(pcm_handle, hwparams, rate, 0);
    if (0 > err) {
        qWarning("snd_pcm_hw_params_set_rate error : %s\n", snd_strerror(err));
		snd_pcm_close(pcm_handle);
        //goto err2;
    }
	//设置通道
	err = snd_pcm_hw_params_set_channels(pcm_handle, hwparams, channels);
	if (err < 0) {
        qWarning("Error setting channels (%s) for play.", snd_strerror(err));
		snd_pcm_close(pcm_handle);
        return(NULL);
    }
	//设置采用率
	// tmprate = (unsigned int)rate;
	// err = snd_pcm_hw_params_set_rate_near(pcm_handle, hwparams, &tmprate, 0);
	// if (err < 0) {
    //     qWarning("Error setting rate (%s) for play.", snd_strerror(err));
    //     snd_pcm_close(pcm_handle);
    //     return(NULL);
    // }

	// tmpbuffersize = periodsize * periods;
	// err = snd_pcm_hw_params_set_buffer_size_near(pcm_handle, hwparams, &tmpbuffersize);
	// if (err < 0) {
    //     qWarning("Error setting buffersize (%s) for play.", snd_strerror(err));
    //     snd_pcm_close(pcm_handle);
    //     return(NULL);
    // }

	// frames = 32*4; 
    // snd_pcm_hw_params_set_period_size_near(pcm_handle, hwparams, &frames, 0);
    // if(tmpbuffersize != (snd_pcm_uframes_t)(periods * periodsize))
	// {
	// 	periodsize = tmpbuffersize/periods;
	// }

	 /* 设置周期大小: period_size */
    err = snd_pcm_hw_params_set_period_size(pcm_handle, hwparams, 1024, 0);
    if (0 > err) {
        // fprintf(stderr, "snd_pcm_hw_params_set_period_size error: %s\n", snd_strerror(ret));
        // goto err2;
    }
    /* 设置周期数（驱动层buffer的大小）: periods */
    // err = snd_pcm_hw_params_set_periods(pcm_handle, hwparams, periods, 0);
    // if (0 > err) {
    //     fprintf(stderr, "snd_pcm_hw_params_set_periods error: %s\n", snd_strerror(ret));
    //     goto err2;
    // }
	//将上面设置的参数传给驱动，只有经过这步，上面设置的参数才有效
	err = snd_pcm_hw_params(pcm_handle, hwparams);
	if (err < 0) {
        qWarning("Error setting HW params (%s) for play.", snd_strerror(err));
        snd_pcm_close(pcm_handle);
        return(NULL);
    }

	snd_pcm_uframes_t g_frames;    //snd_pcm_uframes_t其实是unsigned long类型
	snd_pcm_hw_params_get_period_size(hwparams, &g_frames, 0);
    return pcm_handle;
}

int wav_fd;
void Play::run()
{
    if(play_handle != NULL)
    {
        doPlay = true;
    }
    // else
    // {
    //     doPlay = false;
    //     qWarning("Error can't open pcm device for play.");
    // }
	//int fd = open(wavFileName.toLatin1(), O_RDWR); 
	//FILE * fp = fopen(wavlist.at(playNumber).toLatin1(), "r");
	wav_fd = open(wavlist.at(playNumber).toLatin1(), O_RDONLY); 
	qDebug() << "wavlist.size() " <<wavlist.size();
		
    //while(doPlay & wavlist.size())
	while(wavlist.size())
    {
		int frames = 1024;
		int size = frames*2; //2byte/smaple, 2 channels
		char buffer[size];
		int ret = read(wav_fd, buffer, size);
        if(ret==0)
        {
			::close(wav_fd);
			wavlist.removeAt(playNumber);
			if(wavlist.size())
				wav_fd = open(wavlist.at(playNumber).toLatin1(), O_RDWR);
				//FILE * fp = fopen(wavlist.at(playNumber).toLatin1(), "r");
			else
            	return ;
        } else if(ret!=size)
        {
           
        }
        ret = snd_pcm_writei(play_handle, buffer, frames);
        if(ret == -EPIPE)
        {
            snd_pcm_prepare(play_handle);
        }
    }
    snd_pcm_drain(play_handle);
    //fclose(pWavFile);
	::close(wav_fd);
    //qWarning("play wav file over....\n");
     snd_pcm_close(play_handle);
	
    // play_handle = NULL;
	//doPlay =false;
    return;
}

void Play::SetWavFileName(QString strWavFileName)
{
    wavFileName = strWavFileName;
	wavlist << strWavFileName;//添加新的播放文件到播放列表
	qDebug() << "添加列表 = " <<wavlist;
}

void Play::Stop()
{
	doPlay = false;
}

void Play::Playback(unsigned char* buffer, int size)
{
    if(buffer && size>0) {
		snd_pcm_uframes_t ufcount = (snd_pcm_uframes_t)(size/framesize);
		snd_pcm_sframes_t sfcount = 0;
		snd_pcm_sframes_t sfeach = 0;

		while(sfcount < (snd_pcm_sframes_t) ufcount)
		{
			while((sfeach = snd_pcm_writei(play_handle, buffer+sfcount*framesize, (ufcount-sfcount)))<0)
			{
				snd_pcm_prepare(play_handle);
			}

			if(sfeach == 0) {
				qWarning("Error play device (%s) sfeach = %d",snd_strerror(sfeach), (int)sfeach);
				break;
			} else {
				sfcount += sfeach;
			}
		}
	} else {
		qWarning("Error writing data to playback device.");
	}		
}
