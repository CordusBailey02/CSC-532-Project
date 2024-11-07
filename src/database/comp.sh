gcc -c mysql $(mysql_config --cflags) mysql.c $(mysql_config --libs)
ar rcs libmysql.a libmysql.o