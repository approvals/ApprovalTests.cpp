import textwrap


def remove_indentation_from(text):
    cleaned = textwrap.dedent(text)
    if cleaned.startswith("\n"):
        cleaned = cleaned[1:]
    return cleaned


class RemoveMultilineIndentation:
    def __lshift__(self, text):
        return remove_indentation_from(text)


remove_indentation = RemoveMultilineIndentation()
