/*��������(6369) 
*/

#ifndef READ_H
#define READ_H


#define SEKFILE "read.sek"//��¼�ļ�


extern int32 size,  sek, nsek;//�ļ����ȣ��ļ��������ǰָ�룬��ҳ��ָ��

extern int16 xs;//������

extern char* fbuf;//�Ű滺��

extern mr_screenRectSt rect;//��ʾ����
extern mr_colourSt bclr, qclr;//������ǰ��

extern int32 btupclr,btdownclr;//��������ɫ
extern int pin,fu;//ȫ�����أ�Ƥ������
extern int siz;//��ʾ��������ıߵľ��룬���������
extern int32 zw,zh;

int readInit(char* name);


int readExit(void);//�˳��Ķ�


int readEvent(int msg,int p1,int p2);//�Ķ������¼�����


int downPaiBan(void);



int upPaiBan(void);//�Ϸ�ҳ


void huanFu(void);//�л�Ƥ��




void huanPin(void);//�л�ȫ��


void func(void);


#endif