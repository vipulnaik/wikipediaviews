CREATE TABLE `languages` (
  `code` varchar(20) COLLATE utf8_unicode_ci NOT NULL,
  `name` varchar(40) COLLATE utf8_unicode_ci NOT NULL,
  `start` varchar(8) COLLATE utf8_unicode_ci NOT NULL DEFAULT 'unknown',
  `datastart` varchar(8) COLLATE utf8_unicode_ci NOT NULL DEFAULT '20080201',
  `rank` int(11) DEFAULT NULL,
  PRIMARY KEY (`code`),
  UNIQUE KEY `rank` (`rank`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci

CREATE TABLE `months` (
  `monthfull` enum('202012','202011','202010','202009','202008','202007','202006','202005','202004','202003','202002','202001','201912','201911','201910','201909','201908','201907','201906','201905','201904','201903','201902','201901','201812','201811','201810','201809','201808','201807','201806','201805','201804','201803','201802','201801','201712','201711','201710','201709','201708','201707','201706','201705','201704','201703','201702','201701','201612','201611','201610','201609','201608','201607','201606','201605','201604','201603','201602','201601','201512','201511','201510','201509','201508','201507','201506','201505','201504','201503','201502','201501','201412','201411','201410','201409','201408','201407','201406','201405','201404','201403','201402','201401','201312','201311','201310','201309','201308','201307','201306','201305','201304','201303','201302','201301','201212','201211','201210','201209','201208','201207','201206','201205','201204','201203','201202','201201','201112','201111','201110','201109','201108','201107','201106','201105','201104','201103','201102','201101','201012','201011','201010','201009','201008','201007','201006','201005','201004','201003','201002','201001','200912','200911','200910','200909','200908','200907','200906','200905','200904','200903','200902','200901','200812','200811','200810','200809','200808','200807','200806','200805','200804','200803','200802','200801','200712') COLLATE utf8_unicode_ci NOT NULL,
  `year` enum('2020','2019','2018','2017','2016','2015','2014','2013','2012','2011','2010','2009','2008','2007') COLLATE utf8_unicode_ci DEFAULT NULL,
  `month` enum('January','February','March','April','May','June','July','August','September','October','November','December') COLLATE utf8_unicode_ci DEFAULT NULL,
  `status` enum('past','present','future','mostrecent') COLLATE utf8_unicode_ci DEFAULT NULL,
  `numberofdays` int(11) DEFAULT NULL,
  `timepoint` int(11) DEFAULT NULL,
  PRIMARY KEY (`monthfull`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;

CREATE TABLE `pagetags` (
  `row_id` int(11) NOT NULL AUTO_INCREMENT,
  `pagename` varchar(255) COLLATE utf8_unicode_ci DEFAULT NULL,
  `language` enum('en','es','ru','de','ja','fr','zh','it','pl','pt','nl','id','tr','ar','cs','sv','fa','ko','fi','uk','hu','th','bg','vi','he','av','no','az','ro','da','el','ca','sr','hr','simple','sk','kk','lt','bs','et','hi','sl','sh','af','ms','ka','tl','lv','hy','ta','sq','eu','bi','zh-yue','eo','mk','bn','gl','ml','ur','an','be','nn','te','ak','la','arz','mr','is','mn','war','ceb','cy','oc','kn','bug','br','uz','sco','ast','lb','ky','als','zh-min-nan','si','ga','jv','sw','fy','tt','io','ckb','pa','bar','ne','ba','scn','as','am','pnb','ku','wuu','nds','yi','ia','my','bm','qu','gu','su','yo','tg','lmo','mg','fo','ilo','vo','so','li','bh','cv','pms','ps','or','gd','new','ht','ce','vec','sa','diq','hsb','sah','frr','zh-classical','nah','nds-nl','bat-smg','os','ang','hak','hif','km','wa','gv','pam','mzn','gan','nap','lad','gn','bpy','vls','fiu-vro','tk','dsb','rue','mhr','map-bms','eml','szl','se','ext','stq','cdo','bo','min','sc','co','mt','bcl','sd','ksh','frp','vep','csb','nrm','lo','ug','lij','mai','kw','pap','fur','bxr','ace','dv','ie','kv','mi','crh','cbk-zam','ay','zea','rm','ln','krc','mwl','pdc','mrj','lez','udm','rw','pcd','kab','myv','arc','jbo','xal','nov','roa-tara','sn','bjn','ig','kaa','kl','nv','nso','pag','wo','tpi','roa-rup','chr','haw','na','tet','gom','za','kbd','ab','pi','cu','zu','iu','kg','ts','koi','mdf','pih','ch','om','sm','ki','lbe','ha','pnt','tyv','rmy','srn','tw','xh','chy','ss','ltg','ee','ty','got','ny','glk','dz','ik','tum','st','to','fj','ff','sg','tn','ti','lg','ks','rn','mo','ve','cr','kr','ng','aa','cho','mus','hz','mh','kj','ho','ii') COLLATE utf8_unicode_ci DEFAULT 'en',
  `tag` varchar(255) COLLATE utf8_unicode_ci DEFAULT NULL,
  PRIMARY KEY (`row_id`),
  UNIQUE KEY `pagelangtag` (`pagename`,`language`,`tag`),
  KEY `tag` (`tag`)
) ENGINE=InnoDB AUTO_INCREMENT=92231 DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;

CREATE TABLE `queriedpages` (
  `row_id` int(11) NOT NULL AUTO_INCREMENT,
  `pagename` varchar(255) COLLATE utf8_unicode_ci DEFAULT NULL,
  `language` enum('en','es','ru','de','ja','fr','zh','it','pl','pt','nl','id','tr','ar','cs','sv','fa','ko','fi','uk','hu','th','bg','vi','he','av','no','az','ro','da','el','ca','sr','hr','simple','sk','kk','lt','bs','et','hi','sl','sh','af','ms','ka','tl','lv','hy','ta','sq','eu','bl','zh-yue','eo','mk','bn','gl','ml','ur','an','be','nn','te','ak','la','arz','mr','is','mn','war','ceb','cy','oc','kn','bug','br','uz','sco','ast','lb','ky','als','zh-min-nan','si','ga','jv','sw','fy','tt','io','ckb','pa','bar','ne','ba','scn','as','am','pnb','ku','wuu','nds','yi','ia','my','bm','qu','gu','su','yo','tg','lmo','mg','fo','ilo','vo','so','li','bh','cv','pms','ps','or','gd','new','ht','ce','vec','sa','diq','hsb','sah','frr','zh-classical','nah','nds-nl','bat-smg','os','ang','hak','hif','km','wa','gv','pam','mzn','gan','nap','lad','gn','bpy','vls','fiu-vro','tk','dsb','rue','mhr','map-bms','eml','szl','se','ext','stq','cdo','bo','min','sc','co','mt','bcl','sd','ksh','frp','vep','csb','nrm','lo','ug','lij','mai','kw','pap','fur','bxr','ace','dv','ie','kv','mi','crh','cbk-zar','ay','zea','rm','ln','krc','mwl','pdc','mrj','lez','udm','rw','pcd','kab','myv','arc','jbo','xal','nov','roa-tara','sn','bjn','ig','kaa','kl','nv','nso','pag','wo','tpi','roa-rup','chr','haw','na','tet','gom','za','kbd','ab','pi','cu','zu','iu','kg','ts','koi','mdf','pih','ch','om','sm','ki','lbe','ha','pnt','tyv','rmy','srn','tw','xh','chy','ss','ltg','ee','ty','got','ny','glk','dz','ik','tum','st','to','fj','ff','sg','tn','ti','lg','ks','rn','mo','ve','cr','kr','ng','aa','cho','mus','hz','mh','kj','ho','ii') COLLATE utf8_unicode_ci DEFAULT NULL,
  `archivalstatus` enum('partial','complete','empty','yearsonlypending','mostrecentmonthpending','filling') COLLATE utf8_unicode_ci DEFAULT NULL,
  `entrytime` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `pagelinks` enum('entered') COLLATE utf8_unicode_ci DEFAULT NULL,
  `backlinks` enum('entered') COLLATE utf8_unicode_ci DEFAULT NULL,
  PRIMARY KEY (`row_id`),
  KEY `pagelang` (`pagename`,`language`)
) ENGINE=InnoDB AUTO_INCREMENT=76421 DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;

CREATE TABLE `viewcountsbymonth_all` (
  `row_id` int(11) NOT NULL AUTO_INCREMENT,
  `pagename` varchar(255) COLLATE utf8_unicode_ci DEFAULT NULL,
  `monthfull` enum('202012','202011','202010','202009','202008','202007','202006','202005','202004','202003','202002','202001','201912','201911','201910','201909','201908','201907','201906','201905','201904','201903','201902','201901','201812','201811','201810','201809','201808','201807','201806','201805','201804','201803','201802','201801','201712','201711','201710','201709','201708','201707','201706','201705','201704','201703','201702','201701','201612','201611','201610','201609','201608','201607','201606','201605','201604','201603','201602','201601','201512','201511','201510','201509','201508','201507','201506','201505','201504','201503','201502','201501','201412','201411','201410','201409','201408','201407','201406','201405','201404','201403','201402','201401','201312','201311','201310','201309','201308','201307','201306','201305','201304','201303','201302','201301','201212','201211','201210','201209','201208','201207','201206','201205','201204','201203','201202','201201','201112','201111','201110','201109','201108','201107','201106','201105','201104','201103','201102','201101','201012','201011','201010','201009','201008','201007','201006','201005','201004','201003','201002','201001','200912','200911','200910','200909','200908','200907','200906','200905','200904','200903','200902','200901','200812','200811','200810','200809','200808','200807','200806','200805','200804','200803','200802','200801','200712') COLLATE utf8_unicode_ci DEFAULT NULL,
  `language` enum('en','es','ru','de','ja','fr','zh','it','pl','pt','nl','id','tr','ar','cs','sv','fa','ko','fi','uk','hu','th','bg','vi','he','av','no','az','ro','da','el','ca','sr','hr','simple','sk','kk','lt','bs','et','hi','sl','sh','af','ms','ka','tl','lv','hy','ta','sq','eu','bi','zh-yue','eo','mk','bn','gl','ml','ur','an','be','nn','te','ak','la','arz','mr','is','mn','war','ceb','cy','oc','kn','bug','br','uz','sco','ast','lb','ky','als','zh-min-nan','si','ga','jv','sw','fy','tt','io','ckb','pa','bar','ne','ba','scn','as','am','pnb','ku','wuu','nds','yi','ia','my','bm','qu','gu','su','yo','tg','lmo','mg','fo','ilo','vo','so','li','bh','cv','pms','ps','or','gd','new','ht','ce','vec','sa','diq','hsb','sah','frr','zh-classical','nah','nds-nl','bat-smg','os','ang','hak','hif','km','wa','gv','pam','mzn','gan','nap','lad','gn','bpy','vls','fiu-vro','tk','dsb','rue','mhr','map-bms','eml','szl','se','ext','stq','cdo','bo','min','sc','co','mt','bcl','sd','ksh','frp','vep','csb','nrm','lo','ug','lij','mai','kw','pap','fur','bxr','ace','dv','ie','kv','mi','crh','cbk-zam','ay','zea','rm','ln','krc','mwl','pdc','mrj','lez','udm','rw','pcd','kab','myv','arc','jbo','xal','nov','roa-tara','sn','bjn','ig','kaa','kl','nv','nso','pag','wo','tpi','roa-rup','chr','haw','na','tet','gom','za','kbd','ab','pi','cu','zu','iu','kg','ts','koi','mdf','pih','ch','om','sm','ki','lbe','ha','pnt','tyv','rmy','srn','tw','xh','chy','ss','ltg','ee','ty','got','ny','glk','dz','ik','tum','st','to','fj','ff','sg','tn','ti','lg','ks','rn','mo','ve','cr','kr','ng','aa','cho','mus','hz','mh','kj','ho','ii') COLLATE utf8_unicode_ci DEFAULT 'en',
  `drilldown` enum('desktop','mobile-web','mobile-app','desktop-spider','mobile-web-spider','cumulative-facebook-shares','referrer:Wikipedia','referrer:other-empty','referrer:other-external','referrer:other-internal','referrer:other-other','referrer:other-search','referrer:other-bing','referrer:other-facebook','referrer:other-google','referrer:other-yahoo','referrer:other-twitter','referrer:other-wikipedia','referrer:other') COLLATE utf8_unicode_ci DEFAULT NULL,
  `viewcount` int(11) DEFAULT NULL,
  `querytime` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
  PRIMARY KEY (`row_id`),
  UNIQUE KEY `pagemonthlangdrilldown` (`pagename`,`monthfull`,`language`,`drilldown`)
) ENGINE=InnoDB AUTO_INCREMENT=18409693 DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;

CREATE TABLE `viewcountsbyyear_all` (
  `row_id` int(11) NOT NULL AUTO_INCREMENT,
  `pagename` varchar(255) COLLATE utf8_unicode_ci DEFAULT NULL,
  `year` enum('2020','2019','2018','2017','2016','2015','2014','2013','2012','2011','2010','2009','2008','2007') COLLATE utf8_unicode_ci DEFAULT NULL,
  `language` enum('en','es','ru','de','ja','fr','zh','it','pl','pt','nl','id','tr','ar','cs','sv','fa','ko','fi','uk','hu','th','bg','vi','he','av','no','az','ro','da','el','ca','sr','hr','simple','sk','kk','lt','bs','et','hi','sl','sh','af','ms','ka','tl','lv','hy','ta','sq','eu','bl','zh-yue','eo','mk','bn','gl','ml','ur','an','be','nn','te','ak','la','arz','mr','is','mn','war','ceb','cy','oc','kn','bug','br','uz','sco','ast','lb','ky','als','zh-min-nan','si','ga','jv','sw','fy','tt','io','ckb','pa','bar','ne','ba','scn','as','am','pnb','ku','wuu','nds','yi','ia','my','bm','qu','gu','su','yo','tg','lmo','mg','fo','ilo','vo','so','li','bh','cv','pms','ps','or','gd','new','ht','ce','vec','sa','diq','hsb','sah','frr','zh-classical','nah','nds-nl','bat-smg','os','ang','hak','hif','km','wa','gv','pam','mzn','gan','nap','lad','gn','bpy','vls','fiu-vro','tk','dsb','rue','mhr','map-bms','eml','szl','se','ext','stq','cdo','bo','min','sc','co','mt','bcl','sd','ksh','frp','vep','csb','nrm','lo','ug','lij','mai','kw','pap','fur','bxr','ace','dv','ie','kv','mi','crh','cbk-zar','ay','zea','rm','ln','krc','mwl','pdc','mrj','lez','udm','rw','pcd','kab','myv','arc','jbo','xal','nov','roa-tara','sn','bjn','ig','kaa','kl','nv','nso','pag','wo','tpi','roa-rup','chr','haw','na','tet','gom','za','kbd','ab','pi','cu','zu','iu','kg','ts','koi','mdf','pih','ch','om','sm','ki','lbe','ha','pnt','tyv','rmy','srn','tw','xh','chy','ss','ltg','ee','ty','got','ny','glk','dz','ik','tum','st','to','fj','ff','sg','tn','ti','lg','ks','rn','mo','ve','cr','kr','ng','aa','cho','mus','hz','mh','kj','ho','ii') COLLATE utf8_unicode_ci DEFAULT 'en',
  `drilldown` enum('desktop','mobile-web','mobile-app','desktop-spider','mobile-web-spider','cumulative-facebook-shares','referrer:Wikipedia','referrer:other-empty','referrer:other-external','referrer:other-internal','referrer:other-other','referrer:other-search','referrer:other-bing','referrer:other-facebook','referrer:other-google','referrer:other-yahoo','referrer:other-twitter','referrer:other-wikipedia','referrer:other') COLLATE utf8_unicode_ci DEFAULT NULL,
  `viewcount` int(11) DEFAULT NULL,
  PRIMARY KEY (`row_id`),
  UNIQUE KEY `pageyearlangdrilldown` (`pagename`,`year`,`language`,`drilldown`)
) ENGINE=InnoDB AUTO_INCREMENT=2939714 DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;

CREATE TABLE `viewquerylog` (
  `row_id` int(11) NOT NULL AUTO_INCREMENT,
  `pagename` varchar(255) COLLATE utf8_unicode_ci DEFAULT NULL,
  `monthfull` enum('201612','201611','201610','201609','201608','201607','201606','201605','201604','201603','201602','201601','201512','201511','201510','201509','201508','201507','201506','201505','201504','201503','201502','201501','201412','201411','201410','201409','201408','201407','201406','201405','201404','201403','201402','201401','201312','201311','201310','201309','201308','201307','201306','201305','201304','201303','201302','201301','201212','201211','201210','201209','201208','201207','201206','201205','201204','201203','201202','201201','201112','201111','201110','201109','201108','201107','201106','201105','201104','201103','201102','201101','201012','201011','201010','201009','201008','201007','201006','201005','201004','201003','201002','201001','200912','200911','200910','200909','200908','200907','200906','200905','200904','200903','200902','200901','200812','200811','200810','200809','200808','200807','200806','200805','200804','200803','200802','200801','200712') COLLATE utf8_unicode_ci DEFAULT NULL,
  `language` enum('en','de','es','fr','it','nl','pl','ru','sv','pt','zh','simple','hi','zh-classical','no','fi','ja') COLLATE utf8_unicode_ci DEFAULT NULL,
  `querytime` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
  PRIMARY KEY (`row_id`)
) ENGINE=InnoDB AUTO_INCREMENT=92794 DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;

CREATE TABLE `viewquerylogbyyear` (
  `row_id` int(11) NOT NULL AUTO_INCREMENT,
  `pagename` varchar(255) COLLATE utf8_unicode_ci DEFAULT NULL,
  `year` enum('2007','2008','2009','2010','2011','2012','2013','2014','2015','2016','2017') COLLATE utf8_unicode_ci DEFAULT NULL,
  `language` enum('en','de','es','fr','it','nl','pl','ru','sv','pt','zh','simple','hi','zh-classical','no','fi','ja') COLLATE utf8_unicode_ci DEFAULT NULL,
  `querytime` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
  PRIMARY KEY (`row_id`)
) ENGINE=InnoDB AUTO_INCREMENT=37439 DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;

CREATE TABLE `wantedviewcountsbymonth` (
  `row_id` int(11) NOT NULL AUTO_INCREMENT,
  `pagename` varchar(255) COLLATE utf8_unicode_ci DEFAULT NULL,
  `monthfull` enum('202012','202011','202010','202009','202008','202007','202006','202005','202004','202003','202002','202001','201912','201911','201910','201909','201908','201907','201906','201905','201904','201903','201902','201901','201812','201811','201810','201809','201808','201807','201806','201805','201804','201803','201802','201801','201712','201711','201710','201709','201708','201707','201706','201705','201704','201703','201702','201701','201612','201611','201610','201609','201608','201607','201606','201605','201604','201603','201602','201601','201512','201511','201510','201509','201508','201507','201506','201505','201504','201503','201502','201501','201412','201411','201410','201409','201408','201407','201406','201405','201404','201403','201402','201401','201312','201311','201310','201309','201308','201307','201306','201305','201304','201303','201302','201301','201212','201211','201210','201209','201208','201207','201206','201205','201204','201203','201202','201201','201112','201111','201110','201109','201108','201107','201106','201105','201104','201103','201102','201101','201012','201011','201010','201009','201008','201007','201006','201005','201004','201003','201002','201001','200912','200911','200910','200909','200908','200907','200906','200905','200904','200903','200902','200901','200812','200811','200810','200809','200808','200807','200806','200805','200804','200803','200802','200801','200712') COLLATE utf8_unicode_ci DEFAULT NULL,
  `language` enum('en','es','ru','de','ja','fr','zh','it','pl','pt','nl','id','tr','ar','cs','sv','fa','ko','fi','uk','hu','th','bg','vi','he','av','no','az','ro','da','el','ca','sr','hr','simple','sk','kk','lt','bs','et','hi','sl','sh','af','ms','ka','tl','lv','hy','ta','sq','eu','bl','zh-yue','eo','mk','bn','gl','ml','ur','an','be','nn','te','ak','la','arz','mr','is','mn','war','ceb','cy','oc','kn','bug','br','uz','sco','ast','lb','ky','als','zh-min-nan','si','ga','jv','sw','fy','tt','io','ckb','pa','bar','ne','ba','scn','as','am','pnb','ku','wuu','nds','yi','ia','my','bm','qu','gu','su','yo','tg','lmo','mg','fo','ilo','vo','so','li','bh','cv','pms','ps','or','gd','new','ht','ce','vec','sa','diq','hsb','sah','frr','zh-classical','nah','nds-nl','bat-smg','os','ang','hak','hif','km','wa','gv','pam','mzn','gan','nap','lad','gn','bpy','vls','fiu-vro','tk','dsb','rue','mhr','map-bms','eml','szl','se','ext','stq','cdo','bo','min','sc','co','mt','bcl','sd','ksh','frp','vep','csb','nrm','lo','ug','lij','mai','kw','pap','fur','bxr','ace','dv','ie','kv','mi','crh','cbk-zar','ay','zea','rm','ln','krc','mwl','pdc','mrj','lez','udm','rw','pcd','kab','myv','arc','jbo','xal','nov','roa-tara','sn','bjn','ig','kaa','kl','nv','nso','pag','wo','tpi','roa-rup','chr','haw','na','tet','gom','za','kbd','ab','pi','cu','zu','iu','kg','ts','koi','mdf','pih','ch','om','sm','ki','lbe','ha','pnt','tyv','rmy','srn','tw','xh','chy','ss','ltg','ee','ty','got','ny','glk','dz','ik','tum','st','to','fj','ff','sg','tn','ti','lg','ks','rn','mo','ve','cr','kr','ng','aa','cho','mus','hz','mh','kj','ho','ii') COLLATE utf8_unicode_ci DEFAULT NULL,
  `status` enum('wanted','working') COLLATE utf8_unicode_ci DEFAULT NULL,
  `drilldown` enum('desktop','mobile-web','mobile-app','desktop-spider','mobile-web-spider','cumulative-facebook-shares','referrer:Wikipedia','referrer:other-empty','referrer:other-external','referrer:other-internal','referrer:other-other','referrer:other-search','referrer:other-bing','referrer:other-facebook','referrer:other-google','referrer:other-yahoo','referrer:other-twitter','referrer:other-wikipedia','referrer:other') COLLATE utf8_unicode_ci DEFAULT NULL,
  PRIMARY KEY (`row_id`),
  UNIQUE KEY `pagemonthlangdrilldown` (`pagename`,`monthfull`,`language`,`drilldown`)
) ENGINE=InnoDB AUTO_INCREMENT=7613080 DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;

CREATE TABLE `years` (
  `year` enum('2020','2019','2018','2017','2016','2015','2014','2013','2012','2011','2010','2009','2008','2007') COLLATE utf8_unicode_ci NOT NULL,
  `status` enum('pastincomplete','past','mostrecent','present','future') COLLATE utf8_unicode_ci DEFAULT NULL,
  PRIMARY KEY (`year`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci

