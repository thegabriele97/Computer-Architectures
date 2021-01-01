
#define N 6

extern unsigned int variance(unsigned int* V, unsigned int n);

int main() {
	unsigned int res, V[N] = { 4, 7, 2, 5 ,3, 10 };
	
	res = variance(V, N);
	
	return 0;
}
