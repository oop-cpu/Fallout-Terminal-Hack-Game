import subprocess
subprocess.run(["git add ."], shell=True)
subprocess.run(["git commit -m \"lazy commit\""], shell=True)