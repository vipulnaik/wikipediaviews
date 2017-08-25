<?php

include_once("globalVariables/passwordFile.inc");

function checkSizes($pageOrTagList,$languageList, $drilldownList, $monthOrYearList) {
  global $pageDisplayLimit;
  global $cellDisplayLimit;
  $numberOfPagesOrTags = count($pageOrTagList);
  $numberOfMonthsOrYears = count($monthOrYearList);
  if ($numberOfPagesOrTags > $pageDisplayLimit) {
    print "The number of pages or tags, namely ".$numberOfPagesOrTags.", exceeds ".$pageDisplayLimit.", our hard limit on the number of pages that can be displayed.<br/>";
    return 1;
  }
  $numberOfCells = $numberOfPagesOrTags * $numberOfMonthsOrYears * count($languageList) * count($drilldownList);
  if ($numberOfCells > $cellDisplayLimit) {
    print "The total number of cells to display, namely ".$numberOfCells.", exceeds ".$cellDisplayLimit.", our hard limit on the number of cells that can be displayed.";
    return 2;
  }
  return 0;
}

function totalsAndPercentages($pageOrTagList,$languageList,$drilldownList,$monthOrYearList,$viewCountArray) {
  $pageOrTagCumLanguageCumDrilldownTotal = array();
  $pageOrTagCumLanguageCumMonthOrYearTotal = array();
  $drilldownCumMonthOrYearTotal = array();
  $pageOrTagCumLanguageTotal = array();
  $pageOrTagCumDrilldownTotal = array();
  $pageOrTagCumMonthOrYearTotal = array();
  $pageOrTagTotal = array();
  $languageTotal = array();
  $drilldownTotal = array();
  $monthOrYearTotal = array();
  $grandTotal = 0;
  foreach ($pageOrTagList as $pageOrTag) {
    if (!array_key_exists($pageOrTag, $pageOrTagCumLanguageCumDrilldownTotal)) {
      $pageOrTagCumLanguageCumDrilldownTotal[$pageOrTag] = array();
    }
    if (!array_key_exists($pageOrTag, $pageOrTagCumLanguageCumMonthOrYearTotal)) {
      $pageOrTagCumLanguageCumMonthOrYearTotal[$pageOrTag] = array();
    }
    if (!array_key_exists($pageOrTag, $pageOrTagCumLanguageTotal)) {
      $pageOrTagCumLanguageTotal[$pageOrTag] = array();
    }
    if (!array_key_exists($pageOrTag, $pageOrTagCumDrilldownTotal)) {
      $pageOrTagCumDrilldownTotal[$pageOrTag] = array();
    }
    if (!array_key_exists($pageOrTag, $pageOrTagCumMonthOrYearTotal)) {
      $pageOrTagCumMonthOrYearTotal[$pageOrTag] = array();
    }
    if (!array_key_exists($pageOrTag, $pageOrTagTotal)) {
      $pageOrTagTotal[$pageOrTag] = 0;
    }
    foreach ($languageList as $language) {
      if (!array_key_exists($language, $pageOrTagCumLanguageCumDrilldownTotal[$pageOrTag])) {
        $pageOrTagCumLanguageCumDrilldownTotal[$pageOrTag][$language] = array();
      }
      if (!array_key_exists($language, $pageOrTagCumLanguageCumMonthOrYearTotal[$pageOrTag])) {
        $pageOrTagCumLanguageCumMonthOrYearTotal[$pageOrTag][$language] = array();
      }
      if (!array_key_exists($language, $pageOrTagCumLanguageTotal[$pageOrTag])) {
        $pageOrTagCumLanguageTotal[$pageOrTag][$language] = 0;
      }
      if (!array_key_exists($language, $languageTotal)) {
        $languageTotal[$language] = 0;
      }
      foreach ($drilldownList as $drilldown) {
        if (!array_key_exists($drilldown, $pageOrTagCumDrilldownTotal[$pageOrTag])) {
          $pageOrTagCumDrilldownTotal[$pageOrTag][$drilldown] = 0;
        }
        if (!array_key_exists($drilldown, $pageOrTagCumLanguageCumDrilldownTotal[$pageOrTag][$language])) {
          $pageOrTagCumLanguageCumDrilldownTotal[$pageOrTag][$language][$drilldown] = 0;
        }
        if (!array_key_exists($drilldown, $drilldownCumMonthOrYearTotal)) {
          $drilldownCumMonthOrYearTotal[$drilldown] = array();
        }
        if (!array_key_exists($drilldown, $drilldownTotal)) {
          $drilldownTotal[$drilldown] = 0;
         }
        foreach ($monthOrYearList as $monthOrYear) {
          if (!array_key_exists($monthOrYear, $pageOrTagCumLanguageCumMonthOrYearTotal[$pageOrTag][$language])) {
            $pageOrTagCumLanguageCumMonthOrYearTotal[$pageOrTag][$language][$monthOrYear] = 0;
          }
          if (!array_key_exists($monthOrYear, $drilldownCumMonthOrYearTotal[$drilldown])) {
            $drilldownCumMonthOrYearTotal[$drilldown][$monthOrYear] = 0;
          }
          if (!array_key_exists($monthOrYear, $pageOrTagCumMonthOrYearTotal[$pageOrTag])) {
            $pageOrTagCumMonthOrYearTotal[$pageOrTag][$monthOrYear] = 0;
          }
          if (!array_key_exists($monthOrYear, $monthOrYearTotal)) {
            $monthOrYearTotal[$monthOrYear] = 0;
          }
          if (array_key_exists($pageOrTag, $viewCountArray) and array_key_exists($language, $viewCountArray[$pageOrTag]) and array_key_exists($drilldown, $viewCountArray[$pageOrTag][$language]) and array_key_exists($monthOrYear, $viewCountArray[$pageOrTag][$language][$drilldown])) {
            $increment = intval($viewCountArray[$pageOrTag][$language][$drilldown][$monthOrYear]);
            $pageOrTagCumLanguageCumDrilldownTotal[$pageOrTag][$language][$drilldown] += $increment;
            $pageOrTagCumLanguageCumMonthOrYearTotal[$pageOrTag][$language][$monthOrYear] += $increment;
            $drilldownCumMonthOrYearTotal[$drilldown][$monthOrYear] += $increment;
            $pageOrTagCumMonthOrYearTotal[$pageOrTag][$monthOrYear] += $increment;
            $pageOrTagCumLanguageTotal[$pageOrTag][$language] += $increment;
            $pageOrTagCumDrilldownTotal[$pageOrTag][$drilldown] += $increment;
            $pageOrTagTotal[$pageOrTag] += $increment;
            $languageTotal[$language] += $increment;
            $drilldownTotal[$drilldown] += $increment;
            $monthOrYearTotal[$monthOrYear] += $increment;
            $grandTotal += $increment;
          }
        }
      }
    }
  }

  foreach ($pageOrTagList as $pageOrTag) {
    if ($grandTotal == 0) {
      $pageOrTagPercentage[$pageOrTag] = 'undefined';
    } else {
      $pageOrTagPercentage[$pageOrTag] = round(100.0 * floatval($pageOrTagTotal[$pageOrTag])/floatval($grandTotal),1);
    }
    foreach($languageList as $language) {
      if ($grandTotal == 0) {
        $pageOrTagCumLanguagePercentage[$pageOrTag][$language] = 'undefined';
      } else {
        $pageOrTagCumLanguagePercentage[$pageOrTag][$language] = round(100 * floatval($pageOrTagCumLanguageTotal[$pageOrTag][$language])/floatval($grandTotal),1);
      }
      foreach ($drilldownList as $drilldown) {
        if ($grandTotal == 0) {
	  $pageOrTagCumLanguageCumDrilldownPercentage[$pageOrTag][$language][$drilldown] = 'undefined';
        } else {
	  $pageOrTagCumLanguageCumDrilldownPercentage[$pageOrTag][$language][$drilldown] = round(100 * floatval($pageOrTagCumLanguageCumDrilldownTotal[$pageOrTag][$language][$drilldown])/floatval($grandTotal),1);
        }
      }
    }
  }
  foreach ($monthOrYearList as $monthOrYear) {
    if ($grandTotal == 0) {
      $monthOrYearPercentage[$monthOrYear] = 'undefined';
    } else {
      $monthOrYearPercentage[$monthOrYear] = round(100.0 * floatval($monthOrYearTotal[$monthOrYear])/floatval($grandTotal),1);
    }
    foreach ($pageOrTagList as $pageOrTag) {
      if ($grandTotal == 0) {
	$pageOrTagCumLanguageCumMonthOrYearPercentage[$pageOrTag][$language][$monthOrYear] = 'undefined';
      } else {
	$pageOrTagCumLanguageCumMonthOrYearPercentage[$pageOrTag][$language][$monthOrYear] = round(100 * floatval($pageOrTagCumLanguageCumMonthOrYearTotal[$pageOrTag][$language][$monthOrYear])/floatval($grandTotal),1);
      }
    }
  }

  foreach ($drilldownList as $drilldown) {
    if ($grandTotal == 0) {
      $drilldownPercentage[$drilldown] = 'undefined';
    } else {
      $drilldownPercentage[$drilldown] = round(100 * floatval($drilldownTotal[$drilldown])/floatval($grandTotal),1);
    }
    foreach ($monthOrYearList as $monthOrYear) {
      if ($grandTotal == 0) {
        $drilldownCumMonthOrYearPercentage[$drilldown][$monthOrYear] = 'undefined';
      } else {
        $drilldownCumMonthOrYearPercentage[$drilldown][$monthOrYear] = round(100 * floatval($drilldownCumMonthOrYearTotal[$drilldown][$monthOrYear])/floatval($grandTotal),1);
      }
    }
  }
  
  $tap["grandTotal"] = $grandTotal;
  $tap["pageOrTagCumMonthOrYearTotal"] = $pageOrTagCumMonthOrYearTotal;
  $tap["pageOrTagCumLanguageCumDrilldownTotal"] = $pageOrTagCumLanguageCumDrilldownTotal;
  $tap["pageOrTagCumLanguageCumMonthOrYearTotal"] = $pageOrTagCumLanguageCumMonthOrYearTotal;
  $tap["drilldownCumMonthOrYearTotal"] = $drilldownCumMonthOrYearTotal;
  $tap["pageOrTagCumLanguageTotal"] = $pageOrTagCumLanguageTotal;
  $tap["pageOrTagTotal"] = $pageOrTagTotal;
  $tap["drilldownTotal"] = $drilldownTotal;
  $tap["monthOrYearTotal"] = $monthOrYearTotal;
  $tap["pageOrTagCumLanguageCumDrilldownPercentage"] = $pageOrTagCumLanguageCumDrilldownPercentage;
  $tap["pageOrTagCumLanguageCumMonthOrYearPercentage"] = $pageOrTagCumLanguageCumMonthOrYearPercentage;
  $tap["drilldownCumMonthOrYearPercentage"] = $drilldownCumMonthOrYearPercentage;
  $tap["pageOrTagCumLanguagePercentage"] = $pageOrTagCumLanguagePercentage;
  $tap["pageOrTagPercentage"] = $pageOrTagPercentage;
  $tap["drilldownPercentage"] = $drilldownPercentage;
  $tap["monthOrYearPercentage"] = $monthOrYearPercentage;
  
  return $tap;
}

