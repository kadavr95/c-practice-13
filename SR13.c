//Самостоятельная работа 13. Вариант 1. Яскович Дмитрий (T02-01c). Dimini Inc. (c)2013
#include <stdio.h>//подключение библиотек
#include <stdlib.h>
#include <math.h>
#include <time.h>

int filling(int low, int up, int qty, int *array); //прототипы функций
int output(int qty, int *array);
int null(int qty,int *array);
int maximum(int qty, int *array, int *max);
int savetofile(int qty, int *array);
int readfromfile(int *qty, int *array);
int checkn(int qty, int nmax, int *n);
int replace(int n,int *array);
int checkposnum(int qty, int *pos, int *num);
int arrayinsert(int low, int up,int pos, int num, int *qty, int *array);
int arraycutoff(int pos, int num, int *qty, int *array);
int checksize(int *arraysize);
int sort(int qel, int *qas, int *qco, int *array);
int sort1(int qel, int *qas, int *qco, int *array);
int sortn(int qel, int *qas, int *qco, int *array);


int main(void)//главная функция
{
	int *array, arraysize,n,nmax,position,number,low,up,asgn=0,cmpr=0,asgn1=0,cmpr1=0,asgnn=0,cmprn=0;//определение переменных
	double etime,etime1,etimen;
	time_t start,finish;
	printf("Enter quantity of elements in array: ");//ввод количества элементов в массиве
	scanf("%d", &arraysize);
	checksize(&arraysize);
	array = malloc((n+1)*sizeof(int));//создание массива
	printf("Enter limits: ");//ввод пределов
	scanf("%d %d", &low,&up);
	if (low>up)
	{
		up=low-up;
		low=low-up;
		up=low+up;
	}
	filling(low,up,arraysize,array);//заполнеие массива
	savetofile(arraysize,array);//сохранение массива в файл
	readfromfile(&arraysize,array);//считывание массива из файла
	printf("Array\n",asgn);
  	output(arraysize,array);//вывод массива
	readfromfile(&arraysize,array);//считывание массива из файла
	start=clock();
	sort(arraysize, &asgn, &cmpr,array);//сортировка массива
	finish=clock();
	etime=(finish-start)/CLOCKS_PER_SEC;
	printf("Standart sorting\n",asgn);
	output(arraysize,array);//вывод массива
	printf("Quantity of assignments: %d\n",asgn);
	printf("Quantity of comparisons: %d\n\n",cmpr);
	readfromfile(&arraysize,array);//считывание массива из файла
	start=clock();
	sort1(arraysize, &asgn1, &cmpr1,array);//сортировка массива
	finish=clock();
	etime1=(finish-start)/CLOCKS_PER_SEC;
	printf("Improved sort\n",asgn);
	output(arraysize,array);//вывод массива
	printf("Quantity of assignments: %d\n",asgn1);
	printf("Quantity of comparisons: %d\n\n",cmpr1);
	readfromfile(&arraysize,array);//считывание массива из файла
	start=clock();
	sortn(arraysize, &asgnn, &cmprn,array);//сортировка массива
	finish=clock();
	etimen=(finish-start)/CLOCKS_PER_SEC;
	printf("Improved+\n",asgn);
	output(arraysize,array);//вывод массива
	printf("Quantity of assignments: %d\n",asgnn);
	printf("Quantity of comparisons: %d\n\n",cmprn);
	printf("Method       |  Standart  |  Improved  |  Improved+ |\n");
	printf("Assignments  | %10d | %10d | %10d |\n",asgn,asgn1,asgnn);
	printf("Comparisons  | %10d | %10d | %10d |\n",cmpr,cmpr1,cmprn);
	printf("Elapsed time | %10.3lf | %10.3lf | %10.3lf |\n",etime,etime1,etimen);
	fflush(stdin);//ожидание действий пользователя
	getchar();
	return 0;
}

int filling(int low, int up, int qty, int *array)//заполнение массива
{
	int i;//определение переменных
	int stime;
	long int ltime;
	ltime=time(NULL);//создание случайной последовательности
	stime=(unsigned) ltime/2;
	srand(stime);
	for (i = 1; i <=qty ; i++)//заполнение массива
	{
		array[i]=low+(up-low)*rand()/RAND_MAX;
	}
}

