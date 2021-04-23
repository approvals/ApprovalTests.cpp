# https://matthewsetter.com/tools-that-make-technical-writing-easier-markdown-linter/
# https://github.com/markdownlint/markdownlint/blob/master/docs/RULES.md

# How to run
#  /usr/local/lib/ruby/gems/3.0.0/bin/mdl          doc | grep -v sphinx
#  /usr/local/lib/ruby/gems/3.0.0/bin/mdl -r MD032 doc | grep -v sphinx

all

# Rules that mdsnippets output breaks:
exclude_rule 'MD033' # Inline HTML
exclude_rule 'MD031' # Fenced code blocks should be surrounded by blank lines
exclude_rule 'MD006' # Consider starting bulleted lists at the beginning of the line

# Things I think cannot be turned on
exclude_rule 'MD005' # Inconsistent indentation for list items at the same level
exclude_rule 'MD007' # Unordered list indentation
exclude_rule 'MD041' # First line in file should be a top level header

# Things I don't think matter:
exclude_rule 'MD036' # Emphasis used instead of a header

# Things that I think are bugs in markdownlint:
exclude_rule 'MD046' # Code block style <<< This appears in middle of fenced area, for lines with 4 spaces at the line
exclude_rule 'MD034' # Bare URL used <<< See https://github.com/markdownlint/markdownlint/issues/191

# Fix now
# exclude_rule 'MD032' # Lists should be surrounded by blank lines

# Things I would like to fix eventually
exclude_rule 'MD029' # Ordered list item prefix
exclude_rule 'MD009' # Trailing spaces << Need to work out how to allow 2 or more spaces, for line-breaks
exclude_rule 'MD022' # Headers should be surrounded by blank lines

exclude_tag :line_length
