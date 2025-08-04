#pragma once
#include <stdio.h>
#include <ctype.h>
#include <string.h>

int initTable();
char* vi_encrypt(char* key, char* src);
char* vi_decrypt(char* key, char* src);
