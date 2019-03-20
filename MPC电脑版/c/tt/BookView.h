/*
* BookView(���ı������)
* By:����
* QQ:643552878
* Date:2012.8.29
* �ӿ�:
 ��ʼ�� BVInit(char *FileName);
 ���� BVEvent(int type,int p1,int p2);
* ˵��:�˳��Զ������Ķ����ȡ���Դ������������ġ�
* ����:��(4)����(6)����ҳ��0���л�Ƥ����*�����ÿ�ͷ��#�����ý�β(��bug)��1��������
*/

//�Ķ�����
#define BFONT 1

//�Ķ���¼�ļ���׺
#define SNF ".mark"

struct BView
{
 char *name;//�ļ���
 char *SekName;//�Ķ���¼�ļ���
 uint32 size;//�ļ�����
 int f;//�ļ����
 int sek;//�ļ�ͷָ��λ��
 uint32 nsek;//��ǰҳ��ָ��λ��
 uint32 lsek;//��һ��λ��
 uint8 xs;//�ּ���(����)
 uint8 ys;//�м���(����)
 uint8 kin;//Ƥ��(0��ҹ��1����)
};

struct BView *BV;
colorst
*Bclr,//ǰ��ɫ
*Bgclr;//����ɫ

rectst *Brect;//�Ķ��ı���

/*��ʼ����ڣ��ɹ����� 0��ʧ�ܷ��� -1*/
int BVInit(char *FileName)
{
 if(getlen(FileName)<0)
 return -1;

 int l=sizeof(struct BView);
 BV=(struct BView*)malloc(l);
 memset(BV,0,l);

 BV->name=(char*)malloc(strlen(FileName));
 strcpy(BV->name,FileName);
 BV->SekName=(char*)malloc(strlen(BV->name)+strlen(SNF)+1);
 strcpy(BV->SekName,BV->name);
 strcat(BV->SekName,".mark");
 BV->size=getlen(BV->name);
 BV->f=open(BV->name,1);
 BV->xs=2;
 BV->ys=10;
 BV->kin=1;
 BV->nsek=0;

//ǰ��ɫ
 Bclr=malloc(3);
 memset(Bclr,255,3);
//����ɫ
 Bgclr=malloc(3);
 memset(Bgclr,0,3);
//�Ķ���
 Brect=malloc(8);
 memset(Brect,0,8);
 Brect->x=0;
 Brect->y=0;
 Brect->w=SCRW;
 Brect->h=SCRH;

 
//��ȡ��¼
 if(4==getlen(BV->SekName))
 {
 int f=open(BV->SekName,1);
 read(f,&BV->nsek,4);
 close(f);
 BV->sek=BV->nsek;
 }

//����ļ�������
 if(BV->size<0)
 {
 BVExit();
 return -1;
 }

 HuanSkin();//�л�Ƥ��
 NextPage();
 return 0;
}

//�˳�
int BVExit()
{
//�����Ķ���¼
 int f=open(BV->SekName,2|8);
 seek(f,0,SEEK_SET);
 write(f,&(BV->nsek),4);
 close(f);

 free(BV->name);
 free(BV->SekName);
 close(BV->f);
 free(BV);
 free(Bclr);
 free(Bgclr);
 free(Brect);

// BackFV();
 return 0;
}//�������
int BVEvent(int type, int p1, int p2)
{
 if(KY_DOWN==type)
 switch(p1)
 {
 case _SRIGHT:
 BVExit();
 break;

 case _0:
 HuanSkin();
 //DrawBook();
 break;

 case _1:
 GoPage(BV->nsek+1);
 break;

 case _STAR:
 GoPage(0);
 break;

 case _POUND:
 GoPage(BV->size-50);
 break;

 case _4:
 case _LEFT:
 LastPage();
 break;

 case _6:
 case _RIGHT:
 NextPage();
 break;
 }

 return 0;
}

//���ı�
int DrawBook()
{
 int zw,zh;
 uint8 xs=BV->xs,ys=BV->ys;
 int16 x=Brect->x,y=Brect->y;
 char buf[2];
 BV->nsek=BV->sek;

 drect(Brect->x,Brect->y,Brect->w,Brect->h,Bgclr->r,Bgclr->g,Bgclr->b);
 ref(0,0,SCRW,SCRH);
 while(BV->sek<=BV->size)
 {
 memset(buf,'\0',2);
 seek(BV->f,BV->sek,SEEK_SET);
 read(BV->f,buf,2);
 if(0<=buf[0])
  if(buf[0]<=127)
 buf[1]='\0';
 textwh(buf,0,BFONT,&zw,&zh);

//printf("strw=%d,strh=%d,seek=%d\n",zw,zh,sek);

//����ǻ��з�
 if(buf[0]==13)
 {
  x=Brect->x;
  y=y+zh+ys;
  BV->sek+=2;
  continue;//��������ѭ��
  }

//����һ�д��������
 if(x+zw>Brect->w+Brect->x)
 {
 x=Brect->x;
 y=y+zh+ys;
 }

//�������ҳ
 if(y+zh>Brect->y+Brect->h)
 goto OVER;

// ref(x,y,2,zh);
 dtext(buf,x,y,Bclr->r,Bclr->g, Bclr->b,FALSE,BFONT);
  ref(x-5,y-5,zw+10,zh+10);

//����ǷǺ������һ�ֽڣ�����2�ֽڡ�
 if((0<=buf[0])*(buf[0]<=127))
 BV->sek+=1;
 else
 BV->sek+=2;
 x=x+zw;
 }
 OVER:
 ref(0,0,SCRW,SCRH);
 return 0;
}

//�Ϸ�ҳ
int LastPage()
{
/* if(BV->sek==BV->nsek==0)
 return -1;*/
 BV->sek=BV->lsek;
 DrawBook();
 return 0;
}

//�·�ҳ
int NextPage()
{
/* if(BV->nsek>=BV->size)
 return -1;*/
 BV->lsek=BV->nsek;
 BV->nsek=BV->sek;
 DrawBook();
 return 0;
}

/*��תҳ�棬len:��ת���ȣ�ע:��ת���ܻ�������룡*/
int GoPage(uint32 len)
{
 if(len>BV->size)
 return -1;

 BV->nsek=len;
 BV->sek=len;
 BV->lsek=len-100;
 DrawBook();
 return 0;
}


//��Ƥ��
int HuanSkin()
{
 if(!BV->kin)
 {
 Bclr->r=255;
 Bclr->g=255;
 Bclr->b=255;
 
 Bgclr->r=0;
 Bgclr->g=0;
 Bgclr->b=0;
 }
 else
 {
 Bclr->r=0; 
 Bclr->g=0;
 Bclr->b=0;
 
 Bgclr->r=255;
 Bgclr->g=255;
 Bgclr->b=255;
 }
 BV->kin=!BV->kin;
 return 0;
}

//By:����