/*
��˫�������ļ����
by:ÿ�����һ��
1������б�0ֱ�Ӽ��˳���
����֮������������
*/

#include <base.h>

#define FONT 1
//����
#define MAXLEN 250
//�����ļ�����󳤶�

#define MAXFILENUM 300
//�����ļ������

#define MoveTime 1
//�����ƶ�ʱ����

int tw,th;
textwh("��",FALSE,FONT,&tw,&th);
//��ȡ���ֿ��

colorst TextColor;//������ɫ
TextColor.r=250;
TextColor.g=250;
TextColor.b=250;

colorst BgColor;//����ɫ
BgColor.r=40;
BgColor.g=20;
BgColor.b=40;


void text(char *str,int16 x,int16 y)
{
 dtext(str,x,y,TextColor.r,TextColor.g,TextColor.b,FALSE,FONT);
}

//�ļ�����ṹ
typedef struct listst
{
 struct listst *last;//��1��
 struct listst *next;//��1��
 char *name;//�ļ���
 uint8 mode;//�ļ�����
 uint32 len;//�ļ�����
}LISTST;
uint32 ListLen=sizeof(LISTST);//�ļ�����1�����ĳ���

LISTST *First,*End;//ǰĿ¼�ļ�����ͷ����β

struct 
{
 LISTST *now;//��ǰ���
 LISTST *one;//��ǰǰ��Ļ��1�����
 char *dir;//��ǰĿ¼
 uint32 all;//Ŀ¼�ļ���
 uint32 num;//��ǰ�ļ���
 uint32 onenum;//��ǰ��Ļ��1������ļ���
}Focus;
 Focus.dir="";
int32 timer=timercreate();//������ʱ�����

uint16 TextH=th*2;//һ���ļ������ο��
uint16 Textx=tw;//�ļ���x
uint16 Texty=th*2;//�ļ���y
uint16 HowH=SCRH-th*2;//��Ļ�ļ��б���ο��
uint32 HowDraw=HowH/TextH;//��ʾ�ļ���

//��ʹ������ͷ
void ListStart()
{
 if(First!=NULL)
 free(First);
 First=malloc(ListLen);
 memset(First,NULL,ListLen);
 
}

//����Ŀ¼
void FindPath()
{
 ListStart();
 LISTST *to=First;

 char *buffer=malloc(MAXLEN+ListLen);

 uint32 f=findstart(Focus.dir,buffer,MAXLEN);
 findnext(f,buffer,MAXLEN);

 while(Focus.all<=MAXFILENUM)
 {
 memset(buffer,NULL,MAXLEN);
 if(-1==findnext(f,buffer,MAXLEN))
 break;

//����1�����
 LISTST *one;
 one=malloc(ListLen);
 memset(one,NULL,ListLen);

//�������д�����
 uint32 len=strlen(buffer)+ListLen;
 one->name=malloc(len);
 strncpy(one->name,buffer,len);
//��ȡ�ļ����͡�����
 char *str=malloc(strlen(Focus.dir)+strlen(one->name)+2);
 sprintf(str,"%s/%s",Focus.dir,one->name);
 one->mode=filestate(str);
 if(one->mode==IS_FILE)
 one->len=getlen(str);
 else if(one->mode==IS_DIR)
 one->len=strlen(str);
 free(str);

//��������
 one->last=to;
 to->next=one;
 to=to->next;
 Focus.all++;
 }
 findstop(f);
 free(buffer);

 End=to;
}

void FindFile()
{
 ShowMsg("Loading...");
 Focus.num=Focus.all=0;

 FindPath();

 if(Focus.all<1)
 {
  ShowMsg("���ļ���");
  sleep(500);
  event(KY_DOWN,_SRIGHT,NULL);
  return;
 }
 Focus.num=1;
 First=First->next;
 DelPoint(First->last);
 Focus.now=First;
}

//���б�
void DrawList()
{
 if(Focus.all<=0)
 return;
//�汳��
 cls(BgColor.r,BgColor.g,BgColor.b);
 shaderect(0,0,SCRW,th,52643440,0,0);
 shaderect(0,SCRH-th,SCRW,th,52643440,0,0);

//��Ŀ¼���ļ�������Ϣ
 if(Focus.now->mode==IS_DIR)
 {
  if(strlen(Focus.dir)>1)
 text(Focus.dir,0,0);
  else text("File View",0,0);
 }
 else if(Focus.now->mode==IS_FILE)
 {
 char lenStr[16];
 sprintf(lenStr,"%d.%02dkb",Focus.now->len/1024,Focus.now->len%1024);
 text(lenStr,0,0);
 }
//�� ��ǰ�ļ���/���ļ��� ��Ϣ
  char Str[13];
  sprintf(Str,"%d/%d",Focus.num,Focus.all);
  text(Str,SCRW-strw(Str),0);
  text("��",0,SCRH-th);
  text("����",SCRW-tw*2,SCRH-th);
 //DrawTime((SCRW-tw*2)/2,SCRH-th,TextColor.r,TextColor.g,TextColor.b);

//���������ʾ
 switch(1)
 {
  case (Focus.num==1):
  Focus.onenum=Focus.num;
  Focus.one=Focus.now;
  break;
  case (Focus.num==Focus.all):
 Focus.onenum=Focus.num;
 Focus.one=Focus.now;
 while(Focus.onenum+HowDraw-1!=Focus.all)
  {
  if(Focus.one->last!=NULL)    Focus.one=Focus.one->last;
  else break;
  Focus.onenum--;
  }
  break;
  case (Focus.onenum+HowDraw==Focus.num):
  Focus.onenum++;
  Focus.one=Focus.one->next;
  break;
  case (Focus.num==Focus.onenum-1):
  Focus.onenum=Focus.num;
  Focus.one=Focus.now;
  break;
 }

//���ļ��б�
 LISTST *to=Focus.one;
 uint32 n;

 rectst rect;
 rect.x=Textx;
 rect.y=th+th/2;
 rect.w=SCRW-10;
 rect.h=th*3;

 while(n<HowDraw)
 {
  if(to==Focus.now)
  {
  shaderect(0,rect.y,rect.w,TextH,13158600,3289850,0);
  dtextex(to->name,rect.x,rect.y,&rect,&TextColor,2,FONT);
  }
 else
 text(to->name,rect.x,rect.y);
 effsetcon(rect.x,rect.y+TextH,rect.w,1,128,128,128);
 rect.y+=TextH;n++;
 if(to->next!=NULL)
 to=to->next;
 else break;
 }

//�Ҳ������
 uint32 zx=SCRW-10,zy,zw=10,zh;
 if(Focus.all>NULL)
 zh=HowH/Focus.all;
 zy=Focus.num*zh+th-zh;
 drect(zx,th,1,HowH,0,0,0);
 shaderect(zx+1,zy,zw,zh,179250,216640,1);

 ref(0,0,SCRW,SCRH);
}

