static unsigned long int next = 1;

int rand() {
	next = next * 1103515245 + 12345;
	return next/65536;
}

void srand(unsigned int seed) {
	next = seed;
}
