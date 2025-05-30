# Some Examples

## Simple Counter
```c
function <i32> main()
{
    var <i32> counter = 0;

    for (var <i32> i = 0; i < 10; i = i + 1) {
        counter = counter + 1;
        put_nbr(counter); // not defined in this example
        putchar(10);  // Newline character
    }
    return 0;
}
```

## Fibonacci Sequence
```c
function <i32> main(<i32> argc)
{
    var <i32> old_result = 0;
    var <i32> result = 1;
    var <i32> tmp = 0;
    
    for (var <i32> i = 0; i < argc; i = i + 1) {
        tmp = result;
        result = result + old_result;
        old_result = tmp;
        put_nbr(result); // not defined in this example
        putchar(10);
    }
    return 0;
}
```

