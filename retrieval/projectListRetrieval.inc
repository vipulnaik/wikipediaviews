<?php

# Retrieves the list of languages

## Retrieval of language
$projectList = array("wikipedia");
if (!empty($_REQUEST['projects'])) {
  $projectList = $_REQUEST['projects'];
}
if (!empty($_REQUEST['projectList'])) {
  $projectList = $_REQUEST['projectList'];
}
if (!empty($_REQUEST['project'])) {
  $sentProject = $_REQUEST['project'];
  $projectList = array($sentProject);
}

if (count($projectList) == 1 && projectList[0] != "wikipedia") {
  $projectUrlComponent = "&project=".$projectList[0];
} else if (count($projectList) == 1) {
  $projectUrlComponent = "";
} else {
  $projectUrlComponent = "";
  for ($i = 0; $i < count($projectList); $i++) {
    $projectUrlComponent .= "&projects[$i]=".$projectList[$i];
  }
}

?>
