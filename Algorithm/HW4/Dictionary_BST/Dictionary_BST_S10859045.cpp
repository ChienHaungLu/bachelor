#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <time.h>       
#include <windows.h>


using namespace std;
struct BSTnode {
	char word[128];
	struct BSTnode* left, * right;
};

struct BSTnode* the_root = NULL;

struct BSTnode* Bulid_The_Node(char* word) { //建立節點
	struct BSTnode* the_newNode;
	the_newNode = (struct BSTnode*)malloc(sizeof(struct BSTnode));
	strcpy(the_newNode->word, word);
	the_newNode->left = the_newNode->right = NULL;
	return the_newNode;
}

void Binary_Search_Tree_Insertion(char* word) { //節點搜尋
	struct BSTnode* parent = NULL, * current = NULL, * the_newNode = NULL;
	int the_res_variable = 0;
	if (!the_root) {
		the_root = Bulid_The_Node(word);
		return;
	}
	for (current = the_root; current != NULL;
		current = (the_res_variable > 0) ? current->right : current->left) {
		the_res_variable = strcmp(word, current->word);

		parent = current;
	}
	the_newNode = Bulid_The_Node(word);
	the_res_variable > 0 ? (parent->right = the_newNode) : (parent->left = the_newNode);
	return;
}

void Binary_Search_Tree_Deleteion(char* the_string) { ///節點刪除
	struct BSTnode* parent = NULL, * current = NULL, * the_variable = NULL;
	int flag = 0, the_res_variable = 0;
	if (!the_root) {
		printf("BST is not present!!\n");
		return;
	}
	current = the_root;
	while (1) {
		the_res_variable = strcmp(current->word, the_string);
		if (the_res_variable == 0)
			break;
		flag = the_res_variable;
		parent = current;
		current = (the_res_variable > 0) ? current->left : current->right;
		if (current == NULL)
			return;
	}
	/* 刪除葉節點 */
	if (current->right == NULL) {
		if (current == the_root && current->left == NULL) {
			free(current);
			the_root = NULL;
			return;
		}
		else if (current == the_root) {
			the_root = current->left;
			free(current);
			return;
		}

		flag > 0 ? (parent->left = current->left) :
			(parent->right = current->left);
	}
	else {
		/* 刪除子樹只有一個小孩的節點 */
		the_variable = current->right;
		if (!the_variable->left) {
			the_variable->left = current->left;
			if (current == the_root) {
				the_root = the_variable;
				free(current);
				return;
			}
			flag > 0 ? (parent->left = the_variable) :
				(parent->right = the_variable);
		}
		else {
			/* 刪除子樹有兩個小孩的節點 */
			struct BSTnode* successor = NULL;
			while (1) {
				successor = the_variable->left;
				if (!successor->left)
					break;
				the_variable = successor;
			}
			the_variable->left = successor->right;
			successor->left = current->left;
			successor->right = current->right;
			if (current == the_root) {
				the_root = successor;
				free(current);
				return;
			}
			(flag > 0) ? (parent->left = successor) :
				(parent->right = successor);
		}
	}
	free(current);
	return;
}

int Binary_Search_Tree_Searching(BSTnode* the_root, char* the_string) { //搜尋用BST所建立的字典

	struct BSTnode* the_variable = NULL;
	int flag = 0, the_res_variable = 0;
	if (the_root == NULL) {
		printf("BST不存在!!請先建立一棵BST後再嘗試搜尋\n");
		return 0;
	}
	the_variable = the_root;
	while (the_variable) {
		the_res_variable = strcmp(the_variable->word, the_string);
		if ((the_res_variable) == 0) {
			printf("Token&Words: %s 找到\n", the_string);
			flag = 1;
			return 1;
		}
		the_variable = (the_res_variable > 0) ? the_variable->left : the_variable->right;
	}
	if (!flag) {
		printf("Token&Words: %s 找不到 \n", the_string);
		return 0;
	}
}

