#ifndef ___deflateINTERFACE
#define ___deflateINTERFACE

// enum - Deflate Execute eXtract Return
enum {
	// �}�C�i�X�l�͂��ׂăG���[�Ƃ��邱��
	DZEXR_INITERROR    = -1,	//���������s
	DZEXR_DEFLATEERROR = -2,	//���k���s
	DZEXR_INFLATEERROR = -3,	//�𓀎��s
	DZEXR_OUTBUFFERROR = -4,	//�o�͐�̃o�b�t�@������Ȃ�
};


int do_compress_m2m  (char *pIn,int nInSize,char *pOut,int nOutSize,int level);        /* ���k */
int do_decompress_m2m(char *pIn,int nInSize,char *pOut,int nOutSize);                  /* �W�J�i�����j */

#endif //___deflateINTERFACE
