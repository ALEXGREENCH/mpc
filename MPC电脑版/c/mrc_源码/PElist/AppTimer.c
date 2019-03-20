/*
 * ����ʱ��������
 * ��Ȩ���� (C) 2011-2012 DeepBlue
 * [4/8/2012]
 */

#include <mrc_base.h>
#include "nv_ui.h"
#include "AppTimer.h"

#include "MDskin.h"
#define Apptext "MDplore"

static int32 KeyTimerHandleA = 0;  
static colorct nv_timerColor,nv_timerColorFont;

// ʱ��ˢ����UI
static void nv_timeD(int32 data)
{
	char buf[30]={0};
	int used=0,left=0,rused=0,rleft=0;	
	int32 w=0,h=0;

	mr_datetime  t_dt;
	mrc_getDatetime(&t_dt);

	rectJG(0,0,mspw,14,nv_timerColor);

	if(mspw >= 240)
		txtJG(Apptext,3,1,nv_timerColorFont);

	mrc_getMemStatus(&used,&left,0,0,&rused,&rleft);

	if(t_dt.hour<3)
		mrc_sprintf(buf,"�賿%d:%d",t_dt.hour,t_dt.minute);
	else if(t_dt.hour<7)
		mrc_sprintf(buf,"�峿%d:%d",t_dt.hour,t_dt.minute);
	else if(t_dt.hour<11)
		mrc_sprintf(buf,"����%d:%d",t_dt.hour,t_dt.minute);
	else if(t_dt.hour==12)
		mrc_sprintf(buf,"����%d:%d",t_dt.hour,t_dt.minute);
	else if(t_dt.hour<17)
		mrc_sprintf(buf,"����%d:%d",t_dt.hour-12,t_dt.minute);
	else if(t_dt.hour<19)
		mrc_sprintf(buf,"�ƻ�%d:%d",t_dt.hour-12,t_dt.minute);
	else if(t_dt.hour<=22)
		mrc_sprintf(buf,"����%d:%d",t_dt.hour-12,t_dt.minute);
	else
		mrc_sprintf(buf,"��ҹ%d:%d",t_dt.hour-12,t_dt.minute);

	txtwh(buf,&w,&h);

	if(mspw >= 240)
		txtJG(buf,(int16)(mspw/2-w/2),1,nv_timerColorFont);
	else
		txtJG(buf,3,1,nv_timerColorFont);

	mrc_sprintf(buf,"%d!%dk",left/1024,(left+used)/1024);
	txtwh(buf,&w,&h);
	txtJG(buf,(int16)(mspw-w-3),1,nv_timerColorFont);

	mrc_refreshScreen(0,0,mspw,14);
}

// ʱ������ʼ��
void AppTimerReDo()
{
    KeyTimerHandleA = mrc_timerCreate();

	nv_timerColor = MDskin_Getcolor("��������");
	nv_timerColorFont = MDskin_Getcolor("��������");

    mrc_timerStart(KeyTimerHandleA, 1200, 0, (mrc_timerCB)nv_timeD, 1);
	nv_timeD(0);
}

// �ָ�/����
void AppTimerStart()
{
    AppTimerStop();

    KeyTimerHandleA = mrc_timerCreate();
    mrc_timerStart(KeyTimerHandleA, 1200, 0, (mrc_timerCB)nv_timeD, 1);
	nv_timeD(0);
}

// ��ͣ/ɾ��
void AppTimerStop(void)
{
    if (KeyTimerHandleA != 0)
    {
        mrc_timerStop(KeyTimerHandleA);
        mrc_timerDelete(KeyTimerHandleA);
        KeyTimerHandleA = 0;
    }
}
