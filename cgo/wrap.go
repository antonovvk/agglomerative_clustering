package clustering

/*
#include <stdlib.h>
#include "lib/clustering.h"

int* MakeInts(int n) {
	return (int*)malloc(n * sizeof(int));
}
float* MakeFloats(int n) {
	return (float*)malloc(n * sizeof(float));
}
TElement* MakeElements(int n) {
	return (TElement*)malloc(n * sizeof(TElement));
}
void UpdateLists(int pos, int *ids, float *sims, int id, float sim) {
	ids[pos] = id;
	sims[pos] = sim;
}
void UpdateElement(TElement* elems, int idx, int n, int *ids, float *sims) {
	elems[idx].Index = idx;
	elems[idx].Cluster = -1;
	elems[idx].NumSims = n;
	elems[idx].SimIds = ids;
	elems[idx].Sims = sims;
}
TElement* GetElement(TElement* elems, int idx) {
	return elems + idx;
}
*/
import "C"

import (
	"fmt"
	"unsafe"
)

type Element struct {
	Label   string
	Cluster int
	Sims    map[string]float32
}

type Parameters struct {
	SimilarityThreshold float32
	RecallFactor        float32
	RecallDecayFactor   float32
}

func DefaultParameters() Parameters {
	return Parameters{
		SimilarityThreshold: 0.2,
		RecallFactor:        1,
		RecallDecayFactor:   0,
	}
}

func AgglomerativeClustering(elements []*Element, parameters Parameters) (res int, err error) {
	var errStr *C.char
	params := C.TParameters{
		SimilarityThreshold: C.float(parameters.SimilarityThreshold),
		RecallFactor:        C.float(parameters.RecallFactor),
		RecallDecayFactor:   C.float(parameters.RecallDecayFactor),
	}

	index := map[string]int{}
	for idx, elem := range elements {
		index[elem.Label] = idx
	}
	n := len(elements)
	ids := make([]*C.int, n)
	sims := make([]*C.float, n)
	elems := C.MakeElements(C.int(n))
	for idx, elem := range elements {
		idList := C.MakeInts(C.int(len(elem.Sims)))
		simList := C.MakeFloats(C.int(len(elem.Sims)))
		pos := 0
		for l, s := range elem.Sims {
			C.UpdateLists(C.int(pos), idList, simList, C.int(index[l]), C.float(s))
			pos++
		}
		C.UpdateElement(elems, C.int(idx), C.int(pos), idList, simList)
		ids = append(ids, idList)
		sims = append(sims, simList)
	}
	nc := C.AgglomerativeClustering(C.int(n), elems, &params, &errStr)
	if res = int(nc); res == -1 {
		err = fmt.Errorf("AgglomerativeClustering failed: %s", C.GoString(errStr))
	}
	for idx := range elements {
		elem := C.GetElement(elems, C.int(idx))
		elements[idx].Cluster = int(elem.Cluster)

		C.free(unsafe.Pointer(elem.SimIds))
		C.free(unsafe.Pointer(elem.Sims))
	}
	C.free(unsafe.Pointer(elems))
	return res, err
}
