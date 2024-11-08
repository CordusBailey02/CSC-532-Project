# gcc -c -o mysql.o $(mysql_config --cflags) mysql.c $(mysql_config --libs) -L../lib/lterrorexchange
#
gcc -c terrorbase.c -o terrorbase.o `mysql_config --cflags --libs` -L../lib/lterrorexchange
ar rcs libterrorbase.a terrorbase.o
