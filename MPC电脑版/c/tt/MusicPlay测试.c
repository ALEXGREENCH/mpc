#include <base.h>
#include <c/tt/MusicPlay.h>

int init(void)
{
//��ʼ��(����ȷ�����ļ���)
 if(-1==MPInit("My Music/���� - ����Ľ���.mp3"))
 exit();//��ʼ��ʧ�ܺ��˳�
 return 0;
}

int event(int type, int p1, int p2)
{
//�������
 MPEvent(type,p1,p2);

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