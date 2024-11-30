import numpy as np

A = np.array([
    [2, 3, -1],
    [1, -2, 3],
    [4, 1, -2] 
])

B = np.array([5, 6, 0])
solution = np.linalg.solve(A, B)

print(f"答案：a = {solution[0]}, b = {solution[1]}, c = {solution[2]}")