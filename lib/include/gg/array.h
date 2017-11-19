/*
 *  include FILE <gg/array.h>
 *
 *  written:       1996-08-11
 *  latest update: 1997-03-30 10:05:53
 *
 */

#ifndef __GG_array__
#define __GG_array__

/* arbitrary limits: ------------------------------------------------------ */
#define MAX_ARRAY_SPLIT 50      /* max. number of elements to split array   */

/* ------------------------------------------------------------------------ */
typedef void array_element_destructor (void *payload);

/* ------------------------------------------------------------------------ */
struct ARRAY_ELEMENT
{
  struct ARRAY_ELEMENT *next;
  struct ARRAY_ELEMENT *prev;
  void *payload;
} ;

/* ------------------------------------------------------------------------ */
struct ARRAY_CONTROL
{
  struct ARRAY_ELEMENT *top;
  struct ARRAY_ELEMENT *last;

  long elements;
  array_element_destructor *element_destructor;
} ;

/* ------------------------------------------------------------------------ */
#define array_elements(x) (x->elements)
#define array_last_index(x) (x->elements-1)

#define array_new() \
  ((struct ARRAY_CONTROL *) calloc (sizeof (struct ARRAY_CONTROL), 1))
#define array_new_element() \
  ((struct ARRAY_ELEMENT *) calloc (sizeof (struct ARRAY_ELEMENT), 1))

#define array_top(x) \
  ((x == (struct ARRAY_CONTROL *) 0) ? (struct ARRAY_ELEMENT *) 0 : x->top)
#define array_last(x) \
  ((x == (struct ARRAY_CONTROL *) 0) ? (struct ARRAY_ELEMENT *) 0 : x->last)

#define array_next(x) \
  ((x == (struct ARRAY_ELEMENT *) 0) ? (struct ARRAY_ELEMENT *) 0 : x->next)
#define array_prev(x) \
  ((x == (struct ARRAY_ELEMENT *) 0) ? (struct ARRAY_ELEMENT *) 0 : x->prev)

/* ------------------------------------------------------------------------ */
int array_dispose (struct ARRAY_CONTROL *ac);

long array_push (struct ARRAY_CONTROL *ac, void *pl);
long array_unshift (struct ARRAY_CONTROL *ac, void *pl);
void *array_pop (struct ARRAY_CONTROL *ac);
void *array_shift (struct ARRAY_CONTROL *ac);

long array_push2 (struct ARRAY_CONTROL **ac, void *pl);
long array_unshift2 (struct ARRAY_CONTROL **ac, void *pl);
long array_push2_dup (struct ARRAY_CONTROL **ac, char *pl);
int array_dispose2 (struct ARRAY_CONTROL *ac, array_element_destructor *ad);
int array_dispose_string (struct ARRAY_CONTROL *ac);

int string_push (char *fn);
int string_unshift (char *fn);
char *string_pop (void);
char *string_shift (void);
void string_reset (void);

struct ARRAY_CONTROL *array_append_split_destructive (
  struct ARRAY_CONTROL *ac, char *str, int split_char, int max_fields);

char *array_join (struct ARRAY_CONTROL *ac, char *out_str, int out_size,
  char *conc_str);

struct ARRAY_CONTROL *array_dup_tmp (struct ARRAY_CONTROL *ac);

#ifdef __T2D__ /* 1997-01-15 17:44:46 */
struct ARRAY_CONTROL *array_split (string, split_char);
struct ARRAY_CONTROL *array_isolate_tokens (string);
array_reverse
... udgl ...

#endif /* __T2D__ 1997-01-15 17:44:46 */

#endif /* __GG_array__ */
