import subprocess
import re

def main():

    n_var = int(input("range della variabile: "))
    run_bash = input("scrivi il comando che vuoi eseguire e metti tra [] la variabile: ")
    run_bash = re.split(r'[\[\]]',run_bash)

    for var in range(n_var):
        subprocess.run([f"python {run_bash[0]}{var + 1}{run_bash[2]}"], shell = True)


main()
