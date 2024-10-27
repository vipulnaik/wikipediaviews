MYSQL_ARGS=
DATABASE=wikipediaviews

.PHONY: init
init:
	mysql $(MYSQL_ARGS) -e "create database if not exists $(DATABASE);"

.PHONY: fetch_table_sorting
fetch_table_sorting:
	curl -Lo style/jquery-3.7.1.min.js \
		'https://code.jquery.com/jquery-3.7.1.min.js'
	curl -Lo style/jquery.tablesorter.js \
		'https://github.com/christianbach/tablesorter/raw/master/jquery.tablesorter.js'
	curl -Lo style/style.css \
		'https://raw.githubusercontent.com/christianbach/tablesorter/master/themes/blue/style.css'
	curl -Lo style/bg.gif \
		'https://github.com/christianbach/tablesorter/raw/master/themes/blue/bg.gif'
	curl -Lo style/asc.gif \
		'https://github.com/christianbach/tablesorter/raw/master/themes/blue/asc.gif'
	curl -Lo style/desc.gif \
		'https://github.com/christianbach/tablesorter/raw/master/themes/blue/desc.gif'

.PHONY: clean_table_sorting
clean_table_sorting:
	rm -f style/jquery-*.min.js
	rm -f style/jquery.tablesorter.js
	rm -f style/style.css
	rm -f style/bg.gif
	rm -f style/asc.gif
	rm -f style/desc.gif

.PHONY: fetch_anchorjs
fetch_anchorjs:
	curl -Lo style/anchor.min.js \
		'https://raw.githubusercontent.com/bryanbraun/anchorjs/master/anchor.min.js'

.PHONY: clean_anchorjs
clean_anchorjs:
	rm -f style/anchor.min.js