int output(int qty, int *array)//вывод массива
{
	int i,j,cycles;//определение переменных
	if (qty>0)
	{
		printf("|   Element   |");
	}
	else
	{
		printf("Array has no elements\n");
    }
	for (i = 1; i <=qty; i++) //цикл по всем элементам
	{
		printf(" %10d |",i);//вывод номера элемента в массиве
		if ((i%5==0)&&(i!=qty)) //определение конца строки
		{
			printf("|    Value    |");
			for (j=4; j >=0; j--)//вывод значений
			{
				printf(" %10d |",(array[i-j]));
			}
			printf("|   Element   |");
		}
		else //или последнего элемента в массиве
		{
			if (i==qty)
			{
				if (i%5!=0)
				{
					printf("\n");
				}
				printf("|    Value    |");//вывод значений
				if (i%5==0)
					cycles=5;
				else
					cycles=(i%5);
				for (j=(cycles-1); j >=0; j--)
				{
					printf(" %10d |",array[i-j]);
				}
				printf("\n\n"); //создание пустой строки после вывода
			}
		}
	}
}

int null(int qty, int *array)//обнуление массива
{
	int i;//определение переменных
	for (i = 1; i <=qty; i++)//заполнение массива нулями
	{
		array[i-1]=0;
	}
}

int maximum(int qty, int *array, int *max)//поиск максимального значения
{
	int i;//определение переменных
	*max=-array[i];//приравнивание максимального значения одному из элементов
	for (i = 1; i <=qty; i++)//проход по всем элементам
	{
		if (max>array[i-1])//проверка нового максимального значения
		{
			*max=array[i-1];//задание нового максимального значения
		}
	}
	printf("Maximum: %d |\n",*max);//вывод максимального значения
}

int savetofile(int qty, int *array)//сохранение массива в файл
{
	FILE *filepointer;//определение переменных
	int i;
	filepointer = fopen("SR12", "w");//открытие файла
	if (filepointer==NULL)//не удалось открыть
	{
		//сообщение об ошибке
		exit(1);//выход
	}
	else//удалось открыть
	{
		for (i = 1; i <= qty; i++)//запись в файл
		{
			fprintf(filepointer, "%d ",array[i]);
		}
		fclose(filepointer);//закрытие файла
	}
}

int readfromfile(int *qty, int *array)
{
	FILE *filepointer;//определение переменных
	int i=1;
	*qty=0;//сброс количества элементов в массиве
	filepointer = fopen("SR12", "r");//открытие файла
	if (filepointer==NULL)//не удалось открыть
	{
		printf("Error while opening file.\n");//сообщение об ошибке
		exit(1);//выход
	}
	else//удалось открыть
	{
		while(!feof(filepointer))//считывание до конца файла
		{
			fscanf(filepointer,"%d ",&array[i]);//считывание элемента
			i++;//изменение позиции в массиве
			*qty=*qty+1;//изменение количества элементов
		}
		fclose(filepointer);//закрытие файла
	}
}

int checkn(int qty, int nmax,int *n)//проверка количества элементов
{
	while ((nmax<*n)||(*n<0))//пока не будет веедено правильное число
	{
		printf("This number is not allowed. Enter correct number: ");//ввод другого числа
		scanf("%d", &*n);
	}
}

int replace (int n,int *array)//замена элементов в массиве
{
	int i;//определение переменных
	for (i = 1; i <= n; i++)//проход по всем элементам
	{
		array[0]=array[i];//передача элемента в другую переменную
		array[i]=array[i+n];//замена его другим элементом
		array[i+n]=array[0];//замена другого элемента значением первого
	}
}

int checkposnum(int qty, int *pos, int *num)//проверка количества элементов и позиции
{
	while ((*pos<=0)||(*pos>qty+1)||(((*pos+abs(*num))>(qty+1))&&(*num<0)))//пока не будут введены правильные числа
	{
		printf("Position must be from 1 to %d, sum of position and absolute change must not exceed %d in case of removing elements. Enter correct: ",qty+1,qty+1);//ввод других чисел
		scanf("%d %d", &*pos, &*num);
	}
}

int arrayinsert(int low, int up,int pos, int num, int *qty, int *array)//добавление элементов
{
	int i;//определение переменных
	int stime;
	long int ltime;
	ltime=time(NULL);//создание случайной последовательности
	stime=(unsigned) ltime/2;
	srand(stime);
	*qty=*qty+num;//изменение количества элементов
	*array=realloc(array,*qty*sizeof(int));//увеличение массива
	for (i = (*qty-num); i >=pos ; i--)//сдвиг элементов к концу
	{
		array[i+num]=array[i];
	}
	for (i = pos; i <=pos+num-1; i++)//заполнение освободившегося места случайными числами
	{
		array[i]=low+(up-low)*rand()/RAND_MAX;
	}

}

