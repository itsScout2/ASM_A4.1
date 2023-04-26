#define _CRT_SECURE_NO_WARNINGS

/*Дан массив A из 16 байтов. Те элементы, которые являются суммой соседних,
копировать в массив B (крайние элементы не рассматривать), а в массив C
помещать адреса (смещения) этих элементов. Сосчитать количество таких элементов.*/

#include "stdio.h"
#include "locale.h"

void clear_input() {
	int c;
	while ((c = getchar()) != '\n' && c != EOF) {}
}

int main() {
	setlocale(LC_ALL, "rus");
	setlocale(LC_NUMERIC, "eng");

	char A[16], B[14];
	short* C[14];
	char B_asm[14];
	short* C_asm[14];
	short input;
	short k = 0, k_asm = 0;

	unsigned tmp = 1, flag = 1;
	while (tmp) {

		for (short i = 0; i < 16; ++i) {
			flag = 1;
			while (flag) {
				printf("Введите %hd элемент:\n", i + 1);
				if (scanf("%hd", &input) != 1) {
					printf("Повторите ввод %hd элемента:\n", i + 1);
					clear_input();
				}
				else if(input < -128 || input > 127)
				{
					printf("Повторите ввод %hd элемента:\n", i + 1);
				} 
				else {
					A[i] = (char)input;
					flag = 0;
				}
			}
		}

		printf("\n\nРешение на языке Си:\n\n");
		for (short i = 1; i < 15; ++i) {
			if (A[i] == (A[i + 1] + A[i - 1])) {
				B[k] = A[i];
				*(C + k) = &A[i];
				k++;
			}
		}
		printf("Количество элементов: %hd\n", k);
		if (k == 0) {
			printf("Массивы В и С пустые");
		}
		else {
			printf("Массив B:\n");
			for (short i = 0; i < k; ++i) {
				printf("%hd ", (short)B[i]);
			}
			printf("\nМассив C:\n");
			for (short i = 0; i < k; ++i) {
				printf("%p ", C[i]);
			}
		}
		printf("\n____________________\n");
		printf("\n\nРешение на ассемблере:\n\n");
		__asm {
			;							// начальные установки регистров
			lea esi, A;					// адрес начала массива А в esi
			lea edi, B_asm;				// адрес начала массива B в edi
			lea ebx, C_asm;				// адрес начала массива С в ebx
			mov k_asm, 0;				// счетчик числа подходящих элементов
			xor ecx, ecx;				// счетчик числа цикла и адресация в массиве A
			;							// начало цикла
		NEXT: cmp ecx, 14;
			jae DONE;
			mov al, [esi + 1];
			mov ah, [esi];
			mov dl, [esi + 2];
			add ah, dl;
			cmp al, ah;
			jne NOT_EQ;
			mov [edi], al;
			inc esi;
			mov [ebx], esi;
			dec esi;
			add ebx, 4;
			inc edi;
			inc k_asm;
		NOT_EQ: 
			inc ecx;
			inc esi;
			;
			jmp NEXT;
		DONE:
			nop;
		}
		printf("Количество элементов: %hd\n", k_asm);
		if (k == 0) {
			printf("Массивы В_asm и С_asm пустые");
		}
		else {
			printf("Массив B_asm:\n");
			for (short i = 0; i < k_asm; ++i) {
				printf("%hd ", (short)B_asm[i]);
			}
			printf("\nМассив C_asmm:\n");
			for (short i = 0; i < k_asm; ++i) {
				printf("%p ", C_asm[i]);
			}
		}
		printf("\n____________________\n");


		clear_input();

		printf("Хотите продолжить?\n0 - Нет\n1 - Да\n");

		int term = 1;
		while (term == 1) {
			if (scanf("%d", &tmp) != 1 || (tmp != 0 && tmp != 1)) {
				printf("Введено неверное значение\n");
				printf("Хотите продолжить?\n0 - Нет\n1 - Да\n");
				clear_input();
			}
			else {
				term = 0;
				flag = 1;
			}
		}
	}

	exit();
}