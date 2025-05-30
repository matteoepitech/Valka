# Language Syntax

## Overview

This document describes the syntax and structure of Valka. The language features C-like syntax with explicit type annotations.

## Basic Structure

### Comments
```
// Single line comments (assumed based on C-like syntax)
```

### Program Entry Point
Every program must have a `main` function that serves as the entry point:
```
function <i32> main()
{
    // program code here
    return 0;
}
```

## Data Types

### Primitive Types
- `<i32>` - 32-bit signed integer
- `<char>` - 8-bit Character
- `<bool>` - 1-bit Bool
- `<void>` - Void type (no return value)

## Variable Declarations

Variables are declared using the `var` keyword followed by the type and identifier:

```
var <type> identifier = value;
```

### Examples:
```
var <i32> counter = 0;
var <i32> result = 1;
var <char*> message = "Hello World";
```

## Function Declarations

Functions are declared using the `function` keyword with explicit return type annotation:

```
function <return_type> function_name(<parameter_type> parameter_name, ...)
{
    // function body
    return value; // if not void
}
```

### Function Examples:

#### Void Function (No Return Value)
```
function <void> my_function(<i32> parameter)
{
    // function body
}
```

#### Function with Return Value
```
function <i32> add_numbers(<i32> a, <i32> b)
{
    return a + b;
}
```

#### Function with Multiple Parameters
```
function <i32> calculate(<i32> x, <i32> y, <i32> z)
{
    return x + y * z;
}
```

## Control Flow

### For Loops
```
for (var <i32> i = 0; i < limit; i = i + 1) {
    // loop body
}
```

#### Key Points:
- For init variable are usable even after the loop. So you can get the final index for example.
- Increment uses assignment: `i = i + 1` (no `++` operator at the moment)
- Condition uses standard comparison operators

### While Loops
```
while (condition) {
    // loop body
}
```

### Conditional Statements
```
if (condition) {
    // if body
}
```

## Operators

### Arithmetic Operators
- `+` - Addition
- `-` - Subtraction
- `*` - Multiplication
- `/` - Division (integer division)
- `%` - Modulo

### Comparison Operators
- `==` - Equal to
- `!=` - Not equal to
- `<` - Less than
- `>` - Greater than
- `<=` - Less than or equal to
- `>=` - Greater than or equal to

### Assignment Operator
- `=` - Assignment

## Syntax Rules Summary

1. **Function declarations** must use `function` keyword with explicit type annotations
2. **Variable declarations** must use `var` keyword with type annotation
3. **Braces** `{}` are required for function bodies and control structures
4. **Semicolons** `;` are **NOT** required to terminate statements but **recommended**
5. **Type annotations** use angle bracket notation: `<type>`
6. **Return statements** are required for non-void functions
7. **Loop increments** use full assignment syntax: `i = i + 1`
