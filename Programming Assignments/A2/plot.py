# For the optional part of the assignment
import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt


n_vals = [1000, 10000, 100000, 1000000]

for i in [1, 2] :
    df1 = pd.read_csv('./DataQ' + str(i) + '.csv')

    df2 = pd.DataFrame()
    df2['n'] = [1000, 10000, 100000, 1000000]

    means = []
    twenty_excesses = []
    twenty_under = []
    thirty_excesses = []
    fifty_excesses = []
    hundred_excesses = []

    for val in n_vals:
        df_tmp = df1[df1['n'] == val]
        mean = df_tmp['max_load'].mean()
        means.append(mean)
        twenty_excesses.append(df_tmp[df_tmp['max_load'] > mean * (1.20)]['max_load'].sum())
        thirty_excesses.append(df_tmp[df_tmp['max_load'] > mean * (1.30)]['max_load'].sum())
        fifty_excesses.append(df_tmp[df_tmp['max_load'] > mean * (1.50)]['max_load'].sum())
        hundred_excesses.append(df_tmp[df_tmp['max_load'] > mean * (2)]['max_load'].sum())
        twenty_under.append(df_tmp[df_tmp['max_load'] < mean * (0.8)]['max_load'].sum())

        hist = df_tmp.hist(column='max_load', bins=[0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10], color='lightcoral')
        plt.xlabel('Load')
        plt.ylabel('Number of Bins')
        plt.title('n = ' + str(val) + ' | ' + ('Simple Algorithm' if i == 1 else 'Two Choice Algorithm'))
        plt.axvline(x = mean, color = 'firebrick', linestyle='dashed', label = 'axvline - full height')
        # plt.text(mean - 0.05, -100, '\u03BC')
        plt.axvline(x = 1.2*mean, color = 'firebrick', linestyle='dashed', label = 'axvline - full height')
        # plt.text(1.2*mean - 0.05, -100, '1.2\u03BC')
        # plt.axvline(x = 1.3*mean, color = 'firebrick', linestyle='dashed', label = 'axvline - full height')
        # plt.axvline(x = 1.5*mean, color = 'firebrick', linestyle='dashed', label = 'axvline - full height')
        # plt.axvline(x = 2.0*mean, color = 'firebrick', linestyle='dashed', label = 'axvline - full height')
        plt.grid(False)
        plt.savefig('n = ' + str(val) + ' ' + ('Simple Algorithm' if i == 1 else 'Two Choice Algorithm') + '.png')
        # plt.show()

    df2['mean'] = means
    df2['twenty'] = twenty_excesses
    df2['thirty'] = thirty_excesses
    df2['fifty'] = fifty_excesses
    df2['hundred'] = hundred_excesses
    df2['twenty_under'] = twenty_under

    print(df2)