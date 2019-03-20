
#ifndef mrporting_h
#define mrporting_h

/*����ֻ�ƽ̨û�ж�����������ͣ���#if ����ڵĶ�����Ч*/
#if 1
typedef  unsigned short     uint16;      /* Unsigned 16 bit value */
typedef  unsigned long int  uint32;      /* Unsigned 32 bit value */
typedef  long int  int32;      /* signed 32 bit value */
typedef  unsigned char        uint8;        /* Signed 8  bit value */
typedef  signed char        int8;        /* Signed 8  bit value */
typedef  signed short       int16;       /* Signed 16 bit value */
#endif


enum {
   MR_KEY_0,               //���� 0
   MR_KEY_1,               //���� 1
   MR_KEY_2,               //���� 2
   MR_KEY_3,               //���� 3
   MR_KEY_4,               //���� 4
   MR_KEY_5,               //���� 5
   MR_KEY_6,               //���� 6
   MR_KEY_7,               //���� 7
   MR_KEY_8,               //���� 8
   MR_KEY_9,               //���� 9
   MR_KEY_STAR,            //���� *
   MR_KEY_POUND,           //���� #
   MR_KEY_UP,              //���� ��
   MR_KEY_DOWN,            //���� ��
   MR_KEY_LEFT,            //���� ��
   MR_KEY_RIGHT,           //���� ��
   MR_KEY_POWER,           //���� �һ���
   MR_KEY_SOFTLEFT,        //���� �����
   MR_KEY_SOFTRIGHT,       //���� �����
   MR_KEY_SEND,            //���� ������
   MR_KEY_SELECT,          //���� ȷ��/ѡ����������м���ȷ�ϼ���������Ϊ�ü���
   MR_KEY_VOLUME_UP,          //���� �����
   MR_KEY_VOLUME_DOWN,          //���� �����
   MR_KEY_CLEAR,
   MR_KEY_NONE             //���� ����
};

enum {
   MR_NET_ID_MOBILE,                  //�ƶ�
   MR_NET_ID_CN,          // ��ͨgsm
   MR_NET_ID_CDMA,       //��ͨCDMA
   MR_NET_ID_NONE       //δ�忨
};

enum {
   MR_EDIT_ANY,                  //�κ��ַ�
   MR_EDIT_NUMERIC,          // ����
   MR_EDIT_PASSWORD       //���룬��"*"��ʾ
};

enum {
   MR_SIM_NEW,     //���ֻ���һ�β���SIM��
   MR_SIM_CHANGE, //�û�����SIM��
   MR_SIM_SAME    //δ���л�������
};

enum {
   MR_DIALOG_OK,                   //�Ի�����"ȷ��"����
   MR_DIALOG_OK_CANCEL,
   MR_DIALOG_CANCEL
};

enum {
   MR_DIALOG_KEY_OK,
   MR_DIALOG_KEY_CANCEL
};

enum {
   MR_KEY_PRESS,
   MR_KEY_RELEASE,
   MR_MOUSE_DOWN,
   MR_MOUSE_UP,
   MR_MENU_SELECT,
   MR_MENU_RETURN,
   MR_DIALOG_EVENT,
   MR_SMS_INDICATION,
   MR_EXIT_EVENT,
   MR_SMS_RESULT
};

typedef enum 
{
   MR_SOUND_MIDI,
   MR_SOUND_WAV,
   MR_SOUND_MP3,
   MR_SOUND_AMR,
   MR_SOUND_PCM    //8K
}MR_SOUND_TYPE;

typedef enum 
{
   MR_FONT_SMALL,
   MR_FONT_MEDIUM,
   MR_FONT_BIG
}MR_FONT_TYPE;

enum
{
   MR_SEEK_SET, 
   MR_SEEK_CUR, 
   MR_SEEK_END
};

enum
{
   MR_SOCK_STREAM,
   MR_SOCK_DGRAM
};

enum
{
   MR_IPPROTO_TCP,
   MR_IPPROTO_UDP
};

enum
{
   MR_ENCODE_ASCII,
   MR_ENCODE_UNICODE
};

#define   MR_SMS_ENCODE_FLAG   7
#define   MR_SMS_REPORT_FLAG   8
#define   MR_SMS_RESULT_FLAG   16

enum {
   MR_SOCKET_BLOCK,          //������ʽ��ͬ����ʽ��
   MR_SOCKET_NONBLOCK       //��������ʽ���첽��ʽ��
};

typedef struct
{
   uint16 year;                 //��
   uint8  month;                //��
   uint8  day;                  //��
   uint8  hour;                 //ʱ��24Сʱ��
   uint8  minute;               //��
   uint8  second;               //��
}mr_datetime;

typedef struct
{
   uint32 width;                  //��Ļ��
   uint32 height;                 //��Ļ��
   uint32 bit;                    //��Ļ������ȣ���λbit
}mr_screeninfo;

typedef struct
{
	uint8       IMEI[16];	      //IMEI len eq 15
	uint8       IMSI[16];	      //IMSI len not more then 15
	char        manufactory[8];  //�����������7���ַ������ֽ���\0
	char        type[8];         //mobile type�����7���ַ������ֽ���\0
	uint32      ver;            //SW ver
	uint8       spare[12];       //����
}mr_userinfo;

typedef struct
{
   int32 socket;
   int32 port;
}mr_bind_st;



#ifdef MR_FS_ASYN

typedef int32 (*MR_ASYN_FS_CB)(int32 result, uint32  cb_param);

typedef struct
{
   void* buf;                 //�ļ������ַ
   uint32  buf_len;                //���峤�ȣ���Ҫ��ȡ/д��ĳ���
   uint32  offset;               //�ļ���ȡ/д��ƫ��
   MR_ASYN_FS_CB  cb;      //�ص�����
   uint32  cb_param;               //�ص�����
}mr_asyn_fs_param;
#endif


#if 0 //ȡ��
typedef struct
{
   uint32 mr_head;                 //Mythroad�ļ���ǩ
   uint32 mri_len;                   //Ӧ����Ϣͷ����
   uint32 app_len;                  //Ӧ�ó���
   uint32 appid;                      //Ӧ��ID
   char    filename[12];          //Ӧ���ļ���
   uint16 appname[20];          //Ӧ������Unicode
   uint16 appversion[10];          //Ӧ�ð汾��Unicode
   uint16 vendor[20];             //��������Ϣ��Unicode
   uint16 description[40];      //Ӧ��������Unicode
   char    mrdata[32];            //Ӧ������
}mr_appSt;
#endif

#define MR_FILE_RDONLY     1//��ֻ���ķ�ʽ���ļ���
#define MR_FILE_WRONLY     2//��ֻд�ķ�ʽ���ļ���
#define MR_FILE_RDWR       4//�Զ�д�ķ�ʽ���ļ���
#define MR_FILE_CREATE      8//����ļ������ڣ��������ļ���

#define MR_IS_FILE     1      //�ļ�
#define MR_IS_DIR      2      //Ŀ¼
#define MR_IS_INVALID  8  //��Ч(���ļ�����Ŀ¼)


#define MR_FILE_HANDLE int32
#define MR_SEARCH_HANDLE int32

#define MR_SUCCESS  0    //�ɹ�
#define MR_FAILED   -1    //ʧ��
#define MR_IGNORE   1     //������
#define MR_WAITING   2     //�첽(������)ģʽ
//#define MR_NO_SUPPORT   -2     //��֧��

#define MR_PLAT_VALUE_BASE 1000    //����ĳЩ����ֵ�Ļ���ֵ



