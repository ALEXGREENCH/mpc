#include "mrc_base.h"




int32 usedTime, recevLen, headLen,fileLen;//��ʱ�������������ݵ��ܳ��ȣ�HTTP��Ӧͷ���ȣ��ļ����ݳ���

char hostName[128];
char httpHead[256];
uint16 port;


int32 socketHandle, timerHandle, fileHandle;
char *url;
char *fileName;

char tempData[1024*4];

void StopDownload(void)
{
    if (timerHandle)
    {
        mrc_timerDelete(timerHandle);
        timerHandle = 0;
    }

    if (socketHandle)
    {
        mrc_closeSocket(socketHandle);
        socketHandle = 0;
    }
    if(fileHandle)
    {
        mrc_close(fileHandle);
        fileHandle=0;
    }
    mrc_closeNetwork();
}


void ErrorStop(void)
{
    mrc_clearScreen(0,0,0);
    mrc_drawText("���س���",0,0,255,255,255,0,MR_FONT_MEDIUM);
    mrc_refreshScreen(0,0,240,320);
    StopDownload();
}
void ReceiveCb(int32 data)//�������ݻص�
{
    int32 len;
    static char RecvBuffer[1024*4];

    len = mrc_recv(socketHandle, RecvBuffer, sizeof(RecvBuffer));
    if (0 == len)//�ȴ���������
    {
        usedTime++;
        if (usedTime > 200)
        {
            // �������ݳ�ʱ��
            ErrorStop();
        }
    }
    else if (MR_FAILED == len)
    {
        ErrorStop();
    }
    else
    {
        usedTime = 0;

        if (0 == headLen) //�ڽ�������ͷ
        {
            int respond;
            int templen;
            char *p;
            
            templen=recevLen+len;
            if(templen>sizeof(tempData)) 
            {
                ErrorStop();
                return;
            }
            mrc_memcpy(&tempData[recevLen],RecvBuffer,len);
            p=mrc_strstr(tempData,"\r\n\r\n");
            if (p!=NULL) //ͷ���������
            {
                headLen = p-tempData+4;

                // HTTP/1.1 200 OK
                // Content-Length: 81
                respond = (int)mrc_strtoul(&tempData[9],NULL,10);//�����Ӧ��
                p = mrc_strstr(tempData,"Content-Length: ");//����ļ�����
                if (200 != respond || p==NULL)// ���س���
                {
                    ErrorStop();
                    return;
                }
                fileLen = (int)mrc_strtoul(p+strlen("Content-Length: "),NULL,10);
                mrc_write(fileHandle,&tempData[headLen],templen-headLen);
            }
        }
        else
        {
            mrc_write(fileHandle, RecvBuffer, len);
        }
        recevLen += len;

        if (headLen+fileLen == recevLen) //���ݽ�����
        {
            mrc_clearScreen(0,0,0);
            mrc_drawText("�������",0,0,255,255,255,0,MR_FONT_MEDIUM);
            mrc_refreshScreen(0,0,240,320);
            StopDownload();
        }
    }
}

void httpSendGet(void)//������������
{
    int32 dataLen, sendLen = 0;

    dataLen = strlen(httpHead);
    // �������󡭡�
    do{
        sendLen += mrc_send(socketHandle, &httpHead[sendLen], dataLen - sendLen);
    } while (sendLen < dataLen);
}


void ConnectCb(int32 data)//����״̬��ѯ�ص�
{
    int32 conState = mrc_getSocketState(socketHandle);

    switch (conState)
    {
    case MR_WAITING:// ���ӷ�����        
        usedTime++;
        if (usedTime > 100)// ���ӷ�������ʱ
        {            
            ErrorStop();
        }
    	break;
    case MR_SUCCESS:
        mrc_timerStop(timerHandle);
        httpSendGet();
        usedTime = 0;
        mrc_timerStart(timerHandle, 100, 0, ReceiveCb, 1);
        break;
    case MR_FAILED:
    case MR_IGNORE:
        ErrorStop();
        break;
    }
}

void Connect(int32 ip)//��ʼ����
{
    socketHandle = mrc_socket(MR_SOCK_STREAM, MR_IPPROTO_TCP); //����TCP Socket
    mrc_connect(socketHandle, ip, port, MR_SOCKET_NONBLOCK); //����Socket
    timerHandle = mrc_timerCreate();
    mrc_timerStart(timerHandle, 200, 0, ConnectCb, 1);
}

int32 cbGetHostIp(int32 ip)//����IP�ص�����
{
    if(ip!=-1)//��ȡ�ɹ�
        Connect(ip);
    else
        ErrorStop();
    return 0;
}


int32 cbInitNetwork(int32 result)  //��ʼ���ص�����
{
    switch(result)
    {
    case MR_SUCCESS:
        cbGetHostIp(mrc_getHostByName(hostName, cbGetHostIp)); //����������IP
        break;
    case MR_FAILED:
        ErrorStop();
        break;
    }
    return 0;
}


void parseUrl(void)
{
    int32 hostNameLen;
    char *p;
    char *findPos;

    //http://xxx.xxx.xxx:xxxx/x.xxx
    p = findPos = (char*)mrc_strchr(&url[7], '/');//����http://�ҵ�һ��/
    

    //��ȡ�������Ͷ˿ں�
    p = (char*)mrc_strchr(&url[7], ':');
    if (NULL != findPos)
        hostNameLen = findPos - &url[7];
    else
        hostNameLen = mrc_strlen(url) - 7;
    if (NULL != p)//����ж˿ںţ����¼�������������
        hostNameLen = p - &url[7];
    mrc_strncat(hostName, &url[7], hostNameLen);

    if (NULL == p)
        port = 80;
    else
        port = (uint16)mrc_strtoul(p+1, NULL, 10);

    //����HTTP����ͷ
    if (NULL == findPos)//����"http://"���������/���ʾ�Ǿ�����ļ�
        findPos="/";//������ҳ
    mrc_sprintf(httpHead, "GET %s HTTP/1.1\r\nHost: %s\r\nAccept: */*\r\nConnection: close\r\n\r\n", findPos, hostName);
}

void StartDownLoad(void)//��ʼ���أ���ʼ�����磩
{
    usedTime = 0;
    recevLen = 0;
    fileLen = 0;
    mrc_remove(fileName);
    fileHandle = mrc_open(fileName, MR_FILE_RDWR | MR_FILE_CREATE);
    if(!fileHandle) return;
    parseUrl();
    cbInitNetwork(mrc_initNetwork(cbInitNetwork, "cmnet"));
}
#include "mrc_sound.h"
int32 mrc_init(void)
{
//     url="http://wap.wpa8y.com/logo1.gif";
//     fileName="logo1.gif";

//     url="http://zengming00.vicp.cc:8000/index.html";
//     fileName="zen.txt";
    url="http://img1.pengfu.cn/big/197/407197.gif";
    fileName="407197.gif";
mrc_playSoundExInit(0);
    StartDownLoad();
    return MR_SUCCESS;
}


int32 mrc_event(int32 code, int32 param0, int32 param1)
{
	return MR_SUCCESS;
}

int32 mrc_pause(void)
{
	return 0;
}

int32 mrc_resume(void)
{
	return 0;
}

int32 mrc_exitApp(void)
{
	return 0;
}
int32 mrc_extRecvAppEventEx()
{
	return 0;
}
int32 mrc_extRecvAppEvent()
{
	return 0;
}