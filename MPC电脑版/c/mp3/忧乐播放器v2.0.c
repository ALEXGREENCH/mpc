/******
����ν����Ʒ��
��0����æ��
*������˳���
#����ͼ��
���Ը�����ͼƬŶ��
���ӵ��棡֧�����棡
��ӭѧϰ����ֹ�Ҹģ�
������úõĻ��ͻ�����һ�¸��������ɣ�

**********/

#include <base.h>
char *list="My Music/";
//��������·��

char *cun="c/mp3/list/";
//���ø����б����ļ��С�
int c=0;
//c=0ʱ�˳�ʱ�Զ�ɾ��cun�ļ��С�
//c=1;��ɾ�����´β������Ѹ裬����ֱ�ӽ��롣

int g_y=1;
int g_s;
char *p=malloc(255);
char *pm=malloc(255);

#define pan"mp3������ v2.0"
#include "c/mp3/mp3_time.h"
//ʱ��ӿ�
#include "c/mp3/mp3_help.h"
//�����ӿ�
#include "c/mp3/mp3.h"
//MP3��ӿ�

int jm=1;
//�������
//1�����桢2�����б����
//3��������


int f=0;//��ʱ�����
int x;//�����ƶ�������
int k;//�ض�ʱ������
int k_d;//���ƶ�ʱ������
int v=0;//��������;

int init()
{
cls(0,0,0);
sog();//��������


int i;
if(getlen("tu.jpg")>0)
img("tu.jpg",0,0);
/*����ͼ�飬�����Ը�
*/
ref(0,0,240,320);

for(i=10;i<=140;i+=10)
{
drect(0,100,240,50,255,255,255);
drect(1,101,238,48,0,0,0);
dtext("�����С�",80,110,255,255,255,0,1);
dtext("����ν������ ��Ʒ",15,155,i,i*2,i,0,1);
effsetcon(0,0,240,320,i,i,i);
drect(0,180,240,2,255,150,5);
ref(0,0,i*2,320);
}

MP3(1);//��mp3�豸
MP3(2);//����mp3
MP3(8);//�����������С
MP3(3);//����
MP3(4);//��ͣ

bf();
return 0;
}

void mp3()
{
cls(0,0,0);
drect(0,0,240,30,255,255,255);
drect(1,1,238,28,55,55,55);

dline(0,30,240,30,255,255,0);
dtext(pan,61,5,210,210,210,0,1);
dtext(pan,61,5,255,255,2,0,1);

drect(0,70,240,150,25,255,255);
drect(1,71,238,148,0,0,0);



drect(0,220,240,140,255,255,0);
drect(1,221,238,138,55,50,50);

drect(1,289,51,25,0,0,0);
dtext("�嵥",0,290,210,210,210,0,1);
drect(189,289,51,25,0,0,0);
dtext("�˳�",190,290,210,210,210,0,1);
drect(99,299,51,26,0,0,0);
time(100,300,0,255,0);
//��ʾʱ��
drect(0,30,240,40,255,255,255);
drect(1,31,238,38,2,2,0);

if(pm==NULL)pm=p;
dtext(strrchr(pm,'/')+1,10,35,5,255,2,0,1);


//����ͼ��
int i;
for(i=255;i<=275;i++)
{dline(70,265,80,i,25,255,255);
dline(160,266,150,i,25,255,255);
}

//����ͼ��
yl(0);




//����ͼ��
for(i=110;i<=130;i++)
{
dline(120,230,i,240,25,255,255);
dline(120,300,i,290,25,255,255);
}
//����ͼ��
if(k==1)
{
drect(100,250,5,30,55,255,0);
drect(130,250,5,30,255,255,0);
}
else if(k==0)
{for(i=250;i<=280;i++)
dline(130,265,110,i,25,255,255);
}


ref(0,0,240,320);
}

void yd()
//�������ƶ�
{

drect(0,30,240,40,250,250,250);
drect(1,31,238,38,0,0,0);

if(pm==NULL)pm=p;
if(x<200)x+=5;
else x=-40;
dtext(pm+8,x,35,x,rand()%255,x,0,1);
dline(x-15,69,x+30,69,x,x-20,x*2);
}

void fg(int data)
//�������
{

if(jm==1)
{

int r,g,b;
r=rand()%265;
g=rand()%265;
b=rand()%265;

int i,y;
drect(0,70,240,150,250,250,250);
drect(1,71,238,148,0,0,0);

for(i=0;i<=240;i+=20)
{
y=rand()%256;
while(y<65)
y=rand()%256;

drect(i,y,15,220-y,r-i,g+i,b);
}
for(i=75;i<=220;i+=10)
dline(0,i,240,i,0,0,0);

yd();
ref(0,0,240,320);

}

}

