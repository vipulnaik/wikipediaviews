<tr><td>Enter the drilldown (filter) for which you are interested in pageviews: </td><td><select multiple name="drilldownList[]" size="10">
  <option value="desktop" <?php if ($formdata== true  and in_array($drilldownList, "desktop")) {print 'selected="selected"';} ?>>Desktop</option>
  <option value="mobile-web" <?php if ($formdata==true and in_array($drilldownList, "mobile-web")) {print 'selected="selected"';} ?>>Mobile web</option>
  <option value="mobile-app" <?php if ($formdata==true and in_array($drilldownList, "mobile-app")) {print 'selected="selected"';} ?>>Mobile app</option>
  <option value="desktop-spider" <?php if ($formdata==true and in_array($drilldownList, "desktop-spider")) {print 'selected="selected"';} ?>>Desktop spider</option>
  <option value="mobile-web-spider" <?php if ($formdata==true and in_array($drilldownList, "mobile-web-spider")) {print 'selected="selected"';} ?>>Mobile web spider</option>
  <option value="cumulative-facebook-shares" <?php if ($formdata==true and in_array($drilldownList, "cumulative-facebook-shares")) {print 'selected="selected"';} ?>>Cumulative Facebook share count (supported for month and not for year displays)</option>
</select></td></tr>
