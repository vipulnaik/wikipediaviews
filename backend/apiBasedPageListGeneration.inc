<?php

function getPageListByWikipediaCategory($category,$language,$method='recursive',$continueString='') {
  $category_underscored = str_replace(" ","_",$category);
  $category_encoded = urlencode($category_underscored);
  $apiQueryUrl = 'https://'.$language.'.wikipedia.org/w/api.php?action=query&format=json&list=categorymembers&cmlimit=500&cmtitle=Category:'.$category_encoded;
  $iteration = 0;
  $continue = true;
  $overallIndex = 0;
  $pageList = array();
  while ($continue == true and $iteration < 50) {
    $apiQueryUrlIteration = $apiQueryUrl;
    if ($iteration > 0) {
      $apiQueryUrlIteration = $apiQueryUrl.'&cmcontinue='.$responseJson["continue"]["cmcontinue"];
    } else if ($continueString != '') {
      $apiQueryUrlIteration = $apiQueryUrl.'&cmcontinue='.$continueString;
    }
    print 'Query URL used to retrieve page list by category, iteration '.$iteration.': <a href="'.$apiQueryUrlIteration.'">'.$apiQueryUrlIteration.'</a><br/>';
    flush();
    $responseJson = json_decode(file_get_contents($apiQueryUrlIteration), true);
    for($i = 0;$i < count($responseJson["query"]["categorymembers"]);$i++) {
      $currentTitle = $responseJson["query"]["categorymembers"][$i]["title"]; 
      if ($method == 'recursive' and strlen($currentTitle) > 9 and substr($currentTitle,0,9) == 'Category:')  {
        $extractedCategory = substr($currentTitle,9,strlen($currentTitle));
        $recursedPageList = getPageListByWikipediaCategory($extractedCategory, $language, 'recursive');
        for ($j = 0; $j < count($recursedPageList); $j++) {
          if (!in_array($recursedPageList[$j], $pageList)) {
            $pageList[$overallIndex] = $recursedPageList[$j];
            $overallIndex++;
	  }
        }
      } else {
        if (isset($pageList) && !in_array($currentTitle, $pageList)) {
          $pageList[$overallIndex] = $currentTitle;
          $overallIndex++;
        }
      }
    }
    if (!isset($responseJson["continue"]) or $responseJson["continue"] == "" or !isset($responseJson["continue"]["cmcontinue"]) {
      $continue = false;
    } else {
      print "Continuation token: " . $responseJson["continue"]["cmcontinue"] . "<br/>";
      $iteration++;
    }
  }
  return $pageList;
}

function getPageListbyCreatingUser($user,$language) {
  $user_underscored = str_replace(" ","_",$user);
  $apiQueryUrl = 'http://'.$language.'.wikipedia.org/w/api.php?action=query&format=json&list=usercontribs&ucshow=new&uclimit=500&ucuser='.$user_underscored;
  #print '<a href="'.$apiQueryUrl.'">'.$apiQueryUrl.'</a>';
  $apiquery_html = file_get_contents($apiQueryUrl);
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
  $apiQueryUrl = 'http://'.$language.'.wikipedia.org/w/api.php?action=query&format=json&prop=links&pllimit=500&titles='.$linkingpage_underscored;
  #print '<a href="'.$apiQueryUrl.'">'.$apiQueryUrl.'</a>';
  $apiquery_html = file_get_contents($apiQueryUrl);
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
