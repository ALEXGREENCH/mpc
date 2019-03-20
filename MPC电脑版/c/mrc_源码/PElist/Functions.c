/*
 * ����ͨ�ú�������
 * ��Ȩ���� (C) 2011-2012 eleqian
 * [6/5/2012]
 */

#include <mrc_base.h>
#include <mrc_base_i.h>
#include <mrc_exb.h>
#include <mrc_bmp.h>

#include "Functions.h"
#include "String.h"

// ���̿ռ�ṹ��
typedef struct
{
    uint32 total;    // �ܵĴ�С
    uint32 tunit;    // �ܴ�С�ĵ�λ
    uint32 account;  // ʣ��ռ�Ĵ�С
    uint32 unit;     // ʣ���С�ĵ�λ
} T_DSM_FREE_SAPCE;

/*-------------------------------------------------------------------------------------------------*/

//ȡ��ָ������Ŀ¼�ļ���С
int32 FileLenInPath(const char *path, const char *name)
{
    int32 ret = 0;

    if (NULL != path)
        Switch2Dir(path);

    ret = mrc_getLen(name);

    if (NULL != path)
        Switch2Dir(NULL);

    return ret;
}

//��ָ������Ŀ¼���ļ�
int32 OpenInPath(const char *path, const char *name, uint32 mode)
{
    int32 fd = 0;
    int32 ret = 0;

#ifndef SDK_MOD  // ģ����������Ȼʧ��
    if (NULL != path)
        ret = Switch2Dir(path);
#endif

    if (0 == ret)
        fd = mrc_open(name, mode);

#ifndef SDK_MOD
    if (NULL != path)
        Switch2Dir(NULL);
#endif

    return fd;
}

//��ȡ�ļ�
//������·�����ļ�������ȡλ�ã�����������������С
//���أ�ʵ�ʶ�ȡ��С
int32 ReadFile(const char *dir, const char *file, int32 pos, uint8 *buf, int32 bufSize)
{
    int32 fd;
    int32 rSize = -1;

    memset(buf, 0, bufSize);
    fd = OpenInPath(dir, file, MR_FILE_RDONLY);
    if (fd > 0)
    {
        if (MR_SUCCESS == mrc_seek(fd, pos, MR_SEEK_SET))
        {
            rSize = mrc_read(fd, buf, bufSize);
        }
        mrc_close(fd);
    }

    return rSize;
}

//�����ļ�
//������·�����ļ�������ȡλ�ã�����������������С
//���أ�ʵ�ʱ����С
int32 SaveFile(const char *dir, const char *file, int32 pos, uint8 *buf, int32 bufSize)
{
    int32 fd;
    int32 rSize = -1;

    fd = OpenInPath(dir, file, MR_FILE_RDWR | MR_FILE_CREATE);
    if (fd > 0)
    {
        mrc_seek(fd, pos, MR_SEEK_SET);
        rSize = mrc_write(fd, buf, bufSize);
        mrc_close(fd);
    }

    return rSize;
}

//���ļ���������λ��
//�������ļ�������ʼ����ƫ�ƣ��������ݣ����ݴ�С
//���أ��ҵ���λ��
int32 FindFromFile(const char *dir, const char *file, int32 offset, uint8 *data, int32 size)
{
    int32 ret = -1;
    int32 fd;

    fd = OpenInPath(dir, file, MR_FILE_RDONLY);
    if (0 == fd)
        return ret;

    ret = FindFromFileByHandle(fd, offset, data, size);

    mrc_close(fd);

    return ret;
}

