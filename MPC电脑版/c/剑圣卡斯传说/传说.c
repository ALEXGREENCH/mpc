
int j=1,game_potion=1,an,ti=getuptime();
/*j=0��ͣ,j=1����,j=2ս��*/



#define challenger_NAME "��˹"

char *kill_kind[5]={"����1","����2","����3","����4","����5"};


char *monster_kind[6]={"��ϵ��","ľϵ��","ˮϵ��","��ϵ��","��ϵ��","BOSS"};

/*�������Խṹ��*/
struct CHALLENGER
{
 int x;
 int y;
 char *NAME;
//����
 uint32 LV;
//�ȼ�
 uint32 HP;
//Ѫ��
 uint32 MP;
//ħ��
 uint32 STR;
//������
 uint32 DEF;
//������
 uint32 EXP;
//����
 uint32 NEXT_EXP;
//��������
};

struct CHALLENGER *challenger;
#define Cr challenger

/*��ս�����Գ�ʼ��*/
void chushi_challenger()
{

 if(Cr!=NULL)free(Cr);
 Cr=malloc(sizeof(struct CHALLENGER));

 Cr->x=Cr->y=0;
 Cr->NAME=challenger_NAME;
 Cr->LV=1;
 Cr->HP=10;
 Cr->MP=10;
 Cr->STR=2;
 Cr->DEF=2;
 Cr->EXP=20;
 Cr->NEXT_EXP=Cr->EXP*3;

}

/*����*/
void promote()
{
 if(Cr->LV<LV_BIG)
{
 Cr->LV++;
 Cr->STR+=Cr->STR*10/7;
 Cr->DEF+=Cr->DEF*10/7;
 Cr->HP=Cr->HP*10/6;
 Cr->MP=Cr->MP*10/6;
 Cr->EXP=0;
 Cr->NEXT_EXP=Cr->NEXT_EXP*10/6;
}

}
/*�������Խṹ��*/
struct MONSTER
{
 char *NAME;
 uint32 LV;
 uint32 HP;
 uint32 MP;
 uint32 STR;
 uint32 DEF;
 uint32 EXP;
};

struct MONSTER *monster;
#define Mr monster

/*��ʼ����������*/

void rand_monster()
{
 if(Mr!=NULL)free(Mr);
 Mr=malloc(sizeof(struct MONSTER));

 Mr->NAME=monster_kind[rand()%5];
 Mr->LV=Cr->LV;
 Mr->HP=Cr->HP;
 Mr->STR=Cr->STR/2;
 Mr->DEF=Cr->DEF;
 Mr->MP=Cr->MP;
 Mr->EXP=Cr->EXP/4;
}
uint16 *scr=getscrbuf();
uint16 *person,*guai;

void game_init()
{
 cls(250,250,250);
 
 int l=getlen(tu);
 int l2=getlen(tu2);
 person=malloc(l);
 guai=malloc(l2);
 int32 f=open(tu,1);
 read(f,person,l);
 close(f);
 f=open(tu2,1);
 read(f,guai,l2);
 close(f);

 bmpshowflip(person,0,100,100,100,125,BM_COPY,0,0,0);
 bmp_guai(SCRW-100,100);
 REF;

 sleep(1000);
 cls(10,10,10);
 chushi_challenger();
 rand_monster();
 an=timercreate();
}
/*�����������*/
void challenger_properties()
{
 background();
 char *txt;
 txt=malloc(sizeof(struct CHALLENGER)+50);
 sprintf(txt,"��ɫ:%s\n�ȼ�:%d\nѪ��:%d\nħ��:%d\n������:%d\n������:%d\n����:%d\n��������:%d",Cr->NAME,Cr->LV,Cr->HP,Cr->MP,Cr->STR,Cr->DEF,Cr->EXP,Cr->NEXT_EXP);
 rect_text(txt,tw,th,SCRW,SCRH);
 free(txt);
 REF;
}

//���Ա���
void background()
{
 cls(10,10,10);
 img(cdbei,0,0);
 drect(0,th,SCRW,1,R/2,G/2,B/2);
 drect(0,SCRH-th,SCRW,1,R/2,G/2,B/2);
text("�鿴����",SCRW/2-tw*2,0);
 text("����",SCRW-tw*2,SCRH-th);
}
void monster_properties()
{
 background();
 char *txt;
 txt=malloc(sizeof(struct CHALLENGER)+50);
 sprintf(txt,"����:%s\n����:%d\nѪ��:%d\nħ��:%d\n������:%d\n������:%d\n����:%d",Mr->NAME,Mr->LV,Mr->HP,Mr->MP,Mr->STR,Mr->DEF,Mr->EXP);
 rect_text(txt,tw,th,SCRW,SCRH);
REF;
free(txt);

}


int game_event(int type, int p1, int p2)
{
 if(j==1)
{if(type==KY_DOWN)
 switch(p1)
 {
 case _SRIGHT:
 j=1;jm=0;kz();break;
 
 case _UP:
 case _DOWN:
 case _LEFT:
 case _RIGHT:
 yi(p1);
 timerstart(an,1,p1,"yi",1);
 break;
 }

else if(type==KY_UP)
switch(p1)
{ case _UP:case _DOWN:
 case _RIGHT:case _LEFT:
 timerstop(an);
 break;
}

}

else if(j==2)
{
 if(KY_DOWN==type)
 switch(p1)
{ 
 case _SRIGHT:
 j=1;game_kz();
 break;
}


}

  return 0;
}

void yi(int p1)
{

 switch(p1)
{ 
 case _UP:
 if(Cr->y>0)Cr->y-=10;
 else Cr->y=SCRH-10;
 break;
 case _DOWN:
 if(Cr->y<=SCRH)
 Cr->y+=10;
 else Cr->y=0;
 break;
 case _LEFT:
 if(Cr->x>0)Cr->x-=10;
 else Cr->x=SCRW;
 break;
 case _RIGHT:
 if(Cr->x<SCRW)
 Cr->x+=10;
 else Cr->x=0;
 break;
}
if(j!=1)
timerdel(an);

else if((getuptime()-ti)%10000==0)j=2;

game_kz();



}

int pause(void)
{return 0;}
int resume(void)
{return 0;}

/*�˳�ǰ�Ĺ���*/

void exitapp_game()
{
if(an!=NULL)timerdel(an);
if(Cr!=NULL)free(Cr);
if(Mr!=NULL)free(Mr);
if(person!=NULL)free(person);
if(guai!=NULL)free(guai);
}

void shen()
{
background();

char *t="ʣ���ڴ�:%d.%02dkb";
char *txt=malloc(strlen(t)+10);
int get=getmemremain();
sprintf(txt,t,get/1024,get%1024);
text(txt,0,th);
free(txt);
REF;
}

void game_kz()
{
 switch(j)
{ case 1:
 walk();break;
 case 2:dou();break;
}

}

void walk()
{
 cls(255,255,255);
 bmp_person();
 REF;
}

void dou()
{
 cls(255,255,255);
 char *txt=malloc(20);
 sprintf(txt,"Ѫ��:%d",Cr->HP);
 dtext(txt,0,SCRH-th*2,0,0,0,FALSE,FONT);
 sprintf(txt,"ħ��:%d",Cr->MP);
 dtext(txt,SCRH-th,0,0,0,FALSE,FONT);
 free(txt);
 bmpshowflip(person,0,SCRH-th*2-125,100,100,125,BM_COPY,0,0,0);
 bmpshowflip(guai,SCRW-100,th*2,100,100,125,BM_COPY,0,0,0);
 REF;
}