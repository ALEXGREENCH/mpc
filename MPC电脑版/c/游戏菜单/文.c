#include <base.h>
#include "c/��Ϸ�˵�/���.h"
#define FONT 1
//����

//������ɫ
#define R 155
#define G 255
#define B 255

//����ͼƬ
#define cdbei "c/��Ϸ�˵�/�˵�����.jpg"

#define REF ref(0,0,SCRW,SCRH)
//ˢ��

//���ֺ�
#define text(txt,x,y) dtext(txt,x,y,R,G,B,0,FONT)

//�˵�ѡ�����
#define cd_big 4

//�˵�����
char *cd[cd_big]={"��ʼ��Ϸ","��Ϸ����","��Ϸ����","��Ϸ�˳�"};

int potion=1;
int jm=0;
/*0���˵�,>1��Ϸ����,>2����,>3����.>4�˳�*/

int tw,th;
textwh("��",FALSE,FONT,&tw,&th);

int init()
{
 kz();
 return 0;

}

int event(int type, int p1, int p2)
{
 if(KY_DOWN == type&&!jm)
  switch(p1)
  {
  case _SRIGHT:
 jm=4;kz();
  break;

 case _SLEFT:
 if(potion<5)
 jm=potion;
 kz();break;

 case _6:
 case _RIGHT:
 if(potion<cd_big)potion++;
 else potion=1;
 kz();
  break;

 case _4:
 case _LEFT:
 if(potion>1)potion--;
 else potion=cd_big;
 kz();
 break;
  }

else if(jm==1)
game_event(type,p1,p2);
//��Ϸ����

else
if(type==KY_DOWN&&(jm==2||jm==3))
 switch(p1)
{ case _SRIGHT:
 jm=0;kz();break;
}
else
if(KY_DOWN==type&&jm==4)
 switch(p1)
{
 case _SRIGHT:
 jm=0;kz();
 break;

 case _SLEFT:
 exitapp();
}

    return 0;
}

int pause(void)
{return 0;}
int resume(void)
{
 kz();
 return 0;}

void exitapp()
{
  exit();

}

void kz()
{
switch(jm)
 {
 case 0:hui_cd();break;
 case 1:game();break;
 case 2:about();break;
 case 3:help();break;
 case 4:yesexit();break;
 }

}
void hui_cd()
{
 cls(10,10,10);
 img(cdbei,0,0);
 int H=SCRH-th;
 drect(0,th,SCRW,1,R/2,G/2,,B/2);
 text("�˵�",SCRW/2-tw,0);
 drect(0,H,SCRW,1,R/2,G/2,B/2);
 text("ȷ��",0,H);
 text("�˳�",SCRW-tw*2,H);
 time(SCRW/2-tw,H);

 char *txt=malloc(strlen(cd[potion-1])+4);
 sprintf(txt,">%s<",cd[potion-1]);

 text(txt,(SCRW-textw(txt))/2,SCRH-th*3);
 free(txt);
 REF;
}
int textw(char *txt)
{
 int w,h;
 textwh(txt,FALSE,FONT,&w,&h);
 return w;
}
void yesexit()
{
 effsetcon(0,0,SCRW,SCRH,138,138,138);
 int H=SCRH-th*2;
 drect(0,H,SCRW,th*2,10,10,10);
 drect(0,H,SCRW,1,R/2,G/2,B/2);
text("ȷ���˳�?",tw,H);
text("�˳�",0,H+th);
text("����",SCRW-tw*2,H+th);
 REF;
}


//��Ϸ�����ͼ
void game()
{cls(10,10,10);
 img(cdbei,0,0);
 int r=R/2,g=G/2,b=B/2;
 drect(0,th,SCRW,1,r,g,b);
 text("��δ��ӣ�",SCRW/2-tw*2,0);
 drect(0,SCRH-th,SCRW,1,r,g,b);
 text("����",SCRW-tw*2,SCRH-th);
 REF;
}


void game_event(int type,int p1,int p2)
{
 if(type==KY_DOWN)
 switch(p1)
 {
 case _SRIGHT:
 jm=0;kz();break;
 }

}


//by:ÿ�����һ��