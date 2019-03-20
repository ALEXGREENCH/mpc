/*
 * ��������Ĵ��� v1.0
 * Revise frequency: 0003
 * ��Ȩ���� (C) 2012-2012 DeepBlue
 * [6/8/2012]
 */

#include <mrc_base.h>
#include <mrc_base_i.h>
#include <mrc_exb.h>
#include <mrc_bmp.h>

#include "AppTimer.h"
#include "KeyTimer.h"
#include "nv_base.h"
#include "nv_ui.h"
#include "FileType.h"
#include "String.h"
#include "Functions.h"
#include "AppSmallwin.h"
#include "MDskin.h"
//#include "PictureSee.h"

#include "AppMain.h"

#define namelen   100 // �ļ�����󳤶�
#define lunamelen 300 // ����·����󳤶�

// �ļ����ݽṹ��
typedef struct
{
	char *name; // �ļ���
	int num;    // �ļ����� �μ� FileType.h
	int shear;  // 0:���� 1:ѡ��
}ini;

// �ڵ����ݽṹ��
typedef struct LIST
{
	ini news;          // ������Ϣ
	struct LIST *last; // ��һ�ڵ�
	struct LIST *next; // ��һ�ڵ�
}lists,*plist;

// �ļ���������ݽṹ��
typedef struct
{
	char luname[lunamelen]; // ����·��
	int winnu;              // �ѽ��ļ�����Ŀ
	int pagey;              // �б���λ��
	int32 pagety;           // �б�ͷλ��
	int32 number;           // ����������Ŀ
	int32 jlu[30][2];       // λ�����ݼ�¼
	plist dirhead;          // �ļ���ͷ����
	plist filehead;         // �ļ�ͷ����
	plist pagehead;         // �б���ʾͷ�ڵ�
	plist pagenum;          // ������ʾ�ڵ�
}ini_view;

// �������������ݽṹ��
typedef struct
{
	int xzAll;     // ѡ��ȫ��
	int duplicate; // 1.���� 2.����
}xz_view;

// �������������ݽṹ��
typedef struct
{
	int32 downy; // y����
	int32 upy;   // y�ŵ�
	int32 downx; // x����
	int32 upx;   // x�ŵ�
}mouse_view;

// �������ɫ�ṹ
typedef struct
{
	// ·������ɫ
	colorct waybackground;        // ����ɫ
	colorct wayfont;              // ����ɫ
	// �б���ɫ
	colorct listbackground;       // ����ɫ
	colorct listfont;             // ����ɫ
	colorct listfocusbackground;  // ���㱳��
	colorct listfocusfont;        // ��������ɫ
	colorct listfocusfilenumfont; // �����ļ���ɫ
	colorct listline;             // �б������ɫ
}colort_view_M;

static ini_view vies;        // �ļ����������
static colort_view_M viesco; // �ļ��������ɫ����
static mouse_view viet;      // ����������:��ʱδ����
static xz_view vier;         // ѡ���Ƽ�����
static int32 windownu=0;     // ����id

/*---------------------------------------------------------------------------*/

// ѡ��ȫ��
static void filexzAll()
{
	int32 nuk=0,w=0,h=0;
	char nau[50]={0};
	plist p=vies.dirhead->next;

	while(p != NULL)
	{
		if(vier.xzAll == 0)
			p->news.shear=1;
		else
			p->news.shear=0;
		p=p->next;
		nuk++;
	}
	if(vier.xzAll == 0)
		vier.xzAll=1,mrc_sprintf(nau,"��ѡ��%d���ļ�/�ļ���!",nuk);
	else
		vier.xzAll=0,mrc_sprintf(nau,"���ѡ��%d���ļ�/�ļ���!",nuk);

	txtwh(nau,&w,&h);
	svrect(mspw/2-(int16)w/2-14,msph-50,(int16)w+28,(int16)h+6+8,255,255,255,240,240,240,4);
	rectJG(mspw/2-(int16)w/2-10,msph-46,(int16)w+20,(int16)h+6,viesco.waybackground);
	txtJG(nau,mspw/2-(int16)w/2,msph-50+7,viesco.listfocusfont);
	fresh();

	mrc_sleep(450);
	FileViewBrowser_UI();
}

/*---------------------------------------------------------------------------*/

// ����Loading
static void FileViewBrowser_TrendsWin(void)
{
	int32 w=0,h=0;
	char nau[30]={0};

	mrc_sprintf(nau,">%d",vies.number);

	txtwh(nau,&w,&h);

	rectJG(0,14,mspw,18,viesco.waybackground);
	txtJG("��������������",3,16,viesco.wayfont);
	txtJG(nau,(int16)(mspw-w-5),16,viesco.wayfont);

	mrc_refreshScreen(0,14,mspw,18);
#ifndef SDK_MOD
#else
	mrc_sleep(100); // Windows because so fast , inconvenient test
#endif
}

