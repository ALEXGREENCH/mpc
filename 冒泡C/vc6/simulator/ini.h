#ifndef __INI_H__
#define  __INI_H__
extern "C"
{
	#include "mrporting.h"	
}
typedef enum
{
	INI_MEMORY,
	MAX_INI_EXTERN_ID
}T_INI_EXTERN_ID;

typedef enum
{
	INI_KEY_0,               //���� 0
	INI_KEY_1,               //���� 1
	INI_KEY_2,               //���� 2
	INI_KEY_3,               //���� 3
	INI_KEY_4,               //���� 4
	INI_KEY_5,               //���� 5
	INI_KEY_6,               //���� 6
	INI_KEY_7,               //���� 7
	INI_KEY_8,               //���� 8
	INI_KEY_9,               //���� 9
	INI_KEY_STAR,            //���� *
	INI_KEY_POUND,           //���� #
	INI_KEY_UP,              //���� ��
	INI_KEY_DOWN,            //���� ��
	INI_KEY_LEFT,            //���� ��
	INI_KEY_RIGHT,           //���� ��
	INI_KEY_POWER,           //���� �һ���
	INI_KEY_SOFTLEFT,        //���� �����
	INI_KEY_SOFTRIGHT,       //���� �����
	INI_KEY_SEND,            //���� ������
	INI_KEY_SELECT,          //���� ȷ��/ѡ����������м���ȷ�ϼ���������Ϊ�ü���
	INI_KEY_VOLUME_UP,          //���� �����
	INI_KEY_VOLUME_DOWN,          //���� �����
	INI_KEY_CLEAR,
	INI_KEY_NONE,             //���� ����
	INI_128_XO,
    INI_128_X1,
	INI_128_YO,
	INI_128_Y1,
	INI_176_XO,
    INI_176_X1,
	INI_176_YO,
	INI_176_Y1,
	INI_240_XO,
    INI_240_X1,
	INI_240_YO,
	INI_240_Y1,
	MAX_INI_INSIDE_ID
}T_INI_INSIDE_ID;


typedef struct
{
	char *string;
}T_INI_DATA;

typedef struct  {
	int x0;
	int x1;
	int y0;
	int y1;
}COORDINATE;

void iniInit(void);
int32 getSreenSize(void);
char *getInsideString(int32 index);

COORDINATE *getScreenSite(void);


#endif



