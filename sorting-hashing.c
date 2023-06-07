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

/* 필요에 따라 함수 추가 가능 */
int initialize(int **a);
int freeArray(int *a);
void printArray(int *a);

int selectionSort(int *a);
int insertionSort(int *a);
int bubbleSort(int *a);
int shellSort(int *a);
/* recursive function으로 구현 */
int quickSort(int *a, int n);


/* hash code generator, key % MAX_HASH_TABLE_SIZE */
int hashCode(int key);

/* array a에대 한 hash table을 만든다. */
int hashing(int *a, int **ht);

/* hash table에서 key를 찾아 hash table의 index return */
int search(int *ht, int key);


int main()
{
	char command;			//커맨드
	int *array = NULL;		//배열
	int *hashtable = NULL;	//해시
	int key = -1;			//키
	int index = -1;			//인덱스

	srand(time(NULL));
		printf("---------------------[강은혜 2022041047]--------------------\n");

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

int initialize(int** a)	//a의 배열을 초기화
{
	int *temp = NULL;										//템프

	/* array가 NULL인 경우 메모리 할당 */
	if(*a == NULL) {										//a가 비어있다면
		temp = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);	//temp에 배열 할당
		*a = temp;  /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
	} else
		temp = *a;											//a가 비어있지 않다면, a가 가리키는 배열을 가리키는포인터를 temp로 전달

	/* 랜덤값을 배열의 값으로 저장 */
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		temp[i] = rand() % MAX_ARRAY_SIZE;

	return 0;
}

int freeArray(int *a)//동적배열 할당 해제
{
	if(a != NULL)
		free(a);
	return 0;
}

void printArray(int *a)//배열 출력
{
	if (a == NULL) {
		printf("nothing to print.\n");
		return;
	}
	//포인터를 배열처럼 쓰기 가능
	//인덱스
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		printf("a[%02d] ", i);
	printf("\n");
	//키
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		printf("%5d ", a[i]);
	printf("\n");
}


int selectionSort(int *a)//선택정렬
{
	int min;		//최소 키값
	int minindex;	//최소 키가 있는 인덱스값
	int i, j;		//for문 카운트

	printf("Selection Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);	//배열 출력


	//맨앞의 인덱스의 값을 최소값에 넣고 
	for (i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		minindex = i;
		min = a[i];
		//그 뒤의 값과 비교하며 더 작은 값이 등장하면 교환 
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

int insertionSort(int *a)//삽입정렬
{
	int i, j, t;

	printf("Insertion Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	//배열을 쭉 훑되,
	for(i = 1; i < MAX_ARRAY_SIZE; i++)
	{
		t = a[i];
		j = i;
		//현재 인덱스의 앞을 훑으며 삽입할 공간 탐색후
		while (a[j-1] > t && j > 0)
		{
			a[j] = a[j-1];
			j--;
		}
		//삽입
		a[j] = t;
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);

	return 0;
}

int bubbleSort(int *a)//버블 정렬
{
	int i, j, t;

	printf("Bubble Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	for(i = 0; i < MAX_ARRAY_SIZE; i++)//한 배열을 훑되,
	{
		for (j = 0; j < MAX_ARRAY_SIZE; j++)//한 원소마다 버블 정렬하며 이동
		{
			//이전,현재 원소 비교하며
			if (a[j-1] > a[j])//이전원소가 크면 교체
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

int shellSort(int *a)//쉘 정렬
{
	int i, j, k, h, v;

	printf("Shell Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);
	

	for (h = MAX_ARRAY_SIZE/2; h > 0; h /= 2)	//2의 기하급수로 비교할 인덱스의 간격을 줄여나감...(8-4-2-0 )
	{
		for (i = 0; i < h; i++)					//i는 배열의 원소들을 한번씩 훑기 위한 인덱스
		{
			for(j = i + h; j < MAX_ARRAY_SIZE; j += h)//j는 일정한 거리로 떨어진 인덱스를 점프하며 순회
			{
				v = a[j];	//j번째 값 저장
				k = j;		//인덱스
				while (k > h-1 && a[k-h] > v)//h가 0이 아니고, 일정한 거리 앞에 있는 수가 뒤에있는 수보다 크면
				{
					a[k] = a[k-h];	//바꾸기
					k -= h;			//k를 h만큼 줄임
					//작은수가 계속 앞으로 갈수있게끔 반복
				}
				a[k] = v;//종착에 본래k 넣어주기
			}
		}
	}
	printf("----------------------------------------------------------------\n");
	printArray(a);

	return 0;
}

int quickSort(int *a, int n)//퀵 정렬
{
	int v, t;
	int i, j;

	if (n > 1)
	{
		v = a[n-1];//v=피봇
		i = -1;		//left
		j = n - 1;	//right

		while(1)
		{
			while(a[++i] < v);//피봇보다 큰 수가 나올때까지, left 오른쪽으로 이동
			while(a[--j] > v);//피봇보다 작은 수가 나올때까지, right 왼쪽으로 이동

			if (i >= j) break;//이미 피봇의 좌우가 피봇값을 중심으로 분류되어 있다면, i=v,j=v-1 일것. break
			//아니면 교환
			t = a[i];
			a[i] = a[j];
			a[j] = t;
		}


		t = a[i];
		a[i] = a[n-1];//피봇이 있던자리에 우측 끝값을,
		a[n-1] = t;//끝에 피봇이었던 값을 넣음

		quickSort(a, i);//피봇의 좌측
		quickSort(a+i+1, n-i-1);//피봇의 우측
	}


	return 0;
}

int hashCode(int key) {//해시
   return key % MAX_HASH_TABLE_SIZE;//해시 코드
}

int hashing(int *a, int **ht)//
{
	int *hashtable = NULL;

	/* hash table이 NULL인 경우 메모리 할당 */
	if(*ht == NULL) {
		hashtable = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*ht = hashtable;  /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
	} else {
		hashtable = *ht;	/* hash table이 NULL이 아닌경우, table 재활용, reset to -1 */
	}

	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
		hashtable[i] = -1;//해시테이블 초기화

	int key = -1;
	int hashcode = -1;
	int index = -1;
	for (int i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		key = a[i];
		hashcode = hashCode(key);//키 값에 따른 해시코드 가져오기

		if (hashtable[hashcode] == -1)//해시테이블이 비어있으면,
		{
			hashtable[hashcode] = key;//해시테이블에 키값 추가
		} else 	{

			index = hashcode;//해시코드 따라 인덱스

			while(hashtable[index] != -1)//비어있는 해시코드 따라
			{
				index = (++index) % MAX_HASH_TABLE_SIZE;//이동
			}
			hashtable[index] = key;//찾은뒤 넣기
		}
	}

	return 0;
}

int search(int *ht, int key)//해시코드 탐색
{
	int index = hashCode(key);//인덱스에 해시코드 넣기

	if(ht[index] == key)//있어야 할 곳에 있으면 인덱스 출력
		return index;

	while(ht[++index] != key)//없으면 탐색 후 출력
	{
		index = index % MAX_HASH_TABLE_SIZE;
	}
	return index;//인덱스를 리턴
}



