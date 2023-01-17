import argparse
import pandas as pd

def rqs_vs_qs(df, o):
    df.columns = ['n', 'rt_qs', 'rt_rqs', 'c_qs', 'c_rqs', 'dst_qs', 'dst_rqs']
    if len(df.index) < 1000 : # For n = 10^5
        with open(o, 'a') as f:
            f.write('\n')
            f.write(df.mean().to_string())
    else : # For n \in {10^2, 10^3, 10^4}
        with open(o, 'a') as f:
            for i in range(0, len(df.index) // 2000) :
                f.write('\n')
                f.write(df.iloc[2000 * i : 2000 * (i + 1)].mean().to_string())

def rqs_vs_ms(df, o):
    df.columns = ['n', 'rt_qs', 'rt_ms', 'c_qs', 'c_ms']
    df['ms_win'] = (df['rt_ms'] < df['rt_qs'])
    with open(o, 'a') as f:    
        for i in range(0, len(df.index) // 2000) :
            f.write('\nMean\n')
            f.write(df.iloc[2000 * i : 2000 * (i + 1)].mean().to_string())
            f.write('\nSum\n')
            f.write(df.iloc[2000 * i : 2000 * (i + 1)].sum().to_string())

def rqs(df, o):
    df.columns = ['n', 'rt_qs', 'c_qs']
    p_vals = [5, 10, 20, 30, 50, 100]
    with open(o, 'a') as f:
        for i in range(0, len(df.index) // 2000) :
            f.write('\n')
            rt_mean = df['rt_qs'].iloc[2000 * i : 2000 * (i + 1)].mean()
            f.write(df.iloc[2000 * i : 2000 * (i + 1)].mean().to_string())
            for p in p_vals:
                f.write('\n' + str(p) + ' : ' + str((df['rt_qs'].iloc[2000 * i : 2000 * (i + 1)] > rt_mean * (1 + p/100)).sum()))



parser = argparse.ArgumentParser()
parser.add_argument('-f', help = 'Input File name of the CSV in which data resides', default = None)
parser.add_argument('-o', help = 'Output File in which data is to be printed', default = None)
parser.add_argument('-q', help = 'Question number to be done', default = 1, type = int)
args = parser.parse_args()

funcs = [None, rqs_vs_qs, rqs_vs_ms, rqs]
q, f, o = args.q, args.f, args.o
df = pd.read_csv(f)

if 0 < q and q < 4:
    funcs[q](df, o)
else:
    print("Incorrect Question Number:", q)