/**
 * 算法概念----枚举
 *
 * 练习一 --- 画家问题
 *
 * 有一个正方形的墙，由N*N个正方形的砖组成，其中一些砖是白色的，另外一些砖是黄色的。
 * Bob是个画家，想把全部的砖都涂成黄色。但他的画笔不好使。
 * 当他用画笔涂画第(i, j)个位置的砖时， 位置(i-1, j)、 (i+1, j)、 (i, j-1)、 (i, j+1)上的砖都会改变颜色。
 * 请你帮助Bob计算出最少需要涂画多少块砖，才能使所有砖的颜色都变成黄色。
 *
 * 程序要求：
 * 输入：
 * 第一行是个整数t(1≤ t ≤20)，表示要测试的案例数。然后是t个案例。
 * 每个案例的首行是一个整数n (1 ≤n ≤15)，表示墙的大小。
 * 接下来的n行表示墙的初始状态。每一行包含n个字符。
 * 第i行的第j个字符表示位于位置(i,j)上的砖的颜色。
 * “w”表示白砖，“y”表示黄砖。
 * 输出:
 * 每个案例输出一行。如果Bob能够将所有的砖都涂成黄色，则输出最少需要涂画的砖数，否则输出“inf”。
 *
 * 案例：
 * 输入：
   2
   3
   yyy
   yyy
   yyy
   5
   wwwww
   wwwww
   wwwww
   wwwww
   wwwww
 *
 * 输出：
 * 0
 * 15
 *
 */

#include <stdio.h>


int t; //number of cases

int n; //size of the matrix n*n

int min;

bool guess(int **puzzle, int **press, int row, int column){
    int r, c; // row, column
    //根据press第1行和puzzle数组, 计算press其他行的值
    for(r=1; r<row-1; r++)
        for(c=1; c<n+1; c++)
            press[r+1][c] = (puzzle[r][c]+press[r][c]+ press[r-1][c]+ press[r][c-1]+press[r][c+1]) %2;
    //判断所计算的press数组能否将第n行的所有砖块涂成黄色
    for(c=1; c<column-1; c++)
        if ((press[n][c-1] + press[n][c] + press[n][c+1] + press[n-1][c]) %2 != puzzle[n][c])
            return(false);
    return(true);
}

int enumerate(int **puzzle, int **press, int row, int column) {
    int r,c;
    bool success;
    int sum = -1; //最少次数

    for ( c=1; c<column-1; c++)
        press[1][c] = 0;

    bool end = 0;
    while(end==0){
        int s = 0;
        for ( c=1; c<column-1; c++)
            s += press[1][c];
        if(s==n)
            end = 1;

        if(guess(puzzle,press,row,column)) {
            sum = 0;
            for(r=1; r<row; r++){
                for(c=1; c<column; c++) {
                    if(press[r][c]==1)
                        sum+=1;
                }
            }
            printf("sum: %d \n", sum);
            if(min>sum && sum>=0) min=sum;
            printf("min: %d \n", min);
            for(r=1; r<row; r++) {
                for(c=1; c<column-1; c++)
                    printf("%d ", press[r][c]);
                printf("\n");
            }
            printf("\n");
        }

        //print the value of press[][]
        /*
        for(r=1; r<row; r++){
            for(c=1; c<column-1; c++)
                printf("%d ", press[r][c]);
            printf("\n");
        }
        printf("\n");*/

        press[1][1]++;
        c = 1;
        while (press[1][c] > 1) {
            press[1][c] = 0;
            c++;
            press[1][c]++;
        }
    }
    return min;
}

int main() {
    printf("Please input the number of cases t (1≤t≤20):\n");
    scanf("%d", &t);

    int i,r,c;

    for (i=0; i<t; i++){
        min = 1000;
        printf("Please input the dim of the matrix n(1≤n≤15):\n");
        scanf("%d", &n);

        //int puzzle_n[n+1][n+2];
        //int press[n+1][n+2];
        //char puzzle_s[n+1][n+2];

        //int n = 2;
        //int m = 3;
        int** puzzle_n = new int* [n+1];
        int** press = new int* [n+1];
        char** puzzle_s = new char* [n+1];

        for (int i = 0; i < n+1; i++)
            puzzle_n[i] = new int[n+2];
        for (int i = 0; i < n+1; i++)
            press[i] = new int[n+2];
        for (int i = 0; i < n+1; i++)
            puzzle_s[i] = new char[n+2];

        //第0行, 第0列和第n+1列不属于PRESS矩阵范围, 可全置0
        for (r=0; r<n+1; r++)
            press[r][0] = press[r][n+1] = 0; //0-->y 1-->w
        for (c=1; c<n+2; c++ )
            press[0][c] = 0;

        printf("Please input the initial state of case %d:\n", i+1);
        for(r=1; r<n+1; r++) {
            char s[n+1];
            scanf("%s", &s);
            for (c=1; c<n+1; c++) {
                puzzle_s[r][c] = s[c-1];
                if (puzzle_s[r][c]=='y')
                    puzzle_n[r][c]=0;
                else
                    puzzle_n[r][c]=1;
            }
        }
        //读入输入数据

        printf("puzzle_s:\n");
        for(r=1; r<n+1; r++){
            for(c=1; c<n+1; c++)
                printf("%c ", puzzle_s[r][c]);
            printf("\n");
        }

        printf("puzzle_n:\n");
        for(r=1; r<n+1; r++){
            for(c=1; c<n+1; c++)
                printf("%d ", puzzle_n[r][c]);
            printf("\n");
        }
        printf("Over \n");
        printf("\n");
        //输出读入的数据

        min = enumerate(puzzle_n, press, n+1, n+2);
        printf("PUZZLE #%d\n", i+1);
        if(min == 1000)
            printf("inf");
        else
            printf("%d\n", min);
    }
    return 0;
}