#define FONT 1

//ÿ�����ӿ��
#define WLEN 15

//ÿ�����Ӹ߶�
#define HLEN 15


int tw,th;
textwh("��",FALSE,FONT,&tw,&th);


uint16 WN=SCRW/WLEN,HN=(SCRH/HLEN);


uint16 *scr=getscrbuf();


uint16
*BmpWall,//ǽ
*BmpFloor,//�ذ�
*BmpBomb,//ը��
*BmpMan,//��
*BmpMonster;//��

enum
{
 IS_WALL,
 IS_FLOOR,
 IS_BOMB,
 IS_MAN,
 IS_MONSTER
};


void BmpStart()
{
BmpWall=OpenBmpFile("c/ը������/BMP/wall.bmp");
  BmpFloor=OpenBmpFile("c/ը������/BMP/floor.bmp");
 BmpBomb=OpenBmpFile("c/ը������/BMP/bomb.bmp");
}

void BmpFree()
{
 free(BmpWall);
 free(BmpFloor);
 free(BmpBomb);
}

void* OpenBmpFile(char *filename)
{
 int32 f;
 int32 bmplen;
 bmplen=getlen(filename);
 f=open(filename,1);
 uint16 *tu=malloc(bmplen);
 read(f,tu,bmplen);
 close(f);
 return tu;
}

void DrawMap()
{
 ShowMsg("���Ƶ�ͼ�С�");
 cls(255,255,255);

 uint16 x,y;
 for(x=0;x<=WN;x++)
 for(y=0;y<=HN;y++)
 {
 uint8 k=rand()%3+1;
 if(k==1)
 DrawBmp(IS_WALL,x*WLEN,y*HLEN);
 else if(k==2)
 DrawBmp(IS_FLOOR,x*WLEN,y*HLEN);
 else DrawBmp(IS_BOMB,x*WLEN,y*HLEN);
 ref(x*WLEN,y*HLEN,WLEN,HLEN);
 }
 ref(0,0,SCRW,SCRH);
}





void DrawBmp(uint8 kind,uint16 x,uint16 y)
{
 uint16 *bmp;
 switch(kind)
 {
  case IS_WALL:
  bmp=BmpWall;break;
  case IS_FLOOR:
  bmp=BmpFloor;break;
  case IS_BOMB:
  bmp=BmpBomb;break;
  case IS_MAN:

  case IS_MONSTER:
  break;
 }
 bmpshowflip(bmp,x,y,WLEN,WLEN,HLEN,BM_TRANS,0,0,0xFF);

}