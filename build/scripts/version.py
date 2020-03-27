import configparser
import os


def get_version_text(version):
    return F"v.{version['major']}.{version['minor']}.{version['patch']}"

def get_version_without_v(version_string):
    return version_string.replace("v.", "")

def update_major(version):
    return create_version(get_major(version) + 1, 0, 0)

def update_minor(version):
    return create_version(get_major(version), get_minor(version) + 1, 0)

def update_patch(version):
    return create_version(get_major(version), get_minor(version), get_patch(version) + 1)

def get_major(version):
    return int(version['major'])

def get_minor(version):
    return int(version['minor'])

def get_patch(version):
    return int(version['patch'])

def no_version_change(version):
    # This is useful if a deploy failed part-way through, and we don't want to increment the version number
    return create_version(get_major(version), get_minor(version), get_patch(version))

def version_file_path():
    path = os.getcwd()
    return os.path.join(path, 'version.ini')

def load_version():
    config = configparser.ConfigParser()
    config.read(version_file_path())
    return config['VERSION']

def create_version(major, minor, patch):
    return {"major": major, "minor": minor, "patch": patch}

def write_version(version):
    config = configparser.ConfigParser()
    config['VERSION'] = version

    with open(version_file_path(), 'w') as configfile:
        config.write(configfile)
