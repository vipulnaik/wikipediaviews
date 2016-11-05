<tr><td>Enter the drilldown (filter) for which you are interested in pageviews: </td><td><select name="drilldown">
  <option value="desktop" <?php if ($formdata== true  and $drilldown=="desktop") {print 'selected="selected"';} ?>>Desktop</option>
  <option value="mobile-web" <?php if ($formdata==true and $drilldown=="mobile-web") {print 'selected="selected"';} ?>>Mobile web</option>
  <option value="mobile-app" <?php if ($formdata==true and $drilldown=="mobile-app") {print 'selected="selected"';} ?>>Mobile app</option>
  <option value="desktop-spider" <?php if ($formdata==true and $drilldown=="desktop-spider") {print 'selected="selected"';} ?>>Desktop spider</option>
  <option value="mobile-web-spider" <?php if ($formdata==true and $drilldown=="mobile-web-spider") {print 'selected="selected"';} ?>>Mobile web spider</option>
  <option value="cumulative-facebook-shares" <?php if ($formdata==true and $drilldown=="cumulative-facebook-shares") {print 'selected="selected"';} ?>>Cumulative Facebook share count (supported for month and not for year displays)</option>
</select></td></tr>
