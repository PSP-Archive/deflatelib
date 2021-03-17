#include "pg.h"
#include "font.c"
#include "deflateInterface.h"
#include "zlibInterface.h"

#define TARGETPATH  "ms0:/PSP/GAME/deflatelib_Sample/compress.dat"
#define TARGETPATH2 "ms0:/PSP/GAME/deflatelib_Sample/uncompress.dat"

int funcUnzipCallback(int nCallbackId,
                      unsigned long ulExtractSize,
		      unsigned long ulCurrentPosition,
                      const void *pData,
                      unsigned long ulDataSize,
                      unsigned long ulUserData)
{//Test用。unziplib.aとdeflatelib.aが共存できるかを確認するため
	return 1;
}

// ---------------------------------------------------------------------------------
int exit_callback(void) 
{ 
// Cleanup the games resources etc (if required) 

// Exit game 
   sceKernelExitGame(); 

   return 0; 
} 

#define POWER_CB_POWER      0x80000000 
#define POWER_CB_HOLDON      0x40000000 
#define POWER_CB_STANDBY   0x00080000 
#define POWER_CB_RESCOMP   0x00040000 
#define POWER_CB_RESUME      0x00020000 
#define POWER_CB_SUSPEND   0x00010000 
#define POWER_CB_EXT      0x00001000 
#define POWER_CB_BATLOW      0x00000100 
#define POWER_CB_BATTERY    0x00000080 
#define POWER_CB_BATTPOWER   0x0000007F 
void power_callback(int unknown, int pwrflags) 
{ 
   // Combine pwrflags and the above defined masks 
} 

// Thread to create the callbacks and then begin polling 
int CallbackThread(void *arg) 
{ 
   int cbid; 

   cbid = sceKernelCreateCallback("Exit Callback", exit_callback); 
   SetExitCallback(cbid); 
   cbid = sceKernelCreateCallback("Power Callback", power_callback); 
   PowerSetCallback(0, cbid); 

   KernelPollCallbacks(); 
} 

/* Sets up the callback thread and returns its thread id */ 
int SetupCallbacks(void) 
{ 
   int thid = 0; 

   thid = sceKernelCreateThread("update_thread", CallbackThread, 0x11, 0xFA0, 0, 0); 
   if(thid >= 0) 
   { 
      sceKernelStartThread(thid, 0, 0); 
   } 

   return thid; 
} 

// ---------------------------------------------------------------------------------

unsigned short rgb2col(unsigned char r,unsigned char g,unsigned char b) {
	return ((((b>>3) & 0x1F)<<10)+(((g>>3) & 0x1F)<<5)+(((r>>3) & 0x1F)<<0)+0x8000);
}

char *mh_strncpy(char *s1,char *s2,int n) {
	char *rt = s1;

	while((*s2!=0) && ((n-1)>0)) {
		*s1 = *s2;
		s1++;
		s2++;
		n--;
	}
	*s1 = 0;

	return rt;
}

char *mh_strncat(char *s1,char *s2,int n) {
	char *rt = s1;

	while((*s1!=0) && ((n-1)>0)) {
		s1++;
		n--;
	}

	while((*s2!=0) && ((n-1)>0)) {
		*s1 = *s2;
		s1++;
		s2++;
		n--;
	}
	*s1 = 0;

	return rt;
}

void wait_button(void) {
	ctrl_data_t ctl;
	int btn;

	btn=1;
	while(btn!=0){
		sceCtrlReadBufferPositive(&ctl,1);
		btn = ((ctl.buttons & 0xF000) != 0);
	}
	btn=0;
	while(btn==0){
		sceCtrlReadBufferPositive(&ctl,1);
		btn = ((ctl.buttons & 0xF000) != 0);
	}
}

unsigned short num2elisa(unsigned short c) {
	if (c >= 4418) {
		return c + (0xda1 - 4418);
	} else if (c >= 1410) {
		return c + (0x20c - 1410);
	} else if (c >= 690) {
		return 0x6b;
	} else if (c >= 658) {
		return c + (0x1ec - 658);
	} else if (c >= 612) {
		return c + (0x1cb - 612);
	} else if (c >= 564) {
		return c + (0x1aa - 564);
	} else if (c >= 502) {
		return c + (0x192 - 502);
	} else if (c >= 470) {
		return c + (0x17a - 470);
	} else if (c >= 376) {
		return c + (0x124 - 376);
	} else if (c >= 282) {
		return c + (0xd1 - 282);
	} else if (c >= 252) {
		return c + (0xb7 - 252);
	} else if (c >= 220) {
		return c + (0x9d - 220);
	} else if (c >= 203) {
		return c + (0x93 - 203);
	} else if (c >= 187) {
		return 0x92;
	} else if (c >= 175) {
		return c + (0x8a - 203);
	} else if (c >= 153) {
		return c + (0x7b - 153);
	} else if (c >= 135) {
		return c + (0x74 - 135);
	} else if (c >= 119) {
		return c + (0x6c - 119);
	} else {
		return c;
	}
}

