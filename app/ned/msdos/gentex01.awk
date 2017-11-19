BEGIN {
  print "\\documentstyle[lpr,appleps]{article}"
  print "\\pagestyle{myheadings}"
  print "\\parindent0mm"
  print "\\hbadness=20000"
  print "\\textwidth140mm"
  print "\\begin{document}"
  print "\\def\\LPtopA{{\\Large NED} --- {\\sl The Network Editor}}"
  print "\\pagenumbering{roman}"
  print "\\title{NED\\\\---\\\\The Network Editor}"
  print "\\author{Gerhard Gonter}\\date{\\today}\\maketitle"
  print "\\pagebreak[4]"
  print "\\tableofcontents"
  print "\\def\\LPtopB{Contents}"
  print "\\pagebreak[4]"
  print "\\pagenumbering{arabic}"
  print "\\setcounter{page}{1}"
  print "\\small\\tt"
}