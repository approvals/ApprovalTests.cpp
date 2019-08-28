<a id="top"></a>

# Disposable Objects

Most of the configuration points in Approval Tests return a "disposable object" (also known as [RAII](/doc/Glossary.md#raii-resource-acquisition-is-initialization).) This means that when that object is deleted (when it goes out of scope), the customisation to the configuration is undone, and the previous configuration is restored.

This means it is important to store the result in a variable, to pay attention to the scope of that variable, so it lines up with how long you wish to configuration to exist.

All of our disposable objects take advantage of the C++17 language feature `[[nodiscard]]`. If you are on C++17, this means that the following line will either give a compiler warning or a compiler error, depending on your setup.

snippet: disposable_incorrect

If you are on C++14 or below, the compiler will not detect this, but the code is still incorrect.

The code should look like this:

snippet: disposable_correct

---

[Back to User Guide](/doc/README.md#top)
