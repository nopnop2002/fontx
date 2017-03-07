#define FontxGlyphBufSize	(32*32/8)

typedef struct {
  const char *path;
  char  fxname[9];
  bool  opened;
  bool  valid;
  bool  is_ank;
  uint8_t w;
  uint8_t h;
  uint16_t fsz;
  uint8_t bc;
  FILE *file;
} FontxFile;

