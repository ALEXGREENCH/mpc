/*
* ������Ļ
* By:����
* ����֮�������Լ���ӡ�
* 2012,8,5
*/


#include <base.h>
#define REF ref(0,0,SCRW,SCRH)

#define Photo "c/������Ļ/����.bmp"

#define BMPW 145
#define BMPH 90

uint16 aW=BMPW/3;


uint16 *scr=getscrbuf(),*tu;

enum
{
 IS_START,
 IS_END
};

int init()
{
 BMPInit();

 DrawStartEnd(IS_START);
 DrawWg();
 return 0;
}

void DrawStartEnd(uint8 SE)
{
 char *s[5]={"��","��","��","Ļ","��"};
 char *s2[5]={"л","л","��","��","��"};
 char **ss=s;
 if(SE==IS_END)ss=s2;
 uint8 n=0,color;

 int x=SCRW-aW,y=SCRH,h=SCRH/50;

 cls(255,255,255);
 for(x=0;x<=SCRW;x+=aW)
 {
 for(y=SCRW;y>(SCRH/3);y-=h)
 {
 drect(x,y+h,aW,BMPH,255,255,255);
 DrawBMP(x,y,color);
 if(n<5)
 ShowRectMsg(ss[n],x,y,aW,BMPH/2); REF;
 y-=h;
 }
 n++;color=rand()%3;
 }

}

void DrawWg()
{
 cls(255,255,255);

 char *s[15]={
"��","��","��","��","��",
"E","��","��","��","��",
"8","��","5","��","��"
};
 uint8 n;

 uint16 x,y;

 for(y=0;y<SCRH;y+=(SCRH/3))
 for(x=0;x<SCRW;x+=aW)
 {
 DrawBMP(x,y,rand()%3);
 if(n<15)
 ShowRectMsg(s[n],x,y,aW,BMPH/2);
 n++;
 REF;sleep(200);
 }
 
}


/*��x,y,w,h ���ο��� ���л���*/
void ShowRectMsg(char *Msg,uint16 x,uint16 y,uint16 w,uint16 h)
{
 int zw,zh;
 textwh(Msg,FALSE,1,&zw,&zh);
 uint16 zx,zy;
 zx=(w-zw)/2+x;
 if(h>zh)zy=(h-zh)/2+y;
 dtext(Msg,zx,zy,0,0,0,FALSE,1);
}


int event(int type, int p1, int p2)
{
 if(KY_DOWN == type)
 {
 switch(p1)
  {
  case _SRIGHT:
  exitapp();break;
  case _1:
  break;
  }
 }
 return 0;
}

int pause(void)
{
 return 0;
}


int resume(void)
{
 return 0;
}

//RGB24λת16λ
#define MAKERGB(r,g,b) (r>>3<<11)+(g>>2<<5)+(b>>3)

void exitapp()
{
 DrawStartEnd(IS_END);
 free(tu);
 exit();
}

//��ȡ����ͼƬ
void BMPInit()
{
 uint32 len=getlen(Photo);
 if(len<=0)
 {
  cls(0,0,0);
  dtext("����ͼƬ��ȡʧ�ܣ�",0,0,255,0,0,FALSE,1);
  REF;
  sleep(2000);
  exit();
 }
 if(tu!=NULL)
 free(tu);
 tu=malloc(len);

 uint32 f=open(Photo,1);
 read(f,tu,len);
 close(f);
}


void DrawBMP(uint16 x,uint16 y,uint8 n)
{
 bmpshowflip(tu,x,y,BMPW,aW,BMPH,BM_TRANS,(n-1)*aW,0,0x00);
}

//By:����