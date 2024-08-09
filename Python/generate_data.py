import random
import string
import os

memory = 1024*1024*100
os.makedirs(os.path.join("..", "data"), exist_ok=True)
data = "".join(random.choice(string.ascii_letters) for i in range(memory))
with open(os.path.join("..", "data", "100MB.txt"), "w") as f:
    f.write(data)

print("Data generated")
