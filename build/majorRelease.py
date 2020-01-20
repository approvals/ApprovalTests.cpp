import build_hpp


if __name__ == '__main__':
    version = build_hpp.load_version()
    print(build_hpp.Version.get_version(version))

    new_version = build_hpp.Version.update_major(version)
    print(build_hpp.Version.get_version(new_version))
