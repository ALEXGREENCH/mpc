#include <base.h>
#include "c/��ʥ��˹��˵/��˵.c"
#include "c/��ʥ��˹��˵/���.h"
#define tu "c/��ʥ��˹��˵/ʥ.bmp"
#define tu2 "c/��ʥ��˹��˵/��.bmp"
#define bmp_person bmpshowflip(person,Cr->x,Cr->y,100,100,125,BM_COPY,0,0,0)

void bmp_guai(int x,int y)
{
bmpshowflip(guai,x,y,100,100,125,BM_COPY,0,0,0);
}

#define cdbei "c/��ʥ��˹��˵/�˵�����.jpg"

#define LV_BIG 50
//��߼�,����

#define FONT 1
//����
#define R 155
#define G 255
#define B 255

#define REF ref(0,0,SCRW,SCRH)
//ˢ��
#define text(txt,x,y) dtext(txt,x,y,R,G,B,0,FONT)




char *cd[4]={"��ʼ��Ϸ","��Ϸ����","��Ϸ����","��Ϸ�˳�"};

int potion=1;
int jm=0;

int tw,th;
textwh("��",FALSE,FONT,&tw,&th);

int init()
{
 game_init();
 kz();
 return 0;

}

int event(int type, int p1, int p2)
{
 if(KY_DOWN == type&&!jm)
  switch(p1)
  {
  case _SRIGHT:  jm=4;kz();
  break;

 case _SLEFT:
 if(potion<5)
 jm=potion;
 kz();break;

 case _6:
 case _RIGHT:
 if(potion<4)potion++;
 else potion=1;
 kz();
  break;

 case _4:
 case _LEFT:
 if(potion>1)potion--;
 else potion=4;
 kz();
 break;
  }
else if(jm==1)
game_event(type,p1,p2);

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
/*
int pause(void)
{return 0;}
int resume(void)
{return 0;}
*/

void exitapp()
{
 exitapp_game();
 exit();

}

void kz()
{
switch(jm)
 {
 case 0:hui_cd();break;
 case 1:game_kz();break;
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