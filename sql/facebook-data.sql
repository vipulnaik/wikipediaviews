insert ignore into wantedviewcountsbymonth(pagename, monthfull, `language`, drilldown, status) select pagename, '201702', `language`, 'cumulative-facebook-shares', 'wanted' from (select distinct pagename, `language` from viewcountsbymonth) t1;

delete from wantedviewcountsbymonth where (pagename, monthfull, `language`, drilldown) in (select pagename, monthfull, `language`, drilldown from viewcountsbymonth where monthfull = '201702' and drilldown = 'cumulative-facebook-shares');

