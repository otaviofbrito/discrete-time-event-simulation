import subprocess
import webbrowser
import os
from report import *

report_path = 'report.html'


def run_simulation(seed, l, m, sim_time):
    cmd = f'c_project/main {seed} {l} {m} {sim_time}'
    subprocess.run(cmd, shell=True)


def open_report():
    if os.path.exists(report_path):
        webbrowser.open(f'{report_path}')
    else:
        print(f"O arquivo {report_path} não foi encontrado.")


def main():
    num_simulations = int(input("Número de simulações: "))

    for i in range(num_simulations):
        seed = input(f"\nSeed aleatória[{i+1}]: ")
        tx_chegada = input(f"Taxa média de chegada[{i+1}]: ")
        tx_saida = input(f"Taxa média de atendimento[{i+1}]: ")
        tempo = input(f"Tempo de simulação[{i+1}]: ")
        run_simulation(int(seed), float(tx_chegada),
                       float(tx_saida), int(tempo))

    generate_report()
    open_report()


if __name__ == '__main__':
    main()
