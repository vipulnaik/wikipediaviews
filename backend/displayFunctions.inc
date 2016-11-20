<?php

include_once("globalvariables/passwordfile.inc");

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

function totalsAndPercentages($pageOrTagList,$languageList,$drilldownList,$monthOrYearList,$viewcountarray) {
  foreach ($pageOrTagList as $pageOrTag) {
    foreach ($languageList as $language) {
      foreach ($drilldownList as $drilldown) {
        foreach ($monthOrYearList as $monthOrYear) {
          $increment = intval($viewcountarray[$pageOrTag][$language][$drilldown][$monthOrYear]);
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
  } else {
    return '<td align="right"><a href="'.getpageviewsurl($page,$month,$language,$drilldown).'" title="'.monthviewtooltip($viewcount).'">'.numericDisplay($viewcount,$numericDisplayFormat).'</a></td>';
  }
}

function printYearViewCount($page,$year,$language,$drilldown,$viewcount,$numericDisplayFormat) {
  if ($drilldown == "all") {
    return '<td align="right"><strong><a title="'.yearviewtooltip($viewcount).'">'.numericDisplay($viewcount,$numericDisplayFormat).'</a></strong></td>';
  } else {
    return '<td align="right"><a href="'.getannualpageviewsurl($page,$year,$language,$drilldown).'" title="'.yearviewtooltip($viewcount).'">'.numericDisplay($viewcount,$numericDisplayFormat).'</a></td>';
  }
}

function printtagviewcount($tag,$month,$language,$drilldown,$viewcount,$numericDisplayFormat) {
  return '<td align="right"><a href="'.gettagviewsurl($tag,$month,$language,$drilldown).'" title="'.$viewcount.' (click for data on individual pages)">'.numericDisplay($viewcount,$numericDisplayFormat).'</a></td>';
}

function printtagviewcountbyyear($tag,$year,$language,$drilldown,$viewcount,$numericDisplayFormat) {
  return '<td align="right"><a href="'.getannualtagviewsurl($tag,$year,$language,$drilldown).'" title="'.$viewcount.' (click for data on individual pages)">'.numericDisplay($viewcount,$numericDisplayFormat).'</a></td>';
}

function printPageviewsForMonthOrYearListAsHtmlTable($pageOrTagList,$languageList,$drilldownList,$monthOrYearList,$numericDisplayFormat,$normalization='',$pageOrTagAdvice='page',$monthOrYearAdvice='month',$sort='desc') {
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
    $viewcountarray = viewcountarraybymonth($pageOrTagList,$languageList,$drilldownList,$monthOrYearList,true,$normalization);
  } elseif ($pageOrTagAdvice=='page' and $monthOrYearAdvice=='year') {
    $viewcountarray = viewcountarraybyyear($pageOrTagList,$languageList,$drilldownList,$monthOrYearList,true,$normalization);
  } elseif ($pageOrTagAdvice=='tag' and $monthOrYearAdvice=='month') {
    $viewcountarray = viewcountarraybytagandmonth($pageOrTagList,$languageList,$drilldownList,$monthOrYearList,true,$normalization);
  } elseif ($pageOrTagAdvice=='tag' and $monthOrYearAdvice=='year') {
    $viewcountarray = viewcountarraybytagandyear($pageOrTagList,$languageList,$drilldownList,$monthOrYearList,true,$normalization);
  }
  $tap = totalsAndPercentages($pageOrTagList,$languageList,$drilldownList,$monthOrYearList,$viewcountarray);
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
  ##Table header row
    
  print '<table border="1">';
  $headerstring = "<tr><th>".ucfirst($pageOrTagAdvice)." name";

  if (count($drilldownList) > 1) {
    $headerstring .= " and drilldown";
  }
  $headerstring .= "</th>";
  foreach($monthOrYearList as $monthOrYear) {
    $headerstring .= "<th>Count in ".$monthOrYearAdvice." ".$monthOrYear."</th>";
  }
  if (count($monthOrYearList) > 1) {
    $headerstring .="<th>Total</th>";
  }
  if (count($pageOrTagList) * count($languageList) * count($drilldownList) > 1) {
    $headerstring.="<th>Percentage</th>";
  }

  #Tag list column printing
  if ($pageOrTagAdvice == 'page') {
    $headerstring .= "<th>Tags</th>";
  }
  $headerstring .= "</tr>";
  print $headerstring;
  
  ##Data rows
  foreach($pageOrTagList as $pageOrTag) {
    foreach($languageList as $language) {
      if ($pageOrTagAdvice == 'page') {
        $tagListForPage = $tagListByPages[$pageOrTag][$language];
      }
      
      foreach($drilldownList as $drilldown) {
        if ($pageOrTagAdvice=='page') {
          $pageOrTagCumLanguageCumDrilldownRowString = '<tr><td><a href="'.getpageurl($pageOrTag,$language).'" title = "'.$pageOrTag.' (read page on Wikipedia)">'.$pageOrTag.'</a>';
        } elseif ($pageOrTagAdvice=='tag' and $monthOrYearAdvice=='month') {
          $pageOrTagCumLanguageCumDrilldownRowString = '<td><a href="http://wikipediaviews.org/displayviewsformultiplemonths.php?tag='.$pageOrTag.'&language='.$language.'&drilldown='.$drilldown.'&allmonths=allmonths">'.$pageOrTag.'</a>';
        } elseif ($pageOrTagAdvice=='tag' and $monthOrYearAdvice=='year') {
          $pageOrTagCumLanguageCumDrilldownRowString = '<td><a href="http://wikipediaviews.org/displayviewsformultipleyears.php?tag='.$pageOrTag.'&language='.$language.'&drilldown='.$drilldown.'&allyears=allyears">'.$pageOrTag.'</a>';
        }
        if (count($languageList) > 1) {
          $pageOrTagCumLanguageCumDrilldownRowString .= ', language '.$language;
        }
        if (count($drilldownList) > 1) {
          $pageOrTagCumLanguageCumDrilldownRowString .= ', drilldown '.$drilldown;
        }
        $pageOrTagCumLanguageCumDrilldownRowString .= '</td>';
        
        foreach($monthOrYearList as $monthOrYear) {
          $viewcount = $viewcountarray[$pageOrTag][$language][$drilldown][$monthOrYear];
  	  if ($pageOrTagAdvice=='page' and $monthOrYearAdvice=='month') {
  	    $pageOrTagCumLanguageCumDrilldownRowString .= printMonthViewCount($pageOrTag,$monthOrYear,$language,$drilldown,$viewcount,$numericDisplayFormat);
  	  } elseif ($pageOrTagAdvice=='page' and $monthOrYearAdvice=='year') {
  	    $pageOrTagCumLanguageCumDrilldownRowString .= printYearViewCount($pageOrTag,$monthOrYear,$language,$drilldown,$viewcount,$numericDisplayFormat);
  	  } elseif ($pageOrTagAdvice=='tag' and $monthOrYearAdvice=='month') {
  	    $pageOrTagCumLanguageCumDrilldownRowString .= printtagviewcount($pageOrTag,$monthOrYear,$language,$drilldown,$viewcount,$numericDisplayFormat);
  	  } elseif ($pageOrTagAdvice=='tag' and $monthOrYearAdvice=='year') {
            $pageOrTagCumLanguageCumDrilldownRowString .= printtagviewcountbyyear($pageOrTag,$monthOrYear,$language,$drilldown,$viewcount,$numericDisplayFormat);
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
              $pageOrTagCumLanguageCumDrilldownRowString .= '<a href="http://wikipediaviews.org/displayviewsformultiplemonths.php?tag='.$tag.'&language='.$language.'&drilldown='.$drilldown.'&allmonths=allmonths">'.$tag.'</a> ';
  	    } else {
              $pageOrTagCumLanguageCumDrilldownRowString .= '<a href="http://wikipediaviews.org/displayviewsformultipleyears.php?tag='.$tag.'&language='.$language.'&drilldown='.$drilldown.'&allyears=allyears">'.$tag.'</a> ';
  	    }
          }
          $pageOrTagCumLanguageCumDrilldownRowString .= '</td>';
        }
        $pageOrTagCumLanguageCumDrilldownRowString .="</tr>";
        print $pageOrTagCumLanguageCumDrilldownRowString;
      }
      if (count($drilldownList) > 1 and count($pageOrTagList) * count($languageList) > 1) {
        if ($pageOrTagAdvice=='page') {
          $pageOrTagCumLanguageSummaryString = '<tr><td><strong><a href="'.getpageurl($pageOrTag,$language).'" title = "'.$pageOrTag.' (read page on Wikipedia)">'.$pageOrTag.'</a>';
        } elseif ($pageOrTagAdvice=='tag' and $monthOrYearAdvice=='month') {
          $pageOrTagCumLanguageSummaryString = '<tr><td><strong><a href="http://wikipediaviews.org/displayviewsformultiplemonths.php?tag='.$pageOrTag.'&language='.$language.'&drilldown='.$drilldown.'&allmonths=allmonths">'.$pageOrTag.'</a>';
        } elseif ($pageOrTagAdvice=='tag' and $monthOrYearAdvice=='year') {
          $pageOrTagCumLanguageSummaryString = '<td><a href="http://wikipediaviews.org/displayviewsformultipleyears.php?tag='.$pageOrTag.'&language='.$language.'&drilldown='.$drilldown.'&allyears=allyears">'.$pageOrTag.'</a>';
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
  	    $pageOrTagCumLanguageSummaryString .= printtagviewcount($pageOrTag,$monthOrYear,$language,"all",$viewcount,$numericDisplayFormat);
  	  } elseif ($pageOrTagAdvice=='tag' and $monthOrYearAdvice=='year') {
  	    $pageOrTagCumLanguageSummaryString .= printtagviewcountbyyear($pageOrTag,$monthOrYear,$language,"all",$viewcount,$numericDisplayFormat);
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
              $pageOrTagCumLanguageSummaryString .= '<a href="http://wikipediaviews.org/displayviewsformultiplemonths.php?tag='.$tag.'&language='.$language.'&drilldown=all&allmonths=allmonths">'.$tag.'</a> ';
  	  } else {
              $pageOrTagCumLanguageSummaryString .= '<a href="http://wikipediaviews.org/displayviewsformultipleyears.php?tag='.$tag.'&language='.$language.'&drilldown=all&allyears=allyears">'.$tag.'</a> ';
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
  	  $pageOrTagSummaryString .= printtagviewcount($pageOrTag,$monthOrYear,"all","all",$viewcount,$numericDisplayFormat);
  	} elseif ($pageOrTagAdvice=='tag' and $monthOrYearAdvice=='year') {
  	  $pageOrTagSummaryString .= printtagviewcountbyyear($pageOrTag,$monthOrYear,"all","all",$viewcount,$numericDisplayFormat);
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
        $drilldownPercentageRowString .= '<td></td>'; 
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
}

function printPageviewsForMonthOrYearListAsHtmlTableTransposed($pageOrTagList,$languageList,$drilldownList,$monthOrYearList,$numericDisplayFormat,$normalization='',$pageOrTagAdvice='page',$monthOrYearAdvice='month',$sort='desc') {
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
    $viewcountarray = viewcountarraybymonth($pageOrTagList,$languageList,$drilldownList,$monthOrYearList,true,$normalization);
  } elseif ($pageOrTagAdvice=='page' and $monthOrYearAdvice=='year') {
    $viewcountarray = viewcountarraybyyear($pageOrTagList,$languageList,$drilldownList,$monthOrYearList,true,$normalization);
  } elseif ($pageOrTagAdvice=='tag' and $monthOrYearAdvice=='month') {
    $viewcountarray = viewcountarraybytagandmonth($pageOrTagList,$languageList,$drilldownList,$monthOrYearList,true,$normalization);
  } elseif ($pageOrTagAdvice=='tag' and $monthOrYearAdvice=='year') {
    $viewcountarray = viewcountarraybytagandyear($pageOrTagList,$languageList,$drilldownList,$monthOrYearList,true,$normalization);
  }
  $tap = totalsAndPercentages($pageOrTagList,$languageList,$drilldownList,$monthOrYearList,$viewcountarray);
  $grandTotal = $tap["grandTotal"];
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
     $tagListByPages = getTagListByPageList($pageOrTagList,$language);
  }
  #Pre-table warnings
    
  if ($monthOrYearAdvice=='year') {
    print "<strong>For speed and consistency reasons, we do <em>not</em> include the current month in totals for the current year</strong><br><br>";
  }
  flush();
  #Table header row
  print '<table border="1">';
  $headerstring = "<tr><th>".ucfirst($monthOrYearAdvice)."</th>";
  foreach($pageOrTagList as $pageOrTag) {
    foreach($languageList as $language) {
      foreach($drilldownList as $drilldown) {
        $shortDescriptor = getShortDescriptor($drilldown);
        if ($pageOrTagAdvice=='page') {
          $headerstring .= '<th>'.$shortDescriptor.' of page <a href="'. getpageurl($pageOrTag,$language). '" title="'.$pageOrTag.' (read page on Wikipedia)">' . $pageOrTag.'</a>';
        } elseif ($pageOrTagAdvice=='tag' and $monthOrYearAdvice=='month') {
          $headerstring .= '<th>'.$shortDescriptor.' of pages with tag <a href="http://wikipediaviews.org/displayviewsformultiplemonths.php?tag='.$pageOrTag.'&language='.$language.'&drilldown='.$drilldown.'&allmonths=allmonths">'.$pageOrTag.'</a>';
        } elseif ($pageOrTagAdvice=='tag' and $monthOrYearAdvice=='year') {
          $headerstring .= '<th>'.$shortDescriptor.' of pages with tag <a href="http://wikipediaviews.org/displayviewsformultipleyears.php?tag='.$pageOrTag.'&language='.$language.'&drilldown='.$drilldown.'&allyears=allyears">'.$pageOrTag.'</a>';
        }
        if (count($languageList) > 1) {
          $headerstring .= ", language ".$language;
        }
        if (count($drilldownList) > 1) {
          $headerstring .= ", drilldown ".$drilldown;
        }
        $headerstring .= '</th>';
      }
      if (count($drilldownList) > 1 and count($pageOrTagList) * count($languageList) > 1) {
        if ($pageOrTagAdvice=='page') {
          $headerstring .= '<th>'.$shortDescriptor.' of page <a href="'. getpageurl($pageOrTag,$language). '" title="'.$pageOrTag.' (read page on Wikipedia)">' . $pageOrTag.'</a>';
          if (count($languageList) > 1) {
            $headerstring .= ', language '.$language;
          }
          $headerstring .= ', sum over drilldowns</th>';
        } elseif ($pageOrTagAdvice=='tag' and $monthOrYearAdvice='month') {
          $headerstring .= '<th>'.$shortDescriptor.' of pages with tag <a href="'. getpageurl($pageOrTag,$language). '" title="'.$pageOrTag.' (read page on Wikipedia)">' . $pageOrTag.'</a>';
          if (count($languageList) > 1) {
            $headerstring .= ', language '.$language;
          }
          $headerstring .= ', sum over drilldowns</th>';
        } elseif ($pageOrTagAdvice=='tag' and $monthOrYearAdvice=='year') {
          $headerstring .= '<th>'.$shortDescriptor.' of pages with tag <a href="http://wikipediaviews.org/displayviewsformultipleyears.php?tag='.$pageOrTag.'&language='.$language.'&drilldown='.$drilldown.'&allyears=allyears">'.$pageOrTag.'</a>';
          if (count($languageList) > 1) {
            $headerstring .= ', language '.$language;
          }
          $headerstring .= ', sum over drilldowns</th>';
        }
      }
    }
  }
  if (count($pageOrTagList) * count($languageList) > 1 and count($drilldownList) > 1) {
    foreach ($drilldownList as $drilldown) {
      $headerstring .= '<th>Total, drilldown '.$drilldown.'</th>';
      $headerstring .= '<th>Percentage, drilldown '.$drilldown.'</th>';
    }
  }
  if (count($pageOrTagList) * count($languageList) * count($drilldownList) > 1) {
    $headerstring .="<th>Total</th>";
  }
  if (count($monthOrYearList) > 1) {
    $headerstring.='<td><strong>Percentage</strong></td>';
  }
  $headerstring .= '</tr>';
  print $headerstring;
  
  ##Data rows
  foreach($monthOrYearList as $monthOrYear) { #Prints one row of the table
    $monthOrYearRowString = '<tr><td>'.$monthOrYear.'</td>';
    foreach($pageOrTagList as $pageOrTag) { #Computes one cell entry
      foreach($languageList as $language) {
        foreach($drilldownList as $drilldown) {
          $viewcount = $viewcountarray[$pageOrTag][$language][$drilldown][$monthOrYear];
          if ($pageOrTagAdvice=='page' and $monthOrYearAdvice=='month') {
            $monthOrYearRowString .= printMonthViewCount($pageOrTag,$monthOrYear,$language,$drilldown,$viewcount,$numericDisplayFormat);
          } elseif ($pageOrTagAdvice=='page' and $monthOrYearAdvice=='year') {
            $monthOrYearRowString .= printYearViewCount($pageOrTag,$monthOrYear,$language,$drilldown,$viewcount,$numericDisplayFormat);
          } elseif ($pageOrTagAdvice=='tag' and $monthOrYearAdvice=='month') {
            $monthOrYearRowString .= printtagviewcount($pageOrTag,$monthOrYear,$language,$drilldown,$viewcount,$numericDisplayFormat);
          } elseif ($pageOrTagAdvice=='tag' and $monthOrYearAdvice=='year') {
            $monthOrYearRowString .= printtagviewcountbyyear($pageOrTag,$monthOrYear,$language,$drilldown,$viewcount,$numericDisplayFormat);
          }
        }
        if (count($drilldownList) > 1 and count($pageOrTagList) * count($languageList) > 1) {
          $viewcount = $pageOrTagCumLanguageCumMonthOrYearTotal[$pageOrTag][$language][$monthOrYear];
          $monthOrYearRowString .= '<td align="right"><strong><element title="'.numericDisplay($viewcount, $numericDisplayFormat).'">'.numericDisplay($viewcount, $numericDisplayFormat).'</element></strong></td>';
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
        if (count($pageOrTagList) > 1 and count($drilldownList) > 1) {
          $totalsRowString .= '<td align="right"><strong><element title="'.$drilldownTotal[$drilldown].'">'.numericDisplay($drilldownTotal[$drilldown],$numericDisplayFormat).'</element></strong></td>';
        }
      }
    }
    if (count($pageOrTagList) > 1 and count($drilldownList) > 1) {
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
    }
    if (count($pageOrTagList) * count($languageList) > 1 and count($drilldownList) > 1) {
      foreach($drilldownList as $drilldown) {
        $percentagesRowString .= '<td align="right"><strong>'.$drilldownPercentage[$drilldown].'</strong></td>';
        $percentagesRowString .= '<td></td>';
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
        $tagListForPage = $tagListByPages[$pageOrTag];
        $tagCell = '<td>';
        if (count($tagListForPage) == 0) {
          $tagCell .= "--";
        }
        foreach ($tagListForPage as $tag) {
	  if ($monthOrYearAdvice == 'month') {
            $tagCell .= '<a href="http://wikipediaviews.org/displayviewsformultiplemonths.php?tag='.$tag.'&language='.$language.'&allmonths=allmonths">'.$tag.'</a> ';
	  } else {
            $tagCell .= '<a href="http://wikipediaviews.org/displayviewsformultipleyears.php?tag='.$tag.'&language='.$language.'&allyears=allyears">'.$tag.'</a> ';
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
}

function printPageviewsForMonthOrYearListAsCsv($pageOrTagList,$monthOrYearList,$language,$drilldown,$numericDisplayFormat,$normalization='',$pageOrTagAdvice='page',$monthOrYearAdvice='month') {
  #Check that sizes are workable
  $sizeoverflow = checksizes($pageOrTagList,$monthOrYearList);
  if ($sizeoverflow > 0)
    return false;
  #Collect all the numbers that need to be printed first
  if ($pageOrTagAdvice=='page' and $monthOrYearAdvice=='month')
    {
      $viewcountarray = viewcountarraybymonth($pageOrTagList,$monthOrYearList,$language,$drilldown,true,$normalization);
    }
  elseif ($pageOrTagAdvice=='page' and $monthOrYearAdvice=='year')
    {
      $viewcountarray = viewcountarraybyyear($pageOrTagList,$monthOrYearList,$language,$drilldown,true,$normalization);
    }
  elseif ($pageOrTagAdvice=='tag' and $monthOrYearAdvice=='month')
    {
      $viewcountarray = viewcountarraybytagandmonth($pageOrTagList,$monthOrYearList,$language,$drilldown,true,$normalization);
    }
  elseif ($pageOrTagAdvice=='tag' and $monthOrYearAdvice=='year')
    {
      $viewcountarray = viewcountarraybytagandyear($pageOrTagList,$monthOrYearList,$language,$drilldown,true,$normalization);
    }

  $tap = totalsAndPercentages($pageOrTagList,$languageList,$drilldownList,$monthOrYearList,$viewcountarray);
  $grandTotal = $tap["grandTotal"];
  $pageOrTagCumLanguageCumDrilldownTotal = $tap["pageOrTagCumLanguageCumDrilldownTotal"];
  $pageOrTagCumLanguageCumMonthOrYearTotal = $tap["pageOrTagCumLanguageCumMonthOrYearTotal"];
  $drilldownCumMonthOrYearTotal = $tap["drilldownCumMonthOrYearTotal"];
  $pageOrTagCumLanguageTotal = $tap["pageOrTagCumLanguageTotal"];
  $drilldownTotal = $tap["drilldownTotal"];
  $monthOrYearTotal = $tap["monthOrYearTotal"];
  $pageOrTagCumLanguageCumDrilldownPercentage = $tap["pageOrTagCumLanguageCumDrilldownPercentage"];
  $pageOrTagCumLanguageCumMonthOrYearPercentage = $tap["pageOrTagCumLanguageCumMonthOrYearPercentage"];
  $drilldownCumMonthOrYearPercentage = $tap["drilldownCumMonthOrYearPercentage"];
  $pageOrTagCumLanguagePercentage = $tap["pageOrTagCumLanguagePercentage"];
  $drilldownPercentage = $tap["drilldownPercentage"];
  $monthOrYearPercentage = $tap["monthOrYearPercentage"];

  $headerstring = ucfirst($pageOrTagAdvice)." name";
  $descriptor = getDescriptor($drilldown);
  foreach($monthOrYearList as $monthOrYear) {
    $headerstring .= "|".$descriptor." in ".$monthOrYearAdvice." ".$monthOrYear;
  }
  if (count($monthOrYearList) > 1) 
    $headerstring .="|Total";
  if (count($pageOrTagList) > 1)
    $headerstring .="|Percentage";
  $headerstring.="<br>";
  print $headerstring;
  foreach($pageOrTagList as $pageOrTag)
    {
	$stringtoprint = $pageOrTag;
	$total = 0;
	foreach($monthOrYearList as $monthOrYear)
	  {
	    $viewcount = $viewcountarray[$pageOrTag][$monthOrYear];
	    $stringtoprint .= "|".$viewcount;
	  }
	if (count($monthOrYearList) > 1) 
	  $stringtoprint .="|".$pageOrTagCumLanguageTotal[$pageOrTag];
	if (count($pageOrTagList) > 1) 
	    $stringtoprint .="|".$pageOrTagPercentage[$pageOrTag];
	$stringtoprint .="<br>";
	print $stringtoprint;
    }
  if (count($pageOrTagList) > 1)
    {
      $totalsRowString = "Total";
      foreach($monthOrYearList as $monthOrYear)
	  $totalsRowString .= "|".$monthOrYearTotal[$monthOrYear];
      if (count($monthOrYearList) > 1)
	$totalsRowString .= "|".$grandTotal;
      $totalsRowString .= "|100";
      $totalsRowString .= "<br>";
      print $totalsRowString;
    }
  if (count($monthOrYearList) > 1) {
    $percentagesRowString = "Percentage";
    foreach($monthOrYearList as $monthOrYear){
       $percentagesRowString .= "|".$monthOrYearPercentage[$monthOrYear];
    }
    $percentagesRowString .= "|100";
    $percentagesRowString .= "<br>";
    print $percentagesRowString;
  }
}

function printPageviewsForMonthOrYearListAsCsvTransposed($pageOrTagList,$monthOrYearList,$language,$drilldown,$numericDisplayFormat,$normalization='',$pageOrTagAdvice='page',$monthOrYearAdvice='month') {
  #Check that sizes are workable
  $sizeoverflow = checksizes($pageOrTagList,$monthOrYearList);
  if ($sizeoverflow > 0)
    return false;
  #Collect all the numbers that need to be printed first
  if ($pageOrTagAdvice=='page' and $monthOrYearAdvice=='month')
    $viewcountarray = viewcountarraybymonth($pageOrTagList,$monthOrYearList,$language,$drilldown,true,$normalization);
  elseif ($pageOrTagAdvice=='page' and $monthOrYearAdvice=='year')
    $viewcountarray = viewcountarraybyyear($pageOrTagList,$monthOrYearList,$language,$drilldown,true,$normalization);
  elseif ($pageOrTagAdvice=='tag' and $monthOrYearAdvice=='month')
    $viewcountarray = viewcountarraybytagandmonth($pageOrTagList,$monthOrYearList,$language,$drilldown,true,$normalization);
  elseif ($pageOrTagAdvice=='tag' and $monthOrYearAdvice=='year')
    $viewcountarray = viewcountarraybytagandyear($pageOrTagList,$monthOrYearList,$language,$drilldown,true,$normalization);

  $tap = totalsAndPercentages($pageOrTagList,$languageList,$drilldownList,$monthOrYearList,$viewcountarray);
  $grandTotal = $tap["grandTotal"];
  $pageOrTagCumLanguageCumDrilldownTotal = $tap["pageOrTagCumLanguageCumDrilldownTotal"];
  $pageOrTagCumLanguageCumMonthOrYearTotal = $tap["pageOrTagCumLanguageCumMonthOrYearTotal"];
  $drilldownCumMonthOrYearTotal = $tap["drilldownCumMonthOrYearTotal"];
  $pageOrTagCumLanguageTotal = $tap["pageOrTagCumLanguageTotal"];
  $drilldownTotal = $tap["drilldownTotal"];
  $monthOrYearTotal = $tap["monthOrYearTotal"];
  $pageOrTagCumLanguageCumDrilldownPercentage = $tap["pageOrTagCumLanguageCumDrilldownPercentage"];
  $pageOrTagCumLanguageCumMonthOrYearPercentage = $tap["pageOrTagCumLanguageCumMonthOrYearPercentage"];
  $drilldownCumMonthOrYearPercentage = $tap["drilldownCumMonthOrYearPercentage"];
  $pageOrTagPercentage = $tap["pageOrTagPercentage"];
  $drilldownPercentage = $tap["drilldownPercentage"];
  $monthOrYearPercentage = $tap["monthOrYearPercentage"];

  $headerstring = ucfirst($monthOrYearAdvice);
  foreach($pageOrTagList as $pageOrTag)
    $headerstring .= "|Views of ".$pageOrTagAdvice." ".$pageOrTag;
  if (count($pageOrTagList) > 1) 
    $headerstring .="|Total";
  if (count($monthOrYearList) > 1)
    $headerstring .="|Percentage";
  $headerstring.="<br>";
  print $headerstring;
  foreach($monthOrYearList as $monthOrYear)
    {
	$stringtoprint = $monthOrYear;
	$total = 0;
	foreach($pageOrTagList as $pageOrTag)
	  {
	    $viewcount = $viewcountarray[$pageOrTag][$monthOrYear];
	    $stringtoprint .= "|".$viewcount;
	  }
	if (count($pageOrTagList) > 1) 
	  $stringtoprint .="|".$monthOrYearTotal[$monthOrYear];
	if (count($monthOrYearList) > 1) 
	  {
	    $stringtoprint .="|".$monthOrYearPercentage[$monthOrYear];
	  }
	$stringtoprint .="<br>";
	print $stringtoprint;
    }
  if (count($monthOrYearList) > 1)
    {
      $totalsRowString = "Total";
      foreach($pageOrTagList as $pageOrTag)
	$totalsRowString .= "|".$pageOrTagCumLanguageTotal[$pageOrTag][$language];
      if (count($pageOrTagList) > 1)
	$totalsRowString .= "|".$grandTotal;
      $totalsRowString .="|100";
      $totalsRowString .= "<br>";
      print $totalsRowString;
    }
  if (count($pageOrTagList) > 1)
    {
      $percentagesRowString = "Percentage";
      foreach($pageOrTagList as $pageOrTag)
	{
	  $percentagesRowString .= "|".$pageOrTagPercentage[$pageOrTag];
	}
      $percentagesRowString .= "|100";
      $percentagesRowString .= "<br>";
      print $percentagesRowString;
    }
}

function generateGraphs($pageOrTagList,$languageList,$drilldownList,$monthOrYearList,$numericDisplayFormat,$normalization='',$pageOrTagAdvice='page',$monthOrYearAdvice='month') {
  global $graphTimeTaken;
  global $imagesPath;
  global $generateGraphCmdBase;
  global $generateDistribCmdBase;
  $graphStartTime = microtime(true);
  #Check that sizes are workable
  $sizeOverflow = checkSizes($pageOrTagList,$languageList,$drilldownList,$monthOrYearList);
  if ($sizeOverflow > 0) {
    print " Therefore, we are not constructing graphs.<br/>";
    return false;
  }
  #Collect all the numbers that need to be printed first
  if ($pageOrTagAdvice=='page' and $monthOrYearAdvice=='month')
    $viewcountarray = viewcountarraybymonth($pageOrTagList,$languageList,$drilldownList,$monthOrYearList,false,$normalization);
  elseif ($pageOrTagAdvice=='page' and $monthOrYearAdvice=='year')
    $viewcountarray = viewcountarraybyyear($pageOrTagList,$languageList,$drilldownList,$monthOrYearList,false,$normalization);
  elseif ($pageOrTagAdvice=='tag' and $monthOrYearAdvice=='month')
    $viewcountarray = viewcountarraybytagandmonth($pageOrTagList,$languageList,$drilldownList,$monthOrYearList,false,$normalization);
  elseif ($pageOrTagAdvice=='tag' and $monthOrYearAdvice=='year')
    $viewcountarray = viewcountarraybytagandyear($pageOrTagList,$languageList,$drilldownList,$monthOrYearList,false,$normalization);

  $tap = totalsAndPercentages($pageOrTagList,$languageList,$drilldownList,$monthOrYearList,$viewcountarray);
  $grandTotal = $tap["grandTotal"];
  $pageOrTagCumMonthOrYearTotal = $tap["pageOrTagCumMonthOrYearTotal"];
  $pageOrTagCumLanguageCumDrilldownTotal = $tap["pageOrTagCumLanguageCumDrilldownTotal"];
  $pageOrTagCumLanguageCumMonthOrYearTotal = $tap["pageOrTagCumLanguageCumMonthOrYearTotal"];
  $drilldownCumMonthOrYearTotal = $tap["drilldownCumMonthOrYearTotal"];
  $pageOrTagCumLanguageTotal = $tap["pageOrTagCumLanguageTotal"];
  $drilldownTotal = $tap["drilldownTotal"];
  $monthOrYearTotal = $tap["monthOrYearTotal"];
  $pageOrTagCumLanguageCumDrilldownPercentage = $tap["pageOrTagCumLanguageCumDrilldownPercentage"];
  $pageOrTagCumLanguageCumMonthOrYearPercentage = $tap["pageOrTagCumLanguageCumMonthOrYearPercentage"];
  $drilldownCumMonthOrYearPercentage = $tap["drilldownCumMonthOrYearPercentage"];
  $pageOrTagCumLanguagePercentage = $tap["pageOrTagCumLanguagePercentage"];
  $drilldownPercentage = $tap["drilldownPercentage"];
  $monthOrYearPercentage = $tap["monthOrYearPercentage"];

  $fullOutput = "";

  $headerstring = ucfirst($monthOrYearAdvice);
  foreach($pageOrTagList as $pageOrTag) {
    foreach($languageList as $language) {
      foreach ($drilldownList as $drilldown) {
        $headerstring .= "|".$pageOrTag;
        if (count($languageList) > 1) {
          $headerstring .= " ".$language;
        }
        if (count($drilldownList) > 1) {
          $headerstring .= " ".$drilldown;
        }
      }
    }
  }
  if (count($pageOrTagList) * count($languageList) * count($drilldownList) > 1) {
    $headerstring .="|Total";
  }
  if (count($monthOrYearList) > 1) {
    $headerstring .="|Percentage";
  }
  $headerstring .="\n";
  $fullOutput .= $headerstring;
  foreach($monthOrYearList as $monthOrYear) {
    $stringtoprint = $monthOrYear;
    $total = 0;
    foreach($pageOrTagList as $pageOrTag) {
      foreach($languageList as $language) {
        foreach($drilldownList as $drilldown) { 
          $viewcount = $viewcountarray[$pageOrTag][$language][$drilldown][$monthOrYear];
          $numericViewCount = 0;
          $numericViewCount = $numericViewCount + $viewcount;
          $stringtoprint .= "|".$numericViewCount;
        }
      }
    }
    if (count($pageOrTagList) * count($languageList) * count($drilldownList) > 1) {
      $stringtoprint .="|".$monthOrYearTotal[$monthOrYear];
    }
    if (count($monthOrYearList) > 1) {
      $stringtoprint .="|".$monthOrYearPercentage[$monthOrYear];
    }
    $stringtoprint .="\n";
    $fullOutput .= $stringtoprint;
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
  if (count($pageOrTagList) * count($languageList) * count($drilldownList) > 1) {
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
  }

  # Drilldown output
  $drilldownOutput = "";
  if (count($pageOrTagList) * count($languageList) > 1 and count($drilldownList) > 1) {
    $headerstring = ucfirst($monthOrYearAdvice);
    foreach ($drilldownList as $drilldown) {
      $headerstring .= "|".$drilldown;
    }
    $headerstring .="|Total";
    if (count($monthOrYearList) > 1) {
      $headerstring .="|Percentage";
    }
    $headerstring .="\n";
    $drilldownOutput .= $headerstring;
    foreach($monthOrYearList as $monthOrYear) {
      $stringtoprint = $monthOrYear;
      $total = 0;
      foreach($drilldownList as $drilldown) { 
        $viewcount = $drilldownCumMonthOrYearTotal[$drilldown][$monthOrYear];
        $numericViewCount = 0;
        $numericViewCount = $numericViewCount + $viewcount;
        $stringtoprint .= "|".$numericViewCount;
      }
      $stringtoprint .="|".$monthOrYearTotal[$monthOrYear];
      if (count($monthOrYearList) > 1) {
        $stringtoprint .="|".$monthOrYearPercentage[$monthOrYear];
      }
      $stringtoprint .="\n";
      $drilldownOutput .= $stringtoprint;
    }
    if (count($monthOrYearList) > 1) {
      $totalsRowString = "Total";
      foreach($drilldownList as $drilldown) {
        $totalsRowString .= "|".$drilldownTotal[$drilldown];
      }
    }
    if (count($drilldownList) > 1) {
      $totalsRowString .= "|".$grandTotal;
    }
    $totalsRowString .="|100";
    $totalsRowString .= "\n";
    $drilldownOutput .= $totalsRowString;
    if (count($pageOrTagList) > 0) {
      $percentagesRowString = "Percentage";
      foreach($drilldownList as $drilldown) {
        $percentagesRowString .= "|".$drilldownPercentage[$drilldown];
      }
      $percentagesRowString .= "|100";
      $percentagesRowString .= "\n";
      $drilldownOutput .= $percentagesRowString;
    }
  }

  # pageOrTag output
  $pageOrTagOutput = "";
  if (count($languageList) * count($drilldownList) > 1 and count($pageOrTagList) > 1) {
    $headerstring = ucfirst($monthOrYearAdvice);
    foreach ($pageOrTagList as $pageOrTag) {
      $headerstring .= "|".$pageOrTag;
    }
    $headerstring .="|Total";
    if (count($monthOrYearList) > 1) {
      $headerstring .="|Percentage";
    }
    $headerstring .="\n";
    $pageOrTagOutput .= $headerstring;
    foreach($monthOrYearList as $monthOrYear) {
      $stringtoprint = $monthOrYear;
      $total = 0;
      foreach($pageOrTagList as $pageOrTag) {
        $viewcount = intval($pageOrTagCumMonthOrYearTotal[$pageOrTag][$monthOrYear]);
        $stringtoprint .= "|".$viewcount;
      }
      $stringtoprint .="|".$monthOrYearTotal[$monthOrYear];
      if (count($monthOrYearList) > 1) {
        $stringtoprint .="|".$monthOrYearPercentage[$monthOrYear];
      }
      $stringtoprint .="\n";
      $pageOrTagOutput .= $stringtoprint;
    }
    $totalsRowString = "Total";
    foreach($pageOrTagList as $pageOrTag) {
      $totalsRowString .= "|".$pageOrTagTotal[$pageOrTag];
    }
    if (count($pageOrTagList) > 1) {
      $totalsRowString .= "|".$grandTotal;
    }
    if (count($monthOrYearList) > 1) {
      $totalsRowString .="|100";
    }
    $totalsRowString .= "\n";
    $pageOrTagOutput .= $totalsRowString;
    if (count($pageOrTagList) > 0) {
      $percentagesRowString = "Percentage";
      foreach($pageOrTagList as $pageOrTag) {
        $percentagesRowString .= "|".$pageOrTagPercentage[$pageOrTag];
      }
      $percentagesRowString .= "|100";
      $percentagesRowString .= "\n";
      $pageOrTagOutput .= $percentagesRowString;
    }
  }

  # pageOrTag cum language output
  $pageOrTagCumLanguageOutput = "";
  if (count($drilldownList) > 1 and count($languageList) > 1) {
    $headerstring = ucfirst($monthOrYearAdvice);
    foreach ($pageOrTagList as $pageOrTag) {
      foreach ($languageList as $language) {
        $headerstring .= "|".$pageOrTag;
        if (count($languageList) > 1) {
          $headerstring .= " ".$language;
        }
      }
    }
    $headerstring .="|Total";
    if (count($monthOrYearList) > 1) {
      $headerstring .="|Percentage";
    }
    $headerstring .="\n";
    $pageOrTagCumLanguageOutput .= $headerstring;
    foreach($monthOrYearList as $monthOrYear) {
      $stringtoprint = $monthOrYear;
      $total = 0;
      foreach($pageOrTagList as $pageOrTag) {
        foreach($languageList as $language) {
          $viewcount = $pageOrTagCumLanguageCumMonthOrYearTotal[$pageOrTag][$language][$monthOrYear];
          $numericViewCount = 0;
          $numericViewCount = $numericViewCount + $viewcount;
          $stringtoprint .= "|".$numericViewCount;
        }
      }
      $stringtoprint .="|".$monthOrYearTotal[$monthOrYear];
      if (count($monthOrYearList) > 1) {
        $stringtoprint .="|".$monthOrYearPercentage[$monthOrYear];
      }
      $stringtoprint .="\n";
      $pageOrTagCumLanguageOutput .= $stringtoprint;
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

  $fileName = strval(rand());
  $filePathBase = $imagesPath . $fileName;
  file_put_contents($filePathBase . ".csv", $fullOutput);
  if (count($pageOrTagList) * count($languageList) * count($drilldownList) > 1) {
    $cmdToExecute = $generateDistribCmdBase . " " . $filePathBase . ".csv " . $filePathBase . "-distrib.png ";
    if ($numericDisplayFormat == "log") {
      $cmdToExecute = $cmdToExecute . " --log10 ";
    }
    if (count($pageOrTagList) * count($languageList) * count($drilldownList) <= 30) {
      $cmdToExecute = $cmdToExecute . " --label --label_max_len 40 ";
    }
    if (count($pageOrTagList) * count($languageList) * count($drilldownList) <= 50) {
      $entityDescriptor = "bar";
      $cmdToExecute = $cmdToExecute . " --plot_kind bar ";
    } else {
      $entityDescriptor = "point in the line graph";
      $cmdToExecute = $cmdToExecute . " --plot_kind line ";
    }
    # print("Going to try executing ".$cmdToExecute."<br>");
    exec($cmdToExecute);
    print "<br/><br/>";
    print "<strong>Distribution of pageviews; each ".$entityDescriptor." represents a combination of page, language, and drilldown</strong><br/>";
    print '<img src="/images/'.$fileName.'-distrib.png" alt="Image of pageviews distribution should have loaded here"></img>';
  }
  if (count($monthOrYearList) > 1) {
    $cmdToExecute = $generateGraphCmdBase . " " . $filePathBase . ".csv " . $filePathBase . "-timeseries.png ";
    if ($numericDisplayFormat == "log") {
      $cmdToExecute = $cmdToExecute . " --log10";
    }
    # print("Going to try executing ".$cmdToExecute."<br>");
    exec($cmdToExecute);
    print "<br/><br/>";
    if (count($pageOrTagList) * count($languageList) * count($drilldownList) > 30) {
    $addendum = ", restricted to the top 30 by total across months";
    } else {
      $addendum = "";
    }
    if (count($pageOrTagList) * count($languageList) > 1 and count($drilldownList) > 1) {
      print "<strong>Time series of data; includes overall total and a separate curve for each combination of ".$pageOrTagAdvice.", language, and drilldown".$addendum." below:</strong><br/>"; 
    } else if (count($drilldownList) > 1) {
      print "<strong>Time series of data; includes overall total and a separate curve for each drilldown".$addendum." below:</strong><br/>";
    } else if (count($pageOrTagList) * count($languageList) > 1) {
      print "<strong>Time series of data; includes overall total and a separate curve for each combination of ".$pageOrTagAdvice."and language ".$addendum." below:</strong><br/>";
    } else {
      print "<strong>Time series of data below:</strong><br/>";
    }
    print '<img src="/images/'.$fileName.'-timeseries.png" alt="Graph of pageviews should have loaded here"></img>';
  }

  if (count($pageOrTagList) * count($languageList) > 1 and count($drilldownList) > 1) {
    # Construct drilldown-grouped data
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
    }
    if (count($drilldownList) <= 50) {
      $entityDescriptor = "bar";
      $cmdToExecute = $cmdToExecute . " --plot_kind bar ";
    } else {
      $entityDescriptor = "point in the line graph";
      $cmdToExecute = $cmdToExecute . " --plot_kind line ";
    }
    # print("Going to try executing ".$cmdToExecute."<br>");
    exec($cmdToExecute);
    print "<br/><br/>";
    print "<strong>Distribution of pageviews; each ".$entityDescriptor." represents a drilldown, summed over the over dimensions</strong><br/>";
    print '<img src="/images/'.$drilldownFileName.'-distrib.png" alt="Image of pageviews distribution should have loaded here"></img>';

    if (count($monthOrYearList) > 1) {
      $cmdToExecute = $generateGraphCmdBase . " " . $drilldownFilePathBase . ".csv " . $drilldownFilePathBase . "-timeseries.png";
      if ($numericDisplayFormat == "log") {
        $cmdToExecute = $cmdToExecute . " --log10";
      }
      exec($cmdToExecute);
      print "<br><br>";
      print "<strong>Time series of data; one curve for total by each drilldown, one curve for total, below:</strong><br/>";
      print '<img src="/images/'.$drilldownFileName.'-timeseries.png" alt="Graph of pageviews should have loaded here"></img>';
    }
  }

  if (count($languageList) > 1 and count($drilldownList) > 1) {
    $pageOrTagCumLanguageFileName = $fileName."-".$pageOrTagAdvice."lang";
    $pageOrTagCumLanguageFilePathBase = $imagesPath . $pageOrTagCumLanguageFileName;
    file_put_contents($pageOrTagCumLanguageFilePathBase . ".csv", $pageOrTagCumLanguageOutput);
    $cmdToExecute = $generateDistribCmdBase . " " . $pageOrTagCumLanguageFilePathBase . ".csv " . $pageOrTagCumLanguageFilePathBase . "-distrib.png ";
    if ($numericDisplayFormat == "log") {
      $cmdToExecute = $cmdToExecute . " --log10 ";
    }
    if (count($pageOrTagList) * count($languageList) <= 30) {
      $cmdToExecute = $cmdToExecute . " --label --label_max_len 40 ";
    }
    if (count($pageOrTagList) * count($languageList) <= 50) {
      $entityDescriptor = "bar";
      $cmdToExecute = $cmdToExecute . " --plot_kind bar ";
    } else {
      $entityDescriptor = "point in the line graph";
      $cmdToExecute = $cmdToExecute . " --plot_kind line ";
    }
    # print("Going to try executing ".$cmdToExecute."<br>");
    exec($cmdToExecute);
    print "<br/><br/>";
    print "<strong>Distribution of pageviews; each ".$entityDescriptor." represents a combination of ".$pageOrTagAdvice." and language, summed up over drilldowns</strong><br/>";
    print '<img src="/images/'.$pageOrTagCumLanguageFileName.'-distrib.png" alt="Image of pageviews distribution should have loaded here"></img>';

    if (count($monthOrYearList) > 1) {
      $cmdToExecute = $generateGraphCmdBase . " " . $pageOrTagCumLanguageFilePathBase . ".csv " . $pageOrTagCumLanguageFilePathBase . "-timeseries.png";
      if ($numericDisplayFormat == "log") {
        $cmdToExecute = $cmdToExecute . " --log10";
      }
      exec($cmdToExecute);
      if (count($pageOrTagList) * count($languageList) > 30) {
        $addendum = ", restricted to the top 30 by total across months";
      } else {
        $addendum = "";
      }
      print "<br><br>";
      print "<strong>Time series of data; one curve for total by each ".$pageOrTagAdvice.", one curve for total".$addendum.", below:</strong><br/>";
      print '<img src="/images/' . $pageOrTagCumLanguageFileName . '-timeseries.png" alt="Graph of pageviews should have loaded here"></img>';
    }
  }
  if (count($languageList) * count($drilldownList) > 1 and count($pageOrTagList) > 1) {
    # Construct page or tag
    $pageOrTagFileName = $fileName."-".$pageOrTagAdvice;
    $pageOrTagFilePathBase = $imagesPath . $pageOrTagFileName;
    file_put_contents($pageOrTagFilePathBase . ".csv", $pageOrTagOutput);
    $cmdToExecute = $generateDistribCmdBase . " " . $pageOrTagFilePathBase . ".csv " . $pageOrTagFilePathBase . "-distrib.png ";
    if ($numericDisplayFormat == "log") {
      $cmdToExecute = $cmdToExecute . " --log10 ";
    }
    if (count($pageOrTagList) <= 30) {
      $cmdToExecute = $cmdToExecute . " --label --label_max_len 40 ";
    }
    if (count($pageOrTagList) <= 50) {
      $entityDescriptor = "bar";
      $cmdToExecute = $cmdToExecute . " --plot_kind bar ";
    } else {
      $entityDescriptor = "point in the line graph";
      $cmdToExecute = $cmdToExecute . " --plot_kind line ";
    }
    # print("Going to try executing ".$cmdToExecute."<br>");
    exec($cmdToExecute);
    print "<br/><br/>";
    print "<strong>Distribution of pageviews; each ".$entityDescriptor." represents a ".$pageOrTagAdvice." summed up over the selected languages and drilldowns</strong><br/>";
    print '<img src="/images/'.$pageOrTagFileName.'-distrib.png" alt="Image of pageviews distribution should have loaded here"></img>';

    if (count($monthOrYearList) > 1) {
      $cmdToExecute = $generateGraphCmdBase . " " . $pageOrTagFilePathBase . ".csv " . $pageOrTagFilePathBase . "-timeseries.png";
      if ($numericDisplayFormat == "log") {
        $cmdToExecute = $cmdToExecute . " --log10";
      }
      exec($cmdToExecute);
      if (count($pageOrTagList) > 30) {
        $addendum = ", restricted to the top 30 by total across months";
      } else {
        $addendum = "";
      }
      print "<br><br>";
      print "<strong>Time series of data; one curve for total by each ".$pageOrTagAdvice.", one curve for total".$addendum.", below:</strong><br/>";
      print '<img src="/images/' . $pageOrTagFileName . '-timeseries.png" alt="Graph of pageviews should have loaded here"></img>';
    }
  }

  $graphEndTime = microtime(true);
  $graphTimeTaken = $graphEndTime - $graphStartTime;
}

function printPageviewsForMonthOrYearListAsCpi($pageOrTagList,$monthOrYearList,$language,$drilldown,$numericDisplayFormat,$normalization='',$pageOrTagAdvice='page',$monthOrYearAdvice='month') {
  global $exceededQueryLimitMessage;
  #Check that sizes are workable
  $sizeoverflow = checksizes($pageOrTagList,$monthOrYearList);
  if ($sizeoverflow > 0)
    return false;
  #Collect all the numbers that need to be printed first
  if ($pageOrTagAdvice=='page' and $monthOrYearAdvice=='month')
    $viewcountarray = viewcountarraybymonth($pageOrTagList,$monthOrYearList,$language,$drilldown,true,$normalization);
  elseif ($pageOrTagAdvice=='page' and $monthOrYearAdvice=='year')
    $viewcountarray = viewcountarraybyyear($pageOrTagList,$monthOrYearList,$language,$drilldown,true,$normalization);
  elseif ($pageOrTagAdvice=='tag' and $monthOrYearAdvice=='month')
    $viewcountarray = viewcountarraybytagandmonth($pageOrTagList,$monthOrYearList,$language,$drilldown,true,$normalization);
  elseif ($pageOrTagAdvice=='tag' and $monthOrYearAdvice=='year')
    $viewcountarray = viewcountarraybytagandyear($pageOrTagList,$monthOrYearList,$language,$drilldown,true,$normalization);
  
  #Collect tag information
  if ($pageOrTagAdvice=='page')
    {
      $tagListByPages = getTagListByPageList($pageOrTagList,$language);
      $tagindices = gettagindices($pageOrTagList,$language);
    }
  for ($i = 0; $i < count($pageOrTagList); $i++)
    {
      for ($j = 0; $j < count($monthOrYearList); $j++)
	{
	  $viewcount = $viewcountarray[$pageOrTagList[$i]][$monthOrYearList[$j]];
	  if ($viewcount != $exceededQueryLimitMessage)
	    {
	      print $viewcount; 
	      print " ";
	      print "1,".$i;
	      print " ";
	      print "2,".$j;
	      foreach ($tagListByPages[$pageOrTagList[$i]] as $tag)
		{
		  print " 3,".$tagindices[$tag];
		  print " 4,".($tagindices[$tag] * count($monthOrYearList) + $j);
		}
	      print "<br>";
	    }
	}
    }
}

?>
