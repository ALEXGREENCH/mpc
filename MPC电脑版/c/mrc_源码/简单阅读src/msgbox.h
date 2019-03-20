#ifndef _MSGBOX_H
#define _MSGBOX_H


//��������(6369)
//create date 2012-7-13
#include "mrc_base.h"

#define MSGBOXBK 0x00ff0000
#define MSGBOXBG 0x000011ff
#define MSGBOXCH 0x00ffffff


/*��ʾ��ʾ��(800)ms����ʧ

title ��ʾ����
*/

void showMsgBox(char*title);

//ע�����µĺ���Ϊ���ڼ��Ķ�mpc��ʹ�ã�Ϊ�ѷ���������ʹ�á�����ɾ����������Ķ�mpc���޷�����

/*��ʾ������
x y w h ��������λ������
uclr��dclr�������ϲ���ɫ���²���ɫ 888��ʽ(0x00005500)(��ɫ)
tclr ������ɫ ͬ��
title ����
*/
void showTitleBar (int x,int y,int w,int h,int32 uclr,int32 dclr,int32 tclr,char* title);


/*��ʾ������
x y w h λ����Ϣ
uclr dclr tclr �����ϡ�����ɫ��������ɫ
left �������
zhon �м�
right �ұ�
*/
void showToolBar(int x,int y,int w,int h,int32 uclr,int32 dclr,int32 tclr,char* left,char* zhon,char* right);

#endif