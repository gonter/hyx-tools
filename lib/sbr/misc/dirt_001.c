/*
 *  FILE /usr/sbr/dirt_001.c
 *
 *  1989 11 04
 *
 */

#pragma check_stack(off)
#pragma pack(1)

# define NEW_WAY

/* ------------------------------------------------------------------------ */
# ifdef  OLD_WAY
struct PATCH
{
  int qjump;
  int (*qadresse) ();
} ;

void patch (struct PATCH *a1, int (*a2) ())
{
  a1->qjump     = 0xEA90;      /* 90=NOP, EA=JUMP far */
  a1->qadresse  =     a2;
}
# endif

/* ------------------------------------------------------------------------ */
# ifdef  NEW_WAY
struct PATCH
{
  char qjump;
  char qa1, qa2, qa3, qa4;
} ;

void patch (register struct PATCH *p, int a1, int a2)
{
  p->qjump = 0xEA;      /* 90=NOP, EA=JUMP far */
  p->qa1   =  a1       & 0xFF;
  p->qa2   = (a1 >> 8) & 0xFF;
  p->qa3   =  a2       & 0xFF;
  p->qa4   = (a2 >> 8) & 0xFF;
}
#endif
