/*
˫������ʾ��
by:����
QQ:643552878
���Ҳ�����Լ��ջᣬ��д�ġ��������ʹ��һ��ѧϰ������֮������ָ�㡣
*/

#include <base.h>

/*Ϊ�˷��㣬���Գ��ṹ��ָ���⣬ֻ����1������*/
typedef struct list
{
 struct list *last;
 /*ָ���ϸ����*/
 struct list *next;
 /*ָ���¸����*/
 char *text;
 /*��������*/
}LISTST;

int ListLen=sizeof(LISTST);
/*�ṹ���С*/

/*�ڽ�β���һ�����(�����)*/
void AddEnd(LISTST *First,char *text)
{
 LISTST *to=First,*one;
 while(to->next!=NULL)
 to=to->next;

 one=malloc(ListLen);
 memset(one,NULL,ListLen);
 one->text=malloc(strlen(text));
 strcpy(one->text,text);
 one->last=to;
 one->next=NULL;

 to->next=one;

}

/*�ڵ�n�����󣬲���1�����(�����)*/
void AddOne(LISTST *Head,char *text,int n)
{
 LISTST *to=Head,*one;

 int e=NULL;
/*e��ֵ��������Ӧ��ϵ:
NULL���ڽ�β��1�ڽ�β��*/

 for(int i=1;i<=n;i++)
 if(to->next!=NULL)
 to=to->next;
 else {e=1;break;}

 if(e==NULL)
 /*���ڲ��ڽ�β��ֱ�Ӳ���*/
 {
 one=malloc(ListLen);
 memset(one,NULL,ListLen);
 one->text=malloc(strlen(text));
 strcpy(one->text,text);
 one->last=to;
 one->next=to->next;

  to->next->last=one;
 to->next=one;
 }
 else/*�ڽ�β��*/
 AddEnd(Head,text);
}

/*������б�(�����)*/
void drawList(LISTST *Head)
{
 LISTST *to=Head;

 int x=0,y=0,h=30;
 uint8 r=255,g=155,b=255;

 while(to!=NULL)
 {
 drawtext(to->text,x,y,r,g,b);
 to=to->next;
 y+=h;
 }

}

/*������б�(�����)*/
void drawList2(LISTST *End)
{
 LISTST *to=End;
 int x=SCRW/2,y=0,h=30;
uint8 r=200,g=200,b=0;
 while(to!=NULL)
 {
 drawtext(to->text,x,y,r,g,b);
 to=to->last;
 y+=h;
 }

}

/*ɾ�����1�����(�����)*/
void DelEnd(LISTST *End)
{
 LISTST *one=End;

 if(End->last!=NULL)
 /*�������ֻ��1�����*/
 {
 one=one->last;
 free(one->next->text);
 one->next=NULL;
 }
 else
 if(End->last==NULL)
 /*ֻ��һ�����*/ 
 free(one->text);
 End=one; 
}

/*ɾ����n�����(�����)*/
void DelOne(LISTST *Head,int n)
{
 LISTST *to=Head;

 int e=NULL;
/*e��ֵ����Ӧ����λ�á�
NULL�м� -1��ͷ 1��β
*/
 for(int i=1;i<=n;i++)
 if(to->next!=NULL)
 to=to->next;
 else {e=1;break;}

 if(e==1)DelEnd(to);
 else
 if(i==2)DelEnd(Head,1);
 else if(i!=2)
 {
 
 to->last->next=to->next;
 to->next->last=to->last;

 free(to->text);
 }

}


/*ɾ����ͷ��β�����н��(�����)*/
void DelAllList(LISTST *First,LISTST *End)
{
 LISTST *to=End;
 if(End->last==NULL)
 {
 while(to->last->last!=NULL)
  {
  free(to->text);
  free(to->next);
  to=to->last;
  }
 free(First->text);
 free(End->text);
 First->next=End; 
 End->last=First;
 }

}

/*��ں���*/
int init()
{
 LISTST *First,*End;
 /*����������㣬FirstΪ����ͷ��End��β*/

 First=malloc(ListLen);
 memset(First,NULL,ListLen);
 End=malloc(ListLen);
 memset(End,NULL,ListLen);


 AddEnd(First,"˫������");
 AddEnd(First,"����ѧϰ");
 AddEnd(First,"���ڼ��");
 AddEnd(First,"�������");

 AddOne(First,"by:����Tt",1);
 /*����1�����*/

 End=First;
 while(End->next!=NULL)
 End=End->next;
 /*ʹEndΪ���һ�����*/

 DelEnd(End);
 /*ɾ�����1�����*/
 
 cls(0,0,0);
 drawList(First->next);
 drawList2(End->last);
 ref(0,0,SCRW,SCRH);


 DelAllList(First,End);
 free(First);
 free(End);

 drawCopy(0,SCRH/2,SCRW,SCRH/2);
/*���ֵ�Ӱ*/

 return 0;
}

/*������ں���*/
int event(int type, int p1, int p2)
{
 if(KY_DOWN==type)
 {
  switch(p1)
  {
  case _SRIGHT:
  exit();break;
  case _1:
  break;
   }
  }
 return 0;
}

/*Ӧ����ͣʱ���ú���*/
int pause()
{return 0;}

/*Ӧ�ûָ��ǵ��ô˺���*/
int resume()
{return 0;}

/*����*/
void drawtext(char *text,int x,int y,uint8 r,uint8 g,uint8 b)
{
  dtext(text,x,y,r,g,b,FALSE,1);
}

/*����Ļ��Χ�ľ��ο��ﷴ�������гɾ���Ч��*/
void drawCopy(int x,int y,int w,int h)
{
 uint16 *scr=getscrbuf()-(SCRH-(y+h))*2;
 int nn;
 for(int n=y;n<y+h;n++)
 {
 if(n>SCRH)break;
 nn++;
 memcpy(scr+n*SCRW+x,scr+(n-nn*2)*SCRW+x,w*2);
 ref(x,y,w,h);
 }

}

//by:����Tt