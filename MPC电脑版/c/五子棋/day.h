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

#endif

//by:ÿ�����һ��