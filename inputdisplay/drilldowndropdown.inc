<tr><td>Select the list of drilldowns (filters) for which you are interested in pageviews. You will see the counts separately for each drilldown.</td><td><select multiple name="drilldownList[]" size="6">
  <option value="desktop" <?php if (($formdata == false) or ($formdata== true  and in_array("desktop", $drilldownList))) {print 'selected="selected"';} ?>>Desktop (data from December 2007)</option>
  <option value="mobile-web" <?php if ($formdata==true and in_array("mobile-web", $drilldownList)) {print 'selected="selected"';} ?>>Mobile web (data from July 2015)</option>
  <option value="mobile-app" <?php if ($formdata==true and in_array("mobile-app", $drilldownList)) {print 'selected="selected"';} ?>>Mobile app (data from July 2015)</option>
  <option value="desktop-spider" <?php if ($formdata==true and in_array("desktop-spider", $drilldownList)) {print 'selected="selected"';} ?>>Desktop spider (data from July 2015)</option>
  <option value="mobile-web-spider" <?php if ($formdata==true and in_array("mobile-web-spider", $drilldownList)) {print 'selected="selected"';} ?>>Mobile web spider (data from July 2015)</option>
  <option value="cumulative-facebook-shares" <?php if ($formdata==true and in_array("cumulative-facebook-shares", $drilldownList)) {print 'selected="selected"';} ?>>Cumulative Facebook share count (supported for month and not for year displays) (data from October 2016)</option>
</select></td></tr>
