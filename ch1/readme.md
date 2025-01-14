Компиляция, сборка, запуск

1. Написать программу hello.c, которая выводит фразу “Hello world”:
a. получить исполняемый файл;
b. посмотреть unresolved symbols (puts, printf) с помощью nm;
c. посмотреть зависимости (ldd);
d. запустить.

2. Написать статическую библиотеку с функцией hello_from_static_lib() и
использовать ее в hello.c:
a. посмотреть исполняемый файл на предмет того будет ли функция
hello_from_static_lib() unresolved. Почему?
b. где находится код этой функции?

3. Написать динамическую библиотеку с функцией hello_from_dynamic_lib() и
использовать ее с hello.c:
a. посмотреть состояние функции hello_from_dynamic_lib в получившимся
исполняемом файле. Объяснить увиденное.

4. Написать динамическую библиотеку с функцией hello_from_dyn_runtime_lib() и
загрузить ее в hello.c с помощью dlopen(3). Объяснить что происходит.

Команды:

gcc -c ./source/*.c
ar -r libmy1.a *.o

gcc -c -fPIC ./source/*.c
gcc -shared -o libmy2.so *.o

gcc -o project *.o -L../library -lmy1
gcc -o project *.o -L../library -lmy2 -Wl,-rpath,../library/
