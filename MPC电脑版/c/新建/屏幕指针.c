//����������ͼƬ�����������ֱ���ֱ�ӻ�ͼ������Ļָ����Ƚϣ�
#include <base.h>
#define REF ref(0,0,SCRW,SCRH)

#define photo "tu.jpg"
//����ͼƬ·�����Լ��ġ�
#define photo2 "�羰.jpg"


uint16 *scf=getscrbuf();
//�����Ļ�����ַ
uint16 *tu=malloc(SCRW*SCRH*2);
//������ͼƬָ���ڴ�

int init()
{
 img(photo,0,0);
 //��ͼƬ
 effsetcon(10,10,SCRW-20,SCRH-20,138,200,138);
 //�Աȶ�
 memcpy(tu,scf,SCRW*SCRH*2);
 //����Ļָ�븴��һ��bmpͼƬ

 cls(0,0,0);
 dtext("�����Ҽ��л�����",20,SCRH/2,255,255,0,0,1);
 REF;
return 0;
}

int event(int type, int p1, int p2)
{
if(KY_DOWN == type)
 {
 switch(p1)
 {
   case _SRIGHT:
  free(tu);
 //�ͷ��ڴ�
  exit();break;

  case _LEFT:
  zzref();break;

 case _RIGHT:
 zjref();break;
}


}
return 0;
}

int pause()
{return 0;}
int resume()
{return 0;}


//ֱ�ӻ�ͼ
void zjref()
{
 int px;
 for(px=0;px<=SCRW;px+=20)
 {
  img(photo2,px-SCRW,0);
  effsetcon(px-SCRW+10,10,SCRW-20,SCRH-20,138,200,138);
  dtext("���ˡ��ٶ�",px-SCRW/4*3,100,255,255,255,0,1);
  REF;
 }

}

//ֱ�ӻ�
void zzref()
{
 int px;
 for(px=0;px<=SCRW;px+=20)
 {
  bmpshowflip(tu,SCRW-px,0,SCRW,SCRW,SCRH,BM_COPY,0,0,0);
dtext("����ɶ�ٶȣ���",SCRW-px+SCRW/4,100,255,255,255,0,1);
  REF;
 }

}

/*by:ÿ�����һ��
����������Ļָ���ٶȿ�ɣ���
*/