/*��ʱ������ʱ���ö�ʱ���¼���Mythroadƽ̨����֮���д���
p��������ʱ��ʱ�����Mythroad��ʱ������*/
extern int32 mr_timer(void);
/*��Mythroadƽ̨�ж԰����¼����д���press	= MR_KEY_PRESS�������£�
= MR_KEY_RELEASE�����ͷţ�key	��Ӧ�İ�������*/
extern int32 mr_event(int16 type, int32 param1, int32 param2);
/*�˳�Mythroad���ͷ������Դ*/
extern int32 mr_stop(void);


/****************�ⲿ�ӿڶ���*********************/


#if 0 //��ȡ��
/*������MythroadӦ�õ�ʱ��Ӧ�õ���Mythroad�ĳ�ʼ��������
���Զ�Mythroadƽ̨���г�ʼ����������Mythroadƽ̨������ָ
����Ӧ�ã�appָ��Ҫ���е���Ϸ��Ӧ�õ���������*/
extern int32 mr_start(mr_appSt* app);
#endif

/*������DSMӦ�õ�ʱ��Ӧ�õ���DSM�ĳ�ʼ��������
���Զ�DSMƽ̨���г�ʼ��*/
extern int32 mr_start_dsm(const char* entry);

/*ע��̻�Ӧ��*/
extern int32 mr_registerAPP(uint8 *p, int32 len, int32 index);

#if 0 //��ȡ��
/*ȡ��Ӧ���б�
   appList:ָ���Ѿ���װδ��װӦ���б�ĵ�һ��Ԫ��
   appLen:Ӧ�õĸ���
   ע��:appList��ָ����ڴ�ռ�����ɵ��ô˺����ĳ���Ա
   �ͷ�
*/
extern int32 mr_getAppList(mr_appSt** appList, uint32* appLen);

/*ȡ��Ӧ��˵��*/
void mr_getAppInfo(char* info, mr_appSt *app);

/*ɾ��ָ����Ӧ��
app:��Ӧ�õ�����ָ��
*/
extern int32 mr_uninstall(mr_appSt *app);
#endif

/*��ͣӦ��*/
extern int32 mr_pauseApp(void);

/*�ָ�Ӧ��*/
extern int32 mr_resumeApp(void);

/*���ֻ��յ�����Ϣʱ���øú���*/
extern int32 mr_smsIndiaction(uint8 *pContent, int32 nLen, uint8 *pNum, int32 type);

/*���������ݣ��������ڴ����е�һ�����ص��ļ��������жϣ�
�������ļ���DSM�˵�����DSM����������ļ����б��档ʹ��
������ʱ�������ļ�Ӧ���Ѿ�������ȫ������ȫ�����ݱ�����
�������ڴ��С�*/
extern int32 mr_save_mrp(void *p,uint32 l);

/*����ͬmr_save_mrp�����������һ���򿪵��ļ�������ļ���
�����߹رա��ú���Ŀǰ��δʵ�֣�����Ҫʹ�ã�����ϵouli*/
extern int32 mr_save_mrp_with_handle(MR_FILE_HANDLE f);

/*�û�SIM�����*/
extern int32 mr_newSIMInd(int16  type, uint8* old_IMSI);

/*����mr_initNetworkʹ�õĻص���������*/
typedef int32 (*MR_INIT_NETWORK_CB)(int32 result);

/*����mr_initNetworkʹ�õĻص���������*/
typedef int32 (*MR_CONNECT_CB)(int32 result);

/*����mr_getHostByNameʹ�õĻص���������*/
typedef int32 (*MR_GET_HOST_CB)(int32 ip);


/****************�ⲿ�ӿڶ���*********************/







/*********************�����ǳ���ӿڶ���******************************/





/*���Դ�ӡ*/
extern void mr_printf(const char *format,...);


/*�ڴ�����*/
extern int32 mr_mem_get (char** mem_base, uint32* mem_len);
/*�ڴ��ͷ�*/
extern int32 mr_mem_free (char* mem, uint32 mem_len);


