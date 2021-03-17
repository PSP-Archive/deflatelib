/* zlib を使う例 */

#include <stdio.h>
#include <stdlib.h>

#include "deflateInterface.h"

/*
char tmp_co[600000];
char tmp_de[600000];
void co()
{
	int InBuffSize,CoBuffSize,DeBuffSize;

	InBuffSize = sizeof(zenkaku_font20_KappaB);
	CoBuffSize = do_compress_m2m((char *)zenkaku_font20_KappaB,InBuffSize,tmp_co,sizeof(tmp_co),9);

	if(CoBuffSize >= 0)
	{
		DeBuffSize = do_decompress_m2m(tmp_co,CoBuffSize,tmp_de,sizeof(tmp_de));
		if(DeBuffSize == InBuffSize)
		{
			int i;
			char* pIn = (char *)zenkaku_font20_KappaB;
			char* pDe = (char *)tmp_de;
			for(i=0;i<InBuffSize;i++)
			{
				if(pIn[i] !=pDe[i])
				{
					i = i;
				}
			}
		}
	}
}
*/

int main(int argc, char *argv[])
{
    int c;
	FILE *fin, *fout;               /* 入力・出力ファイル */

    if (argc != 4) {
        fprintf(stderr, "Usage: comptest flag infile outfile\n");
        fprintf(stderr, "  flag: c=compress d=decompress\n");
        exit(0);
    }
    if      (argv[1][0] == 'c') {c = 1;}
	else if (argv[1][0] == 'd') {c = 0;}
	else
	{
        fprintf(stderr, "Unknown flag: %s\n", argv[1]);
        exit(1);
    }

    if ((fin  = fopen(argv[2], "rb")) == NULL) {fprintf(stderr, "Can't open %s\n", argv[2]); exit(1);}
    if ((fout = fopen(argv[3], "wb")) == NULL) {fprintf(stderr, "Can't open %s\n", argv[3]); exit(1);}

	{
		int InBuffSize  = 1024*1024*24;
		int OutBuffSize = 1024*1024*24+1;
		char *tmpInBuff  = malloc(InBuffSize);
		char *tmpOutBuff = malloc(OutBuffSize);
		int level = 9;	//0-9

		InBuffSize = fread(tmpInBuff,1,InBuffSize,fin);

	    if (c)
		{
			OutBuffSize = do_compress_m2m(tmpInBuff,InBuffSize,tmpOutBuff,OutBuffSize,level);
			if(OutBuffSize >= 0)	fwrite(tmpOutBuff,1,OutBuffSize,fout);
		}
		else
		{
			OutBuffSize = do_decompress_m2m(tmpInBuff,InBuffSize,tmpOutBuff,OutBuffSize);
			if(OutBuffSize >= 0)	fwrite(tmpOutBuff,1,OutBuffSize,fout);
		}

		free(tmpInBuff);
		free(tmpOutBuff);
	}
    fclose(fin);
    fclose(fout);

    return 0;
}

