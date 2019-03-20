#ifndef EDIT_H
#define EDIT_H

/*��������(6369)
2012-7-10*/

#define TITMAX 20//�����������
#define SPEED 800//����ٶȣ���Ч


typedef struct
{
int x; int y; int w; int h;
char* title;
char* str;
int32 titleclr;
int32 bkclr;
int32 bgclr;

int max;
int type;
int timeEdit;
int speed;
}Edit,*PEdit;


/*����һ���༭��
������
@ x��y��w��h���༭��ߴ�
@ title �༭�����( <=20)
@ str �༭������
@ titleclr ������ɫ
@ bkclr �߿���ɫ
@ bgclr ������ɫ
@ max �����������
@ type�༭�����ͣ�
     0: ȫ��
     1���ַ�
     2������
����ֵ��
 0 ����ʧ��
 >0 �༭��ָ��
*/
PEdit editCreate(int x, int y, int w, int h, char* title,char* str, int32 titleclr, int32 bkclr, int32 bgclr, int max, int type);

/*ɾ���༭��
������
 a���༭��ָ��
����ֵ����
*/
void editDel(PEdit a);

/*���ý���༭��
@ a ���༭��ָ�룬
*��ΪNULLʱ���൱�����ر༭��
*ע�⣺�뱣ָ֤��Ϸ��ԣ������������������
����ֵ����Ч
 */

int setEditFocus(PEdit a);


//�õ��༭������
char* getEditStr(PEdit a);



/*���Ʊ༭��
*/
void editDraw(PEdit a);

//����༭����ص�(������ʱ����
void _editTime(int a);


//����༭���¼�����
int editEvent(PEdit a,int msg,int p1,int p2);

#endif
