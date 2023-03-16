#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#define CYCLE 10000

int main(int argc, char* argv[])
{
	int num = 0;
	if (argc ==2)
		num = atoi(argv[1]);
	else
		num = 10000;

	int i = 0;
	double x = 0;
	double y = 0;
	double circle = 0;	// 부채꼴 내부에 찍힌 점 개수.
	double count = 0;	// 모든 점의 개수.
	double sum = 0;		// 한 번의 cycle에서 구한 pi값.

	// 계산하는 데 걸린 시간 측정
	struct timeval* start;
	start = malloc(sizeof(struct timeval));
	struct timeval* end;
	end = malloc(sizeof(struct timeval));
	struct timeval* gap;
	gap = malloc(sizeof(struct timeval));

	printf("Simulation time : %d\n", CYCLE);
	printf("Random samples per simulation : %d\n", num);

	srand((double)time(NULL));	// random generator 생성.

	gettimeofday(start, NULL);

	printf("\033[?25l"); 		// hide cursor
	for(int j=0;j<CYCLE;j++)
	{
		for (int i=0; i<num; i++)
		{
			// 사각형 내부에 위치하는 임의의 점(random sample) 생성.
			x = (double)rand()/(double)RAND_MAX;
			y = (double)rand()/(double)RAND_MAX;

			// 부채꼴 내부의 점인지 확인.
			if ((x*x)+(y*y) <=1)
				circle++;
			count++;
		}

		printf("Calculating... ");
		printf("%3.2f%c", (double)j/(CYCLE-1)*100, '%');
		for(int k=0;k<22;k++)
			printf("\b");

		sum += (circle/count)*4;
	}
	printf("\033[?25h"); 		// reveal cursor

	gettimeofday(end, NULL);
	gap->tv_sec = end->tv_sec - start->tv_sec;
	if (end->tv_usec < start->tv_usec)
		gap->tv_usec = start->tv_usec - end->tv_usec;
	else 
		gap->tv_usec = end->tv_usec - start->tv_usec;
	printf("\nElapsed time : %02ld.%02ds\n", gap->tv_sec, gap->tv_usec);
	
	// 근사값의 평균.
	printf("PI = %0.15f\n", sum/CYCLE);

	return 0;
}
