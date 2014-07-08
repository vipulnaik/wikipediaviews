<?php
  include("corecode.inc");
  function removeduplicates()
  {
       global $mysqli;
       if ($mysqli->connect_errno) {
       echo "Failed to connect to MySQL: (" . $mysqli->connect_errno . ") " . $mysqli->connect_error;
}
       $delete_query = "delete from viewcountsbymonth where row_id in (select maxId from dupIDs_viewcountsbymonth);";
       $result=$mysqli->query($delete_query);
       $delete_query = "delete from viewcountsbyyear where row_id in (select maxId from dupIDs_viewcountsbyyear);";
       $result=$mysqli->query($delete_query);
       $delete_query = "delete from queriedpages where row_id in (select maxId from dupIDs_queriedpages);";
       $result=$mysqli->query($delete_query);
  }

  removeduplicates();
?>