/*�궨��*/

/*MRPϵͳ��������ֵ*/
#define OK 0 //�ɹ�
#define BAD -1 //ʧ��
#define IGNORE 1 //������
#define WAIT 2 //�첽(������)

//����
typedef struct
{
 uint16 x;
 uint16 y;
}Wxy;

typedef struct
{
 void *first;
 void *last;
 void *now;
}win_p;

//��ʽָ��
typedef struct
{
 void *prev; //ǰһ��
 void *next; //��һ��
}win_obj;

//����UI����
typedef struct
{
 colorst rgb; //��ɫ
 uint8 w; //�߿���
}focus_ui;


//����UI����
typedef struct
{
 colorst rgb; //������ɫ
 colorst rgb2; //�߿���ɫ
}win_ui;

//����
typedef struct WINDOW
{
 uint16 id; //����id
 rectst rect; //����λ�úʹ�С
 win_ui *ui; //����ui
 win_p point;//�ӿؼ���ʽָ��
}window;

//�����¼�(ö��)
enum
{
 WIN_CREATE, //������
 WIN_DESTROY, //��������
 WIN_SHOW, //����ʾ
 WIN_HIDE, //��������
 WIN_OVERD, //��������
 WIN_FOCUS, //��ý���
 WIN_NOFOCUS, //��ʧȥ����
 WIN_CLICK //�����
};

window *winNow;//��ǰ����ָ��
