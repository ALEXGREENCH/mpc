#ifndef TITLEBAR_H
#define TITLEBAR_H
//��������(6369)
//create date 2012-7-17



typedef struct
{
int x;int y;int w;int h;
int32 upclr;
int32 downclr;
int32 titclr;
char*title;
}Title,*PTitle;

/*����������
x,y,w,h ����λ�ô�С
upclr �������ϲ���ɫ
downclr �²���ɫ
titclr ������ɫ
title ��������
����ֵ ָ���������ָ��
*/

PTitle titleBarCreate(int x,int y,int w,int h,int32 upclr,int32 downclr,int32 titclr,char* title);


/*ɾ��������*/

void titleBarDel(PTitle a);



/*���Ʊ�����*/

void drawTitleBar(PTitle a);

#endif