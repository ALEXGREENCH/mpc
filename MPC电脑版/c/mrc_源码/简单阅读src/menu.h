
/*��������(6369)
2012-7-11*/
#ifndef MENU_H
#define MENU_H

#define MAX_NUM 20//���˵���
#define MAX_ITEMSIZE 10//�˵����������
#define MENUBG 0x00ffffff//�˵�����
#define MENUITEM 0x00000000//�˵���
#define MENUFOCUS 0x0000ff00//�˵�����


typedef struct
{
  int x;int y;int w;int h;
  int num;
  int focus;
  char* item[MAX_ITEMSIZE];
}Menu,*PMenu;

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
PMenu menuCreate(int x,int y,int w,int h, int num);




/*ɾ��һ���˵�
 a �˵���ָ��
 
 ����ֵ����
*/
void menuDel(PMenu a);





/*����һ���˵���
  a �˵����
  index �˵������
  title �˵�������
  
  ����ֵ��-1  ʧ��
             0 �ɹ�
*/
int setMenuItem(PMenu a,int index, char* title);


/*���ò˵�����
  a �˵����
  index �˵������
  
  ����ֵ��
    -1  ʧ��
    0 �ɹ�
*/

int setMenuFocus(PMenu a, int index);


/*��ò˵�����
  a  �˵����
����ֵ ����
*/
int getMenuFocus(PMenu a);



/*�˵������ƶ�
  a  �˵����
  is_next  �Ƿ������ƶ�
    1 ����
    0 ����
  
  ����ֵ ����
*/
void menuFocusNext(PMenu a, int is_next);



/*��ʾ�˵�
  a  �˵����
  ����ֵ����
*/
void menuDraw(PMenu a);

#endif