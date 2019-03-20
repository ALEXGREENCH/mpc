/*
 *ע:���ô˿⺯������ע�ⶨ��FONT(����)��ֵ
*/

/*��ȡ�ַ������,is_wȡ��ֵ�����ַ��������򷵻ظ�*/
int strwh(void *str,int is_w)
{
 int w,h;
 textwh(str,FALSE,FONT,&w,&h);
 return is_w?w:h;
}

//����ʾ��Ϣ��is_ui:���ֱ���
void ShowMsg(char *Msg,int is_uni)
{
 int w,h;uint16 x,y;
 textwh(Msg,FALSE,FONT,&w,&h);
 if(w<SCRW)x=(SCRW-w)>>1;
 y=(SCRH-h)>>1;
 effsetcon(x-5,y-5,w+10,h+10,100,100,100);
 DrawVoidRect(x-5,y-5,w+10,h+10,255,0,0);
 dtext(Msg,x,y,255,255,250,is_uni,FONT);
 ref(x-5,y-5,w+10,h+10);
}


typedef struct RES
{
 uint16 ge;
 uint16 *f;
 char *dt;
}res;

/*����rc�ļ�������ָ��(ȡ��СǮ)*/
void *langload(char *name,uint16 ge)
{
 res *a=(struct RES*)malloc(sizeof(res));
 a->ge=ge;
 a->f=NULL;

 int len=getlen(name),
 f=open(name,1),
 i;
 if(!f)
 {
 free(a);
 return NULL;
 }
 a->f=malloc((ge+1)*2);
 read(f,a->f,(ge+1)*2);
 i=len-ge*2;
 a->dt=(char*)malloc(i);
 read(f,a->dt,i);
 close(f);
 return a;
}

/*��ȡ��nҳ����(ȡ��СǮ)*/
char *langStr(res *a,int n)
{
 if(a==NULL)
 return NULL;
 if(a->dt==NULL)
 return NULL;
 else
 return (char *)a->dt+a->f[n];
}

//gb��uni���뻥ת
void* gb_uni(char* str,int is_uni)
{
 int err,a,b;
 a=wstrlen(str);
 if(is_uni)
 {
 u2c(str,a,&str,&a);
 return str;
 }
 return c2u(str,&err,&b);
}

//ʱ��ṹ
typedef struct
{
 uint16 year;
 uint8  month;
 uint8  day;
 uint8  hour;
 uint8  minute;
 uint8  second;
}datetime;

//��ʱ��
void DrawTime(int xx,int yy)
{
 datetime date;
 getdatetime(&date);
 char str[10];
 sprintf(str,"%d:%02d",date.hour,date.minute,date.second);
 DrawText(str,xx,yy);
}

//�潥�����
void srect(int16 x,int16 y,int16 w,int16 h,uint8 r,uint8 g,uint8 b,uint8 r2,uint8 g2,uint8 b2,uint8 mode)
{
 shaderect(x,y,w,h,r*0x10000+g*0x100+b,r2*0x10000+g2*0x100+b2,mode);
}
//�����ľ���
void DrawVoidRect(uint16 x,uint16 y,uint16 w,uint16 h,uint8 r,uint8 g,uint8 b)
{
 dline(x,y,x,y+h-1,r,g,b);
 dline(x+1,y,x+w-2,y,r,g,b);
 dline(x+w-1,y,x+w-1,y+h-1,r,g,b);
 dline(x+1,y+h-1,x+w-2,y+h-1,r,g,b);
}

/*ȫ����ͼ*/
int PrintScr(char *name)
{
 int f=open(name,8);
 write(f,getscrbuf(),SCRW*SCRH*2);
 close(f);
 return getlen(name);
}