int bf()
{
mp3();
if(k ==1)
{
f=timercreate();
timerstart(f,500,500,"fg",1);
}
else if(f!=0)
{
timerdel(f);
}
return 0;
}

int event(int type, int p1, int p2)
{
    if(KY_DOWN == type)
 {
switch(p1)
{
case _5:
case _SELECT:

if(k==0&&jm==1)
{MP3(5);//����ͣ����
k=1;bf();}

else if(k==1&&jm==1)
{MP3(4);//��ͣ����
k=0;bf();}
break;

case _0:
if(jm==1)
{jm=3;k=0;bf(); help();}
break;

case _SRIGHT:
if(jm==1)
exitapp(1);
if(jm==2||jm==3)
{k=1;jm=1;bf();}
break;

case _SLEFT: 
if(jm==1)
{ qd();jm=2; }

else if(jm==2)
{
hg();//����
jm=1;
}
break;

case _2:
case _UP:
if(jm==1)yl(2);
else if(jm==2&&g_y>1)
{g_y--;qd();}

break;


case _8:case _DOWN:
if(jm==1)yl(8);
else if(jm==2&&g_y<g_s)
{g_y++;qd();}
break;

/*
case _4:
case _LEFT:
if(jm==1&&g_y>1)
{g_y--;hg();}
break;

case _6:
case _RIGHT:
if(jm==1&&g_y<9)
{g_y++;hg();}
break;
*/
case _POUND:
printscr("c/mp3.bmp");
break;
case _STAR:
exitapp(0);break;
}
}

 return 0;}

int pause(void)
{return 0;}
int resume(void)
{return 0;}
void exitapp(int j)
{
free(p);//�ͷ��ڴ�
free(pm);
MP3(6);//ֹͣ
MP3(7);//�ر�
if(f != 0)timerdel(f);

if(getlen(cun)>0)
{  if(c)cut();}


int i;
if(j==1)
{for(i=140;i>=0;i-=10)
{
drect(0,100,240,50,255,255,255);
drect(1,101,238,48,0,0,0);

effsetcon(0,0,240,320,i,i,i);
dtext("�˳��С�",80,110,255,255,255,0,1);
dtext("����ν������ ��Ʒ",15,155,i,i*2,i,0,1);
drect(0,180,240-i*2,2,250,150,5);
ref(0,0,240-i*2,320);
}
}

exit();
}


void yl(int j)
//�䶯����ͼ��
{

MP3(8);//��������

if(j==2&&v<5)v++;
else if(j==8&&v>0)v--;

drect(1,225,20,50,0,0,0);
drect(220,225,19,50,0,0,0);

drect(1,275-v*10,20,v*10,255,255,0);
drect(220,275-v*10,19,v*10,255,255,0);

ref(0,0,240,320);
}


void hg()
{
pm=p;
MP3(6);//ֹͣ����
find_mp3();
MP3(2);//����
MP3(3);//����
MP3(4);//��ͣ
k=0;
bf();
}


void sog()
{
int a=find();

if(a==0)
{
cls(0,0,0);
dtext("�����Զ������б�",10,100,255,255,0,0,1);
dtext("�����ĵȴ���",60,140,255,25,255,0,1);
ref(0,0,240,320);

g_s=find_write();

cls(0,0,0);
if(g_s==0)
{
dtext("û��������",0,100,255,255,255,0,1);
dtext("��Ѹ�ŵ�ָ��·���ڣ�",0,160,255,255,255,0,1);
sleep(1000);
exitapp(0);

}

int i;char p[5];
dtext("������mp3:",30,160,2,255,0,0,1);
for(i=1;i<=g_s;i++)
{
drect(160,0,240,320,0,0,0);

sprintf(p,"%d��",i);
dtext(p,160,160,255,i*20,255,0,1);
ref(0,0,240,320);
sleep(50);
}

}


ref(0,0,240,320);
sleep(1000);
find_mp3();
pm=p;
}

//��ͼ������ժ��СǮ
void printscr(char *name)
{
uint16 *scrf=getscrbuf();

int f=open(name,12);

write(f,scrf,SCRW*SCRH*2);
close(f);


drect(0,120,240,50,255,255,255);
drect(2,122,236,36,0,0,0);

if(getlen(name) > 0)
dtext("��ͼ�ɹ���",50,130,255,255,0,0,1);
else 
dtext("��ͼʧ�ܣ�",50,130,255,5,25,0,1);
ref(0,0,240,320);

}
