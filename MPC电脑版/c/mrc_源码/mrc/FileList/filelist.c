/**
 ** filelist.c the implement of filelist.h
 ** 
 ** �ļ��б� ���������װ ����
 **
 ** ע��1.�б���Ŵ�1��ʼ
 ** 
 ** @Author Jianbin Zhu 2011/9/13
 **/

#include "filelist.h"
#include "mrc_base.h"


static struct 
{
	FILE head;	//�̶�����ͷ���
	PFILE pEnd; //����ָ���������һ���ڵ�

	int size;	//����
	int fc, dc;	//�ļ�����Ŀ¼��
	boolean b_dirFirst;	//����Ŀ¼��ǰ
	boolean b_order_ascending;	//��������
	int i_order_by;	//��������

	/**
	 * Ϊ�˱���ÿ�η���ĳ��Ԫ�ص�ʱ�򶼴ӵ�һ����ʼ��
	 * ����������������
	 */
	PFILE pCur;		//����ָ��ǰ���ʵĽڵ�
	int cur_index;	//��ǰ���ʵĽڵ����� ��1��ʼ
}listData;


//�ͷ�һ���ļ�ʵ��
#define F_free(pf) \
	do { \
		if(pf) \
		{	\
			if(pf->name) \
				free(pf->name); \
			free(pf); \
			pf = NULL; \
		}	\
	} while (0);


void FL_init(boolean dirFirst, boolean order_ascending, int order_by)
{
	memset(&listData, 0, sizeof(listData));
	listData.head.prev = NULL;
	listData.head.next = NULL;
	listData.pEnd = &listData.head;
	listData.b_dirFirst = dirFirst;
	listData.b_order_ascending = order_ascending;
	listData.i_order_by = order_by;
}

PFILE F_new(char *name, int nameLen, boolean isFile, int format, boolean isHiden)
{
	PFILE tmp;
	char *str;
	static int i;

	if(!name) return NULL;

	tmp = (PFILE)malloc(sizeof(FILE));
	if(!tmp) return NULL;

	str = (char *)malloc(nameLen + 1);
	if(!str) {free(tmp); return NULL;};
	memcpy(str, name, nameLen);
	str[nameLen] = 0;

	tmp->b_checked = false;
	tmp->b_isFile = isFile;
	tmp->b_isHiden = isHiden;
	tmp->format = format;
	tmp->length = -2;	//Ĭ�ϳ�ʼ��Ϊ-2��˵������δ��ʼ��
	tmp->next = NULL;
	tmp->prev = NULL;
	tmp->name = str;

	mrc_printf("new file success %d !", ++i);
	//����
	if(isFile) listData.fc++;
	else listData.dc++;

	return tmp;
}

void FL_add(PFILE pf)
{
	if(!pf) return;

	listData.pEnd->next = pf;
	listData.size++;
	listData.pEnd = pf;
}


/**
 * \ͨ���ض������Ƚ������ļ���
 * �� scr �� dst �󣺷��� >0
 * �� src �� dst С������ <0
 * �� src = dst ������ =0
 **/
static int F_cmp(FILE_CmpCond by, PFILE src, PFILE dst)
{
	switch(by)
	{
	case CMPBY_NAME:	//�����ƱȽ�
		{
			int a, b;

			//�������ĸ
			a = (uint8)src->name[0]; 
			if(IS_SMLETTER(a)) a -= 32;

			b = (uint8)dst->name[0]; 
			if(IS_SMLETTER(b)) b -= 32;

			return a-b;
		}
		break;

	case CMPBY_DATE:	//�����ڱȽ�
		{

		}
		break;

	case CMPBY_SIZE:	//����С�Ƚ�
		{

		}
		break;
	}

	return 0;
}

//�ڵ�tmp��ǰ����ڵ�pf
static void FL_insertBefore(PFILE pf, PFILE tmp)
{
	tmp->prev->next = pf;
	pf->prev = tmp->prev;
	pf->next = tmp;
	tmp->prev = pf;
}

