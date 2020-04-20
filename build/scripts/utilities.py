import os
import subprocess
import hashlib


from typing import Callable, List, Any


def run(command: List[str]) -> None:
    print(command)
    subprocess.run(" ".join(command), shell=True, check=True)


def write_file(file_name: str, text: str) -> None:
    with open(file_name, 'w') as output:
        output.write(text)


def read_file(file_name: str) -> str:
    with open(file_name) as input:
        text = input.read()
    return text

def get_file_name(path: str) -> str:
    return os.path.split(path)[1]

pushstack = list()


def pushdir(dirname: str) -> None:
    global pushstack
    pushstack.append(os.getcwd())
    os.chdir(dirname)


def popdir() -> None:
    global pushstack
    os.chdir(pushstack.pop())


def use_directory(dir: str) -> Any: # work around for nested class
    class PushPopDirectory:
        def __init__(self, dir: str) -> None:
            self.dir = dir

        def __enter__(self) -> None:
            pushdir(dir)

        def __exit__(self, exc_type: Any, exc_val: Any, exc_tb: Any) -> None:
            popdir()
    return PushPopDirectory(dir)


def replace_text_in_file(file_name: str, old_text: str, new_text: str) -> None:
    text = read_file(file_name)
    text = text.replace(old_text, new_text)
    write_file(file_name, text)


def calculate_sha256(file_name: str) -> str:
    with open(file_name, "rb") as f:
        bytes = f.read()  # read entire file as bytes
        readable_hash = hashlib.sha256(bytes).hexdigest()
        # print(readable_hash)
        return readable_hash


# condition should be an Expression
def assert_step(condition: Any, message:str = "") -> None:
    assert condition, message


def check_step(step: str) -> None:
    def do_nothing() -> None:
        pass
    check_step_with_revert(step, do_nothing)


def check_step_with_revert(step: str, revert_function: Callable) -> None:
    print("\nCHECK: ", step)
    response = input("  Press Y OR y to continue; Anything else to Quit: ")
    if response not in ['Y', 'y']:
        revert_function()
        exit(0)
    print('---------------------------------------------------------------')
