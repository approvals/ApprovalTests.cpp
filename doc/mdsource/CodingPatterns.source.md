<a id="top"></a>

# Coding Patterns

toc

## Static variables for header-only releases

Here is a sample of the pattern that we are using:

snippet: static_variable_sample_header

snippet: static_variable_sample_implementation

Note the use of the reference (&) on the return type of the private method, and the addition of a getter and setter method.

---

[Back to User Guide](/doc/README.md#top)
