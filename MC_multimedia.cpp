#include "MC_multimedia.h"
#include <QDebug>

#define play_file "/root/wav/3.wav"
//#define play_file "/root/test.wav"

MC_multimedia::MC_multimedia(QObject *parent) : QObject(parent)
{
    int ret =-1;
//    effect = new QSoundEffect;
//    effect->setSource(QUrl::fromLocalFile("/home/ygou/Desktop/project/qt/mct_v1.1/qt_project/mct_v1_1/test.wav"));
//    effect->setLoopCount(1);
//    effect->setVolume(1);
//    bells = new QSound("/home/meican/Alarm.wav");
//    bells = new QSound("/home/ygou/Desktop/project/qt/mct_v1.1/qt_project/mct_v1_1/test.wav");
//    QAudioDeviceInfo audio_device_default = QAudioDeviceInfo::defaultOutputDevice();
//    qDebug()<<"audio:"<<audio_device_default.deviceName();
//    bells->play();
//    effect->play();
//    QSound::play("/home/ygou/Desktop/project/qt/mct_v1.1/qt_project/mct_v1_1/test.wav");
    period_size = 1024;
    periods = 16;
    //fd = -1;

    if(open_wav_file(play_file)!= 0){
         qDebug() << "open_wav_file:failed" << __FILE__ << __FUNCTION__ << __LINE__;
        // return;
    }
    if(snd_pcm_init() != 0){

        qDebug() << "snd_pcm_init:failed" << __FILE__ << __FUNCTION__ << __LINE__;
        return;
    }
    // buf = malloc(buf_bytes);
    // if(0 == buf){
    //     qDebug() << "malloc:failed" << __FILE__ << __FUNCTION__ << __LINE__;
    //     snd_pcm_close(pcm); //关闭pcm设备
    //     //close(fd); //关闭打开的音频文件
    //     return;
    // }
//    play_wav();

 

}

int MC_multimedia::snd_pcm_init()
{
    snd_pcm_hw_params_t *hwparams ;
    int ret;

    
    /* 打开PCM设备 */
    ret = snd_pcm_open(&pcm, PCM_PLAYBACK_DEV, SND_PCM_STREAM_PLAYBACK, 0);
    if (0 > ret) {
        fprintf(stderr, "snd_pcm_open error: %s: %s\n", PCM_PLAYBACK_DEV, snd_strerror(ret));
        //return -1;
    }
    /* 实例化hwparams对象 */
    snd_pcm_hw_params_malloc(&hwparams);

    /* 获取PCM设备当前硬件配置,对hwparams进行初始化 */ 
    ret = snd_pcm_hw_params_any(pcm, hwparams);
    if (0 > ret) {
        fprintf(stderr, "snd_pcm_hw_params_any error: %s\n", snd_strerror(ret));
        goto err2;
    }

    /************** 设置参数 ***************/
    /* 设置访问类型: 交错模式 */
    ret = snd_pcm_hw_params_set_access(pcm, hwparams, SND_PCM_ACCESS_RW_INTERLEAVED);
    if (0 > ret) {
        fprintf(stderr, "snd_pcm_hw_params_set_access error: %s\n", snd_strerror(ret));
        goto err2;
    }
    /* 设置数据格式: 有符号16位、小端模式 */
    ret = snd_pcm_hw_params_set_format(pcm, hwparams, SND_PCM_FORMAT_S16_LE);
    if (0 > ret) {
        fprintf(stderr, "snd_pcm_hw_params_set_format error: %s\n", snd_strerror(ret));
        goto err2;
    }

    /* 设置采样率 */
    ret = snd_pcm_hw_params_set_rate(pcm, hwparams, wav_fmt.SampleRate, 0);
    if (0 > ret) {
        fprintf(stderr, "snd_pcm_hw_params_set_rate error: %s\n", snd_strerror(ret));
        goto err2;
    }
    /* 设置声道数: 双声道 */
    ret = snd_pcm_hw_params_set_channels(pcm, hwparams, wav_fmt.NumChannels);
    if (0 > ret) {
        fprintf(stderr, "snd_pcm_hw_params_set_channels error: %s\n", snd_strerror(ret));
        goto err2;
    }
    /* 设置周期大小: period_size */
    ret = snd_pcm_hw_params_set_period_size(pcm, hwparams, period_size, 0);
    if (0 > ret) {
        fprintf(stderr, "snd_pcm_hw_params_set_period_size error: %s\n", snd_strerror(ret));
        goto err2;
    }
    /* 设置周期数（驱动层buffer的大小）: periods */
    // ret = snd_pcm_hw_params_set_periods(pcm, hwparams, periods, 0);
    // if (0 > ret) {
    //     fprintf(stderr, "snd_pcm_hw_params_set_periods error: %s\n", snd_strerror(ret));
    //     goto err2;
    // }
    /* 使配置生效 */
    ret = snd_pcm_hw_params(pcm, hwparams); snd_pcm_hw_params_free(hwparams);
    //释放hwparams对象占用的内存
    if (0 > ret) { fprintf(stderr, "snd_pcm_hw_params error: %s\n", snd_strerror(ret));
        goto err1;
    }
    buf_bytes = period_size * wav_fmt.BlockAlign; //变量赋值，一个周期的字节大小
    return 0;
err2: snd_pcm_hw_params_free(hwparams); //释放内存
err1: snd_pcm_close(pcm); //关闭pcm设备
      return -1;

}

