gcc -o mysql $(mysql_config --cflags) mysql.c $(mysql_config --libs)
./mysql