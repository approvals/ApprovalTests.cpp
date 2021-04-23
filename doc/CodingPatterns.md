<a id="top"></a>

# Coding Patterns

<!-- toc -->
## Contents

  * [Static variables for header-only releases](#static-variables-for-header-only-releases)<!-- endToc -->

## Static variables for header-only releases

**Note:** As of v.10.1.1, this pattern is still used, but it is no longer needed. Method implementations are now in .cpp files, so the more conventional mechanism for initialising static variables would work fine.

---

Here is a sample of the pattern that we are using:

<!-- snippet: static_variable_sample_header -->
<a id='snippet-static_variable_sample_header'></a>
```h
private:
    static std::shared_ptr<Reporter>& defaultReporter();

public:
    static std::shared_ptr<Reporter> getDefaultReporter();

    static void setDefaultReporter(const std::shared_ptr<Reporter>& reporter);
```
<sup><a href='/ApprovalTests/reporters/DefaultReporterFactory.h#L12-L20' title='Snippet source file'>snippet source</a> | <a href='#snippet-static_variable_sample_header' title='Start of snippet'>anchor</a></sup>
<!-- endSnippet -->

<!-- snippet: static_variable_sample_implementation -->
<a id='snippet-static_variable_sample_implementation'></a>
```cpp
namespace ApprovalTests
{
    std::shared_ptr<Reporter>& DefaultReporterFactory::defaultReporter()
    {
        static std::shared_ptr<Reporter> reporter = std::make_shared<DiffReporter>();
        return reporter;
    }

    std::shared_ptr<Reporter> DefaultReporterFactory::getDefaultReporter()
    {
        return defaultReporter();
    }

    void
    DefaultReporterFactory::setDefaultReporter(const std::shared_ptr<Reporter>& reporter)
    {
        defaultReporter() = reporter;
    }
}
```
<sup><a href='/ApprovalTests/reporters/DefaultReporterFactory.cpp#L4-L24' title='Snippet source file'>snippet source</a> | <a href='#snippet-static_variable_sample_implementation' title='Start of snippet'>anchor</a></sup>
<!-- endSnippet -->

Note the use of the reference (&) on the return type of the private method, and the addition of a getter and setter method.

---

[Back to User Guide](/doc/README.md#top)
