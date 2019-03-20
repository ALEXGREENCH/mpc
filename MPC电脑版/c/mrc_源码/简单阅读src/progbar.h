#ifndef PROGBAR_H
#define PROGBAR_H

//��������(6369)
//create date 2012-7-19


typedef struct
{
int x;int y;int w;int h;
int32 allid;//ȫ���Ľ���id(����)��(һ���ж��ٸ����ȵ�ֵ)
int32 nowid;//��ǰ�Ľ���id
int32 bgclr;//����
int32 qgclr;//ǰ��

}Prog,*PProg;

/*����һ��������
x, y, w, h   ����λ��
qgclr  ǰ����ɫ
bgclr  ������ɫ
����ֵ
   0  ����ʧ��
   >0  ����ָ��
*/

PProg progBarCreate(int x, int y, int w, int h, int32 bgclr, int32 qgclr);



/*ɾ��������
*/
void progBarDel(PProg a);



/*���ý�����ȫ������id����

a ���������
id ������id����
����ֵ����

*/

void setProgBarAllId(PProg a, int32 id);

/*���õ�ǰ�Ľ���id
a  ���������
id ��ǰ��id
����ֵ����
*/ 


void setProgBarNowId(PProg a, int32 id);


/*��������ǰid�ƶ�
a  ���������
is_next �Ƿ������ƶ�
  1 ����
  2 ����
����ֵ ��
*/
void progBarNowIdNext(PProg a, int is_next);


/*���ƹ�����
 a  ���������
����ֵ ��
*/
void drawProgBar(PProg a);


#endif