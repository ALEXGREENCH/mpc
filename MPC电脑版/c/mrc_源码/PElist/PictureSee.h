#ifndef _PictureSee_LIB_H_
#define _PictureSee_LIB_H_

#define PictureSee_EXT_ID               20120515
#define PictureSee_FUNCTION_DrawImg	    0x10				 //����еĺ���ID�������߿������ж��弰��չ
//#define PictureSee_FUNCTION_...	    0x12				 //����еĺ���ID�������߿������ж��弰��չ

#define PictureSee_MRPNAME              "picturesee_mtk.mrp" //���PictureSee���EXT����ε�MRP���ƣ����ڱ��汾Ҫ���Զ��幦�ܲ����Ϊ����MRP���� �����������ΪNULL
#define PictureSee_MRPFOLD              "MDs"     			 //���PictureSee���EXT����ε�MRP·�������ڱ��汾Ҫ���Զ��幦�ܲ����Ϊ����MRP���� �����������ΪNULL
#define PictureSee_EXTNAME              "picturesee.ext"	 //���EXT����ε�����

/*ע�⣺
1������ģ�幤�̴����Ĳ��ʾ��������ʾMRP���ò�����磺verdload���ز��
2����νMRP���ò�������������mrp��lib����������յ����MPR�У���:
	[config_mtk240]
	define=...
	output=...
	c_compiler=thumb
	bmp_mode=normal
	plat=mtk
	loader=c

	[config_game_mtk240x320]
	plugin=app

	[files_mtk240x320]
	#��Ϸ/Ӧ�õ����߼������
	file2=game_mtk240x320.ext(name=game.ext)
	#���ò��
	file3=${MRPBUILDER_HOME}\PictureSees\mainext\mainext_mtk_d.mrp
	#���ò��
	file4=${MRPBUILDER_HOME}\PictureSees\verdload\verdload_mtk.mrp	
	file1=..\res\GJYWLZ_RES_MTK_240X320.mrp

	[files_game_mtk240x320]
	file11=..\lib\GJYWLZ_MTK_240X320_24_T5N.lib
	#���ڴ���
	file12=${MRPBUILDER_HOME}\PictureSees\netpay\netpay_mtkt.lib
	#���ò��
	file13=${MRPBUILDER_HOME}\PictureSees\verdload\verdload_mtkt.lib
	#���ڴ���
	file15=${MRPBUILDER_HOME}\PictureSees\platreq\mr_platreq_mtkt.lib
*/

/*
���ܣ�
	����Ĵ���ص���һ����PictureSee�߼���ɺ��������Ľ��֪ͨ
����˵����
	int32 p0��p1��p2��p3��p4��p5  �ص��βΣ�Ӧ�ÿ����߿��Ը�����Ҫ�������
	��ģ��ʾ���У�
	p0   �����E_PictureSee_CBRESULTö��ȡֵ
	p1��p2��p3��p4��p5			��Ч
����ֵ��
	��
*/

typedef enum
{
	PictureSee_RESULT_EXT_LOADSUCC,				//�����̬���سɹ�
	PictureSee_RESULT_EXT_LOADFAILED,			//�����̬����ʧ��
	PictureSee_RESULT_EXT_MRSUCCESS,				//�������ִ�гɹ�
	PictureSee_RESULT_EXT_MRFAILED				//�������ִ��ʧ��
}E_PictureSee_CBRESULT;

typedef void (*PictureSee_Func_CB)(int32 p0, int32 p1, int32 p2, int32 p3, int32 p4, int32 p5);


/*
���ܣ�
	��ʾ������ʾ�����MRP�ж�ȡ��ԴͼƬ"Hello" ����ʾ
����˵����
	char* bmpFileName     �����򴫵ݹ����Ĵ�����MRP�ж�ȡ����ԴͼƬ����
	Func_CB cb		    PictureSee�����ɹ��ܺ�֪ͨ�ص�
����ֵ��
	��
*/
void PictureSee_Func_DrawImg(PictureSee_Func_CB cb);

#endif