void Draw_Char_Hankaku(int x,int y,unsigned char ch,int col,int backcol,int fill) {
	unsigned short *vr;
	unsigned char  *fnt;
	unsigned char  pt;
	int y1;

	// mapping
	if (ch<0x20) {
		ch = 0;
	} else if (ch<0x80) {
		ch -= 0x20;
	} else if (ch<0xa0) {
		ch = 0;
	} else {
		ch -= 0x40;
	}
	fnt = (unsigned char *)&hankaku_font10[ch*10];

	// draw
	vr = (unsigned short *)pgGetVramAddr(x,y);
	for(y1=0;y1<10;y1++) {
		pt = *fnt++;
		if (pt & 1) { *vr = col; } else { if (fill) *vr = backcol; } vr++; pt = pt >> 1;
		if (pt & 1) { *vr = col; } else { if (fill) *vr = backcol; } vr++; pt = pt >> 1;
		if (pt & 1) { *vr = col; } else { if (fill) *vr = backcol; } vr++; pt = pt >> 1;
		if (pt & 1) { *vr = col; } else { if (fill) *vr = backcol; } vr++; pt = pt >> 1;
		if (pt & 1) { *vr = col; } else { if (fill) *vr = backcol; } vr++; pt = pt >> 1;
		vr += LINESIZE-5;
	}
}

void Draw_Char_Zenkaku(int x,int y,unsigned char u,unsigned char d,int col,int backcol,int fill) {
	unsigned short *vr;
	unsigned short *fnt;
	unsigned short pt;
	int y1;

	// mapping
	if (d > 0x7F) d--;
	if (u > 0x9F) u-=0x40;
	d -= 0x40; u -= 0x81;
	fnt = (unsigned short *)&zenkaku_font10[num2elisa(u*0xbc+d)*10];

	// draw
	vr = (unsigned short *)pgGetVramAddr(x,y);
	for(y1=0;y1<10;y1++) {
		pt = *fnt++;
		if (pt & 1) { *vr = col; } else { if (fill) *vr = backcol; } vr++; pt = pt >> 1;
		if (pt & 1) { *vr = col; } else { if (fill) *vr = backcol; } vr++; pt = pt >> 1;
		if (pt & 1) { *vr = col; } else { if (fill) *vr = backcol; } vr++; pt = pt >> 1;
		if (pt & 1) { *vr = col; } else { if (fill) *vr = backcol; } vr++; pt = pt >> 1;
		if (pt & 1) { *vr = col; } else { if (fill) *vr = backcol; } vr++; pt = pt >> 1;
		if (pt & 1) { *vr = col; } else { if (fill) *vr = backcol; } vr++; pt = pt >> 1;
		if (pt & 1) { *vr = col; } else { if (fill) *vr = backcol; } vr++; pt = pt >> 1;
		if (pt & 1) { *vr = col; } else { if (fill) *vr = backcol; } vr++; pt = pt >> 1;
		if (pt & 1) { *vr = col; } else { if (fill) *vr = backcol; } vr++; pt = pt >> 1;
		if (pt & 1) { *vr = col; } else { if (fill) *vr = backcol; } vr++; pt = pt >> 1;
		vr += LINESIZE-10;
	}
}

void mh_print(int x,int y,unsigned char *str,int col,int backcol,int fill) {
	unsigned char ch = 0,bef = 0;

	while(*str != 0) {
		ch = *str++;
		if (bef!=0) {
			Draw_Char_Zenkaku(x,y,bef,ch,col,backcol,fill);
			x+=10;
			bef=0;
		} else {
			if (((ch>=0x80) && (ch<0xa0)) || (ch>=0xe0)) {
				bef = ch;
			} else {
				Draw_Char_Hankaku(x,y,ch,col,backcol,fill);
				x+=5;
			}
		}
	}
}

#define MAXDEPTH  16
#define MAXDIRNUM 1024
#define MAXPATH   0x108
#define PATHLIST_H 20
#define REPEAT_TIME 0x40000
#define BUFSIZE		65536