// ����Ŀ¼���벢����
static void FindView_Main(void)
{
	int32 fd=0, listlen=sizeof(lists);

	char buf[namelen]={0}, *ptet=NULL;
	char path[lunamelen]={0};

	plist p=NULL, q=NULL, t=NULL;

	// ���������ͷ
	if(vies.dirhead == NULL)
	{
		// ��ʼ���ļ�������ͷ
		vies.dirhead=(plist)mrc_malloc(listlen);
		mrc_memset(vies.dirhead,0,listlen);

		vies.dirhead->last=NULL;
		vies.dirhead->next=NULL;

		// ��ʼ���ļ�����ͷ
		vies.filehead=(plist)mrc_malloc(listlen);
		mrc_memset(vies.filehead,0,listlen);

		vies.filehead->last=NULL;
		vies.filehead->next=NULL;
	}

	q=vies.dirhead,t=vies.filehead;

    //���ҵ�һ��
	fd=mrc_findStart(vies.luname,buf,namelen);
	if(fd>0)
	{
		do
		{
			// ��� buf �� "." �� ".." ������Ч
			if(mrc_strcmp(buf,".") != 0 && mrc_strcmp(buf,"..") != 0)
			{
				// �ϳ�����·��,��ȡ����
				mrc_sprintf(path,"%s/%s",vies.luname,buf);

				// ����ڵ��ڴ�
				p=(plist)mrc_malloc(listlen);
				mrc_memset(p,0,listlen);
				// ��ȡ�ļ���
				p->news.name=strdup(buf);

				// ������ļ���
				if(mrc_fileState(path) == MR_IS_DIR)
				{	
					q->next=p;    // �ļ����������һ��ָ�� p
					p->last=q;    // p ָ���ļ����������һ��
					p->next=NULL; // p ����һ��ָ�� NULL
					q=q->next;    // �ļ�����βָ����һ��
				}
				else
				{ 
					// ��ȡ��׺
					ptet=mrc_strrchr(path,'.');	 
					// ������׺�һ�ȡ�������
					p->news.num=typeanalyse(ptet); 

					t->next=p;    // �ļ��������һ��ָ�� p
					p->last=t;    // p ָ���ļ��������һ��
					p->next=NULL; // p ����һ��ָ�� NULL
					t=t->next;    // �ļ�����βָ����һ��
				}
				// ��¼������Ŀ
				vies.number++; 

				// 15��ˢ��һ��
                if (0 == vies.number % 15 && vies.number > 0) 
					FileViewBrowser_TrendsWin();
			}
            // ������һ��
			buf[0] = '\0';
		}
		while(mrc_findGetNext(fd,buf,namelen) == MR_SUCCESS);
	}
    // ��������
	mrc_findStop(fd);

	// ���������Ŀ����0,��ϲ�����
	if(vies.number > 0) 
		q->next=vies.filehead->next,vies.filehead->next->last=q;

	// ��ֵ������б�ͷ
	vies.pagehead = vies.pagenum = vies.dirhead->next;
}

// �ͷ������ڴ�,�ÿ�����
static void FileViewBrowser_Free(void)
{
	plist p=vies.dirhead,q=NULL;

	while(p!=NULL)
	{
		mrc_free(p->news.name);
		mrc_free(p);
		q=p->next;
		p=q;
	}
	mrc_free(vies.filehead);
	vies.dirhead=NULL;
	vies.filehead=NULL;
}

/*---------------------------------------------------------------------------*/

// ·����
static void FileViewBrowser_QUI(void)
{
	int32 w=0,h=0;
	char nau[70]={0};

	rectJG(0,14,mspw,18,viesco.waybackground);

	// �����·��
	if(mrc_strcmp(vies.luname,"")==0)
	{
		mrc_memcpy(nau,"��Ŀ¼",6);	
		txtJG(nau,4,16,viesco.wayfont);
	}
	else
	{
		// ��ʾ��ǰ·��
		txtJG(vies.luname,4,16,viesco.wayfont);
	}

	mrc_sprintf(nau,"%d/%d",vies.pagey+vies.pagety+1,vies.number);

	txtwh(nau,&w,&h);
	rectJG((int16)(mspw-2*w+4),14,(int16)(2*w)-4,18,viesco.waybackground);
	txtJG(nau,(int16)(mspw-w-4),16,viesco.wayfont);

	mrc_refreshScreen(0,14,mspw,18);
}

