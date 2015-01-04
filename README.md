kuznechik
=========

04-Jan-14  Markku-Juhani O. Saarinen <mjos@iki.fi>

A simple implementation of the proposed Russian block cipher standard, Kuznechik ("Grasshopper"). 128-bit block size, 256-bit key. Matches with the test vectors found in the standard.

A preliminary spec has been around for a year or two, and I met with few of the authors in Moscow in June '14 (CTCryt '14). The doc subdirectory has some documetation: the current Russian spec, Eric Filiol's translation, and 
the version presented at CTCrypt '14. Eric filiol has a 
[blog entry on this cipher](http://cvo-lab.blogspot.fi/2015/01/the-new-gost-standard-from-russian.html)
 (although his is implementation is pretty horrible with code in header files etc). 

There are straight-forward ways to optimize this by transforming the linear transform into a simple lookup.
Will include an optimized version later.

#Compiling on Linux

Pretty standard coding conventions, 4-space tabs.

Just run:
```
$ make
gcc -Wall -Ofast -march=native  -c main.c -o main.o
gcc -Wall -Ofast -march=native  -c kuznechik_simple.c -o kuznechik_simple.o
gcc  -o xtest main.o kuznechik_simple.o 
```
Now you can run the test:
```
$ ./xtest 
K_1	 = 8899AABBCCDDEEFF0011223344556677
K_2  = FEDCBA98765432100123456789ABCDEF
K_3	 = DB31485315694343228D6AEF8CC78C44
K_4	 = 3D4553D8E9CFEC6815EBADC40A9FFD04
K_5	 = 57646468C44A5E28D3E59246F429F1AC
K_6	 = BD079435165C6432B532E82834DA581B
K_7	 = 51E640757E8745DE705727265A0098B1
K_8	 = 5A7925017B9FDD3ED72A91A22286F984
K_9	 = BB44E25378C73123A5F32F73CDB6E517
K_10 = 72E9DD7416BCF45B755DBAA88E4A4043
PT	 = 1122334455667700FFEEDDCCBBAA9988
CT	 = 7F679D90BEBC24305A468D42B9D4EDCD
PT	 = 1122334455667700FFEEDDCCBBAA9988
OK!
```
This indicates success!
