/**
* 有9个时钟，排成一个3*3的矩阵。
|-------|    |-------|    |-------|
|       |    |       |    |   |   |
|---O   |    |---O   |    |   O   |
|       |    |       |    |       |
|-------|    |-------|    |-------|
    A            B            C    

|-------|    |-------|    |-------|
|       |    |       |    |       |
|   O   |    |   O   |    |   O   |
|   |   |    |   |   |    |   |   |
|-------|    |-------|    |-------|
    D            E            F    

|-------|    |-------|    |-------|
|       |    |       |    |       |
|   O   |    |   O---|    |   O   |
|   |   |    |       |    |   |   |
|-------|    |-------|    |-------|
    G            H            I    

* 现在需要用最少的移动，将9个时钟的指针都拨到12点的位置。共允许有9种不同的移动。
* 如下表所示，每个移动会将若干个时钟的指针沿顺时针方向拨动90度。
* 
* 移动    影响的时钟
 
 1         ABDE
 2         ABC
 3         BCEF
 4         ADG
 5         BDEFH
 6         CFI
 7         DEGH
 8         GHI
 9         EFHI 
* 
* 输入
* 9个整数，表示各时钟指针的起始位置，相邻两个整数之间用单个空格隔开。其中，0=12点、1=3点、2=6点、3=9点。
* 
* 输出
* 输出一个最短的移动序列，使得9个时钟的指针都指向12点。按照移动的序号从小到大输出结果。相邻两个整数之间用单个空格隔开。
* 
* 样例输入
* 3 3 0 
  2 2 2 
  2 1 2 
* 
* 样例输出
* 4 5 8 9 
* 
*/

# include <stdio.h>
# include <string.h>

//int clock[9];
int init_clock[9];
int steps[9] = {0};
bool flag = 0;
int possibleCase[64][9];
int indexx = 0;


void move(int *clock,int step) {
	//拨钟操作
	switch(step) {
		case 1: clock[0]++; clock[1]++; clock[3]++; clock[4]++; break;
		case 2: clock[0]++; clock[1]++; clock[2]++; break;
		case 3: clock[1]++; clock[2]++; clock[4]++; clock[5]++; break;
		case 4: clock[0]++; clock[3]++; clock[6]++; break;
		case 5: clock[1]++; clock[3]++; clock[4]++; clock[5]++; clock[7]++; break;
		case 6: clock[2]++; clock[5]++; clock[8]++; break;
		case 7: clock[3]++; clock[4]++; clock[6]++; clock[7]++; break;
		case 8: clock[6]++; clock[7]++; clock[8]++; break;
		case 9: clock[4]++; clock[5]++; clock[7]++; clock[8]++; break;
		default: break;
	}

	for(int i=0;i<9;i++) {
		clock[i]= clock[i]%4; //时钟点数应小于或等于3
	}
}

void enumerateGHI(int *clock) {
	int this_clock[9] = {0};
	memcpy(this_clock, clock, sizeof(clock));
	int possibleSteps[1] = {8};
	for (int i=0; i<4; i++) {
		steps[7]=0; //每一迭代开始前将涉及到的操作位置零
		//还原clock到操作开始前的状态
		for(int m=0;m<9;m++) {
			this_clock[m] = clock[m];
		}
		for(int m=i;m>0;m--) {
			move(this_clock, possibleSteps[0]);
			steps[possibleSteps[0]-1]++;
		}
		if(this_clock[6]!=0 || this_clock[7]!=0 || this_clock[8]!=0)
			continue;
		else {
			memcpy(possibleCase[indexx], steps, sizeof(steps));
			indexx++;
		}
	}
}

void enumerateEF(int *clock) {
	int this_clock[9] = {0};
	memcpy(this_clock, clock, sizeof(clock));
	int possibleSteps[1] = {9};
	int effectedSteps[2] = {7, 8};
	for (int i=0; i<4; i++) {

		//每一迭代开始前将涉及到的操作位置零
		for(int m=0; m<2; m++){
			steps[effectedSteps[m]] = 0;
		}

		//还原clock到操作开始前的状态
		for(int m=0;m<9;m++) {
			this_clock[m] = clock[m];
		}

		for(int m=i;m>0;m--) {
			move(this_clock, possibleSteps[0]);
			steps[possibleSteps[0]-1]++;
		}
		if(this_clock[4]!=0 || this_clock[5]!=0)
			continue;
		else {
			enumerateGHI(this_clock);
		}
	}
}

