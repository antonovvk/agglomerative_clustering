#include <iostream>

#include "lib/clustering.h"

#include "args.h"
#include "timer.h"

#include <map>

struct TElements {
    std::map<std::string, TElement> Elements;
    std::map<int, std::vector<int>> Neighbours;
    std::map<int, std::vector<float>> Similarities;

    void Load(std::istream& in, const TParameters& params) {
        std::string first, second;
        float similarity;

        size_t loadedPairs = 0;
        while (in >> first >> second >> similarity) {
            similarity = std::min(1.f, std::max(0.f, similarity));
            if (similarity < params.SimilarityThreshold) {
                continue;
            }

            TElement& x = Element(first);
            TElement& y = Element(second);

            AddSimilarity(x.Index, y.Index, similarity);
            AddSimilarity(y.Index, x.Index, similarity);

            ++loadedPairs;
        }

        std::cerr << "loaded " << loadedPairs << " pairs\n";
    }

    std::vector<TElement> Get() const {
        std::vector<TElement> elements(Elements.size());
        for (auto it: Elements) {
            auto& e = elements[it.second.Index];
            e = it.second;
            auto sIt = Similarities.find(e.Index);
            if (sIt != Similarities.end()) {
                e.NumSims = sIt->second.size();
                e.Sims = &(sIt->second[0]);
            } else {
                throw std::runtime_error("Invalid element index");
            }
            auto nIt = Neighbours.find(e.Index);
            if (nIt != Neighbours.end()) {
                e.SimIds = &(nIt->second[0]);
            } else {
                throw std::runtime_error("Invalid element index");
            }
        }
        return elements;
    }

    TElement& Element(const std::string& label) {
        TElement elem = { Elements.size(), -1, 0, nullptr, nullptr };
        auto it = Elements.insert(std::make_pair(label, elem)).first;
        return it->second;
    }

    void AddSimilarity(int p, int q, float s) {
        auto x = Neighbours.insert(std::make_pair(p, std::vector<int>())).first;
        x->second.push_back(q);
        auto z = Similarities.insert(std::make_pair(p, std::vector<float>())).first;
        z->second.push_back(s);
    }
};

int Main(int argc, const char** argv) {
    TParameters params;

    {
        TArgsParser argsParser;
        argsParser.AddHandler("f", &params.RecallFactor, "recall factor").Optional();
        argsParser.AddHandler("d", &params.RecallDecayFactor, "decay factor").Optional();
        argsParser.AddHandler("t", &params.SimilarityThreshold, "similarity threshold").Optional();
        argsParser.DoParse(argc, argv);
    }

    TTimer timer(std::cerr);

    timer.Reset("loading documents");
    TElements data;
    std::ios_base::sync_with_stdio(false);
    data.Load(std::cin, params);

    timer.ReportAndReset("clustering documents");
    auto elements = data.Get();
    AgglomerativeClustering(elements.size(), &elements[0], &params, nullptr);

    timer.ReportAndReset("printing clusters");

    for (auto it: data.Elements) {
        auto c = elements[it.second.Index].Cluster;
        if (c == -1) {
            continue;
        }
        std::cout << c << "\t" << it.first << std::endl;
    }

    timer.Report();

    return 0;
}

int main(int argc, const char** argv) {
    try {
        return Main(argc, argv);
    } catch (const std::exception& e) {
        std::cerr << "Caught exception: " << e.what() << std::endl;
    }
    return -1;
}