function printMonthViewCount($page,$month,$language,$drilldown,$viewcount,$numericDisplayFormat) {
  if ($drilldown == "all") {
    return '<td align="right"><strong><a title="'.monthviewtooltip($viewcount).'">'.numericDisplay($viewcount,$numericDisplayFormat).'</a></strong></td>';
  } elseif (substr($drilldown, 0, 9) == "referrer:" or ($page == "[aggregate]" and $month < '201507' and $drilldown != "desktop" and $drilldown != "mobile-web")) {
    return '<td align="right"><a title="'.monthviewtooltip($viewcount).'">'.numericDisplay($viewcount,$numericDisplayFormat).'</a></td>';
  } elseif ($drilldown == "cumulative-facebook-shares") {
    return '<td align="right"><a href="'.str_replace("/v2.8","", getPageviewsUrl($page,$month,$language,$drilldown)).'" title="'.monthviewtooltip($viewcount).'">'.numericDisplay($viewcount,$numericDisplayFormat).'</a></td>';
  } else {
    return '<td align="right"><a href="'.getPageviewsUrl($page,$month,$language,$drilldown).'" title="'.monthviewtooltip($viewcount).'">'.numericDisplay($viewcount,$numericDisplayFormat).'</a></td>';
  }
}

function printYearViewCount($page,$year,$language,$drilldown,$viewcount,$numericDisplayFormat) {
  if ($drilldown == "all") {
    return '<td align="right"><strong><a title="'.yearviewtooltip($viewcount).'">'.numericDisplay($viewcount,$numericDisplayFormat).'</a></strong></td>';
  } else {
    return '<td align="right"><a href="'.getAnnualPageviewsUrl($page,$year,$language,$drilldown).'" title="'.yearviewtooltip($viewcount).'">'.numericDisplay($viewcount,$numericDisplayFormat).'</a></td>';
  }
}

function printTagViewCount($tag,$month,$language,$drilldown,$viewcount,$numericDisplayFormat) {
  return '<td align="right"><a href="'.getTagViewsUrl($tag,$month,$language,$drilldown).'" title="'.$viewcount.' (click for data on individual pages)">'.numericDisplay($viewcount,$numericDisplayFormat).'</a></td>';
}

function printTagViewCountByYear($tag,$year,$language,$drilldown,$viewcount,$numericDisplayFormat) {
  return '<td align="right"><a href="'.getAnnualTagViewsUrl($tag,$year,$language,$drilldown).'" title="'.$viewcount.' (click for data on individual pages)">'.numericDisplay($viewcount,$numericDisplayFormat).'</a></td>';
}

