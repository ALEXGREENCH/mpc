

#define BigNameLen 250
//�����ļ�����󳤶�

char *FileKind[6]={"ͼƬ","����","�ı�", "ѹ������","Ӧ�����","δ֪����"};

enum
{
 KIND_PHOTO=0,
 KIND_MUSIC,
 KIND_BOOK,
 KIND_ZIP,
 KIND_MRP,
 KIND_NOTKNOW
};

//��ȡ�ļ�����
uint32 GetFileKind(char *Name)
{
 char *str=strrchr(Name,'.');
 if(str==NULL)
 return KIND_NOTKNOW;
 switch(0)
 {
 case strcmp(str,".jpg"):
 case strcmp(str,".png"):
 case strcmp(str,".gif"):
 case strcmp(str,".bmp"):
 return KIND_PHOTO;
 break;
 case strcmp(str,".mp3"):
 case strcmp(str,"mid"):
 return KIND_MUSIC;
 break;
 case strcmp(str,".txt"):
 case strcmp(str,".c"):
 case strcmp(str,".h"):
 case strcmp(str,".lrc"):
 case strcmp(str,".wml"):
 return KIND_BOOK;
 break;
 case strcmp(str,".zip"):
 case strcmp(str,".jra"):
 case strcmp(str,".gz"):
 return KIND_ZIP;
 break;
 case strcmp(str,".mrp"):
 return KIND_MRP;
 break;
 }
 return KIND_NOTKNOW;
}


//�ļ�����ṹ��
;typedef struct listst
{
 struct listst *last;//�ϸ�
 struct listst *next;//�¸�
 char *name;//�ļ���
 uint8 mode;//�ļ�����
}LISTST;

uint32 ListLen=sizeof(LISTST);

LISTST
*First,//��ͷ
*End;//��β

struct
{
 LISTST *now;//��������
 char *dir;//��ǰĿ¼
 LISTST *one;//
 uint32 onenum;//
 uint32 num;//��ǰ�ļ���
 uint32 all;//���ļ���
 uint32 timer;//������ʱ�����
}Focus;

Focus.dir="";
Focus.timer=timercreate();


//�����ʼ��
void ListStart()
{
 if(First!=NULL)
 {
  free(First->name);
  free(First);
 }
 First=malloc(ListLen);
 memset(First,NULL,ListLen);
}


//�ļ���������������
void FindFile()
{
 DrawMsg("������...");

 Focus.all=0;
 ListStart();

 LISTST *to=First;
 char *buffer=malloc(BigNameLen);

 int len=0,f=findstart(Focus.dir,buffer,BigNameLen);

 int ret=findnext(f,buffer,BigNameLen);
 if(ret!=-1)
 while(1)
 {
 memset(buffer,NULL,BigNameLen);
 if(findnext(f,buffer,BigNameLen)==-1)
 break;
 LISTST *one=malloc(ListLen);
 memset(one,NULL,ListLen);
 one->last=to;
 one->next=NULL;
 int l=strlen(buffer)+ListLen;
 one->name=malloc(l);
 memset(one->name,NULL,l);
 strncpy(one->name,buffer,l);

 char *ptr=FileName(Focus.dir,one->name);
 one->mode=filestate(ptr);
 free(ptr);
 // printf("%s\n",one->name);

 to->next=one;
 to=to->next;
 Focus.all++;
 }
 if(Focus.all>0)
 {
 First=First->next;
 free(First->last);

 End=to->last->next;
 Focus.now=First;
 Focus.num=1;
 }
 else
 {
 DrawMsg("���ļ���");
 sleep(300);
 event(KY_DOWN,_SRIGHT,NULL);
 }
 findstop(f);
 free(buffer);
 Jm=Jm_LIST;
}

//ɾ���ļ�����
void DelAll()
{
 LISTST *to=First;

 while(to->next!=NULL)
 {
 to=to->next;
 free(to->last->name);
 free(to->last);
 to->last=NULL; }

}

//�����ǰ�ļ��б�
void PrintfFileList()
{
 LISTST *to=First;
 printf("\n\n��ǰĿ¼:%s\n",Focus.dir);

 while(to->next!=NULL)
 {
 printf("%s\n",to->name);
 to=to->next;
 }

}