//���ļ���������λ��-�����
//�������ļ�������ļ�ƫ�ƣ��������ݣ����ݴ�С
//���أ��ҵ���λ��
int32 FindFromFileByHandle(int32 fd, int32 offset, uint8 *data, int32 size)
{
    uint32 *bad_char_skip;
    uint8 *databuf = NULL, *pfind;
    int32 bufUsed, readPos;
    int32 ret = -1;

    if (0 == fd)
        return ret;

    readPos = offset;
    databuf = (uint8 *)malloc(DATA_BUFFER_SIZE_NORMAL);
    memset(databuf, 0, DATA_BUFFER_SIZE_NORMAL);

    bad_char_skip = (uint32 *)malloc(256 * sizeof(uint32));
    ret = BMH_BuildTable(bad_char_skip, 256, data, size);

    while (1)
    {
        mrc_seek(fd, readPos, MR_SEEK_SET);
        bufUsed = mrc_read(fd, databuf, DATA_BUFFER_SIZE_NORMAL);
        if (bufUsed <= 0)
            break;

        pfind = BMH_Ex(bad_char_skip, databuf, bufUsed, data, size);
        if (NULL != pfind)
        {
            ret = readPos + (pfind - databuf);
            break;
        }

        readPos += (DATA_BUFFER_SIZE_NORMAL - size + 1);
    }

    TRYFREE(bad_char_skip);
    TRYFREE(databuf);

    return ret;
}

/*---------------------------------------------------------------------------*/

//�����ļ�
//������Դ�ļ�·����Ŀ���ļ�·��
int32 CopyFile(const char *srcFile, const char *destFile)
{
    int32 ifd, ofd; //Դ�ļ���Ŀ���ļ����
    int32 ret = MR_FAILED, copySize;

    copySize = mrc_getLen(srcFile);
    if (copySize < 0)
        return MR_FAILED;

    ifd = mrc_open(srcFile, MR_FILE_RDONLY); //��Դ�ļ�(ֻ��)
    ofd = mrc_open(destFile, MR_FILE_WRONLY | MR_FILE_CREATE); //��Ŀ���ļ�(�����ڴ���)

    if(ifd != 0 && ofd != 0) //���ļ����ɹ�
    {
        mrc_seek(ifd, 0, MR_SEEK_SET);
        mrc_seek(ofd, 0, MR_SEEK_SET);

        ret = CopyFileByHandle(ifd, ofd, copySize);
    }

    TRYCLOSE(ifd); //�ر�Դ�ļ�
    TRYCLOSE(ofd); //�ر�Ŀ���ļ�

    return ret; 
}

//�����ļ�-����·����
//������Դ�ļ�·����Ŀ���ļ�·��
int32 CopyFileFullPath(const char *srcPath, const char *destPath, const char *srcFile, const char *destFile)
{
    int32 ofd = 0, ifd = 0; //Դ�ļ���Ŀ���ļ����
    int32 ret = MR_FAILED, copySize;

    copySize = FileLenInPath(srcPath, srcFile);
    if (copySize < 0)
        return MR_FAILED;

    ifd = OpenInPath(srcPath, srcFile, MR_FILE_RDONLY); //��Դ�ļ�(ֻ��)
    ofd = OpenInPath(destPath, destFile, MR_FILE_WRONLY | MR_FILE_CREATE); //��Ŀ���ļ�(�����ڴ���)

    if(ifd != 0 && ofd != 0) //���ļ����ɹ�
    {
        mrc_seek(ifd, 0, MR_SEEK_SET);
        mrc_seek(ofd, 0, MR_SEEK_SET);

        ret = CopyFileByHandle(ifd, ofd, copySize);
    }

    TRYCLOSE(ofd); //�ر�Ŀ���ļ�
    TRYCLOSE(ifd); //�ر�Դ�ļ�

    return ret;     
}

//�����ļ�-��չ��
//������Դ�ļ�·����Ŀ���ļ�·����Դ�ļ���ʼλ�ã�Ŀ���ļ���ʼλ�ã����ƴ�С
int32 CopyFileEx(const char *srcFile, const char *destFile, uint32 srcPos, uint32 destPos, uint32 copySize)
{
    int32 ifd, ofd; //Դ�ļ���Ŀ���ļ����
    int32 ret = MR_FAILED;

    ifd = mrc_open(srcFile, MR_FILE_RDONLY); //��Դ�ļ�(ֻ��)
    ofd = mrc_open(destFile, MR_FILE_WRONLY | MR_FILE_CREATE); //��Ŀ���ļ�(�����ڴ���)

    if(ifd != 0 && ofd != 0) //���ļ����ɹ�
    {
        mrc_seek(ifd, srcPos, MR_SEEK_SET);
        mrc_seek(ofd, destPos, MR_SEEK_SET);

        ret = CopyFileByHandle(ifd, ofd, copySize);
    }

    TRYCLOSE(ifd); //�ر�Դ�ļ�
    TRYCLOSE(ofd); //�ر�Ŀ���ļ�

    return ret;
}

