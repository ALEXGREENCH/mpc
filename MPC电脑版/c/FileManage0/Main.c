#include <base.h>

#include <c/FileManage0/Event.h>

#include <c/FileManage0/Draw.h>

#include <c/FileManage0/FindFile.h>


#include <c/FileManage0/Music.h>

#define FileBmpName "c/FileManage0/bmp/file.bmp"

#define DirBmpName "c/FileManage0/bmp/folder.bmp"

int init()
{
 DrawMsg("��ʼ����...");
 BmpStart();
 FindFile();
 DrawList();
 return NULL;
}

//BY:ÿ�����һ��