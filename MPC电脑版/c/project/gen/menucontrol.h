//wildly �˵��ؼ�

#ifndef MENU_CONTROL_H
#define MENU_CONTROL_H

#include <base.h>

//�˵�����������
#define menu_text_size 100

#define SH Texh+10

//�˵��ṹ��
typedef struct
{
   char *text[300];  int br;
   int now;  int bg;
   int num; int bb;
   int gn;  int fr;
   int gf;  int fg;
   int mx;  int fb;
   int my;  int tr;
   int mw;  int tg;
   int mh;  int tb;
}pmenu;

typedef pmenu *Menu;

//�����˵��õ����顣
//����һ���˵� num�˵������
void *MenuCreate(int x,int y,int w,int h,int num)
{Menu a=malloc(sizeof(pmenu));
if(a==NULL)return NULL;
memset(a,0,sizeof(pmenu));
  a->mx=x;
  a->my=y;
  a->mw=w;
  a->mh=h;
  a->num=(num<=300?num:300);
for(int N=0;N<num;N++)
{a->text[N]=malloc(menu_text_size);
if(a->text[N]==NULL)return NULL;
memset(a->text[N],0,menu_text_size);}
MenuRgbSet(a,90,90,90,100,100,200);
MenutRgbSet(a,200,200,200);
a->gn=h/SH;
return a;}

//���ò˵��� item�˵������� n�˵���˳��
int MenuSet(Menu a,char *item,int n)
{if(a==NULL)return -1;
if(n>=(a->num) || n<0)return -1;
strcpy(a->text[n],item);
return 0;}

//��ʾ�˵�
int MenuShow(Menu a)
{if(a==NULL)return -1;
int i,y;
drect(a->mx,a->my,a->mw,a->mh,a->br,a->bg,a->bb);
for(i=a->gf;i<(a->gf)+(a->gn);i++)
{
if(i>a->num-1)break;
if(i==a->now)
drect(a->mx,y,a->mw,SH,a->fr,a->fg,a->fb);
dtext(a->text[i],a->mx+5,y+5,a->tr,a->tg,a->tb,0,FONT);
y+=SH;
}
ref(a->mx,a->my,a->mw,a->mh);
return 0;}

//�˵����� is 0�� 1��
int MenuEvent(Menu a,int is)
{if(a==NULL)return -1;
if(a->num==0)return -1;
int num=a->num,gn=a->gn,gf=a->gf,now=a->now;
     if(is)
        {
   if(now < num-1)
      {now++;
if(now-gf == gn)
gf++;
   }
else {now=0; gf=now;}

}else
 {
      if(now > 0)
        {now--;
if(now-gf == -1)
gf--;
         }
else {now=num-1; gf=num-gn; if(gf < 0)gf=0;}
    }
a->now=now;
a->gf=gf;
return 0;}


//ɾ���˵����˳�ʱ����
int MenuDel(Menu a)
{
if(a==NULL)return -1;
for(int N=0;N<(a->num);N++)
free(a->text[N]);
free(a);
return 0;}

//���ò˵���ɫb rgb������ɫ,f rgb�˵�����ɫ
int MenuRgbSet(Menu a,int br,int bg,int bb,int fr,int fg,int fb)
{if(a==NULL)return -1;
  a->br=br;
  a->bg=bg;
  a->bb=bb;
  a->fr=fr;
  a->fg=fg;
  a->fb=fb;
return 0;
}

//���ò˵���������ɫ
int MenutRgbSet(Menu a,int tr,int tg,int tb)
{if(a==NULL)return -1;
  a->tr=tr;
  a->tg=tg;
  a->tb=tb;
return 0;
}

//��ȡ�˵�����
int getMenuFocus(Menu a)
{if(a==NULL)return -1;
int focus=a->now;
return focus;}

#endif