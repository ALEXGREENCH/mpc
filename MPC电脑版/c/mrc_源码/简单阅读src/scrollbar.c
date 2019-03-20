//��������(6369)
//create date 2012-7-17


#include "type.h"
#include "scrollbar.h"
//#define SCROLLBGCLR 0x000000

/*����һ��������
x, y, w, h   ����λ��
qgclr  ����������ɫ
bgclr  ������ɫ
����ֵ
   0  ����ʧ��
   ��0  ���ھ��
*/

PScroll scrollBarCreate(int x, int y, int w, int h,int pagesize, int32 bgclr, int32 qgclr)
{
  PScroll a;

  a = mrc_malloc( sizeof(Scroll));
  if( a == 0 ) return 0;

  a->x = x;
  a->y = y;
  a->w = w;
  a->h = h;
  a->pagesize=pagesize;
  a->bgclr = bgclr;
  a->qgclr = qgclr;
  a->allid = 0;
  a->nowid = 0;
  return a;
}


/*ɾ��������
*/
void scrollBarDel(PScroll a)
{
  mrc_free(a);
  a=0;
}

/*���ù�����ȫ������id����

a ���������
id ����id����
����ֵ����

*/

void setScrollBarAllId(PScroll a, int32 id)
{
  a->allid = id;
}
 

/*���õ�ǰ�Ĺ���id
a  ���������
id ��ǰ��id
����ֵ����
*/ 


void setScrollBarNowId(PScroll a, int32 id)
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
void scrollBarNowIdNext(PScroll a, int is_next)
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

drawScrollBar( a );
}


/*���ƹ�����
 a  ���������
����ֵ ��
*/
void drawScrollBar(PScroll a)
{
  int r,g,b;
  int x, y, w, h;//����λ�á���С

  make(a->bgclr,&r, &g, &b);
  mrc_drawRect(a->x, a->y, a->w, a->h, r/2, g/2, b/2);
  mrc_drawRect(a->x+1, a->y+1, a->w-2, a->h-2, r, g, b);
  x = a->x ;
  
  w = a->w ;
  if(a->allid <= a->pagesize)
    {h = a->h-2;
    y = a->y+1;}
  else
    {h =(a->h*a->pagesize)/a->allid;
if(h<5)h=5;
    y=a->nowid*(a->h-h)/a->allid+a->y;}
  make(a->qgclr, &r, &g, &b);
  mrc_drawLine(x+1, y, x+w-2, y, r, g, b);
  mrc_drawLine(x+1, y+h-1, x+w-2, y+h-1, r, g, b);
  mrc_drawLine(x, y+1, x, y+h-2, r, g, b);
  mrc_drawLine(x+w-1, y+1, x+w-1, y+h-2,r, g, b);
  mrc_drawRect(x+1, y+1, w-2, h-2, r, g, b);
}