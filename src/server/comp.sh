#!/usr/bin/env bash
gcc -o server server.c -L../lib -lterrorexchange -lsecure_connection -L../database -lterrorbase -lmysqlclient