// �����б����
void FileViewBrowser_UI(void)
{
	int16 yi=0;
	int32 w=0,h=0,tw=0,th=0,pw=0,ph=0;
	char nau[30]={0},nau2[30]={0},path[lunamelen]={0};

	plist p=vies.pagehead;

	rectJG(0,32,mspw,msph-32,viesco.listbackground);

	mrc_sprintf(nau,"%d/%d",vies.pagey+vies.pagety+1,vies.number);

	txtwh(nau,&w,&h);
	rectJG((int16)(mspw-2*w+4),14,(int16)(2*w)-4,18,viesco.waybackground);
	txtJG(nau,(int16)(mspw-w-4),16,viesco.wayfont);

	// ����: p���ǿսڵ� �� ���ô�����ʾ��Ŀ
	while(p!=NULL && yi<=(msph-72)/40)
	{
		mrc_drawRect(0,72+yi*40,mspw,1,viesco.listbackground.r-10,viesco.listbackground.r-10,viesco.listbackground.r-10);
		mrc_drawRect(0,73+yi*40,mspw,1,viesco.listbackground.r+10,viesco.listbackground.r+10,viesco.listbackground.r+10);

		// ����ǽ���
		if(p==vies.pagenum)
		{
			//����
			mrc_EffSetCon(0,32+(int16)vies.pagey*40,mspw,40,viesco.listfocusbackground.r,viesco.listfocusbackground.g,viesco.listfocusbackground.b);
			//mrc_drawText(p->news.name,35,35+(yi++)*40,220,220,220,0,1);
			txtJG(p->news.name,35,40+(yi++)*40,viesco.listfocusfont);

			//����
			mrc_sprintf(nau2,"%s",typeanalysetxt(p->news.num));	
			txtwh(nau2,&tw,&th);
			txtJG(nau2,mspw-(int16)tw-10,44+(int16)th+(yi-1)*40,viesco.listfocusfilenumfont);

			// �ϳ�����·��,��ȡ��С
			mrc_sprintf(path,"%s/%s",vies.luname,p->news.name);
			if(mrc_fileState(path) == MR_IS_FILE)
			{
				mrc_sprintf(nau2,"��С:%d.%dKb",mrc_getLen(path)/1024,mrc_getLen(path)%1024);	
				txtwh(nau2,&pw,&ph);
				txtJG(nau2,mspw-(int16)(tw+pw)-15,44+(int16)(th+(th-ph))+(yi-1)*40,viesco.listfocusfilenumfont);
			}
		}
		else
		{
			//mrc_drawText(p->news.name,35,35+(yi++)*40,0,0,0,0,1);
			txtJG(p->news.name,35,40+(yi++)*40,viesco.listfont);
		}

		if(p->news.shear == 1)
			rectJG(0,32+(yi-1)*40,2,40,viesco.listline);

		// ��ʾͼ��
		MDtub(p->news.num,5,35+(yi-1)*40);

		// ָ����һ��
		p=p->next;
	}

	if(vies.number == 0)
	{
		mrc_sprintf(nau,"���ļ���,�뷵����һ��!");	
		txtwh(nau,&w,&h);
		svrect(mspw/2-(int16)w/2-14,msph-50,(int16)w+28,(int16)h+6+8,255,255,255,240,240,240,4);
		rectJG(mspw/2-(int16)w/2-10,msph-46,(int16)w+20,(int16)h+6,viesco.waybackground);
		txtJG(nau,mspw/2-(int16)w/2,msph-50+7,viesco.listfocusfont);
	}

	// ��Ӱ
	drect(0,32,mspw,4,150,150,150,255,255,255);

	// Move strip
	if(vies.number < (msph-72)/40)
		rectJG(mspw-3,37,1,msph-42,viesco.listline);
	else
		rectJG(mspw-3,37+(int16)vies.pagety/3,1,msph-42-(int16)vies.number/3,viesco.listline);

	mrc_refreshScreen(0,14,mspw,msph-14);
}

