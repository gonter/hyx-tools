/*
 *  include FILE <gg/ccscan.h>
 *
 *  Spezielle Defintionen fuer den C-Compiler - Scanner
 *
 *  written:       1987 11 14
 *                 1990 07 10: Revision
 *  latest update: 1997-08-15 19:29:36
 *
 */

#ifndef __GG_ccscan__
#define __GG_ccscan__

#include <gg/floskel.h>

/* ------------------------------------------------------------------------ */
typedef void CC_SCAN_OUTPUT (int tv, long val);

/* ------------------------------------------------------------------------ */
struct CC_C_SCANNER
{
  struct CC_SCANNER *CC_sc_cc;
  struct CC_SCANNER *CC_sc_cpp;

  CC_SCAN_OUTPUT *CC_sc_cc_output;
  CC_SCAN_OUTPUT *CC_sc_cpp_output;

  /* Zustandsparameter des Scanners */
  int CC_fl_val2;               /* akt. Float-Nachkomma-Wert                */
  int CC_fl_val3;               /* akt. Float-Exponent-Wert                 */
  int CC_fl_evz;                /* akt. Float-Exponent-Vorzeichen           */
  int CC_chv;                   /* akt. Character-Wert                      */
  int CC_idx;                   /* Index des Names bzw. Strings             */
  long CC_value;                /* akt. Integer-Wert                        */
  char CC_id [500];             /* Identifier und String Puffer             */
  char CC_int_token;            /* Unterscheidung: DEZ - HEX - OKT          */
} ;

/* Lexikalische Tokens: --------------------------------------------------- */
#define TOK_DEZ          1
#define TOK_FLOAT        2
#define TOK_CHAR         3
#define TOK_STR          4
#define TOK_ID           5
#define TOK_HEX          6
#define TOK_OKT          7

#define TOK_DELI        10      /* CR, BLANK, TAB ...           */
#define TOK_COMMENT     11      /* Kommentare f. Beautifier     */

#define TOK_SEL         14
#define TOK_DEREFF      15
#define TOK_Lor         16
#define TOK_Land        17
#define TOK_DEC         18
#define TOK_INC         19

#define TOK_Band        20
#define TOK_aBand       21
#define TOK_Bor         22
#define TOK_aBor        23
#define TOK_MOD         24
#define TOK_aMOD        25
#define TOK_DIV         26
#define TOK_aDIV        27
#define TOK_MUL         28
#define TOK_aMUL        29
#define TOK_ADD         30
#define TOK_aADD        31
#define TOK_SUB         32
#define TOK_aSUB        33
#define TOK_XOR         34
#define TOK_aXOR        35
#define TOK_COMPL       36
#define TOK_aCOMPL      37
#define TOK_assign      38

#define TOK_EQ          39
#define TOK_LT          40
#define TOK_LE          41
#define TOK_GT          42
#define TOK_GE          43
#define TOK_not         44
#define TOK_NE          45

#define TOK_Lshift      46
#define TOK_aLshift     47
#define TOK_Rshift      48
#define TOK_aRshift     49

#define TOK_BACK        50
#define TOK_ASK         51
#define TOK_COL         52
#define TOK_HASH        53
#define TOK_KOMMA       54
#define TOK_SEMICOL     55
#define TOK_56          56
#define TOK_57          57
#define TOK_58          58
#define TOK_59          59
#define TOK_60          60
#define TOK_61          61

#define TOK_FNM1        62     /* Include File Name mit Anfuehrungsz. */
#define TOK_FNM2        63     /* .       .    .    .   <..>          */

/* Reservierte Identifier: ------------------------------------------------ */
#define ID_asm          1
#define ID_auto         2
#define ID_break        3
#define ID_case         4
#define ID_char         5
#define ID_const        6
#define ID_continue     7
#define ID_default      8
#define ID_do           9
#define ID_double      10
#define ID_else        11
#define ID_entry       12
#define ID_enum        13
#define ID_extern      14
#define ID_float       15
#define ID_for         16
#define ID_fortran     17
#define ID_goto        18
#define ID_if          19
#define ID_int         20
#define ID_long        21
#define ID_pascal      22
#define ID_register    23
#define ID_return      24
#define ID_short       25
#define ID_sizeof      26
#define ID_static      27
#define ID_struct      28
#define ID_switch      29
#define ID_typedef     30
#define ID_union       31
#define ID_unsigned    32
#define ID_void        33
#define ID_while       34

