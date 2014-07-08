<?php
	include_once(__DIR__."/../backend/corecode.inc");

	##Retrieval of language
        $language='en';
        if (!empty($_REQUEST['language']))
        {$language = $_REQUEST['language'];}

	##Retrieval of page list as entered directly

        $pagelistasstring='';
	if (!empty($_REQUEST['pagelistasstring']))
        {$pagelistasstring = $_REQUEST['pagelistasstring'];}
	if (!empty($_REQUEST['page']))
        {$pagelistasstring = $_REQUEST['page'];}


        ##Retrieval of alternate page specification formats
        $tag = '';
        $category = '';
	$user = '';
	$linkingpage = '';
        if (!empty($_REQUEST['tag']))
        {$tag = $_REQUEST['tag'];}
        if (!empty($_REQUEST['category']))
        {$category = $_REQUEST['category'];}
        if (!empty($_REQUEST['user']))
        {$user = $_REQUEST['user'];}
        if (!empty($_REQUEST['linkingpage']))
        {$linkingpage = $_REQUEST['linkingpage'];}


        ##Figuring out if the page list has been specified in multiple
        ##ways, or not at all, and displaying the appropriate error message.

        if (strlen(trim($pagelistasstring," \t\n\r\0\x0B"))==0 and $tag==='' and $category==='' and $user==='' and $linkingpage==='')
        {
          include(__DIR__."/../head.inc");
	  print "You didn't list any pages (either directly, or via one of the alternative methods).<br>";
          include(__DIR__."/../multiplemonthsdataentry.inc");
  	  exit;
	}
        if (strlen(trim($pagelistasstring," \t\n\r\0\x0B"))>0 and ($tag!='' or $category!='' or $user != ''))
        {
          include(__DIR__."/../head.inc");
	  print "You listed page(s) directly <em>and</em> selected an alternative method to list pages. You can only use one of the two methods at a time.";
          include(__DIR__."/../multiplemonthsdataentry.inc");
  	  exit;
	}
        if (($tag != '' and ($category != '' or $user != '' or $linkingpage != '')) or ($category != '' and ($user != '' or $linkingpage != '')) or ($user != '' and $linkingpage != ''))
        {
          include(__DIR__."/../head.inc");
	  print "You selected multiple alternate methods. Please modify the form below appropriately.<br>";
          include(__DIR__."/../multiplemonthsdataentry.inc");
  	  exit;
	}

        ##Now that we're sure that the page list is specified uniquely, we convert it to an array
        ##named $pagelistasarray

        if (strlen(trim($pagelistasstring," \t\n\r\0\x0B"))>0)
        {
	$pagelistasstring_mod = str_replace("_"," ",$pagelistasstring);
        $pagelistasarray = convertpagelisttoarray($pagelistasstring_mod);
        }
        if ($tag!='')
        {
        $pagelistasarray = getpagelistbytag($tag,$language);
        if (sizeof($pagelistasarray) == 0)
          {
           include(__DIR__."/../head.inc");
           print "Although the tag is valid, there are no pages for the tag-language <em>combination</em>.<br>";
           include(__DIR__."/../multiplemonthsdataentry.inc");
           exit;
          }
        }
        if ($category!='')
        {
        $pagelistasarray = getpagelistbywikipediacategory($category,$language);
        if (sizeof($pagelistasarray) == 0)
          {
           include(__DIR__."/../head.inc");
           print "There are no pages for the category-language <em>combination</em>.<br>";
           include(__DIR__."/../multiplemonthsdataentry.inc");
           exit;
          }
	sort($pagelistasarray);
        }

        if ($user!='')
        {
        $pagelistasarray = getpagelistbycreatinguser($user,$language);
        if (sizeof($pagelistasarray) == 0)
          {
           include(__DIR__."/../head.inc");
           print "There are no pages for the user-language <em>combination</em>.<br>";
           include(__DIR__."/../multiplemonthsdataentry.inc");
           exit;
          }
	sort($pagelistasarray);
        }

        if ($linkingpage!='')
        {
        $pagelistasarray = getpagelistbylinkingpage($linkingpage,$language);
        if (sizeof($pagelistasarray) == 0)
          {
           include(__DIR__."/../head.inc");
           print "There are no pages for the linking page-language <em>combination</em>.<br>";
           include(__DIR__."/../multiplemonthsdataentry.inc");
           exit;
          }
	sort($pagelistasarray);
        }

?>
