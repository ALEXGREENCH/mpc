//wildly �Զ��庯����
/*
�º�����˵��
strint ������תΪ�ַ���
strdel ɾ���ַ����е������ַ���ѡ��СǮ��
getmrpinformation ��ȡmrp��Ϣ��
mrpinformation ����mrp��Ϣ��
readmrpfile ��ȡmrp�ڲ��ļ���
mrpunins ж��mrp,ɾ��mrp���ɵ��ļ��м��ļ�����mrp��
�����⣬�ŵ㣬д��������㣬��ݣ����ܶ࣬������
QQ:319965592   wildly
*/


#ifndef MPC_WILDLY_H

#define MPC_WILDLY_H

//�����С���Զ���
#define FONT 0

#include <base.h>
//�������������
#define c cls(0,0,0)
#define r ref(0,0,SCRW,SCRH)

//ʣ���ڴ�
#define MAIN maine()

//���ڴ�
#define MEM mem()

#define Metime getuptime()

int Time_Create[20];

int Edit_Create[20];

int Menu_Create[20];

int Dlg_Create[20];

//��ȡ�ֻ��ѿ��� ʱ
#define Hou hour()

//��ȡ�ֻ��ѿ��� ��
#define Min minute()

//��ȡ�ֻ��ѿ��� ��
#define Sec second()

//ϵͳʱ�� ��
#define Year _year()

//��
#define Month _month()

//��
#define Day _day()

//ʱ
#define Hour _hour()

//��
#define Minute _minute()

//��ȡ�����ַ���
#define Texw textw()

//��ȡ�����ַ���
#define Texh texth()

//ʱ��ṹ��
typedef struct
{   uint16 year;
    uint8 month;
    uint8 day;
    uint8 hour;
    uint8 minute;
}mr_time;

mr_time date;

//���ֺ�������Ҫ���ڴ棬�ṹ�塣
typedef struct
{
   char *str;
   char *buf[2];
}buffer;

buffer strsc;

//main��ڣ���ʱ��������
int init(void)
{MR_TimeCreate();
return main();}

//�ַ�ת����strҪת�����ַ���is_uni 1 GB2312תΪunicode�ֽ� 0 unicodeתGB2312
void* gb(char *str,int is_uni)
{
 int err,a,b;
 a=wstrlen(str);
 if(!is_uni)
 {
 u2c(str,a,&str,&a);
 return str;
 }
 else
 return c2u(str,&err,&b);
}

//�����ļ���nameҪ���Ƶ��ļ���name2���ƺ���ļ����޸��ƴ�С�� �ɹ����� 0 ʧ���� -1
int copy(char *name,char *name2)
{int Len,f,fa;
if(getlen(name)<=0)return -1;
f=open(name,1);
fa=open(name2,8);
seek(fa,0,SEEK_END);
void *buf=(char*)malloc(51200);
if(buf==NULL)return -1;
while(1)
{memset(buf,NULL,51200);
seek(f,Len,SEEK_SET);
uint32 Read=read(f,buf,51200);
write(fa,buf,Read);
Len+=Read;
if(Read<51200)break;}
close(fa);free(buf);
return close(f);}

//��ʾbmpͼƬ����moc�ĸ�ʽһ�������سɹ�0��ʧ��-1
int bmp(char *filename,int x,int y,int w,int wm,int h,int pm,int dx,int dy)
{int f,len; uint16 *ptr;
len=getlen(filename);
if(len<=0)return -1;
if(filestate(filename)!=IS_FILE)return -1;
ptr=malloc(len);
f=open(filename,1);
read(f,ptr,len);
bmpshowflip(ptr,x,y,w,wm,h,pm,dx,dy,*ptr);
free(ptr);
return close(f);}

//ɾ���ļ���DirPath�������ļ����ļ��У�����DirPath����Ϊ����0��ʧ�ܷ���-1
int rmdirEX(char *DirPath)
{char tDirPath[255];
 char tName[64];
 char tPath[255];
 char *pPath;
 int f,Count = 0;
if(filestate(DirPath)==8)return -1;
strcpy(tDirPath,DirPath);
 while(TRUE)
 {
  f = findstart(tDirPath,tName,64);
  findnext(f,tName,64);
  while(TRUE)
  {
   if(findnext(f,tName,64) == -1)
    break;
   sprintf(tPath,"%s/%s",tDirPath,tName);
   if(IS_DIR == filestate(tPath))
   {
    if(rmdir(tPath))
    {Count++;
     findstop(f);
     strcpy(tDirPath,tPath);
     goto Next;
    }
   }else
   if(remove(tPath))
   {findstop(f);
    goto Stop;
   }
  }
  findstop(f);
  if(Count)
  {pPath = tDirPath;
   pPath = strrchr(pPath,'/');
   memset(pPath,0,strlen(pPath));
   Count--;
  }else break;
  Next:
 }
 Stop:
 int A_T=findstart("",tName,64);
 findstop(A_T);
 return rmdir(DirPath);
}

