import unittest

from scripts.documentation_release import PrepareDocumentationRelease


class TestPrepareDocumentation(unittest.TestCase):
    def test_update_features_with_new_features(self) -> None:
        content = f'''
toc

## v.x.y.z

{self.new_feature_text()}

{self.old_feature_text()}

'''
        expected_new_content = f'''
toc

## v.x.y.z

## v.1.2.4

{self.new_feature_text()}

{self.old_feature_text()}

'''
        old_version = "v.1.2.3"
        new_version = "v.1.2.4"
        action = PrepareDocumentationRelease.prepare_update_features_page(old_version, new_version, content)
        new_content = action("", lambda _, old, new: content.replace(old, new))
        self.assertEqual(expected_new_content, new_content)

    def test_update_features_with_no_new_features(self) -> None:
        content = f'''
toc

## v.x.y.z

{self.old_feature_text()}

'''
        old_version = "v.1.2.3"
        new_version = "v.1.2.4"
        action = PrepareDocumentationRelease.prepare_update_features_page(old_version, new_version, content)
        new_content = action("", lambda text: f'CHECK: {text}')
        self.assertEqual(new_content, 'CHECK: the Features page is empty: are you sure you want this?')

    @staticmethod
    def new_feature_text() -> str:
        return (
            '### New Feature\n'
            '\n'
            'New feature details.'
        )

    @staticmethod
    def old_feature_text() -> str:
        return (
            '## v.1.2.3\n'
            '\n'
            '### Old Feature\n'
            '\n'
            'Old feature details.'
        )


if __name__ == '__main__':
    unittest.main()
