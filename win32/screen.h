#ifndef __SCREEN_H__
#define __SCREEN_H__

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    int    width;
    int    height;
    int    stride;
    void  *pdata;
    void (*create )(void *pb);
    void (*destroy)(void *pb, int flags);
    void (*lock   )(void *pb, int x1, int y1, int x2, int y2);
    void (*unlock )(void *pb);
    int    closed;
    int    reserved[4];
} BMP;

void bitmap_create (BMP *pb, int w, int h);
void bitmap_destroy(BMP *pb, int flags);
void bitmap_lock   (BMP *pb, int x1, int y1, int x2, int y2);
void bitmap_unlock (BMP *pb);
int  bitmap_show   (BMP *pb);

unsigned get_tick_count(void);

extern BMP SCREEN;
extern BMP WINDOW;

#ifdef __cplusplus
}
#endif

#endif
