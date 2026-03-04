#include <stdbool.h>
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#include <windows.h>
#include <string.h>
#define SIZE 3000

//建Hash Table
struct the_hash_data_item {
	char word[1024];
	int key;
};
struct the_hash_data_item* hashArray[SIZE];
struct the_hash_data_item* dummyItem;
struct the_hash_data_item* item;

//雜湊值
int the_hash_code(int key) {
	return key;
}

//透過雜湊表之雜湊值進行搜尋
struct the_hash_data_item* search(int key) {
	//get the hash 
	int hashIndex = the_hash_code(key);

	//move in array until an empty 
	while (hashArray[hashIndex] != NULL) { //掃過一次整個HASH TABLE

		if (hashArray[hashIndex]->key == key) {  //判斷key值是否在table裡面
			printf("Token&Word: [%s] 找到.\n", hashArray[hashIndex]->word);
			return hashArray[hashIndex];
		}
		
		++hashIndex; //沒有就往下

		//wrap around the table
		hashIndex %= SIZE; //透過欲查詢的值，經由hash function來查對應的hash table
	}
	printf("找不到\n");
	return NULL;
}

void insert(int key, char* word) {

	struct the_hash_data_item* item = (struct the_hash_data_item*)malloc(sizeof(struct the_hash_data_item)); //配置空間
	strcpy(item->word, word);
	item->key = key;

	//get the hash 
	int hashIndex = the_hash_code(key);

	//move in array until an empty or deleted cell
	while (hashArray[hashIndex] != NULL && hashArray[hashIndex]->key != -1) {
		
		++hashIndex; //沒有就往下

		//wrap around the table
		hashIndex %= SIZE; //透過欲查詢的值，經由hash function來查對應的hash table
	}

	hashArray[hashIndex] = item;
}

struct the_hash_data_item* deleteItem(struct the_hash_data_item* item) {
	int key = item->key;

	//get the hash 
	int hashIndex = the_hash_code(key);

	//move in array until an empty
	while (hashArray[hashIndex] != NULL) {

		if (hashArray[hashIndex]->key == key) {
			struct the_hash_data_item* temp = hashArray[hashIndex];

			//assign a dummy item at deleted position
			hashArray[hashIndex] = dummyItem; 
			return temp;
		}

		++hashIndex;//沒有就往下

		hashIndex %= SIZE; //透過欲查詢的值，經由hash function來查對應的hash table
	}

	return NULL;
}

int key_comput(char* word) { //將字串變成一個字元一個字元去編碼
	int key = 0;
	for (int i = 0; i < strlen(word); i++) {
		int c = (int)word[i];

		if (c <= 57 && c >= 48) { 
			key += (c - 48);

		}
		else
			key += (c - 64);
	}
	return key;
}



