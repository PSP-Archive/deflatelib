deflatelib.a

�y���e�z
Deflate/Inflate �̈��k/�𓀂��s�����C�u��������ł��B
������g�����A�v���P�[�V�������������Ă���܂��B������͏]�ł��B

�y�g�����i�v���O�������g���Ă݂����l�����j�z
EBOOT.PBP��deflatelib_Sample�f�B���N�g���ɃR�s�[���Ď��s����ƁA
GBFileSelecter004�̉�ʂ��o�Ă��܂��B
�t�@�C����I�����邱�Ƃ�
deflatelib_Sample/compress.dat�Ɉ��k�����f�[�^��
deflatelib_Sample/uncompress.dat�ɓW�J�����f�[�^���o���オ��܂��B
�I�������t�@�C����uncompress.dat���������́i���g�������Ȃ����ŁA�t�@�C������^�C���X�^���v�͈Ⴂ�܂��j��
�Ȃ�͂��Ȃ̂ł����c
�Ȃ�Ȃ�������������f�o�b�O���܂��̂ŁA�ڍׂ������Ă���������Ƃ��肪�����B

�y�g�����i�v���O�����������l�����j�z
���C�u�����̎g�����Ƃ��ẮAdeflatelib.a�������N���āAdeflateInterface.h���C���N���[�h���邾���ł��B

���s���A��ƃG���A�Ƃ��ă��������270K�o�C�g�g���܂��B
�W�J�����ł���40K�o�C�g���炢�ł��ǂ������Ȃ̂ł����A
���k�����悤�Ƃ����270K�o�C�g���炢�͕K�v�����ł��B

���߂͂Ƃ肠�����Q�B
int do_compress_m2m  (char *pIn,int nInSize,char *pOut,int nOutSize,int level);        /* ���k */
int do_decompress_m2m(char *pIn,int nInSize,char *pOut,int nOutSize);                  /* �W�J�i�����j */

��̖��߂����k�p��
���̖��߂��W�J�p�ł��B
level�͈��k���x���ł��B0-9�őI�����Ă��������B0�Ŗ����k�ł��B9�ōō����k���ƂȂ�܂��B���Ȃ�x���ł����B
�W�J�͂���Ȃɒx���Ȃ��c�Ǝv���B�����BWindows�p�̃A�v���ł��A���k�͒x���Ă��𓀂͂������������̂ŁB
�Ȃ��A�f�t�H���g�Ƃ������A�W���Ƃ����͈̂��k���x��6�������ł��B

���̓o�b�t�@�Əo�̓o�b�t�@�͎g�p�ҁi�v���O�����������l�j���p�ӂ��Ă��������B
���k���̏o�̓o�b�t�@�̑傫���́A���͂̑傫��(�P�ʁF�o�C�g)��n�Ƃ���
�ő�� (n�o�C�g+12�o�C�g)*1.001 �ɂȂ邻���ł����A���܂肻�����������k���̈������̂ɏo����Ƃ͖����ł��傤�B
�W�J���̏o�̓o�b�t�@�̑傫���́c�܂����܂����Ɖ��Ƃ����Ă�������(��������

�߂�l�́A���k�p/�W�J�p���ɏo�̓f�[�^�̑傫��(�P�ʁF�o�C�g)�ŁA
���̒l���Ԃ��Ă����Ƃ���
	DZEXR_INITERROR    = -1,	//���������s
	DZEXR_DEFLATEERROR = -2,	//���k���s
	DZEXR_INFLATEERROR = -3,	//�𓀎��s
	DZEXR_OUTBUFFERROR = -4,	//�o�͐�̃o�b�t�@������Ȃ�
�ƂȂ��Ă��܂��B

UnzipLib�ɂ̓R�[���o�b�N�֐������ڂ���Ă��āA���ߍׂ������䂪�ł����̂ł����A
deflatelib�ł͂߂�ǂ������̂ŏȗ��B�\�[�X�����������Ďg���₷���悤�ɉ��ς��Ă��������B

�g�����Ƃ��ẮA�傫�������܂��Ă��Ă���ł��đ傫���f�[�^
�i�󕶌ɂ̃t�H���g�f�[�^���B����͂P��ނ�20�h�b�g�t�H���g��500kByte�قǂ������肵�܂��j��
���k���ă\�[�X�Ɏ�荞��ŃR���p�C�����A���s���Ƀ������ɓW�J����
�i����Ȃ�W�J��̏o�̓o�b�t�@�̑傫�����v���O������g�ސl�ɂ͊��m�Ȃ̂ŏo�̓o�b�t�@�̑傫���ŔY�܂Ȃ��j
�Ȃ�Ďg�������l���Ă��܂��B

�T���l�C���̊G�Ƃ��ɂ��g���邩������܂��񂪁A���̃v���O�����ɂ͏o�Ă��Ȃ��̂łȂ�Ƃ��Ȃ�Ƃ��B

/*
���܂��g����libpng�Ȃ�Ă̂�����A����!?
png��Deflate/Inflate���g���Ă���炵���̂ŁB
*/

�y�����z
2005.06.30�@Ver1.00
�\�[�X���Ō��J�B

�y�ӎ��z
Deflate/Inflate �̐S������zlib�̃\�[�X�𗘗p���Ă��܂��B
�܂��A���k/�W�J�̃v���O�����͎O�d��w�̉������F�搶�̂g�o����q�؂������̂����ɍ���Ă���܂��B
http://oku.edu.mie-u.ac.jp/~okumura/compression/zlib.html

�v���O�������̂�MobileHackerz�����GBFileSelecter004�����Ƀ\�[�X��g�グ�Ă��܂��B

ruka�����UnzipLib����́A�ǂ��Ƃ�����\�Ȍ���p�N�点�Ă��������܂����B

PSPE������������A�ƂĂ��f�o�b�O������Ȃ��������Ƃ͌����܂ł�����܂���B

y�����uo_Snes9x_002y16�ɑg�ݍ���ł��������܂����B�f�o�b�O�ɂ����͂��������܂��Ă��肪�Ƃ��������܂��B

http://hp.vector.co.jp/authors/VA013391/fonts/
�Ŕz�z����Ă���r�b�g�}�b�v�t�H���g�u�i�K10�v���g�킹�Ă��������܂����B

�ȏ�A���̏���؂�Ă���\���グ�܂�

�y������l�z
�@henoheno�@���Z�n�F�ߌ�̍������H

�y�ǐL�z
do_compress_m2m�yMemory->Memory�z�ȊO�ɂ�
do_compress_m2f�yMemory->File�z��
do_decompress_f2m�yFile->Memory�z�Ȃ�Ă̂��A�N������Ă���������Ƃ�����Ƃ��ꂵ���i���͖{��Ő\����Ȃ��j

