
/*
* ��colorst�ṹ��Աֵ��ֵ
* ����:
 rgb �ṹָ��
 r,g,b ֵ
*����:
 �ṹ��ָ��
*/
void* rgbSet(colorst *rgb,uint8 r,uint8 g,uint8 b)
{
 rgb->r=r;
 rgb->g=g;
 rgb->b=b;
 return rgb;
}

/*
* �������
* ����:
 mr ����
 mm  ���������
�����Ҫ����50�ֽ�
*/
void echo(char *nr,int mm)
{
 char *ww;
 static int ty=240;
 ww="012345678901234567890123456789012345678901234567890";
sprintf(ww,"%s:%d",nr,mm);
if(ty+20>SCRH)
 {
 ty=SCRH;
 drect(0,ty,SCRW,80,0,0,0);
 ref(0,ty,SCRW,80);
 }
 drect(0,ty,SCRW,20,0,0,0);
 dtext(ww,0,ty,255,255,255,0,1);
 ref(0,ty,SCRW,25);
 ty+=25;
}