import numpy as np
import matplotlib.pyplot as plt

# 定義時間區間
t1 = np.linspace(-1, 0, 100)  
t2 = np.linspace(0, 5, 100)   
t3 = np.linspace(5, 10, 100)  
t4 = np.linspace(10, 12, 100) 

# 定義 v_c(t) 的分段函數
v1 = np.zeros_like(t1)          
v2 = (3/8) * t2**2                  
v3 = (75/8) - (10/4) * (t3 - 5)     
v4 = np.full_like(t4, -25/8)        

plt.plot(t1, v1, '*', color='blue', label="t <= 0")   
plt.plot(t2, v2, '*', color='orange', label="0 <= t <= 5") 
plt.plot(t3, v3, '*', color='green', label="5 <= t <= 10")
plt.plot(t4, v4, '*', color='red', label="10 <= t <= 12")  

plt.xlabel("t")
plt.ylabel("v_c(t)")
plt.title("Plot of v_c(t) with Different Colors")
plt.axhline(0, color='black', linewidth=0.8, linestyle='--')  
plt.axvline(0, color='black', linewidth=0.8, linestyle='--') 
plt.grid()
plt.legend()
plt.show()