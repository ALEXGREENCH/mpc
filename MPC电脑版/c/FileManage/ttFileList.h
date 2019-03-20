/*
* ttFileList.h
* �ļ��б��װ
* By:����
* QQ:643552878
* Date:2012.8.5
*/

/*�ļ�����󳤶�*/
#define MAXNAME 200

/*����ļ���*/
#define MAXFILE 500

/*�ļ��ṹ��*/
typedef struct filepoint
{
 struct filepoint *prev;//ǰ1��
 struct filepoint *next;//��1��
 char *name;//�ļ���
 uint8 type;//�ļ�����
 uint32 len;//�ļ�����
}*FilePoint;

/*�ļ��ṹ�峤��*/
uint32 FilePointLen=sizeof(struct filepoint);

/*�ļ��б�ṹ��*/
typedef struct filelist
{
 FilePoint first;//�б�ͷ
 FilePoint last;//�б��β
 FilePoint now;//��������
 char *path;//��ǰĿ¼
 uint32 FileN;//�ļ���
 uint32 NowN;//�������
}*FileList;

/*�ļ��б�ṹ�峤��*/
uint32 FileListLen=sizeof(struct filelist);


/*
* ����һ���ļ��б�
* ����:
* �ɹ�:�б�ṹָ�� ʧ��:NULL
*/
void* FileListCreate()
{
 FileList list=(struct filelist*)malloc(FileListLen);
 if(list==NULL)
 return NULL;
 memset(list,NULL,FileListLen);
 list->path="";
 return list;
}

/*
* ɾ���ļ��б�
* list: �ļ��ṹ��ָ��
*/
void FileListDel(FileList list)
{
 FilePointAllDel(list->first); 
 free(list->path);
 free(list);
 list=NULL;
}

/*
* ����һ���ļ����
* ����:
* �ɹ�:���ָ�� ʧ��:NULL
*/
void* FilePointCreate()
{
 FilePoint one=(struct filepoint*)malloc(FilePointLen);
 if(one==NULL)
 return NULL;
 memset(one,NULL,FilePointLen);
 return one;
}

/*ɾ��һ���ļ����*/
void FilePointDel(FilePoint one)
{
 free(one->name);
 free(one);
 one=NULL;
}

/*ɾ�������ļ����*/
void FilePointAllDel(FilePoint first)
{
 FilePoint now=first;
 while(now->next!=NULL)
 {
  now=now->next;
  FilePointDel(now->prev);
 }
}

/*
* �ļ�����
* list:�����ļ��б� 
*/
void FindPath(FileList list)
{
 if(list==NULL)
 return;

 list->first=FilePointCreate();
 FilePoint to=list->first;
 list->FileN=0;

 char *buffer=(char*)malloc(MAXNAME+FilePointLen);

 uint32 f=findstart(list->path,buffer,MAXNAME);
 findnext(f,buffer,MAXNAME);

 while(list->FileN<=MAXFILE)
 {
 memset(buffer,NULL,MAXNAME);
 if(-1==findnext(f,buffer,MAXNAME))
 break;

//����1�����
 FilePoint one=FilePointCreate();

//�������д�����
 uint32 len=strlen(buffer)+FilePointLen;
 one->name=malloc(len);
 strncpy(one->name,buffer,len);
//��ȡ�ļ����͡�����
 char *str=(char*)malloc(strlen(list->path)+strlen(one->name)+1);
 sprintf(str,"%s/%s",list->path,one->name);
 one->type=GetFileKind(str);
 if(one->type!=Is_Dir)
 one->len=getlen(str);
 else
 one->len=strlen(str);
 free(str);

//��������
 one->prev=to;
 to->next=one;
 to=to->next;
 list->FileN++;
 }
 findstop(f);
 free(buffer);

 list->first=list->first->next;
 FilePointDel(list->first->prev);
 list->last=to;
 list->now=list->first;
 list->NowN=1;
}


//��ȡ�ļ������ַ�����type:�ļ�����
char* GetFileKindStr(uint8 type)
{
 char *FileKindStr[7]={"δ֪����","�ļ���","ѹ������", "����","ͼƬ","�ı�","���"};
 return FileKindStr[type];
}

//^
enum
{
 Is_Not=0,
 Is_Dir,
 Is_Zip,
 Is_Music,
 Is_Photo,
 Is_Book,
 Is_Mrp
};

//��ȡ�ļ�����
int GetFileKind(char *Name)
{
//return filestate(Name);

 char *str;
 if(filestate(Name)==IS_DIR)
 return Is_Dir;
 str=strrchr(Name,'.');
 if(str==NULL)
 return Is_Not;
 switch(0)
 {
 case strcmp(str,".jpg"):
 case strcmp(str,".png"):
 case strcmp(str,".gif"):
 case strcmp(str,".bmp"):
 return Is_Photo;
 break;

 case strcmp(str,".mp3"):
 case strcmp(str,".wav"):
 case strcmp(str,".amr"):
 case strcmp(str,".mid"):
 return Is_Music;
 break;

 case strcmp(str,".txt"):
 case strcmp(str,".c"):
 case strcmp(str,".h"):
 case strcmp(str,".lrc"):
 case strcmp(str,".wml"):
 return Is_Book;
 break;

 case strcmp(str,".zip"):
 case strcmp(str,".jra"):
 case strcmp(str,".gz"):
 return Is_Zip;
 break;

 case strcmp(str,".mrp"):
 return Is_Mrp;
 break;
 }
 return Is_Not;
}

//By:����