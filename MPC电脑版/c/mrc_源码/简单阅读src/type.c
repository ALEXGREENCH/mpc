//��������(6369)
//create date 2012-7-13


#include "mrc_exb.h"
#include "type.h"

/*��888��ʽ����ɫa�ֽ�Ϊr,g,b
a��888��ʽ����ɫ
r��g��b  ����r��g��b�ı����ĵ�ַ(ָ��)
*/
void make(int32 a,int* r,int* g,int* b)
{
*r=MAKER(a);
*g=MAKEG(a);
*b=MAKEB(a);
}

/*gb2312��unicode������໥ת��
str ��ת�����ַ���
is_uni �Ƿ������Ϊunicode����
  1 ����unicode��ָ��
  0 gb2312
���� ָ�򷵻��ַ�����ָ��
*/
void* gb_uni(char* str,int is_unicode)
{
int32 err,b;
//uint8 ch =(uint8) str;
if(is_unicode)
{
	//mrc_unicodeToGb2312((uint8*)str,mrc_strlen(str),&ch,&b);
	return NULL;
}
else
	return (void*)mrc_c2uVM(str,&err,&b);
}



void shaderect(int x,int y,int w,int h,int32 upclr,int32 downclr,int is_made)
{
	int r,g,b;
	int r1,g1,b1,r2,g2,b2;
	int i;
	make(upclr,&r1,&g1,&b1);
	make(downclr,&r2,&g2,&b2);
	switch(is_made)
	{

	case 0:
		r=r1;
		g=g1;
		b=b1;
		for(i=y;i<y+h;i++)
		{
			mrc_drawLine(x,i,x+w-1,i,r,g,b);
			r=r-(r1-r2)/h;
			g=g-(g1-g2)/h;
			b=b-(b1-b2)/h;
		}
		break;
	}

}