//�����ļ�-�����
//������Դ�ļ������Ŀ���ļ���������ƴ�С
int32 CopyFileByHandle(int32 ifd, int32 ofd, uint32 copySize)
{
    uint8 *dataBuf = NULL; //�ļ���д����
    int32 size_read, size_write; //���ζ�д��С
    uint32 size_to_read, size_copied; //��Ҫ��ȡ��С���ܸ��ƴ�С
    int32 ret;

    if(0 == ifd || 0 == ofd) //�����Ч
        return MR_FAILED;

    dataBuf = (uint8*)malloc(DATA_BUFFER_SIZE_NORMAL);
    if (NULL == dataBuf) //�ڴ治��
        return MR_FAILED;

    memset(dataBuf, 0, DATA_BUFFER_SIZE_NORMAL);
    size_copied = 0;
    ret = MR_SUCCESS;

    while (copySize > size_copied) //ֱ���������
    {
        size_to_read = MIN(DATA_BUFFER_SIZE_NORMAL, copySize - size_copied);

        size_read = mrc_read(ifd, dataBuf, size_to_read); //��ȡ�ļ�
        if (size_read <= 0)
        {
            ret = MR_FAILED;
            break;
        }

        size_write = mrc_write(ofd, dataBuf, size_read); //д�ļ�
        if (size_write <= 0 || size_write != size_read)
        {
            ret = MR_FAILED;
            break;
        }

        size_copied += size_read;
    }

    TRYFREE(dataBuf); //�ͷ��ڴ�

    return ret;
}

/*---------------------------------------------------------------------------*/

// ��mrp��ȡ�ı��ļ�ȫ������
char *ReadStringFromMrp(const char *name)
{
    char *gbstr;
    char *fbuf;
    int32 fsize;

    fbuf = mrc_readFileFromMrp(name, &fsize, 0);
    if (NULL != fbuf)
    {
        gbstr = (char*)malloc(fsize + 1);
        memcpy(gbstr, fbuf, fsize);
        gbstr[fsize] = '\0';
        mrc_freeFileData(fbuf, fsize);
    }
    else
    {
        return NULL;
    }

    return gbstr;
}

//����ǰ���ֽ�˳��
void SwapBytes(uint8 *data, int32 size)
{
    int32 i;
    uint8 tByte;

    for (i = 0; i < size; i += 2)
    {
        tByte = data[i];
        data[i] = data[i + 1];
        data[i + 1] = tByte;
    }
}

//���м򵥼����ַ��Ľ���
//�������ַ���������ֽ�
void DecodeStr(uint8 *strBytes, uint8 XorByte)
{
    uint8 *p = strBytes;

    while (0 != *p)
        *p++ ^= XorByte;
}

/*-------------------------------------------------------------------------------------------------*/

//���浱ǰ��ĻΪͼƬ
void Screen2File(const char *name_w)
{
    char *picPath = NULL;
    char *name_a = NULL;


    picPath = (char*)malloc(MAX_PATH_LEN_A);
    memset(picPath, 0, MAX_PATH_LEN_A);
    strcat(picPath, "eles/SnapPic");
    MakeDir(picPath);
    strcat(picPath, "/");

    name_a = stru2c(name_w);
    strcat(picPath, name_a);
    TRYFREE(name_a);

    mrc_PrintScreen(picPath);

    TRYFREE(picPath);
}

