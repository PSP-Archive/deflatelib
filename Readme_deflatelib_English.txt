Hi this is Henoheno
The program "AozoraBunko" reader for the PSP has become quite large, so I went ahead and made a
compression/decompression library.  I tried my best to include all of the best parts of Ruka's 
UnzipLib. Many thanks.

(Although there were no problems with UnzipLib itself, with UnzipLib I figured that if I have to 
enter in the file name (I wanted to expand it from the memory), and if including it meant remaking 
it, then I thought including compression would be an interesting way to go.  In addition, Rin's 
Packbits does not do that great of a job of compressing the font I wanted to, (Of course I know it 
wouldn't work) so I was left with no choice but to make it myself.

File selection.
Copying the EBOOT.PBP into the deflatelib_sample directory causes the GBFileSelector004 screen to
appear. Selecting the file causes the compressed deflatelib_Sample/compress.dat data to be decompressed
into the deflatelib_Sample/uncompress.dat.

Local Reference CopyExecute function.
The file that has been selected and the uncompress.dat should be the same thing, but if they are 
not please tell me and I will work on debugging it.

In addition, Deflate/Inflate Compression/Decompression is being used.
Lifted from zlib.
Also, I'm right in the middle of debugging.  I am releasing the source so that if someone would be 
kind enough to help me out I would appreciate it.
I intend to release the final source once all debugging is finished.

On how to use the library, link deflatelib.a, and just include deflateInterface.h.
Two commands.
int do_compress_m2m  (char *pIn,int nInSize,char *pOut,int nOutSize,int level); /* compression */
int do_decompress_m2m(char *pIn,int nInSize,char *pOut,int nOutSize);  /* decompression（restoration） */

The upper line is the compression command.
The lower line is the decompression command.
level refrers to the level of compression.  Please choose from 0-9.  0 is equivalent to zero compression.
9 is the highest level of compression, but is quite slow.
In addition, the default or standard compression level is 6.

The programmer must provide the input and output buffer.
Compression time is equal to the size of the input (bytes) where they are represented by (n).
At the most it will look like this (nバイト+12バイト)*1.001, however it is unlikely for anyone 
to come across a file with such a poor compression ratio.
As for the decompression time....well please try to work something good out...

No matter which of the above two functions, the return value is a negative number equavalent to
the size of the output (bytes)
        DZEXR_INITERROR    = -1,	//Formatting Failure
	DZEXR_DEFLATEERROR = -2,	//Compression Failure
	DZEXR_INFLATEERROR = -3,	//Decompression Failure
	DZEXR_OUTBUFFERROR = -4,	//Output buffer is too small
Listing up the entire call-back function was a pain in the neck, so I abbreviated.


I'm thinking about using this program the following way. Decide on the size of the file, then 
take some large data ( one "AozoraBunko" font is about500kBytes) compresse it, take it into the 
source, compile it, and then run the decompression (I already know the size of the output file).
Decompression shouldn't be that slow...I think.  Maybe.
This could probably also be used for thumbnail compression, but I don't use thumbnails in any of 
my programs so I can't really do anything.

P.S.
After I release the source will someone please make something other than
do_compress_m2m {from memory to memory}, and  also make do_compress_m2f{from memory to file}?



