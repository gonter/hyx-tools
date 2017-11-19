
#define W_MODEL_CGA
#include <gg/window.h>

main ()
{
  w_init_mode ((char *) 0, 5, 0x0001);
  wg_box (20, 20, 30, 30, 1);
  wg_fbox (40, 40, 50, 50, 2);
  wg_circle  (100, 100, 40, 0x82);
  wg_fcircle (200, 100, 40, 0x83);
  wg_fcircle (10, 10, 0, 1);
  wg_fbox (0, 0, 319, 199, 0x81);
}