// �����ƶ����
static void FileViewBrowser_UIEx(int32 data)
{
	int32 tw=0,th=0,pw=0,ph=0;
	char nau[30]={0},path[lunamelen]={0};
	plist p=vies.pagenum;

	mrc_sprintf(nau,"%d/%d",vies.pagey+vies.pagety+1,vies.number);

	txtwh(nau,&pw,&ph);
	rectJG((int16)(mspw-2*pw+4),14,(int16)(2*pw)-4,18,viesco.waybackground);
	txtJG(nau,(int16)(mspw-pw-4),16,viesco.wayfont);

	//����
	mrc_EffSetCon(0,32+(int16)vies.pagey*40,mspw,40,viesco.listfocusbackground.r,viesco.listfocusbackground.g,viesco.listfocusbackground.b);
	//mrc_drawText(p->news.name,35,35+(yi++)*40,220,220,220,0,1);
	txtJG(p->news.name,35,40+(int16)vies.pagey*40,viesco.listfocusfont);

	//����
	mrc_sprintf(nau,"%s",typeanalysetxt(p->news.num));	
	txtwh(nau,&tw,&th);
	txtJG(nau,mspw-(int16)tw-10,44+(int16)th+(int16)vies.pagey*40,viesco.listfocusfilenumfont);

	// �ϳ�����·��,��ȡ��С
	mrc_sprintf(path,"%s/%s",vies.luname,p->news.name);
	if(mrc_fileState(path) == MR_IS_FILE)
	{
		mrc_sprintf(nau,"��С:%d.%dKb",mrc_getLen(path)/1024,mrc_getLen(path)%1024);	
		txtwh(nau,&pw,&ph);
		txtJG(nau,mspw-(int16)(tw+pw)-15,44+(int16)(th+(th-ph))+(int16)vies.pagey*40,viesco.listfocusfilenumfont);
	}

	if(p->news.shear == 1)
		rectJG(0,32+(int16)vies.pagey*40,2,40,viesco.listline);

	MDtub(p->news.num,5,35+(int16)vies.pagey*40);

	if(data == MR_KEY_DOWN)
	{
		//����
		rectJG((int16)(p->last->news.shear*2),32+(int16)(vies.pagey-1)*40,mspw,40,viesco.listbackground);

		mrc_drawRect((int16)(p->last->news.shear*2),32+(int16)(vies.pagey-1)*40,mspw,1,
			viesco.listbackground.r-10,viesco.listbackground.r-10,viesco.listbackground.r-10);
		mrc_drawRect((int16)(p->last->news.shear*2),33+(int16)(vies.pagey-1)*40,mspw,1,
			viesco.listbackground.r+10,viesco.listbackground.r+10,viesco.listbackground.r+10);

		//mrc_drawText(p->news.name,35,35+(yi++)*40,220,220,220,0,1);
		txtJG(p->last->news.name,35,40+(int16)(vies.pagey-1)*40,viesco.listfont);

		if(p->last->news.shear == 1)
			rectJG(0,32+(int16)(vies.pagey-1)*40,2,40,viesco.listline);

		MDtub(p->last->news.num,5,35+(int16)(vies.pagey-1)*40);

		// ��Ӱ
		if(vies.pagey == 1)
			drect(0,32,mspw,4,150,150,150,255,255,255);
	}
	else if(data == MR_KEY_UP)
	{
		//����
		rectJG((int16)(p->next->news.shear*2),32+(int16)(vies.pagey+1)*40,mspw,40,viesco.listbackground);
	
		mrc_drawRect((int16)(p->next->news.shear*2),32+(int16)(vies.pagey+2)*40,mspw,1,
			viesco.listbackground.r-10,viesco.listbackground.r-10,viesco.listbackground.r-10);
		mrc_drawRect((int16)(p->next->news.shear*2),33+(int16)(vies.pagey+2)*40,mspw,1,
			viesco.listbackground.r+10,viesco.listbackground.r+10,viesco.listbackground.r+10);

		//mrc_drawText(p->news.name,35,35+(yi++)*40,220,220,220,0,1);
		txtJG(p->next->news.name,35,40+(int16)(vies.pagey+1)*40,viesco.listfont);

		if(p->next->news.shear == 1)
			rectJG(0,32+(int16)(vies.pagey+1)*40,2,40,viesco.listline);

		MDtub(p->next->news.num,5,35+(int16)(vies.pagey+1)*40);
	}
	// Move strip
	if(vies.number < (msph-72)/40)
		rectJG(mspw-3,37,1,msph-42,viesco.listline);
	else
		rectJG(mspw-3,37+(int16)vies.pagety/3,1,msph-42-(int16)vies.number/3,viesco.listline);

	mrc_refreshScreen(0,14,mspw,msph-14);
}

