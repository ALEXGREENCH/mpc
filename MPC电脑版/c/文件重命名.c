/*
* �ļ�������
* By:����
* 2012.8.22
*/

#include <base.h>

struct edit
{
 int f;//���
 char *title;//����
 char *text;//����
 uint8 type;//����������
 uint32 max_size;//������볤��
};

struct edit editOld,editNew;

uint8 NowEdit;//���ڱ༭����
// ^ ȡֵ
enum
{
 EDIT_OLD,
 EDIT_NEW
};

int init()
{
 ShowMsg("���� ����");
 sleep(1000);

 NowEdit=EDIT_OLD;
 SetEdit(&editOld,"������:���ļ���","",0,100);
 SetEdit(&editNew,"������:���ļ���","",0,100);
 ShowEdit(&editOld);

 return 0;
}

int event(int type, int p1, int p2)
{
 if(MR_DIALOG==type)
 {
 switch(p1)
  {
  case DLG_OK:
  if(NowEdit==EDIT_OLD)
  {
  NowEdit=EDIT_NEW;
  editOld.text=editget(editOld.f);
  editdel(editOld.f);
  ShowEdit(&editNew);
  }
  else
  {
 editNew.text=editget(editNew.f);
  reName(editOld.text,editNew.text);
  editdel(editOld.f);
  editdel(editNew.f);
  exitapp();
  }
  break;

  case DLG_CANCEL:
  if(NowEdit==EDIT_OLD)
  {
  editdel(editOld.f);
  editdel(editNew.f);
  exitapp();
  }
  else
  {
  NowEdit=EDIT_OLD;
  editNew.text=editget(editNew.f);
  editdel(editNew.f);
  ShowEdit(&editOld);
  }
  break;
  }
 }

 return 0;
}

int pause(void)
{
 return 0;
}

int resume(void)
{
 return 0;
}

/*
gb��cnicode���뻥ת
  is_uniȡֵ:
  >0 ����unicode��ָ��
  <=0 gb2312
���� ָ�򷵻��ַ�����ָ��
*/
void* gb_uni(char* str,int is_uni)
{
 int err,a,b;
 a=wstrlen(str);
 if(is_uni)
 {
 u2c(str,a,&str,&a);
 return str;
 }
 return c2u(str,&err,&b);
}

void StrCopy(void *str,void *str2)
{
 uint32 len=strlen(str2);
 if(str2!=NULL)
 free(str2);
 str=malloc(len);
 memset(str,NULL,len);
 memcpy(str,str2,len);
}

void reName(void *OldName,void *NewName)
{
 rename(gb_uni(OldName,0),gb_uni(NewName,0));
}

//���ñ༭�����
void SetEdit(struct edit *editOne,char *title,char *text,uint8 type,uint32 max_size)
{
 editOne->title=gb_uni(title,0);
 editOne->text=gb_uni(text,0);
 editOne->type=type;
 editOne->max_size=max_size;
}

//������ʾ�༭��
void ShowEdit(struct edit *editOne)
{
 editOne->f=editcreate(editOne->title,editOne->text,editOne->type,editOne->max_size);
}

//�˳�
void exitapp()
{
 ShowMsg("���� ����");
 sleep(1000);
 exit();
}

//����ʾ��Ϣ
void ShowMsg(void *Msg)
{
 int w,h;
 uint16 x,y;
 textwh(Msg,FALSE,1,&w,&h);
 if(w<SCRW)
 x=(SCRW-w)>>1;
 y=(SCRH-h)>>1;
 effsetcon(x-5,y-5,w+10,h+10,100,100,100);
 dtext(Msg,x,y,250,250,250,FALSE,1);
 ref(x-5,y-5,w+10,h+10);
}

//By:����
