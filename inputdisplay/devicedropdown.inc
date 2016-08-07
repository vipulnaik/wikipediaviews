<tr><td>Enter the device type for which you are interested in pageviews (option not currently active; will show desktop pageviews reagrdless of selection): </td><td><select name="device">
  <option value="desktop" <?php if ($formdata== true  and $device=="desktop") {print 'selected="selected"';} ?>>Desktop (pageviews from a browser to the main, non-mobile site)</option>
  <option value="mobile-web" <?php if ($formdata==true and $device=="mobile-web") {print 'selected="selected"';} ?>>Mobile web (pageviews from a browser to the mobile website; mobile browsers default to the mobile website)</option>
  <option value="mobile-app" <?php if ($formdata==true and $device=="mobile-app") {print 'selected="selected"';} ?>>Mobile app</option>
</select></td></tr>
