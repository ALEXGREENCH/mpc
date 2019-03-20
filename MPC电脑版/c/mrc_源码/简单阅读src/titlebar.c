
//��������(6369)
//create date 2012-7-17

#include "mrc_base.h"
#include "type.h"
#include "titlebar.h"


/*����������
x,y,w,h ����λ�ô�С
upclr �������ϲ���ɫ
downclr �²���ɫ
titclr ������ɫ
title ��������
����ֵ ָ���������ָ��
*/

PTitle titleBarCreate(int x,int y,int w,int h,int32 upclr,int32 downclr,int32 titclr,char* title)
{
PTitle a;
a=mrc_malloc(sizeof(Title));
if(a==NULL) return 0;
a->x=x;
a->y=y;
a->w=w;
a->h=h;
a->upclr=upclr;
a->downclr=downclr;
a->titclr=titclr;
a->title=title;
return a;
}

/*ɾ��������*/

void titleBarDel(PTitle a)
{
mrc_free(a);
a=0;
}


/*���Ʊ�����*/

void drawTitleBar(PTitle a)
{
int32 zw,zh;
mrc_textWidthHeight(a->title,0,FONT,&zw,&zh);
shaderect(a->x,a->y,a->w,a->h,a->upclr,a->downclr,0);

mrc_drawText(a->title,a->x+2,a->y+(a->h-zh)/2,MAKER(a->titclr),MAKEG(a->titclr),MAKEB(a->titclr),0,FONT);
}

