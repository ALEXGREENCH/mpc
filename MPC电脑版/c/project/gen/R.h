//��ͨ�����ṹ��
typedef struct
{
  int Win;
}BOL; BOL R;

//�¼�������ֵ����ȡ��ֵʱwinΪ -1
int win_r(int win)
{
if(win != -1)R.Win = win;
return (R.Win);
}