#include "lib/clustering.h"

int* MakeInts(int n);
float* MakeFloats(int n);
TElement* MakeElements(int n);
void UpdateLists(int pos, int *ids, float *sims, int id, float sim);
void UpdateElement(TElement* elems, int idx, int n, int *ids, float *sims);
TElement* GetElement(TElement* elems, int idx);
