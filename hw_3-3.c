#include <stdio.h>
#include <stdlib.h>
#define MAX_TERMS 100

typedef struct{
int row;
int col;
int value;
}element;

typedef struct SparseMatrix{
element data[MAX_TERMS];
int rows;
int cols;
int terms;
}SparseMatrix;

void matrix_print(SparseMatrix a)
{
    printf("============<���������>===============\n");
    for(int i=0;i<a.terms;i++){
        printf("(%d,%d,%d) ",a.data[i].row,a.data[i].col,a.data[i].value);
    }
    printf("\n=========================================\n");
}

void matrix_print2(SparseMatrix a)
{
    int x=0;
    for(int r=0;r<a.rows;r++)
    {
        for(int c=0;c<a.cols;c++)
        {
            for(int i=0;i<a.terms;i++)
            {
               if((c==a.data[i].col)&&(r==a.data[i].row)){
                printf("%d ",a.data[i].value);
                x=1;
               }
            }
            if(x==0)
                printf("0 ");
            x=0;
        }
        printf("\n");
    }
    printf("=========================================\n");
}

SparseMatrix matrix_add(SparseMatrix A, SparseMatrix B)
{
    SparseMatrix C;
    int Aindex= 0, Bindex = 0, Cindex= 0;

    if (A.rows != B.rows || A.cols != B.cols) {
        fprintf(stderr,"����� ũ�Ⱑ ��ġ���� �ʽ��ϴ�.\n");
        exit(1);
    }

    C.rows = A.rows;
    C.cols = A.cols;
    while (Aindex < A.terms && Bindex < B.terms)
    {
        if (A.data[Aindex].row < B.data[Bindex].row ||
            (A.data[Aindex].row == B.data[Bindex].row && A.data[Aindex].col < B.data[Bindex].col))
        {
            C.data[Cindex] = A.data[Aindex];
            Cindex++;
            Aindex++;
        }
        else if (A.data[Aindex].row == B.data[Bindex].row && A.data[Aindex].col == B.data[Bindex].col)
        {
            C.data[Cindex].row = A.data[Aindex].row;
            C.data[Cindex].col = A.data[Aindex].col;
            C.data[Cindex].value = A.data[Aindex].value + B.data[Bindex].value;

            Aindex++;
            Bindex++;
            Cindex++;
        }
        else
        {
            C.data[Cindex] = B.data[Bindex];
            Cindex++;
            Bindex++;
        }
    }
    for(;Aindex < A.terms;Aindex++){
        C.data[Cindex] = A.data[Aindex];
        Cindex++;
    }
    for(;Bindex < B.terms;Bindex++){
        C.data[Cindex] = B.data[Bindex];
        Cindex++;
    }
    C.terms = Cindex;
    return C;
}

SparseMatrix matrix_sub(SparseMatrix A, SparseMatrix B)
{
    SparseMatrix C;
    int Aindex= 0, Bindex = 0, Cindex= 0;

    if (A.rows != B.rows || A.cols != B.cols) {
        fprintf(stderr,"����� ũ�Ⱑ ��ġ���� �ʽ��ϴ�.\n");
        exit(1);
    }

    C.rows = A.rows;
    C.cols = A.cols;

    while (Aindex < A.terms && Bindex < B.terms)
    {
        if (A.data[Aindex].row < B.data[Bindex].row ||
            (A.data[Aindex].row == B.data[Bindex].row && A.data[Aindex].col < B.data[Bindex].col))
        {
            C.data[Cindex] = A.data[Aindex];
            Cindex++;
            Aindex++;
        }
        else if (A.data[Aindex].row == B.data[Bindex].row && A.data[Aindex].col == B.data[Bindex].col)
        {
            C.data[Cindex].row = A.data[Aindex].row;
            C.data[Cindex].col = A.data[Aindex].col;
            C.data[Cindex].value = A.data[Aindex].value - B.data[Bindex].value;

            Aindex++;
            Bindex++;
            Cindex++;
        }
        else
        {
            C.data[Cindex].row = B.data[Bindex].row;
            C.data[Cindex].col = B.data[Bindex].col;
            C.data[Cindex].value = -B.data[Bindex].value;
            Cindex++;
            Bindex++;
        }
    }

    for(;Aindex < A.terms;Aindex++){
        C.data[Cindex] = A.data[Aindex];
        Cindex++;
    }
    for(;Bindex < B.terms;Bindex++){
        C.data[Cindex].row = B.data[Bindex].row;
        C.data[Cindex].col = B.data[Bindex].col;
        C.data[Cindex].value = -B.data[Bindex].value;
        Cindex++;
    }
    C.terms = Cindex;
    return C;
}
int main()
{
    SparseMatrix A;
    SparseMatrix B;
    SparseMatrix C;
    int r_A,c_A,v_A;
    int r_B,c_B,v_B;
    int addsub;
    printf("<���A>\ ��� ��:");
    scanf("%d %d",&r_A,&c_A);
    printf("0�� �ƴ� ����� ����:");
    scanf("%d",&v_A);
    A.rows=r_A;
    A.cols=c_A;
    A.terms=v_A;
    for(int i=0;i<v_A;i++){
    printf("��Ұ��Է�:(����� �������):");
    scanf("%d %d %d",&A.data[i].row,&A.data[i].col,&A.data[i].value);
    }
    matrix_print(A);
    matrix_print2(A);

    printf("<���B>\ ��� ��:");
    scanf("%d %d",&r_B,&c_B);
    printf("0�� �ƴ� ����� ����:");
    scanf("%d",&v_B);
    B.rows=r_B;
    B.cols=c_B;
    B.terms=v_B;
    for(int i=0;i<v_B;i++){
    printf("��Ұ��Է�:(����� �������):");
    scanf("%d %d %d",&B.data[i].row,&B.data[i].col,&B.data[i].value);
    }
    matrix_print(B);
    matrix_print2(B);
    printf("��Ŀ��� 1)���� 2)����: ");
    scanf("%d",&addsub);
    switch(addsub)
    {
    case 1:   //�����ϰ��
        printf("===========A,B��============\n");
        C = matrix_add(A, B);
        matrix_print(C);
        matrix_print2(C);
        break;
    case 2:
        printf("===========A,B��============\n");
        C= matrix_sub(A, B);
        matrix_print(C);
        matrix_print2(C);
        break;
    default:
        printf("�߸��Ȱ� �Է� ");
        break;

    }
    return 0;
}
