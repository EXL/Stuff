#include <X11/Xlib.h>
#include <stdio.h>
#include <unistd.h>

const int kWidth = 1024;
const int kHeight = 600;
const unsigned long kBackground = 0xa0a0f0;
const unsigned long kForeground = 0x000000;
const int kDelay = 15000;

int main(void) {
  Display *dpy = XOpenDisplay(NULL);
  Window root_wnd = DefaultRootWindow(dpy);
  Window wnd = XCreateSimpleWindow(dpy, root_wnd, 0, 0, kWidth, kHeight, 0, 0,
                                   kBackground);

  XMapWindow(dpy, wnd);
  XSync(dpy, False);

  GC gcf = XCreateGC(dpy, wnd, GCForeground,
                     &(XGCValues){.foreground = kForeground});
  GC gcb = XCreateGC(dpy, wnd, GCForeground,
                     &(XGCValues){.foreground = kBackground});

  int frame = 0;
  while (1) {
    for (int x = 10; x < kWidth - 10; x += 10) {
      for (int y = 0; y < kHeight; y++) {
        XDrawLine(dpy, wnd, gcb, x - 10, y, x, y);
        XDrawLine(dpy, wnd, gcf, x, y, x + 10, y);
      }
      printf("\rframe %d ready", ++frame);
      fflush(stdout);
      usleep(kDelay);
    }

    for (int x = kWidth - 10; x > 10; x -= 10) {
      for (int y = 0; y < kHeight; y++) {
        XDrawLine(dpy, wnd, gcb, x, y, x + 10, y);
        XDrawLine(dpy, wnd, gcf, x - 10, y, x, y);
      }
      printf("\rframe %d ready", ++frame);
      fflush(stdout);
      usleep(kDelay);
    }
  }

  return 0;
}
