#pragma once

#include "clustering.h"

#include <cmath>

struct TSubsetStats {
    float Reward = 0.;

    float PerMatrixElementSum = 0.;
    float PerRowSum = 0.;

    TSubsetStats& operator += (const TSubsetStats& other) {
        PerMatrixElementSum += other.PerMatrixElementSum;
        PerRowSum += other.PerRowSum;
        return *this;
    }

    TSubsetStats operator + (const TSubsetStats& other) {
        TSubsetStats result(*this);
        result += other;
        return result;
    }
};

struct TSetStats {
    TSubsetStats Stats;
    size_t Count = 0;

    float SumPrecisions() const {
        return Stats.PerMatrixElementSum / Count;
    }

    float AvgRecall() const {
        return Stats.PerRowSum / Count;
    }

    static double CombineMetrics(const TParameters& params, const double precision, const double recall, const size_t uniteSize) {
        float recallFactor = params.RecallFactor;
        if (params.RecallDecayFactor) {
            recallFactor *= params.RecallDecayFactor / (params.RecallDecayFactor + uniteSize);
        }
        return std::pow(recall, recallFactor) * precision;
    }

    static TSetStats InitTrivial(const double sumElementSimilarities) {
        TSetStats result;
        result.Count = 1;
        result.Stats.PerMatrixElementSum = 1.f;
        result.Stats.PerRowSum = 1.f / sumElementSimilarities;
        return result;
    }

    static TSetStats UnityStats(const TSetStats& lhs, const TSetStats& rhs, const TSubsetStats& crossStats) {
        TSetStats unity(lhs);
        unity.Count += rhs.Count;
        unity.Stats += rhs.Stats;
        unity.Stats += crossStats;
        return unity;
    }

    static float UnityReward(const TSetStats& lhs, const TSetStats& rhs, const TSubsetStats& crossStats, const TParameters& params) {
        TSetStats unity(lhs);
        unity.Count += rhs.Count;
        unity.Stats += rhs.Stats;

        const float fragmentsPrecision = (lhs.SumPrecisions() + rhs.SumPrecisions()) / unity.Count;
        const float fragmentsRecall = unity.AvgRecall();
        const float fragmentsECC = CombineMetrics(params, fragmentsPrecision, fragmentsRecall, unity.Count);

        unity.Stats += crossStats;

        const float unityPrecision = unity.SumPrecisions() / unity.Count;
        const float unityRecall = unity.AvgRecall();
        const float unityECC = CombineMetrics(params, unityPrecision, unityRecall, unity.Count);

        const float reward = unityECC - fragmentsECC;
        if (reward < 0.f) {
            return reward;
        }
        return unityPrecision + 0.1 * unityRecall;
    }
};