/* CPP - Identifier duerfen auch als normale Identifier */
/* verwendet werden !!                                  */
#define ID_define      35
#define ID_undef       36
#define ID_include     37
#define ID_ifdef       38       /* if ... auch normales C !! */
#define ID_ifndef      39
/* #define ID_else        40   .... ^^^^^ */
#define ID_endif       41
#define ID_line        42
#define ID_file        43

/* Erweiterungen: (ZORLAND) ----------------------------------------------- */
#define ID_volatile    44
#define ID_message     45

/* IDENTIFIER FLAGS: ------------------------------------------------------ */
#define ID_SYN     0x8000       /* ID == Syntaktisches Symbol         */
#define ID_CPP     0x4000       /* ID == Symbol fuer CPP              */
#define ID_RSV     0xC000       /* ID == Syntakt. | CPP oder beides   */
#define ID_nFL     0x3FFF       /* Flags ausmaskieren                 */

/* Debugging: ------------------------------------------------------------- */
#ifdef  QQ_scann
static char *qq_token [] =
{
  "undef00",    "TOK_DEZ",    "TOK_FLOAT",  "TOK_CHAR",   "TOK_STR",
  "TOK_ID",     "TOK_HEX",    "TOK_OKT",    "undef08",    "undef09",
  "TOK_DELI",   "TOK_COMMENT","undef12",    "undef13",    "TOK_SEL",
  "TOK_DEREFF", "TOK_Lor",    "TOK_Land",   "TOK_DEC",    "TOK_INC",
  "TOK_Band",   "TOK_aBand",  "TOK_Bor",    "TOK_aBor",   "TOK_MOD",
  "TOK_aMOD",   "TOK_DIV",    "TOK_aDIV",   "TOK_MUL",    "TOK_aMUL",
  "TOK_ADD",    "TOK_aADD",   "TOK_SUB",    "TOK_aSUB",   "TOK_XOR",
  "TOK_aXOR",   "TOK_COMPL",  "TOK_aCOMPL", "TOK_assign", "TOK_EQ",
  "TOK_LT",     "TOK_LE",     "TOK_GT",     "TOK_GE",     "TOK_not",
  "TOK_NE",     "TOK_Lshift", "TOK_aLshift","TOK_Rshift", "TOK_aRshift",
  "TOK_BACK",   "TOK_ASK",    "TOK_COL",    "TOK_HASH",   "TOK_KOMMA",
  "TOK_SEMICOL","TOK_56",     "TOK_57",     "TOK_58",     "TOK_59",
  "TOK_60",     "TOK_61",     "TOK_FNM1",   "TOK_FNM2"
} ;

static char *qq2_token [] =
{
  "<undef00>", "<DEZ>", "<FLOAT>", "<CHAR>", "<STR>", "<ID>",
  "<HEX>", "<OKT>", "<undef08>", "<undef09>", "\n",
  "/**/", "<undef12>", "<undef13>", ".", "->", "||", "&&",
  "--", "++", "&", "&=", "|", "|=", "%", "%=", "/", "/=", "*",
  "*=", "+", "+=", "-", "-=", "^", "^=", "~", "~=", "=", "==",
  "<", "<=", ">", ">=", "!", "!=", "<<", "<<=", ">>", ">>=",
  "\\", "?", ":", "#", ",", ";", "(", ")", "[", "]", "{", "}",
  "<FNM1>", "<FNM2>"
} ;
#endif /* QQ_scann */

/* Prototypes: ------------------------------------------------------------ */
int cc_define_output (CC_SCAN_OUTPUT *op);
struct CC_SCANNER *cc_c_init (void);

int cc_cppb_define_output (CC_SCAN_OUTPUT *op);
int cc_cpp_define_output (CC_SCAN_OUTPUT *op);
struct CC_SCANNER *cc_cpp_init (void);

int cc_cpp_Bdefine_output (CC_SCAN_OUTPUT *op);
void cc_cpp_Bscanner (int xch);
void cc_cpp_Binit (void);

/* cc_sc10.c */ struct CC_C_SCANNER *cc_init_c_parser (void);

/* cc.c */
int cc_process (struct CC_C_SCANNER *sc_xx, char *infile, int mode, int aznr);
void cc_set_scan (int i);
long cc_r_pos (void);

/* lex.c */
int get_action_code (struct IDENT *id);
int find_pair (int idx, int c_idx, int t_idx);
void lex_input (int tv, long val);
void cc_proc_tell (char *fmt, char *str, int z);

/* cppscan.c (redefinitions!) */
int cpAsi (int st);
int cpAsc (int xch);
void cpBsi (void);
void cpBsc (int xch);

/* scanner.c (functions redefined!!) */
int SC_init (int st);
int SC_scanner (int xch);

