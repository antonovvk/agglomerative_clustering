#include "lib/clustering.h"

// Need some name mangling to not interfere with other CGo wrappers if included in some larger project
int* ACMakeInts(int n);
float* ACMakeFloats(int n);
TElement* ACMakeElements(int n);
void ACUpdateLists(int pos, int *ids, float *sims, int id, float sim);
void ACUpdateElement(TElement* elems, int idx, int n, int *ids, float *sims);
TElement* ACGetElement(TElement* elems, int idx);
