
//��������(6369)
//create date 2012-7-17

#include "mrc_base.h"
#include "type.h"
#include "toolbar.h"





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

PTool toolBarCreate(int x,int y,int w,int h,int32 upclr,int32 downclr,int32 titclr,char* left,char* zhon,char* right)
{
PTool a;
a=mrc_malloc(sizeof(Tool));
if(a==NULL) return 0;
a->x=x;
a->y=y;
a->w=w;
a->h=h;
a->upclr=upclr;
a->downclr=downclr;
a->titclr=titclr;
a->left=left;
a->zhon=zhon;
a->right=right;
return a;
}

/*ɾ��������*/

void toolBarDel(PTool a)
{
mrc_free(a);
a=0;
}


/*���Ʊ�����*/

void drawToolBar(PTool a)
{
int32 zw,zh;
int r,g,b;
mrc_textWidthHeight(a->zhon,0,FONT,&zw,&zh);
shaderect(a->x,a->y,a->w,a->h,a->upclr,a->downclr,0);
make(a->titclr,&r,&g,&b);
mrc_drawText(a->left,a->x+2,a->y+(a->h-zh)/2,r,g,b,0,FONT);
mrc_drawText(a->zhon,a->x+(a->w-zw)/2,a->y+(a->h-zh)/2,r,g,b,0,FONT);
mrc_textWidthHeight(a->right,0,FONT,&zw,&zh);
mrc_drawText(a->right,a->x+a->w-zw-2,a->y+(a->h-zh)/2,r,g,b,0,FONT);

}
