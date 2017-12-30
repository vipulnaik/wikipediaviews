insert ignore into wantedviewcountsbymonth(pagename, monthfull, `language`, drilldown, status) select pagename, '201712', `language`, 'cumulative-facebook-shares', 'wanted' from (select distinct pagename, `language` from viewcountsbymonth where drilldown = 'cumulative-facebook-shares' and pagename != '[aggregate]' and viewcount > 0 and viewcount < 50) t1; # Pick pages that have at least some shares on Facebook, but not too many. The ones with too many shares, we will do in a separate round right near the turn of the month for maximum accuracy

delete from wantedviewcountsbymonth where (pagename, monthfull, `language`, drilldown) in (select pagename, monthfull, `language`, drilldown from viewcountsbymonth where monthfull = '201712' and drilldown = 'cumulative-facebook-shares');

