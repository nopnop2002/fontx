# fontx
Linux FONTX Library

Linuxで使えるFontxのライブラリを探しましたが見つからなかったので作りました。
  
1.Fontx_init  
半角フォントと全角フォントを指定する。
  
2.GetFontx  
フォントファイルから指定されたSJISコードのフォントパターンを取り出す。
  
3.Fontx2Bitmap  
フォントファイルをビットマップに変換する。
  
4.UnderlineBitmap  
ビットマップにアンダーラインを追加する。
  
5.ReversBitmap  
ビットマップの0/1を反転する。
  
6.UTF2SJIS  
UTFコードをSJISコードに変換する。
  
7.String2SJIS  
UTFコードが含まれている文字列をSJIS配列に変換する。
  
8.ShowFont  
フォントパターンを表示する。  
表示例は16DotFont.txt/24DotFont.txt/32DotFont.txtを参照してください。
  
9.ShowBitmap  
ビットマップを表示する。
  
RaspberryPiやOrangePiでTFTに漢字を表示する際に使うことを想定しています。  
変換したビットマップをTFTのフレームバッファにコピーすれば文字が表示されます。

---

git clone https://github.com/nopnop2002/fontx  
cd fontx  
cc main.c fontx.c  
./a.out

---

こちらで公開されているESP8266用のライブラリを元にRPI/OPI用に移植しました。  
https://github.com/h-nari/Fontx
  
---

FONTX形式のフォントファイルはこちらなどから入手可能です。  
<http://ayati.cocolog-nifty.com/blog/2012/08/ipalx322416-64a.html>  
<http://www.geocities.jp/littlimi/misaki.htm>   

フォントファイルは同じディレクトリに置いてください。   
