import build_hpp


if __name__ == '__main__':
    version = build_hpp.load_version()

    new_version = build_hpp.Version.update_major(version)

    build_hpp.build_hpp(version, new_version, False)