// ������
static int16 Gox=0,Posgox=0;
static void TrendsTXT(int32 data)
{
	int32 w=0,h=0,tw=0,th=0;
	char nau[30]={0},path[lunamelen]={0};

	txtwh(vies.pagenum->news.name,&w,&h);
	if(w > mspw-35-5)
	{
		if(Posgox == 0)
		{
			Gox+=2;
			if(Gox > w-(mspw-40)+10 )
			{
				Posgox=1;
			}
		}
		else
		{
			Gox-=2;
			if(Gox < -10)
			{
				Posgox=0;
			}
		}
		//����
		rectJG(0,32+(int16)vies.pagey*40,mspw,40,viesco.listbackground);
		mrc_EffSetCon(0,32+(int16)vies.pagey*40,mspw,40,viesco.listfocusbackground.r,viesco.listfocusbackground.g,viesco.listfocusbackground.b);

		//mrc_drawText(p->news.name,35,35+(yi++)*40,220,220,220,0,1);
		txtJG(vies.pagenum->news.name,35-Gox,40+(int16)vies.pagey*40,viesco.listfocusfont);

		//����
		mrc_sprintf(nau,"%s",typeanalysetxt(vies.pagenum->news.num));	
		txtwh(nau,&w,&h);
		txtJG(nau,mspw-(int16)w-10,44+(int16)h+(int16)vies.pagey*40,viesco.listfocusfilenumfont);
	
		// �ϳ�����·��,��ȡ��С
		mrc_sprintf(path,"%s/%s",vies.luname,vies.pagenum->news.name);
		if(mrc_fileState(path) == MR_IS_FILE)
		{
			mrc_sprintf(nau,"��С:%d.%dKb",mrc_getLen(path)/1024,mrc_getLen(path)%1024);	
			txtwh(nau,&tw,&th);
			txtJG(nau,mspw-(int16)(w+tw)-15,44+(int16)(th+(h-th))+(int16)vies.pagey*40,viesco.listfocusfilenumfont);
		}

		// Move strip
		if(vies.number < (msph-72)/40)
			rectJG(mspw-3,37,1,msph-42,viesco.listline);
		else
			rectJG(mspw-3,37+(int16)vies.pagety/3,1,msph-42-(int16)vies.number/3,viesco.listline);

		MDtub(vies.pagenum->news.num,5,35+(int16)vies.pagey*40);
	
		if(vies.pagenum->news.shear == 1)
			rectJG(0,32+(int16)vies.pagey*40,2,40,viesco.listline);

		if(vies.pagey == 0)
			drect(0,32,mspw,4,150,150,150,255,255,255);

		mrc_refreshScreen(0,32+(int16)vies.pagey*40,mspw,40);
	}
	else
	{
		KeyTimerStop();
	}
}

/*---------------------------------------------------------------------------*/

//�����ļ��б����
//��������������
static void FileViewBrowser_Trun(int32 data)
{	
	if(vies.number > 1) // ������ǿ��ļ���
	{
		switch(data) // ѡ���б���
		{
		case MR_KEY_DOWN:
			// �������С����Ļ���λ��,����ָ����һ��
			if(vies.pagenum->next != NULL && vies.pagey < (msph-72)/40)
			{
				vies.pagenum=vies.pagenum->next;
				vies.pagey++;
				FileViewBrowser_UIEx(MR_KEY_DOWN);
			}
			// ��������������Ļ���λ��,������б�ͷָ����һ��
			else if(vies.pagenum->next != NULL && vies.pagey < vies.number)
			{
				vies.pagehead=vies.pagehead->next,vies.pagenum=vies.pagenum->next;
				vies.pagety++;
				FileViewBrowser_UI();
			}
			// ��������ͷ
			else
			{
				vies.pagehead = vies.pagenum = vies.dirhead->next;
				vies.pagety = vies.pagey = 0;
				FileViewBrowser_UI();
			}
			break;
		case MR_KEY_UP:
			// ����������0,����ָ����һ��
			if(vies.pagenum != NULL && vies.pagey > 0)
			{
				vies.pagenum=vies.pagenum->last;
				vies.pagey--;
				FileViewBrowser_UIEx(MR_KEY_UP);
			}
			// ����������0,������б�ͷָ����һ��
			else if(vies.pagety > 0 && vies.pagehead->last != NULL)
			{
				vies.pagehead=vies.pagehead->last,vies.pagenum=vies.pagenum->last;
				vies.pagety--;
				FileViewBrowser_UI();
			}
			// ��������β
			else
			{
				int32 i=0;
				plist p=vies.dirhead;

				while(p->next != NULL)
					p=p->next;

				vies.pagenum=p;

				if(vies.number > (msph-72)/40)
				{
					while(i < (msph-72)/40 && p!=NULL)
						p=p->last,i++;

					vies.pagehead=p;
					vies.pagety=vies.number-(msph-72)/40-1;
					vies.pagey=(msph-72)/40;
				}
				else
				{
					vies.pagey=vies.number-1;
					vies.pagety=0;
				}
				FileViewBrowser_UI();
			}
			break;
		case MR_KEY_LEFT:
			// ����������0,����ָ���б�ͷ
			if(vies.pagey > 0)
			{
				while(vies.pagenum->last != NULL && vies.pagey > 0)
				{
					vies.pagenum=vies.pagenum->last;
					vies.pagey--;
				}
			}
			// ����������0,����ָ����һ���б�ͷ,��������,�Զ�����������ͷ
			else
			{
				int32 i=0;
				vies.pagey=0;

				while(vies.pagenum->last->last !=NULL && i <= (msph-72)/40)
				{	
					vies.pagenum=vies.pagenum->last,vies.pagehead=vies.pagehead->last;
					vies.pagety--,i++;
				}
			}
			FileViewBrowser_UI();
			break;
		case MR_KEY_RIGHT:
			// �������С����Ļ���λ��,����ָ���б�ͷβ��
			if(vies.pagey < (msph-72)/40)
			{
				while(vies.pagenum->next != NULL && vies.pagey < (msph-72)/40)
				{
					vies.pagenum=vies.pagenum->next;
					vies.pagey++;
				}
			}
			// ������������Ļ���λ��,����ָ����һ���б�ͷ,�������׶�,�Զ�����������β
			else
			{
				int32 i=0;
				while(vies.pagenum->next != NULL && i <= (msph-72)/40)
				{
					vies.pagehead=vies.pagehead->next,vies.pagenum=vies.pagenum->next;
					vies.pagety++,i++;
				}
			}
			FileViewBrowser_UI();
			break;
		}
	}
}

