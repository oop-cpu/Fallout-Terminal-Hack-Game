import subprocess
import time

            #replace with your own path
file_path = "/home/oop-cpu/gitKey.dat"
#     FILE FORMAT FOR KEY
#     -------------------
#     <USERNAME>
#     <KEY/PASSWORD>

with open(file_path, 'r') as file:
    for line in file:
        print(line.strip())
subprocess.run(["git add ."], shell=True)
time.sleep(1)
subprocess.run(["git commit -m \"lazy commit\""], shell=True)
time.sleep(1)
subprocess.run(["git push"], shell=True)