/*
�ж���Ӯ����
��8���������Ƿ���5������
*/

int win()
{
 uint8 c[8],i;
 memset(c,NULL,8*sizeof(uint8));
 int x=Move->x,y=Move->y;

//1.���ϼ��
 for(i=0;i<4;i++)
{
  if(y-i==0)break;
  if(Q[x][y-i]==Q[x][y-i-1])
 c[0]++;
 else break;
}
 if(c[0]==4) return 1;
 
//2.���¼��
 for(i=0;i<4;i++)
{ 
 if(y+i==H)break;
 if(Q[x][y+i]==Q[x][y+i+1])
 c[1]++;
 else break;
}
 if(c[1]==4) return 1;

//3.������ 
 for(i=0;i<4;i++)
 {
 if(x-i==0)break;
 if(Q[x-i][y]==Q[x-i-1][y])
 c[2]++;
 else break;

}
 if(c[2]==4)return 1;

//4.���Ҽ��
 for(i=0;i<4;i++)
{ 
 if(x+i==W)break;
 if(Q[x+i][y]==Q[x+i+1][y])
 c[3]++;
 else break;
}
 if(c[3]==4)return 1;


//5.���ϼ��
 for(i=0;i<4;i++)
{
 if((x-i==0)||(y-i==0))
 break;
 if(Q[x-i][y-i]==Q[x-i-1][y-i-1])
 c[4]++;
 else break;
}
if(c[4]==4)return 1;


//6.���ϼ��
for(i=0;i<4;i++)
{
 if((x+i==W)||(y-i==0))
 break;

 if(Q[x+i][y-i]==Q[x+i+1][y-i-1])
 c[5]++;
 else break;
}
if(c[5]==4)return 1;


//7.���¼��
for(i=0;i<4;i++)
{
 if((x-i==0)||(y+i==H))
 break;
 if(Q[x-i][y+i]==Q[x-i-1][y+i+1])
 c[6]++;
 else break;
}
if(c[6]==4)return 1;


//8.���¼��
for(i=0;i<4;i++)
{
 if((x+i==W)||(y+i==H))
 break;
 if(Q[x+i][y+i]==Q[x+i+1][y+i+1])
 c[7]++;
 else break;
}
if(c[7]==4)return 1;
 switch(4)
 {
  case c[0]+c[1]:
  case c[2]+c[3]:
  case c[4]+c[5]:
  case c[6]+c[7]:
  return 1;
  break;
 }
 return 0;

}
//by:ÿ�����һ��