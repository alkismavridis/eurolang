#1. Compile
    ../out/eulc ../data/test.eul ../data/obj.o


#2. Link
ld ../data/obj.o -e _startEul \
    -dynamic-linker /lib64/ld-linux-x86-64.so.2 \
    /usr/lib/gcc/x86_64-linux-gnu/7/../../../x86_64-linux-gnu/crt1.o \
    /usr/lib/gcc/x86_64-linux-gnu/7/../../../x86_64-linux-gnu/crti.o \
    /usr/lib/gcc/x86_64-linux-gnu/7/crtbegin.o \
    /usr/lib/gcc/x86_64-linux-gnu/7/crtend.o \
    -L/usr/lib/gcc/x86_64-linux-gnu/7 -L/usr/lib/gcc/x86_64-linux-gnu/7/../../../x86_64-linux-gnu -L/usr/lib/gcc/x86_64-linux-gnu/7/../../../../lib -L/lib/x86_64-linux-gnu -L/lib/../lib -L/usr/lib/x86_64-linux-gnu -L/usr/lib/../lib -L/usr/lib/gcc/x86_64-linux-gnu/7/../../.. \
    -lc -lgcc -lgcc_s -o ../data/pr


    #gcc -no-pie -o ../data/pr_gcc ../data/hello



#3. cleanup
    rm ../data/obj.o

