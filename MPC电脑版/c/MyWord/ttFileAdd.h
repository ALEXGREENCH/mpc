/*
* �ļ���������
* By:����
* QQ:643552878
* Date:2012.8.20
*/

/*���ļ��������ļ������ַ���ָ�룬������ڴ����Լ��ͷ�*/
void *FileOpen(char *FileName)
{
 uint32 f,len;
 len=getlen(FileName);
 void *Buffer=(void*)malloc(len);
 f=open(FileName,1);
 read(f,Buffer,len);
 return Buffer;
}


//ÿ�β������ݴ����ٶȴ�С,��λ:�ֽ�
#define MAXLEN 10240


/*��FileName���Ƶ�FileName2
����:
�ɹ� >0 ʧ��-1(��ͬ)
*/
int FileCopy(char *FileName,char *FileName2)
{
 if(getlen(FileName)<=0)
 return -1;
 return AddFileTo(FileName,FileName2);
}
/*��FileName���Ƶ�FileName2��β,��FileName2�������򴴽�֮.
*/
int AddFileTo(char *FileName,char *FileName2)
{
 uint32 Filef,Filef2,
NowLen=0,//���ƽ���
FileLen=getlen(FileName);//FileName�ļ�����

 if(FileLen<=0)
 return -1;
 Filef=open(FileName,1);
 Filef2=open(FileName2,8);

 seek(Filef2,0,SEEK_END);
 void *Buffer=(void*)malloc(MAXLEN);

 while(1)
 {
 memset(Buffer,NULL,MAXLEN);
 seek(Filef,NowLen,SEEK_SET);
 uint32 ReadLen=read(Filef,Buffer,MAXLEN); 
 write(Filef2,Buffer,ReadLen);
 ;
 NowLen+=ReadLen;
 if(ReadLen<MAXLEN)
 break;
 }
 free(Buffer);
 close(Filef);
 return close(Filef2);
}

//By:����