import textwrap


class RemoveMultilineIndentation:
    def __lshift__(self, text):
        cleaned = textwrap.dedent(text)
        if cleaned.startswith("\n"):
            cleaned = cleaned[1:]
        return cleaned

remove_indentation = RemoveMultilineIndentation()