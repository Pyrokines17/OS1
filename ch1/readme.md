`gcc` - GNU project C and C++ compiler
`nm` - list symbols from object files
`ldd` - print shared object dependencies
`ar` - create, modify, and extract from archives

`"U" The symbol is undefined`

Команды:
`gcc -c *.c` -- создание объектных файлов
`ar -rcs <libname.a> *.o` -- создание статической библиотеки

При использовании статической библиотеки её код будет перемещён в итоговую программу

`gcc -c -fPIC *.c` -- создание объектного файла для динамической библиотеки
`gcc -shared -o <libname.so> *.o` -- создание динамической библиотеки

При использовании динамической библиотеки в итоговой программе будет механизм, ссылающийся на код в динамической библиотеке 

