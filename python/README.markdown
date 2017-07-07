# Plotting code for Wikipedia Views

    $ python3 graph.py --help
    usage: graph.py [-h] [--log10] [--vertical_lines] [--plot_kind PLOT_KIND]
                    [--top TOP] [--label] [--similarity_matrix] [--subtract_avg]
                    csv output

    positional arguments:
      csv                   the CSV file to graph
      output                the output file

    optional arguments:
      -h, --help            show this help message and exit
      --log10               plot log10 of pageviews
      --vertical_lines      show vertical transition lines in graph
      --plot_kind PLOT_KIND
                            plot kind, accepts line, bar, barh, etc.; defaults to
                            line.
      --top TOP             if this is a positive integer, only the top TOP
                            columns are plotted
      --label               label the pages at the bottom of the plot
      --similarity_matrix   print the similarity matrix of the columns in the CSV
      --subtract_avg        subtract the average value of each column before
                            producing a similarity matrix; you must select
                            --similarity_matrix
