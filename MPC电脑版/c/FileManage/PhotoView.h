/*
* (PhotoView)��ͼƬ�����
* By:���� 
* QQ:643552878
* Date:2012.8.23
* �ӿں���:
��ʼ��: PVInit(char *Name);
�������: PVEvent(int type,int p1,int p2);
*/

//ͼƬ�ƶ����ʱ��(ms)
#define PMTime 1
//����
#define PFONT 1 

struct DPhoto
{
 int8 Mxy;//ͼƬ�ƶ���(��)��
 int16 x;
 int16 y;//ͼƬx��y����
 int timer;//ͼƬ�ƶ���ʱ�����
 char *name;//ͼƬ�ļ���
};

struct DPhoto *DP;

//ͼƬ�����ڣ�FileName:ͼƬ�ļ���
int PVInit(char* FileName)
{
 if(getlen(FileName)<0)
 return -1;

 int l=sizeof(struct DPhoto);
 DP=(struct DPhoto*)malloc(l);
 memset(DP,NULL,l);

 DP->timer=timercreate();
 int len=strlen(FileName);
 DP->name=(char*)malloc(len);
 memset(DP->name,NULL,len);
 strcpy(DP->name,FileName);

 if(getlen(DP->name)<0)
 {
 DPExit();
 return -1;
 }
 DrawPhoto();
 return 0;
}

//ͼƬ����������
int PVEvent(int type, int p1, int p2)
{
 if(KY_DOWN==type)
 switch(p1)
 {
 case _SRIGHT:
 PVExit();
 break;

 case _UP:
 case _DOWN:
 case _LEFT:
 case _RIGHT:
 DP->Mxy=1;
 PMove(p1);
 timerstart(DP->timer,PMTime,p1,"PMove",TRUE);
 break;
 }
 else
 if(type==KY_UP)
 {
 case _UP:
 case _DOWN:
 case _LEFT:
 case _RIGHT:
 timerstop(DP->timer);
 break;
 }

 return 0;
}

//�˳��ļ����
int PVExit()
{
 timerdel(DP->timer);
 free(DP->name);
 free(DP);
 BackFV();
 return 0;
}

//ͼƬ�ƶ�(�ı�x��y����)
void PMove(int p1)
{
 int8 Mxy=DP->Mxy;

 if(p1==_UP)
 DP->y-=Mxy;
 else
 if(p1==_DOWN)
 DP->y+=Mxy;
 else
 if(p1==_LEFT)
 DP->x-=Mxy;
 else
 if(p1==_RIGHT)
 DP->x+=Mxy;

 if(DP->Mxy<5)
 DP->Mxy++;
 DrawPhoto();
}

//��ͼƬ
void DrawPhoto()
{
 cls(181,207,231);
 img(DP->name,DP->x,DP->y);
 char str[21];
 sprintf(str,"%d,%d",DP->x,DP->y);
 dtext(str,0,0,128,128,128,FALSE,PFONT);
 ref(0,0,SCRW,SCRH);
}

//By:����