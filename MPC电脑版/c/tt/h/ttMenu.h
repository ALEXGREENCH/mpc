
/*
* tt�˵���װ
* ttMenu.h
* By:����
* QQ:643552878
*/


/*�˵����*/
typedef struct menupoint
{
 struct menupoint *prev;//ǰһ��
 struct menupoint *next;//��һ��
 char *text;//�˵�����
 uint32 id;//�˵�id
}
MenuPoint;
typedef (*MenuPoint) PMenu;

uint32 PMenuLen=sizeof(MenuPoint);


/*�˵��б�ṹ��*/typedef struct menulist
{
 uint16 x; uint16 y;
 //�˵���ʼxyλ��
 uint16 bgclr;//����ɫ
 uint16 chclr;//ǰ��ɫ

 PMenu first;//��ͷ
 PMenu last;//��β
 PMenu now;//��������

 uint32 Num;//�˵�����
 uint32 id;//����id
}
MenuList;
typedef (*MenuList) LMenu;
