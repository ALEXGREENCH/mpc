/*
* ������¼��
* By:����
* QQ:643552878
* 2012.8.7
* ˵��:������¼������textFile��print.txt�ļ��в鿴
*/

#include <base.h>
#include <c/tt������¼��/tt.h>
#define textFile "c/������¼.txt"

uint32 Filef,time;


struct
{
 int type;//��������
 uint32 downTime;//�������µ�ʱ��
 uint32 upTime;//�����ɿ���ʱ��
}EventMsg;


int init(void)
{
 ShowMsg("��������");
 sleep(1000);
 remove(textFile);
 Filef=open(textFile,8);
 write(Filef,"������¼:\n",10);

 time=getuptime();
 DrawMain();
 ShowMsg("�밴�¼���");

 return 0;
}

int event(int type, int p1, int p2)
{
 if(p1==_SRIGHT)
 {
  exitapp();
  return 0;
 }

 if(type==KY_DOWN)
 {
 EventMsg.type=p1;
 EventMsg.downTime=getuptime();
 writeEventMsg(type);
 }
 else if(type==KY_UP)
 {
  EventMsg.upTime=getuptime();
 writeEventMsg(type);
 }
 return 0;
}

int pause(void)
{
 return 0;
}

int resume(void)
{
 return 0;
}

void exitapp()
{
 ShowMsg("��������");
 sleep(1000);
 close(Filef);



 exit();
}

void DrawMain()
{
 cls(250,250,250);
 drect(0,th-1,SCRW,1,0,0,0);
 Drawtext("������¼��",0,0);

 ref(0,0,SCRW,SCRH);
}

void writeEventMsg(int type)
{
 char str[50];
 if(type==KY_DOWN)
 sprintf(str,"ʱ��=%ds,����ֵ=%d,״̬:����\n",(EventMsg.downTime-time)/1000,EventMsg.type);
 else
 sprintf(str,"ʱ��=%ds,����ֵ=%d,״̬:�ɿ�,����ʱ��=%dms\n",(EventMsg.upTime-time)/1000,EventMsg.type,EventMsg.upTime-EventMsg.downTime);
 DrawEventMsg(str);

 write(Filef,str,strlen(str));
 printf("%s",str);
}