int main() 
{
	LARGE_INTEGER t1,t2,t3,t4,t5,t6,ts;
	QueryPerformanceFrequency(&ts); //windows高精度定時器的用法，先獲取頻率

	QueryPerformanceCounter(&t1); //獲取當前的計數值

	int the_index_character,index;
	char str[128];
	printf("TestFile1.txt:[1]  TestFile2.txt:[2] 使用何者檔案當作字典?\n");
	printf("請輸入1或2: ");
	scanf("%d", &index);
	printf("\n/-------------------------------------------------------------/\n");

	//選擇使用的txt檔案來建立字典庫
	if (index == 1)
	{
		FILE* File1;

		File1 = fopen("TestFile1.txt", "r");
		while (fscanf(File1, "%s", str) != EOF) {
			int flag1 = 0;
			for (int i = 0; i < strlen(str); i++) {
				int j = 0;  
				//特殊字元的處理
				if (str[i] == '\'' || str[i] == ',' || str[i] == '\"' || str[i] == '.' || str[i] == '-' || str[i] == '(' || str[i] == ')' || str[i] == ':') {
					char str_A[64] = {}, str_B[64] = {};
					str[i] = ' ';
					for (j = 0; j < i; j++)
						str_A[j] = str[j];
					for (int k = i + 1, j = 0; k < strlen(str); j++, k++) {
						if (str[k] != '\'' && str[k] != ',' && str[k] != '\"' && str[k] != '.' && str[k] != '-' && str[i] != '(' && str[i] != ')' && str[i] != ':')
							str_B[j] = str[k];
						else
							break;
					}

					if (strcmp(str_A, " ")) 
					{
						insert(key_comput(str_B), str_B);
					}
					else if (strcmp(str_B, " ")) 
					{
						insert(key_comput(str_A), str_A);
					}
					else 
					{
						insert(key_comput(str_B), str_B);
						insert(key_comput(str_A), str_A);
					}
					flag1 = 1;
					break;
				}
			}
			if (flag1 == 0) {
				if (strcmp(str, " ")) {
					insert(key_comput(str), str);
				}
			}
		}

		FILE* File11;
		File11 = fopen("TestFile11.txt", "r");
		/*-----------------------------查詢檔案-----------------------------*/
		int success11 = 0.0, failure11 = 0.0;
		while (fscanf(File11, "%s", str) != EOF) {
			int flag11 = 0;

			for (int i = 0; i < strlen(str); i++) {
				int j = 0;
				//特殊字元的處理
				if (str[i] == '\'' || str[i] == ',' || str[i] == '\"' || str[i] == '.' || str[i] == '-' || str[i] == '(' || str[i] == ')' || str[i] == ':') {
					char str_A[64] = {}, str_B[64] = {};
					str[i] = ' ';
					for (j = 0; j < i; j++)
						str_A[j] = str[j];
					for (int k = i + 1, j = 0; k < strlen(str); j++, k++) {
						if (str[k] != '\'' && str[k] != ',' && str[k] != '\"' && str[k] != '.' && str[k] != '-' && str[i] != '(' && str[i] != ')' && str[i] != ':')
							str_B[j] = str[k];
						else
							break;
					}

					if (search(key_comput(str_A)) != NULL || search(key_comput(str_B)) != NULL) {
						success11++;
					}
					else {
						failure11++;
					}
					flag11 = 1;
					break;
				}
			}
			if (flag11 == 0) {
				if (search(key_comput(str))) {
					success11++;
				}
				else {
					failure11++;
				}
			}
		}
		QueryPerformanceCounter(&t2);
		printf("\n查詢 TestFile11.txt：成功數: %d  失敗數: %d \n", success11, failure11);
		float the_success_rate11 = (float)success11 / (success11 + failure11) * 100.0;
		float the_failure_rate11 = (float)failure11 / (success11 + failure11) * 100.0;
		printf("\n成功率：%f %%\n", the_success_rate11);
		printf("失敗率：%f %%\n", the_failure_rate11);
		printf("總時間: %lf 秒\n", (t2.QuadPart - t1.QuadPart) / (double)(ts.QuadPart));
		printf("/-------------------------------------------------------------/\n");

		/*------------------------------------------------------------*/
		QueryPerformanceCounter(&t3);
		FILE* File12;
		File12 = fopen("TestFile12.txt", "r");
		/*-----------------------------查詢檔案-----------------------------*/
		int success12 = 0.0, failure12 = 0.0;
		while (fscanf(File12, "%s", str) != EOF) {
			int flag12 = 0;

			for (int i = 0; i < strlen(str); i++) {
				int j = 0;
				//特殊字元的處理
				if (str[i] == '\'' || str[i] == ',' || str[i] == '\"' || str[i] == '.' || str[i] == '-' || str[i] == '(' || str[i] == ')' || str[i] == ':') {
					char str_A[64] = {}, str_B[64] = {};
					str[i] = ' ';
					for (j = 0; j < i; j++)
						str_A[j] = str[j];
					for (int k = i + 1, j = 0; k < strlen(str); j++, k++) {
						if (str[k] != '\'' && str[k] != ',' && str[k] != '\"' && str[k] != '.' && str[k] != '-' && str[i] != '(' && str[i] != ')' && str[i] != ':')
							str_B[j] = str[k];
						else
							break;
					}

					if (search(key_comput(str_A)) != NULL || search(key_comput(str_B)) != NULL) {
						success12++;
					}
					else {
						failure12++;
					}
					flag12 = 1;
					break;
				}
			}
			if (flag12 == 0) {
				if (search(key_comput(str))) {
					success12++;
				}
				else {
					failure12++;
				}
			}
		}
		QueryPerformanceCounter(&t4);
		printf("\n查詢 TestFile12.txt：成功數: %d  失敗數: %d \n", success12, failure12);
		float the_success_rate12 = (float)success12 / (success12 + failure12) * 100.0;
		float the_failure_rate12 = (float)failure12 / (success12 + failure12) * 100.0;
		printf("\n成功率：%f %%\n", the_success_rate12);
		printf("失敗率：%f %%\n", the_failure_rate12);
		printf("總時間: %lf 秒\n", (t4.QuadPart - t3.QuadPart) / (double)(ts.QuadPart));
		printf("/-------------------------------------------------------------/\n");
		
		/*------------------------------------------------------------*/
		QueryPerformanceCounter(&t5);
		FILE* File13;
		File13 = fopen("TestFile13.txt", "r");
		/*-----------------------------查詢檔案-----------------------------*/
		int success13 = 0.0, failure13 = 0.0;
		while (fscanf(File13, "%s", str) != EOF) {
			int flag13 = 0;

			for (int i = 0; i < strlen(str); i++) {
				int j = 0;
				//特殊字元的處理
				if (str[i] == '\'' || str[i] == ',' || str[i] == '\"' || str[i] == '.' || str[i] == '-' || str[i] == '(' || str[i] == ')' || str[i] == ':') {
					char str_A[64] = {}, str_B[64] = {};
					str[i] = ' ';
					for (j = 0; j < i; j++)
						str_A[j] = str[j];
					for (int k = i + 1, j = 0; k < strlen(str); j++, k++) {
						if (str[k] != '\'' && str[k] != ',' && str[k] != '\"' && str[k] != '.' && str[k] != '-' && str[i] != '(' && str[i] != ')' && str[i] != ':')
							str_B[j] = str[k];
						else
							break;
					}

					if (search(key_comput(str_A)) != NULL || search(key_comput(str_B)) != NULL) {
						success13++;
					}
					else {
						failure13++;
					}
					flag13 = 1;
					break;
				}
			}
			if (flag13 == 0) {
				if (search(key_comput(str))) {
					success13++;
				}
				else {
					failure13++;
				}
			}
		}
		QueryPerformanceCounter(&t6);
		printf("\n查詢 TestFile13.txt：成功數: %d  失敗數: %d \n", success13, failure13);
		float the_success_rate13 = (float)success13 / (success13 + failure13) * 100.0;
		float the_failure_rate13 = (float)failure13 / (success13 + failure13) * 100.0;
		printf("\n成功率：%f %%\n", the_success_rate13);
		printf("失敗率：%f %%\n", the_failure_rate13);
		printf("總時間: %lf 秒\n", (t6.QuadPart - t5.QuadPart) / (double)(ts.QuadPart));
		printf("/-------------------------------------------------------------/\n");
	}

	else if (index == 2)
	{
		FILE* File2;

		File2 = fopen("TestFile2.txt", "r");
		while (fscanf(File2, "%s", str) != EOF) {
			int flag2 = 0;
			for (int i = 0; i < strlen(str); i++) {
				int j = 0;
				//特殊字元的處理
				if (str[i] == '\'' || str[i] == ',' || str[i] == '\"' || str[i] == '.' || str[i] == '-' || str[i] == '(' || str[i] == ')' || str[i] == ':') {
					char str_A[64] = {}, str_B[64] = {};
					str[i] = ' ';
					for (j = 0; j < i; j++)
						str_A[j] = str[j];
					for (int k = i + 1, j = 0; k < strlen(str); j++, k++) {
						if (str[k] != '\'' && str[k] != ',' && str[k] != '\"' && str[k] != '.' && str[k] != '-' && str[i] != '(' && str[i] != ')' && str[i] != ':')
							str_B[j] = str[k];
						else
							break;
					}

					if (strcmp(str_A, " ")) {

						insert(key_comput(str_B), str_B);
					}
					else if (strcmp(str_B, " ")) {
						insert(key_comput(str_A), str_A);

					}
					else {
						insert(key_comput(str_B), str_B);
						insert(key_comput(str_A), str_A);

					}
					flag2 = 1;
					break;
				}
			}
			if (flag2 == 0) {
				if (strcmp(str, " ")) {
					insert(key_comput(str), str);
				}
			}
		}

		FILE* File21;
		File21 = fopen("TestFile21.txt", "r");
		/*-----------------------------查詢檔案-----------------------------*/
		int success21 = 0.0, failure21 = 0.0;
		while (fscanf(File21, "%s", str) != EOF) {
			int flag21 = 0;

			for (int i = 0; i < strlen(str); i++) {
				int j = 0;
				//特殊字元的處理
				if (str[i] == '\'' || str[i] == ',' || str[i] == '\"' || str[i] == '.' || str[i] == '-' || str[i] == '(' || str[i] == ')' || str[i] == ':') {
					char str_A[64] = {}, str_B[64] = {};
					str[i] = ' ';
					for (j = 0; j < i; j++)
						str_A[j] = str[j];
					for (int k = i + 1, j = 0; k < strlen(str); j++, k++) {
						if (str[k] != '\'' && str[k] != ',' && str[k] != '\"' && str[k] != '.' && str[k] != '-' && str[i] != '(' && str[i] != ')' && str[i] != ':')
							str_B[j] = str[k];
						else
							break;
					}

					if (search(key_comput(str_A)) != NULL || search(key_comput(str_B)) != NULL) {
						success21++;
					}
					else {
						failure21++;
					}
					flag21 = 1;
					break;
				}
			}
			if (flag21 == 0) {
				if (search(key_comput(str))) {
					success21++;
				}
				else {
					failure21++;
				}
			}
		}
		QueryPerformanceCounter(&t2);
		printf("\n查詢 TestFile21.txt：成功數: %d  失敗數: %d \n", success21, failure21);
		float the_success_rate21 = (float)success21 / (success21 + failure21) * 100.0;
		float the_failure_rate21 = (float)failure21 / (success21 + failure21) * 100.0;
		printf("\n成功率：%f %%\n", the_success_rate21);
		printf("失敗率：%f %%\n", the_failure_rate21);
		printf("總時間: %lf 秒\n", (t2.QuadPart - t1.QuadPart) / (double)(ts.QuadPart));
		printf("/-------------------------------------------------------------/\n");

		/*------------------------------------------------------------*/
		QueryPerformanceCounter(&t3);
		FILE* File22;
		File22 = fopen("TestFile22.txt", "r");
		/*-----------------------------查詢檔案-----------------------------*/
		int success22 = 0.0, failure22 = 0.0;
		while (fscanf(File22, "%s", str) != EOF) {
			int flag22 = 0;

			for (int i = 0; i < strlen(str); i++) {
				int j = 0;
				//特殊字元的處理
				if (str[i] == '\'' || str[i] == ',' || str[i] == '\"' || str[i] == '.' || str[i] == '-' || str[i] == '(' || str[i] == ')' || str[i] == ':') {
					char str_A[64] = {}, str_B[64] = {};
					str[i] = ' ';
					for (j = 0; j < i; j++)
						str_A[j] = str[j];
					for (int k = i + 1, j = 0; k < strlen(str); j++, k++) {
						if (str[k] != '\'' && str[k] != ',' && str[k] != '\"' && str[k] != '.' && str[k] != '-' && str[i] != '(' && str[i] != ')' && str[i] != ':')
							str_B[j] = str[k];
						else
							break;
					}

					if (search(key_comput(str_A)) != NULL || search(key_comput(str_B)) != NULL) {
						success22++;
					}
					else {
						failure22++;
					}
					flag22 = 1;
					break;
				}
			}
			if (flag22 == 0) {
				if (search(key_comput(str))) {
					success22++;
				}
				else {
					failure22++;
				}
			}
		}
		QueryPerformanceCounter(&t4);
		printf("\n查詢 TestFile22.txt：成功數: %d  失敗數: %d \n", success22, failure22);
		float the_success_rate22 = (float)success22 / (success22 + failure22) * 100.0;
		float the_failure_rate22 = (float)failure22 / (success22 + failure22) * 100.0;
		printf("\n成功率：%f %%\n", the_success_rate22);
		printf("失敗率：%f %%\n", the_failure_rate22);
		printf("總時間: %lf 秒\n", (t4.QuadPart - t3.QuadPart) / (double)(ts.QuadPart));
		printf("/-------------------------------------------------------------/\n");


		/*------------------------------------------------------------*/
		QueryPerformanceCounter(&t5);
		FILE* File23;
		File23 = fopen("TestFile23.txt", "r");
		/*-----------------------------查詢檔案-----------------------------*/
		int success23 = 0.0, failure23 = 0.0;
		while (fscanf(File23, "%s", str) != EOF) {
			int flag23 = 0;

			for (int i = 0; i < strlen(str); i++) {
				int j = 0;
				//特殊字元的處理
				if (str[i] == '\'' || str[i] == ',' || str[i] == '\"' || str[i] == '.' || str[i] == '-' || str[i] == '(' || str[i] == ')' || str[i] == ':') {
					char str_A[64] = {}, str_B[64] = {};
					str[i] = ' ';
					for (j = 0; j < i; j++)
						str_A[j] = str[j];
					for (int k = i + 1, j = 0; k < strlen(str); j++, k++) {
						if (str[k] != '\'' && str[k] != ',' && str[k] != '\"' && str[k] != '.' && str[k] != '-' && str[i] != '(' && str[i] != ')' && str[i] != ':')
							str_B[j] = str[k];
						else
							break;
					}

					if (search(key_comput(str_A)) != NULL || search(key_comput(str_B)) != NULL) {
						success23++;
					}
					else {
						failure23++;
					}
					flag23 = 1;
					break;
				}
			}
			if (flag23 == 0) {
				if (search(key_comput(str))) {
					success23++;
				}
				else {
					failure23++;
				}
			}
		}
		QueryPerformanceCounter(&t6);
		printf("\n查詢 TestFile23.txt：成功數: %d  失敗數: %d \n", success23, failure23);
		float the_success_rate23 = (float)success23 / (success23 + failure23) * 100.0;
		float the_failure_rate23 = (float)failure23 / (success23 + failure23) * 100.0;
		printf("\n成功率：%f %%\n", the_success_rate23);
		printf("失敗率：%f %%\n", the_failure_rate23);
		printf("總時間: %lf 秒\n", (t6.QuadPart - t5.QuadPart) / (double)(ts.QuadPart));
		printf("/-------------------------------------------------------------/\n");
	}
	else
	{
		printf("請重新輸入");
		exit(0);
	}

	int flagA = 1;
	while (flagA) {
		printf("/-------------------------------------------------------------/\n");
		printf("[1] 插入(Insertion)\t[2] 刪除(Deletion)\n");
		printf("[3] 搜尋(Searching)\t[4] 離開(Exit)\n");
		printf("請輸入您選擇的數字:");
		scanf("%d", &the_index_character);
		getchar();
		switch (the_index_character) {
		case 1:
			printf("欲插入的文字:");
			fgets(str, 100, stdin);
			insert(key_comput(str), str);
			break;
		case 2:
			printf("欲刪除的文字:");
			fgets(str, 100, stdin);
			item = search(key_comput(str));
			deleteItem(item);
			break;
		case 3:
			printf("欲搜尋的文字:");
			fgets(str, 100, stdin);
			item = search(key_comput(str));
			if (item != NULL) {
				printf("Element found:%s\n", str);
			}
			else {
				printf("Element not found\n");
			}
			break;
		case 4:
			flagA--;
		default:
			printf("輸入錯誤，請重新輸入。\n\n");
			break;
		}
	}



	return 0;
	system("PAUSE");
}
