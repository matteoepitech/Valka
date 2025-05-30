# Getting Started with Valka

## Installation
Clone the Valka repository:

```bash
git clone https://github.com/yourusername/valka.git
cd valka
```

## Build the compiler
Use the appropriate script depending on your operating system.

```bash
chmod +x build_linux_mac.sh
./build_linux_mac.sh
```

```bash
chmod +x build_linux_mac.sh
./build_windows.sh
```

## Create your first program
> Valka is using libC so we can use `puts` to make our first print.

Create a `file.vk` and put this:
```bash
function <i32> puts(<char*> string);

function <i32> main()
{
    puts("Hello World!");
    return 0;
}
```

Compile it using the binary `valkac` or `valkac.exe` compiled earlier.

```bash
./valkac file.vk
```

And run it!

```bash
./a.out
```
