import unittest

from scripts.utilities import pushdir, popdir, run
from tests.helpers import set_home_directory


class TestTypehints(unittest.TestCase):
    def test_typehints(self) -> None:
        set_home_directory()
        pushdir('../build')
        run(['./check_type_hints.sh'])
        popdir()
