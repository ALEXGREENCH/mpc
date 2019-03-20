/*�궨��*/
#define OK 0
#define BAD -1
#define IGNORE 1
#define WAIT 2


/*Window ����*/

//����
typedef struct
{
int16 x;int16 y;
} wxy;

//ָ��ؼ���ָ��
typedef struct
{
void *first;
void *last;
void *now;
} wwindowp;

//�ؼ�����ʽָ��
typedef struct
{
void *before;
void *next;
} wobjp;

//����UI����
typedef struct
{
colorst rgb;
uint8 w;
} wfocusui;

//����UI����
typedef struct
{
colorst rgb;
colorst rgb2;
} wwindowui;

//��ťUI����
typedef struct
{
colorst rgb;
colorst rgb2;
char *title;
colorst titrgb;
} wbuttonui;

//����
typedef struct wwindow
{
uint16 id;
uint8 type;
rectst locat;
wwindowui *ui;
wwindowp point;
} wwindow;

//�ؼ�
typedef struct
{
uint16 id;
uint8 type;
rectst locat;
void *ui;
wobjp point;
} wobj;

//�ؼ�����
enum
{
WNONE,
WWINDOW,
WBUTTON
};

//���ںͿؼ��¼�
enum
{
WECREATE, //������
WEDESTROY, //��������
WESHOW, //����ʾ
WEHIDE, //��������
WEOVERD, //��������
WEFOCUS, //��ý���
WENOFOCUS, //��ʧȥ����
WECLICK //�����
};

/*ȫ�ֱ���*/
wwindow *wnowwindow; //��ǰ����ָ��
wobj *wnowobj; //��ǰ�ؼ�ָ��
wfocusui wfocus; //����UI
