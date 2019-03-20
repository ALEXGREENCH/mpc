/***
wildly hp��ܿؼ�����������Ϸ
QQ 319965592
��ʱ������ˢ��Ч����á�
***/

#ifndef HP_CONTROL_H
#define HP_CONTROL_H

#include <base.h>

//HP�������ֵ
#define HpMax 200

//ÿ��HP�ܵ�HPֵ
#define Hpox 200

typedef struct
{
   int hp[HpMax];
   int hr[HpMax];
   int hg[HpMax];
   int hb[HpMax];
   int hpe;
   int hpnum;
   int nis;
   int x;
   int y;
   int w;
   int h;
}Hpc;

typedef Hpc *hpint;

//����һ��HP��ܣ�hpnum ��������ֵ��w��Hpoxͬ��
void *hpcreate(int x,int y,int w,int h,int hpnum)
{int time = getuptime();
if(hpnum >= HpMax)return NULL;
hpint pm = malloc(sizeof(Hpc));
memset(pm,0,sizeof(Hpc));
if(pm == NULL)return NULL;
int dp,h1[4]={255,0,255,0},h2[4]={0,0,128,205},h3[4]={0,205,0,0};
for(int a=0;a<hpnum;a++)
{if(dp > 3)dp = 0;
pm->hp[a] = Hpox;
pm->hr[a] = h1[dp];
pm->hg[a] = h2[dp];
pm->hb[a] = h3[dp];
dp++;}
  pm->x = x;
  pm->y = y;
  pm->w = w;
  pm->h = h;
pm->hpnum = hpnum;
pm->hpe = Hpox;
time = getuptime()-time;
//printf("\n����HP����ʱ��%d.%ds,%s\n",time/1000,time%1000);
return pm;
}

//��ʾHP��ܣ�hpj HP��Ч���ٶȣ�is�Ƿ�ˢ�±��� 0�� 1��
int hpshow(hpint pm,int hpj,int is)
{
if(is)
drect(pm->x,pm->y,pm->w,pm->h,0,0,0);
if(pm->hp[pm->hpnum] <= 0){pm->nis = pm->hp[pm->hpnum];pm->hp[pm->hpnum]=0;pm->hpnum--;}
if(pm->nis < 0){pm->hp[pm->hpnum] += (pm->nis);if(pm->nis >= -Hpox)pm->nis = 0;}
drect(pm->x,pm->y,Hpox,pm->h,255,255,255);
if(pm->hp[pm->hpnum] < (pm->hpe))pm->hpe-=hpj;
if(pm->hpe < (pm->hp[pm->hpnum]))pm->hpe = (pm->hp[pm->hpnum]);
drect(pm->x,pm->y,pm->hpe,pm->h,160,0,0);
drect(pm->x,pm->y,pm->hp[pm->hpnum],pm->h,pm->hr[pm->hpnum],pm->hg[pm->hpnum],pm->hb[pm->hpnum]);
ref(pm->x,pm->y,pm->w,pm->h);
return 0;
}

//����HP���
int hpdel(hpint pm)
{free(pm);
return 0;
}

//HP��ܵ�HPֵ������sh����ֵ
int hpnext(hpint pm,int sh)
{
pm->hp[pm->hpnum] -= sh;
return 0;
}

//��ȡ��ǰ����
int gethpnum(hpint pm)
{
return (pm->hpnum);
}

//���ù���������
int sethpnum(hpint pm,int hpnum)
{
for(int a=0;a<(pm->hpnum);a++)
pm->hp[a] = Hpox;
pm->hpnum = hpnum;
}

#endif