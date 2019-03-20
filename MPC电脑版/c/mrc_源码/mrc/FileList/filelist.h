/**
 ** filelist.h the declare of filelist.c
 ** 
 ** �ļ��б� ���������װ ����
 **
 ** @Author Jianbin Zhu 2011/9/13
 **
 ** ����޸����ڣ�2011/11/16
 **/

#ifndef	_RX_FILELIST_ 
#define _RX_FILELIST_


//#include "appdef.h"
#include "mrc_base.h"


typedef unsigned char boolean;	//���� ��������

#ifndef false
#define false 0
#endif

#ifndef true
#define true 1
#endif

//�����ֵ
#ifndef ABS
#define ABS(x)              (((x)<0) ? -(x) : (x))
#endif

//���һ���ַ��ǲ���Сд��ĸ
#ifndef IS_SMLETTER
#define IS_SMLETTER(i)		((i >= 97) && (i <= 122))
#endif

//�ļ���ʽö�٣�1�ֽ�|��
typedef enum
{
	FILE_UNDEFINE=-1,		//��ʼ״̬δ����
	FILE_FOLDER=0x0001,		//�ļ���
	FILE_TEXT=0x0002,		//�ı��ļ�
	FILE_ARCHIVE=0x0004,	//ѹ���ļ�
	FILE_AUDIO=0x0008,		//�����ļ�
	FILE_IMAGE=0x0010,		//ͼ���ļ�
	FILE_MRP=0x0020,		//MRP�ļ�
	FILE_REG=0x0040,		//��Ϸע���ļ�
	FILE_UNTYPE=0xffff		//�������ļ�(��ָ�ļ������е������ļ�)
}FILE_Format;

//�Ƚ������ļ�������
typedef enum
{
	CMPBY_NAME,
	CMPBY_SIZE,
	CMPBY_DATE
}FILE_CmpCond;

//�ļ�ʵ��
typedef struct _file
{
	char	*name;		//��ָ��(GB����)
	int		format;		//��ʽ
	int		length;		//��С

	boolean b_isHiden;	//�Ƿ�����
	boolean b_checked;	//�Ƿ�ѡ��
	boolean	b_isFile;	//����

	struct _file *next;		//��һ��
	struct _file *prev;		//��һ��
}FILE, *PFILE;


//�б��ʼ���������������κη���֮ǰ���ã�
void FL_init(boolean dirFirst, boolean order_ascending, int order_by);
//��Ĭ�����ݳ�ʼ��
#define  FL_initDef() \
	FL_init(true, true, CMPBY_NAME)

//�ļ����췽��
PFILE F_new(char *name, int nameLen, boolean isFile, int format, boolean isHiden);

#define F_new1(name, nameLen, isFile) \
	F_new(name, nameLen, isFile, FILE_UNDEFINE, false)

#define F_new2(name, nameLen, isFile, format) \
	F_new(name, nameLen, isFile, format, false)

//���б��β��׷��ָ�����ļ�
void FL_add(PFILE pf);
//���б�׷�Ӳ�����������ʵʱ��̬����
void FL_add_sortByName(PFILE pf);

//���б����Ƴ������ļ� 
void FL_clear(void);

//�����б���ָ��λ�õ��ļ�
PFILE FL_get(int index);
//��ȡָ������ļ���
char* FL_getName(int index);
//��ȡָ������ļ���ʽ
FILE_Format FL_getFormat(int index);
//��ȡ�б��ļ���
int FL_getFCount(void);
//��ȡ�б�Ŀ¼��
int FL_getDCount(void);
//��ȡָ������ļ��Ƿ�ѡ��
boolean FL_isChecked(int index);
//��ȡָ����Ų����ļ�
boolean FL_isFile(int index);
//��ȡָ������ļ��Ƿ�����
boolean FL_isHiden(int index);

//�����б����״γ���ָ��Ԫ�ص�����������б�������Ԫ�أ��򷵻� -1��
int FL_indexOf(PFILE pf);

//����б�����Ԫ�أ��򷵻� true.
boolean FL_isEmpty(void);

//�Ƴ��б���ָ��λ�õ�Ԫ�أ���ѡ�������� 
void FL_remove(int index);

//��ָ��Ԫ���滻�б���ָ��λ�õ�Ԫ�أ���ѡ��������
void FL_set(int index, PFILE pf); 

//�����б��е�Ԫ������ 
int FL_size(void);

//ѡ��ָ���ļ�
void FL_check(int index, boolean checked);

#endif