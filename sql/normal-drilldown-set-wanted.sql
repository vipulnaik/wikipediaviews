create temporary table insertion_list as select distinct pagename, `language` from viewcountsbymonth where drilldown = 'desktop' and viewcount > 0; insert ignore into wantedviewcountsbymonth(pagename, monthfull, `language`, drilldown, status) select pagename, '202005', `language`, 'desktop', 'wanted' from insertion_list; insert ignore into wantedviewcountsbymonth(pagename, monthfull, `language`, drilldown, status) select pagename, '202005', `language`, 'mobile-web', 'wanted' from insertion_list; insert ignore into wantedviewcountsbymonth(pagename, monthfull, `language`, drilldown, status) select pagename, '202005', `language`, 'mobile-app', 'wanted' from insertion_list; insert ignore into wantedviewcountsbymonth(pagename, monthfull, `language`, drilldown, status) select pagename, '202005', `language`, 'desktop-spider', 'wanted' from insertion_list; insert ignore into wantedviewcountsbymonth(pagename, monthfull, `language`, drilldown, status) select pagename, '202005', `language`, 'mobile-web-spider', 'wanted' from insertion_list;
