#include "c2/spz/print.h"
#include "c2/spz/xcpfr.h"
#include "c2/spz/edit.h"
char *st;
int qt;

int init(void)
{
cls(50,200,100);
refall();
rst.x=30;
print("������
������:���
Q:���������������ľ�",3000);
rst.x=20;
print("�ף�����ϸ�Ķ���������",1000);
print("���ѽ��༭������ģʽ��*�������������������������ʽ��֧�ּ򵥵����������������ţ�����������֧��С�������Գ�����ȡ��",5000);
print("�ǲ��Ǿ����Һ�luosuo�����������������ǣ����ˣ��۲�����",2000);
print("���ˣ�����˵�������ֻ�Ǹ���ҿ�������������ʲôʵ�ʼ�ֵ",2500);
startedit(14,140,200,"Welcome");
return 0;
}

int event(int type, int p1, int p2)
{
    if(KY_DOWN == type)
    {
play(p1);
        switch(p1)
        {
        case _SLEFT:
if(qt==0)jg();
else if(qt==1){qt=0;
startedit(14,140,200,"Welcome");}
            break;
case _SRIGHT:
if(qt==1)exitApp();
break;
        case _1:
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

void jg()
{
char b[30];
st=endedit();
intowrxcp(st);
rst.x=50;
sprintf(b,"%s=%d",st,gbxcp());
print(b,2000);
print("����û��������",2000);
rst.x=0;
print("��                    ��",2000);
free(st);
qt=1;
}

int exitApp()
{
rst.x=50;
print("��������.......",3500);
if(st!=NULL)free(st);
if(ob!=NULL)free(ob);
exit();
return 0;
}