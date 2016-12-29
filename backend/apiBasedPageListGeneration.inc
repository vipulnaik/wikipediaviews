<?php

function getPageListByWikipediaCategory($category,$language) {
  $category_underscored = str_replace(" ","_",$category);
  $category_encoded = urlencode($category_underscored);
  $apiquery_url = 'http://'.$language.'.wikipedia.org/w/api.php?action=query&format=json&list=categorymembers&cmlimit=500&cmtitle=Category:'.$category_encoded;
  $iteration = 0;
  $continue = true;
  while ($continue == true and $iteration < 500) {
    $apiquery_url_iteration = $apiquery_url;
    if ($iteration > 0) {
      $apiquery_url_iteration = $apiquery_url.'&cmcontinue='.$response_json["continue"]["cmcontinue"];
    }
    print 'Query URL used to retrieve page list by category, iteration '.$iteration.': <a href="'.$apiquery_url_iteration.'">'.$apiquery_url_iteration.'</a><br/>';
    $response_json = json_decode(file_get_contents($apiquery_url_iteration), true);
    for($i = 0;$i < count($response_json["query"]["categorymembers"]);$i++) {
      $pageList[$iteration * 500 + $i] = $response_json["query"]["categorymembers"][$i]["title"];
    }
    if ($response_json["continue"] == "") {
      $continue = false;
    } else {
      $iteration++;
    }
  }
  return $pageList;
}

function getPageListbyCreatingUser($user,$language) {
  $user_underscored = str_replace(" ","_",$user);
  $apiquery_url = 'http://'.$language.'.wikipedia.org/w/api.php?action=query&format=json&list=usercontribs&ucshow=new&uclimit=500&ucuser='.$user_underscored;
  #print '<a href="'.$apiquery_url.'">'.$apiquery_url.'</a>';
  $apiquery_html = file_get_contents($apiquery_url);
  #print $apiquery_html;
  $apiquery_txt = html_entity_decode($apiquery_html);
  #preg_match_all('/(?<=\bns=&quot;0&quot; title=&quot;)\K[^&]+/',$apiquery_html,$pageList);
  preg_match_all('/"ns":0,"title":"\K[^"]+/',$apiquery_txt,$pageList);
  #$pageList[0] = str_replace($pageList[0],"#039&","%27");
  #print_r($pageList[0]);
  return $pageList[0];
}

function getPageListByLinkingPage($linkingpage,$language)
{
  $linkingpage_underscored = str_replace(" ","_",$linkingpage);
  $apiquery_url = 'http://'.$language.'.wikipedia.org/w/api.php?action=query&format=json&prop=links&pllimit=500&titles='.$linkingpage_underscored;
  #print '<a href="'.$apiquery_url.'">'.$apiquery_url.'</a>';
  $apiquery_html = file_get_contents($apiquery_url);
  #print $apiquery_html;
  $apiquery_txt = html_entity_decode($apiquery_html);
  $apiquery_txt = str_replace("&#039;","'",$apiquery_txt);
  #preg_match_all('/"title":\s+"\K[^"]+/',$apiquery_html,$pageList);
  preg_match_all('/"ns":0,"title":"\K[^"]+/',$apiquery_txt,$pageList);
  #print_r($pageList[0]);
  #$pageList[0] = str_replace($pageList[0],"#039&","%27");
  return $pageList[0];	
}

?>