int arraycutoff(int pos, int num, int *qty, int *array)//удаление элементов
{
	int i;//определение переменных
	*qty=*qty+num;//изменение количества элементов
	for (i = pos; i <=pos+abs(num); i++)//сдвиг элементов к началу
	{
		array[i]=array[i+abs(num)];
	}

}

int checksize(int *arraysize)
{
	while (*arraysize<1)//пока не будет введено правильное число
	{
		printf("Quantity of elements in array must be more than zero. Enter correct quantity: ");//ввод другого числа
		scanf("%d", &*arraysize);
	}

}

int sort(int qel, int *qas, int *qco, int *array)//сортировка массива
{
	int k,j,i; //определение переменных
	for (k = 2; k <=qel ; k++)//проход по всем элементам после первого
	{
		array[0]=array[k];//передача сравниваемого элемента в нулевой элемент
		*qas=*qas+1;//операция присваивания
		j=1;//сброс счетчика
		while((array[j]<array[0])&&(j<k))//проход по отсортированным элементам
		{
			j++;//изменение счетчика
			*qco=*qco+1;//операция сравнения
		}
		*qco=*qco+1;//операция сравнения
		for (i = k; i > j; i--)//цикл сдвига значений
		{
			array[i]=array[i-1];//сдвиг значения
			*qas=*qas+1;//операция присваивания
		}
		array[j]=array[0];//вставка элемента из нулевого
		*qas=*qas+1;//операция присваивания
	}
}

int sort1(int qel, int *qas, int *qco, int *array)//сортировка массива
{
	int k,j,i,qsort=1,midel; //определение переменных
	for (k = 2; k <=qel ; k++)//проход по всем элементам после первого
	{
		array[0]=array[k];//передача сравниваемого элемента в нулевой элемент
		*qas=*qas+1;//операция присваивания
		midel=qsort/2;
		if (midel==0)
		{
			midel=1;
		}
		if (array[0]>array[midel])
		{
			j=midel;
			while((array[j]<array[0])&&(j<k))//проход по отсортированным элементам
			{
				j++;//изменение счетчика
				*qco=*qco+1;//операция сравнения
			}
		}
		else
		{
			j=1;//сброс счетчика
			while((array[j]<array[0])&&(j<midel))//проход по отсортированным элементам
			{
				j++;//изменение счетчика
				*qco=*qco+1;//операция сравнения
			}
		}
		*qco=*qco+2;//операция сравнения
		for (i = k; i > j; i--)//цикл сдвига значений
		{
			array[i]=array[i-1];//сдвиг значения
			*qas=*qas+1;//операция присваивания
		}
		array[j]=array[0];//вставка элемента из нулевого
		*qas=*qas+1;//операция присваивания
		qsort++;
	}
}

int sortn(int qel, int *qas, int *qco, int *array)//сортировка массива
{
	int l,k,j,i,qsort=2,poss=1,pose=qsort; //определение переменных
	for (k = 2; k <=qel ; k++)//проход по всем элементам после первого
	{
		array[0]=array[k];//передача сравниваемого элемента в нулевой элемент
		*qas=*qas+1;//операция присваивания
		for (l = 0; l <= (log10(qsort)/log10(2)+0.5); l++)//нахождение позиции
		{
			if (array[0]>array[poss+(pose-poss)/2])//сужение диапазона
			{
				poss=poss+(pose-poss)/2;//изменение начала
			}
			else
			{
				pose=poss+(pose-poss)/2;//изменение конца
			}
			*qco=*qco+1;
		}
		if (qsort==1)//корректировка для первого элемента
		{
			j=pose;
			qsort++;
			poss=1;
			if (array[0]<array[1])
			{
				array[2]=array[1];
				array[1]=array[0];
			}
			*qco=*qco+1;
			*qas=*qas+2;
		}
		else
		{
			j=pose;
			qsort++;
			poss=1;
			pose=qsort;
			for (i = k; i > j; i--)//цикл сдвига значений
			{
				array[i]=array[i-1];//сдвиг значения
				*qas=*qas+1;//операция присваивания
			}
			array[j]=array[0];//вставка элемента из нулевого
		}
		*qas=*qas+1;//операция присваивания

	}
}


