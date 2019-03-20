/***************************************************************************************************************
***************************************************************************************************************
*Version:V2.0.0616
*New Features:Support Memory or TCard load, config this by Function FontmoduleInit's  parameter: BOOL isMemLoad. If game's memory 
			 is enough,you can set isMemLoad as TRUE to accelerate the speed of drawing.
*Others:Support Unicode string only; 
*           Font with unequal width; 
*           OutPut file as sky_X_XXX.bin.
***************************************************************************************************************
***************************************************************************************************************/

#ifndef _DRAWTEXT_H
#define _DRAWTEXT_H

#ifndef BOOL_T
#define BOOL_T
typedef int	BOOL;
#endif

typedef enum charset_e
{
	MR_SET_GB,				//BG�ַ���
	MR_SET_UNICODE		//UNICODE�ַ���
}E_CHR_SET;
/*
��	  �ܣ����Ƶ����ı�����Ӧ��SKY SDK mrc_drawText�ӿ�
����˵����
	      	  char*chr					��IN �ݶ����������ı�����
		  int16 x					��IN �ݶ����������ı�����ʼx���꣨�������Ļ����ԭ��(0,0)��
		  int16 y					��IN �ݶ����������ı�����ʼy���꣨�������Ļ����ԭ��(0,0)��
		  mr_colourSt  colorst      		��IN �ݶ����������ı����ɫֵ�����mr_colourSt����
		  E_CHRSET flag			��IN �ݶ�Ӧ��E_CHRSETö���壬ȡֵΪSET_GB,MR_SET_UNICODE�������������ı����ַ�������
		  uint16 font				��IN �ݶ�Ӧ�� SKY SDK MR_FONT_TYPEö���壬ȡֵΪMR_FONT_BIG, MR_FONT_MEDIUM, MR_FONT_SMALL
����ֵ:
		MR_SUCCESS  ���Ƴɹ�
		MR_FAILED   ����ʧ��
*/
int32 _drawText(char* chr, int16 x, int16 y,  mr_colourSt colorst,E_CHR_SET flag,  uint16 font);
/*
��	  �ܣ����Ƶ����ַ�
����˵����
	      	  char*chr					��IN �ݶ����������ı�����
		  int16 x					��IN �ݶ����������ı�����ʼx���꣨�������Ļ����ԭ��(0,0)��
		  int16 y					��IN �ݶ����������ı�����ʼy���꣨�������Ļ����ԭ��(0,0)��
		  mr_colourSt  colorst      		��IN �ݶ����������ı����ɫֵ�����mr_colourSt����
		  E_CHRSET flag			��IN �ݶ�Ӧ��E_CHRSETö���壬ȡֵΪSET_GB,MR_SET_UNICODE�������������ı����ַ�������
		  uint16 font				��IN �ݶ�Ӧ�� SKY SDK MR_FONT_TYPEö���壬ȡֵΪMR_FONT_BIG, MR_FONT_MEDIUM, MR_FONT_SMALL
����ֵ:
		MR_SUCCESS  ���Ƴɹ�
		MR_FAILED   ����ʧ��
*/
int32 _drawChar(char* chr, int16 x, int16 y, mr_colourSt colorst,E_CHR_SET flag,  uint16 font);