//��Ӳ�����������
void FL_add_sortByName(PFILE pf)
{
	PFILE tmp;

	if(!pf) return;

	listData.size++;

	//��һ���ڵ�
	if(listData.size == 1) 
	{
		listData.pEnd->next = pf;
		pf->prev = listData.pEnd;
		listData.pEnd = pf;

		return;	//ֻ��һ���ļ�������
	}

	//�������
	tmp = listData.head.next;
	while(tmp)
	{
		//�ȿ����ļ�����Ĭ��Ŀ¼��ǰ
		if(pf->b_isFile)	//����������ļ�
		{
			//�Թ��ļ���
			if(!tmp->b_isFile) goto NEXT;

			//�����ļ��б�
			if(listData.b_order_ascending)	//��������
			{
				/**
				 * ��������������ڵ� <= ��ǰ�ڵ�
				 * ����λ�ã��ڵ�ǰ�ڵ�ǰ����
				 */
				if(F_cmp(listData.i_order_by, pf, tmp) <= 0)
				{
					FL_insertBefore(pf, tmp);

					//�ҵ��˲���λ�ã���ֱ������ѭ��
					break;
				}
			}else{	//��������
				/**
				 * ������������ǰ�ڵ����һ�ڵ㲻ΪNULL������ڵ� >= ��ǰ�ڵ����һ�ڵ�
				 * ����λ�ã���ǰ�ڵ�����
				 */
				if(tmp->next && F_cmp(listData.i_order_by, pf, tmp->next) >= 0)
				{
					FL_insertBefore(pf, tmp->next);

					//�ҵ��˲���λ�ã���ֱ������ѭ��
					break;
				}
			}
			
		}else{	//����������ļ���
			//tmp �����ļ��е������1.��û���ļ��� 2.�����ļ��������ˣ����ǲ��ڵ�ǰ�ڵ�tmpǰ
			if(tmp->b_isFile)
			{
				FL_insertBefore(pf, tmp);

				//�ҵ��˲���λ�ã���ֱ������ѭ��
				break;
			}

			if(listData.b_order_ascending)	//��������
			{
				if(F_cmp(listData.i_order_by, pf, tmp) <= 0)
				{
					FL_insertBefore(pf, tmp);

					//�ҵ��˲���λ�ã���ֱ������ѭ��
					break;
				}
			}else{
				if(tmp->next && F_cmp(listData.i_order_by, pf, tmp->next) >= 0)
				{
					FL_insertBefore(pf, tmp->next);

					//�ҵ��˲���λ�ã���ֱ������ѭ��
					break;
				}
			}
		}

NEXT:	//������һ��
		/**
		 * ���ƶ������һ���ڵ㻹�ǲ����ϲ������������������һ����
		 * ��������ѭ��tmp����NULL�ˣ��ýڵ�������ڵ� listData.pEnd �󼴿�
		 */
		tmp = tmp->next;
	}

	//��� tmp�������NULL��˵��û���룬��������
	if(tmp == NULL)
	{
		listData.pEnd->next = pf;
		pf->prev = listData.pEnd;
		listData.pEnd = pf;
	}
}

//�б����
void FL_clear(void)
{
	PFILE tmp = listData.head.next;

	while(tmp)
	{
		PFILE del = tmp;
		tmp = tmp->next;
		if(del->name) free(del->name);
		free(del);
	}

	listData.head.next = NULL;
	listData.pEnd = &listData.head;
	listData.size = listData.dc = listData.fc = 0;

	listData.cur_index = 0;
	listData.pCur = NULL;
}

