<?php

## This file has the code for the text area for entering the list of
## pages, plus instructions on top of that text area. It pre-populates
## the text area with the list of pages from a previous GET or POST
## request if any, otherwise leaves it blank. If on a follow-up page, it
## is collapsed in cases that the pages were specified through an
## alternate page specification method.

## Included in: onemonthdataentry.inc, multiplemonthsdataentry.inc, multipleyearsdataentry.inc

## Associated retrieval file: retrieval/pageListRetrieval.inc

if ($formdata == true and strlen(trim($pageListAsString," \t\n\r\0\x0B"))==0 and count($pageListAsArray) > 0)
  {
    print '<br><a id="displayText5" href="javascript:toggle5();">Show text area for manual page entry</a><br><br>';
    print '<div id="toggleText5" style="display: none">';
  }

if ($formdata == false) 
  { 
    print '<p><strong>Please list the
Wikipedia page names for which you want view count statistics
reported. Please enter one page name per line. Enter page names, not full URLs. You may also leave this blank and choose
one of the alternative methods of specifying lists of pages.</strong>
(more help below, and more background at the <a href="/about">about
page</a>)</p>';
  }
else
  {
    print '<p><strong>Continue editing the list of pages.</strong> (more help below, and
more background at the <a href="/about">about page</a>)</p>';
  }

print '<textarea name="pageListAsString" rows="5" cols="100" placeholder="Enter page names here. Each page name should be on a separate line. Remember, enter page names, not URLs. You may also leave this blank and use an alternative method below for specifying lists of pages.">';

if ($formdata == true) 
  {
    print $pageListAsString;
  }

print '</textarea>';

if ($formdata == true and strlen(trim($pageListAsString," \t\n\r\0\x0B"))==0 and count($pageListAsArray) > 0)
  {
    print '</div>';
  }

?>
