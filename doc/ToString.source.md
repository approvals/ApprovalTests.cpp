# String conversions

When you use Approval tests, the results of the things you are testing are going to be stored on disk. It is good if you can diff the files, to gain an understanding of what is created and how they change. Mainly this is done by creating strings.

## How

This is often done by overloading the output operator (`<<`).

For example

snippet: to_string_standard_example

If including the standard string is problematic, and you are tempted to surround it with `#ifdef`s so that it only shows up in testing, we recommend that you use the template approach instead.

snippet: to_string_template_example


## Design