//�����ľ��Σ���rect��һ���ġ�
void rest(int x,int y,int w,int h,int r,int g,int b)
{
dline(x,y,x,y+h-1,r,g,b);
dline(x+1,y,x+w-2,y,r,g,b);
dline(x+w-1,y,x+w-1,y+h-1,r,g,b);
dline(x+1,y+h-1,x+w-2,y+h-1,r,g,b);
}

//����������mes���ȳ���x,y��λ��w�߿���ȿ�,h�߿���ȸߣ�r,g,b�߿���ɫ��r2,g2,b2������ɫ
void rent(int mes,int x,int y,int w,int h,int r,int g,int b,int r2,int g2,int b2)
{int cm;
if(mes<=2)cm=0; else cm=2;
rest(x,y,w,h,r,g,b);
drect(x+1,y+1,mes-cm,h-2,r2,g2,b2);
}

int maine()
{return getmemremain();}

int mem()
{return getsysmem();}

//��str�ַ��������str2�ַ���str�ַ���һ�γ���str2�ַ�ʱ �򷵻�0 ���򷵻�-1
int strch(char *str,char *str2)
{if(strstr(str,str2)==NULL)return -1;
return 0;}

//��dtext��str�ַ���x,y����
int txt(char *str,int x,int y)
{dtext(str,x,y,255,255,255,0,FONT);
return 0;}

//��MOC��drawtxt2��һ���ģ�����������
int text(char *str, int x, int y, int w ,int h ,int r , int g , int b)
{rectst rect;
rectst ect;
colorst color;
rect.x = x;
rect.y = y;
rect.w = w;
rect.h = h;
color.r = r;
color.g = g;
color.b = b;
dtextex(str,x,y,&rect,&color,2,FONT);
return 0;}


//��������Σ�r,g,b��һ��ɫ ��ra,ga,ba �ڶ���ɫ��Fen��ɫ��λ��
void sect(int x, int y, int w, int h, int r, int g, int b, int ra, int ga, int ba, int Fen)
{int N1 = r*0x10000+g*0x100+b, N2=ra*0x10000+ga*0x100+ba;
shaderect(x,y,w,h,N1,N2,Fen);}

//��ʾ������x,y����
void intxt(int mes,int x,int y)
{char str[255];
dtext(sprintf(str,"%d",mes),x,y,255,255,255,0,FONT);}

//��ȡ�ֻ�CPU�����ӣ�printf("%d.%dMhz",10000/cpu(),1000000/cpu()-10000/cpu()*100);����ȡ�ٶȺ�����
int cpu()
{int a,b;
a=getuptime();
for(b=0;b<=10000;b++);
a=getuptime()-a;
return a;}

int hour()
{int chen=Metime/1000/60/60%60;
return chen;}

int minute()
{int chen=Metime/1000/60%60;
return chen;}

int second()
{int chen=Metime/1000%60;
return chen;}

int _year()
{if(getdatetime(&date))
return -1;
return date.year;}

int _month()
{if(getdatetime(&date))
return -1;
return date.month;}

int _day()
{if(getdatetime(&date))
return -1;
return date.day;}

int _hour()
{if(getdatetime(&date))
return -1;
return date.hour;}

int _minute()
{if(getdatetime(&date))
return -1;
return date.minute;}

//����20����ʱ��
void MR_TimeCreate()
{int i;
for(i=0;i<20;i++)
{Time_Create[i]=timercreate();} }

//ֹͣ��ʱ����data��ʱ������š�
void Stop(int data)
{timerstop(Time_Create[data]);}

//������ʱ����data��ʱ����ţ�sm��ʱ��ʱ�� ��λ��times��ʱ���ص�������type�Ƿ�ѭ�� 0��ѭ�� 1ѭ��
void timer(int data,int sm,char *times,int type)
{timerstart(Time_Create[data],sm,TRUE,times,type);}

     /****����UI����****/