/*---------------------------------------------------------------------------*/

/*
void Back_CB(int32 p0, int32 p1, int32 p2, int32 p3, int32 p4, int32 p5)
{
	FileViewBrowser_QUI();
	FileViewBrowser_UI();
}
*/

// ������һ���ļ���
static void FileViewBrowser_Next(void)
{
	char path[lunamelen]={0};

	if(vies.number != 0) // ������ǿ��ļ���
	{
		// �ϲ�·��
		mrc_sprintf(path,"%s/%s",vies.luname,vies.pagenum->news.name);

		// ������ļ���, �������һ���ļ���
		if(mrc_fileState(path) == MR_IS_DIR)
		{
			FileViewBrowser_Free();

			mrc_sprintf(vies.luname,"%s",path);

			// ��¼�ϸ��ļ���λ��
			vies.jlu[vies.winnu][0]=vies.pagey;
			vies.jlu[vies.winnu][1]=vies.pagety;

			// �ѽ���Ŀ��1
			vies.winnu++;

			// ��������λ�á���Ŀ����
			vies.number=0,vies.pagey=0,vies.pagety=0;

			FindView_Main();

			FileViewBrowser_QUI();
			FileViewBrowser_UI();
		}
		else
		{
			if(vies.pagenum->news.num == FILE_BMP)
			{
				//WLog(path);
				//windownu=APPWINDOWS_EXITREAME;
				//PictureSee_Func_DrawImg(Back_CB);
			}
		}
	}
}

// ������һ���ļ���
static void FileViewBrowser_Last(void)
{
	int32 len=0;
	char *text="";
	char path[namelen+1]={0};

	// �������һ�� "/" ����
	text=mrc_strrchr(vies.luname,'/');
	len=mrc_strlen(vies.luname)-mrc_strlen(text);

	// ����·��ָ�����ȵ�·��
	memcpy(path,vies.luname,len);
	memset(vies.luname,0,lunamelen);

	mrc_sprintf(vies.luname,"%s",path);

	// �ͷ������ڴ�,�ÿ�����
	FileViewBrowser_Free();

	// �ѽ���Ŀ��1
	vies.winnu--;

	// ��������λ�á���Ŀ����
	vies.number=0;

	FindView_Main();

	// ��ȡ�����λ�ü�¼
	vies.pagey=vies.jlu[vies.winnu][0];
	vies.pagety=vies.jlu[vies.winnu][1];

	// ����λ�ü�¼,�����������ʾ
	len=0;
	while(len < vies.pagey + vies.pagety)
		vies.pagenum=vies.pagenum->next,len++;

	len=0;
	while(len < vies.pagety)
		vies.pagehead=vies.pagehead->next,len++;

	FileViewBrowser_QUI();
	FileViewBrowser_UI();
}

