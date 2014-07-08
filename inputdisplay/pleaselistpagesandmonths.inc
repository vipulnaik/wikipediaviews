<?php
if ($formdata == false){
print '<p><strong>Please list page names for which you want view count
statistics reported. Please enter one page name per line. Please
include only page names, not full URLs. Alternatively,
you can choose a tag from the dropdown menu below to have statistics
displayed for all pages in our database with that tag.</strong></p>

<p><strong>Then check the list of months
for which you wish to view statistics.</strong> (more help below, and
more background at the <a href="/about">about page</a>)</p>';
}
else{
print '<p><strong>You may continue editing the list of pages here.</strong> (more help below, and
more background at the <a href="/about">about page</a>)</p>';
}