void enumerateD(int *clock) {
	int this_clock[9] = {0};
	memcpy(this_clock, clock, sizeof(clock));
	int possibleSteps[1] = {7};
	int effectedSteps[3] = {6, 7, 8};
	for (int i=0; i<4; i++) {

		//每一迭代开始前将涉及到的操作位置零
		for(int m=0; m<3; m++){
			steps[effectedSteps[m]] = 0;
		} 

		//还原clock到操作开始前的状态
		for(int m=0;m<9;m++) {
			this_clock[m] = clock[m];
		}

		for(int m=i;m>0;m--) {
			move(this_clock, possibleSteps[0]);
			steps[possibleSteps[0]-1]++;
		}
		if(this_clock[3]!=0)
			continue;
		else {
			enumerateEF(this_clock);
		}
	}
}

void enumerateC(int *clock) {
	int this_clock[9] = {0};
	memcpy(this_clock, clock, sizeof(clock));
	int possibleSteps[1] = {6};
	int effectedSteps[4] = {5, 6, 7, 8};
	for (int i=0; i<4; i++) {

		//每一迭代开始前将涉及到的操作位置零
		for(int m=0; m<4; m++){
			steps[effectedSteps[m]] = 0;
		} 
		
		//还原clock到操作开始前的状态
		for(int m=0;m<9;m++) {
			this_clock[m] = clock[m];
		}

		for(int m=i;m>0;m--) {
			move(this_clock, possibleSteps[0]);
			steps[possibleSteps[0]-1]++;
		}
		if(this_clock[2]!=0)
			continue;
		else {
			enumerateD(this_clock);
		}
	}
}

void enumerateB(int *clock) {
	int this_clock[9] = {0};
	memcpy(this_clock, clock, sizeof(clock));
	int possibleSteps[2] = {3, 5};
	int effectedSteps[6] = {2, 4, 5, 6, 7, 8};
	for (int i=0; i<4; i++) {
		for (int j=0; j<4; j++) {
			
			//每一迭代开始前将涉及到的操作位置零
			for(int m=0; m<6; m++){
				steps[effectedSteps[m]] = 0;
			}

			//还原clock到操作开始前的状态
			for(int m=0;m<9;m++) {
				this_clock[m] = clock[m];
			}

			for(int m=i;m>0;m--) {
				move(this_clock, possibleSteps[0]);
				steps[possibleSteps[0]-1]++;
			}
			for(int m=j;m>0;m--) {
				move(this_clock, possibleSteps[1]);
				steps[possibleSteps[1]-1]++;
			}
			if(this_clock[1]!=0)
				continue;
			else {
				enumerateC(this_clock);
			}
		}
	}
}

void enumerateA(int *clock) {
	/*
	printf("A_Clock:\n");
	for(int i=0; i<9;i++) {
		printf("%d ", clock[i]);
	}
	printf("\n");*/

	int this_clock[9] = {0};
	memcpy(this_clock, clock, sizeof(clock));
	int possibleSteps[3] = {1, 2, 4};
	for (int i=0; i<4; i++) {
		for (int j=0; j<4; j++) {
			for (int k=0; k<4; k++) {

				//memcpy(this_clock, clock, sizeof(clock)); 
				//尝试用这个语句去还原clock到操作开始前的状态，但是赋值不成功
				//不知道为什么
				//于是采用了下面这个循环结构来赋值
				for(int m=0;m<9;m++) {
					steps[m]=0;   //每一迭代开始前将涉及到的操作位置零
					this_clock[m] = clock[m]; //还原clock到操作开始前的状态
				} 

				for(int m=i;m>0;m--) {
					move(this_clock, possibleSteps[0]);
					steps[possibleSteps[0]-1]++;
				}
				for(int m=j;m>0;m--) {
					move(this_clock, possibleSteps[1]);
					steps[possibleSteps[1]-1]++;
				}
				for(int m=k;m>0;m--) {
					move(this_clock, possibleSteps[2]);
					steps[possibleSteps[2]-1]++;
				}
				if(this_clock[0]!=0)
					continue;
				else {
					enumerateB(this_clock);

				}
			}
		}
	}
}

int main() {

	int clock[9] = {0};

	printf("Please input the initial state of the clock:\n");
	for (int i=0; i<9; i++) {
		scanf("%d", &init_clock[i]);
	}

	memcpy(clock, init_clock, sizeof(init_clock));

	enumerateA(clock);

	int min = 36; //最大可能移动36步
	int minSteps[9]={0};
	int min_index;

	printf("The number of possible cases: %d\n", indexx);
	for (int i=0; i<indexx;i++) {
		int sum = 0;
		for (int j=0; j<9; j++) {
			printf("%d ", possibleCase[i][j]);
			sum += possibleCase[i][j];
		}
		if (sum<min) {
			min = sum;
			min_index = i;
		}
		printf("\n");
	}

	memcpy(minSteps, possibleCase[min_index], sizeof(minSteps));
	printf("minSteps:\n");
	for (int i=0; i<9; i++) {
		//printf("%d ", minSteps[i]);
		for(int j=minSteps[i]; j>0; j--)
			printf("%d ", i+1);
	}
}