awk stream2.awk %1.txt >%1
awk rfc2hyx.awk %1
copy/b tmp\@1.h + tmp\@1.t %1.hyx
hyxidx -i %1.hyx
