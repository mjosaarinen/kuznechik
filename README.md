kuznechik
=========

04-Jan-15  Markku-Juhani O. Saarinen <mjos@iki.fi>

A simple, totally unoptimized implementation of the proposed Russian block cipher standard, Kuznechik ("Grasshopper"). 128-bit block size, 256-bit key. 

A preliminary spec has been around for a year or two, and I met with few of the authors in Moscow in June '14 (CTCryt '14). The doc subdirectory has some documetation: the current Russian spec, Eric Filiol's translation, and 
the version presented at CTCrypt '14. Eric Filiol also has a 
[blog entry on this cipher](http://cvo-lab.blogspot.fi/2015/01/the-new-gost-standard-from-russian.html)
 (although his implementation is pretty horrible -- with code in header files etc). 

This package includes two versions; a really simple 8-bit version and a version that uses 128-bit data types and really big tables (to show that it can be done). You can choose the version you want in the Makefile; there is about a 100x difference in performance between the two versions but output is equivalent. The implementations match with the test vector found in the standard. However I am not sure about the endianess convention used to store data on wire, so I am just guessing big endian (network byte order -- not the endianess Intel systems usually use).

#Compiling on Linux

Pretty standard coding conventions, 4-space tabs.

Compile on most Linux systems:
```
$ make
gcc -Wall -Ofast -march=native  -c main.c -o main.o
gcc -Wall -Ofast -march=native  -c kuznechik_128bit.c -o kuznechik_128bit.o
gcc  -o xtest main.o kuznechik_128bit.o 
```
Now you can run the test:
```
$ ./xtest 
Self-test:
K_1     = 88 99 AA BB CC DD EE FF 00 11 22 33 44 55 66 77
K_2     = FE DC BA 98 76 54 32 10 01 23 45 67 89 AB CD EF
K_3     = DB 31 48 53 15 69 43 43 22 8D 6A EF 8C C7 8C 44
K_4     = 3D 45 53 D8 E9 CF EC 68 15 EB AD C4 0A 9F FD 04
K_5     = 57 64 64 68 C4 4A 5E 28 D3 E5 92 46 F4 29 F1 AC
K_6     = BD 07 94 35 16 5C 64 32 B5 32 E8 28 34 DA 58 1B
K_7     = 51 E6 40 75 7E 87 45 DE 70 57 27 26 5A 00 98 B1
K_8     = 5A 79 25 01 7B 9F DD 3E D7 2A 91 A2 22 86 F9 84
K_9     = BB 44 E2 53 78 C7 31 23 A5 F3 2F 73 CD B6 E5 17
K_10    = 72 E9 DD 74 16 BC F4 5B 75 5D BA A8 8E 4A 40 43
PT      = 11 22 33 44 55 66 77 00 FF EE DD CC BB AA 99 88
CT      = 7F 67 9D 90 BE BC 24 30 5A 46 8D 42 B9 D4 ED CD
PT      = 11 22 33 44 55 66 77 00 FF EE DD CC BB AA 99 88
Self-test OK!
kuz_encrypt_block(): 23976.211 kB/s (n=51200kB,t=2.135s)
kuz_decrypt_block(): 17261.171 kB/s (n=51200kB,t=2.966s)
```
This indicates success!
