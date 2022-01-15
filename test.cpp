#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

typedef int (*opfunc)(int);
typedef void (*func2)();

int main(int argc, char** argv)
{
    if(argc < 3)
    {
        printf("usage: %s <library> <number> \n", argv[0]);
        exit(1);
    }

    char *libpath = argv[1];
    int n = atoi(argv[2]);

    printf("lib path %s, n=%d\n", libpath, n);
    
    void *handler = dlopen(libpath, RTLD_LAZY);
    if(handler == NULL)
    {
        perror("error - dlopen");
    } else {
        printf("dlopen OK\n");
    }

    opfunc f1 = (opfunc)dlsym(handler, "do_operation");
    if(f1 == NULL)
    {
        printf("error - dlsym\n%s\n", dlerror());
        exit(-1);
    }
    func2 f2 = (func2)(dlsym(handler, "get_library_name"));
    if(f2 == NULL)
    {
        printf("error - dlsym\n%s\n", dlerror());
        exit(-1);
    }

    f2();
    printf("%d --> %d\n", n, f1(n));

    dlclose(handler);

    return 0;
}