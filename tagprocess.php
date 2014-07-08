<!doctype html public "-//W3C//DTD HTML 4.01 Transitional//EN"><html><head><meta http-equiv="Content-Type" content="text/html;charset=utf-8" >
<title>Wikipedia Views: results</title></head>

<?php
        include("backend/corecode.inc");
	$pagelistasstring = $_POST['pagelistasstring'];
        $tag = $_POST['tag'];
        $tagmanual = $_POST['tagmanual'];
        $language = $_POST['language'];
        $createnew = $_POST['createnew'];
        $pagelistasarray = convertpagelisttoarray($pagelistasstring);
        if ($tagmanual != "")
        {
           $tag = $tagmanual;
        }
        if (checktagpresence($tag) or $createnew=="createnew")
        {
             foreach ($pagelistasarray as $page)
             {
                 addpagetotag($page,$language,$tag);
             }
             print "Success!";
        }
        else
        {
             print "Sorry, the tag you requested does not already existed and you did not indicate that you are willing to create a new tag.";
        }
?>
