<tr><td>Enter the language Wikipedia that you are interested in: </td><td><select name="language">
  <option value="en" <?php if ($formdata== true  and $language=="en") {print 'selected="selected"';} ?>>English (en)</option>
  <option value="de" <?php if ($formdata==true and $language=="de") {print 'selected="selected"';} ?>>German (Deutsch) (de)</option>
  <option value="fr" <?php if ($formdata==true and $language=="fr") {print 'selected="selected"';} ?>>French (Francais) (fr)</option>
  <option value="es" <?php if ($formdata==true and $language=="es") {print 'selected="selected"';} ?>>Spanish (Espanol) (es)</option>
  <option value="it" <?php if ($formdata==true and $language=="it") {print 'selected="selected"';} ?>>Italian (Italiano) (it)</option>
  <option value="nl" <?php if ($formdata==true and $language=="nl") {print 'selected="selected"';} ?>>Dutch (Nederlands) (nl)</option>
  <option value="pl" <?php if ($formdata==true and $language=="pl") {print 'selected="selected"';} ?>>Polish (Polski) (pl)</option>
  <option value="ru" <?php if ($formdata==true and $language=="ru") {print 'selected="selected"';} ?>>Russian (Russkiy) (ru)</option>
  <option value="pt" <?php if ($formdata==true and $language=="pt") {print 'selected="selected"';} ?>>Portuguese (Portugues) (pt)</option>
  <option value="sv" <?php if ($formdata==true and $language=="sv") {print 'selected="selected"';} ?>>Swedish (Svenska) (sv)</option>
  <option value="zh" <?php if ($formdata==true and $language=="zh") {print 'selected="selected"';} ?>>Chinese (Zhongwen) (zh)</option>
  <option value="simple" <?php if ($formdata==true and $language=="simple") {print 'selected="selected"';} ?>>Simple English (simple)</option>
  <option value="zh-classical" <?php if ($formdata==true and $language=="zh-classical") {print 'selected="selected"';} ?>>Chinese (Zhongwen) (classical) (zh-classical)</option>
  <option value="no" <?php if ($formdata==true and $language=="no") {print 'selected="selected"';} ?>>Norwegian (Norsk (bokmal)) (no)</option>
  <option value="fi" <?php if ($formdata==true and $language=="fi") {print 'selected="selected"';} ?>>Finnish (fi)</option>
  <option value="hi" <?php if ($formdata==true and $language=="hi") {print 'selected="selected"';} ?>>Hindi (hi)</option>
  <option value="ja" <?php if ($formdata==true and $language=="ja") {print 'selected="selected"';} ?>>Japanese (ja)</option>
</select></td></tr>
