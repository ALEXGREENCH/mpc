#ifndef __APPMAIN_H__
#define __APPMAIN_H__

enum
{
	APPWINDOWS_VIEW, // ������
	APPWINDOWS_DELREAME, // ɾ��С����
	APPWINDOWS_EXITREAME // �˳�С����
};
// ȡ������
void Noback(void);
// �����б����
void FileViewBrowser_UI(void);
void RefreshList(void);
// �ļ��������ʼ��
void FileViewBrowser_Main(void);
// �ļ��������������
void FileViewBrowser_Event(int32 code, int32 p, int32 q);

#endif // __APPMAIN_H__