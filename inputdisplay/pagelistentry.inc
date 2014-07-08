<?php
	if ($formdata == true and strlen(trim($pagelistasstring," \t\n\r\0\x0B"))==0 and count($pagelistasarray) > 0)
	{
		print '<br><a id="displayText5" href="javascript:toggle5();">Show text area for manual page entry</a><br><br>';

		print '<div id="toggleText5" style="display: none">';
	}
	if ($formdata == false) 
	{ 
	print '<p><strong>Please list the
Wikipedia page names for which you want view count statistics
reported. Please enter one page name per line. Please include only
page names, not full URLs. You may also leave this blank and choose
one of the alternative methods of specifying lists of pages.</strong>
(more help below, and more background at the <a href="/about">about
page</a>)</p>';}

	else
	{
	print '<p><strong>Continue editing the list of pages.</strong> (more help below, and
more background at the <a href="/about">about page</a>)</p>';
        }
	print '<form method="post" name="pagecountinfo" action="displayviewsfor'.$pagetypeadvice.'.php">';
	print '<textarea name="pagelistasstring" rows="5" cols="100" placeholder="Enter page names here. Each page name should be on a separate line. Remember, enter page names, not URLs. You may also leave this blank and use an alternative method below for specifying lists of pages.">';
	if ($formdata == true) {print $pagelistasstring;} 
	print '</textarea>';
	if ($formdata == true and strlen(trim($pagelistasstring," \t\n\r\0\x0B"))==0 and count($pagelistasarray) > 0)
	{
		print '</div>';
	}
?>