function printPageviewsForMonthOrYearListAsHtmlTable($pageOrTagList,$languageList,$drilldownList,$monthOrYearList,$numericDisplayFormat,$normalization='',$pageOrTagAdvice='page',$monthOrYearAdvice='month',$sort='desc',$shortcutTag='') {
  global $pageOrTagTotal;
  global $timeTaken;
  $startTime = microtime(true);
  flush();
  #Check that sizes are workable
  $sizeOverflow = checkSizes($pageOrTagList,$languageList,$drilldownList,$monthOrYearList);
  if ($sizeOverflow > 0) {
    print " Therefore, we are not printing the table.<br/>";
    return false;
  }
  #Collect all the numbers that need to be printed first
  if ($pageOrTagAdvice=='page' and $monthOrYearAdvice=='month') {
    $viewCountArray = viewCountArrayByMonth($pageOrTagList,$languageList,$drilldownList,$monthOrYearList,true,$normalization,$shortcutTag);
  } elseif ($pageOrTagAdvice=='page' and $monthOrYearAdvice=='year') {
    $viewCountArray = viewCountArrayByYear($pageOrTagList,$languageList,$drilldownList,$monthOrYearList,true,$normalization);
  } elseif ($pageOrTagAdvice=='tag' and $monthOrYearAdvice=='month') {
    $viewCountArray = viewCountArrayByTagAndMonth($pageOrTagList,$languageList,$drilldownList,$monthOrYearList,true,$normalization);
  } elseif ($pageOrTagAdvice=='tag' and $monthOrYearAdvice=='year') {
    $viewCountArray = viewCountArraybyTagAndYear($pageOrTagList,$languageList,$drilldownList,$monthOrYearList,true,$normalization);
  }
  $tap = totalsAndPercentages($pageOrTagList,$languageList,$drilldownList,$monthOrYearList,$viewCountArray);
  $grandTotal = $tap["grandTotal"];
  $pageOrTagCumMonthOrYearTotal = $tap["pageOrTagCumMonthOrYearTotal"];
  $pageOrTagCumLanguageCumDrilldownTotal = $tap["pageOrTagCumLanguageCumDrilldownTotal"];
  $pageOrTagCumLanguageCumMonthOrYearTotal = $tap["pageOrTagCumLanguageCumMonthOrYearTotal"];
  $drilldownCumMonthOrYearTotal = $tap["drilldownCumMonthOrYearTotal"];
  $pageOrTagCumLanguageTotal = $tap["pageOrTagCumLanguageTotal"];
  $pageOrTagTotal = $tap["pageOrTagTotal"];
  $drilldownTotal = $tap["drilldownTotal"];
  $monthOrYearTotal = $tap["monthOrYearTotal"];
  $pageOrTagCumLanguageCumDrilldownPercentage = $tap["pageOrTagCumLanguageCumDrilldownPercentage"];
  $pageOrTagCumLanguageCumMonthOrYearPercentage = $tap["pageOrTagCumLanguageCumMonthOrYearPercentage"];
  $drilldownCumMonthOrYearPercentage = $tap["drilldownCumMonthOrYearPercentage"];
  $pageOrTagCumLanguagePercentage = $tap["pageOrTagCumLanguagePercentage"];
  $pageOrTagPercentage = $tap["pageOrTagPercentage"];
  $drilldownPercentage = $tap["drilldownPercentage"];
  $monthOrYearPercentage = $tap["monthOrYearPercentage"];

  function cmp($firstPage, $secondPage) {
    global $pageOrTagTotal;
    if (intval($pageOrTagTotal[$firstPage]) == intval($pageOrTagTotal[$secondPage])) {
      if ($firstPage == $secondPage) {
        return 0;
      } else {
        return ($firstPage < $secondPage) ? -1 : 1;
      }
    }
    return (intval($pageOrTagTotal[$firstPage]) > intval($pageOrTagTotal[$secondPage])) ? -1 : 1;
  }

  switch($sort) {
    case "desc" :
      usort($pageOrTagList, "cmp");
      break;
    case "asc" :
      usort($pageOrTagList, "cmp");
      $pageOrTagList = array_reverse($pageOrTagList);
      break;
    case "alphabetical" :
      sort($pageOrTagList);
      break;
  }
  
  #Tag list fetching
  if ($pageOrTagAdvice=='page') {
    $tagListByPages = getTagListByPageList($pageOrTagList,$languageList);
  }
  #Pre-table warnings

  if ($monthOrYearAdvice=='year') {
    print "<strong>For speed and consistency reasons, we do <em>not</em> include the current month in totals for the current year</strong><br><br>";
  }
  flush();
  ##Table header row
    
  print '<table border="1">';
  $headerString = "<tr><th>".ucfirst($pageOrTagAdvice)." name";

  if (count($drilldownList) > 1) {
    $headerString .= " and drilldown";
  }
  $headerString .= "</th>";
  foreach($monthOrYearList as $monthOrYear) {
    $headerString .= "<th>Count in ".$monthOrYearAdvice." ".$monthOrYear."</th>";
  }
  if (count($monthOrYearList) > 1) {
    $headerString .="<th>Total</th>";
  }
  if (count($pageOrTagList) * count($languageList) * count($drilldownList) > 1) {
    $headerString.="<th>Percentage</th>";
  }

  #Tag list column printing
  if ($pageOrTagAdvice == 'page') {
    $headerString .= "<th>Tags</th>";
  }
  $headerString .= "</tr>";
  print $headerString;
  
  ##Data rows
  foreach($pageOrTagList as $pageOrTag) {
    foreach($languageList as $language) {
      if ($pageOrTagAdvice == 'page') {
        $tagListForPage = $tagListByPages[$pageOrTag][$language];
      }
      
      foreach($drilldownList as $drilldown) {
        if ($pageOrTagAdvice=='page') {
          $pageOrTagCumLanguageCumDrilldownRowString = '<tr><td><a href="'.getPageUrl($pageOrTag,$language).'" title = "'.$pageOrTag.' (read page on Wikipedia)">'.$pageOrTag.'</a>';
        } elseif ($pageOrTagAdvice=='tag' and $monthOrYearAdvice=='month') {
          $pageOrTagCumLanguageCumDrilldownRowString = '<td><a href="https://wikipediaviews.org/displayviewsformultiplemonths.php?tag='.$pageOrTag.'&language='.$language.'&drilldown='.$drilldown.'&allmonths=allmonths">'.$pageOrTag.'</a>';
        } elseif ($pageOrTagAdvice=='tag' and $monthOrYearAdvice=='year') {
          $pageOrTagCumLanguageCumDrilldownRowString = '<td><a href="https://wikipediaviews.org/displayviewsformultipleyears.php?tag='.$pageOrTag.'&language='.$language.'&drilldown='.$drilldown.'&allyears=allyears">'.$pageOrTag.'</a>';
        }
        if (count($languageList) > 1) {
          $pageOrTagCumLanguageCumDrilldownRowString .= ', language '.$language;
        }
        if (count($drilldownList) > 1) {
          $pageOrTagCumLanguageCumDrilldownRowString .= ', drilldown '.$drilldown;
        }
        $pageOrTagCumLanguageCumDrilldownRowString .= '</td>';
        
        foreach($monthOrYearList as $monthOrYear) {
          $viewcount = $viewCountArray[$pageOrTag][$language][$drilldown][$monthOrYear];
  	  if ($pageOrTagAdvice=='page' and $monthOrYearAdvice=='month') {
  	    $pageOrTagCumLanguageCumDrilldownRowString .= printMonthViewCount($pageOrTag,$monthOrYear,$language,$drilldown,$viewcount,$numericDisplayFormat);
  	  } elseif ($pageOrTagAdvice=='page' and $monthOrYearAdvice=='year') {
  	    $pageOrTagCumLanguageCumDrilldownRowString .= printYearViewCount($pageOrTag,$monthOrYear,$language,$drilldown,$viewcount,$numericDisplayFormat);
  	  } elseif ($pageOrTagAdvice=='tag' and $monthOrYearAdvice=='month') {
  	    $pageOrTagCumLanguageCumDrilldownRowString .= printTagViewCount($pageOrTag,$monthOrYear,$language,$drilldown,$viewcount,$numericDisplayFormat);
  	  } elseif ($pageOrTagAdvice=='tag' and $monthOrYearAdvice=='year') {
            $pageOrTagCumLanguageCumDrilldownRowString .= printTagViewCountByYear($pageOrTag,$monthOrYear,$language,$drilldown,$viewcount,$numericDisplayFormat);
  	  }
        }
        if (count($monthOrYearList) > 1) {
  	  $pageOrTagCumLanguageCumDrilldownRowString .='<td align="right"><strong><element title="'.$pageOrTagCumLanguageCumDrilldownTotal[$pageOrTag][$language][$drilldown].'">'.numericDisplay($pageOrTagCumLanguageCumDrilldownTotal[$pageOrTag][$language][$drilldown],$numericDisplayFormat).'</element></strong></td>';
        }
        if (count($pageOrTagList) * count($languageList) * count($drilldownList) > 1) {
          $pageOrTagCumLanguageCumDrilldownRowString .= '<td align="right"><strong>'.$pageOrTagCumLanguageCumDrilldownPercentage[$pageOrTag][$language][$drilldown].'</strong></td>';
        }
        if ($pageOrTagAdvice == 'page') {
          $pageOrTagCumLanguageCumDrilldownRowString .= '<td>';
          if (count($tagListForPage)==0) {
            $pageOrTagCumLanguageCumDrilldownRowString .= "--";
          }
          foreach ($tagListForPage as $tag) {
            if ($monthOrYearAdvice == 'month') {
              $pageOrTagCumLanguageCumDrilldownRowString .= '<a href="https://wikipediaviews.org/displayviewsformultiplemonths.php?tag='.$tag.'&language='.$language.'&drilldown='.$drilldown.'&allmonths=allmonths">'.$tag.'</a> ';
  	    } else {
              $pageOrTagCumLanguageCumDrilldownRowString .= '<a href="https://wikipediaviews.org/displayviewsformultipleyears.php?tag='.$tag.'&language='.$language.'&drilldown='.$drilldown.'&allyears=allyears">'.$tag.'</a> ';
  	    }
          }
          $pageOrTagCumLanguageCumDrilldownRowString .= '</td>';
        }
        $pageOrTagCumLanguageCumDrilldownRowString .="</tr>";
        print $pageOrTagCumLanguageCumDrilldownRowString;
      }
      if (count($drilldownList) > 1 and count($pageOrTagList) * count($languageList) > 1) {
        if ($pageOrTagAdvice=='page') {
          $pageOrTagCumLanguageSummaryString = '<tr><td><strong><a href="'.getPageUrl($pageOrTag,$language).'" title = "'.urlencode($pageOrTag).' (read page on Wikipedia)">'.$pageOrTag.'</a>';
        } elseif ($pageOrTagAdvice=='tag' and $monthOrYearAdvice=='month') {
          $pageOrTagCumLanguageSummaryString = '<tr><td><strong><a href="https://wikipediaviews.org/displayviewsformultiplemonths.php?tag='.urlencode($pageOrTag).'&language='.$language.'&drilldown='.$drilldown.'&allmonths=allmonths">'.$pageOrTag.'</a>';
        } elseif ($pageOrTagAdvice=='tag' and $monthOrYearAdvice=='year') {
          $pageOrTagCumLanguageSummaryString = '<tr><td><strong><a href="https://wikipediaviews.org/displayviewsformultipleyears.php?tag='.urlencode($pageOrTag).'&language='.$language.'&drilldown='.$drilldown.'&allyears=allyears">'.$pageOrTag.'</a>';
        }
        if (count($languageList) > 1) {
          $pageOrTagCumLanguageSummaryString .= ', language '.$language;
        }
        $pageOrTagCumLanguageSummaryString .= ', sum over drilldowns</strong></td>';
        foreach($monthOrYearList as $monthOrYear) {
          $viewcount = $pageOrTagCumLanguageCumMonthOrYearTotal[$pageOrTag][$language][$monthOrYear];
  	  if ($pageOrTagAdvice=='page' and $monthOrYearAdvice=='month') {
  	    $pageOrTagCumLanguageSummaryString .= printMonthViewCount($pageOrTag,$monthOrYear,$language,"all",$viewcount,$numericDisplayFormat);
  	  } elseif ($pageOrTagAdvice=='page' and $monthOrYearAdvice=='year') {
  	    $pageOrTagCumLanguageSummaryString .= printYearViewCount($pageOrTag,$monthOrYear,$language,"all",$viewcount,$numericDisplayFormat);
  	  } elseif ($pageOrTagAdvice=='tag' and $monthOrYearAdvice=='month') {
  	    $pageOrTagCumLanguageSummaryString .= printTagViewCount($pageOrTag,$monthOrYear,$language,"all",$viewcount,$numericDisplayFormat);
  	  } elseif ($pageOrTagAdvice=='tag' and $monthOrYearAdvice=='year') {
  	    $pageOrTagCumLanguageSummaryString .= printTagViewCountByYear($pageOrTag,$monthOrYear,$language,"all",$viewcount,$numericDisplayFormat);
          }
        }
        if (count($monthOrYearList) > 1) {
          $pageOrTagCumLanguageSummaryString .='<td align="right"><strong><element title="'.$pageOrTagCumLanguageTotal[$pageOrTag][$language].'">'.numericDisplay($pageOrTagCumLanguageTotal[$pageOrTag][$language],$numericDisplayFormat).'</element></strong></td>';
        }
        $pageOrTagCumLanguageSummaryString .= '<td align="right"><strong>'.$pageOrTagCumLanguagePercentage[$pageOrTag][$language].'</strong></td>';
        if ($pageOrTagAdvice == 'page') {
          $pageOrTagCumLanguageSummaryString .= '<td>';
  	if (count($tagListForPage)==0) {
  	  $pageOrTagCumLanguageSummaryString .= "--";
          }
  	foreach ($tagListForPage as $tag) {
            if ($monthOrYearAdvice == 'month') {
              $pageOrTagCumLanguageSummaryString .= '<a href="https://wikipediaviews.org/displayviewsformultiplemonths.php?tag='.$tag.'&language='.$language.'&drilldown=all&allmonths=allmonths">'.$tag.'</a> ';
  	  } else {
              $pageOrTagCumLanguageSummaryString .= '<a href="https://wikipediaviews.org/displayviewsformultipleyears.php?tag='.$tag.'&language='.$language.'&drilldown=all&allyears=allyears">'.$tag.'</a> ';
  	  }
          }
          $pageOrTagCumLanguageSummaryString .= '</td>';
        }
        $pageOrTagCumLanguageSummaryString .="</tr>";
        print $pageOrTagCumLanguageSummaryString;
      }
    }
    if (count($pageOrTagList) > 1 and count($languageList) > 1) { ## Summary row across languages and drilldowns, for a given page or tag
      $pageOrTagSummaryString = '<tr><td><strong>'.$pageOrTag.', sum over languages';
      if (count($drilldownList) > 1) {
        $pageOrTagSummaryString .= ' and  drilldowns</strong></td>';
      } else {
        $pageOrTagSummaryString .= '</strong></td>';
      }
      foreach($monthOrYearList as $monthOrYear) {
        $viewcount = $pageOrTagCumMonthOrYearTotal[$pageOrTag][$monthOrYear];
  	if ($pageOrTagAdvice=='page' and $monthOrYearAdvice=='month') {
  	  $pageOrTagSummaryString .= printMonthViewCount($pageOrTag,$monthOrYear,"all","all",$viewcount,$numericDisplayFormat);
  	} elseif ($pageOrTagAdvice=='page' and $monthOrYearAdvice=='year') {
  	  $pageOrTagSummaryString .= printYearViewCount($pageOrTag,$monthOrYear,"all","all",$viewcount,$numericDisplayFormat);
  	} elseif ($pageOrTagAdvice=='tag' and $monthOrYearAdvice=='month') {
  	  $pageOrTagSummaryString .= printTagViewCount($pageOrTag,$monthOrYear,"all","all",$viewcount,$numericDisplayFormat);
  	} elseif ($pageOrTagAdvice=='tag' and $monthOrYearAdvice=='year') {
  	  $pageOrTagSummaryString .= printTagViewCountByYear($pageOrTag,$monthOrYear,"all","all",$viewcount,$numericDisplayFormat);
        }
      }
      if (count($monthOrYearList) > 1) {
        $pageOrTagSummaryString .='<td align="right"><strong><element title="'.$pageOrTagTotal[$pageOrTag].'">'.numericDisplay($pageOrTagTotal[$pageOrTag],$numericDisplayFormat).'</element></strong></td>';
      }
      $pageOrTagSummaryString .= '<td align="right"><strong>'.$pageOrTagPercentage[$pageOrTag].'</strong></td>';
      if ($pageOrTagAdvice == 'page') {
        $pageOrTagSummaryString .= '<td>--</td>';
      }
      $pageOrTagSummaryString .="</tr>";
      print $pageOrTagSummaryString;
    }
  }
  if (count($pageOrTagList) * count($languageList) > 1 and count($drilldownList) > 1) {
    foreach($drilldownList as $drilldown) {
      $drilldownTotalRowString  = "<tr><td><strong>Total, drilldown ".$drilldown."</strong></td>";
      foreach($monthOrYearList as $monthOrYear) {
        $drilldownTotalRowString .= '<td align="right"><strong><element title="'.$drilldownCumMonthOrYearTotal[$drilldown][$monthOrYear].'">'.numericDisplay($drilldownCumMonthOrYearTotal[$drilldown][$monthOrYear],$numericDisplayFormat).'</element></strong></td>';
      }
      if (count($monthOrYearList) > 1) {
        $drilldownTotalRowString .= '<td align="right"><strong><element title="'.$drilldownTotal[$drilldown].'">'.numericDisplay($drilldownTotal[$drilldown],$numericDisplayFormat).'</element></strong></td>';
      }
      $drilldownTotalRowString .= '<td align="right"><strong>'.$drilldownPercentage[$drilldown].'</strong></td>';
      if ($pageOrTagAdvice == 'page') {
        $drilldownTotalRowString .= '<td>--</td>';
      }
      $drilldownTotalRowString .= '</tr>';
      print($drilldownTotalRowString);
      if (count($monthOrYearList) > 1) {
        $drilldownPercentageRowString = "<tr><td><strong>Percentage, drilldown ".$drilldown."</strong></td>";
        foreach($monthOrYearList as $monthOrYear) {
          $drilldownPercentageRowString .= '<td align="right"><strong>' . $drilldownCumMonthOrYearPercentage[$drilldown][$monthOrYear]. '</strong></td>';
        }
        $drilldownPercentageRowString .= '<td align="right"><strong>'.$drilldownPercentage[$drilldown].'</strong></td>';
        $drilldownPercentageRowString .= '<td>--</td>'; 
        if ($pageOrTagAdvice == 'page') {
          $drilldownPercentageRowString .= '<td>--</td>';
        }
        $drilldownPercentageRowString .= '</tr>';
        print($drilldownPercentageRowString);
      }
    }
  }
  if (count($pageOrTagList) * count($languageList) * count($drilldownList) > 1) {
    $totalsRowString="<tr><td><strong>Total</strong></td>";
    foreach($monthOrYearList as $monthOrYear) {
      $totalsRowString .= '<td align="right"><strong><element title="'.$monthOrYearTotal[$monthOrYear].'">'.numericDisplay($monthOrYearTotal[$monthOrYear],$numericDisplayFormat).'</element></strong></td>';
    }
    if (count($monthOrYearList) > 1) {
      $totalsRowString .= '<td align="right"><strong><element title="'.$grandTotal.'">'.numericDisplay($grandTotal,$numericDisplayFormat).'</element></strong></td>';
    }
    $totalsRowString .= '<td align="right"><strong>100</strong></td>';
    if ($pageOrTagAdvice == 'page') {
      $totalsRowString .= "<td>--</td>";
    }
    $totalsRowString .= "</tr>";
    print $totalsRowString;
  }
  if (count($monthOrYearList) > 1) {
    $percentagesRowString = "<tr><td><strong>Percentage</strong></td>";
    foreach($monthOrYearList as $monthOrYear) {
      $percentagesRowString .= '<td align="right"><strong>'.$monthOrYearPercentage[$monthOrYear].'</strong></td>';
    }
    $percentagesRowString .= '<td align="right"><strong>100</strong></td>';
    if (count($pageOrTagList) * count($languageList) * count($drilldownList) > 1) {
      $percentagesRowString .= '<td align="right">--</td>';
    }
    if ($pageOrTagAdvice == 'page') {
      $percentagesRowString .= "<td>--</td>";
    }
    $percentagesRowString .= '</tr>';
    print $percentagesRowString;
  }
  print "</table>";
  $endTime = microtime(true);
  $timeTaken = $endTime - $startTime;
  flush();
  return true;
}

