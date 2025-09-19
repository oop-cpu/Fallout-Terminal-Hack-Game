import subprocess
import time
subprocess.run(["git add ."], shell=True)
time.sleep(1)
subprocess.run(["git commit -m \"lazy commit\""], shell=True)