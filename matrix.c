/*Домашнее задание №2
В аргументе командной строки передаётся имена текстовых файлов в которых записаны двумерные
матрицы вещественных чисел.
Необходимо напечатать на стандартный выходной поток результат следующего алгоритма:
Умножение матриц, хранящихся во входных файлах.
Формат хранения матриц в файлах – не разреженный – в первой строке файла записано количе-
ство строк матрицы; во второй – количество столбцов матрицы; в последующих строках файла записаны
элементы строк самой матрицы (по одной строке матрицы на одной строке файла).
В качестве внутреннего представления матрицы в памяти программы использовать разреженное пред-
ставление – одномерный массив структур (полями которых являются индексы элемента матрицы и само
значение элемента), упорядоченный по значениям пар индексов элементов матрицы (для быстрого поиска
в нём).
Целевой алгоритм не должен зависеть от представления матрицы в файле и в памяти, т.е. для рабо-
ты с матрицей должны быть реализованы и использованы в алгоритме функции: double get_elem(void
*matr, int row, int col), которая возвращает значение элемента матрицы по его индексам, и void
set_elem(void *matr, int row, int col, double elem), которая устанавливает значение элемента мат-
рицы по его индексам*/

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

#define MALLOC 1
#define ABROAD 2
#define READING 3
#define ARGUMENTS 4
#define OPENING 5
#define DIMENTION NULL
#define MEMALLOC NULL

typedef struct 
{
	int row;
	int col;
	double val;
}EL;

typedef  struct
{
    int cols;
    int rows;
    EL* data;
}Mat;

double get_elem(Mat* matr, int col, int row) 
{
    if(row > matr->cols || col > matr->rows)
    {
        printf("Exit abroad from get, incorrect arguments row,col\n");
        return ABROAD;
    } 

    int offset = matr->rows * row + col;

    return matr->data[offset].val;
}

int set_elem(Mat* matr, int col, int row, double elem)
{
    if(row > matr->cols || col > matr->rows)
    {
        printf("Exit abroad from set, incorrect arguments row,col\n");
        return ABROAD;
    } 

    int offset = matr->rows * row + col;

    matr->data[offset].val = elem;

    return 0;
}

int fill_matrix(FILE* f,Mat* matrix)
{
    for(int i = 0; i < matrix->rows; i++)
    {   
        for(int j = 0; j < matrix->cols; j++)
        {
            if(fscanf(f,"%lf",&matrix->data[i+j*matrix->cols].val) != 1)
            {
                printf("Error reading element from file\n");
                return READING;
            }

            matrix->data[i+j*matrix->cols].col = i;
            matrix->data[i+j*matrix->rows].row = j;
        }
    }
    return 0;
}

void print_matrix(Mat* matr)
{
    for(int i = 0; i < matr->rows; i++)
    {
        for(int j = 0; j < matr->cols; j++)
        {
            printf("\t%.2lf",matr->data[i+j*matr->cols].val);
        }
        putchar('\n');
    }
}

Mat* create_result_matrix(int rows, int cols)
{
    int rsize = rows * cols;

    if(rows != cols)
    {
        printf("Incorrect dimention of matrix\n");
        return DIMENTION;
    }

    Mat* multy = (Mat*)calloc(rsize, sizeof(Mat));
    if(multy == NULL)
    {
        printf("MEMORY ERROR %s\n", strerror(errno));
        return MEMALLOC;
    }

    multy->rows = rows;
    multy->cols = cols;

    multy->data = malloc(sizeof(EL)*multy->rows*multy->cols);
    if(multy->data == NULL)
    {
        printf("MEMORY ERROR %s\n", strerror(errno));
        return MEMALLOC;
    }

    return multy;
}

Mat* multy_matrix(Mat* mat1, Mat* mat2)
{
	Mat* multy = create_result_matrix(mat1->rows,mat2->cols);

    for(int i = 0; i < mat1->rows; i++)
    {
        for(int j = 0; j < mat2->cols; j++)
        {
            double multi_elem = 0;

            for(int t = 0; t < mat1->cols; t++)
            {
                multi_elem += get_elem(mat1, i, t) * get_elem(mat2, t, j);
            }

           set_elem(multy, i, j, multi_elem);
        }
    }
    return multy;
}

int main(int argc, const char* argv[])
{
	if(argc < 3)
	{
		puts("Enter filenames with matrix\n");
	    return ARGUMENTS;
	}
    
    Mat* matr = (Mat*)malloc(sizeof(Mat)*(argc-1));
    if(matr == NULL)
    {
        printf("ERROR MALLOC (matr) %s\n",strerror(errno));
        return MALLOC;
    }

    int num_matrix = 0;
    for(int i = 0; i < argc-1; i++)
    {

        FILE* f = fopen(argv[i+1],"r");
    	if(f == NULL) 
		{
 	   		printf("ERROR OPENING %s\n",strerror(errno));
 	   		return OPENING;
 		}

 		if(fscanf(f,"%d %d",&matr[i].rows,&matr[i].cols)!=2)
		{
			printf("Error reading number of rows & cols %s\n",strerror(errno));
			return READING;
		}

		matr[i].data = malloc(sizeof(EL)*matr[i].rows*matr[i].cols);
    	if (matr[i].data == NULL)
    	{
    		printf("ERROR MALLOC (data) %s\n",strerror(errno));
    		return MALLOC;
    	}

    	if(fill_matrix(f, &matr[i]) == 0)
    		num_matrix++;

		fclose(f);
	}

	Mat* res_mat = NULL;
	if(argc > 3)
	{
   		for(int i = 0; i < argc-3; i++)
    	{
    		res_mat = multy_matrix(multy_matrix(&matr[i],&matr[i+1]),&matr[i+2]);
    	}
    }
    else
    {
    	int i = 0;
    	res_mat = multy_matrix(&matr[i],&matr[i+1]);
    }

    print_matrix(res_mat);

    for(int i = 0; i < num_matrix; i++)
    {
    	free(matr[i].data);
    }
    free(matr);

    return 0;
}