function printPageviewsForMonthOrYearListAsHtmlTableTransposed($pageOrTagList,$languageList,$drilldownList,$monthOrYearList,$numericDisplayFormat,$normalization='',$pageOrTagAdvice='page',$monthOrYearAdvice='month',$sort='desc',$shortcutTag='') {
  global $timeTaken;
  global $pageOrTagTotal;
  $startTime = microtime(true);
  flush();
  #Check that sizes are workable
  $sizeOverflow = checkSizes($pageOrTagList,$languageList,$drilldownList,$monthOrYearList);
  if ($sizeOverflow > 0) {
    print " Therefore, we are not printing the table<br/>";
    return false;
  }
  #Collect all the numbers that need to be printed first
  if ($pageOrTagAdvice=='page' and $monthOrYearAdvice=='month') {
    $viewCountArray = viewCountArrayByMonth($pageOrTagList,$languageList,$drilldownList,$monthOrYearList,true,$normalization,$shortcutTag);
  } elseif ($pageOrTagAdvice=='page' and $monthOrYearAdvice=='year') {
    $viewCountArray = viewCountArrayByYear($pageOrTagList,$languageList,$drilldownList,$monthOrYearList,true,$normalization);
  } elseif ($pageOrTagAdvice=='tag' and $monthOrYearAdvice=='month') {
    $viewCountArray = viewCountArrayByTagAndMonth($pageOrTagList,$languageList,$drilldownList,$monthOrYearList,true,$normalization);
  } elseif ($pageOrTagAdvice=='tag' and $monthOrYearAdvice=='year') {
    $viewCountArray = viewCountArraybyTagAndYear($pageOrTagList,$languageList,$drilldownList,$monthOrYearList,true,$normalization);
  }
  $tap = totalsAndPercentages($pageOrTagList,$languageList,$drilldownList,$monthOrYearList,$viewCountArray);
  $grandTotal = $tap["grandTotal"];
  $pageOrTagCumMonthOrYearTotal = $tap["pageOrTagCumMonthOrYearTotal"];
  $pageOrTagCumLanguageCumDrilldownTotal = $tap["pageOrTagCumLanguageCumDrilldownTotal"];
  $pageOrTagCumLanguageCumMonthOrYearTotal = $tap["pageOrTagCumLanguageCumMonthOrYearTotal"];
  $drilldownCumMonthOrYearTotal = $tap["drilldownCumMonthOrYearTotal"];
  $pageOrTagCumLanguageTotal = $tap["pageOrTagCumLanguageTotal"];
  $pageOrTagTotal = $tap["pageOrTagTotal"];
  $drilldownTotal = $tap["drilldownTotal"];
  $monthOrYearTotal = $tap["monthOrYearTotal"];
  $pageOrTagCumLanguageCumDrilldownPercentage = $tap["pageOrTagCumLanguageCumDrilldownPercentage"];
  $pageOrTagCumLanguageCumMonthOrYearPercentage = $tap["pageOrTagCumLanguageCumMonthOrYearPercentage"];
  $drilldownCumMonthOrYearPercentage = $tap["drilldownCumMonthOrYearPercentage"];
  $pageOrTagCumLanguagePercentage = $tap["pageOrTagCumLanguagePercentage"];
  $pageOrTagPercentage = $tap["pageOrTagPercentage"];
  $drilldownPercentage = $tap["drilldownPercentage"];
  $monthOrYearPercentage = $tap["monthOrYearPercentage"];

  function cmp($firstPage, $secondPage) {
    global $pageOrTagTotal;
    if (intval($pageOrTagTotal[$firstPage]) == intval($pageOrTagTotal[$secondPage])) {
      return 0;
    }
    return (intval($pageOrTagTotal[$firstPage]) > intval($pageOrTagTotal[$secondPage])) ? -1 : 1;
  }

  switch($sort) {
    case "desc" :
      usort($pageOrTagList, "cmp");
      break;
    case "asc" :
      usort($pageOrTagList, "cmp");
      $pageOrTagList = array_reverse($pageOrTagList);
      break;
    case "alphabetical" :
      sort($pageOrTagList);
      break;
  }

  #Tag list fetching
  if ($pageOrTagAdvice=='page') {
     $tagListByPages = getTagListByPageList($pageOrTagList,$languageList);
  }
  #Pre-table warnings
    
  if ($monthOrYearAdvice=='year') {
    print "<strong>For speed and consistency reasons, we do <em>not</em> include the current month in totals for the current year</strong><br><br>";
  }
  flush();
  #Table header row
  print '<table border="1">';
  $headerString = "<tr><th>".ucfirst($monthOrYearAdvice)."</th>";
  foreach($pageOrTagList as $pageOrTag) {
    foreach($languageList as $language) {
      foreach($drilldownList as $drilldown) {
        $shortDescriptor = getShortDescriptor($drilldown);
        if ($pageOrTagAdvice=='page') {
          $headerString .= '<th>'.$shortDescriptor.' of page <a href="'. getPageUrl($pageOrTag,$language). '" title="'.$pageOrTag.' (read page on Wikipedia)">' . $pageOrTag.'</a>';
        } elseif ($pageOrTagAdvice=='tag' and $monthOrYearAdvice=='month') {
          $headerString .= '<th>'.$shortDescriptor.' of pages with tag <a href="https://wikipediaviews.org/displayviewsformultiplemonths.php?tag='.urlencode($pageOrTag).'&language='.$language.'&drilldown='.$drilldown.'&allmonths=allmonths">'.$pageOrTag.'</a>';
        } elseif ($pageOrTagAdvice=='tag' and $monthOrYearAdvice=='year') {
          $headerString .= '<th>'.$shortDescriptor.' of pages with tag <a href="https://wikipediaviews.org/displayviewsformultipleyears.php?tag='.urlencode($pageOrTag).'&language='.$language.'&drilldown='.$drilldown.'&allyears=allyears">'.$pageOrTag.'</a>';
        }
        if (count($languageList) > 1) {
          $headerString .= ", language ".$language;
        }
        if (count($drilldownList) > 1) {
          $headerString .= ", drilldown ".$drilldown;
        }
        $headerString .= '</th>';
      }
      if (count($drilldownList) > 1 and count($pageOrTagList) * count($languageList) > 1) {
        if ($pageOrTagAdvice=='page') {
          $headerString .= '<th>'.$shortDescriptor.' of page <a href="'. getPageUrl($pageOrTag,$language). '" title="'.$pageOrTag.' (read page on Wikipedia)">' . $pageOrTag.'</a>';
          if (count($languageList) > 1) {
            $headerString .= ', language '.$language;
          }
          $headerString .= ', sum over drilldowns</th>';
        } elseif ($pageOrTagAdvice=='tag' and $monthOrYearAdvice='month') {
          $headerString .= '<th>'.$shortDescriptor.' of pages with tag <a href="'. getPageUrl($pageOrTag,$language). '" title="'.$pageOrTag.' (read page on Wikipedia)">' . $pageOrTag.'</a>';
          if (count($languageList) > 1) {
            $headerString .= ', language '.$language;
          }
          $headerString .= ', sum over drilldowns</th>';
        } elseif ($pageOrTagAdvice=='tag' and $monthOrYearAdvice=='year') {
          $headerString .= '<th>'.$shortDescriptor.' of pages with tag <a href="https://wikipediaviews.org/displayviewsformultipleyears.php?tag='.urlencode($pageOrTag).'&language='.$language.'&drilldown='.$drilldown.'&allyears=allyears">'.$pageOrTag.'</a>';
          if (count($languageList) > 1) {
            $headerString .= ', language '.$language;
          }
          $headerString .= ', sum over drilldowns</th>';
        }
      }
    }
    if (count($pageOrTagList) > 1 and count($languageList) > 1) { ## Summary column across languages and drilldowns, for a given page or tag
      $headerString .= '<th><strong>'.$pageOrTag.', sum over languages';
      if (count($drilldownList) > 1) {
        $headerString .= ' and  drilldowns</strong></th>';
      } else {
        $headerString .= '</strong></th>';
      }
    }
  }
  if (count($pageOrTagList) * count($languageList) > 1 and count($drilldownList) > 1) {
    foreach ($drilldownList as $drilldown) {
      $headerString .= '<th>Total, drilldown '.$drilldown.'</th>';
      $headerString .= '<th>Percentage, drilldown '.$drilldown.'</th>';
    }
  }
  if (count($pageOrTagList) * count($languageList) * count($drilldownList) > 1) {
    $headerString .="<th>Total</th>";
  }
  if (count($monthOrYearList) > 1) {
    $headerString.='<td><strong>Percentage</strong></td>';
  }
  $headerString .= '</tr>';
  print $headerString;
  
  ##Data rows
  foreach($monthOrYearList as $monthOrYear) { #Prints one row of the table
    $monthOrYearRowString = '<tr><td>'.$monthOrYear.'</td>';
    foreach($pageOrTagList as $pageOrTag) { #Computes one cell entry
      foreach($languageList as $language) {
        foreach($drilldownList as $drilldown) {
          $viewcount = $viewCountArray[$pageOrTag][$language][$drilldown][$monthOrYear];
          if ($pageOrTagAdvice=='page' and $monthOrYearAdvice=='month') {
            $monthOrYearRowString .= printMonthViewCount($pageOrTag,$monthOrYear,$language,$drilldown,$viewcount,$numericDisplayFormat);
          } elseif ($pageOrTagAdvice=='page' and $monthOrYearAdvice=='year') {
            $monthOrYearRowString .= printYearViewCount($pageOrTag,$monthOrYear,$language,$drilldown,$viewcount,$numericDisplayFormat);
          } elseif ($pageOrTagAdvice=='tag' and $monthOrYearAdvice=='month') {
            $monthOrYearRowString .= printTagViewCount($pageOrTag,$monthOrYear,$language,$drilldown,$viewcount,$numericDisplayFormat);
          } elseif ($pageOrTagAdvice=='tag' and $monthOrYearAdvice=='year') {
            $monthOrYearRowString .= printTagViewCountByYear($pageOrTag,$monthOrYear,$language,$drilldown,$viewcount,$numericDisplayFormat);
          }
        }
        if (count($drilldownList) > 1 and count($pageOrTagList) * count($languageList) > 1) {
          $viewcount = $pageOrTagCumLanguageCumMonthOrYearTotal[$pageOrTag][$language][$monthOrYear];
          $monthOrYearRowString .= '<td align="right"><strong><element title="'.numericDisplay($viewcount, $numericDisplayFormat).'">'.numericDisplay($viewcount, $numericDisplayFormat).'</element></strong></td>';
        }
      }
      if (count($pageOrTagList) > 1 and count($languageList) > 1) { ## Summary column across languages and drilldowns, for a given page or tag
        $viewcount = $pageOrTagCumMonthOrYearTotal[$pageOrTag][$monthOrYear];
  	if ($pageOrTagAdvice=='page' and $monthOrYearAdvice=='month') {
  	  $monthOrYearRowString .= printMonthViewCount($pageOrTag,$monthOrYear,"all","all",$viewcount,$numericDisplayFormat);
  	} elseif ($pageOrTagAdvice=='page' and $monthOrYearAdvice=='year') {
  	  $monthOrYearRowtring .= printYearViewCount($pageOrTag,$monthOrYear,"all","all",$viewcount,$numericDisplayFormat);
  	} elseif ($pageOrTagAdvice=='tag' and $monthOrYearAdvice=='month') {
  	  $monthOrYearRowString .= printTagViewCount($pageOrTag,$monthOrYear,"all","all",$viewcount,$numericDisplayFormat);
  	} elseif ($pageOrTagAdvice=='tag' and $monthOrYearAdvice=='year') {
  	  $monthOrYearRowString .= printTagViewCountByYear($pageOrTag,$monthOrYear,"all","all",$viewcount,$numericDisplayFormat);
        }
      }
    }
    if (count($pageOrTagList) * count($languageList) > 1 and count($drilldownList) > 1) {
      foreach ($drilldownList as $drilldown) {
        $monthOrYearRowString .= '<td align="right"><strong><element title="'.$drilldownCumMonthOrYearTotal[$drilldown][$monthOrYear].'">'.numericDisplay($drilldownCumMonthOrYearTotal[$drilldown][$monthOrYear],$numericDisplayFormat).'</element></strong></td>';
        if (count($monthOrYearList) > 1) {
          $monthOrYearRowString .= '<td align="right"><strong>'.$drilldownCumMonthOrYearPercentage[$drilldown][$monthOrYear].'</strong></td>';
        }
      }
    }
    if (count($pageOrTagList) * count($languageList) * count($drilldownList) > 1) {
      $monthOrYearRowString .='<td align="right"><strong><element title="'.$monthOrYearTotal[$monthOrYear].'">'.numericDisplay($monthOrYearTotal[$monthOrYear],$numericDisplayFormat).'</element></strong></td>';
    }
    if (count($monthOrYearList) > 1) {
      $monthOrYearRowString .='<td align="right"><strong>'.$monthOrYearPercentage[$monthOrYear].'</strong></td></tr>';
    }
    print $monthOrYearRowString;
  }
    
  ##Totals row
  if (count($monthOrYearList) > 1) {
    $totalsRowString="<tr><td><strong>Total</strong></td>";
    foreach($pageOrTagList as $pageOrTag) { #Prints bottom row with totals
      foreach($languageList as $language) {
        foreach($drilldownList as $drilldown) {
          $totalsRowString .= '<td align="right"><strong><element title="'.$pageOrTagCumLanguageCumDrilldownTotal[$pageOrTag][$language][$drilldown].'">'.numericDisplay($pageOrTagCumLanguageCumDrilldownTotal[$pageOrTag][$language][$drilldown],$numericDisplayFormat).'</element></strong></td>';
        }
	if (count($drilldownList) > 1 and count($pageOrTagList) * count($languageList) > 1) {
          $totalsRowString .= '<td align="right"><strong><element title="'.$pageOrTagCumLanguageTotal[$pageOrTag][$language].'">'.numericDisplay($pageOrTagCumLanguageTotal[$pageOrTag][$language],$numericDisplayFormat).'</element></strong></td>';
        }
      }
      if (count($pageOrTagList) > 1 and count($languageList) > 1) { ## Summary column across languages and drilldowns, for a given page or tag
         $totalsRowString .='<td align="right"><strong><element title="'.$pageOrTagTotal[$pageOrTag].'">'.numericDisplay($pageOrTagTotal[$pageOrTag],$numericDisplayFormat).'</element></strong></td>';
      }
    }
    if (count($pageOrTagList) * count($languageList) > 1 and count($drilldownList) > 1) {
      foreach($drilldownList as $drilldown) {
        $totalsRowString .= '<td align="right"><strong><element title="'.$drilldownTotal[$drilldown].'">'.numericDisplay($drilldownTotal[$drilldown],$numericDisplayFormat).'</element></strong></td>';
        $totalsRowString .= '<td align="right"><strong>'.$drilldownPercentage[$drilldown].'</strong></td>';
      }
    }
    if (count($pageOrTagList) * count($languageList) * count($drilldownList) > 1) { 
      $totalsRowString .= '<td align="right"><strong><element title="'.$grandTotal.'">'.numericDisplay($grandTotal,$numericDisplayFormat).'</element></strong></td>';
    }
    $totalsRowString .= '<td align="right"><strong>100</strong></td></tr>';
    print $totalsRowString;
  }

  ##Percentages row
  if (count($pageOrTagList) * count($languageList) * count($drilldownList) > 1) {
    $percentagesRowString = "<tr><td><strong>Percentage</strong></td>";
    foreach($pageOrTagList as $pageOrTag) {
      foreach($languageList as $language) {
        foreach($drilldownList as $drilldown) {
	  $percentagesRowString .= '<td align="right"><strong>'.$pageOrTagCumLanguageCumDrilldownPercentage[$pageOrTag][$language][$drilldown].'</strong></td>';
        }
        if (count($pageOrTagList) * count($languageList) > 1 and count($drilldownList) > 1) {
          $percentagesRowString .= '<td align="right"><strong>'.$pageOrTagCumLanguagePercentage[$pageOrTag][$language].'</strong></td>';
        }
      }
      if (count($pageOrTagList) > 1 and count($languageList) > 1) { ## Summary column across languages and drilldowns, for a given page or tag
        $percentagesRowString .= '<td align="right"><strong>'.$pageOrTagPercentage[$pageOrTag].'</strong></td>';
      }
    }
    if (count($pageOrTagList) * count($languageList) > 1 and count($drilldownList) > 1) {
      foreach($drilldownList as $drilldown) {
        $percentagesRowString .= '<td align="right"><strong>'.$drilldownPercentage[$drilldown].'</strong></td>';
        $percentagesRowString .= '<td>--</td>';
      }
    }

    $percentagesRowString .= '<td align="right"><strong>100</strong></td>';
    if (count($monthOrYearList) > 1) {
      $percentagesRowString .= '<td align="right">--</td></tr>';
    }
    print $percentagesRowString;
  }

  ##Tags row
  if ($pageOrTagAdvice == 'page') {
    $tagsRowString = "<tr><td><strong>Tags</strong></td>";
    foreach ($pageOrTagList as $pageOrTag) {
      foreach ($languageList as $language) {
        $tagListForPage = $tagListByPages[$pageOrTag][$language];
        $tagCell = '<td>';
        if (count($tagListForPage) == 0) {
          $tagCell .= "--";
        }
        foreach ($tagListForPage as $tag) {
	  if ($monthOrYearAdvice == 'month') {
            $tagCell .= '<a href="https://wikipediaviews.org/displayviewsformultiplemonths.php?tag='.urlencode($tag).'&language='.$language.'&allmonths=allmonths">'.$tag.'</a> ';
	  } else {
            $tagCell .= '<a href="https://wikipediaviews.org/displayviewsformultipleyears.php?tag='.urlencode($tag).'&language='.$language.'&allyears=allyears">'.$tag.'</a> ';
	  }
        }
        $tagCell .= '</td>';
        foreach ($drilldownList as $drilldown) {  
          $tagsRowString .= $tagCell; 
        }
        if (count($pageOrTagList) * count($languageList) > 1 and count($drilldownList) > 1) {
          $tagsRowString .= $tagCell;
        }
      }
    }
    if (count($pageOrTagList) * count($languageList) > 1 and count($drilldownList) > 1) {
      foreach ($drilldownList as $drilldown) {
        $tagsRowString .= '<td>--</td><td>--</td>';
      }
    }
    if (count($pageOrTagList) * count($languageList) * count($drilldownList) > 1) {
      $tagsRowString .= '<td>--</td>';
    }
    if (count($monthOrYearList) > 1) {
      $tagsRowString .= '<td>--</td>';
    }
    $tagsRowString .= '</tr>';
    print $tagsRowString;
  }	  
  print "</table>";
  $endTime = microtime(true);
  $timeTaken = $endTime - $startTime;
  flush();
  return true;
}

