# fontx
Linux FONTX Library

Linuxで使えるFontxのライブラリを探しましたが見つからなかったので作りました。  
フォントファイルから指定されたSJISコードのフォントパターンを取り出すだけの関数です。  
RaspberryPiやOrangePiでグラフィックLCDに漢字を表示する際に使うことを想定しています。  

git clone https://github.com/nopnop2002/fontx  
cd fontx  
cc main.c fontx.c  
./a.out

---

こちらで公開されているESP8266用のライブラリをRPI/OPIで使えるようにしただけです。

https://github.com/h-nari/Fontx

---

FONTX形式のフォントファイルはこちらなどから入手可能です。

<http://ayati.cocolog-nifty.com/blog/2012/08/ipalx322416-64a.html>


<http://www.geocities.jp/littlimi/misaki.htm>



