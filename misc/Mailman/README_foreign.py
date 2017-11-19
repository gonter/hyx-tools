$Id: README_foreign.py,v 1.1 2017/09/11 12:11:49 gonter Exp $

==foreign.py==

The module foreign.py can be used in a Mailman installation in the
Cgi directory to allow other (foreign) applications to authenticate
address/password pairs against a certain mailman list.  This may
be useful if a website needs to restrict access based on the memberhip
of a certain mailman list.


===installation===
* put foreign.py into ~mailman/Mailman/Cgi
* add a configuration clause to mm_cfg.py
* install a wrapper in cgi-bin, e.g. by patching an appropriate wrapper;
<pre>
cp private foreign
perl -pi.bak -e 's/private/foreign/g;' foreign
</pre>


===configuration===
In mm_cfg.py 
# Foreign Authentication Applications
FAA = {
  'x1': { 'list': 'test', 'code': 'testsecretcode', 'dt': 3600, 'rf': 'php/1' },
}

===TODO===
* add code to build the wrapper script
* provide more information...


