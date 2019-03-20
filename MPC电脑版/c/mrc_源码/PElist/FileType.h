#ifndef __FILETYPE_H__
#define __FILETYPE_H__

enum
{
	// �ļ���
	FILE_DIR,
	// �ı�
	FILE_TXT,FILE_WML,
	FILE_LRC,
	FILE_C,FILE_H,
	// Ӧ�ó���
	FILE_MRP,
	// ͼƬ
	FILE_JPG,FILE_GIF,
	FILE_BMP,FILE_PNG,
	// ѹ��
	FILE_ZIP,FILE_RAR,
	FILE_GZ,FILE_7Z,
	// ����
	FILE_MP3,FILE_AMR,
	FILE_WAV,FILE_AWB,
	FILE_MID,
	// Ӱ��
	FILE_MP4,FILE_F4V,
	FILE_RMVB,FILE_3GP,
	// ����
	FILE_OTHER
};

// �ļ�ͼ��
void MDtub(int32 dtd,int16 x,int16 y);
// �����ļ�����
int typeanalyse(char *name);
// �����ļ�����,��������
char *typeanalysetxt(int num);

#endif // __FILETYPE_H__