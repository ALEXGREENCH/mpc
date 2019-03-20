#ifndef __PLAT_H__
#define  __PLAT_H__
extern "C"
{
	#include "mrporting.h"	
}
#define MAX_LIST_NO       256
#define MAX_LIST_LEN       128
#define PLATEX_LISTBOXSELECT 1 //����������ѡ��
#define PLATEX_LISTBOXITEM 2//���õ�����ѡ��
 enum
{
	MR_LIST_NO_ICON  ,   //(û����ʾ��ŵ�) 
	MR_LIST_NORMAL_ICON ,//(һ���list�ģ��������menu�Ľӿ���ʵ��)
	MR_LIST_SINGLE_SEL , //(��ѡ��)
	MR_LIST_MUTI_SEL    //(��ѡ��)
		
};

typedef struct
{
	int32 menu;     //list�ľ��
	char *text;     //��һ�������(���unicode)
	int32 index;    //��һ��������list�е�λ��(��0��ʼ)
	int32 selected; //��һ���Ƿ���Ϊѡ��(1��ѡ�У�0��δѡ��)
}MMIMR_LISTBOXITEM_T;

typedef struct
{
	char *title;     //����(���unicode ����)
	int16 itemNum;   //list ����Ŀ����
	int16 listType;  //����
}MMIMR_LISTBOXSELECT_T;

typedef struct  {
	char title[MAX_LIST_LEN];
	char *items[MAX_LIST_NO];
	int32 selected[MAX_LIST_NO];
	int16 itemNum;
	int32 index;
	int16 listType;
}T_WIN_LIST;

int32 createListBox(uint8 *p);
int32 setListBox(uint8 *p);
#endif



