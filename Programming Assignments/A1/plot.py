# For the optional part of the assignment
import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt

df = pd.read_csv('./dataQ3.csv')

count = len(df.index) // 5
fig, ax = plt.subplots(figsize = (10, 5))
ax.set_xlim(0, 5)
ax.set_xlabel("Runtime / Average Runtime")
mean = df['rt_qs'].iloc[0 : count].mean()
sns.histplot(df['rt_qs'].iloc[0 : count] / mean, kde=True, label="10^2", element='step', ax = ax)
plt.legend()
plt.savefig('n2_reduced_axis')
plt.show()

fig, ax = plt.subplots()
ax.set_xlabel("Runtime / Average Runtime")
sns.histplot(df['rt_qs'].iloc[0 : count] / mean, kde=True, label="10^2", element='step', ax = ax)
plt.legend()
plt.savefig('n2_complete_axis')
plt.show()

for i in range(1, 5):
    mean = df['rt_qs'].iloc[count * i : count * (i + 1)].mean()
    ax = sns.histplot(df['rt_qs'].iloc[count * i : count * (i + 1)] / mean, kde=True, label="10^" + str(i+2), element='step')
    ax.set(xlabel = "Runtime / Average Runtime")
plt.legend()
plt.savefig('n_with_line')
plt.show()

for i in range(1, 5):
    mean = df['rt_qs'].iloc[count * i : count * (i + 1)].mean()
    ax = sns.distplot(df['rt_qs'].iloc[count * i : count * (i + 1)] / mean, norm_hist=False, kde=False, label="10^" + str(i+2))
    ax.set(xlabel = "Runtime / Average Runtime")
plt.legend()
plt.savefig('n_without_line')
plt.show()