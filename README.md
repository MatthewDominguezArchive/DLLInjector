# DLLInjector
Simple Windows DLL Injector source code + example DLL source code.

### Description
Here is a visual studio solution I made with the help of internet research. It's a CLI DLL Injector, Aswell as a source for a DLL. I tried my best to make it as legible as possible. It's not really something I plan on spending a lot of more time on so if you are looking for a UI, I would encourage you to add one! I'm fairly confident this will not bypass any modern anti-virus or anti-cheat so I'm comfortable publicizing this project.

### How To Build
```
DLL Project Properties (Change From Debug To Release):
 |
 |--- General
 |    |--- C++ Language Standard: ISO C++20 Standard (/std:c++20)
 |
 |--- Advanced
 |    |--- Character Set: Use Multi-Byte Character Set
 |
 |--- C/C++
      |--- Precompiled Headers
           |---Precompiled Header: Not Using Precompiled Headers
```

```        
Injector Project Properties (Change From Debug To Release):
 |
 |--- General
 |    |--- C++ Language Standard: ISO C++20 Standard (/std:c++20)
 |
 |--- Advanced
      |--- Character Set: Use Multi-Byte Character Set```

### How To Use
CLI: <Injector.exe> <DLL.dll> <targetprcoess.exe>
