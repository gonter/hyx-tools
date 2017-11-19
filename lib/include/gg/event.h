/*
 *  include FILE <gg/event.h>
 *
 *  Definitionen fÅr Event-Handler
 *
 *  written:       1989 07 11
 *  latest update: 1995-10-26
 *
 */

#ifndef __GG_event__
#define __GG_event__

/* Return Values: EVENT_xxxx ---------------------------------------------- */
#define EVENT_key                      0x0001
#define EVENT_timeout                  0x0002
#define EVENT_mouse                    0x0003
#define EVENT_button                   0x0004
#define EVENT_field                    0x1001
#define EVENT_mmenu                    0x1002

/* Mask Values: ----------------------------------------------------------- */
#define EVENT_MASK_key                 0x0001
#define EVENT_MASK_timeout             0x0002
#define EVENT_MASK_mouse               0x0004
#define EVENT_MASK_button              0x0008

/* Modul %jeannie/event.c ------------------------------------------------- */
void cdecl INIT_event (void);
int get_event (int *key, int *x, int *y, int *timeout, int mask, int flg);
void cdecl wait_maus (void);

/* Modul %jeannie/ik3a.c -------------------------------------------------- */
unsigned int cdecl keymap_analyse (
int  key,               /* zu untersuchende Taste                           */
char fkt1 [],           /* globale und ...                                  */
char fkt2 []);          /* ... lokale Funktion Key Tabelle                  */
                        /* fkt2 wird mit hîherer PrioritÑt behandelt        */
/* RETURN: FR_UNDEF ... Zuordnung nicht gefunden                            */
/*         sonst    ... gefunden Zuordnung                                  */

/* Modul %jeannie/ik3b.c -------------------------------------------------- */
unsigned int cdecl get_entry (char *fkt, int akt);

/* Modul %jeannie/ik3c.c -------------------------------------------------- */
unsigned int cdecl get_2_entry (int fkt [], int akt);

/* Modul %jeannie/ik4.c --------------------------------------------------- */
int cdecl E_field_edit (char  field [],
                        char  desc [],
                        int   mode,
                        int   akt_page,
                        int   event_mask,
                        int  *key,
                        int  *timeout,
                        int  *x,
                        int  *y,
                        int  *update);

void cdecl E_show_field (char  field [],
                         char  desc [],
                         int   mode,
                         int   akt_page,
                         int   flag);

int cdecl E_scan_str (  int   p,
                        int   x,
                        int   y,
                        int   l,
                        int   attr,
                        int   event_mask,
                        char *pu,
                        int  *key,
                        int  *timeout,
                        int   flg);

int cdecl E_scan_int (  int   p,
                        int   x,
                        int   y,
                        int   l,
                        int   attr,
                        int   event_mask,
                        int  *val,
                        int  *key,
                        int  *timeout,
                        int   flg);

void cdecl E_set_cursor_offset (int cursor_off);
int  cdecl E_get_cursor_offset (void);

/* Modul %jeannie/maskedit.c ---------------------------------------------- */
int cdecl msk_edit (char ff [], char *dss [], int dmode, int *kv,
            int *timeout, int *x, int *y, int mask, int *update, int flgs);

void cdecl msk_set_fld (int fld);
int  cdecl msk_get_flg (void);

/* Modul %jeannie/complex.c ----------------------------------------------- */
int cdecl complex_screen (int *key, int *x, int *y, int *timeout,
            long *value, int mask, char *screen, char *fields,
            char *data [], char *buttons, struct  MMctrl *mmctrl,
            long aktivate, int aktivate_key);

int cdecl complex_update (void);

#endif /* __GG_event__ */