/*******************************************************************/
/*��ʹ�ñ�����Ļ����ʱʹ�õĽӿ�*/
/*����Ļ�ϻ�BMP*/
extern void mr_drawBitmap(uint16* bmp, int16 x, int16 y, uint16 w, uint16 h);
/*ȡ�û�ȡunicode��chָ�������ĵ�����Ϣ������֮
������Ŀ�͸ߣ���ȡ���ĵ�����Ϣÿһ��bit��ʾ
�����һ�����أ�����ÿ�е����ر��밴�ֽڶ��䣬
Ҳ����˵���һ�������Ϊ12������Ҫ�������ֽ�
����ʾ����Ϣ���ڶ����ֽڵĺ��ĸ�bitΪ0���ӵ���
���ֽڿ�ʼ�ű�ʾ��һ�еĵ�������*/
extern const char *mr_getCharBitmap(uint16 ch, uint16 fontSize, int *width, int *height);
/*******************************************************************/

#if 0
/*******************************************************************/
/*��ʹ�ó�����Ļ����ʱʹ�õĽӿ�*/
/*��ʾ�ַ�������Ļ���������Ͻ�Ϊx,y��color��RGB��ɫ*/
extern void mr_drawText(char * pcText, int16 x, int16 y, uint32 color);
/*����ʾ����������ʾ�豸��ͼ����²��������·�Χ���Ͻ�Ϊx,y��
���Ϊw,h*/
extern void mr_bufToScreen(int16 x, int16 y, uint16 w, uint16 h);
/*ȡ����Ļ������ָ��*/
extern void* mr_getScreenBuf(void);
/*******************************************************************/
#endif


/*������ʱ��*/
extern int32 mr_timerStart(uint16 t);
/*ֹͣ��ʱ����*/
extern int32 mr_timerStop(void);
/*ȡ��ʱ�䣬��λms*/
extern uint32 mr_getTime(void);
/*��ȡϵͳ����ʱ�䡣*/
extern int32 mr_getDatetime(mr_datetime* datetime);
/*ȡ���ֻ������Ϣ��*/
extern int32 mr_getUserInfo(mr_userinfo* info);
/*����˯�ߣ���λms*/
extern int32 mr_sleep(uint32 ms);
/*ƽ̨��չ�ӿ�*/
extern int32 mr_plat(int32 code, int32 param);
/*��ǿ��ƽ̨��չ�ӿ�*/
typedef void (*MR_PLAT_EX_CB)(uint8* output, int32 output_len);
extern int32 mr_platEx(int32 code, uint8* input, int32 input_len, uint8** output, int32* output_len, MR_PLAT_EX_CB *cb);


/*�ļ���Ŀ¼����*/
extern int32 mr_ferrno(void);
extern MR_FILE_HANDLE mr_open(const char* filename,  uint32 mode);
extern int32 mr_close(MR_FILE_HANDLE f);
extern int32 mr_info(const char* filename);
extern int32 mr_write(MR_FILE_HANDLE f,void *p,uint32 l);
extern int32 mr_read(MR_FILE_HANDLE f,void *p,uint32 l);
extern int32 mr_seek(MR_FILE_HANDLE f, int32 pos, int method);
extern int32 mr_getLen(const char* filename);
extern int32 mr_remove(const char* filename);
extern int32 mr_rename(const char* oldname, const char* newname);
extern int32 mr_mkDir(const char* name);
extern int32 mr_rmDir(const char* name);


/*�첽�ļ���д�ӿ�*/
#ifdef MR_FS_ASYN
extern int32 mr_asyn_read(MR_FILE_HANDLE f, mr_asyn_fs_param *param);
extern int32 mr_asyn_write(MR_FILE_HANDLE f, mr_asyn_fs_param *param);
#endif

