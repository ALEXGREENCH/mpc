#include <base.h>
#include <c/win/tt.h>
#include <c/win/windef.h>
#include <c/win/winfunc.h>


win_obj *obj;
window *win;

uint16 win_index=0;
int tw,th;
textwh("��",0,1,&tw,&th);


/*
* �����¼�
* ����:
 msg �����¼�(��ϸ��windef.h)
 ��Ϊ�������p0,p1 Ϊ������꣬��Ϊ���������Ϊ -1
*/
int winEvent(window *pWin,uint8 msg,int p1,int p2)
{
 uint16 id=pWin->id;
 switch(msg)
 {
 case WIN_CREATE:
 echo("������id",id);
 break;

 case WIN_DESTROY:
 echo("��������id",id);

 break; 
 case WIN_SHOW:
 echo("����ʾid",id);
 break;

 case WIN_CLICK:
 echo("�����id",id);
 break;
 }
 return 0;
}

int init(void)
{
 cls(255,255,255);
 ref(0,0,SCRW,SCRH);
 colorst rgb,rgb2;
 rgbSet(&rgb,0,0,0);
 rgbSet(&rgb2,255,2,2);
 win=winCreate(win_index,0,0,SCRW,th); //��������
 winSet(win,&rgb,&rgb2); //������ʽ����
 winShow(win); //��ʾ����
 return 0;
}

int event(int type, int p1, int p2)
{
 if(KY_DOWN == type)
 switch(p1)
 {
  case _SRIGHT:
  exitapp();

  break;
  case _1:
  break;
 }
 return 0;
}

int pause(void)
{
  return 0;
}

int resume(void)
{
 return 0;
}

/*�����˳�*/
void exitapp()
{
 winDel(win);//���ٴ���
 sleep(500);
 exit();
}
