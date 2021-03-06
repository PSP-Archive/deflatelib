deflatelib.a

【内容】
Deflate/Inflate の圧縮/解凍を行うライブラリが主です。
それを使ったアプリケーションも同梱してあります。こちらは従です。

【使い方（プログラムを使ってみたい人向け）】
EBOOT.PBPをdeflatelib_Sampleディレクトリにコピーして実行すると、
GBFileSelecter004の画面が出てきます。
ファイルを選択することで
deflatelib_Sample/compress.datに圧縮したデータが
deflatelib_Sample/uncompress.datに展開したデータが出来上がります。
選択したファイルとuncompress.datが同じもの（中身が同じなだけで、ファイル名やタイムスタンプは違います）に
なるはずなのですが…
ならなかったらもう一回デバッグしますので、詳細を教えていただけるとありがたい。

【使い方（プログラムを書く人向け）】
ライブラリの使い方としては、deflatelib.aをリンクして、deflateInterface.hをインクルードするだけです。

実行時、作業エリアとしてメモリを約270Kバイト使います。
展開だけですと40Kバイトくらいでも良さそうなのですが、
圧縮をしようとすると270Kバイトくらいは必要そうです。

命令はとりあえず２つ。
int do_compress_m2m  (char *pIn,int nInSize,char *pOut,int nOutSize,int level);        /* 圧縮 */
int do_decompress_m2m(char *pIn,int nInSize,char *pOut,int nOutSize);                  /* 展開（復元） */

上の命令が圧縮用で
下の命令が展開用です。
levelは圧縮レベルです。0-9で選択してください。0で無圧縮です。9で最高圧縮率となります。かなり遅いですが。
展開はそんなに遅くない…と思う。多分。Windows用のアプリでも、圧縮は遅くても解凍はそこそこ速いので。
なお、デフォルトというか、標準というのは圧縮レベル6だそうです。

入力バッファと出力バッファは使用者（プログラムを書く人）が用意してください。
圧縮時の出力バッファの大きさは、入力の大きさ(単位：バイト)をnとして
最大で (nバイト+12バイト)*1.001 になるそうですが、あまりそういった圧縮率の悪いものに出会うことは無いでしょう。
展開時の出力バッファの大きさは…まぁうまいこと何とかしてください(ぉぃぉぃ

戻り値は、圧縮用/展開用共に出力データの大きさ(単位：バイト)で、
負の値が返ってきたときは
	DZEXR_INITERROR    = -1,	//初期化失敗
	DZEXR_DEFLATEERROR = -2,	//圧縮失敗
	DZEXR_INFLATEERROR = -3,	//解凍失敗
	DZEXR_OUTBUFFERROR = -4,	//出力先のバッファが足りない
となっています。

UnzipLibにはコールバック関数が搭載されていて、きめ細かい制御ができたのですが、
deflatelibではめんどかったので省略。ソースを書き換えて使いやすいように改変してください。

使い方としては、大きさが決まっていてそれでいて大きいデータ
（青空文庫のフォントデータ等。これは１種類の20ドットフォントで500kByteほどあったりします）を
圧縮してソースに取り込んでコンパイルし、実行時にメモリに展開する
（これなら展開後の出力バッファの大きさがプログラムを組む人には既知なので出力バッファの大きさで悩まない）
なんて使い方を考えています。

サムネイルの絵とかにも使えるかもしれませんが、私のプログラムには出てこないのでなんともなんとも。

/*
うまく使えばlibpngなんてのも作れる、かも!?
pngはDeflate/Inflateを使っているらしいので。
*/

【履歴】
2005.06.30　Ver1.00
ソースつきで公開。

【謝辞】
Deflate/Inflate の心臓部はzlibのソースを利用しています。
また、圧縮/展開のプログラムは三重大学の奥村晴彦先生のＨＰから拝借したものを元に作っております。
http://oku.edu.mie-u.ac.jp/~okumura/compression/zlib.html

プログラム自体はMobileHackerzさんのGBFileSelecter004を元にソースを組上げています。

rukaさんのUnzipLibからは、良いところを可能な限りパクらせていただきました。

PSPEが無かったら、とてもデバッグしきれなかったことは言うまでもありません。

yさんのuo_Snes9x_002y16に組み込んでいただきました。デバッグにご協力いただきましてありがとうございます。

http://hp.vector.co.jp/authors/VA013391/fonts/
で配布されているビットマップフォント「ナガ10」を使わせていただきました。

以上、この場を借りてお礼申し上げます

【作った人】
　henoheno　居住地：午後の高速道路

【追伸】
do_compress_m2m【Memory->Memory】以外にも
do_compress_m2f【Memory->File】や
do_decompress_f2m【File->Memory】なんてのも、誰か作っていただけるとちょっとうれしい（他力本願で申し訳ない）

