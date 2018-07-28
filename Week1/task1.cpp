/**
 * 算法概念----枚举
 *
 * 案例一 --- 熄灯问题
 * 有一个由按钮组成的矩阵, 其中每行有6个按钮, 共5行
 * 每个按钮的位置上有一盏灯
 * 当按下一个按钮后, 该按钮以及周围位置(上边, 下边, 左边, 右边)的灯都会改变一次
 * 如果灯原来是点亮的, 就会被熄灭
 * 如果灯原来是熄灭的, 则会被点亮
 *   在矩阵角上的按钮改变3盏灯的状态
 *   在矩阵边上的按钮改变4盏灯的状态
 *   其他的按钮改变5盏灯的状态
 *
 * 程序要求：
 * 矩阵中的每盏灯有一个初始状态
 * 写一个程序, 确定需要按下哪些按钮, 恰好使得所有的灯都熄灭
 *
 * 基本思想：
 * 枚举所有可能的按键组合不现实，可以枚举局部
 * 即第一行的按键情况
 * 剩下其他行的按键情况可以根据第一行来确定
 *
 * 案例：
 * 输入：
   Please input the number of cases:
   1
   Please input the initial state of case 1:
   1 1 0 0 1 1
   1 0 0 0 0 1
   0 0 0 0 0 0
   1 0 0 0 0 1
   1 1 0 0 1 1
   输出：
   PUZZLE #1
   1 0 0 0 0 1
   0 0 0 0 0 0
   0 0 0 0 0 0
   0 0 0 0 0 0
   1 0 0 0 0 1
 *
 */

#include <stdio.h>

//用一个6*8的数组来表示按钮矩阵
//简化计算数组下一行的值的计算公式
int puzzle[6][8], press[6][8];

/**
 * 推测验证过程
 *
 * 用6*8按钮矩阵来简化下一行按钮值的计算公式
 * 根据press[1][]和Puzzle数组
 * 用公式来计算使得1-4行所有灯熄灭的press其他行的值
 * 再判断所计算的press数组能否熄灭矩阵第5行的所有灯
 *
 * 根据第一行的按键情况 确定剩下每行按键情况
 * 然后判断通过这种按键方案 第五行的所有灯能不能被熄灭
 * @return true/false 第五行的所有灯能不能被熄灭
 */
bool guess(){
    int r, c; // row, column
    //根据press第1行和puzzle数组, 计算press其他行的值
    for(r=1; r<5; r++)
        for(c=1; c<7; c++)
            press[r+1][c] = (puzzle[r][c]+press[r][c]+ press[r-1][c]+ press[r][c-1]+press[r][c+1]) %2;
    //判断所计算的press数组能否熄灭第5行的所有灯
    for(c=1; c<7; c++)
        if ((press[5][c-1] + press[5][c] + press[5][c+1] + press[4][c]) %2 != puzzle[5][c])
            return(false);
    return(true);
}

/**
 * 枚举过程
 * 对press第1行的元素press[1][1]~press[1][6]的各种取值情况进行枚举
 *
 * 在此采用二进制进位方法以避免使用六重循环
 * press[1][]中每一个元素表示一个二进制数0/1
 * 通过模拟二进制加法方式实现枚举
 * 需要处理进位
 */
void enumerate (){
    int c;
    bool success;
    //第0行, 第0列和第7列不属于PRESS矩阵范围, 可全置0
    for ( c=1; c<7; c++)
        press[1][c] = 0;
    while(guess()==false){
        press[1][1]++;
        c = 1;
        while (press[1][c] > 1) {
            press[1][c] = 0;
            c++;
            press[1][c]++;
        }
    }
    return;
}

int main() {
    int cases, i, r, c;
    printf("Please input the number of cases:\n");
    scanf("%d", &cases);
    for ( r=0; r<6; r++ )
        press[r][0] = press[r][7] = 0;
    for ( c=1; r<7; r++ )
        press[0][c] = 0;
    for (i=0; i<cases; i++){
        printf("Please input the initial state of case %d:\n", i+1);
        for(r=1; r<6; r++)
            for(c=1; c<7; c++)
                scanf("%d", &puzzle[r][c]);
                //读入输入数据
        enumerate();
        printf("PUZZLE #%d\n", i+1);
        for(r=1; r<6; r++){
            for(c=1; c<7; c++)
                printf("%d ", press[r][c]);
            printf("\n");
        }
    }
    return 0;
}