// ˢ���б�
void RefreshList(void)
{
	// �ͷ������ڴ�,�ÿ�����
	FileViewBrowser_Free();

	// ��������λ�á���Ŀ����
	vies.number=0,vies.pagey=0,vies.pagety=0;

	FindView_Main();

	FileViewBrowser_QUI();
	FileViewBrowser_UI();
}

// С����ȡ������
void Noback(void)
{
	windownu=APPWINDOWS_VIEW;
}

void warePlug_CB(int32 p0, int32 p1, int32 p2, int32 p3, int32 p4, int32 p5)
{
	FileViewBrowser_UI();
}

/*---------------------------------------------------------------------------*/

// ����λ�÷���
static int32 ReturnMoveDownUp(int32 q)
{
	int32 downy=0;
	if(q>32 && q<32+40)
	{
		downy=0;
	}
	if(q>32+40 && q<32+80)
	{
		downy=1;
	}
	if(q>32+80 && q<32+120)
	{
		downy=2;
	}
	if(q>32+120 && q<32+160)
	{
		downy=3;
	}
	if(q>32+160 && q<32+200)
	{
		downy=4;
	}
	if(q>32+200 && q<32+240)
	{
		downy=5;
	}
	if(q>32+240 && q<32+280)
	{
		downy=6;
	}
	return downy;
}

/*---------------------------------------------------------------------------*/
/*
	// ·������ɫ
	colorct waybackground;        // ����ɫ
	colorct wayfont;              // ����ɫ
	// �б���ɫ
	colorct listbackground;       // ����ɫ
	colorct listfont;             // ����ɫ
	colorct listfocusbackground;  // ���㱳��
	colorct listfocusfont;        // ��������ɫ
	colorct listfocusfilenumfont; // �����ļ���ɫ
	colorct listline;             // �б������ɫ
*/

static void colorthuo(void)
{
	viesco.waybackground        = MDskin_Getcolor("·��������");
	viesco.wayfont              = MDskin_Getcolor("·��������");
	viesco.listbackground       = MDskin_Getcolor("�б���");
	viesco.listfont             = MDskin_Getcolor("�б�����");
	viesco.listfocusbackground  = MDskin_Getcolor("�б��㱳��");
	viesco.listfocusfont        = MDskin_Getcolor("�б����ļ�������");
	viesco.listfocusfilenumfont = MDskin_Getcolor("�б����ļ���������");
	viesco.listline             = MDskin_Getcolor("�б������");
}

/*---------------------------------------------------------------------------*/

// �ļ��������ʼ��
void FileViewBrowser_Main(void)
{
	// ��ȡ��ɫ
	colorthuo();
	// ����
	FindView_Main();

	// ��ʾ
	FileViewBrowser_QUI();
	FileViewBrowser_UI();
}

