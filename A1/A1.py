import argparse
import pandas as pd

def rqs_vs_qs(df, o):
    n_vals = [100, 1_000, 10_000, 100_000, 1000_000]
    count = {}                # Count of data
    rt_rqs, rt_qs = {}, {}      # Run time
    c_rqs, c_qs = {}, {}        # Comparisons
    dst_rqs, dst_qs = {}, {}    # Double Sort time

    for index, row in df.iterrows():
        n = row[0]
        if count.get(n, 0) != 0:
            rt_qs[n]    += int(row[1])
            rt_rqs[n]   += int(row[2])
            c_qs[n]     += int(row[3])
            c_rqs[n]    += int(row[4])
            dst_qs[n]   += int(row[5])
            dst_rqs[n]  += int(row[6])
            count[n]    += 1
        else:
            rt_qs[n]    = int(row[1])
            rt_rqs[n]   = int(row[2])
            c_qs[n]     = int(row[3])
            c_rqs[n]    = int(row[4])
            dst_qs[n]   = int(row[5])
            dst_rqs[n]  = int(row[6])
            count[n]    = 1
    
    with open(o, 'a') as f:
        f.write("n,rt_qs,rt_rqs,c_qs,c_rqs,dst_qs,dst_rqs,count\n")
        for n in n_vals:
            if count.get(n, 0) == 0:
                continue
            c = count[n]
            f.write(str(n) + "," + str(int(rt_qs[n]/c)) + "," + str(int(rt_rqs[n]/c)) + ",")
            f.write(str(int(c_qs[n]/c)) + "," + str(int(c_rqs[n]/c)) + ",")
            f.write(str(int(dst_qs[n]/c)) + "," + str(int(dst_rqs[n]/c)) + "," + str(c) + "\n")


def rqs_vs_ms(df, o):
    n_vals = [100, 1_000, 10_000, 100_000, 1000_000]
    count = {}                  # Count of data
    rt_ms, rt_qs = {}, {}       # Run time
    c_ms, c_qs = {}, {}         # Comparisons
    ms_won = {}                 # Count of MS outperforming RQS/QS

    for index, row in df.iterrows():
        n = row[0]
        if count.get(n, 0) != 0:
            rt_qs[n]    += int(row[1])
            rt_ms[n]    += int(row[2])
            c_qs[n]     += int(row[3])
            c_ms[n]     += int(row[4])
            ms_won[n]   += (int(row[2]) < int(row[1]))
            count[n]    += 1
        else:
            rt_qs[n]    = int(row[1])
            rt_ms[n]    = int(row[2])
            c_qs[n]     = int(row[3])
            c_ms[n]     = int(row[4])
            ms_won[n]   = (int(row[2]) < int(row[1]))
            count[n]    = 1
    
    with open(o, 'a') as f:
        f.write("n,rt_qs,rt_ms,c_qs,c_ms,ms_won,count\n")
        for n in n_vals:
            if count.get(n, 0) == 0:
                continue
            c = count[n]
            f.write(str(n) + "," + str(int(rt_qs[n]/c)) + "," + str(int(rt_ms[n]/c)) + ",")
            f.write(str(int(c_qs[n]/c)) + "," + str(int(c_ms[n]/c)) + ",")
            f.write(str(ms_won[n]) + "," + str(c) + "\n")


def rqs(df, o):
    pass


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