//�����༭��set�༭����ţ�Name�༭���� ����GB2312��Open�༭������ ����GB2312�������ʽ 0�������� 1�������� 2�������� ��Max�������ơ�
int editc(int set,char *Name,char *Open,int Pes,int Max)
{Edit_Create[set]=editcreate(gb(Name,1),gb(Open,1),Pes,Max);
return Edit_Create[set];}

//��ȡ�༭�����ݣ�setҪ��ȡ��Ϣ�ı༭����ţ���ȡ����Ϣ���ͣ�GB2312
void *getb(int set)
{void *EditGet = gb(editget(Edit_Create[set]),0); return EditGet;}

//���ٱ༭��SetCeҪ���ٵı༭����š�
void edel(int SetCe)
{editdel(Edit_Create[SetCe]);}

//�༭���¼����ɲ�����event
void edit_event(int type,int p,int p2)
{if(type==MR_DIALOG)
{switch(p)
{case DLG_OK:
edit_ok(); break;
case DLG_CANCEL:
edit_cancel(); break;
} } }

//��ȡ��������� ��λByte
int stdiolen()
{return getlen("stdio.h");}

int textw()
{int w,h;
textwh("��",0,0,&w,&h);
return w;}

int texth()
{int w,h;
textwh("��",0,0,&w,&h);
return h;}

//�����˵���Mes�˵���ţ�Name�˵����⡢����GB2312��MenuMax�˵�������
void menuc(int Mes,char *Name,int MenuMax)
{
Menu_Create[Mes]=menucreate(gb(Name,1),MenuMax);
}

//�˵��Mes�˵���ţ�Name�˵�����⡢����GB2312��Menuy�˵���˳��
void mset(int Mes,char *Name,int Menuy)
{menuset(Menu_Create[Mes],gb(Name,1),Menuy);}

//�ͷŲ˵���Mes�˵����
void mshow(int Mes)
{menushow(Menu_Create[Mes]);}

//���ٲ˵���Mes�˵����
void mdel(int Mes)
{menudel(Menu_Create[Mes]);}

//����һ���Ի���Mes�Ի�����ţ�text�Ի������ݡ����ݸ�ʽGB2312��type�Ի������͡�0�С�ȷ������1�С�ȷ�����������ء���2�С����ء���
void dlgc(int Mes,char *text,int type)
{Dlg_Create[Mes]=dlgcreate("",gb(text,1),type);}

//���ٶԻ���Mes�Ի������
void gdel(int Mes)
{dlgdel(Dlg_Create[Mes]);}

//�����ļ���filename�ļ���
int newfile(char *filename)
{int f=open(filename,8);
close(f);
return f;}

     /****����UI���ֽ���****/

//��λȷ��,������0
int ifrect(int x,int y,int x2,int y2,int w,int h)
{
if(x>x2-w&x<=x2&y>y2-h&y<=y2)return 0;

return -1;}

//new������
void where(char *t,int b,int er,int h)
{ drect(0,SCRH/2,SCRW,h,200,80,100);
drect(0,SCRH/2+1,SCRW*b/er,h-2,20,20,190);
txt(t,0,SCRH/2); ref(0,SCRH/2,SCRW,35); 
}

//������תΪ�ַ���,str ת�����ַ���
char *strint(int32 p)
{char n[200];
sprintf(n,"%d",p);
return n;
}

//ɾ��text�ַ��У�dt�ַ���ͨ������ֵ��ȡ,�ú������ú����freestrbuf()�����˳�ʱ����freestrbuf()
char *strdel(char *text,char *dt)
{if(text==NULL)return NULL;
int len=strlen(text);
strsc.str = malloc(len)+1;
memset(strsc.str,0,len);
if(dt == NULL)return strsc.str;
char *b=strstr(text,dt);
int len2=strlen(dt),len3=strlen(b);
if(len==len2||b==NULL)return strsc.str;
free(strsc.str);
strsc.str = malloc(len-len2+2);
memset(strsc.str,0,len-len2+2);
memcpy(strsc.str,text,len-len3);
strcat(strsc.str,text+len-(len3-len2));
return strsc.str;
} 

      /****mrp����****/

     //��ȡ'���ģ�mrp��Ϣ��ȡֵ��
