/*
wildly ���������ؼ�
QQ 319965592
ʹ�÷���:
int event(int type,int p,int pa)
{TimerEvent(type,p);
if(type == KY_DOWN)
{case _SRIGHT:
TimerEventDel();
exit();
break;
}
  }
TimerEventStop(type);
return 0;
} �������¼������Ǽ�����ʱ*/

#include <base.h>

int TimeCreate_Buffer[2]={timercreate(),timercreate()};

typedef struct
{
   int timermax;
   int timerlin;
   uint8 off_on;
   int typef;
   int time;
   int type;
   int p;
}Event;

Event Pe;

//��������
void TimerEvent(int type,int p)
{if(Pe.off_on)break;
if(Pe.typef)break;
Pe.type=type;
Pe.p=p;
timers(0,Pe.timermax,"TimeRun",1);
}

//������
void TimeRun(int pax)
{Stope(0);
timers(1,Pe.timerlin,"TimeTimer",1);
}

//������
void TimeTimer(int pax)
{Pe.typef=1;
event(Pe.type,Pe.p,0);
}

//ֹͣ����
void TimerEventStop(int type)
{if(type == KY_UP)
{Pe.typef=0;
Pe.type=-1;
Pe.p=-1;
Stope(1);
} }

//�����������˳�ʱ��ص���
void TimerEventDel()
{
Pe.type=-1;Pe.p=-1;Pe.typef=1;
Stope(0);Stope(1);
}

/*��������ʱ�䣬timermax��������ʱ��sm��timerlin�������ʱ��sm*/
int TimerEventSet(int timermax,int timerlin)
{
if(!timermax || !timerlin)return -1;
  Pe.timermax=timermax;
  Pe.timerlin=timerlin;
return 0;}

//�������أ�f=0 ON f=1 OFF
void TimerEventOffOn(uint8 f)
{if(f > 1)break;
  Pe.off_on=f;
}

//��ʼ������ʱ��
TimerEventSet(500,100);

//�ؼ�������ʱ��������
void timers(int t,int ms,char *f,int loop)
{
timerstart(TimeCreate_Buffer[t],ms,TRUE,f,loop);
}

//��ʱ��ֹͣ��
void Stope(int t)
{
timerstop(TimeCreate_Buffer[t]);
}