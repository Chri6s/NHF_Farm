#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define A 65
#define TABLE_WIDTH 26

char table[TABLE_WIDTH][TABLE_WIDTH];


int initTable()
{
	int i, j;
	for (i = 0; i < TABLE_WIDTH; i++)   {
		for (j = 0; j < TABLE_WIDTH; j++)    {
			table[i][j] = A + (i + j) % TABLE_WIDTH;
		}
	}
	return 1;
}

int vi_encrypt(char* key, char* src, char* dest)
{
	char *pSrc = src;
	char *pKey = key;
	char *pDest = dest;

	do {
		if (!isalpha(*pSrc))
		{
			continue;
		}
		*pDest++ = table[toupper(*pKey) - A][toupper(*pSrc) - A];

		if (!(*(++pKey)))
			pKey = key;
	} while (*pSrc++);

	dest[strlen(src)] = 0;
	return 1;
}

int vi_decrypt(char* key, char* src, char* dest)
{	char *pSrc = src;
	char *pKey = key;
	char *pDest = dest;
	char offset;

	do {
		offset = (*pSrc) - toupper(*pKey);
		offset = offset >= 0 ? offset : offset + TABLE_WIDTH;
		*pDest++ = tolower(A + offset);

		if (!(*(++pKey)))
			pKey = key;
	} while (*pSrc++);

	dest[strlen(src)] = 0;
	return 1;
}

// int main()
// {
// 	char secret[6] = "FarmR";
// 	char text[10000] = "hgaksgdfjkhgsdafkegakjgsdfkjegakjgdfjkahgfkjeagkzudsgfkehabkjabsvkahsdbvkajbhsdvkajsgfiwuazgrihasdbkajsdhbfkaezgfkahgaksgdfjkhgsdafkegakjgsdfkjegakjgdfjkahgfkjeagkzudsgfkehabkjabsvkahsdbvkajbhsdvkajsgfiwuazgrihasdbkajsdhbfkaezgfkahgaksgdfjkhgsdafkegakjgsdfkjegakjgdfjkahgfkjeagkzudsgfkehabkjabsvkahsdbvkajbhsdvkajsgfiwuazgrihasdbkajsdhbfkaezgfkahgaksgdfjkhgsdafkegakjgsdfkjegakjgdfjkahgfkjeagkzudsgfkehabkjabsvkahsdbvkajbhsdvkajsgfiwuazgrihasdbkajsdhbfkaezgfkahgaksgdfjkhgsdafkegakjgsdfkjegakjgdfjkahgfkjeagkzudsgfkehabkjabsvkahsdbvkajbhsdvkajsgfiwuazgrihasdbkajsdhbfkaezgfkahgaksgdfjkhgsdafkegakjgsdfkjegakjgdfjkahgfkjeagkzudsgfkehabkjabsvkahsdbvkajbhsdvkajsgfiwuazgrihasdbkajsdhbfkaezgfkahgaksgdfjkhgsdafkegakjgsdfkjegakjgdfjkahgfkjeagkzudsgfkehabkjabsvkahsdbvkajbhsdvkajsgfiwuazgrihasdbkajsdhbfkaezgfkahgaksgdfjkhgsdafkegakjgsdfkjegakjgdfjkahgfkjeagkzudsgfkehabkjabsvkahsdbvkajbhsdvkajsgfiwuazgrihasdbkajsdhbfkaezgfkahgaksgdfjkhgsdafkegakjgsdfkjegakjgdfjkahgfkjeagkzudsgfkehabkjabsvkahsdbvkajbhsdvkajsgfiwuazgrihasdbkajsdhbfkaezgfkahgaksgdfjkhgsdafkegakjgsdfkjegakjgdfjkahgfkjeagkzudsgfkehabkjabsvkahsdbvkajbhsdvkajsgfiwuazgrihasdbkajsdhbfkaezgfkahgaksgdfjkhgsdafkegakjgsdfkjegakjgdfjkahgfkjeagkzudsgfkehabkjabsvkahsdbvkajbhsdvkajsgfiwuazgrihasdbkajsdhbfkaezgfka";
// 	char ciphertext[256];
// 	char output[10000];

// 	initTable();

// 	encrypt(secret, text, ciphertext);
// 	printf("out: [%s]\n", ciphertext);

// 	decrypt(secret, ciphertext, output);
// 	printf("input was: [%s]\n", output);

// 	return 0;
// }