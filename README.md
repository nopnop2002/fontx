# fontx
Linux FONTX Library

Linuxで使えるFontxのライブラリを探しましたが見つからなかったので作りました。  
  
1.GetFontx
フォントファイルから指定されたSJISコードのフォントパターンを取り出す。
2.Fontx2Bitmap
フォントファイルをビットマップに変換する。
  
RaspberryPiやOrangePiでグラフィックLCDに漢字を表示する際に使うことを想定していますので  
UTF→SJIS変換の関数も含まれています。  

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