/*Ŀ¼������ʼ*/
extern MR_SEARCH_HANDLE mr_findStart(const char* name, char* buffer, uint32 len);
/*ȡ��һ��Ŀ¼�������*/
extern int32 mr_findGetNext(MR_SEARCH_HANDLE search_handle, char* buffer, uint32 len);
/*Ŀ¼��������*/
extern int32 mr_findStop(MR_SEARCH_HANDLE search_handle);

/*�˳�ƽ̨*/
extern int32 mr_exit(void);

/*��ʼ�ֻ���*/
extern int32 mr_startShake(int32 ms);
/*�����ֻ���*/
extern int32 mr_stopShake(void);

/*������Ƶ����*/
extern int32 mr_playSound(int type, const void* data, uint32 dataLen, int32 loop);
/*ֹͣ������Ƶ*/
extern int32 mr_stopSound (int type);

/*����һ������Ϣ*/
extern int32 mr_sendSms(char* pNumber, char*pContent, int32 flags);
/*����绰*/
extern void mr_call(char *number);
/*ȡ������ID��0 �ƶ���1 ��ͨ*/
extern int32 mr_getNetworkID(void);
/*����WAP*/
extern void mr_connectWAP(char* wap);


/*GUI �ӿ�*/
extern int32 mr_menuCreate(const char* title, int16 num);
extern int32 mr_menuSetItem(int32 menu, const char *text, int32 index);
extern int32 mr_menuShow(int32 menu);
/*����ѡ����Ŀ������*/
extern int32 mr_menuSetFocus(int32 menu, int32 index);
extern int32 mr_menuRelease(int32 menu);
extern int32 mr_menuRefresh(int32 menu);



extern int32 mr_dialogCreate(const char * title, const char * text, int32 type);
extern int32 mr_dialogRelease(int32 dialog);
extern int32 mr_dialogRefresh(int32 dialog, const char * title, const char * text, int32 type);

extern int32 mr_textCreate(const char * title, const char * text, int32 type);
extern int32 mr_textRelease(int32 text);
extern int32 mr_textRefresh(int32 handle, const char * title, const char * text);

extern int32 mr_editCreate(const char * title, const char * text, int32 type, int32 max_size);
extern int32 mr_editRelease(int32 edit);
extern const char* mr_editGetText(int32 edit);

extern int32 mr_winCreate(void);
extern int32 mr_winRelease(int32 win);

extern int32 mr_getScreenInfo(mr_screeninfo * screeninfo);


/*Socket�ӿ�*/
extern int32 mr_initNetwork(MR_INIT_NETWORK_CB cb, const char *mode);
extern int32 mr_closeNetwork(void);
extern int32 mr_getHostByName(const char *name, MR_GET_HOST_CB cb);
extern int32 mr_socket(int32 type, int32 protocol);
extern int32 mr_connect(int32 s, int32 ip, uint16 port, int32 type);
extern int32 mr_closeSocket(int32 s);
extern int32 mr_recv(int32 s, char *buf, int len);
extern int32 mr_recvfrom(int32 s, char *buf, int len, int32 *ip, uint16 *port);
extern int32 mr_send(int32 s, const char *buf, int len);
extern int32 mr_sendto(int32 s, const char *buf, int len, int32 ip, uint16 port);

extern int32 mr_plat(int32 code, int32 param);
extern int32 mr_platEx(int32 code, uint8* input, int32 input_len, uint8** output, int32* output_len, MR_PLAT_EX_CB *cb);


/*HXH:�����ӿ�*/
extern int32 mr_sdk(int code, int param);//�ڴ���ʾ
#define CHECK_EVENT  1    //�¼�����
#define CHECK_MEM  2
#define CHECK_TIMER  4
#define CHECK_FILE 8
#define CHECK_SOCKET  16
#define CHECK_PLAX  32
#define CHECK_UI  64

char* _get_filename1(const char *filename) ;
char* _get_filename(const char *filename) ;
void reStartres(int32 flag);
void INSIDETRACE(int32 ID,const char *format,...);
#endif
