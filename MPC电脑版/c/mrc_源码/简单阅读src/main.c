/*���Ķ�MPC��v2.01��
���ߣ���������(6369)
������վ��wap.mrpej.com


�����ļ������
�Ķ����棺
 �������2��4��6��8����ҳ��
 1���������롣
 3������n�ֽ�
 7���л�ȫ����
 9�����ñ߿���
 *���ļ���ʼ
 #���ļ�ĩβ
 0���л�Ƥ��

�ļ�������棺
 ���·�����������ƶ�
 ȷ�����������ѡ��
 ������������ϼ�Ŀ¼����Ŀ¼�򷵻��Ķ�����

������沦�ż���ͼ

*/
//#define FONT 1
#include "mrc_base.h"
//#include "../controls/type.h"
#include "read.h"
#include "win.h"
#include "filefind.h"
#include "readmenu.h"
#include "jump.h"
#include "BK.h"
#include "LineSize.h"
#include "Screen.h"
#include "msgbox.h"

WIN win;
int32 FONT;
int32 mrc_init(void)
{
	win = WIN_FILEFIND;
	FONT = 1;
    readInit("");
    menuInit();
    fileFindInit();
//    downPaiBan();
    return MR_SUCCESS;
}

int32 mrc_appEvent(int type, int p1, int p2)
{
switch(win)
{
case WIN_READ:
  readEvent(type,p1,p2);
  break;
case WIN_FILEFIND:
  fileFindEvent(type,p1,p2);
break;
case WIN_MENU:
  menuEvent(type,p1,p2);
  break;
case WIN_INJUMP:
  inJumpEvent(type,p1,p2);
  break;
case WIN_INBK:
inBKEvent(type,p1,p2);
break;
case WIN_INLINESIZE:
inLineSizeEvent(type,p1,p2);
break;
}
  if(p1==MR_KEY_SEND&&type==MR_KEY_RELEASE){
    ScreenShut("���Ķ���ͼ.bmp",0,0,SCRW,SCRH,1);
    
  }
  return MR_SUCCESS;
}

int32 mrc_pause(void)
{
saveScreenBuf();
    return MR_SUCCESS;
}

int32 mrc_resume(void)
{
readScreenBuf();
mrc_refreshScreen(0,0,SCRW,SCRH);
    return MR_SUCCESS;
}

int32 mrc_exitApp(void)
{
	showMsgBox("�����˳�������");
	  mrc_platEx( 1204, "c:/MYTHROAD", 11, NULL, NULL, NULL );
	
	fileFindExit();
	menuExit();
	readExit();
return MR_SUCCESS;
}