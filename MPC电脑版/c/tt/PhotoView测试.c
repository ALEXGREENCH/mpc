#include <base.h>
#include <c/tt/PhotoView.h>

int init(void)
{
//��ʼ�����(����ȷ�����ļ���)
 if(-1==PVInit("c/tt/By����.jpg"))
 exit();//��ʼ��ʧ���˳�

 return 0;
}

int event(int type, int p1, int p2)
{
/*�������*/
 PVEvent(type,p1,p2);

 if(KY_DOWN==type)
 {
 switch(p1)
  {
  case _SRIGHT:
  exit();
  break;
  }
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