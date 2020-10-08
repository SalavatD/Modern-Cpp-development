#pragma once

#include <istream>
#include <ostream>
#include <set>
#include <list>
#include <vector>
#include <map>
#include <string>
#include <future>

using namespace std;

class InvertedIndex {
public:
    InvertedIndex() : countOfDocuments(0) {
        docs.reserve(50000);
    }

    void Add(string &&document);

    vector<pair<size_t, size_t>> Lookup(string_view word) const;

    const string &GetDocument(size_t id) const {
        return docs[id];
    }

    size_t countOfDocuments;

private:
    map<string_view, vector<pair<size_t, size_t>>> index;
    vector<string> docs;
};

class SearchServer {
public:
    SearchServer() = default;

    explicit SearchServer(istream &document_input);

    void UpdateDocumentBase(istream &document_input);

    void AddQueriesStream(istream &query_input, ostream &search_results_output);

    ~SearchServer();

private:
    vector<future<void>> futures;
    mutex m;
    InvertedIndex index;
};