/*
��	  �ܣ�����ָ�����ı�����������ʾ������ָ���ľ����������Զ�����
		      ����ʱ������������ʾ
����˵����
	      	  char*chr					��IN �ݶ����������ı�����
		  int16 x					��IN �ݶ����������ı�����ʼx���꣬�����rect�����϶��㣬�м�
		  int16 y					��IN �ݶ����������ı�����ʼy���꣨�������Ļ����ԭ��(0,0)��
		  mr_screenRectSt  rect              ��IN �ݶ����������ı�����ʾ�������mr_screenRectSt����
		  mr_colourSt  colorst      		��IN �ݶ����������ı����ɫֵ�����mr_colourSt����
		  E_CHRSET flag			��IN �ݶ�Ӧ��E_CHRSETö���壬ȡֵΪSET_GB,MR_SET_UNICODE�������������ı����ַ�������
		  uint16 font				��IN �ݶ�Ӧ�� SKY SDK MR_FONT_TYPEö���壬ȡֵΪMR_FONT_BIG, MR_FONT_MEDIUM, MR_FONT_SMALL
����ֵ:
		MR_SUCCESS  ���Ƴɹ�
		MR_FAILED   ����ʧ��
*/
int32 _drawTextFromRight(char* pcText, int16 x, int16 y, mr_screenRectSt rect, mr_colourSt colorst, E_CHR_SET flag, uint16 font);

/*
��	  �ܣ�����ָ�����ı�����������ʾ������ָ���ľ����������Զ�����
����˵����
	      	  char*chr					��IN �ݶ����������ı�����
		  int16 x					��IN �ݶ����������ı�����ʼx���꣨�������Ļ����ԭ��(0,0)��
		  int16 y					��IN �ݶ����������ı�����ʼy���꣨�������Ļ����ԭ��(0,0)��
		  mr_screenRectSt  rect              ��IN �ݶ����������ı�����ʾ�������mr_screenRectSt����
		  mr_colourSt  colorst      		��IN �ݶ����������ı����ɫֵ�����mr_colourSt����
		  E_CHRSET flag			��IN �ݶ�Ӧ��E_CHRSETö���壬ȡֵΪSET_GB,MR_SET_UNICODE�������������ı����ַ�������
		  uint16 font				��IN �ݶ�Ӧ�� SKY SDK MR_FONT_TYPEö���壬ȡֵΪMR_FONT_BIG, MR_FONT_MEDIUM, MR_FONT_SMALL
����ֵ:
		MR_SUCCESS  ���Ƴɹ�
		MR_FAILED   ����ʧ��
*/
int32 _drawTextLeft(char* pcText, int16 x, int16 y, mr_screenRectSt rect, mr_colourSt colorst, E_CHR_SET flag, uint16 font);