dirent_t		dlist[MAXDIRNUM];
int				dlist_num;
char			now_path[MAXPATH];
char			target[MAXPATH];
char			path_tmp[MAXPATH];
int				dlist_start;
int				dlist_curpos;
int				cbuf_start[MAXDEPTH];
int				cbuf_curpos[MAXDEPTH];
int				now_depth;
char			buf[BUFSIZE];

static unsigned long control_bef_ctl  = 0;
static unsigned long control_bef_tick = 0;

unsigned long Read_Key(void) {
	ctrl_data_t ctl;

	sceCtrlReadBufferPositive(&ctl,1);
	if (ctl.buttons == control_bef_ctl) {
		if ((ctl.frame - control_bef_tick) > REPEAT_TIME) {
			return control_bef_ctl;
		}
		return 0;
	}
	control_bef_ctl  = ctl.buttons;
	control_bef_tick = ctl.frame;
	return control_bef_ctl;
}

void Get_DirList(char *path) {
	int ret,fd;

	// Directory read
	fd = sceIoDopen(path);
	dlist_num = 0;
	ret = 1;
	while((ret>0) && (dlist_num<MAXDIRNUM)) {
		ret = sceIoDread(fd, &dlist[dlist_num]);
		if (dlist[dlist_num].name[0] == '.') continue;
		if (ret>0) dlist_num++;
	}
	sceIoDclose(fd);

	// ディレクトリリストエラーチェック
	if (dlist_start  >= dlist_num) { dlist_start  = dlist_num-1; }
	if (dlist_start  <  0)         { dlist_start  = 0;           }
	if (dlist_curpos >= dlist_num) { dlist_curpos = dlist_num-1; }
	if (dlist_curpos <  0)         { dlist_curpos = 0;           }
}

void Draw_All(void) {
	int			i,col;

	pgFillvram(0);

	// 現在地
	mh_strncpy(path_tmp,now_path,40);
	mh_print(0,0,path_tmp,rgb2col(255,255,255),0,0);

	// ディレクトリリスト
	i = dlist_start;
	while (i<(dlist_start+PATHLIST_H)) {
		if (i<dlist_num) {
			col = rgb2col(255,255,255);
			if (dlist[i].type & TYPE_DIR) {
				col = rgb2col(255,255,0);
			}
			if (i==dlist_curpos) {
				col = rgb2col(255,0,0);
			}
			mh_strncpy(path_tmp,dlist[i].name,40);
			mh_print(32,((i-dlist_start)+2)*10,path_tmp,col,0,0);
		}
		i++;
	}
	pgScreenFlipV();
}

void Draw_Confirm(void) {
	pgFillvram(0);

	mh_print(40, 80,"ファイルを"   ,rgb2col(255,255,255),0,0);
	mh_print(50, 90,target         ,rgb2col(255,255,0)  ,0,0);
	mh_print(40,100,"から"         ,rgb2col(255,255,255),0,0);
	mh_print(50,110,TARGETPATH     ,rgb2col(255,255,0)  ,0,0);
	mh_print(40,120,"にコピーします。よろしいですか？",rgb2col(255,255,255),0,0);

	mh_print(40,160,"実行：○  キャンセル：×",rgb2col(255,255,255),0,0);
	pgScreenFlipV();
}

int Confirm_Control(void) {
	unsigned long key;

	while(1) {
		while(1) {
			key = Read_Key();
			if (key != 0) break;
			pgWaitV();
		}

		if (key & CTRL_CIRCLE) {
			return 1;
		}
		if (key & CTRL_CROSS) {
			return 0;
		}
	}
}

