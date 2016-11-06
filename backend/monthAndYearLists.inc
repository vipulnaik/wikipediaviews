<?php

function presentandpastmonths_sql()
{
  global $mysqli;
  if ($mysqli->connect_errno) 
    {
      echo "Failed to connect to MySQL: (" . $mysqli->connect_errno . ") " . $mysqli->connect_error;
    }
  $select_query = "select monthfull,month,year,status from months where status!='future'";
  return $mysqli->query($select_query);
}	

function pastmonths_sql()
{
  global $mysqli;
  if ($mysqli->connect_errno) 
    {
      echo "Failed to connect to MySQL: (" . $mysqli->connect_errno . ") " . $mysqli->connect_error;
    }
  $select_query = "select monthfull,month,year,status from months where status!='future' and status!='present'";
  return $mysqli->query($select_query);
}	

function presentandpastyears_sql()
{
  global $mysqli;
  if ($mysqli->connect_errno) 
    {
      echo "Failed to connect to MySQL: (" . $mysqli->connect_errno . ") " . $mysqli->connect_error;
    }
  $select_query = "select year,status from years where status!='future'";
  return $mysqli->query($select_query);
}	

function presentandpastyears_yearList()
{
  $sql_result = presentandpastyears_sql();
  $yearList = array();
  for ($i = 0;$i < $sql_result->num_rows;$i++)
    {
      $row = $sql_result->fetch_assoc();
      array_push($yearList,$row['year']);
    }
  return $yearList;
}

function presentandpastmonths_monthList()
{
  $sql_result = presentandpastmonths_sql();
  $monthList = array();
  for ($i = 0;$i < $sql_result->num_rows;$i++)
    {
      $row = $sql_result->fetch_assoc();
      array_push($monthList,$row['monthfull']);
    }
  return $monthList;
}

function pastmonths_monthList()
{
  $sql_result = pastmonths_sql();
  $monthList = array();
  for ($i = 0;$i < $sql_result->num_rows;$i++)
    {
      $row = $sql_result->fetch_assoc();
      array_push($monthList,$row['monthfull']);
    }
  return $monthList;
}

function pastmonthsinyear($year)
{
  global $mysqli;
  if ($mysqli->connect_errno) 
    {
      echo "Failed to connect to MySQL: (" . $mysqli->connect_errno . ") " . $mysqli->connect_error;
    }
  $select_query = "select monthfull,month,year,status from months where status!='future' and status!='present' and year='".$year."';";
  $sql_result = $mysqli->query($select_query);
  $monthList = array();
  for ($i = 0;$i < $sql_result->num_rows;$i++)
    {
      $row = $sql_result->fetch_assoc();
      array_push($monthList,$row['monthfull']);
    }
  return $monthList;
}	

function monthswithoutyears()
{
  return array('January','February','March','April','May','June','July','August','September','October','November','December');
}

function monthacrossallyears($month)
{
  global $mysqli;
  if ($mysqli->connect_errno) 
    {
      echo "Failed to connect to MySQL: (" . $mysqli->connect_errno . ") " . $mysqli->connect_error;
    }
  $select_query = "select monthfull,month from months where status!='future' and status!='present' and month='".$month."';";
  $sql_result = $mysqli->query($select_query);
  $monthList = array();
  for ($i = 0;$i < $sql_result->num_rows;$i++)
    {
      $row = $sql_result->fetch_assoc();
      array_push($monthList,$row['monthfull']);
    }
  return $monthList;
}

?>
