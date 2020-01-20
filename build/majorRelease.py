import Version
import build_hpp


if __name__ == '__main__':
    version = Version.Version.load_version()

    new_version = Version.Version.update_major(version)

    build_hpp.build_hpp(version, new_version, False)
