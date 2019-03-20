/*���ڲ�������*/


/*
*����һ������
*����
 id ����id
 x,y,w,h ����λ��
*����:
 !=NULL  ���ھ��
 NULL ʧ��
*/
void* winCreate(uint16 id,uint16 x,uint16 y,uint16 w,uint16 h)
{
 window *pWin;
 pWin=malloc(sizeof(window));
 memset(pWin,0,sizeof(window));
 pWin->id=id;
 pWin->rect.x=x;
 pWin->rect.y=y;
 pWin->rect.w=w;
 pWin->rect.h=h;
 
 winEvent(pWin,WIN_CREATE,0,0);
 return pWin;
}


/*
* ���ô�����ʽ
* ����:
 pWin ���ھ��
 rgb��rgb2 ������ʽ
*/
void winSet(window *pWin,colorst *rgb,colorst *rgb2)
{
 win_ui *ui;
 ui=malloc(sizeof(win_ui));
 memset(ui,0,sizeof(win_ui));
 pWin->ui=ui;
 ui->rgb=*rgb;
 ui->rgb2=*rgb2;
}

/*
* ��ʾ����
* ����
 pWin ���ھ��
*/
void winShow(window *pWin)
{
 rectst r;
 colorst c;
 win_ui *ui=pWin->ui;
 r=pWin->rect;
 c=ui->rgb2;
 drect(r.x,r.y,r.w,r.h,c.r,c.g,c.b);
 c=ui->rgb;
 drect(r.x+3,r.y+3,r.w-6,r.h-6,c.r,c.g,c.b);
 winEvent(pWin,WIN_SHOW,0,0);
 ref(r.x,r.y,r.w,r.h);
 return ;
}

/*
* ��ʾ���д���
* ����:
 first ���ڿ�ͷָ��
*/
/*void winShowAll(win_obj* p)
{
 while(!p){
 winShow(!first);
 {
 winShow(p->now);
 p=p->next;
 }

}
*/

/*
* ���ٴ���
* ����
 pWin ���ھ��
*/
void winDel(window *pWin)
{
 winEvent(pWin,WIN_DESTROY,0,0);
 free(pWin->ui);
 free(pWin);
}
