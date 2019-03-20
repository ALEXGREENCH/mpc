#ifndef BUTTON_H
#define BUTTON_H
//��������(6369)
//2012-7-17


#define BUTTONFOCUSCLR 0x0055ff
#define BUTTON

typedef struct
{
int x;int y;int w;int h;
int32 upclr;
int32 downclr;
int32 titclr;
char* title;
int is_getfocus;
}Button,*PButton;

/*������Ŧ*/

PButton buttonCreate(int x,int y,int w,int h,int32 upclr,int32 downclr,int32 titclr,char* title);



/*ɾ����ť*/

void buttonDel(PButton a);



/*���ð�Ŧ�õ�����*/
void setButtonFocus(PButton a);


/*���ð�Ŧʧȥ����*/
void setButtonClearFocus(PButton a);


/*��ť��ý���*/

void buttonGetFocus(PButton a);



/*��ť������*/
void buttonClick(PButton a);



/*��ť���ͷ�*/
void buttonReleace(PButton a);


/*���ư�ť*/
void drawButton(PButton a);


#endif