PFILE FL_get(int index)	//��Ŵ�1��ʼ
{
	int i;
	PFILE tmp = &listData.head;

	if(index < 1 || index > listData.size)
		return NULL;

	//pCurδ����ʼ�����ӿ�ͷ��
	if(listData.cur_index == 0 || listData.pCur == NULL)
	{
		for(i=0; i<index; i++)
		{
			if(!tmp->next)
			{
				mrc_printf("NULL nodal at index %d", i+2);
				return NULL;
			}
			tmp = tmp->next;
		}
	}else	//�� pCur λ�ÿ�ʼ��Ѱ
	{
		/*--20111022���-- �ж�Ҫ�ҵ�index����ͷ���
		 *��ͷ����β����ǰ��
		 */
		int d0, d1;

		while(listData.cur_index != index)
		{
			if(listData.cur_index < index)	//ǰ��
			{
				d0 = listData.size - index;	//��β�ڵ�
				d1 = index - listData.cur_index;

				if(d0 < d1){	//��β�ڵ��������β�ڵ���
					listData.cur_index = listData.size;
					listData.pCur = listData.pEnd;
					continue;
				}

				listData.cur_index++;
				listData.pCur = listData.pCur->next;
			}else{	//����
				d0 = index - 1;	//�࿪ͷ
				d1 = listData.cur_index - index;	//�൱ǰ

				if(d0 < d1){	//�࿪ͷ�������ӿ�ͷ��
					listData.cur_index = 1;
					listData.pCur = listData.head.next;
					continue;
				}

				listData.cur_index--;
				listData.pCur = listData.pCur->prev;
			}
		}

		tmp = listData.pCur;
	}
	
	return tmp;
}

char* FL_getName(int index)
{
	return FL_get(index)->name;
}
FILE_Format FL_getFormat(int index)
{
	return FL_get(index)->format;
}
int FL_getFCount(void)
{
	return listData.fc;
}
int FL_getDCount(void)
{
	return listData.dc;
}
boolean FL_isChecked(int index)
{
	return FL_get(index)->b_checked;
}
boolean FL_isFile(int index)
{
	return FL_get(index)->b_isFile;
}
boolean FL_isHiden(int index)
{
	return FL_get(index)->b_isHiden;
}

//�ڲ��������Ƚ������ļ�ʵ��
static boolean F_equal(PFILE src, PFILE dst)
{
	//Ŀǰֻ���ļ����ж�
	return (0 == strcmp(src->name, dst->name));
}

int FL_indexOf(PFILE pf)
{
	int i = 1;
	PFILE tmp = listData.head.next;

	while(tmp)
	{
		if (F_equal(tmp, pf))
		{
			return i;
		}
		i++;
		tmp = tmp->next;
	}
	//����ѭ��˵���ļ�������
	return -1;
}

boolean FL_isEmpty(void)
{
	return (listData.size == 0);
}

void FL_check(int index, boolean checked)
{
	PFILE tmp = FL_get(index);

	if(!tmp)
	{
		mrc_printf("FL_check: NULL nodal");
		return;
	}

	tmp->b_checked = checked;
}

int FL_size(void)
{
	return listData.size;
}

//�ڵ��滻
void FL_set(int index, PFILE pf)
{
	PFILE tmp = FL_get(index);

	if(!tmp || !pf)
	{
		mrc_printf("FL_set: NULL nodal");
		return;
	}

	//���һ���ڵ�
	if(index == listData.size)
	{
		pf->prev = tmp->prev;
		tmp->prev->next = pf;
		F_free(tmp);
	}else{
		tmp->prev->next = pf;
		pf->prev = tmp->prev;
		tmp->next->prev = pf;
		pf->next = tmp->next;
		F_free(tmp);
	}
}

void FL_remove(int index)
{
	PFILE tmp = FL_get(index);

	if(!tmp)
	{
		mrc_printf("FL_remove: NULL nodal");
		return;
	}
	
	//������
	if(tmp->b_isFile) listData.fc--;
	else listData.dc--;
	listData.size--;

	//�ж�pcur
	if(tmp == listData.pCur)
	{
		listData.cur_index = 0;
		listData.pCur = NULL;
	}

	//ɾ�����һ���ڵ����⣬����һ��
	if(index == listData.size)
	{
		tmp->prev->next = NULL;
		F_free(tmp);
	}else{
		tmp->prev->next = tmp->next;
		tmp->next->prev = tmp->prev;
		F_free(tmp);
	}
}