function generateGraphs($pageOrTagList,$languageList,$drilldownList,$monthOrYearList,$numericDisplayFormat,$normalization='',$pageOrTagAdvice='page',$monthOrYearAdvice='month',$shortcutTag='',$cleanPermalinkUrl='') {
  global $graphTimeTaken;
  global $imagesPath;
  global $generateGraphCmdBase;
  global $generateDistribCmdBase;
  global $unifontLocation;
  global $purgePeriod;
  $graphStartTime = microtime(true);
  #Check that sizes are workable
  $sizeOverflow = checkSizes($pageOrTagList,$languageList,$drilldownList,$monthOrYearList);
  if ($sizeOverflow > 0) {
    print " Therefore, we are not constructing graphs.<br/>";
    return false;
  }
  $verticalLineExplainer = "";
  $fontParam = "";
  if (count($monthOrYearList) > 1 and max($monthOrYearList) >= '201506' and min($monthOrYearList) <= '201506') {
    $verticalLineExplainer = ' Since June 2015 is between the beginning and end of your time interval, you will see a vertical red line for that month. This is because June 2015 is the last month for which we use stats.grok.se data as our source for Wikipedia Views, and also because, starting July 2015, we have data for the drilldowns of mobile web, mobile app, desktop spider, and mobile web spider. See the <a href="/about">about page</a> for more information.';
  }
  #Collect all the numbers that need to be printed first
  $purgePeriodBackup = $purgePeriod;
  if ($purgePeriod < 0) {
    $purgePeriod = 0;
  }
  if ($pageOrTagAdvice=='page' and $monthOrYearAdvice=='month') {
    $viewCountArray = viewCountArrayByMonth($pageOrTagList,$languageList,$drilldownList,$monthOrYearList,false,$normalization,$shortcutTag);
  } elseif ($pageOrTagAdvice=='page' and $monthOrYearAdvice=='year') {
    $viewCountArray = viewCountArrayByYear($pageOrTagList,$languageList,$drilldownList,$monthOrYearList,false,$normalization);
  } elseif ($pageOrTagAdvice=='tag' and $monthOrYearAdvice=='month') {
    $viewCountArray = viewCountArrayByTagAndMonth($pageOrTagList,$languageList,$drilldownList,$monthOrYearList,false,$normalization);
  } elseif ($pageOrTagAdvice=='tag' and $monthOrYearAdvice=='year') {
    $viewCountArray = viewCountArraybyTagAndYear($pageOrTagList,$languageList,$drilldownList,$monthOrYearList,false,$normalization);
  }
  $purgePeriod = $purgePeriodBackup;

  $tap = totalsAndPercentages($pageOrTagList,$languageList,$drilldownList,$monthOrYearList,$viewCountArray);
  $grandTotal = $tap["grandTotal"];
  $pageOrTagCumMonthOrYearTotal = $tap["pageOrTagCumMonthOrYearTotal"];
  $pageOrTagCumLanguageCumDrilldownTotal = $tap["pageOrTagCumLanguageCumDrilldownTotal"];
  $pageOrTagCumLanguageCumMonthOrYearTotal = $tap["pageOrTagCumLanguageCumMonthOrYearTotal"];
  $drilldownCumMonthOrYearTotal = $tap["drilldownCumMonthOrYearTotal"];
  $pageOrTagCumLanguageTotal = $tap["pageOrTagCumLanguageTotal"];
  $pageOrTagTotal = $tap["pageOrTagTotal"];
  $drilldownTotal = $tap["drilldownTotal"];
  $monthOrYearTotal = $tap["monthOrYearTotal"];
  $pageOrTagCumLanguageCumDrilldownPercentage = $tap["pageOrTagCumLanguageCumDrilldownPercentage"];
  $pageOrTagCumLanguageCumMonthOrYearPercentage = $tap["pageOrTagCumLanguageCumMonthOrYearPercentage"];
  $drilldownCumMonthOrYearPercentage = $tap["drilldownCumMonthOrYearPercentage"];
  $pageOrTagCumLanguagePercentage = $tap["pageOrTagCumLanguagePercentage"];
  $drilldownPercentage = $tap["drilldownPercentage"];
  $monthOrYearPercentage = $tap["monthOrYearPercentage"];

  if (count($languageList) > 1 or $languageList[0] != 'en') {
    $fontParam = " --font ".$unifontLocation. " ";
  }
  $fullOutput = "";

  $headerString = ucfirst($monthOrYearAdvice);
  foreach($pageOrTagList as $pageOrTag) {
    foreach($languageList as $language) {
      foreach ($drilldownList as $drilldown) {
        $headerString .= "|".$pageOrTag;
        if (count($languageList) > 1) {
          $headerString .= " ".$language;
        }
        if (count($drilldownList) > 1) {
          $headerString .= " ".$drilldown;
        }
      }
    }
  }
  if (count($pageOrTagList) * count($languageList) * count($drilldownList) > 1) {
    $headerString .="|Total";
  }
  if (count($monthOrYearList) > 1) {
    $headerString .="|Percentage";
  }
  $headerString .="\n";
  $fullOutput .= $headerString;
  foreach($monthOrYearList as $monthOrYear) {
    $stringToPrint = $monthOrYear;
    $total = 0;
    foreach($pageOrTagList as $pageOrTag) {
      foreach($languageList as $language) {
        foreach($drilldownList as $drilldown) { 
          $viewcount = $viewCountArray[$pageOrTag][$language][$drilldown][$monthOrYear];
          $numericViewCount = 0;
          $numericViewCount = $numericViewCount + $viewcount;
          $stringToPrint .= "|".$numericViewCount;
        }
      }
    }
    if (count($pageOrTagList) * count($languageList) * count($drilldownList) > 1) {
      $stringToPrint .="|".$monthOrYearTotal[$monthOrYear];
    }
    if (count($monthOrYearList) > 1) {
      $stringToPrint .="|".$monthOrYearPercentage[$monthOrYear];
    }
    $stringToPrint .="\n";
    $fullOutput .= $stringToPrint;
  }
  $totalsRowString = "Total";
  foreach($pageOrTagList as $pageOrTag) {
    foreach($languageList as $language) {
      foreach($drilldownList as $drilldown) {
        $totalsRowString .= "|".$pageOrTagCumLanguageCumDrilldownTotal[$pageOrTag][$language][$drilldown];
      }
    }
  }
  if (count($pageOrTagList) * count($languageList) * count($drilldownList) > 1) {
    $totalsRowString .= "|".$grandTotal;
  }
  if (count($monthOrYearList) > 1) {
    $totalsRowString .="|100";
  }
  $totalsRowString .= "\n";
  $fullOutput .= $totalsRowString;
  $percentagesRowString = "Percentage";
  foreach($pageOrTagList as $pageOrTag) {
    foreach($languageList as $language) {
      foreach($drilldownList as $drilldown) {
        $percentagesRowString .= "|".$pageOrTagCumLanguageCumDrilldownPercentage[$pageOrTag][$language][$drilldown];
      }
    }
  }
  $percentagesRowString .= "|100";
  $percentagesRowString .= "\n";
  $fullOutput .= $percentagesRowString;

  # Drilldown output
  $drilldownOutput = "";
  if (count($pageOrTagList) * count($languageList) > 1 and count($drilldownList) > 1) {
    $headerString = ucfirst($monthOrYearAdvice);
    foreach ($drilldownList as $drilldown) {
      $headerString .= "|".$drilldown;
    }
    $headerString .="|Total";
    if (count($monthOrYearList) > 1) {
      $headerString .="|Percentage";
    }
    $headerString .="\n";
    $drilldownOutput .= $headerString;
    foreach($monthOrYearList as $monthOrYear) {
      $stringToPrint = $monthOrYear;
      $total = 0;
      foreach($drilldownList as $drilldown) { 
        $viewcount = $drilldownCumMonthOrYearTotal[$drilldown][$monthOrYear];
        $numericViewCount = 0;
        $numericViewCount = $numericViewCount + $viewcount;
        $stringToPrint .= "|".$numericViewCount;
      }
      $stringToPrint .="|".$monthOrYearTotal[$monthOrYear];
      if (count($monthOrYearList) > 1) {
        $stringToPrint .="|".$monthOrYearPercentage[$monthOrYear];
      }
      $stringToPrint .="\n";
      $drilldownOutput .= $stringToPrint;
    }
    $totalsRowString = "Total";
    foreach($drilldownList as $drilldown) {
      $totalsRowString .= "|".$drilldownTotal[$drilldown];
    }
    $totalsRowString .= "|".$grandTotal;
    $totalsRowString .= "\n";
    $drilldownOutput .= $totalsRowString;
    $percentagesRowString = "Percentage";
    foreach($drilldownList as $drilldown) {
      $percentagesRowString .= "|".$drilldownPercentage[$drilldown];
    }
    $percentagesRowString .= "|100";
    $percentagesRowString .= "\n";
    $drilldownOutput .= $percentagesRowString;
  }

  # pageOrTag output
  $pageOrTagOutput = "";
  if (count($languageList) * count($drilldownList) > 1 and count($pageOrTagList) > 1) {
    $headerString = ucfirst($monthOrYearAdvice);
    foreach ($pageOrTagList as $pageOrTag) {
      $headerString .= "|".$pageOrTag;
    }
    $headerString .="|Total";
    if (count($monthOrYearList) > 1) {
      $headerString .="|Percentage";
    }
    $headerString .="\n";
    $pageOrTagOutput .= $headerString;
    foreach($monthOrYearList as $monthOrYear) {
      $stringToPrint = $monthOrYear;
      $total = 0;
      foreach($pageOrTagList as $pageOrTag) {
        $viewcount = intval($pageOrTagCumMonthOrYearTotal[$pageOrTag][$monthOrYear]);
        $stringToPrint .= "|".$viewcount;
      }
      $stringToPrint .="|".$monthOrYearTotal[$monthOrYear];
      if (count($monthOrYearList) > 1) {
        $stringToPrint .="|".$monthOrYearPercentage[$monthOrYear];
      }
      $stringToPrint .="\n";
      $pageOrTagOutput .= $stringToPrint;
    }
    $totalsRowString = "Total";
    foreach($pageOrTagList as $pageOrTag) {
      $totalsRowString .= "|";
      if (array_key_exists($pageOrTag, $pageOrTagTotal)) {
        $totalsRowString .= $pageOrTagTotal[$pageOrTag];
      }
    }
    if (count($pageOrTagList) > 1) {
      $totalsRowString .= "|".$grandTotal;
    }
    if (count($monthOrYearList) > 1) {
      $totalsRowString .="|100";
    }
    $totalsRowString .= "\n";
    $pageOrTagOutput .= $totalsRowString;
    $percentagesRowString = "Percentage";
    foreach($pageOrTagList as $pageOrTag) {
      $percentagesRowString .= "|";
      if (array_key_exists($pageOrTag, $pageOrTagPercentage)) {
        $percentagesRowString .= $pageOrTagPercentage[$pageOrTag];
      }
    }
    $percentagesRowString .= "|100";
    $percentagesRowString .= "\n";
    $pageOrTagOutput .= $percentagesRowString;
  }

  # pageOrTag cum language output
  $pageOrTagCumLanguageOutput = "";
  if (count($drilldownList) > 1 and count($languageList) > 1) {
    $headerString = ucfirst($monthOrYearAdvice);
    foreach ($pageOrTagList as $pageOrTag) {
      foreach ($languageList as $language) {
        $headerString .= "|".$pageOrTag;
        if (count($languageList) > 1) {
          $headerString .= " ".$language;
        }
      }
    }
    $headerString .="|Total";
    if (count($monthOrYearList) > 1) {
      $headerString .="|Percentage";
    }
    $headerString .="\n";
    $pageOrTagCumLanguageOutput .= $headerString;
    foreach($monthOrYearList as $monthOrYear) {
      $stringToPrint = $monthOrYear;
      $total = 0;
      foreach($pageOrTagList as $pageOrTag) {
        foreach($languageList as $language) {
          $viewcount = $pageOrTagCumLanguageCumMonthOrYearTotal[$pageOrTag][$language][$monthOrYear];
          $numericViewCount = 0;
          $numericViewCount = $numericViewCount + $viewcount;
          $stringToPrint .= "|".$numericViewCount;
        }
      }
      $stringToPrint .="|".$monthOrYearTotal[$monthOrYear];
      if (count($monthOrYearList) > 1) {
        $stringToPrint .="|".$monthOrYearPercentage[$monthOrYear];
      }
      $stringToPrint .="\n";
      $pageOrTagCumLanguageOutput .= $stringToPrint;
    }
    $totalsRowString = "Total";
    foreach($pageOrTagList as $pageOrTag) {
      foreach($languageList as $language) {
        $totalsRowString .= "|".$pageOrTagCumLanguageTotal[$pageOrTag][$language];
      }
    }
    if (count($pageOrTagList) > 1) {
      $totalsRowString .= "|".$grandTotal;
    }
    if (count($monthOrYearList) > 1) {
      $totalsRowString .="|100";
    }
    $totalsRowString .= "\n";
    $pageOrTagCumLanguageOutput .= $totalsRowString;
    if (count($pageOrTagList) > 0) {
      $percentagesRowString = "Percentage";
      foreach($pageOrTagList as $pageOrTag) {
        foreach($languageList as $language) {
          $percentagesRowString .= "|".$pageOrTagCumLanguagePercentage[$pageOrTag][$language];
	}
      }
      $percentagesRowString .= "|100";
      $percentagesRowString .= "\n";
      $pageOrTagCumLanguageOutput .= $percentagesRowString;
    }
  }

  $fileName = hash("md5",$cleanPermalinkUrl);
  $filePathBase = $imagesPath . $fileName;
  $dataHasChanged = false;
  if (file_exists($filePathBase . ".csv") == false) {
    # print "<br/>There is no file with the CSV $filePathBase . csv, so we are writing it out<br/>";
    file_put_contents($filePathBase . ".csv", $fullOutput);
    $dataHasChanged = true;
  } else {
    $previousOutput = file_get_contents($filePathBase . ".csv");
    if ($previousOutput != $fullOutput) {
      # print "<br/>We have a cached file but the underlying data has changed<br/><br/>";
      $dataHasChanged = true;
      file_put_contents($filePathBase . ".csv", $fullOutput);
    } else {
      # print "<br/>The cached file contents match the existing data<br/><br/>";
    }
  }
  if (count($pageOrTagList) * count($languageList) * count($drilldownList) > 1) {
    $addendum = "";
    $cmdToExecute = $generateDistribCmdBase . $fontParam . " " . $filePathBase . ".csv " . $filePathBase . "-distrib.png ";
    if ($numericDisplayFormat == "log") {
      $cmdToExecute = $cmdToExecute . " --log10 ";
      $addendum .= ", taking logs";
    }
    if (count($pageOrTagList) * count($languageList) * count($drilldownList) <= 30) {
      $cmdToExecute = $cmdToExecute . " --label --label_max_len 40 ";
      $addendum .= ", showing labels as there are 30 or fewer items";
    } else {
      $addendum .= ", not showing labels as there are more than 30 items";
    }
    if (count($pageOrTagList) * count($languageList) * count($drilldownList) <= 50) {
      $entityDescriptor = "bar";
      $cmdToExecute = $cmdToExecute . " --plot_kind bar ";
      $addendum .= ", using bars as there are 50 or fewer items";
    } else {
      $entityDescriptor = "point in the line graph";
      $cmdToExecute = $cmdToExecute . " --plot_kind line ";
      $addendum .= ", using lines (not bars) as there are more than 50 items";
    }
    if ($dataHasChanged == true or file_exists($filePathBase . "-distrib.png") == false) {
      if (file_exists($filePathBase . "-distrib.png") == true) {
        exec("rm ".$filePathBase . "-distrib.png");
      }
      exec($cmdToExecute);
    }
    print "<br/><br/>";
    print '<strong>Distribution of pageviews; each '.$entityDescriptor.' represents a combination of '.$pageOrTagAdvice.', language, and drilldown'.$addendum.'</strong> (<a href="/images/'.$fileName.'.csv">underlying CSV using pipe (|) as separator</a>)<br/>';
    print '<img src="/images/'.$fileName.'-distrib.png" alt="Image of pageviews distribution should have loaded here"></img>';
  }
  if (count($monthOrYearList) > 1) {
    $cmdToExecute = $generateGraphCmdBase . " " . $filePathBase . ".csv " . $filePathBase . "-timeseries.png ";
    if ($numericDisplayFormat == "log") {
      $cmdToExecute = $cmdToExecute . " --log10";
    }
    if ($dataHasChanged == true or file_exists($filePathBase . "-timeseries.png") == false) {
      if (file_exists($filePathBase . "-timeseries.png") == true) {
        exec("rm ".$filePathBase . "-timeseries.png");
      }
      exec($cmdToExecute);
    }
    print "<br/><br/>";
    if (count($pageOrTagList) * count($languageList) * count($drilldownList) > 30) {
      $addendum = ", restricted to the top 30 by total across months";
    } else {
      $addendum = "";
    }
    if (count($pageOrTagList) * count($languageList) > 1 and count($drilldownList) > 1) {
      print "<strong>Time series of data; includes overall total and a separate curve for each combination of ".$pageOrTagAdvice.", language, and drilldown".$addendum." below:</strong>"; 
    } else if (count($drilldownList) > 1) {
      print "<strong>Time series of data; includes overall total and a separate curve for each drilldown".$addendum." below:</strong>";
    } else if (count($pageOrTagList) * count($languageList) > 1) {
      print "<strong>Time series of data; includes overall total and a separate curve for each combination of ".$pageOrTagAdvice."and language ".$addendum." below:</strong>";
    } else {
      print "<strong>Time series of data below:</strong>";
    }
    print '(<a href="/images/'.$fileName.'.csv">underlying CSV using pipe (|) as separator</a>)'.$verticalLineExplainer.'<br/>';
    print '<img src="/images/'.$fileName.'-timeseries.png" alt="Graph of pageviews should have loaded here"></img>';
  }

  if (count($pageOrTagList) * count($languageList) > 1 and count($drilldownList) > 1) {
    # Construct drilldown-grouped data
    $addendum = "";
    $drilldownFileName = $fileName."-drilldown";
    $drilldownFilePathBase = $imagesPath . $drilldownFileName;
    file_put_contents($drilldownFilePathBase . ".csv", $drilldownOutput);

    # Construct page or tag
    $cmdToExecute = $generateDistribCmdBase . " " . $drilldownFilePathBase . ".csv " . $drilldownFilePathBase . "-distrib.png ";
    if ($numericDisplayFormat == "log") {
      $cmdToExecute = $cmdToExecute . " --log10 ";
    }
    if (count($drilldownList) <= 30) {
      $cmdToExecute = $cmdToExecute . " --label --label_max_len 40 ";
      $addendum .= ", showing labels as there are 30 or fewer items";
    } else {
      $addendum .= ", not showing labels as there are more than 30 items";
    }
    if (count($drilldownList) <= 50) {
      $entityDescriptor = "bar";
      $cmdToExecute = $cmdToExecute . " --plot_kind bar ";
      $addendum .= ", using bars as there are 50 or fewer items";
    } else {
      $entityDescriptor = "point in the line graph";
      $cmdToExecute = $cmdToExecute . " --plot_kind line ";
      $addendum .= ", using lines (not bars) as there are more than 50 items";
    }
    # print("Going to try executing ".$cmdToExecute."<br>");
    if ($dataHasChanged == true or file_exists($drilldownFilePathBase . "-distrib.png") == false) {
      if (file_exists($drilldownFilePathBase . "-distrib.png") == true) {
        exec("rm ".$drilldownFilePathBase . "-distrib.png");
      }
      exec($cmdToExecute);
    }
    print "<br/><br/>";
    print '<strong>Distribution of pageviews; each '.$entityDescriptor.' represents a drilldown, summed over the other dimensions'.$addendum.'</strong> (<a href="/images/'.$drilldownFileName.'.csv">underlying CSV using pipe (|) as separator</a>)<br/>';
    print '<img src="/images/'.$drilldownFileName.'-distrib.png" alt="Image of pageviews distribution should have loaded here"></img>';

    if (count($monthOrYearList) > 1) {
      $cmdToExecute = $generateGraphCmdBase . " " . $drilldownFilePathBase . ".csv " . $drilldownFilePathBase . "-timeseries.png";
      if ($numericDisplayFormat == "log") {
        $cmdToExecute = $cmdToExecute . " --log10";
      }
      if ($dataHasChanged == true or file_exists($drilldownFilePathBase . "-timeseries.png") == false) {
        if (file_exists($drilldownFilePathBase . "-timeseries.png") == true) {
	  exec("rm ".$drilldownFilePathBase . "-timeseries.png");
	}
        exec($cmdToExecute);
      }
      print "<br><br>";
      print '<strong>Time series of data; one curve for total by each drilldown, one curve for total, below:</strong> (<a href="/images/'.$drilldownFileName.'.csv">underlying CSV using pipe (|) as separator</a>).'.$verticalLineExplainer.'<br/>';
      print '<img src="/images/'.$drilldownFileName.'-timeseries.png" alt="Graph of pageviews should have loaded here"></img>';
    }
  }

  if (count($languageList) > 1 and count($drilldownList) > 1) {
    $addendum = "";
    $pageOrTagCumLanguageFileName = $fileName."-".$pageOrTagAdvice."lang";
    $pageOrTagCumLanguageFilePathBase = $imagesPath . $pageOrTagCumLanguageFileName;
    file_put_contents($pageOrTagCumLanguageFilePathBase . ".csv", $pageOrTagCumLanguageOutput);
    $cmdToExecute = $generateDistribCmdBase . $fontParam . " " . $pageOrTagCumLanguageFilePathBase . ".csv " . $pageOrTagCumLanguageFilePathBase . "-distrib.png ";
    if ($numericDisplayFormat == "log") {
      $cmdToExecute = $cmdToExecute . " --log10 ";
    }
    if (count($pageOrTagList) * count($languageList) <= 30) {
      $cmdToExecute = $cmdToExecute . " --label --label_max_len 40 ";
      $addendum .= ", showing labels as there are 30 or fewer items";
    } else {
      $addendum .= ", not showing labels as there are more than 30 items";
    }
    if (count($pageOrTagList) * count($languageList) <= 50) {
      $entityDescriptor = "bar";
      $cmdToExecute = $cmdToExecute . " --plot_kind bar ";
      $addendum .= ", using bars as there are 50 or fewer items";
    } else {
      $entityDescriptor = "point in the line graph";
      $cmdToExecute = $cmdToExecute . " --plot_kind line ";
      $addendum .= ", using lines (not bars) as there are more than 50 items";
    }
    # print("Going to try executing ".$cmdToExecute."<br>");
    if ($dataHasChanged == true or file_exists($pageOrTagCumLanguageFilePathBase . "-distrib.png") == false) {
      if (file_exists($pageOrTagCumLanguageFilePathBase . "-distrib.png") == true) {
        exec("rm ".$pageOrTagCumLanguageFilePathBase . "-distrib.png");
      }
      exec($cmdToExecute);
    }
    print "<br/><br/>";
    print '<strong>Distribution of pageviews; each '.$entityDescriptor.' represents a combination of '.$pageOrTagAdvice.' and language, summed up over drilldowns'.$addendum.'</strong> (<a href="/images/'.$pageOrTagCumLanguageFileName.'.csv">underlying CSV using pipe (|) as separator</a>)<br/>';
    print '<img src="/images/'.$pageOrTagCumLanguageFileName.'-distrib.png" alt="Image of pageviews distribution should have loaded here"></img>';

    if (count($monthOrYearList) > 1) {
      $cmdToExecute = $generateGraphCmdBase . " " . $pageOrTagCumLanguageFilePathBase . ".csv " . $pageOrTagCumLanguageFilePathBase . "-timeseries.png";
      if ($numericDisplayFormat == "log") {
        $cmdToExecute = $cmdToExecute . " --log10";
      }
      if ($dataHasChanged == true or file_exists($pageOrTagCumLanguageFilePathBase . "-timeseries.png") == false) {
        if (file_exists($pageOrTagCumLanguageFilePathBase . "-timeseries.png") == true) {
          exec("rm ".$pageOrTagCumLanguageFilePathBase . "-timeseries.png");
        } 
        exec($cmdToExecute);
      }
      if (count($pageOrTagList) * count($languageList) > 30) {
        $addendum = ", restricted to the top 30 by total across months";
      } else {
        $addendum = "";
      }
      print "<br><br>";
      print '<strong>Time series of data; one curve for total by each '.$pageOrTagAdvice.', one curve for total'.$addendum.', below:</strong> (<a href="/images/'.$pageOrTagCumLanguageFileName.'.csv">underlying CSV using pipe (|) as separator</a>)'.$verticalLineExplainer.'<br/>';
      print '<img src="/images/' . $pageOrTagCumLanguageFileName . '-timeseries.png" alt="Graph of pageviews should have loaded here"></img>';
    }
  }
  if (count($languageList) * count($drilldownList) > 1 and count($pageOrTagList) > 1) {
    # Construct page or tag
    $addendum = ""; 
    $pageOrTagFileName = $fileName."-".$pageOrTagAdvice;
    $pageOrTagFilePathBase = $imagesPath . $pageOrTagFileName;
    file_put_contents($pageOrTagFilePathBase . ".csv", $pageOrTagOutput);
    $cmdToExecute = $generateDistribCmdBase . $fontParam . " " . $pageOrTagFilePathBase . ".csv " . $pageOrTagFilePathBase . "-distrib.png ";
    if ($numericDisplayFormat == "log") {
      $cmdToExecute = $cmdToExecute . " --log10 ";
      $addendum .= ", taking logs";
    }
    if (count($pageOrTagList) <= 30) {
      $cmdToExecute = $cmdToExecute . " --label --label_max_len 40 ";
      $addendum .= ", showing labels as there are 30 or fewer items";
    } else {
      $addendum .= ", not showing labels as there are more than 30 items";
    }
    if (count($pageOrTagList) <= 50) {
      $entityDescriptor = "bar";
      $cmdToExecute = $cmdToExecute . " --plot_kind bar ";
      $addendum .= ", using bars as there are 50 or fewer items";      
    } else {
      $entityDescriptor = "point in the line graph";
      $cmdToExecute = $cmdToExecute . " --plot_kind line ";
      $addendum .= ", using lines (not bars) as there are more than 50 items";      
    }
    # print("Going to try executing ".$cmdToExecute."<br>");
    if ($dataHasChanged == true or file_exists($pageOrTagFilePathBase . "-distrib.png") == false) {
      if (file_exists($pageOrTagFilePathBase . "-distrib.png") == true) {
        exec("rm ".$pageOrTagFilePathBase . "-distrib.png");
      }
      exec($cmdToExecute);
    }
    print "<br/><br/>";
    print '<strong>Distribution of pageviews; each '.$entityDescriptor.' represents a '.$pageOrTagAdvice.' summed up over the selected languages and drilldowns'.$addendum.'</strong> (<a href="/images/'.$pageOrTagFileName.'.csv">underlying CSV using pipe (|) as separator</a>)<br/>';
    print '<img src="/images/'.$pageOrTagFileName.'-distrib.png" alt="Image of pageviews distribution should have loaded here"></img>';

    if (count($monthOrYearList) > 1) {
      $cmdToExecute = $generateGraphCmdBase . " " . $pageOrTagFilePathBase . ".csv " . $pageOrTagFilePathBase . "-timeseries.png";
      if ($numericDisplayFormat == "log") {
        $cmdToExecute = $cmdToExecute . " --log10";
      }
      if ($dataHasChanged == true or file_exists($pageOrTagFilePathBase . "-timeseries.png") == false) {
        if (file_exists($pageOrTagFilePathBase . "-timeseries.png") == true) {
          exec("rm ".$pageOrTagFilePathBase . "-timeseries.png");
        }
        exec($cmdToExecute);
      }
      if (count($pageOrTagList) > 30) {
        $addendum = ", restricted to the top 30 by total across months";
      } else {
        $addendum = "";
      }
      print "<br><br>";
      print '<strong>Time series of data; one curve for total by each '.$pageOrTagAdvice.', one curve for total'.$addendum.', below:</strong> (<a href="/images/'.$pageOrTagFileName.'.csv">underlying CSV using pipe (|) as separator</a>)<br/>';
      print '<img src="/images/' . $pageOrTagFileName . '-timeseries.png" alt="Graph of pageviews should have loaded here"></img>';
    }
  }

  $graphEndTime = microtime(true);
  $graphTimeTaken = $graphEndTime - $graphStartTime;
}

?>
