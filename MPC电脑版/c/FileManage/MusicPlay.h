/*
* MusicPlay(�����ֲ�����)
* By:����
* Date:2012.8.28
* �ӿ�:
 ��ʼ�� MPInit(char *name);
 ������� MPEvent(int type,int p1,int p2);
* ����:��(2)����(8)���Ӽ�����������(5)�� ��ͣ/���š�0��ֹͣ���š�
*/

#include <sound.h>
//����
#define MFONT 1

enum
{
_MIDI=1, _WAVE, _MP3, _AMR, _PCM, _M4A, _AMR_WB
};

typedef struct
{
 int32 pos;
}T_DSM_AUDIO_POS;

//����״̬
enum
{
Is_Play=0,//������
Is_Pause,//��ͣ
Is_Stop//ֹͣ
};

//����״̬�ַ���
char* GetPlayStateStr(int type)
{
char *PlayStateStr[3]={"������","��ͣ","ֹͣ"};
 return PlayStateStr[type];
}

struct PMusic
{
 int timer;//��ʱ�����
 char *name;//�ļ�·��
 int8 type;//������������
 int8 state;//����״̬
 int8 block;//����(ѭ��)ģʽ
 int8 volume;//����(0~5)
 int8 loop;//����ѭ��ģʽ
 int totaltime;//������ʱ��
 int curtime;//��ʱ����ʱ��
};

//��ȡ�����ļ�����
int GetMusicKind(char *FileName)
{
 char *str=strrchr(FileName,'.');
 switch(0)
 {
 case strcmp(str,".mp3"):
 return _MP3;
 break;
 case strcmp(str,".amr"):
 return _AMR;
 break;
 case strcmp(str,".mid"):
 return _MIDI;
 break;
 case strcmp(str,".wave"):
 return _WAVE;
 break;
 case strcmp(str,".m4a"):
 return _M4A;
 break;
 case strcmp(str,".pcm"):
 return _PCM;
 break;
 }
 return -1;
}

struct PMusic *PM;

/*��ʹ�����,FileName:�����ļ������ɹ�����0��ʧ�ܷ���-1*/
int MPInit(char *FileName)
{
 if(getlen(FileName)<0)
 return -1;
 int t=GetMusicKind(FileName);
 if(-1==t)
 return -1;

 int l=sizeof(struct PMusic);
 PM=(struct PMusic*)malloc(l);
 memset(PM,NULL,l);

 int len=strlen(FileName);
 PM->name=(char*)malloc(len);
 strcpy(PM->name,FileName);

 PM->timer=timercreate();
 PM->type=t;
 PM->block=0;
 PM->loop=1;
 PM->state=Is_Play;
 PM->volume=1;
 soundinit(PM->type);//�򿪲����豸
soundloadfile(PM->type,PM->name);//�����ļ�
 soundplay(PM->type,PM->block,PM->loop);//����
 PM->totaltime=GetMusicTime(PM->type,1);//������ʱ��
 setvolume(PM->volume);//��������
 timerstart(PM->timer,500,500,"PMtimer",1);
 return 0;
}

//�˳�
int PMExit()
{
 timerdel(PM->timer);
 soundstop(PM->type);//ֹͣ
 soundclose(PM->type);//�رղ����豸
 free(PM->name);
 free(PM);
 BackFV();
 return 0;
}

//��ʱ���������
void PMtimer(int p1)
{
 PM->curtime=GetMusicTime(PM->type,0);//��ȡ����ʱ��
 PMDraw();
}

//�����Ž���
void PMDraw()
{
 cls(120,245,230);
 char *str=(char*)malloc(200);
 sprintf(str,"���ֲ�����\n%s\n%d:%d %d:%d\n%s ����:%d",PM->name,(PM->curtime)/60,(PM->curtime)%60,(PM->totaltime)/60,(PM->totaltime)%60,GetPlayStateStr(PM->state),PM->volume);

 colorst *clr=malloc(3);
 memset(clr,0,3);
 rectst *rect=malloc(8);
 memset(rect,0,8);
 rect->w=SCRW;
 rect->h=SCRH;
 dtextex(str,0,0,rect,clr,2,MFONT);
 free(str);
 free(clr);
 free(rect);
 ref(0,0,SCRW,SCRH);
}

/*��ȡ����ʱ��(��S)
* type:�豸����
* is_alltime:ȡ��ֵ���ز�����ʱ�䡢���򷵻��Ѳ���ʱ��
*/
int GetMusicTime(int32 type,int is_alltime)
{
 uint8 *p;
 if(is_alltime)
 getsoundtotaltime(type,&p);
 else
 getsoundcurtime(type,&p);
 if(p==NULL)return 0;
 return (int)(*p);
}

//�������
int MPEvent(int type,int p1,int p2)
{
 if(KY_DOWN==type)
 switch(p1)
 {
 case _SRIGHT:
 PMExit();
 break;

 case _0:
 if(PM->state!=Is_Stop)
 {
 soundstop(PM->type);
 PM->state=Is_Stop;
 timerstop(PM->timer);
 PM->curtime=0;
 PMDraw();
 }
 break;

 case _5:
 case _SELECT:
 if(PM->state==Is_Stop)
 {
 soundplay(PM->type,PM->block,PM->loop);
 timerstart(PM->timer,500,500,"PMtimer",1);
 PM->state=Is_Play;
 }
 else
 if(PM->state==Is_Pause)
 {
 PM->state=Is_Play;
 soundresume(PM->type);
 timerstart(PM->timer,500,500,"PMtimer",1);
 }
 else
 {
 soundpause(PM->type);
 timerstop(PM->timer);
 PM->state=Is_Pause;
 }
 PMDraw();
 break;

 case _2:
 case _UP:
 if(PM->volume<5)
 {
 PM->volume++;
 setvolume(PM->volume);
 PMDraw();
 }
 break;

 case _8:
 case _DOWN:
 if(PM->volume>0)
 {
 PM->volume--;
 setvolume(PM->volume);
 PMDraw();
 break;
 }

 }
 return 0;
}


//���ò���ʱ��(ms)
void SetPlayTime(int type,int time)
{
 T_DSM_AUDIO_POS *p=malloc(sizeof(T_DSM_AUDIO_POS));
 p->pos=time;
 setplaytime(type,p);
 free(p);
}

//By:����