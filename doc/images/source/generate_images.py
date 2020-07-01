#! /usr/bin/env python3
import os
import subprocess
from glob import glob


def generate_pngs():
    for input_file in glob('*.dot'):
        output_format = 'png'
        base_name = os.path.splitext(input_file)[0]
        output_file = os.path.join('..', base_name + '.' + output_format)

        command = f'dot -T{output_format} {input_file} -o {output_file}'
        subprocess.run(command, shell=True, check=True)
        print(f'regenerated {output_file}')


if __name__ == '__main__':
    generate_pngs()
