
/*��������(6369)
2012-7-11*/

#include "mrc_base.h"
#include "mrc_exb.h"

#include "type.h"
#include "menu.h"

/*����һ���˵�
 rect �˵�λ�ã���С
 �˵��߶ȼ��㷽ʽΪ��
   (����߶�+5)*�˵�����+4
  ������Ϊ��������+20
 num �˵�����Ŀ

 ����ֵ��
  0 �����˵�ʧ��
  ��0 ָ��˵��ڴ��ָ��
*/
PMenu menuCreate(int x,int y,int w,int h, int num)
{
	int i;
  PMenu a;
  a = (PMenu)mrc_malloc(sizeof(Menu));

  if(a == NULL) return 0;

  a -> x = x;
a->y=y;
a->w=w;
a->h=h;
a->focus=0;
  a -> num = num;
  for(i = 0; i<num; i++)
  {
    a -> item[i] = (char*)mrc_malloc(MAX_ITEMSIZE*sizeof(char));
    if(a->item[i]==NULL)
{mrc_free(a);return 0;}
    mrc_memset(a->item[i], 0, sizeof(a->item[i]));
  }
return a;
}


/*ɾ��һ���˵�
 a �˵���ָ��
 
 ����ֵ����
*/
void menuDel(PMenu a)
{
	int i;
  for(i = 0; i<a->num; i++)
    mrc_free(a->item[i]);
  mrc_free(a);
  a= 0;
}


/*����һ���˵���
  a �˵����
  index �˵������
  title �˵�������
  
  ����ֵ��-1  ʧ��
             0 �ɹ�
*/
int setMenuItem(PMenu a,int index, char* title)
{
  if(index >= a->num) return -1;
  mrc_memcpy(a->item[index],title, MAX_ITEMSIZE);
  return 0;
}
 

/*���ò˵�����
  a �˵����
  index �˵������
  
  ����ֵ��
    -1  ʧ��
    0 �ɹ�
*/

int setMenuFocus(PMenu a, int index)
{
  if(a->num <= index) return -1;
  a->focus = index;
  return 0;
}

/*��ò˵�����
  a  �˵����
����ֵ ����
*/
int getMenuFocus(PMenu a)
{
  return a->focus;
}


/*�˵������ƶ�
  a  �˵����
  is_next  �Ƿ������ƶ�
    1 ����
    0 ����
  
  ����ֵ ����
*/
void menuFocusNext(PMenu a, int is_next)
{
  if(is_next)
  {
    a -> focus++;
    if(a -> focus >= a->num) 
      a -> focus = 0;

  }
  else
  {
    a -> focus--;
    if(a->focus<0)
      a->focus = a->num - 1;
      
  }
  menuDraw(a);
}



/*��ʾ�˵�
  a  �˵����
  ����ֵ����
*/
void menuDraw(PMenu a)
{
  int x, y, w, h;
  int32 zw, zh;
  int i;
  x = a->x; y = a->y; w = a -> w; h= a->h;

  mrc_drawRect(x, y, w, h, MAKER(MENUBG)/2, MAKEG(MENUBG)/2, MAKEB(MENUBG)/2);
  mrc_drawRect(x+1, y+1, w-2, h-2, MAKER(MENUBG), MAKEG(MENUBG), MAKEB(MENUBG));
  mrc_textWidthHeight("��", 0, FONT, &zw, &zh);
  zh+=5;
  shaderect(x+2, y+2+(a->focus*zh), w-4, zh, MENUFOCUS, MENUFOCUS-MENUFOCUS/5,0);
  for(i = 0; i<(a->num); i++)
  {
    if(i == a->focus)
      mrc_drawText(a->item[i], x+10, y+2+(i*zh)+2,MAKER(MENUBG), MAKEG(MENUBG), MAKEB(MENUBG),0 , FONT);
    else
       mrc_drawText(a->item[i], x+10, y+2+(i*zh)+2,MAKER(MENUITEM), MAKEG(MENUITEM), MAKEB(MENUITEM),0 , FONT);
  }

}


