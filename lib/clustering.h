#pragma once

typedef struct {
    int Index;
    int Cluster;
    int NumSims;
    const int* SimIds;
    const float* Sims;
} TElement;

typedef struct {
    float SimilarityThreshold;
    float RecallFactor;
    float RecallDecayFactor;
} TParameters;

#ifdef __cplusplus
extern "C" {
#endif

int AgglomerativeClustering(int n, TElement* elements, const TParameters* params, const char** err);

#ifdef __cplusplus
}
#endif
