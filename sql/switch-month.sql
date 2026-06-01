update months set status = 'past' where monthfull = date_format(date_add(curdate(), interval -2 month), '%Y%m') and status = 'mostrecent';
update months set status = 'mostrecent' where monthfull = date_format(date_add(curdate(), interval -1 month), '%Y%m') and status = 'present';
update months set status = 'present' where monthfull = date_format(curdate(), '%Y%m') and status = 'future';
delete from viewcountsbymonth where monthfull = date_format(date_add(curdate(), interval -1 month), '%Y%m');
delete from viewcountsbyyear where year = year(date_add(curdate(), interval -1 month));
