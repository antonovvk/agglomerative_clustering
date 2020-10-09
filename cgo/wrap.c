#include <stdlib.h>
#include "wrap.h"

int* ACMakeInts(int n) {
	return (int*)malloc(n * sizeof(int));
}

float* ACMakeFloats(int n) {
	return (float*)malloc(n * sizeof(float));
}

TElement* ACMakeElements(int n) {
	return (TElement*)malloc(n * sizeof(TElement));
}

void ACUpdateLists(int pos, int *ids, float *sims, int id, float sim) {
	ids[pos] = id;
	sims[pos] = sim;
}

void ACUpdateElement(TElement* elems, int idx, int n, int *ids, float *sims) {
	elems[idx].Index = idx;
	elems[idx].Cluster = -1;
	elems[idx].NumSims = n;
	elems[idx].SimIds = ids;
	elems[idx].Sims = sims;
}

TElement* ACGetElement(TElement* elems, int idx) {
	return elems + idx;
}
