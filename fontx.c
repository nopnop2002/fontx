#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "fontx.h"

void Fontx_dump(FontxFile *fxs)
{
  int i;
  for(i=0;i<2;i++) {
    printf("fxs[%d]->path=%s\n",i,fxs[i].path);
    printf("fxs[%d]->opened=%d\n",i,fxs[i].opened);
    printf("fxs[%d]->fxname=%s\n",i,fxs[i].fxname);
    printf("fxs[%d]->valid=%d\n",i,fxs[i].valid);
    printf("fxs[%d]->is_ank=%d\n",i,fxs[i].is_ank);
    printf("fxs[%d]->w=%d\n",i,fxs[i].w);
    printf("fxs[%d]->h=%d\n",i,fxs[i].h);
    printf("fxs[%d]->fsz=%d\n",i,fxs[i].fsz);
    printf("fxs[%d]->bc=%d\n",i,fxs[i].bc);
  }
}

void Fontx_addFont(FontxFile *fx, const char *path)
{
  memset(fx,0,sizeof(FontxFile));
  fx->path = path;
  fx->opened = false;
}

void Fontx_init(FontxFile *fxs,const char *f0,const char *f1)
{
  Fontx_addFont(&fxs[0],f0);
  Fontx_addFont(&fxs[1],f1);
}

bool Fontx_openFontxFile(FontxFile *fx)
{
  FILE *f;
  int i;

  if(!fx->opened){
    fx->opened = true;
    f = fopen(fx->path,"r");
    if(!f){
      fx->valid = false;
      printf("FsFontx:%s not found.\n",fx->path);
    } else {
      fx->file = f;
      char buf[18];

      fread(buf, sizeof buf, 1, fx->file);
//      for(i=0;i<sizeof(buf);i++) {
//        printf("buf[%d]=%x\n",i,buf[i]);
//      }
      memcpy(fx->fxname,&buf[6],8);
      fx->w = buf[14];
      fx->h = buf[15];
      fx->is_ank = (buf[16] == 0);
      fx->bc = buf[17];
      fx->fsz = (fx->w + 7)/8 * fx->h;
      if(fx->fsz > FontxGlyphBufSize){
	printf("too big font size.\n");
	fx->valid = false;
      } else {
	fx->valid = true;
      }
    }
  }
  return fx->valid;
}

void Fontx_closeFontxFile(FontxFile *fx)
{
  if(fx->opened){
    fclose(fx->file);
    fx->opened = false;
  }
}


bool Fontx_getGlyph (FontxFile *fxs, uint32_t sjis , uint8_t *pGlyph,
			uint8_t *pw, uint8_t *ph)
{
  
  int i;
//  FontxFile fx;
  long offset;
  int ret;

//  printf("sjis=%x %d\n",sjis,sjis);
  for(i=0; i<2; i++){
    if(!Fontx_openFontxFile(&fxs[i])) continue;
//    printf("openFontxFile[%d]\n",i);
    
    if(sjis < 0x100){
      if(fxs[i].is_ank){
//	printf("fxs.is_ank fxs.fsz=%d\n",fxs[i].fsz);
	offset = 17 + sjis * fxs[i].fsz;
//	printf("offset=%d\n",offset);
	if(fseek(fxs[i].file, offset, SEEK_SET)) {
  	  printf("Fontx::fseek(18) failed.\n");
	  return false;
        }
	if(fread(pGlyph, 1, fxs[i].fsz, fxs[i].file) != fxs[i].fsz){
	  printf("Fontx::fread failed.\n");
	  return false;
        }
	if(pw) *pw = fxs[i].w;
	if(ph) *ph = fxs[i].h;
	return true;
      }
    }
    else {
      if(!fxs[i].is_ank){
        if(fseek(fxs[i].file, 18, SEEK_SET)) {
  	  printf("Fontx::fseek(18) failed.\n");
	  return false;
        }
        uint16_t buf[2], nc = 0, bc = fxs[i].bc;
    
        while(bc--){ 
	  if(fread((char *)buf, 1, 4, fxs[i].file) != 4){
	    printf("Fontx::fread failed.\n");
	    return false;
	  }

//          printf("buf=%x %x\n",buf[0],buf[1]);
	  if(sjis >= buf[0] && sjis <= buf[1]) {
	    nc += sjis - buf[0];
	    uint32_t pos = 18 + fxs[i].bc * 4 + nc * fxs[i].fsz;
	    if(fseek(fxs[i].file, pos, SEEK_SET)) {
	      printf("FsFontx::seek(%u) failed.\n",pos);
	      return false;
	    }
	    if(fread(pGlyph, 1, fxs[i].fsz, fxs[i].file) != fxs[i].fsz){
	      printf("Fontx::fread failed.\n");
	      return false;
            }
	    if(pw) *pw = fxs[i].w;
	    if(ph) *ph = fxs[i].h;
	    return true;
	  }
	  nc += buf[1] - buf[0] + 1;
        }
      }
    }
  }
  return false;
}