/*
��	  �ܣ�����ָ�����ı�����������ʾ������ָ���ľ����������Զ����У�֧�ִӾֲ���lineStart��ʼ���ơ�
����˵����
	      	  char*chr					��IN �ݶ����������ı�����
		  int16 x					��IN �ݶ����������ı�����ʼx���꣨�������Ļ����ԭ��(0,0)��
		  int16 y					��IN �ݶ����������ı�����ʼy���꣨�������Ļ����ԭ��(0,0)��
		  mr_screenRectSt  rect              ��IN �ݶ����������ı�����ʾ�������mr_screenRectSt����
		  mr_colourSt  colorst      		��IN �ݶ����������ı����ɫֵ�����mr_colourSt����
		  E_CHRSET flag			��IN �ݶ�Ӧ��E_CHRSETö���壬ȡֵΪSET_GB,MR_SET_UNICODE�������������ı����ַ�������
		  uint16 font				��IN �ݶ�Ӧ�� SKY SDK MR_FONT_TYPEö���壬ȡֵΪMR_FONT_BIG, MR_FONT_MEDIUM, MR_FONT_SMALL
		  int32  lineStart	 [IN]  ���ƶ��д�ʱ������ʾ����������
����ֵ:
		MR_SUCCESS  ���Ƴɹ�
		MR_FAILED   ����ʧ��
��ע������������ͨ��_textWidthHeightLine�ӿ��Բ���linewidthΪ׼����õ��ģ�����ȷ��Rect����ʱ��������һ�¡�
*/
int32 _drawTextLeftByLineN(char* pcText, int16 x, int16 y, mr_screenRectSt rect, mr_colourSt colorst, E_CHR_SET flag, uint16 font, int32 lineStart);
/*
��	  �ܣ���ȡ�ַ�����ָ�������еĿ���ֵ
����˵����
	      	  char*pcText				��IN �ݶ����ı�����
		  int32 width				��OUT���ַ����Ŀ�ȣ����м�
		  int32 height				��OUT ���ַ����ĸ߶�
		  mr_screenRectSt  rect              ��IN �� �����������ı�����ʾ�������mr_screenRectSt����
		  mr_colourSt  colorst      		��IN �ݶ����������ı����ɫֵ�����mr_colourSt����
		  E_CHRSET flag			��IN �ݶ�Ӧ��E_CHRSETö���壬ȡֵΪSET_GB,MR_SET_UNICODE�������������ı����ַ�������
		  uint16 font				��IN �ݶ�Ӧ�� SKY SDK MR_FONT_TYPEö���壬ȡֵΪMR_FONT_BIG, MR_FONT_MEDIUM, MR_FONT_SMALL
����ֵ:
		MR_SUCCESS  ���Ƴɹ�
		MR_FAILED   ����ʧ��
*/
int32 _textWidthHeight(char *pcText,int32 *width,int32 *height,E_CHR_SET flag, uint16 font);
/*
��	  �ܣ���ȡ�ַ�����ָ�������еĿ���ֵ
����˵����
	      	  char*pcText				��IN �ݶ����ı�����
		  int32 width				��OUT���ַ����Ŀ�ȣ����м�
		  int32 height				��OUT ���ַ����ĸ߶�
		  int32 lines					 [OUT] �ַ�������lineWidthΪ��ʱ����Ҫ�����С�
		  mr_screenRectSt  rect              ��IN �� �����������ı�����ʾ�������mr_screenRectSt����
		  mr_colourSt  colorst      		��IN �ݶ����������ı����ɫֵ�����mr_colourSt����
		  E_CHRSET flag			��IN �ݶ�Ӧ��E_CHRSETö���壬ȡֵΪSET_GB,MR_SET_UNICODE�������������ı����ַ�������
		  uint16 font				��IN �ݶ�Ӧ�� SKY SDK MR_FONT_TYPEö���壬ȡֵΪMR_FONT_BIG, MR_FONT_MEDIUM, MR_FONT_SMALL
		  int32  linewidth   [IN]	 һ�еĿ��
����ֵ:
		MR_SUCCESS  ���Ƴɹ�
		MR_FAILED   ����ʧ��
*/
int32 _textWidthHeightLine(char *pcText,int32 *width,int32 *height,int32 *lines,E_CHR_SET flag, uint16 font, int32 linewidth);
/*
��	  �ܣ���Ϸ�Դ�����ģ���ʼ��������mrc_init�е��á�
����˵����
	      	  BOOL isBigFontSupport					��IN ���Դ��ֿ��Ƿ����BIG�ֿ� ����Ӧ��PC����MR_FONT_BIGѡ ��
		  BOOL isMediumFontSupport				��IN�� �Դ��ֿ��Ƿ����MEDIUM�ֿ�  ����Ӧ��PC����MR_FONT_MEDIUMѡ ��
		  BOOL isSmallFontSupport				��IN ���Դ��ֿ��Ƿ����SMALL�ֿ�  ����Ӧ��PC����MR_FONT_SMALLѡ ��
		  BOOL isMemLoad						 [   IN ]     �ֿ�����Ƿ�Load���ڴ��У�TRUE�ڴ����,FALSE T������ V1.0.9�汾����
����ֵ:
		MR_SUCCESS  ��ʼ���ɹ�
		MR_FAILED   ��ʼ��ʧ��
*/
int32 FontModuleInit(BOOL isUnicodeIndexSupport,BOOL isGBIndexSupport, BOOL isMemLoad);
/*
��	  �ܣ���Ϸ�Դ�����ģ����Դ�ͷţ��������mrc_exitApp�е��á�
����˵����
	         ��
����ֵ:
		��
*/
void FontModuleRelease(void);
#endif