//主函式
int main() {
	int the_index_character, index;
	char the_string[128];
	printf("TestFile1.txt:[1]  TestFile2.txt:[2] 使用何者檔案當作字典?\n");
	printf("請輸入1或2: ");
	scanf("%d", &index);
	printf("\n/-------------------------------------------------------------/\n");

	//選擇使用的txt檔案來建立字典庫
	if (index == 1)
	{
		FILE* File1;
		File1 = fopen("TestFile1.txt", "r");
		LARGE_INTEGER t1, t2, t3, t4, t5, t6, ts, ts1, ts2;
		QueryPerformanceFrequency(&ts);


		QueryPerformanceCounter(&t1);

		/*-----------------------------建立TestFile1.txt字典---------------------------*/
		while (fscanf(File1, "%s", the_string) != EOF) {

			int flag1 = 0;
			for (int i = 0; i < strlen(the_string); i++) {
				int j = 0;
				if (the_string[i] == '\'' || the_string[i] == ',' || the_string[i] == '\"' || the_string[i] == '.' || the_string[i] == '-' || the_string[i] == '(' || the_string[i] == ')' || the_string[i] == ':') {
					char the_str_A[64] = {}, the_str_B[64] = {};
					the_string[i] = ' ';
					for (j = 0; j < i; j++)
						the_str_A[j] = the_string[j];
					for (int k = i + 1, j = 0; k < strlen(the_string); j++, k++) {
						if (the_string[k] != '\'' && the_string[k] != ',' && the_string[k] != '\"' && the_string[k] != '.' && the_string[k] != '-' && the_string[i] != '(' && the_string[i] != ')' && the_string[i] != ':')
							the_str_B[j] = the_string[k];
						else
							break;
					}
					Binary_Search_Tree_Insertion(the_str_A);

					Binary_Search_Tree_Insertion(the_str_B);

					flag1 = 1;
					break;
				}
			}
			if (flag1 == 0) {
				Binary_Search_Tree_Insertion(the_string);
			}
		}
		/*----------------------------------------------------------*/
		FILE* File11;
		File11 = fopen("TestFile11.txt", "r");
		/*-----------------------------查詢TestFile11.txt檔案---------------------------*/
		int the_success = 0.0, the_failure = 0.0;
		while (fscanf(File11, "%s", the_string) != EOF) {
			int flag11 = 0;

			for (int i = 0; i < strlen(the_string); i++) {
				int j = 0;
				if (the_string[i] == '\'' || the_string[i] == ',' || the_string[i] == '\"' || the_string[i] == '.' || the_string[i] == '-' || the_string[i] == '(' || the_string[i] == ')' || the_string[i] == ':') {
					char the_str_A[64] = {}, the_str_B[64] = {};
					the_string[i] = ' ';
					for (j = 0; j < i; j++)
						the_str_A[j] = the_string[j];
					for (int k = i + 1, j = 0; k < strlen(the_string); j++, k++) {
						if (the_string[k] != '\'' && the_string[k] != ',' && the_string[k] != '\"' && the_string[k] != '.' && the_string[k] != '-' && the_string[i] != '(' && the_string[i] != ')' && the_string[i] != ':')
							the_str_B[j] = the_string[k];
						else
							break;
					}
					if (Binary_Search_Tree_Searching(the_root, the_str_A) || Binary_Search_Tree_Searching(the_root, the_str_B)) {
						the_success++;
					}
					else {
						the_failure++;
					}

					flag11 = 1;
					break;
				}
			}
			if (flag11 == 0) {
				if (Binary_Search_Tree_Searching(the_root, the_string)) {
					the_success++;
				}
				else {
					the_failure++;
				}
			}
		}
		QueryPerformanceCounter(&t2);
		printf("\n查詢 TestFile11.txt：成功數: %d  失敗數: %d \n", the_success, the_failure);
		float the_success_rate = (float)the_success / (the_success + the_failure) * 100.0;
		float the_fail_rate = (float)the_failure / (the_success + the_failure) * 100.0;
		printf("\n成功率：%f %%\n", the_success_rate);
		printf("失敗率：%f %%\n", the_fail_rate);
		printf("總時間: %lf 秒\n", (t2.QuadPart - t1.QuadPart) / (double)(ts.QuadPart));
		printf("/-------------------------------------------------------------/\n");


		QueryPerformanceFrequency(&ts1);
		QueryPerformanceCounter(&t3);
		FILE* File12;
		File12 = fopen("TestFile12.txt", "r");
		/*-----------------------------查詢TestFile12.txt檔案---------------------------*/
		int the_success1 = 0.0, the_failure1 = 0.0;
		while (fscanf(File12, "%s", the_string) != EOF) {
			int flag12 = 0;

			for (int i = 0; i < strlen(the_string); i++) {
				int j = 0;
				if (the_string[i] == '\'' || the_string[i] == ',' || the_string[i] == '\"' || the_string[i] == '.' || the_string[i] == '-' || the_string[i] == '(' || the_string[i] == ')' || the_string[i] == ':') {
					char the_str_A[64] = {}, the_str_B[64] = {};
					the_string[i] = ' ';
					for (j = 0; j < i; j++)
						the_str_A[j] = the_string[j];
					for (int k = i + 1, j = 0; k < strlen(the_string); j++, k++) {
						if (the_string[k] != '\'' && the_string[k] != ',' && the_string[k] != '\"' && the_string[k] != '.' && the_string[k] != '-' && the_string[i] != '(' && the_string[i] != ')' && the_string[i] != ':')
							the_str_B[j] = the_string[k];
						else
							break;
					}
					if (Binary_Search_Tree_Searching(the_root, the_str_A) || Binary_Search_Tree_Searching(the_root, the_str_B)) {
						the_success1++;
					}
					else {
						the_failure1++;
					}

					flag12 = 1;
					break;
				}
			}
			if (flag12 == 0) {
				if (Binary_Search_Tree_Searching(the_root, the_string)) {
					the_success1++;
				}
				else {
					the_failure1++;
				}
			}
		}
		QueryPerformanceCounter(&t4);

		printf("\n查詢 TestFile12.txt：成功數: %d  失敗數: %d \n", the_success1, the_failure1);
		float the_success_rate1 = (float)the_success1 / (the_success1 + the_failure1) * 100.0;
		float the_fail_rate1 = (float)the_failure1 / (the_success1 + the_failure1) * 100.0;
		printf("\n成功率：%f %%\n", the_success_rate1);
		printf("失敗率：%f %%\n", the_fail_rate1);
		printf("總時間: %lf 秒\n", (t4.QuadPart - t3.QuadPart) / (double)(ts1.QuadPart));
		printf("/-------------------------------------------------------------/\n");


		QueryPerformanceFrequency(&ts2);
		QueryPerformanceCounter(&t5);
		FILE* File13;
		File13 = fopen("TestFile13.txt", "r");
		/*-----------------------------查詢TestFile13.txt檔案---------------------------*/
		int the_success2 = 0.0, the_failure2 = 0.0;
		while (fscanf(File13, "%s", the_string) != EOF) {
			int flag13 = 0;

			for (int i = 0; i < strlen(the_string); i++) {
				int j = 0;
				if (the_string[i] == '\'' || the_string[i] == ',' || the_string[i] == '\"' || the_string[i] == '.' || the_string[i] == '-' || the_string[i] == '(' || the_string[i] == ')' || the_string[i] == ':') {
					char the_str_A[64] = {}, the_str_B[64] = {};
					the_string[i] = ' ';
					for (j = 0; j < i; j++)
						the_str_A[j] = the_string[j];
					for (int k = i + 1, j = 0; k < strlen(the_string); j++, k++) {
						if (the_string[k] != '\'' && the_string[k] != ',' && the_string[k] != '\"' && the_string[k] != '.' && the_string[k] != '-' && the_string[i] != '(' && the_string[i] != ')' && the_string[i] != ':')
							the_str_B[j] = the_string[k];
						else
							break;
					}
					if (Binary_Search_Tree_Searching(the_root, the_str_A) || Binary_Search_Tree_Searching(the_root, the_str_B)) {
						the_success2++;
					}
					else {
						the_failure2++;
					}

					flag13 = 1;
					break;
				}
			}
			if (flag13 == 0) {
				if (Binary_Search_Tree_Searching(the_root, the_string)) {
					the_success2++;
				}
				else {
					the_failure2++;
				}
			}
		}
		QueryPerformanceCounter(&t6);

		printf("\n查詢 TestFile13.txt：成功數: %d  失敗數: %d \n", the_success2, the_failure2);
		float the_success_rate2 = (float)the_success2 / (the_success2 + the_failure2) * 100.0;
		float the_fail_rate2 = (float)the_failure2 / (the_success2 + the_failure2) * 100.0;
		printf("\n成功率：%f %%\n", the_success_rate2);
		printf("失敗率：%f %%\n", the_fail_rate2);
		printf("總時間: %lf 秒\n", (t6.QuadPart - t5.QuadPart) / (double)(ts2.QuadPart));
	}

	else if (index == 2)
	{
		FILE* File2;
		File2 = fopen("TestFile2.txt", "r");
		LARGE_INTEGER t1, t2, t3, t4, t5, t6, ts, ts1, ts2;
		QueryPerformanceFrequency(&ts);


		QueryPerformanceCounter(&t1);

		/*-----------------------------建立TestFile2.txt字典---------------------------*/
		while (fscanf(File2, "%s", the_string) != EOF) {

			int flag2 = 0;
			for (int i = 0; i < strlen(the_string); i++) {
				int j = 0;
				if (the_string[i] == '\'' || the_string[i] == ',' || the_string[i] == '\"' || the_string[i] == '.' || the_string[i] == '-' || the_string[i] == '(' || the_string[i] == ')' || the_string[i] == ':') {
					char the_str_A[64] = {}, the_str_B[64] = {};
					the_string[i] = ' ';
					for (j = 0; j < i; j++)
						the_str_A[j] = the_string[j];
					for (int k = i + 1, j = 0; k < strlen(the_string); j++, k++) {
						if (the_string[k] != '\'' && the_string[k] != ',' && the_string[k] != '\"' && the_string[k] != '.' && the_string[k] != '-' && the_string[i] != '(' && the_string[i] != ')' && the_string[i] != ':')
							the_str_B[j] = the_string[k];
						else
							break;
					}
					Binary_Search_Tree_Insertion(the_str_A);

					Binary_Search_Tree_Insertion(the_str_B);

					flag2 = 1;
					break;
				}
			}
			if (flag2 == 0) {
				Binary_Search_Tree_Insertion(the_string);
			}
		}


		FILE* File21;
		File21 = fopen("TestFile21.txt", "r");
		/*-----------------------------查詢TestFile21.txt檔案---------------------------*/
		int the_success = 0.0, the_failure = 0.0;
		while (fscanf(File21, "%s", the_string) != EOF) {

			int flag21 = 0;

			for (int i = 0; i < strlen(the_string); i++) {
				int j = 0;
				if (the_string[i] == '\'' || the_string[i] == ',' || the_string[i] == '\"' || the_string[i] == '.' || the_string[i] == '-' || the_string[i] == '(' || the_string[i] == ')' || the_string[i] == ':') {
					char the_str_A[64] = {}, the_str_B[64] = {};
					the_string[i] = ' ';
					for (j = 0; j < i; j++)
						the_str_A[j] = the_string[j];
					for (int k = i + 1, j = 0; k < strlen(the_string); j++, k++) {
						if (the_string[k] != '\'' && the_string[k] != ',' && the_string[k] != '\"' && the_string[k] != '.' && the_string[k] != '-' && the_string[i] != '(' && the_string[i] != ')' && the_string[i] != ':')
							the_str_B[j] = the_string[k];
						else
							break;
					}
					if (Binary_Search_Tree_Searching(the_root, the_str_A) || Binary_Search_Tree_Searching(the_root, the_str_B)) {
						the_success++;
					}
					else {
						the_failure++;
					}

					flag21 = 1;
					break;
				}
			}
			if (flag21 == 0) {
				if (Binary_Search_Tree_Searching(the_root, the_string)) {
					the_success++;
				}
				else {
					the_failure++;
				}
			}
		}
		QueryPerformanceCounter(&t2);
		printf("\n查詢 TestFile21.txt：成功數: %d  失敗數: %d \n", the_success, the_failure);
		float the_success_rate = (float)the_success / (the_success + the_failure) * 100.0;
		float the_fail_rate = (float)the_failure / (the_success + the_failure) * 100.0;
		printf("\n成功率：%f %%\n", the_success_rate);
		printf("失敗率：%f %%\n", the_fail_rate);
		printf("總時間: %lf 秒\n", (t2.QuadPart - t1.QuadPart) / (double)(ts.QuadPart));
		printf("/-------------------------------------------------------------/\n");
		


		QueryPerformanceFrequency(&ts1);
		QueryPerformanceCounter(&t3);
		FILE* File22;
		File22 = fopen("TestFile22.txt", "r");
		/*-----------------------------查詢TestFile22.txt檔案---------------------------*/
		int the_success1 = 0.0, the_failure1 = 0.0;
		while (fscanf(File22, "%s", the_string) != EOF) {
			int flag = 0;

			for (int i = 0; i < strlen(the_string); i++) {
				int j = 0;
				if (the_string[i] == '\'' || the_string[i] == ',' || the_string[i] == '\"' || the_string[i] == '.' || the_string[i] == '-' || the_string[i] == '(' || the_string[i] == ')' || the_string[i] == ':') {
					char the_str_A[64] = {}, the_str_B[64] = {};
					the_string[i] = ' ';
					for (j = 0; j < i; j++)
						the_str_A[j] = the_string[j];
					for (int k = i + 1, j = 0; k < strlen(the_string); j++, k++) {
						if (the_string[k] != '\'' && the_string[k] != ',' && the_string[k] != '\"' && the_string[k] != '.' && the_string[k] != '-' && the_string[i] != '(' && the_string[i] != ')' && the_string[i] != ':')
							the_str_B[j] = the_string[k];
						else
							break;
					}
					if (Binary_Search_Tree_Searching(the_root, the_str_A) || Binary_Search_Tree_Searching(the_root, the_str_B)) {
						the_success1++;
					}
					else {
						the_failure1++;
					}

					flag = 1;
					break;
				}
			}
			if (flag == 0) {
				if (Binary_Search_Tree_Searching(the_root, the_string)) {
					the_success1++;
				}
				else {
					the_failure1++;
				}
			}
		}
		QueryPerformanceCounter(&t4);

		printf("\n查詢 TestFile22.txt：成功數: %d  失敗數: %d \n", the_success1, the_failure1);
		float the_success_rate1 = (float)the_success1 / (the_success1 + the_failure1) * 100.0;
		float the_fail_rate1 = (float)the_failure1 / (the_success1 + the_failure1) * 100.0;
		printf("\n成功率：%f %%\n", the_success_rate1);
		printf("失敗率：%f %%\n", the_fail_rate1);
		printf("總時間: %lf 秒\n", (t4.QuadPart - t3.QuadPart) / (double)(ts1.QuadPart));
		printf("/-------------------------------------------------------------/\n");


		QueryPerformanceFrequency(&ts2);
		QueryPerformanceCounter(&t5);
		FILE* File23;
		File23 = fopen("TestFile23.txt", "r");
		/*-----------------------------查詢TestFile23.txt檔案---------------------------*/
		int the_success2 = 0.0, the_failure2 = 0.0;
		while (fscanf(File23, "%s", the_string) != EOF) {
			int flag = 0;

			for (int i = 0; i < strlen(the_string); i++) {
				int j = 0;
				if (the_string[i] == '\'' || the_string[i] == ',' || the_string[i] == '\"' || the_string[i] == '.' || the_string[i] == '-' || the_string[i] == '(' || the_string[i] == ')' || the_string[i] == ':') {
					char the_str_A[64] = {}, the_str_B[64] = {};
					the_string[i] = ' ';
					for (j = 0; j < i; j++)
						the_str_A[j] = the_string[j];
					for (int k = i + 1, j = 0; k < strlen(the_string); j++, k++) {
						if (the_string[k] != '\'' && the_string[k] != ',' && the_string[k] != '\"' && the_string[k] != '.' && the_string[k] != '-' && the_string[i] != '(' && the_string[i] != ')' && the_string[i] != ':')
							the_str_B[j] = the_string[k];
						else
							break;
					}
					if (Binary_Search_Tree_Searching(the_root, the_str_A) || Binary_Search_Tree_Searching(the_root, the_str_B)) {
						the_success2++;
					}
					else {
						the_failure2++;
					}

					flag = 1;
					break;
				}
			}
			if (flag == 0) {
				if (Binary_Search_Tree_Searching(the_root, the_string)) {
					the_success2++;
				}
				else {
					the_failure2++;
				}
			}
		}
		QueryPerformanceCounter(&t6);

		printf("\n查詢 TestFile23.txt：成功數: %d  失敗數: %d \n", the_success2, the_failure2);
		float the_success_rate2 = (float)the_success2 / (the_success2 + the_failure2) * 100.0;
		float the_fail_rate2 = (float)the_failure2 / (the_success2 + the_failure2) * 100.0;
		printf("\n成功率：%f %%\n", the_success_rate2);
		printf("失敗率：%f %%\n", the_fail_rate2);
		printf("總時間: %lf 秒\n", (t6.QuadPart - t5.QuadPart) / (double)(ts2.QuadPart));
	}

	else
	{
		printf("請重新輸入\n");
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
			fgets(the_string, 100, stdin);
			Binary_Search_Tree_Insertion(the_string);

			break;
		case 2:
			printf("欲刪除的文字:");
			fgets(the_string, 100, stdin);
			Binary_Search_Tree_Deleteion(the_string);
			break;
		case 3:
			printf("欲搜尋的文字:");
			fgets(the_string, 100, stdin);
			Binary_Search_Tree_Searching(the_root, the_string);
			break;
		case 4:
			flagA--;
			break;
		default:
			printf("輸入錯誤，請重新輸入。\n\n");
			break;
		}
	}

	system("pause");
	return 0;
}
