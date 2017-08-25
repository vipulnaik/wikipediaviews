insert ignore into wantedviewcountsbymonth(pagename, monthfull, `language`, drilldown, status) select pagename, '201708', `language`, 'cumulative-facebook-shares', 'wanted' from (select distinct pagename, `language` from viewcountsbymonth where drilldown = 'desktop' and pagename != 'aggregate' and viewcount > 20) t1;

delete from wantedviewcountsbymonth where (pagename, monthfull, `language`, drilldown) in (select pagename, monthfull, `language`, drilldown from viewcountsbymonth where monthfull = '201708' and drilldown = 'cumulative-facebook-shares');

