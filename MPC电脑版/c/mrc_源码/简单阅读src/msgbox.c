//��������(6369)
//create date 2012-7-13


#include "type.h"
#include "msgbox.h"


/*��ʾ��ʾ��(800)ms����ʧ

title ��ʾ����
*/

void showMsgBox(char*title)
{
int32 zw,zh,x,y;
int r,g,b;
make(MSGBOXBK,&r,&g,&b);
mrc_textWidthHeight(title,0,FONT,&zw,&zh);
zw+=10;zh+=5;
x=(SCRW-zw)/2;
y=(SCRH-zh)/2;
mrc_drawLine(x+1,y,x+zw-1,y,r,g,b);
mrc_drawLine(x+1,y+zh,x+zw-1,y+zh,r,g,b);
mrc_drawLine(x,y+1,x,y+zh-1,r,g,b);
mrc_drawLine(x+zw,y+1,x+zw,y+zh-1,r,g,b);
make(MSGBOXBG,&r,&g,&b);
mrc_drawRect(x+1,y+1,zw-1,zh-1,r,g,b);
make(MSGBOXCH,&r,&g,&b);
mrc_drawText(title,x+5,y+3,r,g,b,0,FONT);
mrc_refreshScreen(x,y,zw+1,zh+1);
//mrc_sleep(800);
}
//ע�����µĺ���Ϊ���ڼ��Ķ�mpc��ʹ�ã�Ϊ�ѷ���������ʹ�á�����ɾ����������Ķ�mpc���޷�����

/*��ʾ������
x y w h ��������λ������
uclr��dclr�������ϲ���ɫ���²���ɫ 888��ʽ(0x00005500)(��ɫ)
tclr ������ɫ ͬ��
title ����
*/


void showTitleBar(int x,int y,int w,int h,int32 uclr,int32 dclr,int32 tclr,char* title)
{
int32 zw,zh;
mrc_textWidthHeight(title,0,FONT,&zw,&zh);
shaderect(x,y,w,h,uclr,dclr,0);
mrc_drawText(title,x+2,y+(h-zh)/2,MAKER(tclr),MAKEG(tclr),MAKEB(tclr),0,FONT);

}

/*��ʾ������
x y w h λ����Ϣ
uclr dclr tclr �����ϡ�����ɫ��������ɫ
left �������
zhon �м�
right �ұ�
*/
void showToolBar(int x,int y,int w,int h,int32 uclr,int32 dclr,int32 tclr,char* left,char* zhon,char* right)
{
int32 zw,zh;
int r,g,b;
mrc_textWidthHeight(left,0,FONT,&zw,&zh);
shaderect(x,y,w,h,uclr,dclr,0);
make(tclr,&r,&g,&b);
mrc_drawText(left,x+2,y+(h-zh)/2,r,g,b,0,FONT);
mrc_textWidthHeight(zhon,0,FONT,&zw,&zh);
mrc_drawText(zhon,x+(w-zw)/2,y+(h-zh)/2,r,g,b,0,FONT);
mrc_textWidthHeight(right,0,FONT,&zw,&zh);
mrc_drawText(right,x+w-zw-2,y+(h-zh)/2,r,g,b,0,FONT);
}