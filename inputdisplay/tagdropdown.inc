<tr><td>Select the tag that you want to work with (the page-tag relationships are defined locally on this site and do not correspond to any relationships on Wikipedia):</td><td><select name="tag">
<?php
  include_once(__DIR__."/../backend/corecode.inc");
  global $mysqli;
  if ($mysqli->connect_errno) {
       echo "Failed to connect to MySQL: (" . $mysqli->connect_errno . ") " . $mysqli->connect_error;
}
  $select_query = "select distinct tag from pagetags order by tag;";
  $result = $mysqli->query($select_query);
  $numrows = $result->num_rows;
  print '<option value="" selected="selected">-- (none selected) --</option>';
  for ($i=0;$i < $numrows; $i++)
  {
	$row = $result->fetch_assoc();
	$tag_current = $row['tag'];
	print '<option value="'.$tag_current.'"';
	if ($formdata == true and $tag == $tag_current) {print ' selected="selected"';}
	print '>'.$tag_current.'</option>';
  }
?>
</select></td></tr>
