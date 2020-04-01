import os
import subprocess
import hashlib


def run(command):
    print(command)
    subprocess.run(" ".join(command), shell=True, check=True)


def write_file(file_name, text):
    with open(file_name, 'w') as output:
        output.write(text)


def read_file(file_name):
    with open(file_name) as input:
        text = input.read()
    return text

def get_file_name(path):
    return os.path.split(path)[1]

pushstack = list()


def pushdir(dirname):
    global pushstack
    pushstack.append(os.getcwd())
    os.chdir(dirname)


def popdir():
    global pushstack
    os.chdir(pushstack.pop())


def use_directory(dir):
    class PushPopDirectory:
        def __init__(self, dir):
            self.dir = dir

        def __enter__(self):
            pushdir(dir)

        def __exit__(self, exc_type, exc_val, exc_tb):
            popdir()
    return PushPopDirectory(dir)


def replace_text_in_file(file_name, old_text, new_text):
    text = read_file(file_name)
    text = text.replace(old_text, new_text)
    write_file(file_name, text)


def calculate_sha256(file_name):
    with open(file_name, "rb") as f:
        bytes = f.read()  # read entire file as bytes
        readable_hash = hashlib.sha256(bytes).hexdigest()
        # print(readable_hash)
        return readable_hash


def assert_step(condition, message = ""):
    assert condition, message


def check_step(step):
    def do_nothing():
        pass
    check_step_with_revert(step, do_nothing)


def check_step_with_revert(step, revert_function):
    print("\nCHECK: ", step)
    response = input("  Press Y OR y to continue; Anything else to Quit: ")
    if response not in ['Y', 'y']:
        revert_function()
        exit(0)
    print('---------------------------------------------------------------')
