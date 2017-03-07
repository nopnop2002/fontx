#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <iconv.h>
#include "fontx.h"

#define MYBUFSZ 128

int main (int argc, char **argv) {
  FontxFile fx[2];

  iconv_t ic;
  char    str_in[MYBUFSZ+1];
  char    str_out[MYBUFSZ+1];
  char    *ptr_in  = str_in;
  char    *ptr_out = str_out;
  size_t  mybufsz = (size_t) MYBUFSZ;
  uint32_t sjis[128];
  int spos = 0;

  uint8_t fonts[128];
  uint8_t pw;
  uint8_t ph;
  int x,y,fpos;
  int i;

  /* 変換元文字列を作成（このソースはUTF-8で書かれている）*/
  strcpy(str_in, "漢字TEST");
//  printf("%d\n", strlen(str_in));

  /* 文字コード変換(UTF-8->SJIS)処理 */
  ic = iconv_open("SJIS", "UTF-8");
  iconv(ic, &ptr_in, &mybufsz, &ptr_out, &mybufsz);
  iconv_close(ic);

  /* 文字コード変換された文字列を格納 */
//  printf("%d\n", strlen(str_out));
//  printf("%s\n", str_out);
  for (i=0;i<strlen(str_out);) {
//    printf("sjis=%x\n",str_out[i]);
    if (str_out[i] & 0x80) {
      sjis[spos] = str_out[i++] << 8;
      sjis[spos] = sjis[spos] + str_out[i++];
      spos++;
    } else {
      sjis[spos++] = str_out[i++];
    }
  }
  
  /* フォントファイルの指定(お好みで) */
  Fontx_init(fx,"./ILGH16XB.FNT","./ILGZ16XB.FNT"); // 16Dot Gothic
//  Fontx_init(fx,"./ILMH16XB.FNT","./ILMZ16XB.FNT"); // 16Dot Mincyo
//  Fontx_init(fx,"./ILGH24XB.FNT","./ILGZ24XB.FNT"); // 24Dot Gothic
//  Fontx_init(fx,"./ILGH32XB.FNT","./ILGZ32XB.FNT"); // 32Dot Gothic

  for (i=0;i<spos;i++) {
    printf("sjis[%d]=%x\n",i,sjis[i]);
    Fontx_getGlyph(fx,sjis[i],fonts,&pw,&ph); // SJIS -> Fontパターン
//    printf("pw=%d ph=%d\n",pw,ph);
    fpos=0;
    for (y=0;y<ph;y++) {
      printf("%02d",y);
      for (x=0;x<pw;x++) {
        if (fonts[fpos+x/8] & (0x80 >> (x % 8))) {
         printf("*");
        } else {
         printf(".");
        }
      }
      printf("\n");
      fpos=fpos+(pw+7)/8;
    }
  }

  return 0;
}

