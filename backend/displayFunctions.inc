<?php

include_once("globalvariables/passwordfile.inc");

function checkSizes($pageOrTagList,$monthOrYearList, $drilldownList) {
  global $pageDisplayLimit;
  global $cellDisplayLimit;
  $numberOfPagesOrTags = count($pageOrTagList);
  $numberOfMonthsOrYears = count($monthOrYearList);
  if ($numberOfPagesOrTags > $pageDisplayLimit) {
    print "The number of pages or tags, namely ".$numberOfPagesOrTags.", exceeds ".$pageDisplayLimit.", our hard limit on the number of pages that can be displayed.";
    return 1;
  }
  $numberOfCells = $numberOfPagesOrTags * $numberOfMonthsOrYears * count($drilldownList);
  if ($numberOfCells > $cellDisplayLimit) {
    print "The total number of cells to display, namely ".$numberofcells.", exceeds ".$cellDisplayLimit.", our hard limit on the number of cells that can be displayed.";
    return 2;
  }
  return 0;
}

function totalsAndPercentages($pageOrTagList,$monthOrYearList,$drilldownList,$viewcountarray) {
  $grandTotal = 0;
  foreach ($pageOrTagList as $pageOrTag) {
    $pageOrTagTotal[$pageOrTag] = 0;
    foreach ($drilldownList as $drilldown) {
      $pageOrTagCumDrilldownTotal[$pageOrTag][$drilldown] = 0;
      foreach ($monthOrYearList as $monthOrYear) {
        $increment = intval($viewcountarray[$pageOrTag][$monthOrYear][$drilldown]);
        $pageOrTagCumDrilldownTotal[$pageOrTag][$drilldown] += $increment;
        $pageOrTagCumMonthOrYearTotal[$pageOrTag][$monthOrYear] += $increment;
        $drilldownCumMonthOrYearTotal[$drilldown][$monthOrYear] += $increment;
        $pageOrTagTotal[$pageOrTag] += $increment;
        $drilldownTotal[$drilldown] += $increment;
        $monthOrYearTotal[$monthOrYear] += $increment;
        $grandTotal += $increment;
      }
    }
  }

  foreach ($pageOrTagList as $pageOrTag) {
    if ($grandTotal == 0) {
      $pageOrTagPercentage[$pageOrTag] = 'undefined';
    } else {
      $pageOrTagPercentage[$pageOrTag] = round(100 * floatval($pageOrTagTotal[$pageOrTag])/floatval($grandTotal),1);
    }
    foreach ($drilldownList as $drilldown) {
      if ($grandTotal == 0) {
	$pageOrTagCumDrilldownPercentage[$pageOrTag][$drilldown] = 'undefined';
      } else {
	$pageOrTagCumDrilldownPercentage[$pageOrTag][$drilldown] = round(100 * floatval($pageOrTagCumDrilldownTotal[$pageOrTag][$drilldown])/floatval($grandTotal),1);
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
	$pageOrTagCumMonthOrYearPercentage[$pageOrTag][$monthOrYear] = 'undefined';
      } else {
	$pageOrTagCumMonthOrYearPercentage[$pageOrTag][$monthOrYear] = round(100 * floatval($pageOrTagCumMonthOrYearTotal[$pageOrTag][$monthOrYear])/floatval($grandTotal),1);
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
  $tap["pageOrTagCumDrilldownTotal"] = $pageOrTagCumDrilldownTotal;
  $tap["pageOrTagCumMonthOrYearTotal"] = $pageOrTagCumMonthOrYearTotal;
  $tap["drilldownCumMonthOrYearTotal"] = $drilldownCumMonthOrYearTotal;
  $tap["pageOrTagTotal"] = $pageOrTagTotal;
  $tap["drilldownTotal"] = $drilldownTotal;
  $tap["monthOrYearTotal"] = $monthOrYearTotal;
  $tap["pageOrTagCumDrilldownPercentage"] = $pageOrTagCumDrilldownPercentage;
  $tap["pageOrTagCumMonthOrYearPercentage"] = $pageOrTagCumMonthOrYearPercentage;
  $tap["drilldownCumMonthOrYearPercentage"] = $drilldownCumMonthOrYearPercentage;
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

function printPageviewsForMonthOrYearListAsHtmlTable($pageOrTagList,$monthOrYearList,$language,$drilldownList,$explanatoryheader,$includetotal,$numericDisplayFormat,$normalization='',$pageOrTagAdvice='page',$monthOrYearAdvice='month') {
  global $timeTaken;
  $startTime = microtime(true);
  flush();
  #Check that sizes are workable
  $sizeOverflow = checkSizes($pageOrTagList,$monthOrYearList,$drilldownList);
  if ($sizeOverflow > 0) {
    return false;
  }
  #Collect all the numbers that need to be printed first
  if ($pageOrTagAdvice=='page' and $monthOrYearAdvice=='month') {
    $viewcountarray = viewcountarraybymonth($pageOrTagList,$monthOrYearList,$language,$drilldownList,true,$normalization);
  } elseif ($pageOrTagAdvice=='page' and $monthOrYearAdvice=='year') {
    $viewcountarray = viewcountarraybyyear($pageOrTagList,$monthOrYearList,$language,$drilldownList,true,$normalization);
  } elseif ($pageOrTagAdvice=='tag' and $monthOrYearAdvice=='month') {
    $viewcountarray = viewcountarraybytagandmonth($pageOrTagList,$monthOrYearList,$language,$drilldownList,true,$normalization);
  } elseif ($pageOrTagAdvice=='tag' and $monthOrYearAdvice=='year') {
    $viewcountarray = viewcountarraybytagandyear($pageOrTagList,$monthOrYearList,$language,$drilldownList,true,$normalization);
  }
  $tap = totalsAndPercentages($pageOrTagList,$monthOrYearList,$drilldownList,$viewcountarray);
  $grandTotal = $tap["grandTotal"];
  $pageOrTagCumDrilldownTotal = $tap["pageOrTagCumDrilldownTotal"];
  $pageOrTagCumMonthOrYearTotal = $tap["pageOrTagCumMonthOrYearTotal"];
  $drilldownCumMonthOrYearTotal = $tap["drilldownCumMonthOrYearTotal"];
  $pageOrTagTotal = $tap["pageOrTagTotal"];
  $drilldownTotal = $tap["drilldownTotal"];
  $monthOrYearTotal = $tap["monthOrYearTotal"];
  $pageOrTagCumDrilldownPercentage = $tap["pageOrTagCumDrilldownPercentage"];
  $pageOrTagCumMonthOrYearPercentage = $tap["pageOrTagCumMonthOrYearPercentage"];
  $drilldownCumMonthOrYearPercentage = $tap["drilldownCumMonthOrYearPercentage"];
  $pageOrTagPercentage = $tap["pageOrTagPercentage"];
  $drilldownPercentage = $tap["drilldownPercentage"];
  $monthOrYearPercentage = $tap["monthOrYearPercentage"];

  #Tag list fetching
  if ($pageOrTagAdvice=='page') {
    $tagListByPages = getTagListByPageList($pageOrTagList,$language);
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
  if ($includetotal=='includetotal' and count($monthOrYearList) > 1) {
    $headerstring .="<th>Total</th>";
  }
  if (count($pageOrTagList) * count($drilldownList) > 1) {
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
    if ($pageOrTagAdvice == 'page') {
      $tagListForPage = $tagListByPages[$pageOrTag];
    }      
    foreach($drilldownList as $drilldown) {
      if ($pageOrTagAdvice=='page') {
        $pageOrTagCumDrilldownRowString = '<tr><td><a href="'.getpageurl($pageOrTag,$language).'" title = "'.$pageOrTag.' (read page on Wikipedia)">'.$pageOrTag.'</a>';
      } elseif ($pageOrTagAdvice=='tag' and $monthOrYearAdvice=='month') {
        $pageOrTagCumDrilldownRowString = '<td><a href="http://wikipediaviews.org/displayviewsformultiplemonths.php?tag='.$pageOrTag.'&language='.$language.'&drilldown='.$drilldown.'&allmonths=allmonths">'.$pageOrTag.'</a>';
      } elseif ($pageOrTagAdvice=='tag' and $monthOrYearAdvice=='year') {
        $pageOrTagCumDrilldownRowString = '<td><a href="http://wikipediaviews.org/displayviewsformultipleyears.php?tag='.$pageOrTag.'&language='.$language.'&drilldown='.$drilldown.'&allyears=allyears">'.$pageOrTag.'</a>';
      }
      if (count($drilldownList) > 1) {
	$pageOrTagCumDrilldownRowString .= ', drilldown '.$drilldown;
      }
      $pageOrTagCumDrilldownRowString .= '</td>';
      
      foreach($monthOrYearList as $monthOrYear) {
	$viewcount = $viewcountarray[$pageOrTag][$monthOrYear][$drilldown];
	if ($pageOrTagAdvice=='page' and $monthOrYearAdvice=='month') {
	  $pageOrTagCumDrilldownRowString .= printMonthViewCount($pageOrTag,$monthOrYear,$language,$drilldown,$viewcount,$numericDisplayFormat);
	} elseif ($pageOrTagAdvice=='page' and $monthOrYearAdvice=='year') {
	  $pageOrTagCumDrilldownRowString .= printYearViewCount($pageOrTag,$monthOrYear,$language,$drilldown,$viewcount,$numericDisplayFormat);
	} elseif ($pageOrTagAdvice=='tag' and $monthOrYearAdvice=='month') {
	  $pageOrTagCumDrilldownRowString .= printtagviewcount($pageOrTag,$monthOrYear,$language,$drilldown,$viewcount,$numericDisplayFormat);
	} elseif ($pageOrTagAdvice=='tag' and $monthOrYearAdvice=='year') {
	  $pageOrTagCumDrilldownRowString .= printtagviewcountbyyear($pageOrTag,$monthOrYear,$language,$drilldown,$viewcount,$numericDisplayFormat);
	}
      }
      if ($includetotal=='includetotal' and count($monthOrYearList) > 1) {
	$pageOrTagCumDrilldownRowString .='<td align="right"><strong><element title="'.$pageOrTagCumDrilldownTotal[$pageOrTag][$drilldown].'">'.numericDisplay($pageOrTagCumDrilldownTotal[$pageOrTag][$drilldown],$numericDisplayFormat).'</element></strong></td>';
      }
      if (count($pageOrTagList) * count($drilldownList) > 1) {
	$pageOrTagCumDrilldownRowString .= '<td align="right"><strong>'.$pageOrTagCumDrilldownPercentage[$pageOrTag][$drilldown].'</strong></td>';
      }
      if ($pageOrTagAdvice == 'page') {
        $pageOrTagCumDrilldownRowString .= '<td>';
	if (count($tagListForPage)==0) {
	  $pageOrTagCumDrilldownRowString .= "--";
        }
	foreach ($tagListForPage as $tag) {
          if ($monthOrYearAdvice == 'month') {
            $pageOrTagCumDrilldownRowString .= '<a href="http://wikipediaviews.org/displayviewsformultiplemonths.php?tag='.$tag.'&language='.$language.'&drilldown='.$drilldown.'&allmonths=allmonths">'.$tag.'</a> ';
	  } else {
            $pageOrTagCumDrilldownRowString .= '<a href="http://wikipediaviews.org/displayviewsformultipleyears.php?tag='.$tag.'&language='.$language.'&drilldown='.$drilldown.'&allyears=allyears">'.$tag.'</a> ';
	  }
        }
        $pageOrTagCumDrilldownRowString .= '</td>';
      }
      $pageOrTagCumDrilldownRowString .="</tr>";
      print $pageOrTagCumDrilldownRowString;
    }
    if (count($drilldownList) > 1 and count($pageOrTagList) > 1) {
      if ($pageOrTagAdvice=='page') {
        $pageOrTagSummaryString = '<tr><td><strong><a href="'.getpageurl($pageOrTag,$language).'" title = "'.$pageOrTag.' (read page on Wikipedia)">'.$pageOrTag.'</a>, sum over drilldowns</strong></td>';
      } elseif ($pageOrTagAdvice=='tag' and $monthOrYearAdvice=='month') {
        $pageOrTagSummaryString = '<tr><td><strong><a href="http://wikipediaviews.org/displayviewsformultiplemonths.php?tag='.$pageOrTag.'&language='.$language.'&drilldown='.$drilldown.'&allmonths=allmonths">'.$pageOrTag.'</a>, sum over drilldowns</strong></td>';
      } elseif ($pageOrTagAdvice=='tag' and $monthOrYearAdvice=='year') {
        $pageOrTagSummaryString = '<td><a href="http://wikipediaviews.org/displayviewsformultipleyears.php?tag='.$pageOrTag.'&language='.$language.'&drilldown='.$drilldown.'&allyears=allyears">'.$pageOrTag.'</a>, sum over drilldowns</td>';
      }
      foreach($monthOrYearList as $monthOrYear) {
	$viewcount = $pageOrTagCumMonthOrYearTotal[$pageOrTag][$monthOrYear];
	if ($pageOrTagAdvice=='page' and $monthOrYearAdvice=='month') {
	  $pageOrTagSummaryString .= printMonthViewCount($pageOrTag,$monthOrYear,$language,"all",$viewcount,$numericDisplayFormat);
	} elseif ($pageOrTagAdvice=='page' and $monthOrYearAdvice=='year') {
	  $pageOrTagSummaryString .= printYearViewCount($pageOrTag,$monthOrYear,$language,"all",$viewcount,$numericDisplayFormat);
	} elseif ($pageOrTagAdvice=='tag' and $monthOrYearAdvice=='month') {
	  $pageOrTagSummaryString .= printtagviewcount($pageOrTag,$monthOrYear,$language,"all",$viewcount,$numericDisplayFormat);
	} elseif ($pageOrTagAdvice=='tag' and $monthOrYearAdvice=='year') {
	  $pageOrTagSummaryString .= printtagviewcountbyyear($pageOrTag,$monthOrYear,$language,"all",$viewcount,$numericDisplayFormat);
	}
      }
      if ($includetotal=='includetotal' and count($monthOrYearList) > 1) {
        $pageOrTagSummaryString .='<td align="right"><strong><element title="'.$pageOrTagTotal[$pageOrTag].'">'.numericDisplay($pageOrTagTotal[$pageOrTag],$numericDisplayFormat).'</element></strong></td>';
      }
      $pageOrTagSummaryString .= '<td align="right"><strong>'.$pageOrTagPercentage[$pageOrTag].'</strong></td>';
      if ($pageOrTagAdvice == 'page') {
        $pageOrTagSummaryString .= '<td>';
	if (count($tagListForPage)==0) {
	  $pageOrTagSummaryString .= "--";
        }
	foreach ($tagListForPage as $tag) {
          if ($monthOrYearAdvice == 'month') {
            $pageOrTagSummaryString .= '<a href="http://wikipediaviews.org/displayviewsformultiplemonths.php?tag='.$tag.'&language='.$language.'&drilldown=all&allmonths=allmonths">'.$tag.'</a> ';
	  } else {
            $pageOrTagSummaryString .= '<a href="http://wikipediaviews.org/displayviewsformultipleyears.php?tag='.$tag.'&language='.$language.'&drilldown=all&allyears=allyears">'.$tag.'</a> ';
	  }
        }
        $pageOrTagSummaryString .= '</td>';
      }
      $pageOrTagSummaryString .="</tr>";
      print $pageOrTagSummaryString;
    }
  }
  if (includetotal=='includetotal' and count($pageOrTagList) > 1 and count($drilldownList) > 1) {
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
  if ($includetotal=='includetotal' and count($pageOrTagList) * count($drilldownList) > 1) {
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
    if ($includetotal == 'includetotal') {
      $percentagesRowString .= '<td align="right"><strong>100</strong></td>';
    }
    if (count($pageOrTagList) * count($drilldownList) > 1) {
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

function printPageviewsForMonthOrYearListAsHtmlTableTransposed($pageOrTagList,$monthOrYearList,$language,$drilldownList,$explanatoryheader,$includetotal,$numericDisplayFormat,$normalization='',$pageOrTagAdvice='page',$monthOrYearAdvice='month') {
  global $timeTaken;
  $startTime = microtime(true);
  flush();
  #Check that sizes are workable
  $sizeOverflow = checkSizes($pageOrTagList,$monthOrYearList,$drilldownList);
  if ($sizeOverflow > 0)
    return false;

  #Collect all the numbers that need to be printed first
  if ($pageOrTagAdvice=='page' and $monthOrYearAdvice=='month') {
    $viewcountarray = viewcountarraybymonth($pageOrTagList,$monthOrYearList,$language,$drilldownList,true,$normalization);
  } elseif ($pageOrTagAdvice=='page' and $monthOrYearAdvice=='year') {
    $viewcountarray = viewcountarraybyyear($pageOrTagList,$monthOrYearList,$language,$drilldownList,true,$normalization);
  } elseif ($pageOrTagAdvice=='tag' and $monthOrYearAdvice=='month') {
    $viewcountarray = viewcountarraybytagandmonth($pageOrTagList,$monthOrYearList,$language,$drilldownList,true,$normalization);
  } elseif ($pageOrTagAdvice=='tag' and $monthOrYearAdvice=='year') {
    $viewcountarray = viewcountarraybytagandyear($pageOrTagList,$monthOrYearList,$language,$drilldownList,true,$normalization);
  }
  $tap = totalsAndPercentages($pageOrTagList,$monthOrYearList,$drilldownList,$viewcountarray);
  $grandTotal = $tap["grandTotal"];
  $pageOrTagCumDrilldownTotal = $tap["pageOrTagCumDrilldownTotal"];
  $pageOrTagCumMonthOrYearTotal = $tap["pageOrTagCumMonthOrYearTotal"];
  $drilldownCumMonthOrYearTotal = $tap["drilldownCumMonthOrYearTotal"];
  $pageOrTagTotal = $tap["pageOrTagTotal"];
  $drilldownTotal = $tap["drilldownTotal"];
  $monthOrYearTotal = $tap["monthOrYearTotal"];
  $pageOrTagCumDrilldownPercentage = $tap["pageOrTagCumDrilldownPercentage"];
  $pageOrTagCumMonthOrYearPercentage = $tap["pageOrTagCumMonthOrYearPercentage"];
  $drilldownCumMonthOrYearPercentage = $tap["drilldownCumMonthOrYearPercentage"];
  $pageOrTagPercentage = $tap["pageOrTagPercentage"];
  $drilldownPercentage = $tap["drilldownPercentage"];
  $monthOrYearPercentage = $tap["monthOrYearPercentage"];

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
    foreach($drilldownList as $drilldown) {
      $shortDescriptor = getShortDescriptor($drilldown);
      if ($pageOrTagAdvice=='page') {
        $headerstring .= '<th>'.$shortDescriptor.' of page <a href="'. getpageurl($pageOrTag,$language). '" title="'.$pageOrTag.' (read page on Wikipedia)">' . $pageOrTag.'</a>';
      } elseif ($pageOrTagAdvice=='tag' and $monthOrYearAdvice=='month') {
        $headerstring .= '<th>'.$shortDescriptor.' of pages with tag <a href="http://wikipediaviews.org/displayviewsformultiplemonths.php?tag='.$pageOrTag.'&language='.$language.'&drilldown='.$drilldown.'&allmonths=allmonths">'.$pageOrTag.'</a>';
      } elseif ($pageOrTagAdvice=='tag' and $monthOrYearAdvice=='year') {
        $headerstring .= '<th>Views of pages with tag <a href="http://wikipediaviews.org/displayviewsformultipleyears.php?tag='.$pageOrTag.'&language='.$language.'&drilldown='.$drilldown.'&allyears=allyears">'.$pageOrTag.'</a>';
      }
      if (count($drilldownList) > 1) {
        $headerstring .= ", drilldown ".$drilldown;
      }
      $headerstring .= '</th>';
    }
  }
  if ($includetotal=='includetotal' and count($pageOrTagList) * count($drilldownList) > 1) {
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
      foreach($drilldownList as $drilldown) {
        $viewcount = $viewcountarray[$pageOrTag][$monthOrYear][$drilldown];
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
    }
    if ($includetotal=='includetotal' and count($pageOrTagList) * count($drilldownList) > 1) {
      $monthOrYearRowString .='<td align="right"><strong><element title="'.$monthOrYearTotal[$monthOrYear].'">'.numericDisplay($monthOrYearTotal[$monthOrYear],$numericDisplayFormat).'</element></strong></td>';
    }
    if (count($monthOrYearList) > 1) {
      $monthOrYearRowString .='<td align="right"><strong>'.$monthOrYearPercentage[$monthOrYear].'</strong></td></tr>';
    }
    print $monthOrYearRowString;
  }
    
  ##Totals row
  if ($includetotal=='includetotal' and count($monthOrYearList) > 1) {
    $totalsRowString="<tr><td><strong>Total</strong></td>";
    foreach($pageOrTagList as $pageOrTag) { #Prints bottom row with totals
      foreach($drilldownList as $drilldown) {
        $totalsRowString .= '<td align="right"><strong><element title="'.$pageOrTagCumDrilldownTotal[$pageOrTag][$drilldown].'">'.numericDisplay($pageOrTagCumDrilldownTotal[$pageOrTag][$drilldown],$numericDisplayFormat).'</element></strong></td>';
      }
    }
    if (count($pageOrTagList) * count($drilldownList) > 1) { 
      $totalsRowString .= '<td align="right"><strong><element title="'.$grandTotal.'">'.numericDisplay($grandTotal,$numericDisplayFormat).'</element></strong></td>';
    }
    $totalsRowString .= '<td align="right"><strong>100</strong></td></tr>';
    print $totalsRowString;
  }

  ##Percentages row
  if (count($pageOrTagList) * count($drilldownList) > 1) {
    $percentagesRowString = "<tr><td><strong>Percentage</strong></td>";
    foreach($pageOrTagList as $pageOrTag) {
      foreach($drilldownList as $drilldown) {
	$percentagesRowString .= '<td align="right"><strong>'.$pageOrTagCumDrilldownPercentage[$pageOrTag][$drilldown].'</strong></td>';
      }
    }
    if ($includetotal == 'includetotal') {
      $percentagesRowString .= '<td align="right"><strong>100</strong></td>';
    }
    if (count($monthOrYearList) > 1) {
      $percentagesRowString .= '<td align="right">--</td></tr>';
    }
    print $percentagesRowString;
  }

  ##Tags row
  if ($pageOrTagAdvice == 'page') {
    $tagsRowString = "<tr><td><strong>Tags</strong></td>";
    foreach ($pageOrTagList as $pageOrTag) {
      foreach ($drilldownList as $drilldown) {  
	$tagsRowString .= '<td>';
	$tagListForPage = $tagListByPages[$pageOrTag];
	if (count($tagListForPage)==0) {
	  $tagsRowString .= "--";
	}
	foreach ($tagListForPage as $tag) {
	  if ($monthOrYearAdvice == 'month') {
            $tagsRowString .= '<a href="http://wikipediaviews.org/displayviewsformultiplemonths.php?tag='.$tag.'&language='.$language.'&allmonths=allmonths">'.$tag.'</a> ';
	  } else {
            $tagsRowString .= '<a href="http://wikipediaviews.org/displayviewsformultipleyears.php?tag='.$tag.'&language='.$language.'&allyears=allyears">'.$tag.'</a> ';
	  }
	}
	$tagsRowString .= '</td>';
      }
    }
    if (count($pageOrTagList) * count($drilldownList) > 1) {
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

function printPageviewsForMonthOrYearListAsCsv($pageOrTagList,$monthOrYearList,$language,$drilldown,$explanatoryheader,$includetotal,$numericDisplayFormat,$normalization='',$pageOrTagAdvice='page',$monthOrYearAdvice='month') {
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

  $tap = totalsAndPercentages($pageOrTagList,$monthOrYearList,$drilldownList,$viewcountarray);
  $grandTotal = $tap["grandTotal"];
  $pageOrTagCumDrilldownTotal = $tap["pageOrTagCumDrilldownTotal"];
  $pageOrTagCumMonthOrYearTotal = $tap["pageOrTagCumMonthOrYearTotal"];
  $drilldownCumMonthOrYearTotal = $tap["drilldownCumMonthOrYearTotal"];
  $pageOrTagTotal = $tap["pageOrTagTotal"];
  $drilldownTotal = $tap["drilldownTotal"];
  $monthOrYearTotal = $tap["monthOrYearTotal"];
  $pageOrTagCumDrilldownPercentage = $tap["pageOrTagCumDrilldownPercentage"];
  $pageOrTagCumMonthOrYearPercentage = $tap["pageOrTagCumMonthOrYearPercentage"];
  $drilldownCumMonthOrYearPercentage = $tap["drilldownCumMonthOrYearPercentage"];
  $pageOrTagPercentage = $tap["pageOrTagPercentage"];
  $drilldownPercentage = $tap["drilldownPercentage"];
  $monthOrYearPercentage = $tap["monthOrYearPercentage"];

  $headerstring = ucfirst($pageOrTagAdvice)." name";
  $descriptor = getDescriptor($drilldown);
  foreach($monthOrYearList as $monthOrYear) {
    $headerstring .= "|".$descriptor." in ".$monthOrYearAdvice." ".$monthOrYear;
  }
  if ($includetotal=='includetotal' and count($monthOrYearList) > 1) 
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
	if ($includetotal=='includetotal' and count($monthOrYearList) > 1) 
	  $stringtoprint .="|".$pageOrTagTotal[$pageOrTag];
	if (count($pageOrTagList) > 1) 
	    $stringtoprint .="|".$pageOrTagPercentage[$pageOrTag];
	$stringtoprint .="<br>";
	print $stringtoprint;
    }
  if ($includetotal == 'includetotal' and count($pageOrTagList) > 1)
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
  if (count($monthOrYearList) > 1)
    {
      $percentagesRowString = "Percentage";
      foreach($monthOrYearList as $monthOrYear)
	{
	  $percentagesRowString .= "|".$monthOrYearPercentage[$monthOrYear];
	}
      $percentagesRowString .= "|100";
      $percentagesRowString .= "<br>";
      print $percentagesRowString;
    }
}

function printPageviewsForMonthOrYearListAsCsvTransposed($pageOrTagList,$monthOrYearList,$language,$drilldown,$explanatoryheader,$includetotal,$numericDisplayFormat,$normalization='',$pageOrTagAdvice='page',$monthOrYearAdvice='month') {
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

  $tap = totalsAndPercentages($pageOrTagList,$monthOrYearList,$drilldownList,$viewcountarray);
  $grandTotal = $tap["grandTotal"];
  $pageOrTagCumDrilldownTotal = $tap["pageOrTagCumDrilldownTotal"];
  $pageOrTagCumMonthOrYearTotal = $tap["pageOrTagCumMonthOrYearTotal"];
  $drilldownCumMonthOrYearTotal = $tap["drilldownCumMonthOrYearTotal"];
  $pageOrTagTotal = $tap["pageOrTagTotal"];
  $drilldownTotal = $tap["drilldownTotal"];
  $monthOrYearTotal = $tap["monthOrYearTotal"];
  $pageOrTagCumDrilldownPercentage = $tap["pageOrTagCumDrilldownPercentage"];
  $pageOrTagCumMonthOrYearPercentage = $tap["pageOrTagCumMonthOrYearPercentage"];
  $drilldownCumMonthOrYearPercentage = $tap["drilldownCumMonthOrYearPercentage"];
  $pageOrTagPercentage = $tap["pageOrTagPercentage"];
  $drilldownPercentage = $tap["drilldownPercentage"];
  $monthOrYearPercentage = $tap["monthOrYearPercentage"];

  $headerstring = ucfirst($monthOrYearAdvice);
  foreach($pageOrTagList as $pageOrTag)
    $headerstring .= "|Views of ".$pageOrTagAdvice." ".$pageOrTag;
  if ($includetotal=='includetotal' and count($pageOrTagList) > 1) 
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
	if ($includetotal=='includetotal' and count($pageOrTagList) > 1) 
	  $stringtoprint .="|".$monthOrYearTotal[$monthOrYear];
	if (count($monthOrYearList) > 1) 
	  {
	    $stringtoprint .="|".$monthOrYearPercentage[$monthOrYear];
	  }
	$stringtoprint .="<br>";
	print $stringtoprint;
    }
  if ($includetotal == 'includetotal' and count($monthOrYearList) > 1)
    {
      $totalsRowString = "Total";
      foreach($pageOrTagList as $pageOrTag)
	$totalsRowString .= "|".$pageOrTagTotal[$pageOrTag];
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

function generateGraphs($pageOrTagList,$monthOrYearList,$language,$drilldownList,$explanatoryheader,$includetotal,$numericDisplayFormat,$normalization='',$pageOrTagAdvice='page',$monthOrYearAdvice='month') {
  global $graphTimeTaken;
  global $imagesPath;
  global $generateGraphCmdBase;
  $graphStartTime = microtime(true);
  #Check that sizes are workable
  $sizeOverflow = checkSizes($pageOrTagList,$monthOrYearList,$drilldownList);
  if ($sizeOverflow > 0)
    return false;
  #Collect all the numbers that need to be printed first
  if ($pageOrTagAdvice=='page' and $monthOrYearAdvice=='month')
    $viewcountarray = viewcountarraybymonth($pageOrTagList,$monthOrYearList,$language,$drilldownList,false,$normalization);
  elseif ($pageOrTagAdvice=='page' and $monthOrYearAdvice=='year')
    $viewcountarray = viewcountarraybyyear($pageOrTagList,$monthOrYearList,$language,$drilldownList,false,$normalization);
  elseif ($pageOrTagAdvice=='tag' and $monthOrYearAdvice=='month')
    $viewcountarray = viewcountarraybytagandmonth($pageOrTagList,$monthOrYearList,$language,$drilldownList,false,$normalization);
  elseif ($pageOrTagAdvice=='tag' and $monthOrYearAdvice=='year')
    $viewcountarray = viewcountarraybytagandyear($pageOrTagList,$monthOrYearList,$language,$drilldownList,false,$normalization);

  $tap = totalsAndPercentages($pageOrTagList,$monthOrYearList,$drilldownList,$viewcountarray);
  $grandTotal = $tap["grandTotal"];
  $pageOrTagCumDrilldownTotal = $tap["pageOrTagCumDrilldownTotal"];
  $pageOrTagCumMonthOrYearTotal = $tap["pageOrTagCumMonthOrYearTotal"];
  $drilldownCumMonthOrYearTotal = $tap["drilldownCumMonthOrYearTotal"];
  $pageOrTagTotal = $tap["pageOrTagTotal"];
  $drilldownTotal = $tap["drilldownTotal"];
  $monthOrYearTotal = $tap["monthOrYearTotal"];
  $pageOrTagCumDrilldownPercentage = $tap["pageOrTagCumDrilldownPercentage"];
  $pageOrTagCumMonthOrYearPercentage = $tap["pageOrTagCumMonthOrYearPercentage"];
  $drilldownCumMonthOrYearPercentage = $tap["drilldownCumMonthOrYearPercentage"];
  $pageOrTagPercentage = $tap["pageOrTagPercentage"];
  $drilldownPercentage = $tap["drilldownPercentage"];
  $monthOrYearPercentage = $tap["monthOrYearPercentage"];

  $fullOutput = "";

  $headerstring = ucfirst($monthOrYearAdvice);
  foreach($pageOrTagList as $pageOrTag) {
    foreach ($drilldownList as $drilldown) {
      $headerstring .= "|".$pageOrTag." on drilldown ".$drilldown;
    }
  }
  if ($includetotal=='includetotal' and count($pageOrTagList) * count($drilldownList) > 1) {
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
      foreach($drilldownList as $drilldown) { 
        $viewcount = $viewcountarray[$pageOrTag][$monthOrYear][$drilldown];
        $numericViewCount = 0;
        $numericViewCount = $numericViewCount + $viewcount;
        $stringtoprint .= "|".$numericViewCount;
      }
    }
    if ($includetotal=='includetotal' and count($pageOrTagList) * count($drilldownList) > 1) {
      $stringtoprint .="|".$monthOrYearTotal[$monthOrYear];
    }
    if (count($monthOrYearList) > 1) {
      $stringtoprint .="|".$monthOrYearPercentage[$monthOrYear];
    }
    $stringtoprint .="\n";
    $fullOutput .= $stringtoprint;
  }
  if ($includetotal == 'includetotal' and count($monthOrYearList) > 1) {
    $totalsRowString = "Total";
    foreach($pageOrTagList as $pageOrTag) {
      foreach($drilldownList as $drilldown) {
        $totalsRowString .= "|".$pageOrTagCumDrilldownTotal[$pageOrTag][$drilldown];
      }
    }
    if (count($pageOrTagList) * count($drilldownList) > 1) {
      $totalsRowString .= "|".$grandTotal;
    }
    $totalsRowString .="|100";
    $totalsRowString .= "\n";
    $fullOutput .= $totalsRowString;
  }
  if (count($pageOrTagList) > 0) {
    $percentagesRowString = "Percentage";
    foreach($pageOrTagList as $pageOrTag) {
      foreach($drilldownList as $drilldown) {
        $percentagesRowString .= "|".$pageOrTagCumDrilldownPercentage[$pageOrTag][$drilldown];
      }
    }
    $percentagesRowString .= "|100";
    $percentagesRowString .= "\n";
    $fullOutput .= $percentagesRowString;
  }

  # Drilldown output
  $drilldownOutput = "";
  if (count($pageOrTagList) > 1 and count($drilldownList) > 1) {
    $headerstring = ucfirst($monthOrYearAdvice);
    foreach ($drilldownList as $drilldown) {
      $headerstring .= "|".$drilldown;
    }
    if ($includetotal=='includetotal' and count($pageOrTagList) * count($drilldownList) > 1) {
      $headerstring .="|Total";
    }
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
      if ($includetotal=='includetotal') {
        $stringtoprint .="|".$monthOrYearTotal[$monthOrYear];
      }
      if (count($monthOrYearList) > 1) {
        $stringtoprint .="|".$monthOrYearPercentage[$monthOrYear];
      }
      $stringtoprint .="\n";
      $drilldownOutput .= $stringtoprint;
    }
    if ($includetotal == 'includetotal' and count($monthOrYearList) > 1) {
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
  if (count($drilldownList) > 1 and count($pageOrTagList) > 1) {
    $headerstring = ucfirst($monthOrYearAdvice);
    foreach ($pageOrTagList as $pageOrTag) {
      $headerstring .= "|".$pageOrTag;
    }
    if ($includetotal=='includetotal' and count($pageOrTagList) * count($drilldownList) > 1) {
      $headerstring .="|Total";
    }
    if (count($monthOrYearList) > 1) {
      $headerstring .="|Percentage";
    }
    $headerstring .="\n";
    $pageOrTagOutput .= $headerstring;
    foreach($monthOrYearList as $monthOrYear) {
      $stringtoprint = $monthOrYear;
      $total = 0;
      foreach($pageOrTagList as $pageOrTag) { 
        $viewcount = $pageOrTagCumMonthOrYearTotal[$pageOrTag][$monthOrYear];
        $numericViewCount = 0;
        $numericViewCount = $numericViewCount + $viewcount;
        $stringtoprint .= "|".$numericViewCount;
      }
      if ($includetotal=='includetotal') {
        $stringtoprint .="|".$monthOrYearTotal[$monthOrYear];
      }
      if (count($monthOrYearList) > 1) {
        $stringtoprint .="|".$monthOrYearPercentage[$monthOrYear];
      }
      $stringtoprint .="\n";
      $pageOrTagOutput .= $stringtoprint;
    }
    if ($includetotal == 'includetotal' and count($monthOrYearList) > 1) {
      $totalsRowString = "Total";
      foreach($pageOrTagList as $pageOrTag) {
        $totalsRowString .= "|".$pageOrTagTotal[$pageOrTag];
      }
    }
    if (count($pageOrTagList) > 1) {
      $totalsRowString .= "|".$grandTotal;
    }
    $totalsRowString .="|100";
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

  $fileName = strval(rand());
  $filePathBase = $imagesPath . $fileName;
  file_put_contents($filePathBase . ".csv", $fullOutput);
  $cmdToExecute = $generateGraphCmdBase . " " . $filePathBase . ".csv " . $filePathBase . ".png ";
  if ($numericDisplayFormat == "log") {
    $cmdToExecute = $cmdToExecute . " --log10";
  }
  # print("Going to try executing ".$cmdToExecute."<br>");
  exec($cmdToExecute);
  print "<br/><br/>";
  if (count($pageOrTagList) * count($drilldownList) > 30) {
    $addendum = ", restricted to the top 30 by total across months";
  } else {
    $addendum = "";
  }
  if (count($pageOrTagList) > 1 and count($drilldownList) > 1) {
    print "<strong>Graph of data; includes overall total and a separate curve for each combination of ".$pageOrTagAdvice." and drilldown".$addendum." below:</strong><br/>"; 
  } else if (count($drilldownList) > 1) {
    print "<strong>Graph of data; includes overall total and a separate curve for each drilldown".$addendum." below:</strong><br/>";
  } else if (count($pageOrTagList) > 1) {
    print "<strong>Graph of data; includes overall total and a separate curve for each ".$pageOrTagAdvice.$addendum." below:</strong><br/>";
  } else {
    print "<strong>Graph of data below:</strong><br/>";
  }
  print '<img src="/images/'.$fileName.'.png" alt="Graph of pageviews should have loaded here"></img>';
  if (count($pageOrTagList) > 1 and count($drilldownList) > 1) {
    # Construct drilldown-grouped data
    $drilldownFileName = $fileName."-drilldown";
    $drilldownFilePathBase = $imagesPath . $drilldownFileName;
    file_put_contents($drilldownFilePathBase . ".csv", $drilldownOutput);
    $cmdToExecute = $generateGraphCmdBase . " " . $drilldownFilePathBase . ".csv " . $drilldownFilePathBase . ".png";
    if ($numericDisplayFormat == "log") {
      $cmdToExecute = $cmdToExecute . " --log10";
    }
    exec($cmdToExecute);
    print "<br><br>";
    print "<strong>Graph of data; one curve for total by each drilldown, one curve for total, below:</strong><br/>";
    print '<img src="/images/'.$drilldownFileName.'.png" alt="Graph of pageviews should have loaded here"></img>';

    # Construct page or tag
    $pageOrTagFileName = $fileName."-".$pageOrTagAdvice;
    $pageOrTagFilePathBase = $imagesPath . $pageOrTagFileName;
    file_put_contents($pageOrTagFilePathBase . ".csv", $pageOrTagOutput);
    $cmdToExecute = $generateGraphCmdBase . " " . $pageOrTagFilePathBase . ".csv " . $pageOrTagFilePathBase . ".png";
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
    print "<strong>Graph of data; one curve for total by each page, one curve for total".$addendum.", below:</strong><br/>";
    print '<img src="/images/'.$pageOrTagFileName.'.png" alt="Graph of pageviews should have loaded here"></img>';
  }
  $graphEndTime = microtime(true);
  $graphTimeTaken = $graphEndTime - $graphStartTime;
}

function printPageviewsForMonthOrYearListAsCpi($pageOrTagList,$monthOrYearList,$language,$drilldown,$explanatoryheader,$includetotal,$numericDisplayFormat,$normalization='',$pageOrTagAdvice='page',$monthOrYearAdvice='month') {
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
