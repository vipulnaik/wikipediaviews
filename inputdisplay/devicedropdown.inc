<tr><td>Enter the device type for which you are interested in pageviews (option not currently active; will show desktop pageviews reagrdless of selection): </td><td><select name="device">
  <option value="desktop" <?php if ($formdata== true  and $device=="desktop") {print 'selected="selected"';} ?>>Desktop</option>
  <option value="mobile-web" <?php if ($formdata==true and $device=="mobile-web") {print 'selected="selected"';} ?>>Mobile web</option>
  <option value="mobile-app" <?php if ($formdata==true and $device=="mobile-app") {print 'selected="selected"';} ?>>Mobile app</option>
</select></td></tr>
