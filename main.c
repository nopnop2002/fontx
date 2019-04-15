#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <iconv.h>
#include "fontx.h"

#define MYBUFSZ 128

int main (int argc, char **argv) {
  FontxFile fx[2];
  char str_utf[MYBUFSZ+1];
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
  spos = String2SJIS((unsigned char *)str_utf, strlen(str_utf), sjis, 128);

  /* フォントファイルの指定(お好みで) */
  // 16Dot Gothic
  //InitFontx(fx,"./fontx/ILGH16XB.FNT","./fontx/ILGZ16XB.FNT");
  // 16Dot Mincyo
  //InitFontx(fx,"./fontx/ILMH16XB.FNT","./fontx/ILMZ16XB.FNT");
  // 24Dot Gothic
  //InitFontx(fx,"./fontx/ILGH24XB.FNT","./fontx/ILGZ24XB.FNT");
  // 32Dot Gothic
  InitFontx(fx,"./fontx/ILGH32XB.FNT","./fontx/ILGZ32XB.FNT");

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
  //DumpFontx(fx);

  return 0;
}