enum
{
   _MNAME = 0,     //mrp��
   _INTERNAL,     //mrp�ڲ���
   _PAUTHOR,     //mrp����
   _SERIALNUMBER, //mrp ���к�
   _MHELP      //mrp ����
};

//�����á���������
void *mrpmalloc(uint8 s,int len)
{strsc.buf[s] = malloc(len);
if(strsc.buf[s] == NULL)return NULL;
return strsc.buf[s];
}

//��ȡmrp��Ϣ��file mrp�ļ���s ��ȡ��Ϣ��ȡֵ, ����ֵ��ȡ���ú������ú����freestrbuf()�����˳�ʱ����freestrbuf() 
void *getmrpinformation(char *file,int s)
{int pys,lens;
if(filestate(file) != 1 || getlen(file) < 100)return NULL;
int f = open(file,1);
if(f == -1){close(f);return NULL;}
      switch(s)
       {
         case _MNAME:
         pys = 28; lens = 22;
        break;
         case _INTERNAL:
         pys = 16; lens = 11;
        break;
         case _PAUTHOR:
      pys = 88; lens = 37;
         break;
         case _SERIALNUMBER:
      pys = 52; lens = 15;
         break;
       case _MHELP:
      pys = 128; lens = 59;
          break;
}
if(mrpmalloc(0,lens) == NULL){close(f);return NULL;}
seek(f,pys,SEEK_SET);
read(f,strsc.buf[0],lens);
close(f);
return strsc.buf[0];
}

//����mrp��Ϣ��file mrp�ļ���str ������Ϣ��s ����ȡֵ��
int mrpinformationwrite(char *file,char *str,int s)
{int pys,lens;
if(filestate(file) != 1 || getlen(file) < 100)return -1;
int f = open(file,4);
if(f == -1){close(f);return -1;}
    switch(s)
     {
    case _MNAME:
    pys = 28; lens = 22;
    break;
    case _INTERNAL:
    pys = 16; lens = 11;
    break;
    case _PAUTHOR:
    pys = 88; lens = 37;
    break;
    case _SERIALNUMBER:
    pys = 52; lens = 15;
    break;
    case _MHELP:
    pys = 128; lens = 59;
    break;
}
seek(f,pys,SEEK_SET);
write(f,str,strlen(str) > lens ? lens : strlen(str));
seek(f,pys+strlen(str),SEEK_SET);
write(f,"",lens-strlen(str));
close(f);
return 0;
}

//��ȡmrp���ļ���file mrp�ļ���mrpfile ��Ҫ��ȡ���ļ�����len ��ȡ�ļ��ĳ��ȣ�lookfor 0���ú������ú����freestrbuf()�����˳�ʱ����freestrbuf() 
void *readmrpfile(char *file,char *mrpfile,int32 len,int lookfor)
{uint8 *buf;
readfilefrommrp(file,mrpfile,&buf,&len,lookfor);
int slen = strlen(buf);
mrpmalloc(1,slen);
memset(strsc.buf[1],0,slen);
if(strsc.buf[1] == NULL)return NULL;
memcpy(strsc.buf[1],buf,slen);
freefiledata(buf,len);
return strsc.buf[1];
}

//ж��mrp���ú�����ɾ��mrp���ɵ��ļ��к��ļ����ú������ܲ�׼ȷж����Ϸ�Ƚ�׼ȷ,file mrp�ļ�����is �Ƿ�ɾ��mrp 0�� ��1�ǣ��ú������ú����freestrbuf()�����˳�ʱ����freestrbuf() 
void mrpunins(char *file,int is)
{
char *files = strdel( getmrpinformation(file) ,".mrp");
if(is)remove(file);
if(filestate(files) != 2)break;
rmdirEX(files);
}

      /****mrp���ֽ���****/

//�ͷ��ڴ棬����ע�����ᵽ���øú��������ú����󣬾͸��ͷ��ڴ档
void freestrbuf()
{
for(int i=0;i<2;i++)
free(strsc.buf[i]);
free(strsc.str);
}

//��ȡ�ַ���ߣ��򻯡�
void strwh(char *str,int32 *sw,int32 *sh);
{
int32 w,h;
textwh(str,0,FONT,&w,&h);
*sw = w; *sh = h;
}

//�����ڴ棬����ʼ����
void *Malloc(int size)
{
void *buf = malloc(size);
memset(buf,0,size);
return buf;
}

#endif