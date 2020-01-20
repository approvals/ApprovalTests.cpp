import Version
import build_hpp


if __name__ == '__main__':
    version = Version.load_version()

    new_version = Version.update_patch(version)

    build_hpp.Release(version, new_version, False).build_hpp()
