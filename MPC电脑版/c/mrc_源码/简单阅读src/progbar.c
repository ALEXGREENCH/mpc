//��������(6369)
//create date 2012-7-19

#include "mrc_base.h"
#include "type.h"
#include "progbar.h"


/*����һ��������
x, y, w, h   ����λ��
qgclr  ǰ����ɫ
bgclr  ������ɫ
����ֵ
   0  ����ʧ��
   >0  ����ָ��
*/

PProg progBarCreate(int x, int y, int w, int h, int32 bgclr, int32 qgclr)
{
  PProg a;

  a = mrc_malloc( sizeof(Prog));
  if( a == 0 ) return 0;

  a->x = x;
  a->y = y;
  a->w = w;
  a->h = h;
  a->bgclr = bgclr;
  a->qgclr = qgclr;
  a->allid = 0;
  a->nowid = 0;
  return a;
}


/*ɾ��������
*/
void progBarDel(PProg a)
{
  mrc_free(a);
  a=0;
}

/*���ý�����ȫ������id����

a ���������
id ������id����
����ֵ����

*/

void setProgBarAllId(PProg a, int32 id)
{
  a->allid = id;
}
 

/*���õ�ǰ�Ľ���id
a  ���������
id ��ǰ��id
����ֵ����
*/ 


void setProgBarNowId(PProg a, int32 id)
{
  a->nowid = id;
}

/*��������ǰid�ƶ�
a  ���������
is_next �Ƿ������ƶ�
  1 ����
  2 ����
����ֵ ��
*/
void progBarNowIdNext(PProg a, int is_next)
{
if(is_next)
  {a->nowid++;
if(a->nowid>=a->allid)
a->nowid=a->allid;
}
else
{  a->nowid--;
if(a->nowid<=0)
  a->nowid=0;
}


drawProgBar( a );
}


/*���ƹ�����
 a  ���������
����ֵ ��
*/
void drawProgBar(PProg a)
{
  int r,g,b;
  int x, y, w, h;//����λ�á���С

  make(a->bgclr,&r, &g, &b);
  mrc_drawRect(a->x, a->y, a->w, a->h, r/2, g/2, b/2);
  mrc_drawRect(a->x+1, a->y+1, a->w-2, a->h-2, r, g, b);
  x = a->x ;
  
  y = a->y ;w=a->nowid*(a->w)/a->allid;
h=a->h;
  make(a->qgclr, &r, &g, &b);
  //dline(x+1, y, x+w-2, y, r, g, b);
  //dline(x+1, y+h-1, x+w-2, y+h-1, r, g, b);
  //dline(x, y+1, x, y+h-2, r, g, b);
  //dline(x+w-1, y+1, x+w-1, y+h-2,r, g, b);
  mrc_drawRect(x+1, y+1, w-2, h-2, r, g, b);
}