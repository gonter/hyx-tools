
/* ------------------------------------------------------------------------ */
#ifdef OBSOLETE /* 1995-12-21 13:20:30 */
  if (lps->HPS_parser_level == 1
      && ch == lps->HPS_minimization_char
      && lps->HPS_segment_length > 0
      && lps->HPS_white_spaces == 0
     )
  {
    is_minimization_begin= 1;
#ifdef PARSER_DEBUG
    printf ("is_minimization_begin\n");
#endif /* PARSER_DEBUG */
  }

  if (lps->HPS_parser_level == 0
      && lps->HPS_minimization_seen == 1
      && ch == lps->HPS_minimization_char
     )
  {
    is_minimization_end= 1;
#ifdef PARSER_DEBUG
    printf ("is_minimization_end\n");
#endif /* PARSER_DEBUG */
  }

  if (ch == lps->HPS_tag_open
      || (ch == lps->HPS_tag_close && lps->HPS_parser_level >= 1)
      || is_minimization_begin
      || is_minimization_end
      || ch == -1               /* end of SGML stream !! */
     )
  { /* finish latest SGML text segment */
#ifdef PARSER_DEBUG
    printf ("finish text segment\n");
#endif /* PARSER_DEBUG */

    if ((seg= hyx_mktx_segm (lps->HPS_segment, lps->HPS_segment_length))
        != (struct TEXT_SEGMENT *) 0)
    {
      if (!lps->HPS_text_alloc_flag)
      { /* create a text element if there was not already one */
#ifdef PARSER_DEBUG
        printf ("finish text element\n");
#endif /* PARSER_DEBUG */

        *lps->HPS_ptx= tt= hyx_mktx_elem (lps->HPS_parser_level);
        hyx_transfer_details (lps, tt);
        lps->HPS_ptxs= &tt->TE_text_segment;
        lps->HPS_ptx= &tt->TE_next;
        lps->HPS_tx_cnt++;
      }

      /* link newly created text segment into current text element */
      *lps->HPS_ptxs= seg;
      lps->HPS_ptxs= &seg->TSEG_next;
      lps->HPS_tx_cnt++;

#ifdef PARSER_DEBUG
      diag_display_markup (stdout, hpc, tt, 0, 0, 0);
#endif /* PARSER_DEBUG */
    }

    lps->HPS_segment_length= 0;
    lps->HPS_level_changed= 1;
    if (lps->HPS_parser_level == 0) tt= (struct TEXT_ELEMENT *) 0;
    if (ch == lps->HPS_tag_close && lps->HPS_parser_level > 0)
      lps->HPS_parser_level--;
    if (ch == lps->HPS_tag_open) lps->HPS_parser_level++;
    lps->HPS_white_spaces= 0;
    lps->HPS_minimization_seen= 0;

    if (is_minimization_begin)
    {
      lps->HPS_parser_level= 0;
      lps->HPS_minimization_seen= 1;
    }

    if (is_minimization_end)
    { /* the end of a minimized markup section is handled like  */
      /* a unnamed markup close tag.                            */
#ifdef PARSER_DEBUG
      printf ("finish text element and segment, insert tag end\n");
#endif /* PARSER_DEBUG */

      *lps->HPS_ptx= tt= hyx_mktx_elem_and_segm (hpc, "/", 1L, 1L, 1, 1);
      hyx_transfer_details (lps, tt);
      lps->HPS_ptxs= &tt->TE_text_segment;
      lps->HPS_ptx= &tt->TE_next;
      lps->HPS_tx_cnt++;
      lps->HPS_parser_level= 0;
      lps->HPS_minimization_seen= 0;
    }

#ifdef PARSER_DEBUG
  diag_display_markup (stdout, hpc, tt, 0, 0, 0);
  if (PARSER_DEBUG > 10)
  {
    printf ("TEXT_ELEMENT finished\n");
    printf ("END hyxp0002.c SGML parser ----------------------\n");
  }
#endif /* PARSER_DEBUG */

    return tt;
  }
  else
  { /* any text character */
#ifdef NOT_USED_NOW
    if (lps->HPS_segment_length == 0    /* at the beginning of the list,    */
        && lps->HPS_level_changed == 1  /* after a tag open or close,       */
        && (ch == ' '                   /* strip off white space characters */
            || ch == '\t'               /* but don't do that within a       */
            || ch == '\n'               /* segmented text block             */
           )
       )
    {
      /*******************
      fputc ('*', stdout);
      *******************/
      goto END;
    }
#endif /* NOT_USED_NOW */

    if (ch == ' ' || ch == '\t' || ch == '\n') lps->HPS_white_spaces++;

    if (lps->HPS_segment_length == 0)
    {
      if (lps->HPS_parser_level >= 1)
      {
        if (ch == '!')
        {
#ifdef PARSER_DEBUG
          printf ("declaration begin\n");
#endif /* PARSER_DEBUG */
          lps->HPS_element_type= TEt_declaration;
        }
        else
        {
#ifdef PARSER_DEBUG
          printf ("tag begin\n");
#endif /* PARSER_DEBUG */
          lps->HPS_element_type= TEt_tag;
        }
      }
      else
      {
#ifdef PARSER_DEBUG
        printf ("text begin\n");
#endif /* PARSER_DEBUG */
        lps->HPS_element_type= TEt_text;
      }
    }

    lps->HPS_level_changed= 0;
    lps->HPS_segment [lps->HPS_segment_length++]= (char) ch;
    lps->HPS_segment [lps->HPS_segment_length]= 0;

  }

#ifdef NOT_USED_NOW
END:
#endif

  return (struct TEXT_ELEMENT *) 0;
#endif /* OBSOLETE 1995-12-21 13:20:50 */
