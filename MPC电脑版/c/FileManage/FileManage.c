/*
* FileManage(�ļ�������)
* By:����
* QQ:643552878
* Date:2012..
* PS:ȫ���������д�����쾫��֮����֮ǰFileViewҲŪ��3��4�Ρ����˺ܾõġ��ֻ�Ҳ��֪�����˶��ٴ���������֧�֣�* *����ͼ(ȫ��)
*/

#include <base.h>

//����
#define FONT 1

//���ֿ��
int tw,th;
textwh("��",FALSE,FONT,&tw,&th);

#include <c/FileManage/FileView.h>

#include <c/FileManage/PhotoView.h>

#include <c/FileManage/BookView.h>

#include <c/FileManage/MusicPlay.h>

#include <c/FileManage/tt/ttFileAdd.h>

#include <c/FileManage/tt/tt.h>


uint8 Jm;//�������

//Jmȡֵ
enum
{
 Jm_FV,//�ļ����(FileView)
 Jm_PV,//ͼƬ���(PhotoView)
 Jm_BV,//�ı����(BookView)
 Jm_MP//���ֲ���(MusicPlay)
};

res *lang;
uint16 *Bmp;

//��ں���
int init(void)
{
 //lang=langload("c/FileManage/tt/res_lang0.rc",28);
 ShowMsg("��ʼ��...",0);
 Bmp=FileOpen("c/FileManage/tt/fileicon.bmp");
 Jm=Jm_FV;
 ListInit();
 return 0;
}

//������ں���
int event(int type, int p1, int p2)
{
 if(type==KY_UP&&p1==_STAR)
 {
 char *text;
 text=PrintScr("c/FileManage��ͼ.bmp")?"��ͼ�ɹ���":"��ͼʧ�ܣ�";
 ShowMsg(text,0);
 }

 switch(Jm)
 {
 case Jm_FV:
 FVEvent(type,p1,p2);
 break;
/* case Jm_PV:
 PVEvent(type,p1,p2);
 break;
 case Jm_BV:
 BVEvent(type,p1,p2);
 break;
 case Jm_MP:
 MPEvent(type,p1,p2);
 break;
*/ }

 return 0;
}

//ƽ̨��ͣ��ں���
int pause(void)
{
 return 0;
}

//ƽ̨�ָ���ں���
int resume(void)
{
 return 0;
}

//�����˳�
void ExitApp()
{
 ShowMsg("��������",0);
 //free(lang);
 free(Bmp);
 ExitList();
 sleep(500);
 exit();
}

//By:����