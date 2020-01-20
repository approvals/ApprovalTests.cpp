import configparser


class Version:
    @staticmethod
    def get_version(version):
        return F"v.{version['major']}.{version['minor']}.{version['patch']}"

    @staticmethod
    def update_major(version):
        return {"major": int(version['major']) + 1, "minor": 0, "patch": 0}

    @staticmethod
    def update_minor(version):
        return {"major": version['major'], "minor": int(version['minor']) + 1, "patch": 0}

    @staticmethod
    def update_patch(version):
        return {"major": version['major'], "minor": version['minor'], "patch": int(version['patch'] + 1)}

    @staticmethod
    def load_version():
        config = configparser.ConfigParser()
        config.read('version.ini')
        return config['VERSION']

    @staticmethod
    def write_version(version):
        config = configparser.ConfigParser()
        config['VERSION'] = version

        with open('version.ini', 'w') as configfile:
            config.write(configfile)