//��ɫֵת��Ϊ�ṹ
void Color2ST(uint32 uColor, mr_colourSt *tColor)
{
    tColor->r = (uint8)(uColor >> 16) & 0xff;
    tColor->g = (uint8)(uColor >> 8) & 0xff;
    tColor->b = (uint8)(uColor & 0xff);
}

//��¼��־
void WLog(const char* text)
{
	int32 fd=0;

	if(mrc_fileState("MDs/log.ini") != MR_IS_INVALID || mrc_fileState("MDs/log.ini") == MR_IS_DIR)
		mrc_remove("MDs/log.ini");

	fd = mrc_open("MDs/log.ini", MR_FILE_RDWR | MR_FILE_CREATE);
	if(fd != 0)
	{
		mrc_seek(fd, 0, MR_SEEK_SET);
		mrc_write(fd, (void*)text, mrc_strlen(text));
	}
	mrc_close(fd);
}

/*-------------------------------------------------------------------------------------------------*/

//��ȡ��ǰ·����
//���������������
int32 GetCurDir(char *strDir)
{
    int32 ret = MR_FAILED, len = 0;
    uint8 *pDir = NULL;

    if (NULL == strDir)
        return MR_FAILED;

#ifdef WIN32
    return MR_FAILED;
#endif

    ret = mrc_platEx(1204, (uint8*)"Y", 1, &pDir, &len, NULL);
    if (MR_SUCCESS == ret)
    {
        memcpy(strDir, pDir, len + 1);
        TRYFREE(pDir);
        ret = len;
    }

    return ret;
}

//�л�Ŀ¼
//������·����NULL�л����ϴ�Ŀ¼
int32 Switch2Dir(const char* strDir)
{
    static char lastDir[MAX_PATH_LEN_A];
    int32 slen, ret;

#ifdef WIN32
    return MR_FAILED;
#endif

    if (NULL != strDir)
    {
        slen = strlen(strDir);
        GetCurDir(lastDir);
        ret = mrc_platEx(1204, (uint8*)ConvertPathSeparator(strDir), slen, NULL, NULL, NULL);
    }
    else
    {
        if ('\0' == lastDir[0])
            lastDir[0] = 'Z';
        slen = strlen(lastDir);
        ret = mrc_platEx(1204, (uint8*)lastDir, slen, NULL, NULL, NULL);
    }

    return ret;
}

// �������Ŀ¼
// �ɹ�����0��ʧ�ܷ���-1
int32 MakeDir(const char *newdir)
{
    char *strBuf = NULL;
    char *p = NULL;
    int32 len = 0;

    if (NULL == newdir || '\0' == *newdir) 
        return -1;

    len = strlen(newdir);
    strBuf = strdup(newdir);

    // �滻��б��Ϊб��
    for (p = strBuf; '\0' != *p; p++)
    {
        if ('\\' == *p)
            *p = '/';
    }

    // �������ķָ���
    if ('/' == strBuf[len - 1])
        strBuf[len - 1] = '\0';

    // ѭ������
    for (p = strBuf + 1; p < strBuf + len; p++)
    {
        // ������һ��Ŀ¼
        while(('\0' != *p) && ('/' != *p)) 
            p++;
        *p = '\0';

        if (MR_IS_FILE == mrc_fileState(strBuf)) // �����ͬ���ļ���Kill
            mrc_remove(strBuf);
        if (MR_IS_DIR != mrc_fileState(strBuf)) // ������ļ��У�Make
            mrc_mkDir(strBuf);
        if (MR_IS_DIR != mrc_fileState(strBuf)) // ����ʧ��
        {
            TRYFREE(strBuf);
            return -1;
        }

        *p = '/';
    }

    TRYFREE(strBuf);
    return 0;
}

// �������Ŀ¼���Զ��жϾ��Ժ����·��
// �ɹ�����0��ʧ�ܷ���-1
int32 MakeDirEx(const char *newdir)
{
    char *p;
    int32 ret;

    p = (char*)strchr(newdir, ':');

    if (NULL != p)
    {
        // ����·��
        *(p + 1) = '\0';
        ret = Switch2Dir(newdir);
        if (0 == ret)
            ret = MakeDir(p + 2);
        Switch2Dir(NULL);
    }
    else
    {
        // ���·��
        ret = MakeDir(newdir);
    }

    return ret;
}