// �ļ��������������
void FileViewBrowser_Event(int32 code, int32 p, int32 q)
{
	if(windownu == APPWINDOWS_VIEW)
	{
		if(code == MR_KEY_PRESS) // ѡ���б���
		{
			KeyTimerStop();
			Gox=0;
			switch(p)
			{
			case MR_KEY_POUND:
			case MR_KEY_SOFTRIGHT:
				if(vies.winnu == 0)
				{
					ExitSmallwin();
					windownu=APPWINDOWS_EXITREAME;
				}
				else
					FileViewBrowser_Last();
				break;
			case MR_KEY_SELECT:
				FileViewBrowser_Next();
				break;
			case MR_KEY_DOWN:
				KeyTimerStart(MR_KEY_DOWN,FileViewBrowser_Trun);
				break;
			case MR_KEY_UP:
				KeyTimerStart(MR_KEY_UP,FileViewBrowser_Trun);
				break;
			case MR_KEY_LEFT:
				KeyTimerStart(MR_KEY_LEFT,FileViewBrowser_Trun);
				break;
			case MR_KEY_RIGHT:
				KeyTimerStart(MR_KEY_RIGHT,FileViewBrowser_Trun);
				break;
			case MR_KEY_2: // ����
				break;
			case MR_KEY_3: // ����
				break;
			case MR_KEY_1: // ����
				if(vies.number > 0)
				{
					if(vies.pagenum->news.shear == 0)
						vies.pagenum->news.shear=1;
					else
						vies.pagenum->news.shear=0;
					FileViewBrowser_UI();
				}
				break;
			case MR_KEY_4: // ȫ��
				if(vies.number>0)
				{
					filexzAll();
				}
				break;
			case MR_KEY_7: // ���
				break;
			case MR_KEY_STAR: // ˢ���б�
				RefreshList();
				break;
			case MR_KEY_SEND: // ��ͼ
				{
					int32 w=0,h=0;	
					char buf[50]={0},nau[50]={0};
					
					mr_datetime  t_dt;
					mrc_getDatetime(&t_dt);

					mrc_sprintf(buf,"MDs/%d-%d-%d %d.%d.%d.bmp",t_dt.year,t_dt.month,t_dt.day,t_dt.hour,t_dt.minute,t_dt.second);

					mrc_PrintScreen(buf);
	
					mrc_sprintf(nau,"��ͼ�ɹ�!");
					txtwh(nau,&w,&h);
					svrect(mspw/2-(int16)w/2-14,msph-50,(int16)w+28,(int16)h+6+8,255,255,255,240,240,240,4);
					rectJG(mspw/2-(int16)w/2-10,msph-46,(int16)w+20,(int16)h+6,viesco.waybackground);
					txtJG(nau,mspw/2-(int16)w/2,msph-50+7,viesco.listfocusfont);
					fresh();

					mrc_sleep(450);
					FileViewBrowser_UI();
				}
				break;
			case MR_KEY_8: // ɾ��	
				break;
			case MR_KEY_6: // ��ռ���
				break;
			}
	
		}
		else if(MR_KEY_RELEASE == code)
		{
			KeyTimerStop();
			if(vies.pagenum != NULL)
				KeyTimerStart(0,TrendsTXT);
	     }

		if(MR_MOUSE_DOWN == code && mspw <= 240 && msph <= 320) // 240*320
		{
			int32 len=0;
			plist tp=vies.pagehead;

			KeyTimerStop();
			Gox=0;
			if(q<14)
			{
			}
		
			if(q>14 && q<32)
			{
			}

			if(q>32 && q<32+280)
				viet.downy=ReturnMoveDownUp(q);

			viet.downx=p;
			viet.upx=q;

			if(vies.number>viet.downy)
			{
				vies.pagey=viet.downy;

				while(len<viet.downy)
					tp=tp->next,len++;

				vies.pagenum=tp;
			}

			FileViewBrowser_UI();
	
		}
		else if(MR_MOUSE_UP == code && mspw <= 240 && msph <= 320) // 240*320
		{
			int32 len=0;
		
			if(q>32 && q<32+280)
				viet.upy=ReturnMoveDownUp(q);

			if(viet.upy < viet.downy && vies.number > (msph-72)/40) // Towards descend slip
			{
				if(vies.pagey+vies.pagety+(viet.downy-viet.upy) < vies.number - (msph-72)/40 +2)
				{
					while(vies.pagehead != NULL && len < viet.downy-viet.upy)
					{
						vies.pagehead=vies.pagehead->next;
						vies.pagety++,len++;
					}
					vies.pagey=viet.upy;
					FileViewBrowser_UI();
				}
				else if(vies.pagety < vies.number - (msph-72)/40 - 1)
				{
					while(vies.pagehead != NULL && vies.pagety < vies.number - (msph-72)/40 - 1)
						vies.pagehead=vies.pagehead->next,vies.pagety++;

					while(vies.pagenum != NULL && len < viet.upy-viet.downy-2)
						vies.pagenum=vies.pagenum->last,len++;

					vies.pagey=viet.upy;
					FileViewBrowser_UI();
				}
			}
			if(viet.upy > viet.downy && vies.number > (msph-72)/40) // Towards mount slip
			{
				if(vies.pagety-(viet.upy-viet.downy) > 0)
				{
					while(vies.pagehead != NULL && len < viet.upy-viet.downy)
					{
						vies.pagehead=vies.pagehead->last;
						vies.pagety--,len++;
					}
					vies.pagey=viet.upy;
					FileViewBrowser_UI();
				}
				else if(vies.pagety > 0)
				{
					while(vies.pagehead != NULL && vies.pagety > 0)
						vies.pagehead=vies.pagehead->last,vies.pagety--;

					while(vies.pagenum != NULL && len < viet.upy-viet.downy-2)
						vies.pagenum=vies.pagenum->next,len++;

					vies.pagey=viet.upy;
					FileViewBrowser_UI();
				}
			}
			if(viet.upy == viet.downy && q > viet.upx-30 && viet.upx < q+30)
			{
				if(viet.downx < p)
				{	
					if(vies.winnu > 0)
					{
						FileViewBrowser_Last();
					}
				}
				else if(p < viet.downx)
				{	
					FileViewBrowser_Next();
				}
			}
			if(vies.pagenum != NULL)
				KeyTimerStart(0,TrendsTXT);
        }
    }
	else if(windownu != APPWINDOWS_VIEW) // ѡ���б���
	{
		RmSmallwin_Event(windownu,code, p, q);
	}
}
