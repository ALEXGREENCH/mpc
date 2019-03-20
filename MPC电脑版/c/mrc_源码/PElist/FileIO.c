/*
 * ת����·���ָ������ļ���������
 * ��Ȩ���� (C) 2011-2012 eleqian
 * [5/18/2012]
 */

#include <mrc_base.h>

#include "FileIO.h"

// ת��·���ָ���
char* ConvertPathSeparator(const char *path)
{
    static char dstPath[MAX_PATH_LEN_A]; //ת���ָ������·��
    char *psrc, *pdst;

    for (psrc = (char*)path, pdst = dstPath; '\0' != *psrc; psrc++, pdst++)
    {
        *pdst = ('\\' == *psrc) ? '/' : *psrc;
    }

    *pdst = '\0';

    return dstPath;
}

// ͬ�ϣ�Ϊ��ʵ��ͬʱת������·��
char* ConvertPathSeparator1(const char *path)
{
    static char dstPath1[MAX_PATH_LEN_A]; //ת���ָ������·��
    char *psrc, *pdst;

    for (psrc = (char*)path, pdst = dstPath1; '\0' != *psrc; psrc++, pdst++)
    {
        *pdst = ('\\' == *psrc) ? '/' : *psrc;
    }

    *pdst = '\0';

    return dstPath1;
}

#ifdef USE_SAFE_PATH_FUNC

// ��ֹ�����º����н����滻������
# undef mrc_open
# undef mrc_mkDir
# undef mrc_rmDir
# undef mrc_rename
# undef mrc_remove
# undef mrc_fileState
# undef mrc_getLen
# undef mrc_readAll

//���ļ�
int32 mrc_open_s(const char *filename, uint32 mode)
{
    return mrc_open(ConvertPathSeparator(filename), mode);
}

//�����ļ���
int32 mrc_mkDir_s(const char *name)
{
    return mrc_mkDir(ConvertPathSeparator(name));
}

//ɾ���ļ���
int32 mrc_rmDir_s(const char *name)
{
    return mrc_rmDir(ConvertPathSeparator(name));
}

//�������ļ�(��)
int32 mrc_rename_s(const char* oldname, const char* newname)
{
    return mrc_rename(ConvertPathSeparator(oldname), ConvertPathSeparator1(newname));
}

//ɾ���ļ�
int32 mrc_remove_s(const char* filename)
{
    return mrc_remove(ConvertPathSeparator(filename));
}

//ȡ���ļ�������Ϣ
int32 mrc_fileState_s(const char* filename)
{
    return mrc_fileState(ConvertPathSeparator(filename));
}

//ȡ���ļ�����
int32 mrc_getLen_s(const char* filename)
{
    return mrc_getLen(ConvertPathSeparator(filename));
}

//��ȡ�ļ�����������
void* mrc_readAll_s(const char* filename, uint32 *len)
{
    return mrc_readAll(ConvertPathSeparator(filename), len);
}

#endif
