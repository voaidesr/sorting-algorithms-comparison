import matplotlib.pyplot as plt
import pandas as pd

df = pd.read_csv('results.csv')

plt.figure(figsize=(10, 6))
plt.barh(df['algorithm'], df['time_s'], color='skyblue')
plt.xlabel('Time (seconds)')
plt.title('Comparison of Sorting Algorithms')
plt.grid(True)
plt.tight_layout()
plt.show()
