/*
 * ����������
 * ��Ȩ���� (C) 2011-2012 eleqian
 * [4/8/2012]
 */

#include <mrc_base.h>

#include "KeyTimer.h"

static int32 KeyTimerHandle = 0;  // ������ʱ��
static mrc_timerCB KeyTimerCB;    // �����ص�

// ��ס����
static void KeyTimerReDo(int32 data)
{
    mrc_timerStop(KeyTimerHandle);
    mrc_timerStart(KeyTimerHandle, 60, data, KeyTimerCB, 1);
}

// ��ʼ������ʱ(���°���)
void KeyTimerStart(int32 data, mrc_timerCB timercb)
{
    KeyTimerStop();

    KeyTimerCB = timercb;
    KeyTimerHandle = mrc_timerCreate();
    mrc_timerStart(KeyTimerHandle, 220, data, KeyTimerReDo, 0);
    KeyTimerCB(data);
}

// ����������ʱ(̧�𰴼�)
void KeyTimerStop(void)
{
    if (KeyTimerHandle != 0)
    {
        mrc_timerStop(KeyTimerHandle);
        mrc_timerDelete(KeyTimerHandle);
        KeyTimerHandle = 0;
    }
}