int MC_multimedia::open_wav_file(const char *file)
{
    RIFF_t wav_riff;
    DATA_t wav_data;
    int ret,pcmfd =-1;

    pcmfd = open(file, O_RDONLY);
    if (0 > pcmfd) {
        fprintf(stderr, "open error: %s: %s\n", file, strerror(errno));
        return -1;
    }
    /* 读取RIFF chunk */
    ret = read(pcmfd, &wav_riff, sizeof(RIFF_t));
    if (sizeof(RIFF_t) != ret) {
        if (0 > ret) perror("read error");
        else fprintf(stderr, "check error: %s\n", file);
        close(pcmfd); return -1;
    }
    if (strncmp("RIFF", wav_riff.ChunkID, 4) ||//校验
            strncmp("WAVE", wav_riff.Format, 4)) {
        fprintf(stderr, "check error: %s\n", file);
        close(pcmfd);
        return -1;
    }
    /* 读取sub-chunk-fmt */
    ret = read(pcmfd, &wav_fmt, sizeof(FMT_t));
    if (sizeof(FMT_t) != ret) {
        if (0 > ret) perror("read error");
        else fprintf(stderr, "check error: %s\n", file);
        close(pcmfd);
        return -1;
    }
    if (strncmp("fmt ", wav_fmt.Subchunk1ID, 4)) {//校验
        fprintf(stderr, "check error: %s\n", file); close(pcmfd);
        return -1;
    }
    /* 打印音频文件的信息 */
    printf("<<<<音频文件格式信息>>>>\n\n");
    printf(" file name: %s\n", file);
    printf(" Subchunk1Size: %u\n", wav_fmt.Subchunk1Size);
    printf(" AudioFormat: %u\n", wav_fmt.AudioFormat);
    printf(" NumChannels: %u\n", wav_fmt.NumChannels);
    printf(" SampleRate: %u\n", wav_fmt.SampleRate);
    printf(" ByteRate: %u\n", wav_fmt.ByteRate);
    printf(" BlockAlign: %u\n", wav_fmt.BlockAlign);
    printf(" BitsPerSample: %u\n\n", wav_fmt.BitsPerSample);
    /* sub-chunk-data */
    if (0 > lseek(pcmfd, int(sizeof(RIFF_t) + 8 + wav_fmt.Subchunk1Size), SEEK_SET)) {
        perror("lseek error");
        close(pcmfd);
        return -1;
    }
    while(sizeof(DATA_t) == read(pcmfd, &wav_data, sizeof(DATA_t))) {
        /* 找到sub-chunk-data */
        if (!strncmp("data", wav_data.Subchunk2ID, 4))//校验
        {
            
            //snd_pcm_init();
           buf_bytes = period_size * wav_fmt.BlockAlign; //变量赋值，一个周期的字节大小
            // if(sizeof(buf))
            //     free(buf);
            buf = malloc(buf_bytes);
            printf("音频文件打开成功 pcmfd = %d\n",pcmfd);
            return pcmfd;
        }
            
        if (0 > lseek(pcmfd, int(wav_data.Subchunk2Size), SEEK_CUR)) {
            perror("lseek error");
            close(pcmfd);
            return -1;
        }
    }
    fprintf(stderr, "check error: %s\n", file);
   
    return pcmfd;

}
/*==================================================================================
* 函 数 名： MC_multimedia::play_voice
* 参    数： None
* 功能描述:  play touch key voice
* 返 回 值： None
* 备    注： None
* 作    者： Thomas yang
==================================================================================*/
int MC_multimedia::play_wav(int pcmfd)
{
    int ret = 0;
    printf("play_wav pcmfd = %d,buf_bytes = %d\n",pcmfd,buf_bytes);
    for( ; ; ){

        memset(buf,0x00,buf_bytes);
        ret = read(pcmfd,buf,buf_bytes);
        if(ret <= 0){
            close(pcmfd);
            free(buf);
            goto err3;
        }
reapeat:
        ret = snd_pcm_writei(pcm,buf,period_size);
        if(ret == 0){
            break;
        }else if(ret < 0){
            snd_pcm_prepare(pcm);
            goto reapeat;
        }
//        qDebug() << "snd_pcm_writei ret:"<< ret;
//        if(ret <= 0){
//            fprintf(stderr, "snd_pcm_writei error: %s\n", snd_strerror(ret));
//            qDebug() << "snd_pcm_writei error";
//            goto err3;
//        }else if(ret < int(period_size)){
//            qDebug() << "snd_pcm_writei < preiod_size";
//            if(0>lseek(fd,(ret-period_size)*wav_fmt.BlockAlign,SEEK_CUR)){
//                perror("lseek error");
//                goto err3;
//            }

//        }

    }
err3:
//    free(buf);
//    snd_pcm_close(pcm);
//    snd_pcm_init();
//    close(fd);
//    snd_pcm_prepare(pcm);
//    snd_pcm_reset(pcm);
//    snd_pcm_drain(pcm);
//    snd_pcm_pause(pcm,1);
    lseek(pcmfd,0,SEEK_SET);
    return 0;
}

