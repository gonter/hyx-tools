# Verzeichnis der Kommandos der HyperText Engine
#
# 1990 04 12
#
# ----------------------------------------------------------------------------
# Aufbau der Eintr„ge in diesem File:
#
# <code> <pars> <command>
#   ³      ³        ÀÄÄÄÄÄÄÄÄÄÄ Name des Kommandos
#   ³      ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ Mindestanzahl der Parameter
#   ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ OpCode fr die HyperText Maschine
#
# Class 0: -------------------------------------------------------------------
      1   0 help
# Class 1: -------------------------------------------------------------------
    101   1 cluster <clustername>
    102   1 frame <framename>
    103   0 delete
    104   0 undelete
    105   1 rename <new-framename>
    106   1 move <new-clustername>
    107   1 output <out-file>
    110   1 format core|raw|NED|text
    111   1 processor <processor-name>
# Class 2: -------------------------------------------------------------------
    201   1 attr <attributename> [<attributvalue>]
    202   1 delattr <attributename>
    203   0 touch
# Class 3: -------------------------------------------------------------------
    301   0 purge
    302   0 export
    303   1 import <in-file>
    304   1 string
# Class 4: -------------------------------------------------------------------
    401   0 list
    402   0 new
    499   0 quit
# Optionen: ------------------------------------------------------------------
   1301   0 core
   1302   0 raw
   1303   0 NED
   1304   0 text
