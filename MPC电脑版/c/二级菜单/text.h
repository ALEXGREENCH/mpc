void rect_text(char *text)
{
cls(BR,BG,BB);

rectst rect; 
colorst color;
rect.x=0;
rect.y=th;
rect.w=SCRW;
rect.h=SCRH;

color.r=R;
color.g=G;
color.b=B;
bmp(1);bmp(2);

dtextex(text,rect.x,rect.y,&rect,&color,2,1);

}


void about()
{rect_text("�༶�˵�ʾ��
by:�����>ÿ�����һ��>��д
����ɳܣ���֧��ԭ���ߣ�

����֧���������Ķ�����
����:abook.yy.ai
>>>>>>>>>>
");
text("����",tw,0);
text("����",SCRW-tw*2,SCRH-th);
REF;
}

void help()
{
rect_text("
����ʡ��

����Ͳ��ý����˰ɣ�
>>>>>>>>>>>");
text("����",tw,0);
text("����",SCRW-tw*2,SCRH-th);
REF;
}



void nono()
{
rect_text("��ѧ��̵�·�ϲ�����������ۣ�
��Ҫ���ġ���Ҫɥ����
ÿ�����ֶ���һ�����߹����ģ�
�������߷�һ��������");
text("����>>>",tw,0);
text("����",SCRW-tw*2,SCRH-th);
REF;
}



//ˢ����ʱ������
int32 cls_timer=timercreate();

void CLS(int data)
{sand(getuptime());
drect(0,0,SCRW,SCRH,rand()%255,rand()%255,rand()%255);
bmp(1);bmp(2);
text("ˢ��",tw,0);
text("����",SCRW-tw*2,SCRH-th);

text("��",rand()%SCRW,rand()%(SCRH-th)+th);
REF;

}


void wu()
{
cls(BR,BG,BB);
bmp(1);bmp(2);
rect_text("\n\n\n\n��Ϊ��ӣ����Լ���ӣ�\n<<<<<<");
text("����",SCRW-tw*2,SCRH-th);
REF;

}