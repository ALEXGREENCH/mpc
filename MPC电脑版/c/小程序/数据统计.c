/*
����ͳ��
by:ԾȻ
QQ:643552878
2012.5.12
*/

#include <base.h>
#define S 100 
//������ķ�Χ0-S

#define m 100
//���ݵĸ���
#define n1 10
#define n2 20
//Ҫͳ�����ķ�Χn1~n2(������n2)

int init()
{
 int s1[m],s2[n2],i;

 for(i=0;i<m;i++)
{ 
 //���������
 printf("%d-",s1[i]=rand()%S);
 if((i+1)%5==0)printf("\n");
 //ÿ5������

 if(s1[i]<n2)
 { if(s1[i]>=n1)
  s2[s1[i]]++;
 }
 //ͳ�ƹؼ����룡


}

 printf("\n����ͳ��:\n");


//���ͳ�ƽ��
 for(i=n1;i<n2;i++)
{
 printf("_%d-%d��_",i,s2[i]);
 if((i+1)%3==0)
 printf("\n");
 //ÿ3����
}
 exit();
 return 0;

}

int event(int type, int p1, int p2)
{
    if(KY_DOWN == type)
    {
        switch(p1)
        {
        case _SRIGHT:
            exit();
            break;
        case _1:
            break;
        }
    }

    return 0;
}

int pause(void)
{return 0;}
int resume(void)
{return 0;}