import matplotlib.pyplot as plt
import pandas as pd
import os
import time

df = pd.read_csv('results.csv')

plt.figure(figsize=(10, 6))
plt.barh(df['algorithm'], df['time_s'], color='skyblue')
plt.xlabel('Time (seconds)')
plt.title('Comparison of Sorting Algorithms')
plt.grid(True)
plt.tight_layout()
save_folder = "./prezentare/img"
timestamp = time.strftime("%Y%m%d_%H%M%S")
filename = os.path.join(save_folder, f"img_{timestamp}.png")
plt.savefig(filename)
