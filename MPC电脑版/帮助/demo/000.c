#include <base.h>
#include "l:/mythroad/c/windowdef.h"
#include "l:/mythroad/c/windowfunc.h"

wobj *obj;
wwindow *win;

/*�ӿں���*/
void wevent(wwindow *win,wobj *obj,uint8 msg,int p1,int p2)
{
if(obj==NULL&&msg==WESHOW)
 {
echo("Ϊ�˲��䣡",strlen(" "));
 }
else if(obj!=NULL && msg==WEFOCUS)
 {
echo("����id",obj->id);
 }else if(msg==WECLICK)
{echo("������",obj->id);
if(obj->id==10)
 {exitapp();}
}
}
int init(void)
{
int i,tm;
colorst aa,bb,cc;
echo("��ʼ",10086);
tm=getuptime();
wfocus.w=5;
torgb(&wfocus.rgb,0,255,0);
win=wwindowct(1,10,20,180,200);
echo("��ʼ������",(int)win->point.last);
torgb(&aa,0,50,0);
torgb(&bb,50,0,0);
wwindowset(win,&aa,&bb);
for(i=5;i<9;i++){
obj=wobjct(i,win,30,5+(i-5)*50,80,40);
torgb(&aa,250,0,0);
torgb(&bb,0,200,200);
torgb(&cc,250,250,250);
wbuttonset(obj,&aa,&bb,"����",&cc);
}
win->point.now=obj;
obj=wobjct(10,win,120,120,40,80);
wbuttonset(obj,&aa,&bb,"�˳�",&cc);
wwindowshow(win);
echo("ʤ���������ǣ�",getuptime()-tm);
return 0;
}
int event(int type, int p1, int p2)
{
wkey(type,p1,p2);
if(KY_DOWN==type)
{
switch(p1)
{
case _SRIGHT:
 echo("����",0);exitapp();
break;
case _1:
wkey(MS_DOWN,45,30);
 break;
}
}
return 0;
}

int resume(void)
{
if(wnowwindow!=NULL)
{wwindowshow(wnowwindow);}
return 0;
}
int pause(void)
{
if(wnowwindow!=NULL)
{wevent(wnowwindow,0,WEOVERD,0,0);}
return 0;
}

void exitapp()
{
wwindowfree(wnowwindow);
exit();
}

