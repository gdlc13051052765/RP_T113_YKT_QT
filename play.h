#ifndef PLAY_H
#define PLAY_H

#include <QString>
#include <qobject.h>
#include <qthread.h>
#include <qmutex.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include <alsa/asoundlib.h>


class Play : public QThread
{
private:
	snd_pcm_t *play_handle = NULL;
	bool doPlay;
	QString pcmName;
    QString wavFileName;
    FILE* pWavFile;

	int samplesize;
	int framesize;
	int channels;
	int rate;
	int periods;
	int periodsize;
	
private:
	snd_pcm_t *open_pcm();
	
	
public:
	Play(void);
	int open_and_print_file_params(char *file_name);
	~Play();
    virtual void run();
        //void Start();
	void Stop();
	void Playback(unsigned char* buffer, int size);
    void SetWavFileName(QString strWavFileName);
	void close_pcm();
};

#endif
