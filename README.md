# fontx
Linux FONTX Library

Linuxで使えるFontxのライブラリを探しましたが見つからなかったので作りました。   

__InitFontx__  
半角フォントと全角フォントを指定する。   

__GetFontx__  
フォントファイルから指定されたSJISコードのフォントパターンを取り出す。   

__Fontx2Bitmap__  
フォントファイルをビットマップに変換する。   

__UnderlineBitmap__  
ビットマップにアンダーラインを追加する。   

_ReversBitmap__  
ビットマップの0/1を反転する。   

__UTF2SJIS__  
UTFコードをSJISコードに変換する。   

__String2SJIS__  
UTFコードが含まれている文字列をSJIS配列に変換する。  

__ShowFont__  
フォントパターンを表示する。  
表示例は16DotFont.txt/24DotFont.txt/32DotFont.txtを参照してください。  

__ShowBitmap__  
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

フォントファイルはfontxディレクトリに置いてください。   
