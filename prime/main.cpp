#include<stdio.h>
//#include<stdlib.h>
//#include<time.h>

typedef unsigned long long ull;

const unsigned req_n    = 100000000;
const unsigned MAX_BASE = 10000000;
const unsigned BASE     = 10000000;
const unsigned MAX_N    = 26 * req_n;
unsigned isnt_prime_base[MAX_BASE >> 5] = {0};
unsigned isnt_prime[MAX_N >> 5] = {0};
unsigned prime_base[MAX_BASE / 5];
unsigned delta_prime_base[MAX_BASE / 5];
unsigned base = 1;
unsigned num_prime_base = 0;
unsigned num_tobase = 0;
bool ok_base = false;
unsigned prime[req_n] = {0};
unsigned num_prime = 0;
unsigned n;

int main()
{
	//clock_t start,end;
	//start = clock();

	if (scanf("%d",&n) != 1 || n <= 0 || n > 100000000)
	{
		printf("Error input\n");
		return 0;
	}

	unsigned i,j,k,ix,x,y;
	
	for (i = 1; !ok_base || i <= base; i++)
	{
		if ((isnt_prime_base[i >> 5] & (1 << (i & 31))) == 0)
		{
			if (!ok_base && i != 1 && base * i <BASE)
			{
				prime[num_prime++] = i;
				num_tobase++;
				base *= i;
				for (k = i; k <= BASE; k += i)
					isnt_prime_base[k >> 5] |= 1 << (k & 31);
			}
			else
			{
				if (num_prime_base)
					delta_prime_base[num_prime_base - 1] = i - prime_base[num_prime_base - 1];
				prime_base[num_prime_base++] = i;
				if (base * i > BASE)
					ok_base = true;
			}
		}
	}
	delta_prime_base[num_prime_base - 1] = 2;

	j = 1;
	ix = prime_base[j];
	while (num_prime < n)
	{
		if ((isnt_prime[ix >> 6] & (1 << ((ix >> 1) & 31))) == 0)
		{
			prime[num_prime++] = ix;
		}
		y = MAX_N / ix;
		for (k = num_tobase; prime[k] && prime[k] <= y; k++)
		{
			x = ix * prime[k];
			isnt_prime[x >> 6] |= 1 << ((x >> 1) & 31);
			if (ix % prime[k] == 0) break;
		}
		ix += delta_prime_base[j];
		j++;
		if (j == num_prime_base)
		{
			j = 0;
		}
	}


	printf("%d\n", prime[n - 1]);
	
	//end = clock();
	//printf("%d\n", end - start);
	//system("pause");
	return 0;
}