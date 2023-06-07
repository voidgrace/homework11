/*
 * sorting-hashing.c
 *
 *  Sorting & Hashing
 *  School of Computer Science at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ARRAY_SIZE			13	/* prime number */
#define MAX_HASH_TABLE_SIZE 	MAX_ARRAY_SIZE

/* �ʿ信 ���� �Լ� �߰� ���� */
int initialize(int **a);
int freeArray(int *a);
void printArray(int *a);

int selectionSort(int *a);
int insertionSort(int *a);
int bubbleSort(int *a);
int shellSort(int *a);
/* recursive function���� ���� */
int quickSort(int *a, int n);


/* hash code generator, key % MAX_HASH_TABLE_SIZE */
int hashCode(int key);

/* array a���� �� hash table�� �����. */
int hashing(int *a, int **ht);

/* hash table���� key�� ã�� hash table�� index return */
int search(int *ht, int key);


int main()
{
	char command;			//Ŀ�ǵ�
	int *array = NULL;		//�迭
	int *hashtable = NULL;	//�ؽ�
	int key = -1;			//Ű
	int index = -1;			//�ε���

	srand(time(NULL));
		printf("---------------------[������ 2022041047]--------------------\n");

	do{

		printf("----------------------------------------------------------------\n");
		printf("                        Sorting & Hashing                       \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize       = z           Quit             = q\n");
		printf(" Selection Sort   = s           Insertion Sort   = i\n");
		printf(" Bubble Sort      = b           Shell Sort       = l\n");
		printf(" Quick Sort       = k           Print Array      = p\n");
		printf(" Hashing          = h           Search(for Hash) = e\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initialize(&array);
			break;
		case 'q': case 'Q':
			freeArray(array);
			break;
		case 's': case 'S':
			selectionSort(array);
			break;
		case 'i': case 'I':
			insertionSort(array);
			break;
		case 'b': case 'B':
			bubbleSort(array);
			break;
		case 'l': case 'L':
			shellSort(array);
			break;
		case 'k': case 'K':
			printf("Quick Sort: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);
			quickSort(array, MAX_ARRAY_SIZE);
			printf("----------------------------------------------------------------\n");
			printArray(array);

			break;

		case 'h': case 'H':
			printf("Hashing: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);
			hashing(array, &hashtable);
			printArray(hashtable);
			break;

		case 'e': case 'E':
			printf("Your Key = ");
			scanf("%d", &key);
			printArray(hashtable);
			index = search(hashtable, key);
			printf("key = %d, index = %d,  hashtable[%d] = %d\n", key, index, index, hashtable[index]);
			break;

		case 'p': case 'P':
			printArray(array);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initialize(int** a)	//a�� �迭�� �ʱ�ȭ
{
	int *temp = NULL;										//����

	/* array�� NULL�� ��� �޸� �Ҵ� */
	if(*a == NULL) {										//a�� ����ִٸ�
		temp = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);	//temp�� �迭 �Ҵ�
		*a = temp;  /* �Ҵ�� �޸��� �ּҸ� ���� --> main���� �迭�� control �Ҽ� �ֵ��� ��*/
	} else
		temp = *a;											//a�� ������� �ʴٸ�, a�� ����Ű�� �迭�� ����Ű�������͸� temp�� ����

	/* �������� �迭�� ������ ���� */
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		temp[i] = rand() % MAX_ARRAY_SIZE;

	return 0;
}

int freeArray(int *a)//�����迭 �Ҵ� ����
{
	if(a != NULL)
		free(a);
	return 0;
}

void printArray(int *a)//�迭 ���
{
	if (a == NULL) {
		printf("nothing to print.\n");
		return;
	}
	//�����͸� �迭ó�� ���� ����
	//�ε���
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		printf("a[%02d] ", i);
	printf("\n");
	//Ű
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		printf("%5d ", a[i]);
	printf("\n");
}


int selectionSort(int *a)//��������
{
	int min;		//�ּ� Ű��
	int minindex;	//�ּ� Ű�� �ִ� �ε�����
	int i, j;		//for�� ī��Ʈ

	printf("Selection Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);	//�迭 ���


	//�Ǿ��� �ε����� ���� �ּҰ��� �ְ� 
	for (i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		minindex = i;
		min = a[i];
		//�� ���� ���� ���ϸ� �� ���� ���� �����ϸ� ��ȯ 
		for(j = i+1; j < MAX_ARRAY_SIZE; j++)
		{
			if (min > a[j])
			{
				min = a[j];
				minindex = j;
			}
		}
		a[minindex] = a[i];
		a[i] = min;
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);
	return 0;
}

int insertionSort(int *a)//��������
{
	int i, j, t;

	printf("Insertion Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	//�迭�� �� �ȵ�,
	for(i = 1; i < MAX_ARRAY_SIZE; i++)
	{
		t = a[i];
		j = i;
		//���� �ε����� ���� ������ ������ ���� Ž����
		while (a[j-1] > t && j > 0)
		{
			a[j] = a[j-1];
			j--;
		}
		//����
		a[j] = t;
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);

	return 0;
}

int bubbleSort(int *a)//���� ����
{
	int i, j, t;

	printf("Bubble Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	for(i = 0; i < MAX_ARRAY_SIZE; i++)//�� �迭�� �ȵ�,
	{
		for (j = 0; j < MAX_ARRAY_SIZE; j++)//�� ���Ҹ��� ���� �����ϸ� �̵�
		{
			//����,���� ���� ���ϸ�
			if (a[j-1] > a[j])//�������Ұ� ũ�� ��ü
			{
				t = a[j-1];
				a[j-1] = a[j];
				a[j] = t;
			}
		}
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);

	return 0;
}

int shellSort(int *a)//�� ����
{
	int i, j, k, h, v;

	printf("Shell Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);
	

	for (h = MAX_ARRAY_SIZE/2; h > 0; h /= 2)	//2�� ���ϱ޼��� ���� �ε����� ������ �ٿ�����...(8-4-2-0 )
	{
		for (i = 0; i < h; i++)					//i�� �迭�� ���ҵ��� �ѹ��� �ȱ� ���� �ε���
		{
			for(j = i + h; j < MAX_ARRAY_SIZE; j += h)//j�� ������ �Ÿ��� ������ �ε����� �����ϸ� ��ȸ
			{
				v = a[j];	//j��° �� ����
				k = j;		//�ε���
				while (k > h-1 && a[k-h] > v)//h�� 0�� �ƴϰ�, ������ �Ÿ� �տ� �ִ� ���� �ڿ��ִ� ������ ũ��
				{
					a[k] = a[k-h];	//�ٲٱ�
					k -= h;			//k�� h��ŭ ����
					//�������� ��� ������ �����ְԲ� �ݺ�
				}
				a[k] = v;//������ ����k �־��ֱ�
			}
		}
	}
	printf("----------------------------------------------------------------\n");
	printArray(a);

	return 0;
}

int quickSort(int *a, int n)//�� ����
{
	int v, t;
	int i, j;

	if (n > 1)
	{
		v = a[n-1];//v=�Ǻ�
		i = -1;		//left
		j = n - 1;	//right

		while(1)
		{
			while(a[++i] < v);//�Ǻ����� ū ���� ���ö�����, left ���������� �̵�
			while(a[--j] > v);//�Ǻ����� ���� ���� ���ö�����, right �������� �̵�

			if (i >= j) break;//�̹� �Ǻ��� �¿찡 �Ǻ����� �߽����� �з��Ǿ� �ִٸ�, i=v,j=v-1 �ϰ�. break
			//�ƴϸ� ��ȯ
			t = a[i];
			a[i] = a[j];
			a[j] = t;
		}


		t = a[i];
		a[i] = a[n-1];//�Ǻ��� �ִ��ڸ��� ���� ������,
		a[n-1] = t;//���� �Ǻ��̾��� ���� ����

		quickSort(a, i);//�Ǻ��� ����
		quickSort(a+i+1, n-i-1);//�Ǻ��� ����
	}


	return 0;
}

int hashCode(int key) {//�ؽ�
   return key % MAX_HASH_TABLE_SIZE;//�ؽ� �ڵ�
}

int hashing(int *a, int **ht)//
{
	int *hashtable = NULL;

	/* hash table�� NULL�� ��� �޸� �Ҵ� */
	if(*ht == NULL) {
		hashtable = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*ht = hashtable;  /* �Ҵ�� �޸��� �ּҸ� ���� --> main���� �迭�� control �Ҽ� �ֵ��� ��*/
	} else {
		hashtable = *ht;	/* hash table�� NULL�� �ƴѰ��, table ��Ȱ��, reset to -1 */
	}

	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
		hashtable[i] = -1;//�ؽ����̺� �ʱ�ȭ

	int key = -1;
	int hashcode = -1;
	int index = -1;
	for (int i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		key = a[i];
		hashcode = hashCode(key);//Ű ���� ���� �ؽ��ڵ� ��������

		if (hashtable[hashcode] == -1)//�ؽ����̺��� ���������,
		{
			hashtable[hashcode] = key;//�ؽ����̺� Ű�� �߰�
		} else 	{

			index = hashcode;//�ؽ��ڵ� ���� �ε���

			while(hashtable[index] != -1)//����ִ� �ؽ��ڵ� ����
			{
				index = (++index) % MAX_HASH_TABLE_SIZE;//�̵�
			}
			hashtable[index] = key;//ã���� �ֱ�
		}
	}

	return 0;
}

int search(int *ht, int key)//�ؽ��ڵ� Ž��
{
	int index = hashCode(key);//�ε����� �ؽ��ڵ� �ֱ�

	if(ht[index] == key)//�־�� �� ���� ������ �ε��� ���
		return index;

	while(ht[++index] != key)//������ Ž�� �� ���
	{
		index = index % MAX_HASH_TABLE_SIZE;
	}
	return index;//�ε����� ����
}



