//ջ,���ʽ������
#define max 50
int stack[max+1][3];

int put(int n)
{
if(stack[0][n]>0)return stack[stack[0][n]--][n];
else pt();
}

int get(int n)
{
if(stack[max][n]<=stack[0][n])return stack[stack[max][n]++][n];
else pt();
}

int push(int k,int n)
{
if(stack[0][n]<max){
stack[++stack[0][n]][n]=k;
return 0;}
else pt();
}

void pt()
{
rst.x=20;
print("���ݳ������⣬���������ڱ��ʽ�������ڱ����쳣���裬ͬʱΪ�˷�������12���ǿ���˳�������ټ����ʽ",4000);
print(st,6000);   
print("��ӭʹ�ã���",2500);
exitApp();
}