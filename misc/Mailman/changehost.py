# Usage:
#
# bin/withlist -l -r changehost test-list list.example.org https://lists.example.org/mailman/
#

def changehost(mlist, hn, wpu):
    try:
        print 'changing host names'
	print 'old:'
	print mlist.host_name
	print mlist.web_page_url
	mlist.host_name= hn
	mlist.web_page_url= wpu
	print 'new:'
	print mlist.host_name
	print mlist.web_page_url
        mlist.Save()
    except NotAMemberError:
        print 'No address matched:', addr

