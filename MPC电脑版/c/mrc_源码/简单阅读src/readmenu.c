//��������(6369)

#include "mrc_base.h"
#include "menu.h"
#include "readmenu.h"
#include "read.h"
#include "type.h"
#include "win.h"
#include "filefind.h"
#include "BK.h"
#include "LINESIZE.h"
#include "JUMP.h"
#include "msgbox.h"
//#define FONT 1
PMenu a1,a2,a3,a4,a5,nowm;//���˵�����ת�����ã����������壬��ǰ�˵����
//int32 zw,zh;

int menuInit(void)
{

a1=menuCreate(0, SCRH-zh-(zh*6+4), zw*3+20,zh*6+4,6);
setMenuItem(a1,0,"Ŀ¼");
setMenuItem(a1,1,"����");
setMenuItem(a1,2,"��ת  >");
setMenuItem(a1,3,"����  >");
setMenuItem(a1,4,"����  >");
setMenuItem(a1,5,"�˳�");


a2=menuCreate(zw*3+20,SCRH-zh-(zh*3+4),zw*4+20,zh*3+4,3);
setMenuItem(a2,0,"��ת");
setMenuItem(a2,1,"�ļ���ʼ");
setMenuItem(a2,2,"�ļ���β");


a3=menuCreate(zw*3+20,SCRH-zh-(zh*5+4),zw*3+20,zh*5+4,5);
setMenuItem(a3,0,"ȫ��");
setMenuItem(a3,1,"Ƥ��");
setMenuItem(a3,2,"�о�");
setMenuItem(a3,3,"�߿�");
setMenuItem(a3,4,"����  >");

a4=menuCreate(zw*3+20, SCRH-zh-(zh*2+4),zw*2+20,zh*2+4,2);
setMenuItem(a4, 0, "����");
setMenuItem(a4, 1, "����");


a5=menuCreate((zw*3+20)+(zw*3+20),SCRH-zh-(zh*3+4),zw*3+20,zh*3+4,3);
setMenuItem(a5,0,"С����");
setMenuItem(a5,1,"������");
setMenuItem(a5,2,"������");


nowm=a1;
return 0;
}

void drawreadmenu(void)
{
menuDraw(nowm);
showToolBar(0,SCRH-zh
,SCRW,zh,btupclr,btdownclr,MAKERGB(qclr.r,qclr.g,qclr.b),"ȷ��","","����");
refs();
}


void menuExit(void)
{
menuDel(a1);
menuDel(a2);
menuDel(a3);
}


int menuEvent(int type,int p1,int p2)
{
if(type==MR_KEY_PRESS)
{
switch(p1)
{
case MR_KEY_DOWN:
menuFocusNext(nowm,1);
refs();
break;
case MR_KEY_UP:
menuFocusNext(nowm,0);
refs();
break;
}
}
if(type==MR_KEY_RELEASE)
{

switch (p1)
{
case MR_KEY_RIGHT:
case MR_KEY_SOFTLEFT:
case MR_KEY_SELECT:
_sleft();
break;
case MR_KEY_LEFT:
case MR_KEY_SOFTRIGHT:
_sright();
break;
}
}
return 0;
}

void refs()
{
mrc_refreshScreen(0,0,SCRW,SCRH);
}

int _sleft()
{
if(nowm==a1)
{
switch(getMenuFocus(nowm))
{
case 0:
win=WIN_FILEFIND;
//menuExit();
DrawMain();
nowm=a1;
break;
case 1:
win=WIN_READ;
sek=nsek-1;
downPaiBan();
nowm=a1;
break;
case 2:
nowm=a2;
menuDraw(nowm);
refs();
break;

case 3:
nowm=a3;
menuDraw(nowm);
refs();
break;
case 4:
	nowm=a4;
	menuDraw(nowm);
	refs();
	break;

case 5:

mrc_exit();
break;
}
return 0;
}
if(nowm==a2)
{
switch(getMenuFocus(nowm))
{
case 0:
win=WIN_INJUMP;
inJumpInit();
nowm=a1;
break;
case 1:
win=WIN_READ;
sek=0;
downPaiBan();
nowm=a1;
break;
case 2:
win=WIN_READ;
sek=size-40;
downPaiBan();
nowm=a1;
break;
}
nowm=a1;
return 0;
}
if(nowm==a3)
{
switch(getMenuFocus(nowm))
{
case 0:
win=WIN_READ;
//menuExit();
huanPin();
sek=nsek;
downPaiBan();
nowm=a1;
break;
case 1:
win =WIN_READ;
//menuExit();
huanFu();
sek=nsek;
downPaiBan();
nowm=a1;
break;
case 2:
win=WIN_INLINESIZE;
inLineSizeInit();
nowm=a1;
break;
case 3:
win=WIN_INBK;
inBKInit();
nowm=a1;
break;
case 4:
	nowm=a5;
	menuDraw(nowm);
	refs();
	break;
}

return 0;
}
if(nowm==a4)
{
switch(getMenuFocus(a4))
{
case 0:
	//break;
case 1:
	showMsgBox("����������Ʒ");
	mrc_sleep(800);
	win=WIN_READ;
	nowm = a1;
	sek = nsek;
	downPaiBan();
	break;
}
}

if(nowm==a5)
{
switch(getMenuFocus(a5))
{
case 0:
	win = WIN_READ;
	FONT = 0;
	nowm=a1;
	sek = nsek;
	downPaiBan();
	
	break;
case 1:
	win = WIN_READ;
	sek = nsek;
	nowm=a1;
	FONT = 1;
	downPaiBan();
	
	break;
case 2:
	win = WIN_READ;
	FONT = 2;
	nowm=a1;
	sek=nsek;
	downPaiBan();
	

	break;

}
}
return 0;
}


int _sright()
{
if(nowm==a5)
{mrc_drawRect(nowm->x,nowm->y,nowm->w,nowm->h,bclr.r,bclr.g,bclr.b); nowm=a3;menuDraw(nowm);refs();return 0;}
if(nowm==a4)
{mrc_drawRect(nowm->x,nowm->y,nowm->w,nowm->h,bclr.r,bclr.g,bclr.b); nowm=a1;menuDraw(nowm);refs();return 0;}
if(nowm==a3)
{ 
mrc_drawRect(nowm->x,nowm->y,nowm->w,nowm->h,bclr.r,bclr.g,bclr.b); nowm=a1;menuDraw(nowm);refs();return 0;}
if(nowm==a2)
{ mrc_drawRect(nowm->x,nowm->y,nowm->w,nowm->h,bclr.r,bclr.g,bclr.b); nowm=a1;menuDraw(nowm);refs();return 0;}
if(nowm==a1)
{win=WIN_READ;
sek=nsek;
downPaiBan();
return 0;}
return 0;
}
