void rect_text(char *txt,int x,int y,int w,int h)
{
 rectst rect; 
 colorst color;
 rect.x=x;
 rect.y=y;
 rect.w=w;
 rect.h=h;

color.r=R;
color.g=G;
color.b=B;

dtextex(txt,rect.x,rect.y,&rect,&color,2,1);

}
void bei()
{
 cls(10,10,10);
 img(cdbei,0,0);drect(0,th,SCRW,1,R/2,G/2,B/2);
int H=SCRH-th;
drect(0,H,SCRW,1,R/2,G/2,B/2);
text("����",SCRW-tw*2,H);
time(SCRW/2-tw,H);

}

void about()
{
bei();
text("����",0,0);
rect_text("��˹��˵v1.0
by:ÿ�����һ��
QQ:643552878
�������������Ļ���������֧���°ɣ�^_^
������ԭ���ߣ�����ɳܣ�
����֧���������Ķ�����
����:wap.mrpej.com
",0,th,SCRW,SCRH);
REF;
}
void help()
{
 bei();
text("����",0,0);
rect_text("���˵�:��(4)����(6)���л��˵���
�ϡ��¡����ҡ��ƶ���ȷ����ѡ��
�������߷�һ��������"
,0,th,SCRW,SCRH);
REF;
}

typedef struct
//ʱ��ṹ
{
uint16 year;
uint8  month;
uint8  day;
uint8  hour;
uint8  minute;
uint8  second;
} datetime;
//��ʾʱ��

void time(int xx,int yy)
{
datetime date;
getdatetime(&date);

char *da=malloc(5);

sprintf(da,"%d:%02d",date.hour,date.minute,date.second);
text(da,xx,yy);
free(da);

}

//by:ÿ�����һ��