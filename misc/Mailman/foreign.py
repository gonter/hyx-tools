# Copyright (C) 1998-2006 by the Free Software Foundation, Inc.
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License
# as published by the Free Software Foundation; either version 2
# of the License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301,
# USA.
#
# $Id: foreign.py,v 1.1 2006/12/15 11:42:53 gonter Exp $

"""Provide a password-interface wrapper around private archives."""

import os
import sys
import cgi
import mimetypes
import md5
import time

from Mailman import mm_cfg
from Mailman import Utils
from Mailman import MailList
from Mailman import Errors
from Mailman import i18n
from Mailman.htmlformat import *
from Mailman.Logging.Syslog import syslog

# Set up i18n.  Until we know which list is being requested, we use the
# server's default.
_ = i18n._
i18n.set_language(mm_cfg.DEFAULT_SERVER_LANGUAGE)

SLASH = '/'



def true_path(path):
    "Ensure that the path is safe by removing .."
    # Workaround for path traverse vulnerability.  Unsuccessful attempts will
    # be logged in logs/error.
    parts = [x for x in path.split(SLASH) if x not in ('.', '..')]
    return SLASH.join(parts)[1:]



def guess_type(url, strict):
    if hasattr(mimetypes, 'common_types'):
        return mimetypes.guess_type(url, strict)
    return mimetypes.guess_type(url)



def main():
    # print 'Content-type: text/plain\n\n'
    print 'Content-type: text/plain; charset=us-ascii\n'

    doc = Document()
    doc.set_language(mm_cfg.DEFAULT_SERVER_LANGUAGE)

    parts = Utils.GetPathPieces()
    if not parts:
        doc.SetTitle(_("Private Archive Error"))
        doc.AddItem(Header(3, _("You must specify a list.")))
        print doc.Format()
        return

    path = os.environ.get('PATH_INFO')
    tpath = true_path(path)
    if tpath <> path[1:]:
        msg = _('Private archive - "./" and "../" not allowed in URL.')
        doc.SetTitle(msg)
        doc.AddItem(Header(2, msg))
        print doc.Format()
        syslog('mischief', 'Private archive hostile path: %s', path)
        return
    # BAW: This needs to be converted to the Site module abstraction
    true_filename = os.path.join(
        mm_cfg.PRIVATE_ARCHIVE_FILE_DIR, tpath)

    listname = parts[0].lower()

    try:
        mlist = MailList.MailList(listname, lock=0)
    except Errors.MMListError, e:
        # Avoid cross-site scripting attacks
        safelistname = Utils.websafe(listname)
        msg = _('No such list <em>%(safelistname)s</em>')
        doc.SetTitle(_("Private Archive Error - %(msg)s"))
        doc.AddItem(Header(2, msg))
        print doc.Format()
        syslog('error', 'No such list "%s": %s\n', listname, e)
        return

    i18n.set_language(mlist.preferred_language)
    doc.set_language(mlist.preferred_language)

    cgidata = cgi.FieldStorage()
    ai = cgidata.getvalue('ai', '')
    ad = cgidata.getvalue('ad', '')
    ts = cgidata.getvalue('ts', '')
    hc = cgidata.getvalue('hc', '')
    dx = cgidata.getvalue('dx', '')

    if ai=='' or ad=='' or ts=='' or hc=='':
      return

    try:
      papp= mm_cfg.FAA[ai]
    except:
      return

    now= time.time()
    dt= abs(now-int(ts))

    if dx == 'true':
      print 'listname=%s' % listname
      print 'ad=%s' % ad
      print 'ai=%s' % ai
      print ' ts=%s' % ts
      print 'now=%s' % now
      print ' dt=%s' % dt
      print papp
      print mlist

    if dt > papp['dt']:
      return

    if papp['list'] != listname:
      # list names not matching
      return

    try:
      password= mlist.getMemberPassword(ad)
    except:
      return

    code= papp['code']

    ## print 'password=%s' % password
    hs= SLASH.join ((ad, ts, password, code))
    md5s= md5.new(hs).hexdigest()

    if dx == 'true':
      print 'code=%s' % code
      print 'hs=%s' % hs
      print 'md5s=%s' % md5s

    if md5s != hc:
      return

    if papp['rf'] == 'php/1':
      print '<?php\n$MM_AUTH=true;\n?>'
    else:
      print 'passt so...'

