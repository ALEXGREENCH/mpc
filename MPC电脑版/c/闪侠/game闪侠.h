/*
����
by:ÿ�����һ��   С��ͼƬ�ṩ
QQ:643552878��1281132839
2012.5
�������ͣ,������˳�,
�м����ɱ����#����ʼ��
*/
#define FONT 1
#define photo "c/����/jpg/F.jpg"

#define photo_F "c/����/jpg/FF.jpg"  
#define photo_D "c/����/jpg/��.jpg"

int pw=24,ph=24;
//����ͼƬ���
int pw2=15,ph2=15;
//��ͼƬ���
#define game_text(txt,x,y,r,g,b) dtext(txt,x,y,r,g,b,0,FONT)

int LV=10;
//��ʼ������Ļ�谭�������,����̫����,�����ٶȻ������

#define FV 5
//ˢ���ٶ�

#define KY_V 1
//���ٶ�

int *fx,*fy;
//�谭�������

int8 *fv;
//�谭����ٶ�

int ffx,ffy;
//�ɻ�������

//int8 ffv;
//�ɻ����ٶ�,δ����

int8 bxs;
//��ɱ��

//��Ļ�ֻ�
int WK=20;
int HK=20;

//ÿ�ִ�С
int FW=SCRW/WK;
int FH=SCRH/HK;


int32 timer=NULL;
int32 timer_an=NULL;
//��Ϸ��ʱ���Ͱ�����ʱ�����,

int on=NULL;
//��Ϸ״̬
int8 off=NULL;

uint16 *FF,*DD,*scr=getscrbuf();

int game_init()
{
 if(timer)stop();
 if(timer_an)
 timerstop(timer_an);
 on=off=NULL;

 int len=pw*ph*2;
 if(FF!=NULL)free(FF);
 FF=malloc(len);

 int len2=pw2*ph*2;
 if(DD!=NULL)free(DD);
 DD=malloc(len);

 cls(100,200,250);
 img(photo_F,0,0);
 for(int y=0;y<ph;y++)
 memcpy(FF+y*pw,scr+y*SCRW,pw*2);
 cls(100,200,250);
 img(photo_D,0,0);
 for(y=0;y<ph2;y++)
 memcpy(DD+y*pw2,scr+y*SCRW,pw2*2);
  game_inits();
  return 0;
}

//�����ڴ�
void malloc_()
{
 if(fx!=NULL)
 free(fx);
 fx=malloc(LV*4);

 if(fy!=NULL)
 free(fy);
 fy=malloc(LV*4);

 if(fv!=NULL)
 free(fv);
 fv=malloc(LV*4);
}


//��ʼ��
void game_inits()
{ 
 for(int a=SCRW;a>-80;a-=tw/2)
{
 cls(250,250,250);
 img(photo,a,SCRH/2);
 game_text("Loading.......",(SCRW/2)-40,(SCRH/2)+65,255,2*a,50);
 game_text("С��-ÿ�����һ��",a,50,2*a,a,a);
 REF;

 }
 on=1;

 malloc_();
 memset(fx,NULL,LV*4);
 memset(fy,NULL,LV*4);

for(a=0;a<LV;a++)
{ fx[a]=rand_x();
  fy[a]=0;
  fv[a]=rand_v();
}

ffx=FW*(FW/2);
ffy=FH*(HK-1);
//ffv=3;
bxs=5;


if(timer)timerdel(timer);
timer=timercreate();

if(timer_an)timerdel(timer_an);
timer=timercreate();
timer_an=timercreate();
start();


}

int game_event(int type, int p1, int p2)
{
 if(KY_DOWN==type&&!off)
 switch(p1)
 {
  case _SRIGHT:
  stop();
  over();
  break;

 case _SLEFT:
 if(on)stop();
 else start();
 on=!on;
 break;
 
 case _POUND:
 game_inits();break;

 case _SELECT:
 if(on)BX();break;


case _UP:case _DOWN:
case _LEFT:case _RIGHT:
 case _2:case _8:
 case _4:case _6:
 if(on)
{
 ffxy(p1);
 timerstart(timer_an,KY_V,p1,"ffxy",1);
 }
      break;

 }
else if(type==KY_DOWN&&off)
 switch(p1)
{ 
 case _SLEFT:
 jm=0;kz();
 game_exitapp();break;

 case _SRIGHT:
 off=NULL;
 game_inits();break;
}

else
if(type==KY_UP&&!off)
switch(p1)
{
 case _UP:case _DOWN:
 case _LEFT:case _RIGHT:
 case _2:case _8:
 case _4:case _6:
 if(on)
 timerstop(timer_an);

}
    return 0;
}

