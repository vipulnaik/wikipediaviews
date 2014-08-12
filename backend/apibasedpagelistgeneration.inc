<?php

function getpagelistbywikipediacategory($category,$language)
{
  $category_underscored = str_replace(" ","_",$category);
  $apiquery_url = 'http://'.$language.'.wikipedia.org/w/api.php?action=query&list=categorymembers&cmlimit=500&cmtitle=Category:'.$category_underscored;
  #print '<a href="'.$apiquery_url.'">'.$apiquery_url.'</a>';
  $apiquery_html = file_get_contents($apiquery_url);
  #print $apiquery_html;
  $apiquery_txt = html_entity_decode($apiquery_html);
  #preg_match_all('/(?<=\bns=&quot;0&quot; title=&quot;)\K[^&]+/',$apiquery_html,$pagelist);
  preg_match_all('/(?<=\bns="0" title=")\K[^"]+/',$apiquery_txt,$pagelist);
  #print_r($pagelist[0]);
  #$pagelist[0] = str_replace($pagelist[0],"#039&","%27");
  return $pagelist[0];
}

function getpagelistbycreatinguser($user,$language)
{
  $user_underscored = str_replace(" ","_",$user);
  $apiquery_url = 'http://'.$language.'.wikipedia.org/w/api.php?action=query&list=usercontribs&ucshow=new&uclimit=500&ucuser='.$user_underscored;
  #print '<a href="'.$apiquery_url.'">'.$apiquery_url.'</a>';
  $apiquery_html = file_get_contents($apiquery_url);
  #print $apiquery_html;
  $apiquery_txt = html_entity_decode($apiquery_html);
  #preg_match_all('/(?<=\bns=&quot;0&quot; title=&quot;)\K[^&]+/',$apiquery_html,$pagelist);
  preg_match_all('/(?<=\bns="0" title=")\K[^"]+/',$apiquery_txt,$pagelist);
  #$pagelist[0] = str_replace($pagelist[0],"#039&","%27");
  return $pagelist[0];
}

function getpagelistbylinkingpage($linkingpage,$language)
{
  $linkingpage_underscored = str_replace(" ","_",$linkingpage);
  $apiquery_url = 'http://'.$language.'.wikipedia.org/w/api.php?action=query&prop=links&pllimit=500&titles='.$linkingpage_underscored;
  #print '<a href="'.$apiquery_url.'">'.$apiquery_url.'</a>';
  $apiquery_html = file_get_contents($apiquery_url);
  #print $apiquery_html;
  $apiquery_txt = html_entity_decode($apiquery_html);
  $apiquery_txt = str_replace("&#039;","'",$apiquery_txt);
  #preg_match_all('/(?<=\bns=&quot;0&quot; title=&quot;)\K[^&]+/',$apiquery_html,$pagelist);
  preg_match_all('/(?<=\bns="0" title=")\K[^"]+/',$apiquery_txt,$pagelist);
  #print_r($pagelist[0]);
  #$pagelist[0] = str_replace($pagelist[0],"#039&","%27");
  return $pagelist[0];	
}

?>
