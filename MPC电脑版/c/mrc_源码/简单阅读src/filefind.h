/*
��������(6369)

*/
#ifndef _FILEFIND_H
#define _FILEFIND_H



#define PATHLEN 1000//�·��
#define NAMELEN 74//�ļ����
#define MAX 300//����ļ���
#define BMP "icon.bmp"


void loadFileFind (void);



//Ѱ��ָ��Ŀ¼
void FileFind(char *path);



//�ͷ��ڴ�
void FileFindDel (void);


//�����������
void clearbuf(void);



void DrawMain (void);


//�����б�
void DrawList(void);



//�������
void dorect(int x,int y,int w,int h,int r,int g,int b);
   



//����ͼƬ������free�ͷţ����������ַ
void *LoadBmp(char *FileName);


//�����ϼ�Ŀ¼

int back(void);

//������
int donext(void);



//�¼�����
int fileFindEvent(int msg,int p1,int p2);



//���������¼��ص�
void _time(int a);


//��ʼ����������һ����ʹ������֮ǰ����
int fileFindInit(void);



//�˳�����
int fileFindExit(void);

#endif
