#ifndef UTILS_H__
#define UTILS_H__
#include  <stdio.h>
#include  <stdlib.h>
#include <sys/types.h>          /*  See NOTES */
#include <time.h>
#include <string.h>
#include <errno.h>

#ifndef __DBMSG__
#define __DBMSG__
#define dbmsg(fmt, args ...) printf("%s:%s[%d]: "fmt"\n", __FILE__,__FUNCTION__, __LINE__,##args)
#endif

//语音播放
int alsa_aplay (  char *argv );
#endif
