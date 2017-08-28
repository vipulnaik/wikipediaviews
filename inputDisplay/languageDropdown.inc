<?php

print '<tr><td>Enter the language Wikipedia that you are interested in: </td><td><select name="language">';
$result = languages_sql();
for($i=0; $i < $result -> num_rows; $i++) {
  $row = $result -> fetch_assoc();
  print "<option value=\"".$row['code']."\" ";
  if ($formdata == true and (isset($language) and $language == $row['code']) or ((!isset($language) or $language == '') and $row['code'] == "en")) {
    print 'selected="selected"';
  }
  print ">".$row['name']." (".$row['code'].")</option>";
}
print "</select></td></tr>";
?>