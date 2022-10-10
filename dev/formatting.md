---
title: Code Formatting Requirements - Juno

toc: true
numbersections: true
colorlinks: true
linkcolor: Bittersweet
---

\pagebreak

# Spacing and Indentation

## General

Single indentations are defined as four spaces each. I believe this is also what tabs in VSCode are defaultly set to, for ease.

Include a space between a function name and its parameters, and between an operator and its operands. 

Example: 

```c
    int addition (int a, int b)
    {
        return a + b;
    }
```

Use extra new lines between blocks of code that logically make sense (do the same task, or same step of a task in a function).

There is no need to include extra newlines after the opening brace, because the opening brace (see next section) provides enough spacing.

## Curly Braces

Opening curly braces should follow the Allman style: be placed on the next line below the function header or conditional, with the same indentation. 

Examples:

```c
    int main (int argc, char[] argv)
    {
        if (such && so)
        {
            return 1;
        }
        return 0;
    }
```

Conditional statements without curly braces *CAN* be used, but ensure that using them does not decrease readability. 

Examples:

```c
    bool main (int argc, char[] argv)
    {
        // this is cool
        if (okay)
            return true;
        
        // this is also cool
        if (such && so)
            return true;
        else
            return false;

        // this should use braces
        if (super super longggggggggggggggggggggggggggggg conditionalllllllllllllll)
            return true;

        // reconsider
        if (such && so)
            return true;
        return false;

        // permissable, depends on context (section 1.1)
        //    i.e. the rest of the function builds up to
        //    this `if` statement and the `return false`
        //    is a default return
        if (such && so)
            return true;

        return false;
    }
```

## Parameters

Parameters can be listed on the same line as the function declaration. Consider listing them on the following lines only if it is starting to get long. When listing on separate lines, align the parameters on an indentation. 

Example (bottom function from the Linux kernel):

```c
    int main (int argc, char[] argv)
    {
        ...
    }

    static void kvm_make_vcpu_request ( struct kvm_vcpu* vcpu,
                                        unsigned int req,
                                        struct cpumask* tmp, 
                                        int current_cpu)
    {
        ...
    }
```

## Pointer Asterisks (Hot Take)

Asterisks denoting pointers go next to the type they are pointing to in the variable declaration. Pointers are types in and of themselves; we don't want to declare a dereferenced variable, we want to declare a pointer.

Example: 

```c
    // My brother in christ
    int *p;

    // Perfect, beautiful, stunning
    int* p;
```

This comes with the caveat that you should be careful when declaring variables with commas:

```c
    // This...
    int* p, q, r;

    // does NOT mean this...
    int* p;
    int* q;
    int* r;

    // It means THIS:
    int* p;
    int q;
    int r;
```

# Naming Conventions

Variable and function names follow classic-C `snake_case`. While names can use abbreviations, make sure they are as descriptive of the function/variable's role as possible. 

Iterators (`i`, `j`, etc) are exempt from this. 

Macros are named in all caps.

These are pretty standard naming conventions, not very controversial.

# Comments

## File Headers

Include a comment block at the very top of the file, defining what the code inside the file is for. If you can't easily distinguish what sets this code file from the rest, consider squashing it into a pre-existing file. 

Example:

```c
    /* ******************************************************
     * MUTEX.C
     *
     * Defines primitive mutex functions used by specialized
     * functions in logging.c and ioctl.c
     * *****************************************************/
```

## Function Headers

Include a comment block with a short description before each function definition (implementation); comments are not neccessary for declarations in header files. Consider listing inputs and outputs in the description. 

Example:

```c
    int addition (int a, int b);

    ...

    /*
     * Performs simple addition. Takes in two ints and
     * returns an int = a + b.
     */
    int addition (int a, int b)
    {
        ...
    }
```

## In-Code Comments

When utilizing in-code comments, put the comment on the line above or below the line you are commenting. 

If you must put a comment on the same line as code, keep it very short (i.e. clarifying the value of a variable). 

In-code comments are especially useful when writing code doing any of the following:

- complicated string manipulation
- binary operations/math
- assembly instructions
- direct memory addressing (such as in a kernel)

Example (adapted from [here](https://github.com/cacama-valvata/emuga)):

```c
    // not shown: first two bytes and higher nibble of third byte in buffer
    int effect [3];                         // effects are always defined by three nibbles
    effect[0] = buffer[2] & 0x0f;           // lower nibble of third byte
    effect[1] = (buffer[3] & 0xf0) >> 4;    // higher nibble of fourth byte
    effect[2] = buffer[3] & 0x0f;           // lower nibble of fourth byte

```
