<?php
$mysqli = new mysqli("localhost", "database name", "password", "username");
$mysqli->set_charset("utf8");
$imagesPath = "folder to store images"
$generateGraphCmdBase = "python3.5 (project folder)/python/graph.py --vertical_lines --top 30 ";
$generateDistribCmdBase = "python3.5 (project folder)/python/distrib.py ";
$unifontLocation = "/usr/share/fonts/truetype/unifont/unifont.ttf";
$fbToken = "Get token from https://developers.facebook.com/tools/explorer/";
$curlOutputDirectory="folder where you want to store temporary curl outputs";
$clickstreamFolder = "folder with downloaded clickstream data";
?>