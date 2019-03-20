#ifndef _SCROLLBAR_H
#define _SCROLLBAR_H

//��������(6369)
//create date 2012-7-17
#include "mrc_base.h"

typedef struct
{
int x;
int y;
int w;
int h;
int32 allid;//ȫ���Ĺ���id(����)��(һ���ж��ٸ�������ֵ)
int32 nowid;//��ǰ�Ĺ���id
int pagesize;//ÿҳ������ʾ����
int32 bgclr;//����
int32 qgclr;//ǰ��

}Scroll,*PScroll;

/*����һ��������
x, y, w, h   ����λ��
qgclr  ����������ɫ
bgclr  ������ɫ
����ֵ
   0  ����ʧ��
   ��0  ���ھ��
*/

PScroll scrollBarCreate(int x, int y, int w, int h,int pagesize, int32 bgclr, int32 qgclr);


/*ɾ��������
*/
void scrollBarDel(PScroll a);



/*���ù�����ȫ������id����

a ���������
id ����id����
����ֵ����

*/

void setScrollBarAllId(PScroll a, int32 id);

 

/*���õ�ǰ�Ĺ���id
a  ���������
id ��ǰ��id
����ֵ����
*/ 


void setScrollBarNowId(PScroll a, int32 id);


/*��������ǰid�ƶ�
a  ���������
is_next �Ƿ������ƶ�
  1 ����
  2 ����
����ֵ ��
*/
void scrollBarNowIdNext(PScroll a, int is_next);



/*���ƹ�����
 a  ���������
����ֵ ��
*/
void drawScrollBar(PScroll a);



#endif