#ifndef TOOLBAR_H
#define TOOLBAR_H
//��������(6369)
//create date 2012-7-17


typedef struct
{
	int x;int y;int w;int h;
	int32 upclr;
	int32 downclr;
	int32 titclr;
	char* left;
	char* zhon;
	char* right;
}Tool,*PTool;


/*����������
x,y,w,h ����λ�ô�С
upclr �������ϲ���ɫ
downclr �²���ɫ
titclr ������ɫ
left �������
zhon �м�
right �ұ�
����ֵ ָ���������ָ��
*/

PTool toolBarCreate(int x,int y,int w,int h,int32 upclr,int32 downclr,int32 titclr,char* left,char* zhon,char* right);

/*ɾ��������*/

void toolBarDel(PTool a);


/*���Ʊ�����*/

void drawToolBar(PTool a);

#endif