int game_pause()
{
 if(on)
 { stop();
   stoptimer(timer_an);
 }
return 0;
}

int game_resume()
{ 
 if(on)start();
 return 0;
}


//�˳�ǰ�Ĺ���
void game_exitapp()
{
//ɾ����ʱ��
 if(timer)
 timerdel(timer);
 if(timer_an)
 timerdel(timer_an);
 timer=timer_an=NULL;

//�ͷ��ڴ�
 if(FF!=NULL)free(FF);
 if(DD!=NULL)free(DD);
 if(fx!=NULL)free(fx);
 if(fy!=NULL)free(fy);
 if(fv!=NULL)free(fv);
 fx=fy=NULL;
 fv=NULL;

}

//��ʼ
void start()
{
timerstart(timer,FV,0,"FFF",1);
}

//��ͣ
void stop()
{
timerstop(timer);
timerstop(timer_an);
}

//�ɻ��ƶ�
void ffxy(int p1)
{
if(on&&!off)
switch(p1)
{
 case _UP:
 case _2:
 if(ffy>0)ffy-=FH;
 else  ffy=FH*HK;
 break;

 case _DOWN:
 case _8:
 if(ffy<FH*HK)
 ffy+=FH; else ffy=0;
 break;

 case _LEFT:
 case _4:
 if(ffx>0)ffx-=FW;
 else ffx=FW*WK;
 break;

 case _RIGHT:
 case _6:
 if(ffx<FW*WK)
 ffx+=FW;
 else ffx=0;
 break;
}

}


//��ͼ,����ɻ����Ƿ����谭����ײ
void FFF(int data)
{
 if(on&&!off)
{
 cls(100,200,250);
 int w=HK*FH;
 int b;
 for(int a;a<LV;a++)
 {
  if(!on&&off)break;

  fy[a]+=fv[a]*FH;
 if((fy[a]>=w)||(fy[a]<=NULL))
  {
   fx[a]=rand_x();
   fy[a]=0;
   fv[a]=rand_v();
  }

 if((ffx==fx[a])&&(fy[a]>FH/2))
 switch(1)
 {
  case (ffy==fy[a]):
  case (ffy-fy[a]<=FH*fv[a]):
  //case (fy[a]-ffy<=FH/2):
  sss();stop();over();
  b=1;break;
 }
if(b)break;


bmpshowflip(DD,fx[a],fy[a],pw2,pw2,ph2,BM_COPY,0,0,0);
//����谭��ͼ��
 
}

if(!b)
{
 bmpshowflip(FF,ffx,ffy,pw,pw,ph,BM_COPY,0,0,0);
//��ɻ���ͼ��
 REF;
 }

}

}


//�������һ���Ǹ���
int rand_()
{
 int a=rand();
 if(a>=0)return a;
 else return (-a);
}

//��������谭���x����
int rand_x()
{
 for(int a=FW*2;1;a=rand_()%HK)
 if(a<=HK)break;
 return a*FW;
}

//��������谭����ٶ�
int rand_v()
{
 for(int a=FH*16;1;a=rand_()%5)
if(a<=9)break;
return a;
}


//��ɱ��
void BX()
{
if(bxs)
{
 for(int a=HK*FH;a>=0;a-=FH)
{
 drect(0,a,SCRW,a+FH,100,20,50);

 bmpshowflip(FF,ffx,ffy,pw,pw,ph,BM_COPY,0,0,0);
//�ɻ�ͼ��
 REF;
}

 for(a=0;a<LV;a++)
 if(fy[a]<=ffy)
 fy[a]=0;
 REF;

 if(bxs)bxs--;

}

}


//������ͼ
void sss()
{
 effsetcon(0,SCRH/2,SCRW,30,138,138,138);
 game_text("������������Ϸ������",0,SCRH/2,255,5,5);
 REF;
 sleep(1000);
 REF;
}

//�˳���
void over()
{
 drect(0,0,SCRW,SCRH,100,200,250);

 game_text("�Ƿ������˵���",SCRW/2-tw*3,SCRH-th*2,255,25,25);

 game_text("��",0,SCRH-th,25,25,25);

 game_text("��",SCRW-tw,SCRH-th,25,25,25);

 REF;

 on=NULL;//��ͣ����
 off=!NULL;//��������

}
//by:ÿ�����һ��