#include <base.h>
#include <c/tt/BookView.h>

int init(void)
{
//��ʼ��(����ȷ�����ļ���)
 if(-1==BVInit("c/tt/��һ������.txt"))
 exit();//��ʼ��ʧ���˳�
 return 0;
}

int event(int type, int p1, int p2)
{
//�������
 BVEvent(type,p1,p2);
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