//����ļ��б�
void PrintList()
{
 printf("\n��ǰĿ¼: %s\n",Focus.dir);
 LISTST *to=First;
 uint32 n=1;
 while(to!=NULL)
 {
  printf("%d.%s,len=%d\n",n,to->name,to->len);
  to=to->next;
  n++;
 }
}

//ɾ�������ļ�����
void DelAll()
{
 LISTST *now=First;
 while(now->next!=NULL)
 {
  now=now->next;
  DelPoint(now->last);
 }
}

void DelPoint(LISTST *one)
{
 free(one->name);
 free(one);
 one=NULL;
}

//��ں���
int init()
{
 FindFile();
 DrawList();
 return 0;
}

//������ں���
int event(int type, int p1, int p2)
{
 if(KY_DOWN==type)
 switch(p1)
  {
 case _0:
 exitapp();break;

 //����б�
 case _1:
 ShowMsg("���Ժ�");
 PrintList();
 ShowMsg("���");
 sleep(500);
 DrawList();
 break;

 //��Ŀ¼
 case _SLEFT:
 case _SELECT:
 if(Focus.now->mode==IS_DIR)
 {
 uint32 len=strlen(Focus.dir)+strlen(Focus.now->name)+2;
 char *str=malloc(len);
 sprintf(str,"%s/%s",Focus.dir,Focus.now->name);
 if(Focus.dir!=NULL)
 free(Focus.dir);
 Focus.dir=str;

 DelAll();
 FindFile();
 DrawList();
 }
 else
 {
  ShowMsg("�����ļ���");
  sleep(500);
  DrawList();
 }
 break;

//�����ϼ�Ŀ¼�������ϼ�Ŀ¼���˳�
 case _SRIGHT:
 if(Focus.dir=="")
 exitapp();
 char *str=strrchr(Focus.dir,'/');
 if(str!=NULL)
 if(strlen(Focus.dir)>1)
 {
 uint32 l=strlen(str);
 memset(Focus.dir+strlen(Focus.dir)-l,NULL,l);

 DelAll();
 FindFile();
 DrawList();
 }
 else exitapp();
 break;

 case _UP:
 case _DOWN:
 LongMove(p1);
 timerstart(timer,MoveTime,p1,"LongMove",1);
 break;
 }
 else if(type==KY_UP)
 switch(p1)
 {
  case _UP:
  case _DOWN:
  timerstop(timer);
  break;
 }
 return 0;
}

//ƽ̨��ͣ����
int pause(void)
{
 return 0;
}
//ƽ̨�ָ�����
int resume(void)
{
    return 0;
}

//�˳�
void exitapp()
{
 ShowMsg("�˳��С�");
 timerdel(timer);
 free(Focus.dir);
 DelAll();
 exit();
}

void LongMove(int p1)
{
 if(Focus.all<1)
 return;

 switch(p1)
 {
  case _UP:
  if(Focus.num>1)
  {
   Focus.num--;
   Focus.now=Focus.now->last;
  }
  else
  {
   Focus.num=Focus.all;
   Focus.now=End;
  }
  break;

  case _DOWN:
  if(Focus.num<Focus.all)
 {
  Focus.num++;
  Focus.now=Focus.now->next;
 }
 else
 {
  Focus.num=1;
  Focus.now=First;
 }
  break;
 }

 DrawList();
}


/*����Ϣ��ʾ*/
void ShowMsg(char *Msg)
{
 int w,h;uint16 x,y;
 textwh(Msg,FALSE,FONT,&w,&h);
 if(w<SCRW)x=(SCRW-w)/2;
 y=(SCRH-h)/2;
 effsetcon(x,y,w,h,50,50,50);
 dtext(Msg,x,y,255,255,250,FALSE,FONT);
 ref(x-5,y-5,w+10,h+10);
}

//��ȡ�ִ���
int strw(char *str)
{
 int w,h;
 textwh(str,FALSE,FONT,&w,&h);
 return w;
}

//��ȡ�ִ��߶�
int strh(char *str)
{
 int w,h;
 textwh(str,FALSE,FONT,&w,&h);
 return h;
}


typedef struct
{
 uint16 year;
 uint8  month;
 uint8  day;
 uint8  hour;
 uint8  minute;
 uint8  second;
} datetime;

//��ʱ��
void DrawTime(int16 x,int16 y,uint8 r,uint8 g,uint8 b)
{
 datetime date;
 getdatetime(&date);
 char da[7];
 memset(da,NULL,7);
 sprintf(da,"%d:%02d",date.hour,date.minute,date.second);
 dtext(da,x,y,r,g,b,FALSE,FONT);
}