<?php
$mysqli = new mysqli("localhost", "username", "password", "database name");
$mysqli->set_charset("utf8");
$imagesPath = "folder to store images (with trailing slash)";
$generateGraphCmdBase = "python3 (project folder)/python/graph.py --label --vertical_lines --top 30 ";
$generateDistribCmdBase = "python3 (project folder)/python/distrib.py ";
$unifontLocation = "/usr/share/fonts/truetype/unifont/unifont.ttf";
$fbToken = "Get token from https://developers.facebook.com/tools/explorer/";
$fbTokenStartTime = "Epoch time when you set the FB token. We assume the token works for another 60 minutes";
$curlOutputDirectory="folder where you want to store temporary curl outputs";
$clickstreamFolder = "folder with downloaded clickstream data";
?>