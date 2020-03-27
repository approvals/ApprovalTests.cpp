import configparser
import os


def get_version(version):
    return F"v.{version['major']}.{version['minor']}.{version['patch']}"

def get_version_without_v(version_string):
    return version_string.replace("v.", "")

def update_major(version):
    return {"major": int(version['major']) + 1, "minor": 0, "patch": 0}

def update_minor(version):
    return {"major": version['major'], "minor": int(version['minor']) + 1, "patch": 0}

def update_patch(version):
    return {"major": version['major'], "minor": version['minor'], "patch": int(version['patch']) + 1}

def no_version_change(version):
    # This is useful if a deploy failed part-way through, and we don't want to incremen the version number
    return {"major": version['major'], "minor": version['minor'], "patch": int(version['patch'])}

def version_file_path():
    path = os.getcwd()
    return os.path.join(path, 'version.ini')

def load_version():
    config = configparser.ConfigParser()
    config.read(version_file_path())
    return config['VERSION']

def write_version(version):
    config = configparser.ConfigParser()
    config['VERSION'] = version

    with open(version_file_path(), 'w') as configfile:
        config.write(configfile)
