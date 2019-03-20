#include <base.h>
#include <c/��ȭ/day.h>

uint8 l,/*��ǰ����*/
z,/*���Ӯ�ľ���*/
fen;/*��ҷ���*/

uint8 kindA,/*���Է���ȭ����*/
kindB;/*��ҳ�ȭ����*/

/*��ȭ����*/
enum
{ stone=1,/*ʯͷ=1*/
 scissor,/*����=2*/
 paper/*��=3*/
};
char *Lei[3]={"ʯͷ","����","��"};


int j=-1;
/*
-1���ڽ���
0��ȭ�������
1������
2�������
*/

int init()
{
 about();

 printf("ʯͷ=%d,����=%d,��=%d\n\n",stone,scissor,paper);

 return 0;
}
void inits()
{
 if(l)printfAll();
 printf("\n��ʼ��\n");

 int h2=SCRH/2;
 drect(0,h2,SCRW,th,255,250,250);
 drect(1,h2+1,SCRW-2,th-2,0,0,0);
 text("��ʼ��",(SCRW-tw*2)/2,h2,55,255,255);
 REF;sleep(800);
 l=z=fen=0;
 kindA=kindB=0;
 dawMain();
}

int event(int type, int p1, int p2)
{
if(type==KY_UP)
{
 if(j<0)
 {j=1;inits();}

 else if(j==0)
 {j=1;dawMain();}

 else if(j==1)
 switch(p1)
  {
  case _SRIGHT:
  exitapp();break;
  case _0:inits();break;


  case _1:
    do{kindA=rand()%3;}
  while(kindA==0);

  dawA();REF;
  break;

 case _SLEFT:
 j=2;dawScanf();  break;

 case _SELECT:
 if(kindA&&kindB)
 dawWin();break;

 }

 else if(j==2)
 { if(p1>0&&p1<4)
  { kindB=p1;
  dawScanf();
  }
  else if(p1==_SLEFT)
  {j=1;dawMain();}
  else if(p1==_SRIGHT)
 {j=1;kindB=0;dawMain();}

 }

  }
 return 0;
}

int pause(void)
{return 0;}
int resume(void)
{return 0;}

void printfAll()
{
 printf("\n\n��Ϸ����:\n�ܹ�%d��,��Ӯ��%d��,����%d",l,z,fen);
}
void exitapp()
{ dawExit();
 exit();
}


void dawMain()
{
 int h=SCRH-th;
 cls(100,250,250);
 drect(0,0,SCRW,th,150,200,200);
 drect(0,h,SCRW,th,150,200,200);
 text("MPC����ȭ",(SCRW-tw*5)/2,0,255,0,25);
 text("��ȭ",0,h,255,255,0);
 text("�˳�",SCRW-tw*2,h,255,0,0);
 text("���",SCRW/2-tw,h,255,25,255);
 dawA();
 dawB();
 dawText();

 REF;
}

/*����Գ�ȭ״̬ͼ*/
void dawA()
{
 char *txt;
 txt=(kindA?"����:�ѳ�":"����:δ��");
 drect(tw,th*3,SCRW,th,100,250,250);
 text(txt,tw,th*3,150,50,50);
}

/*����ҳ�ȭ״̬*/
void dawB()
{
 drect(tw,th*5,SCRW,th,100,250,250);
 text("���:",tw,th*5,150,150,25);
 if(kindB)
 text(Lei[kindB-1],tw*3+5,th*5,150,50,50);
else text("δ��",tw*3+5,th*5,150,50,50);
}

void dawText()
{
 printf_d("��ǰ:��%d��",l,tw,SCRH-th*5,55,55,55);
 printf_d("��ʤ:%d��",z,tw,SCRH-th*4,55,55,55);
 printf_d("����:%d",fen,tw,SCRH-th*3,55,55,55);
}


/*�ж���Ӯ����������*/
void dawWin()
{
 int a;
/*ȡֵ:
-1 ����Ӯ
0  ƽ��
1  ���Ӯ
*/
 if(kindA==kindB)a=0;
 
 else if(kindA==stone)
 { if(kindB==scissor)a=-1;
  else a=1;
 }
 else if(kindA==scissor)
 {if(kindB==stone)a=1;
  else a=-1;
 }
 else if(kindA==paper)
 {if(kindB==stone)a=-1;
  else a=1;
 }

 int h2=SCRH/2;
 effsetcon(0,h2,SCRW,th*3,128,128,128);

 char *s1,*s2,*s3,*s4,*s5;
 s1=Lei[kindA-1];
 s2=Lei[kindB-1];

 if(a==-1)s3="����ʤ��";
 else if(a==0)s3="ƽ�֣�";
 else if(a)s3="���ʤ";

 s4="���:%s,���Գ�:%s\n���:%s\n�����������";

 s5=malloc(strlen(s1)+strlen(s2)+strlen(s3)+strlen(s4));
 sprintf(s5,s4,s2,s1,s3);
 rect_text(s5,0,h2,SCRW,SCRH,255,255,255);

 printf("��%d��:\n%s\n\n",++l,s5);
 free(s5);
 h2+=th*3;

 for(int y=SCRH/2;y<=h2;y+=5)
 ref(0,y,SCRW,5);
 REF;

 if(a)
 {z++;fen++;}
  kindA=kindB=0;
 j=0;

}


/*��ҳ�ȭͼ*/
void dawScanf()
{
 int h2=SCRH/2;
 drect(0,h2,SCRW,th*3,55,55,55);

 rect_text("��1~3�ֱ�Ϊʯͷ����������\n��ѡ��:",0,h2,SCRW,SCRH,255,255,255);
 char *s;
 if(kindB!=NULL)
 {s=Lei[kindB-1];
 text(s,tw*4,h2+th*2,255,255,0);
 }
 h2+=th*4;
 for(int y=SCRH/2;y<=h2;y+=5)
 ref(0,y,SCRW,5);
 REF;
}