int digit (int chr);
int back_check (int chr);
#define ldigit(x) ((long) digit(x))

#define __CC_SCAN_ACTION__ void *_sc, int SC_ch, void *client_data

/* CPP-SCANNER-ACTIONS prototypes: ---------------------------------------- */
void cpp00 (__CC_SCAN_ACTION__);
void cpp01 (__CC_SCAN_ACTION__);
void cpp02 (__CC_SCAN_ACTION__);
void cpp03 (__CC_SCAN_ACTION__);
void cpp04 (__CC_SCAN_ACTION__);
void cpp05 (__CC_SCAN_ACTION__);
void cpp06 (__CC_SCAN_ACTION__);

/* C-SCANNER-ACTIONS prototypes: ------------------------------------------ */
void s_00 (__CC_SCAN_ACTION__);
void s_01 (__CC_SCAN_ACTION__);
void s_02 (__CC_SCAN_ACTION__);
void s_03 (__CC_SCAN_ACTION__);
void s_04 (__CC_SCAN_ACTION__);
void s_05 (__CC_SCAN_ACTION__);
void s_06 (__CC_SCAN_ACTION__);
void s_07 (__CC_SCAN_ACTION__);
void s_08 (__CC_SCAN_ACTION__);
void s_09 (__CC_SCAN_ACTION__);
void s_10 (__CC_SCAN_ACTION__);
void s_11 (__CC_SCAN_ACTION__);
void s_12 (__CC_SCAN_ACTION__);
void s_13 (__CC_SCAN_ACTION__);
void s_14 (__CC_SCAN_ACTION__);
void s_15 (__CC_SCAN_ACTION__);
void s_16 (__CC_SCAN_ACTION__);
void s_17 (__CC_SCAN_ACTION__);
void s_18 (__CC_SCAN_ACTION__);
void s_19 (__CC_SCAN_ACTION__);
void s_20 (__CC_SCAN_ACTION__);
void s_21 (__CC_SCAN_ACTION__);
void s_22 (__CC_SCAN_ACTION__);
void s_23 (__CC_SCAN_ACTION__);
void s_24 (__CC_SCAN_ACTION__);
void s_25 (__CC_SCAN_ACTION__);
void s_26 (__CC_SCAN_ACTION__);
void s_27 (__CC_SCAN_ACTION__);
void s_28 (__CC_SCAN_ACTION__);
void s_29 (__CC_SCAN_ACTION__);
void s_30 (__CC_SCAN_ACTION__);
void s_31 (__CC_SCAN_ACTION__);
void s_32 (__CC_SCAN_ACTION__);
void s_33 (__CC_SCAN_ACTION__);
void s_34 (__CC_SCAN_ACTION__);
void s_35 (__CC_SCAN_ACTION__);
void s_36 (__CC_SCAN_ACTION__);
void s_37 (__CC_SCAN_ACTION__);
void s_38 (__CC_SCAN_ACTION__);
void s_39 (__CC_SCAN_ACTION__);
void s_40 (__CC_SCAN_ACTION__);
void s_41 (__CC_SCAN_ACTION__);
void s_42 (__CC_SCAN_ACTION__);
void s_43 (__CC_SCAN_ACTION__);
void s_44 (__CC_SCAN_ACTION__);
void s_45 (__CC_SCAN_ACTION__);
void s_46 (__CC_SCAN_ACTION__);
void s_47 (__CC_SCAN_ACTION__);
void s_48 (__CC_SCAN_ACTION__);
void s_49 (__CC_SCAN_ACTION__);
void s_50 (__CC_SCAN_ACTION__);
void s_51 (__CC_SCAN_ACTION__);
void s_52 (__CC_SCAN_ACTION__);
void s_53 (__CC_SCAN_ACTION__);
void s_54 (__CC_SCAN_ACTION__);
void s_55 (__CC_SCAN_ACTION__);
void s_56 (__CC_SCAN_ACTION__);
void s_57 (__CC_SCAN_ACTION__);
void s_58 (__CC_SCAN_ACTION__);
void s_59 (__CC_SCAN_ACTION__);
void s_60 (__CC_SCAN_ACTION__);
void s_61 (__CC_SCAN_ACTION__);
void s_62 (__CC_SCAN_ACTION__);
void s_63 (__CC_SCAN_ACTION__);
void s_64 (__CC_SCAN_ACTION__);
void s_65 (__CC_SCAN_ACTION__);
void s_66 (__CC_SCAN_ACTION__);
void s_67 (__CC_SCAN_ACTION__);

#endif /* __GG_ccscan__ */
