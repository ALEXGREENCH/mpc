#ifndef _TYPE_H
#define _TYPE_H 

/*��������(6369)
2012-7-11

*/

#include "mrc_base.h"


#define SCRW 240
#define SCRH 320

#define FOCUSBK 0xff0000//�õ�����Ŀؼ��߿���ɫ
#define FOCUSBKW 2//�õ�����ؼ��ı߿���

#define MAKERGB(r,g,b)(r<<16)+(g<<8)+(b)
#define MAKER(a)(a>>16&0xff)

#define MAKEG(a)(a>>8&0xff)

#define MAKEB(a)(a&0xff)


extern int32 FONT;//��Ҫʱ��ע��

/*��888��ʽ����ɫa�ֽ�Ϊr,g,b
a��888��ʽ����ɫ
r��g��b  ����r��g��b�ı����ĵ�ַ(ָ��)
*/
void make(int32 a,int* r,int* g,int* b);


/*gb2312��unicode������໥ת��
str ��ת�����ַ���
is_uni �Ƿ������Ϊunicode����
  1 ����unicode��ָ��
  0 gb2312
���� ָ�򷵻��ַ�����ָ��
*/
void* gb_uni(char* str,int is_unicode);

void shaderect(int x,int y,int w,int h,int32 upclr,int32 downclr,int is_made);


#endif