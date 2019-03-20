#ifndef TEXTFUN_H
#define TEXTFUN_H

//��������(6369)
//create date 2012_7_18
#include "scrollbar.h"

typedef struct
{
int x;int y;int w;int h;
int32 bgclr;
int32 chclr;
char* text;
int nowline;//�ڼ���
int allline;//һ�����л�
int pageline;//ÿҳ����
int th;//ÿ�и�
PScroll scroll;
}Textfun,*PTextfun;


/*�����ı���*/

PTextfun textFunCreate(int x,int y,int w,int h,int32 bgclr,int32 chclr,char* text);



/*ɾ���ı���*/
void textFunDel(PTextfun a);




/*�ı������ַ���*/

void textFunLineNext(PTextfun a,int is_next);


/*�����ı���*/

void drawTextFun(PTextfun a);


#endif
