import subprocess
import time
subprocess.run(["git add ."], shell=True)
time.sleep(1)
subprocess.run(["git commit -m \"lazy commit\""], shell=True)

file_path = "/home/oop-cpu/gitKey.dat"

with open(file_path, 'r') as file:
    content = file.read()
    print(content)