//ȡ�ô��̿ռ��С
//�������̷�����С���ͣ�0 - �ܴ�С��1 - ʣ���С
//���أ���С��-1ʧ��
int64 GetDiskSize(const char* strDisk, uint8 Type)
{
    T_DSM_FREE_SAPCE *getInfo = NULL;
    //MR_PLAT_EX_CB cb = NULL;
    int32 output_len = 0;
    int32 ret;

    ret = mrc_platEx(1305, (uint8*)strDisk, 1, (uint8**)&getInfo, &output_len, NULL);
    if (MR_SUCCESS == ret)
    {
        if (0 == Type)
        {
            return (int64)getInfo->total * (int64)getInfo->tunit;
        }
        else if (1 == Type)
        {
            return (int64)getInfo->account * (int64)getInfo->unit;
        }

        /*if (NULL != cb)
            cb((uint8*)getInfo, output_len);*/
    }

    return -1;
}

// ȡ�ó���ID
int32 GetAppId(void)
{
    int32 appid = 0;
    char *pMrpName = mrc_getPackName();

    mrc_GetMrpInfo(pMrpName, MRP_APPID, (uint8*)&appid, sizeof(int32));

    return appid;
}

// ȡ�ó���汾
int32 GetAppVer(void)
{
    int32 appver = 0;
    char *pMrpName = mrc_getPackName();

    mrc_GetMrpInfo(pMrpName, MRP_APPVER, (uint8*)&appver, sizeof(int32));

    return appver;
}

//�ݹ�ɾ���ļ����µ������ļ�
int32 removeDir(const char* dirName)
{
    char fullName[128];
    char fileName[64];

    int32 ret = -1;
    int32 dirNameLen;
     //��������
    if(!dirName)
        return MR_FAILED;    

    memset(fullName, 0, sizeof(fullName));
    memset(fileName, 0, sizeof(fileName));

    dirNameLen = strlen(dirName);
    memcpy(fullName, dirName, dirNameLen);

    if(fullName[dirNameLen-1] != '/')
    {//׼��ƴ��Ŀ¼�µ����ļ�����Ŀ¼
        fullName[dirNameLen] = '/';
        dirNameLen++;
    }

    if(mrc_fileState(dirName) == MR_IS_DIR)
    {
        int32 fd;
        int32 result = MR_FAILED;
         //������ʼ��
        fd = mrc_findStart(dirName, fileName, sizeof(fileName));
        if(fd > 0)//���������Ч
        {
            result = MR_SUCCESS;

            while(result == MR_SUCCESS)
            {
                //���fileNameȡֵΪ��.����ʶ������ֵ��Ч����������δ���
                if(fileName[0] && fileName[0] != '.')
                {
                    int32 length = strlen(fileName);
                    memcpy(&fullName[dirNameLen], fileName, length);
                    fullName[dirNameLen+length] = 0;

                    if(mrc_fileState(fullName) == MR_IS_FILE)
                    {//�ļ����ͣ�ɾ���ļ�
                        //mrc_printf("ɾ���ļ���%s", fullName);
                        ret = mrc_remove(fullName);
                    }
                    else if(mrc_fileState(fullName) == MR_IS_DIR)
                    {//�ļ������ͣ��ݹ�ɾ�����ļ���
                        //mrc_printf("ɾ���ļ��У�%s", fullName);
                        ret = removeDir(fullName);
                    }
                }
                memset(fileName, 0, sizeof(fileName));
                result = mrc_findGetNext(fd, fileName, sizeof(fileName));
            }
            mrc_findStop(fd);
        }
        //mrc_printf("ɾ����Ŀ¼��%s", dirName);
        ret = mrc_rmDir(dirName);
    }
    return ret;
}
