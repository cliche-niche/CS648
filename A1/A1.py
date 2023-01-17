import argparse
import pandas as pd

def rqs_vs_qs(df, o):
    df.columns = ['n','rt_qs','rt_rqs','c_qs','c_rqs','dst_qs','dst_rqs']
    if len(df.index) < 1000 : # For n = 10^5
        with open(o, 'a') as f:
            f.write('\n')
            f.write(df.mean().to_string())
    else : # For n \in {10^2, 10^3, 10^4}
        with open(o, 'a') as f:
            f.write('\n')
            f.write(df.iloc[0:2000].mean().to_string())
            f.write('\n')
            f.write(df.iloc[2000:4000].mean().to_string())
            f.write('\n')
            f.write(df.iloc[4000:6000].mean().to_string())

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
            rt_mean = df.iloc[2000 * i : 2000 * (i + 1)]
            f.write(df.iloc[2000 * i : 2000 * (i + 1)].mean().to_string())
            for p in p_vals:
                f.write('\n' + str(p) + ' : ' + str((df['rt_qs'] < rt_mean * (1 + p/100)).sum()))


    # n_vals = [100, 1_000, 10_000, 100_000, 1000_000]
    # count = {}                  # Count of data
    # rt_qs = {}                  # Run time
    # c_qs = {}                   # Comparisons
    # exceed = {}                 # Run time exceed count

    # for index, row in df.iterrows():
    #     n = row[0]
    #     if count.get(n, 0):
    #         rt_qs[n]    += int(row[1])
    #         c_qs[n]     += int(row[2])
    #         count[n]    += 1
    #     else:
    #         rt_qs[n]    = int(row[1])
    #         c_qs[n]     = int(row[2])
    #         count[n]    = 1
    #         exceed[n]   = {}

    # for n in n_vals:
    #     if count.get(n, 0):
    #         for p in p_vals:
    #             exceed[n][p].set(n, 0)
    #             rt_qs[n] /= count[n]
    
    # for index, row in df.iterrows():
    #     n = row[1]
    #     for p in p_vals:
    #         exceed[n][p] += (rt_qs[n] * (1 + p/100) < row[1])
    
    # with open(o, 'a') as f:
    #     f.write("\nn,rt_qs,5,10,20,30,50,100\n")
    #     for n in n_vals:
    #         if count.get(n, 0):
    #             c = count[n]
    #             f.write(str(n) + "," + str(int(rt_qs[n] / c)) + ",")
    #             for p in p_vals:
    #                 if exceed[n].get(p, 0):
    #                     f.write(str(exceed[n][p]) + ",")
    #             f.write('\n')


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