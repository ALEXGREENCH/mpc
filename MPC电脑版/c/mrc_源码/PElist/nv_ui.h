#ifndef __NV_UI_H__
#define __NV_UI_H__

#define mspw MSpw()
#define msph MSph()

typedef struct COLORCT
{
	uint8 r;
	uint8 g;
	uint8 b;
}colorct;

// ��ʼ��
void nv_ui_init(void);
// ж��
void font_exit(void);

// ����
void cls(int32 r,int32 g,int32 b);
// �������
void clsr(int32 w,int32 h);

// ��ʾ��д
void fms(int16 x,int16 y,int16 w,int16 h);
// С��ʾ
void fresh(void);
// ȫ����ʾ
void fresht(void);
// ��Ļ��
int16 MSpw(void);
// ��Ļ��
int16 MSph(void);

// ������
int32 txtwh(char *text,int32 *tw,int32 *th);

// ������ɫ�ṹ��ͼ
void txtJG(char* szText,int16 x,int16 y,colorct bs);
void rectJG(int16 x,int16 y,int16 w,int16 h,colorct bs);
void yrectJG(int16 x,int16 y,int16 w,int16 h,colorct bs);
void ysrectJG(int16 x,int16 y,int16 w,int16 h,colorct bs,colorct bs2);

// ������ɫRGB��ͼ

// д����12��
void txt(char* szText,int16 x,int16 y,uint8 r,uint8 g,uint8 b);
// дunicode12��
void txt2(char* szText,int16 x,int16 y,uint8 r,uint8 g,uint8 b);

// ͸��������϶���
void drect(int16 x,int16 y,int16 w,int16 h,uint8 r1,uint8 g1,uint8 b1,uint8 r2,uint8 g2,uint8 b2);
// ͸�����������
void drect2(int16 x,int16 y,int16 w,int16 h,uint8 r1,uint8 g1,uint8 b1,uint8 r2,uint8 g2,uint8 b2);
// ���䰴ť
void ysrect(int16 x,int16 y,int16 w,int16 h,uint8 r1,uint8 g1,uint8 b1,uint8 r2,uint8 g2,uint8 b2);
// ������δ�����
void wsrect(int16 x,int16 y,int16 w,int16 h,uint8 r1,uint8 g1,uint8 b1,uint8 r2,uint8 g2,uint8 b2);
// ������δ��϶���
void srect(int16 x,int16 y,int16 w,int16 h,uint8 r1,uint8 g1,uint8 b1,uint8 r2,uint8 g2,uint8 b2);
// x����
void urect(int16 x,int16 y,int16 tx,int16 ty,uint8 r,uint8 g,uint8 b,int16 hu);
// 1��Բ�Ǿ���
void yrect(int16 x,int16 y,int16 w,int16 h,uint8 r,uint8 g,uint8 b);
// 1��Բ�Ǿ��ο��
void nrect(int16 x,int16 y,int16 w,int16 h,uint8 r,uint8 g,uint8 b,int16 hu);
// 1��͸��Բ�Ǿ��ο��
void ntrect(int16 x,int16 y,int16 w,int16 h,uint8 r,uint8 g,uint8 b,int16 hu);
// ֱ�Ǿ��ο�
void mrect(int16 x,int16 y,int16 w,int16 h,uint8 r,uint8 g,uint8 b,int16 hu);
// 4��Բ�Ǿ���
void vrect(int16 x,int16 y,int16 w,int16 h,uint8 r,uint8 g,uint8 b,int t);
// ����4��͸��Բ�Ǿ�����Ӱ
void svrect(int16 x,int16 y,int16 w,int16 h,uint8 r1,uint8 g1,uint8 b1,uint8 r2,uint8 g2,uint8 b2,int t);
// ������
void san(int16 x,int16 y,int16 w,uint8 r,uint8 g,uint8 b,int16 hu);
// 1��͸��Բ�Ǿ���
void trect(int16 x,int16 y,int16 w,int16 h,uint8 r,uint8 g,uint8 b);

#endif  // __NV_UI_H__