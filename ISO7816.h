

#include "string.h"
#include <stdint.h>
#include <unistd.h>

#define     MATCHCODE_ERR           19//PSAM闁告帗绻傞～鎰板礌閺嶎厽鏅╅悹鍥锋嫹(1.濠㈣泛绉崇紞锟�2.PPS濠㈡儼绮剧憴锟�3.濞戞挴鍋撻柛妤嬬節閳ь剚姘ㄥú鎷屻亹閿燂拷4.閻熸瑱濡囬崑锝夊箳閵夈剱鏇熺▔瀹ュ牆顥�)
#define     CPU_SELFILE_FAIL        20//闂侇偄顦伴弸鍐╃鐠烘亽浜奸悹鎰舵嫹(1.濞戞捁宕靛ú鎷屻亹閿燂拷2.濞戞挴鍋撻柛妤嬬節閳ь剚鑹剧花鏌ユ偨閿燂拷3.闂佽棄宕€垫﹢寮崶锔筋偨)
#define     CPU_READFILE_FAIL       21//閻犲洨绮弸鍐╃鐠烘亽浜奸悹鎰舵嫹(1.闁稿浚鍓欓崣鈩冪┍閳╁啩绱�2.缂侀硸鍨甸鎼佸棘閸ワ附顐�3.閻犱焦婢樼紞锟�)
#define     CPU_REDABALANCE_FAIL    22//閻犲洩顔婄紞鎴烇紣濠靛棎浜奸悹鎰舵嫹
#define		Uncert_State						23//闁告劖鐟ュ畷閬嶅Υ娴ｉ攱鍞夐柡鍕尭閵囨垹鎷归敓锟�
#define     CARD_SAME_ERROR	        24//闂傚牏鍋涢幃鎾寸▔閳ь剙顕ｉ悩鎻掑耿闂佹寧鐟ㄩ锟�(1.閹兼潙绻愰崹顏堝矗閿燂拷2.闁告せ鈧啿绁柛鎺戝槻瑜帮拷)
#define 	GET_PROVE_FAIL		    25//闁告瑦鐗斿锕傚及閹捐鍚囬悹鍥︾閵囨垹鎷归敓锟�
#define     PSAM_MAC1_FAIL		    26//MAC1
#define     PSAM_CHECK_MAC2		    27//MAC2
#define	    PSAM_RESET_ERROR        28//闁告牕缍婇崢銈団偓娑欘殜閺侊拷
#define	    PSAM_FILEPARA_ERR       29//PSAM闂佹寧鐟ㄩ锟�(1.濞戞挴鍋撻柛妤嬬節閳ь剚姘ㄥú鎷屻亹閿燂拷2.闁告瑥鍊归弳鐔烘嫚鐠囨彃绲�3.缂佹梹鐟ч崑锝嗙▔閿燂拷0)
#define		NO_PURSE_ERROR			30 //闂佽棄宕€垫ê鈻介檱椤旀洜绱旈敓锟�
#define		SYS_CONSUM_ESC			31 //闂佽棄宕€垫ê鈻介檱椤旀洜绱旈敓锟�
#define		No_Use					32 //濞戞挸绉撮崢鎴犳媼閸涘⿴鍔冮棅顒夊亗閸炪倕鈽夐崼锝呯€�
#define		No_ip					33 //IP濞戞挶鍨归妵锟�#define		CARD_NOCARD				0xff
  
#define     PSAM_COM_ERROR          0xf1//PSAM闂侇偅淇洪鍡涙煥濞嗘帩鍤�(1.闂傗偓閸喖顔�2.闁哄啰濮撮幖閿嬫償閿燂拷3.闁告繂绉寸花鏌ユ煥濞嗘帩鍤�) 
#define     CPU_WRITEPURSE_FAIL     0xf2//闁告劖鐟ч悿顔炬媼閳ョ偨浜奸悹鎰舵嫹
#define     CONSUM_PROCE_FAIL	    0xf3//濞存嚎鍊栧Σ妤佸緞鏉堫偉袝



char ISO7816_PSAM(unsigned char SendLen, unsigned char * SendBuf, unsigned char * RcvLen, unsigned char * Rcvdata);

uint8_t ReadCardCommonDatas_CPU(void);//闁哄秷顫夊畵渚€宕￠檱椤宕氶幒鏇ㄥ殺闁告瑦娓縋U闁告せ鍓濋弳鐔煎箲閿燂拷

