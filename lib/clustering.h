#pragma once

struct TElement {
    int Index;
    int Cluster;
    int NumSims;
    const int* SimIds;
    const float* Sims;
};

struct TParameters {
    float SimilarityThreshold = 0.2f;
    float RecallFactor = 1.f;
    float RecallDecayFactor = 0.;
};

#ifdef __cplusplus
extern "C" {
#endif

int AgglomerativeClustering(int n, TElement* elements, const TParameters* params, const char** err);

#ifdef __cplusplus
}
#endif
