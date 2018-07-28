/**
 * 算法概念----枚举
 *
 * 案例二---讨厌的青蛙
 * 有一种小青蛙, 每到晚上, 这种青蛙会跳跃稻田, 从而踩踏稻子
 * 农民早上看到被踩踏的稻子, 希望找到造成最大损害的那只青蛙经过的路径
 * 每只青蛙总是沿着一条直线跳跃稻田
 * 且每次跳跃的距离都相同
 *
 * 详细描述：
 * 稻田里的稻子组成一个栅格, 每棵稻子位于一个格点上
 * 而青蛙总是从稻田的一侧跳进稻田, 然后沿着某条直线穿越稻田, 从另一侧跳出去
 * 可能会有多只青蛙从稻田穿越
 * 青蛙每一跳都恰好踩在一棵水稻上, 将这棵水稻拍倒
 * 有些水稻可能被多只青蛙踩踏
 * 农民所见到的是水稻被踩倒后的情形, 并看不到青蛙经过的路径（直线）,也见不到别人家田里被踩踏的水稻
 *
 * 程序要求：
 * 求在各条青蛙行走路径中, 踩踏水稻最多的那一条上, 有多少颗水稻被踩踏
 *
 * 案例：
 * 输入：
   Initialized max: 2
   Please input row and column:
   3 3
   3 rows and 3 columns.
   Please input number of destroyed plants:
   4
   Please input position of each destroyed plants(index starts from 0):
   0 0
   0 1
   1 1
   2 2
 * 输出：
   Max number of destroyed plants on one way: 3
 */

#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
int r; //行数
int c; //列数
int n; //被踩踏的植物总数

struct PLANT{
    int x,y; //植物的坐标
};

PLANT plants[5001];
PLANT plant;

/**
 *
 * @param secPlant 起始点
 * @param dX x方向上的步长
 * @param dY y方向上的步长
 * @return steps 落在稻田里的步数
 */
int searchPath(PLANT secPlant, int dX, int dY) {
    PLANT nextPlant;
    int steps = 2;
    nextPlant.x = secPlant.x + dX;
    nextPlant.y = secPlant.y + dY;
    while(nextPlant.x<r && nextPlant.x>1 && nextPlant.y<c && nextPlant.y>1) {
        if (!binary_search(plants, plants+n, plant)) { //每一步都必须踩到植物
            steps = 2;
            break;
        }
        steps = steps + 1;
        nextPlant.x += dX;
        nextPlant.y += dY;
    }
    return steps;
}


//重载operator以进行排序
bool operator<(const PLANT &p1, const PLANT &p2) {
    if (p1.x==p2.x)
    return p1.y < p2.y;  //如果两点x相等，则按照y来排序
    return p1.x < p2.x; //否则按照x排序
}

int main() {
    int i, j;
    int dX, dY; //步长
    int pX, pY; //
    int steps;
    int max = 2; //当前的最长路径涉及的植物数(步数)
    printf("Initialized max: %d\n", max);

    printf("Please input row and column:\n");
    scanf("%d  %d", &r, &c);
    printf("%d rows and %d columns. \n", r, c);
    //行数和列数，x方向是上下，y方向是左右
    printf("Please input number of destroyed plants:\n");
    scanf("%d", &n);
    printf("Please input position of each destroyed plants(index starts from 0):\n");
    for(i=0; i<n; i++) {
        scanf("%d  %d", &plants[i].x, &plants[i].y);
    }
    //将植物按x坐标从小到大排序，x坐标相同按y从小到大排序
    sort(plants,plants+n);
    for(int h=0; h++; h < sizeof(plants)) {
        if(plants[h].x!=0 && plants[h].y!=0) {
            printf("X[%d] = %d, Y[%d] = %d.\n", h, plants[h].x, h, plants[h].y);
        }
    }

    for (i=0; i<n-2; i++) //plants[i]是第一个点
        for (j=i+1; j<n-1; j++) { //plants[j]是第二个点
            dX = plants[j].x - plants[i].x;
            dY = plants[j].y - plants[i].y;
            pX = plants[i].x - dX;
            pY = plants[i].y - dY;
            if(pX<r && pX>1 && pY<c && pY>1)
                continue;
                //第一点的前一点在稻田里，说明本次选的第二点导致的x方向步长不合理（太小）
                //取下一个点作为第二点
            if(plants[i].x + (max-1) * dX > r)
                break;
                //x方向上过早越界了，说明这次选的第二点一定不成立，一定不是有最多植物的那条路径上的点
                //如果换下一个点作为第二点，x的步长只会更大，更不成立
                //所以应该认为这次选的第一个点必然是不成立的，那么取下一个点作为第一个点再试
            pY = plants[i].y + (max-1) * dY;
            if(pY>c || pY<1)
                continue; //y方向上越界了，换一个点作为第二点再试
            steps = searchPath(plants[j], dX, dY);
            //看看从这两点出发，是否有一条合理的路径，以及如果有的话一共能走几步
            if (steps > max)  max = steps;
        }

    if(max==2) max = 0; //如果不存在一条包含三棵及以上植物的路径, 则输出0
    printf("Max number of destroyed plants on one way: %d \n", max);

    return 0;
}