#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <iconv.h>
#include "fontx.h"

#define MYBUFSZ 128

int main (int argc, char **argv) {
  FontxFile fx[2];

  char    str_utf[MYBUFSZ+1];
  uint16_t sjis[128];
  int spos;

  uint8_t fonts[128];
  uint8_t bitmap[128];
  uint8_t pw;
  uint8_t ph;
  int i;

  /* 変換元文字列を作成（このソースはUTF-8で書かれている）*/
  strcpy(str_utf, "漢字TESTｶﾝｼﾞ");
//  printf("%d\n", strlen(str_utf));

  /* 文字コード変換(UTF-8->SJIS) */
  spos = String2SJIS(str_utf, strlen(str_utf), sjis);

  /* フォントファイルの指定(お好みで) */
  Fontx_init(fx,"./ILGH16XB.FNT","./ILGZ16XB.FNT"); // 16Dot Gothic
//  Fontx_init(fx,"./ILMH16XB.FNT","./ILMZ16XB.FNT"); // 16Dot Mincyo
//  Fontx_init(fx,"./ILGH24XB.FNT","./ILGZ24XB.FNT"); // 24Dot Gothic
//  Fontx_init(fx,"./ILGH32XB.FNT","./ILGZ32XB.FNT"); // 32Dot Gothic

  bool rc;
  for (i=0;i<spos;i++) {
    printf("sjis[%d]=%x\n",i,sjis[i]);
    rc = GetFontx(fx, sjis[i], fonts, &pw, &ph); // SJIS -> Fontパターン
//    printf("rc=%d pw=%d ph=%d\n",rc,pw,ph);
    if (!rc) continue;
    ShowFont(fonts, pw, ph);

    Font2Bitmap(fonts, bitmap, pw, ph, 0);
    ShowBitmap(bitmap, pw, ph);
  }
//  DumpFX(fx);

  return 0;
}

