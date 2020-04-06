from scripts.multiline_string_utilities import remove_indentation


class PragmaOnceDiscarder:
    def __init__(self):
        self.ifndef_count = 0
        self.defined_count = 0
        self.endif_count = 0
        self.toggle = ""
        self.missing = ""

    def pragma_once_discarder(self, line):
        stripped_line = line.strip()
        if stripped_line.startswith('#ifndef') and stripped_line.endswith('_H'):
            self.ifndef_count += 1
            if self.toggle != "":
                self.missing += f"Error: The #endif for this line needs a comment added: {self.toggle} \n"
            toggle = line
            return True
        if stripped_line.startswith('#define') and stripped_line.endswith('_H'):
            self.defined_count += 1
            return True
        if stripped_line.startswith('#endif') and stripped_line.endswith('_H'):
            self.endif_count += 1
            toggle = ""
            return True
        return False

    def get_method(self):
        def is_discardable(line):
            return self.pragma_once_discarder(line)

        return is_discardable

    def assert_checks(self):
        if (self.ifndef_count != self.defined_count or self.ifndef_count != self.endif_count):
            stats = remove_indentation << f'''
                ifndef  # {self.ifndef_count}
                defined # {self.defined_count}
                endif   # {self.endif_count}
            '''
            print(stats)
            print(self.missing)
            assert False
