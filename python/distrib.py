#!/usr/bin/python3

import argparse
import pandas as pd
import numpy as np
import matplotlib
# Force matplotlib to not use any Xwindows backend.
matplotlib.use('Agg')
import matplotlib.pyplot as plt
import matplotlib.font_manager as font_manager

from graph import get_df

def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("csv", type=str, help="the CSV file to graph")
    parser.add_argument("output", type=str, help="the output file")
    parser.add_argument("--log10", action="store_true",
            help="plot log10 of pageviews")
    parser.add_argument("--plot_kind", type=str, default="line",
            help="plot kind, accepts line, bar, barh, etc.; defaults to line")
    parser.add_argument("--top", type=int, default=0, metavar='N',
            help="if this is a positive integer, only the top " +
            "N columns are plotted; does not include a Total column")
    parser.add_argument("--label", action="store_true",
            help="label the pages at the bottom of the plot")
    parser.add_argument("--label_max_len", type=int, default=10,
            metavar="N", help="maximum length in characters of each " +
            "label; only used if --label is given; default N=10")
    parser.add_argument("--font", type=str, help="optional font " +
            "path to use; only in effect when --label is given")
    args = parser.parse_args()

    if args.top > 0:
        # Add one to top because get_df includes a "Total"
        df = get_df(args.csv, args.top + 1)
    else:
        df = get_df(args.csv)
    df = df.sum().sort_values(ascending=False)
    del df['Total']

    if args.log10:
        df = np.log10(df)

    df.plot(kind=args.plot_kind)
    if args.label:
        labels = trim_labels(df.index, max_len=args.label_max_len)
        if args.font:
            plt.xticks(np.arange(len(df)), labels, rotation='vertical',
                    fontproperties=font_manager.FontProperties(fname=args.font))
        else:
            plt.xticks(np.arange(len(df)), labels, rotation='vertical')
        plt.tight_layout()
    else:
        plt.xticks([])
    plt.savefig(args.output)
    plt.clf()
    plt.close()

def trim_labels(labels, max_len=10):
    '''
    Take a list of strings and trim each so that each is at most max_len
    characters long. Return a new list of strings containing the labels in the
    same order.
    '''
    def rm_views_of_page(s):
        if s.startswith("Views of page "):
            s = s[len("Views of page "):]
        return s
    def trim(s, max_len=max_len, trail="…"):
        if len(s) > max_len:
            sli = max_len - len(trail)
            if sli > 0:
                s = s[:sli] + trail
            else:
                s = trail
        return s
    def multi_trim(s):
        '''
        "John F. Kennedy"
            => ['John', 'F.', 'Kennedy']
            => ['Joh', 'F.', 'Ken'] (map)
            => "JohF.Ken"
        '''
        s_lst = s.split()
        u_lst = list(map(lambda x: x[:1].upper() + x[1:], s_lst))
        t_lst = map(lambda x: trim(x, max_len=max_len//len(u_lst), trail=""),
                u_lst)
        return "".join(t_lst)
    return list(map(lambda x: multi_trim(rm_views_of_page(x)),
        labels))

if __name__ == "__main__":
    main()
