#ifndef __NV_BASE_H__
#define __NV_BASE_H__

// ���غ�̨
void MINApp(void);
// �л�Ŀ¼
void SwitchDisk(const char* strDisk);
// ָ��ƫ��
char* strplen(char *text,int32 poss,int32 str_len);
// ��ȡָ�����������ļ�
void* ReadAllex(const char* strDisk,const char* returnstrDisk,const char* filename);
// �ַ�����,���������ַ�
char *strfind(char *text,char *s,char *t);
// �ַ�����,�����������ַ�
char *strfindEx(char *text,char *s,char *ts);

#endif // __NV_BASE_H__
