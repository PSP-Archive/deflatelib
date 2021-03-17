#include "deflateInterface.h"
#include "zlib.h"

char TMP[5816+65536+65536+65536+65536];	//MAX 5816+65536+65536+65536+65536?
int usedTMP;

#define INBUFSIZ   1024         /* ���̓o�b�t�@�T�C�Y�i�C�Ӂj */
#define OUTBUFSIZ  1024         /* �o�̓o�b�t�@�T�C�Y�i�C�Ӂj */

void ClearTmpBuff()
{
	usedTMP = 0;
}

voidpf zcalloc(voidpf opaque, uInt items, uInt size)
{
	voidpf p = Z_NULL;
	if(sizeof(TMP) >= usedTMP + items*size)
	{
		p = &(TMP[usedTMP]);
		usedTMP += items*size;
	}
	return p;
}

void zcfree(voidpf opaque, voidpf address)
{;
}

int do_compress_m2m(char *pIn,int nInSize,char *pOut,int nOutSize,int level)          /* ���k */
{
	int flush, status;
	z_stream z;                     /* ���C�u�����Ƃ��Ƃ肷�邽�߂̍\���� */

	char *pI = pIn;
	char *pO = pOut;
	int nUsedSizeIn  = 0;
	int nUsedSizeOut = 0;

	if((level < 0) || (9 < level))	level = 6;
	if(nOutSize < 0)	return DZEXR_OUTBUFFERROR;

	ClearTmpBuff();
    /* ���ׂẴ������Ǘ������O�ōs�� */
    z.zalloc = zcalloc;
    z.zfree  = zcfree;
    z.opaque = Z_NULL;

    /* ������ */
    /* ��2�����͈��k�̓x���B0�`9 �͈̔͂̐����ŁC0 �͖����k */
    if (deflateInit(&z, level) != Z_OK){return DZEXR_INITERROR;}

    z.avail_in  = 0;            /* ���̓o�b�t�@���̃f�[�^�̃o�C�g�� */
    z.next_out  = pO;           /* �o�̓|�C���^ */
    z.avail_out = (nOutSize - nUsedSizeOut >= OUTBUFSIZ) ? OUTBUFSIZ : nOutSize - nUsedSizeOut;    /* �o�̓o�b�t�@�̃T�C�Y */
	pO           += z.avail_out;
	nUsedSizeOut += z.avail_out;

    /* �ʏ�� deflate() �̑�2������ Z_NO_FLUSH �ɂ��ČĂяo�� */
    flush = Z_NO_FLUSH;

    while (1)
	{
        if (z.avail_in == 0)
		{  /* ���͂��s����� */
            z.next_in  = pI;  /* ���̓|�C���^����̓o�b�t�@�̐擪�� */
            z.avail_in = (nInSize - nUsedSizeIn >= INBUFSIZ) ? INBUFSIZ : nInSize - nUsedSizeIn;	/* �f�[�^��ǂݍ��� */
			pI          += z.avail_in;
			nUsedSizeIn += z.avail_in;

            /* ���͂��Ō�ɂȂ����� deflate() �̑�2������ Z_FINISH �ɂ��� */
            if (z.avail_in < INBUFSIZ) flush = Z_FINISH;
        }
        status = deflate(&z, flush); /* ���k���� */
        if (status == Z_STREAM_END) break; /* ���� */
        if (status != Z_OK) {   /* �G���[ */
            return DZEXR_DEFLATEERROR;
        }
        if (z.avail_out == 0)
		{ /* �o�̓o�b�t�@���s����� */
            z.next_out  = pO;        /* �o�̓|�C���^�����ɖ߂� */
            z.avail_out = (nOutSize - nUsedSizeOut >= OUTBUFSIZ) ? OUTBUFSIZ : nOutSize - nUsedSizeOut; /* �o�̓o�b�t�@�c�ʂ����ɖ߂� */
			pO           += z.avail_out;
			nUsedSizeOut += z.avail_out;

			if(z.avail_out == 0)	return DZEXR_OUTBUFFERROR;
        }
    }

    /* �c���f���o�� */
    nUsedSizeOut -= z.avail_out;

    /* ��n�� */
    if (deflateEnd(&z) != Z_OK)
	{
        return DZEXR_DEFLATEERROR;
    }

	return nUsedSizeOut;
}

int do_decompress_m2m(char *pIn,int nInSize,char *pOut,int nOutSize)        /* �W�J�i�����j */
{
	int status;
	z_stream z;                     /* ���C�u�����Ƃ��Ƃ肷�邽�߂̍\���� */

	char *pI = pIn;
	char *pO = pOut;
	int nUsedSizeIn  = 0;
	int nUsedSizeOut = 0;

	if(nOutSize < 0)	return DZEXR_OUTBUFFERROR;

 	ClearTmpBuff();
   /* ���ׂẴ������Ǘ������O�ōs�� */
    z.zalloc = zcalloc;
    z.zfree  = zcfree;
    z.opaque = Z_NULL;

    /* ������ */
    z.next_in  = Z_NULL;
    z.avail_in = 0;
    if (inflateInit(&z) != Z_OK){return DZEXR_INITERROR;}

    z.next_out  = pO;           /* �o�̓|�C���^ */
    z.avail_out = (nOutSize - nUsedSizeOut >= OUTBUFSIZ) ? OUTBUFSIZ : nOutSize - nUsedSizeOut;    /* �o�̓o�b�t�@�c�� */
 	pO           += z.avail_out;
	nUsedSizeOut += z.avail_out;
    status = Z_OK;

    while (status != Z_STREAM_END)
	{
        if (z.avail_in == 0)
		{  /* ���͎c�ʂ��[���ɂȂ�� */
            z.next_in  = pI;  /* ���̓|�C���^�����ɖ߂� */
            z.avail_in = (nInSize - nUsedSizeIn >= INBUFSIZ) ? INBUFSIZ : nInSize - nUsedSizeIn;	/* �f�[�^��ǂݍ��� */
			pI          += z.avail_in;
			nUsedSizeIn += z.avail_in;
        }
        status = inflate(&z, Z_NO_FLUSH); /* �W�J */
        if (status == Z_STREAM_END) break; /* ���� */
        if (status != Z_OK)
		{   /* �G���[ */
            return DZEXR_INFLATEERROR;
        }
        if (z.avail_out == 0)
		{ /* �o�̓o�b�t�@���s����� */
            z.next_out    = pO;        /* �o�̓|�C���^�����ɖ߂� */
            z.avail_out   = (nOutSize - nUsedSizeOut >= OUTBUFSIZ) ? OUTBUFSIZ : nOutSize - nUsedSizeOut; /* �o�̓o�b�t�@�c�ʂ����ɖ߂� */
			pO           += z.avail_out;
			nUsedSizeOut += z.avail_out;

			if(z.avail_out == 0)	return DZEXR_OUTBUFFERROR;
        }
    }

    /* �c���f���o�� */
    nUsedSizeOut -= z.avail_out;

    /* ��n�� */
    if (inflateEnd(&z) != Z_OK)
	{
        return DZEXR_INFLATEERROR;
    }

	return nUsedSizeOut;
}
