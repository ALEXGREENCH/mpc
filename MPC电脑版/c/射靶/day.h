#ifndef MPC_DAY_H
#define MPC_DAY_H

#define FONT 1
//�����С

#define REF ref(0,0,SCRW,SCRH)
//ˢ�º�

#define text(txt,x,y,r,g,b) dtext(txt,x,y,r,g,b,FALSE,FONT)
//���ֺ�

int tw,th;
textwh("־",FALSE,FONT,&tw,&th);
//��õ�ǰ�����µ����ֿ��

//�˳�����
void dawExit()
{
 drect(0,SCRH/2,SCRW,th,255,255,250);
 drect(1,SCRH/2+1,SCRW-2,th-2,0,0,0);
 text("by:ÿ�����һ��",tw,SCRH/2,255,255,255);
 for(int x;x<=SCRW;x+=2)
 ref(0,SCRH/2,x,th);
 

}

void rect_text(char *txt,int x,int y,int w,int h,int r,int g,int b)
{
 rectst rect; 
 colorst color;
 rect.x=x;
 rect.y=y;
 rect.w=w;
 rect.h=h;

 color.r=r;
 color.g=g;
 color.b=b;

dtextex(txt,rect.x,rect.y,&rect,&color,2,FONT);
}


void about()
{
cls(255,255,255);
drect(1,1,SCRW-2,SCRH-2,0,0,0);
char *txt="MPC�������Ϸ
by:ÿ�����һ��
date:2012,6.26��
QQ:643552878
����:wap.mrpej.com
˵��:�κ��˲��ò���ͬ�⣬�����ޱ����򣡱�д�д���bug�������⣡�������
����������룡
";
rect_text(txt,0,0,SCRW,SCRH,255,100,255);
rect_text(txt,1,1,SCRW,SCRH,25,255,100);

 for(int h=10;h<=SCRH;h+=5+h/5)
 ref(0,0,SCRW,h);
 REF;
}
#endif

//by:ÿ�����һ��