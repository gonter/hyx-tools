/*
 *  FILE %ned/00/ned0002.c
 *
 *  table of ned's primitive names
 *
 *  written:       1987 03 21
 *                 1988 ?? ??: Kommando System (fuer Setup)
 *                 1989 04 23: Maus Menu System
 *  latest update: 2001-02-11 12:42:17
 *  $Id: ned0002.c,v 1.4 2001/02/12 00:03:15 gonter Exp $
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#define __NED_proto__
#include "proto.h"

#include "ned0009.c"    /* Deklaration der primitiven Funktionen            */

#ifndef MSDOS
#define cdecl
#endif

/* ------------------------------------------------------------------------ */
#ifdef JUNK
static int cdecl yy (void);
static int yy () { return 0; }          /* Dummyfunktion */
#endif

/* see also: other NED Tcl commands */
/* ------------------------------------------------------------------------ */
struct NED_PRIMITIVES NED_PRIMITIVE_TABLE [] =
{
  { "insert",                           p_ins                               },
  { "tabulate",                         tabulate                            },
  { "split_join",                       p_split_join                        },
  { "cursor_up",                        ned_cursor_up                       },
  { "cursor_down",                      ned_cursor_down                     },
  { "cursor_left",                      ned_cursor_left                     },
  { "cursor_right",                     ned_cursor_right                    },
  { "word_left",                        p_word_left                         },
  { "word_right_beg",                   p_word_right_beg                    },
  { "word_right_end",                   p_word_right_end                    },
  { "page_down",                        ned_page_down                       },
  { "page_up",                          ned_page_up                         },
  { "half_page_down",                   ned_half_page_down                  },
  { "half_page_up",                     ned_half_page_up                    },
  { "delete_char_right",                ned_del_char_right                  },
  { "delete_char_left",                 ned_del_char_left                   },
  { "delete_line",                      ned_delete_line                     },
  { "turn_line",                        p_turn_line                         },
  { "scroll_up",                        p_upscr                             },
  { "scroll_down",                      p_dnscr                             },
  { "delete_word",                      ned_delete_word                     },
  { "new_line",                         p_nl                                },
  { "break_line",                       p_nl2                               },
  { "first_or_last",                    p_ax_lng                            },
  { "refresh",                          p_refresh                           },
  { "refresh_all",                      p_refresh_all                       },
  { "jump_to_window",                   p_jmpwdw                            },
  { "pushpage",                         p_pushpage                          },
  { "load_old_version",                 p_fget                              },
  { "save_reload",                      p_save_reload                       },
  { "open_file_in_context",             p_ofile1                            },
  { "open_file",                        p_ofile2                            },
  { "wdwqfile",                         p_wdwqfile                          },
  { "abandon",                          p_abandon                           },
  { "qabandon",                         p_qabandon                          },
  { "rename_object",                    ned_rename_object                   },
  { "rename_and_save",                  ned_rename_and_save                 },
  { "link",                             p_link                              },
  { "unlink",                           p_unlink                            },
  { "save",                             p_save                              },
  { "ssave",                            p_ssave                             },
  { "sx",                               p_sx                                },
  { "pr_jump_to_line",                  ned_pr_jump_to_line                 },
  { "top",                              pq_up                               },
  { "bot",                              pq_dn                               },
  { "del2eoln",                         ned_del2eoln                        },
  { "aitoggle",                         p_aitoggle                          },
  { "rdsetup",                          p_rdsetup                           },
  { "edsetup",                          p_edsetup                           },
  { "blkbeg",                           p_blkbeg                            },
  { "blkend",                           p_blkend                            },
  { "hideblk",                          p_hideblk                           },
  { "ned_blk_mode",                     ned_blk_mode                        },
  { "ovins",                            p_ovins                             },
  { "ww",                               p_ww                                },
  { "block_copy",                       ned_blk_copy                        },
  { "block_move",                       ned_blk_move                        },
  { "block_delete",                     ned_blk_delete                      },
  { "block_iconify",                    ned_blk_iconify                     },
  { "block_read",                       ned_blk_read                        },
  { "block_write",                      ned_blk_write                       },
  { "block_append",                     ned_blk_append                      },
  { "block_print",                      ned_blk_print                       },
  { "jmp_boln",                         ned_jmp_boln                        },
  { "jml_eoln",                         ned_jmp_eoln                        },
  { "vi_jmp_boln",                      vi_jmp_boln                         },
  { "vi_jmp_prev_boln",                 vi_jmp_prev_boln                    },
  { "vi_jmp_next_boln",                 vi_jmp_next_boln                    },
  { "clone_window",                     p_clone_window                      },
  { "colornxt",                         p_colornxt                          },
  { "backcolnxt",                       p_backcolnxt                        },
  { "window_menu",                      p_window_menu                       },
  { "wdwfaecher",                       p_wdwfaecher                        },
  { "open_jou_rd",                      p_open_jou_rd                       },
  { "open_jou_wr",                      p_open_jou_wr                       },
  { "close_jou",                        p_close_jou                         },
  { "wdwopen",                          p_wdwopen                           },
  { "close_window",                     ned_close_window                    },
  { "wdwsize",                          p_wdwsize                           },
  { "ned_exit",                         p_exit                              },
  { "pico_exit",                        ned_pico_exit                       },
  { "insblk",                           p_insblk                            },
  { "ultra_panic",                      p_ultra_panic                       },
  { "feature_next",                     p_feature_next                      },
  { "feature_prev",                     p_feature_prev                      },
  { "feature_range",                    p_feature_range                     },
  { "feature_set",                      p_feature_set                       },
  { "feature_reset",                    p_feature_reset                     },
  { "link_feature",                     p_link_feature                      },
  { "show_author",                      ned_show_author                     },
  { "find",                             p_find                              },
  { "replace",                          p_replace                           },
  { "fr_next",                          p_fr_next                           },
  { "jmblkbeg",                         p_jmp_blkbeg                        },
  { "jmblkend",                         p_jmp_blkend                        },
  { "alt_minus",                        p_alt_minus                         },
  { "alt_gleich",                       p_alt_gleich                        },
  { "insert_null_char",                 p_alt_zero                          },
  { "line_end_MAC",                     ned_line_end_MAC                    },
  { "line_end_MSDOS",                   ned_line_end_MSDOS                  },
  { "line_end_UNIX",                    ned_line_end_UNIX                   },
  { "find_matching_bracket",            p_find_matching_bracket             },
  { "find_higher_bracket",              p_find_higher_bracket               },
  { "find_lower_bracket",               p_find_lower_bracket                },
  { "eval_str",                         ned_eval_str                        },
  { "eval_block",                       ned_eval_block                      },
  { "eval_feature",                     ned_eval_feature                    },
  { "cross_ref",                        p_cross_ref                         },
  { "link_more",                        p_link_more                         },
  { "logic_link_more",                  p_logic_link_more                   },
#ifdef __NOT_USED__ /* 1998-08-15 18:24:06 */
  { "cl0",                              p_activate_cl0                      },
  { "start",                            p_activate_cl0                      },
  { "cl1",                              p_activate_cl1                      },
  { "help",                             p_activate_cl1                      },
  { "cl2",                              p_activate_cl2                      },
  { "cl3",                              p_activate_cl3                      },
  { "cl4",                              p_activate_cl4                      },
  { "notes",                            p_activate_cl4                      },
#endif /* __NOT_USED__ 1998-08-15 18:24:06 */
  { "activate_crf",                     p_activate_crf                      },
  { "activate_cl_fr",                   ned_p_activate_cl_fr                },
  { "activate_fr_root",                 p_activate_fr_root                  },
  { "activate_fr_notes",                p_activate_fr_notes                 },
  { "activate_fr_help",                 p_activate_fr_help                  },
  { "logic_link_next",                  p_logic_link_next                   },
  { "logic_link_prev",                  p_logic_link_prev                   },
  { "logic_link_menu",                  p_logic_link_menu                   },
  { "logic_link_up",                    p_logic_link_up                     },
  { "logic_link",                       p_logic_link                        },
  { "logic_link_lang",                  p_logic_link_lang                   },
  { "logic_link_sort",                  p_logic_link_sort                   },
  { "logic_link_view",                  p_logic_link_view                   },
  { "mac_define",                       p_mac_define                        },
  { "memorize_location",                ned_memorize_location               },
  { "forget_location",                  ned_forget_location                 },
  { "pfile",                            p_pfile                             },
  { "vi_ins",                           vi_ins                              },
  { "vi_ovr",                           vi_ovr                              },
  { "vi_bell",                          vi_bell                             },
  { "vi_ex",                            vi_ex                               },
  { "vi_dkey",                          vi_dkey                             },
  { "vi_append",                        vi_append                           },
  { "vi_append_eol",                    vi_append_eol                       },
  { "vi_insert_bol",                    vi_insert_bol                       },
  { "vi_insert_before_line",            vi_insert_before_line               },
  { "vi_insert_after_line",             vi_insert_after_line                },
  { "vi_repeat_last_command",           vi_repeat_last_command              },
  { "change_2eoln",                     vi_change_2eoln                     },
  { "change_line",                      vi_change_line                      },
  { "vi_join",                          vi_join                             },
  { "toggle_case",                      p_toggle_case                       },
  { "set_mark",                         ned_set_mark                        },
  { "set_lookup_tag",                   ned_set_lookup_tag                  },
  { "set_lookup_tag_fr",                ned_set_lookup_tag_fr               },
  { "set_hyx_l",                        ned_set_hyx_l                       },
  { "set_SGML_tag",                     ned_set_SGML_tag                    },
  { "set_SGML_entity",                  ned_set_SGML_entity                 },
  { "read_entity",                      ned_read_entity                     },
  { "tag_disp_normal",                  p_show_tag_normally                 },
  { "tag_disp",                         p_show_tag                          },
  { "tag_disp_full",                    p_show_full_tag                     },
  { "reload_sgml",                      ned_reload_sgml                     },
  { "reload_ascii",                     ned_reload_ascii                    },
  { "format_SGML",                      p_format_SGML                       },
  { "format_ASCII",                     p_format_ASCII                      },
  { "pico",                             pico_mode                           },
  { "WordStar",                         wordstar_mode                       },
  { "vi_mode",                          vi_mode                             },
  { "paste_file_name",                  ned_paste_file_name                 },
  { "paste_user",                       ned_paste_user                      },
  { "paste_date",                       ned_paste_date                      },
  { "paste_date_time",                  ned_paste_date_time                 },
  { "paste_date_string",                ned_paste_date_string               },
  { "paste_seconds",                    ned_paste_seconds                   },
  { "paste_renamed_object",             ned_paste_renamed_object            },
  { "group_set_marker",                 ned_group_set_marker                },

  /*** unneeded ??? ***/
  { "subprocessor_q",                   p_ctrlq                             },
  { "subprocessor_k",                   p_ctrlk                             },
  { "subprocessor_o",                   p_ctrlo                             },
  { "subprocessor_u",                   p_ctrlu                             },
  { "subprocessor_w",                   p_ctrlw                             },
  /*** unneeded ??? ***/

#ifdef USE_TK
  { "import_selection",                 ned_tk_import_selection             },
  { "withdraw_current_window",          ned_tk_aw_withdraw                  },
  { "save_withdraw_current_window",     ned_tk_aw_save_withdraw             },
  { "iconify_current_window",           ned_tk_aw_iconify                   },
  { "deiconify_current_window",         ned_tk_aw_deiconify                 },
#endif /* USE_TK */

  { (char *) 0,                         (ned_primitive *) 0                 }
} ;
