#include <base.h>

int init(void)
{
 main();
 return 0;
}

int event(int type, int p1, int p2)
{
 if(KY_DOWN==type)
 {
 switch(p1)
  {
  case _SRIGHT:
  exit();
  break;
  }
 }

 return 0;
}

int pause(void)
{
 return 0;
}

int resume(void)
{
 return 0;
}


int main()
{
	/*(x,y)��ʾ��������Ļ�ϵĳ�ʼλ��,
	depth��ʾ������غ󷴵��ĸ߶�,
	times��������ʱ����ӳ�,
	m���������˶��ķ���m=-1˵���������˶���m=1˵���������˶�*/
	int x=SCRW/2,y=4,depth=10,times=20,m=1,i,j;
	
for(;depth!=0;) 
	{
		m=-m;
		if(m==1)
			depth--; 
		for(i=1;i<=depth;i++) 
		{
			
			/*��������ͼ��*/ /* 		gotoxy(x,y);
		 printf("***\n");
		 gotoxy(x,y+1);
		 printf("|*|\n");
 gotoxy(x,y+2);
  	printf("***");
*/
cls(0,0,0);
drect(x,y,10,10,255,250,0);
ref(0,0,SCRW,SCRH);
			
/*���Ʋ�ͬ���ӳ���ʾ��ʱ���С
			for(j=1;j<=times;j++) 
					delay(10);
  
			cls(0,0,0); 
*/			

if(m==-1)
			{
				/*���������˶�*/
				y++;  
				/*��ʱԽ��ԽС��˵���ٶ�Խ��Խ��*/
				times--;
			}
			else
			{
				/*���������˶�*/
				y--;
				/*��ʱԽ��Խ��˵���ٶ�Խ��Խ����˵����*/
				times++; 
			}    
		} 
	} 
	 //getch();
	 return 0;
} 