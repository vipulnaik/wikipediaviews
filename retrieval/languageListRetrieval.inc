<?php

# Retrieves the list of languages

## Retrieval of language
$languageList = array("en");
if (!empty($_REQUEST['languages'])) {
  $languageList = $_REQUEST['languages'];
}
if (!empty($_REQUEST['languageList'])) {
  $languageList = $_REQUEST['languageList'];
}
if (!empty($_REQUEST['language'])) {
  $sentLanguage = $_REQUEST['language'];
  $languageList = array($sentLanguage);
}

if (count($languageList) == 1) {
  $languageUrlComponent = "&language=".$languageList[0];
} else {
  $languageUrlComponent = "";
  for ($i = 0; $i < count($languageList); $i++) {
    $languageUrlComponent .= "&languages[$i]=".$languageList[$i];
  }
}

?>