int Control(void) {
	unsigned long key;
	int i;

	// wait key
	while(1) {
		key = Read_Key();
		if (key != 0) break;
		pgWaitV();
	}

	if (key & CTRL_UP) {
		if (dlist_curpos > 0) {
			dlist_curpos--;
			if (dlist_curpos < dlist_start) { dlist_start = dlist_curpos; }
		}
	}
	if (key & CTRL_DOWN) {
		if (dlist_curpos < (dlist_num-1)) {
			dlist_curpos++;
			if (dlist_curpos >= (dlist_start+PATHLIST_H)) { dlist_start++; }
		}
	}
	if (key & CTRL_LEFT) {
		dlist_curpos -= PATHLIST_H;
		if (dlist_curpos <  0)          { dlist_curpos = 0;           }
		if (dlist_curpos < dlist_start) { dlist_start = dlist_curpos; }
	}
	if (key & CTRL_RIGHT) {
		dlist_curpos += PATHLIST_H;
		if (dlist_curpos >= dlist_num) { dlist_curpos = dlist_num-1; }
		while (dlist_curpos >= (dlist_start+PATHLIST_H)) { dlist_start++; }
	}

	if (key & CTRL_CIRCLE) {
		if (dlist[dlist_curpos].type & TYPE_DIR) {
			if (now_depth<MAXDEPTH) {
				// path移動
				mh_strncat(now_path,dlist[dlist_curpos].name,MAXPATH);
				mh_strncat(now_path,"/",MAXPATH);
				cbuf_start[now_depth] = dlist_start;
				cbuf_curpos[now_depth] = dlist_curpos;
				dlist_start  = 0;
				dlist_curpos = 0;
				now_depth++;
				return 1;
			}
		} else {
			//
			return 2;
/*			for(i=0;i<MAXPATH;i++) {
				if (dlist[dlist_curpos].name[i]==0) break;
			}
			if (i>2) {
				if (((dlist[dlist_curpos].name[i-3] & 0xDF) == '.') &&
				    ((dlist[dlist_curpos].name[i-2] & 0xDF) == 'G') &&
				    ((dlist[dlist_curpos].name[i-1] & 0xDF) == 'B')) {
					return 2;
				}
				i--;
			}*/
		}
	}
	if (key & CTRL_CROSS) {
		if (now_depth > 0) {
			// path移動
			for(i=0;i<MAXPATH;i++) {
				if (now_path[i]==0) break;
			}
			i--;
			while(i>4) {
				if (now_path[i-1]=='/') {
					now_path[i]=0;
					break;
				}
				i--;
			}
			now_depth--;
			dlist_start  = cbuf_start[now_depth];
			dlist_curpos = cbuf_curpos[now_depth];
			return 1;
		}
	}
	
	return 0;
}
#define BIGBUFFSIZE 1024*1024*10
char tmpInBuff[BIGBUFFSIZE];
char tmpOutBuff[BIGBUFFSIZE];
void CopyExecute(void) {
	int fd1,fd2,fd3,len,i;

	pgFillvram(0);
	mh_print(0,0,"圧縮しています",0xFFFF,0,0);
	pgScreenFlipV();

	fd1 = sceIoOpen(target,O_RDONLY,0777);
	fd2 = sceIoOpen(TARGETPATH ,O_RDWR | O_CREAT | O_TRUNC,0777);
	fd3 = sceIoOpen(TARGETPATH2,O_RDWR | O_CREAT | O_TRUNC,0777);
	
	len = sceIoRead(fd1, tmpInBuff, BIGBUFFSIZE);
	len = do_compress_m2m(tmpInBuff,len,tmpOutBuff,BIGBUFFSIZE,9);
	pgFillvram(0);
	mh_print(0,20,"続けて解凍しています",0xFFFF,0,0);
	pgScreenFlipV();
	sceIoWrite(fd2,tmpOutBuff,len);
	for(i=0;i<BIGBUFFSIZE;i++){tmpInBuff[i] = 0;}
	len = do_decompress_m2m(tmpOutBuff,len,tmpInBuff,BIGBUFFSIZE);
	sceIoWrite(fd3,tmpInBuff,len);

	sceIoClose(fd1);
	sceIoClose(fd2);
	sceIoClose(fd3);
}

int xmain(void) {
	int fd,fd2,ret;
	int ptr,len;
	unsigned long d;
	int i;
	unsigned char *p;

	// Initialize
	pgInit();
	SetupCallbacks();
	pgScreenFrame(2,0);
	sceCtrlInit(0);
	sceCtrlSetAnalogMode(0);

	// default value
	mh_strncpy(now_path,"ms0:/",MAXPATH);

	//
	Get_DirList(now_path);
	dlist_start  = 0;
	dlist_curpos = 0;
	now_depth    = 0;

	while(1) {
		Draw_All();
		switch(Control()) {
		case 1:
			Get_DirList(now_path);
			break;
		case 2:
			// Copy confirm
			mh_strncpy(target,now_path,MAXPATH);
			mh_strncat(target,dlist[dlist_curpos].name,MAXPATH);
			Draw_Confirm();
			if (Confirm_Control()!=0) {
				CopyExecute();
			}
			break;
		case 3:
			//Test用。unziplib.aとdeflatelib.aが共存できるかを確認するため
			Unzip_setCallback(funcUnzipCallback);
			Unzip_execExtract("ms0:/PSP/GAME/HogeHoge/Foo.zip", 0);
			break;
		}
	}

	return 0;
}
