/*
 *  include FILE <gg/csed.h>
 *
 *  Defintionen fuer DED 80/40-Zeichen Bildschirmeditor
 *  - prototypes
 *
 *  written:       1989 07 22
 *  latest update: 1995-10-26
 *
 */

#ifndef __GG_csed__
#define __GG_csed__

#define  DED_EXIT             0x0801
#define  DED_CUP              0x0802
#define  DED_CDOWN            0x0803
#define  DED_CLEFT            0x0804
#define  DED_CRIGHT           0x0805
#define  DED_HOME             0x0806
#define  DED_END              0x0807
#define  DED_FIELD_CREATE     0x0810
#define  DED_FIELD_TOGGLE     0x0811
#define  DED_FIELD_DELETE     0x0812
#define  DED_FIELD_SHORT      0x0813
#define  DED_FIELD_ATTRIBUTE  0x0814
#define  DED_FIELD_DEFAULT_1  0x0815
#define  DED_FIELD_DEFAULT_2  0x0816
#define  DED_FIELD_REPEAT     0x0817
#define  DED_FIELD_TYPE       0x0818
#define  DED_FIELD_OFFSET     0x0819
#define  DED_FIELD_FWD        0x0880
#define  DED_FIELD_BWD        0x0881
#define  DED_FIELD_TYPEAHEAD  0x0882
#define  DED_FIELD_REEDIT     0x0883
#define  DED_FIELD_CLR        0x0884
#define  DED_FIELD_LENGTH     0x0885
#define  DED_FIELD_SINGLE     0x0886
#define  DED_FIELD_ATTR2      0x0887
#define  DED_FIELD_FORMAT     0x0888
#define  DED_FIELD_HELP       0x0889
#define  DED_COLOR_FOREGROUND 0x0820
#define  DED_COLOR_BACKGROUND 0x0821
#define  DED_COLOR_BLINK_HELL 0x0822
#define  DED_COLOR_SCREEN     0x0823
#define  DED_COLOR_BORDER     0x0824
#define  DED_COLOR_DEL_BORDER 0x0825
#define  DED_REFRESH          0x0830
#define  DED_STATUS_TOGGLE    0x0831
#define  DED_BLOCK_BEGIN      0x0840
#define  DED_BLOCK_END        0x0841
#define  DED_BLOCK_DO         0x0842
#define  DED_DBOX_R           0x0843
#define  DED_DBOX_D           0x0844
#define  DED_DBOX_L           0x0845
#define  DED_DBOX_U           0x0846
#define  DED_SBOX_R           0x0847
#define  DED_SBOX_D           0x0848
#define  DED_SBOX_L           0x0849
#define  DED_SBOX_U           0x0850
#define  DED_CBOX_R           0x0851
#define  DED_CBOX_D           0x0852
#define  DED_CBOX_L           0x0853
#define  DED_CBOX_U           0x0854
#define  DED_INS_TOGGLE       0x0860
#define  DED_DEL_LEFT         0x0861
#define  DED_DEL_RIGHT        0x0862
#define  DED_DEL_OBJECT       0x0863
#define  DED_MOVE_OBJECT      0x0864
#define  DED_MARK             0x0865
#define  DED_RETURN           0x0866
#define  DED_CUT              0x0867
#define  DED_PASTE            0x0868
#define  DED_COMPILE          0x0869

/* Beschraenkungen: ------------------------------------------------------- */
#define M_FLDB       1700       /* .    .       .   Field     .             */
#define M_SO          200               /* max. Anz der Screen Objekte      */
#define M_FO    M_FLDB/FLD_size         /* .    .   . Fields                */
#define M_FLD          30               /* .    .   . Menue/FR- Selections  */

/* KEYS: Names       Values   Alias                  */
#define K_EXIT       0x0141
#define K_CUT        0x012E
#define K_PASTE      0x0119
#define K_INDEX      0x0117
#define K_DOC        0x0120
#define K_HARD       0x0007   /* Hardcopy            */

#define SIG(x) (x)
#define POS(x) ((x)&0x00FF)

/* prototypes: ------------------------------------------------------------ */
void cdecl alt_field (char *f, int cx, int cy);
void cdecl w_print_int (int p, int x, int y, int attr, char *fmt, int val);

int cdecl col_8040_ed (char *fr_name, char s [], char f [], int  flag);
void cdecl display_f (char *s);
void cdecl DED_rst (void);

int cdecl synt_sync (FILE *fi, char *struct_name, char *fr_name);
int cdecl synt_data (FILE *fi, char data [], int flg);

void cdecl set_comp_option (int opt);
int cdecl open_comp_file (char *name, char *mode, int flg);
void cdecl close_comp_file (void);
int cdecl comp_screen (char *fr_name, char *data);
int cdecl comp_fields (char *fr_name, char *data);
int cdecl comp_fk (char *fr_name, char *data);
void cdecl comp_comment (char *fr_name);

int cdecl comp_data (FILE *comp_file, char *data, char *pfx,
                     char *fr_name, int hex, int neun_neun_neun);

#endif /* __GG_csed__ */
