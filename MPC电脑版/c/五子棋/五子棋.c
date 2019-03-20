/*������
by:ÿ�����һ��
QQ:643552878
E��ID:47241
�������:2012.7.17

*/

#include <base.h>
#include <c/������/day.h>
#include "c/������/win.h"

#define W 12
//������

#define H 16
//���и���

int Wlen=SCRW/W;
int Hlen=SCRH/H;
//ÿ�����ӵĿ���

#define anV 100
//�������


//���ṹ��
typedef struct
{
 int timer[2];
/*��ʱ�����
timer[0]Ϊ������ʱ�����
timer[1]Ϊ���������ʱ��
*/
 int x;
 int y;
//����xy

 int x2;
 int y2;
//����ƶ�ǰ��xy

 int color;
/*��Ҫ�µ��������
1Ϊ���壬2Ϊ����
*/
}M;  M *Move;

 int8 Q[W][H];
/*0����
  1����
  2����
*/


//��ʼ��
void start()
{
 cls(0,0,0);
 text("��ʼ��",SCRW/2-tw,SCRH/2,255,255,0);
 REF;sleep(500);
 
 if(Move!=NULL)
{ timerdel(Move->timer[1]);
 free(Move);
}

 Move=malloc(sizeof(M));
 memset(Q,NULL,sizeof(int8)*W*H);
 Move->x=Move->y=0;
 Move->color=1;
 Move->timer[0]=timercreate();
 Move->timer[1]=timercreate();
}

uint8 jm=0;
/*
�������
0���ڽ���
1���̽���
*/

int init()
{
 kz();
 return 0;
}


int inits()
{
 start();
 daw();
 return 0;
}

void kz()
{
 switch(jm)
{ case 0:about();break;
 case 1:inits();break;
}

}

int event(int type,int p1,int p2)
{
 switch(jm)
{  case 0:
 aboutEvent(type,p1,p2);
 break;
  case 1:
 chessEvent(type,p1,p2);break;
}

return 0;
}

int aboutEvent(int type,int p1,int p2)
{
 if(type==KY_UP)
 {jm=1;kz();}

 return 0;
}

int chessEvent(int type, int p1, int p2)
{
 if(KY_DOWN==type)
 {
 switch(p1)
 {
   case _SRIGHT:
  exitapp();break;

 case _0:inits();break;

 case _2:case _UP:
 case _8:case _DOWN:
 case _4:case _LEFT:
 case _6:case _RIGHT:
 an(p1);//�̰�
 timerstart(Move->timer[0],anV,p1,"an",1);
 //����
 break;

  case _SELECT:
  case _5:
 int x=Move->x,y=Move->y;

 if(Q[x][y]==NULL)
 //�統ǰλ�����壬����
 {
 Q[x][y]=Move->color;

 if(win())
 dawWin(Move->color);
//����Ƿ�����������

 if(Move->color==2)
 Move->color=1;
 else Move->color=2;
//���������:�컻�ڣ��ڻ���

}
 break;
   }
  }

else if(type==KY_UP)
{ 
 switch(p1)
 {
 case _2:case _UP:
 case _8:case _DOWN:
 case _4:case _LEFT:
 case _6:case _RIGHT:
 timerstop(Move->timer[0]);break;
 //������̧��ֹͣ��ʱ��
 }
 }
 return 0;
}

//�˳�ǰ
void exitapp()
{
 if(Move!=NULL)
{ timerdel(Move->timer[1]);
 free(Move);
}
 dawExit();
 exit();
}
 //������ʱ������
void an(int p1)
{
if(p1)
{ Move->x2=Move->x;
 Move->y2=Move->y;
}
//�����δ�ƶ�ǰ��xy�����¼


 switch(p1)
 {
 case _2:case _UP:
 if(Move->y>0)Move->y--;
 else Move->y=H-1;
 break;

 case _8:case _DOWN:
 if(Move->y<H-1)Move->y++;
 else Move->y=0;
 break;

 case _4:case _LEFT:
 if(Move->x>0)Move->x--;
 else Move->x=W-1;
 break;

 case _6:case _RIGHT:
 if(Move->x<W-1)Move->x++;
 else Move->x=0;
 break;
 }


//////
 int r=128,g=224,b=224;
 int x=Move->x2,y=Move->y2;

 if(Q[x][y]==1)
 {r=255;g=b=0;}
 else if(Q[x][y]==2)
 {r=g=b=0;}

 drect(Move->x2*Wlen+1,Move->y2*Hlen+1,Wlen-1,Hlen-1,r,g,b);

//���ƶ�ǰ���λ�������ӣ��������
/////

 if(Move->color==1)
 {r=255;g=b=0;}
 else if(Move->color==2)
 {r=g=b=0;}
 drect(Move->x*Wlen+1,Move->y*Hlen+1,Wlen-1,Hlen-1,r,g,b);
//������

 REF;
}

int pause(void)
{return 0;}
int resume(void)
{return 0;}


//������ͼ
void daw()
{
 cls(128,224,224);
 for(int n=0;n<=SCRW;n+=Wlen)
{ dline(n,0,n,SCRH,255,255,255);
 REF;
}
 for(n=0;n<=SCRH;n+=Hlen)
{ dline(0,n,SCRW,n,255,255,255);
 REF;
}
 REF;an(0);
 timerstart(Move->timer[1],500,NULL,"dodo",1);
}


int Ms=1;
//�����˸
void dodo(int a)
{
 Ms=!Ms;
 int r=128,g=224,b=224;
 if(Ms)
 {
  if(Move->color==1)
  {r=255;g=b=0;}
  else if(Move->color==2)
  {r=g=b=0;}
  else if(Move->color==0)
 {r=128;g=b=244;}
}
 drect(Move->x*Wlen+1,Move->y*Hlen+1,Wlen-1,Hlen-1,r,g,b);
REF;
}


//����ֽ��
void dawWin(int color)
{
 char *txt;
 
 if(color==1)
txt="����ʤ��";
 else if(color==2)
 txt="����ʤ��";

 effsetcon(0,SCRH/2,SCRW,th,128,128,128);
 text(txt,SCRW/2-tw,SCRH/2,255,255,255);
 REF;
 sleep(1000);
 init();//��ʼ��
}



void about()
{
 cls(255,255,255);
 drect(1,1,SCRW-2,SCRH-2,0,0,0);
 
char *txt="����:
������
by:ÿ�����һ��
QQ:643552878
E��ID:47241
2012.7.17 
0����ʼ����֧�ֳ�����
˵��:�κ��˲��ò���ͬ�⣬�����ޱ�����
����������룡
";
rect_text(txt,0,0,SCRW,SCRH,25,255,255);
//rect_text(txt,1,1,SCRW,SCRH,250,25,25);

 REF;
}

//by:ÿ�����һ��