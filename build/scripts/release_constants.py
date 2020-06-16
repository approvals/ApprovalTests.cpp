import os


class ReleaseConstants:
    def __init__(self) -> None:
        self.build_dir = F"../build"
        self.release_dir = F"../build/releases"

        self.xxx_release_notes_path = os.path.join(self.build_dir, F'relnotes_x.y.z.md')
        self.release_notes_dir = os.path.join(self.build_dir, 'release_notes')
        self.template_release_notes_path = os.path.join(self.release_notes_dir, F'relnotes_template.md')


release_constants = ReleaseConstants()
