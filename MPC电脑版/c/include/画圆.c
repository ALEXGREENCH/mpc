//Ϊ��Բ������׼��
void CirPoint(int x0, int y0, int x1, int y1, int r, int g, int b)
{   
  dpointex(x0+x1, y0+y1, r, g, b);
  dpointex(x0+y1, y0+x1, r, g, b);
  dpointex(x0-y1, y0+x1, r, g, b);
  dpointex(x0-x1, y0+y1, r, g, b);
  dpointex(x0+y1, y0-x1, r, g, b);
  dpointex(x0+x1, y0-y1, r, g, b);
  dpointex(x0-x1, y0-y1, r, g, b);
  dpointex(x0-y1, y0-x1, r, g, b);
}

//��Բ����(ժ��Ĭˮƿ). x0,y0Ϊ����,r0Ϊ�뾶,r,g,bΪ��ɫ
void circle(int x0,int y0,int r0,int r,int g,int b)
{   
  int d,x,y;
  d = 1 - r0;
  x = 0;
  y = r0;
  CirPoint(x0, y0, x, y, r, g, b);
  while(y>x)
   {
    if(d<=0)
     d += 2 * x + 3;
    else 
     d += 2 * (x - y--);

    x++;
    CirPoint(x0, y0, x, y, r, g, b);
   }
}
