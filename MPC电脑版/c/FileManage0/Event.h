
uint8 Jm;//�������

//����ȡֵ
enum
{
 Jm_LIST=1,//�б�
 Jm_MENU,//�˵�
 Jm_HELP,//����
 Jm_ABOUT,//����
 Jm_FILE_MSG,//�鿴�ļ���Ϣ
 Jm_PHOTO,//���ͼƬ
 Jm_TXT,//���TXT
 Jm_MUSIC//��������
};

int event(int type,int p1,int p2)
{
 if(type==KY_DOWN)
 {
//����˳�
  if(p1==_STAR)exitapp();

//�ļ��б���水��
 else if(Jm==Jm_LIST)
 switch(p1)
 {
 case _SLEFT:
 DrawMenuList();break;

 case _SRIGHT:
 if(Focus.dir=="")
 exitapp();
 char *str=strrchr(Focus.dir,'/');
 if(str!=NULL)
 {
 int l=strlen(str);
 int l2=strlen(Focus.dir);
 memset(Focus.dir+(l2-l),NULL,l);
 FindFile();
 DrawList();
 }
 else exitapp();
 break;

 case _SELECT:
 if(Focus.now->mode==IS_DIR)
 {
 char *str=FileName(Focus.dir,Focus.now->name);
 free(Focus.dir);
 Focus.dir=str;
 FindFile();
 DrawList();
 }
 else OpenFile();
 break;

 case _DOWN:case _8:
 Down(p1);
 break;

 case _UP:case _2:
 Up(p1);break;
 case _9:
 DrawFileMsg();break;

 }
 else if(Jm==Jm_MUSIC)
 switch(p1)
 {
  case _SRIGHT:
  Jm=Jm_LIST;DrawList();break;
 case _SELECT:
 if(PALY_MUSIC.state)
 StopPaly();
 else PalyMusic(PALY_MUSIC.filename);
 PALY_MUSIC.state=!PALY_MUSIC.state;
 break;

 case _DOWN:
 if(PALY_MUSIC.state)
 if(PALY_MUSIC.volume>0)
 PALY_MUSIC.volume--;
 setvolume(PALY_MUSIC.volume);
 break;

 case _UP:
 if(PALY_MUSIC.state) 
 if(PALY_MUSIC.volume<5)
 PALY_MUSIC.volume++;
 setvolume(PALY_MUSIC.volume);
 break;
 }

 else if((Jm==Jm_PHOTO)||(Jm==Jm_HELP)||(Jm==Jm_ABOUT)||(Jm==Jm_FILE_MSG))
 {
  if(p1==_SRIGHT)
  { Jm=Jm_LIST;
   DrawList();
  }
 }

 }
 return NULL;
}

int pause()
{return NULL;}

int resume()
{
 if(Jm=IS_LIST)DrawList();
 return NULL;
}


void exitapp()
{
 DrawMsg("�˳���...");
 DelAll();
 free(FileBmp);
 free(DirBmp);
 timerdel(Focus.timer);

 if(Focus.dir!="")
 free(Focus.dir);
 
 StopPaly();
 sleep(500);
 exit();
}

//�����ƶ�
void Down(int p1)
{
 if(Focus.all>1)
 if(Focus.num<Focus.all)
 {
 Focus.num++;
 Focus.now=Focus.now->next;
 }
 else
 {
 Focus.num=1;
 Focus.now=First;
 }
 DrawList();
}


//�����ƶ�
void Up(int p1)
{
 if(Focus.all>1)
 if(Focus.num>1)
 {
 Focus.num--;
 Focus.now=Focus.now->last;
 }
 else
 {
 Focus.num=Focus.all;
 Focus.now=End; 
 }
 DrawList();
}

//�����ļ�·��
char *FileName(char *dir,char *str)
{
 uint32 len=strlen(dir)+strlen(str)+2;
 char *Name=malloc(len);
 memset(Name,NULL,len);
 sprintf(Name,"%s/%s",dir,str);
 return Name;
}


int OpenFile()
{
 char *str=strrchr(Focus.now->name,'.');
 if(str==NULL)return -1;
 char *path=FileName(Focus.dir,Focus.now->name);
 switch(0)
 {
 case strcmp(str,".jpg"):
 case strcmp(str,".gif"):
 img(path,0,0);
 Jm=Jm_PHOTO;
 break;

 case strcmp(str,".mp3"):
 Jm=Jm_MUSIC;
 PalyMusic(path);
 DrawPaly();
 break;
 }
 if(Jm==Jm_LIST)
 {
 DrawMsg("�ݲ�֧�ִ˸�ʽ");
 sleep(500);
 DrawList();
 }
 free(path);
 REF;return 1;
}
