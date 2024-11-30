import numpy as np
import matplotlib.pyplot as plt

# 定義角度範圍 (0 到 2π)
theta = np.linspace(0, 2 * np.pi, 500)

x = np.cos(theta) 
y = np.sin(theta) 
plt.plot(x, y, label="Circle (r=1)")

plt.axhline(0, color='black', linewidth=0.8, linestyle='--')  
plt.axvline(0, color='black', linewidth=0.8, linestyle='--') 
plt.gca().set_aspect('equal', adjustable='box')  # 確保 x 和 y 軸比例相等
plt.title("Circle with Radius 1")
plt.xlabel("X")
plt.ylabel("Y")
plt.grid()
plt.legend()
plt.show()
