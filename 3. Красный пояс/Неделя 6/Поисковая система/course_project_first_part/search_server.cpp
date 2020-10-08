#include "search_server.h"
#include "iterator_range.h"

#include <algorithm>
#include <iterator>
#include <sstream>
#include <iostream>

vector<string> SplitIntoWords(const string &line) {
    istringstream words_input(line);
    return {istream_iterator<string>(words_input), istream_iterator<string>()};
}

SearchServer::SearchServer(istream &document_input) {
    UpdateDocumentBase(document_input);
}

void SearchServer::UpdateDocumentBase(istream &document_input) {
    InvertedIndex new_index;
    for (string current_document; getline(document_input, current_document);) {
        new_index.Add(current_document);
    }
    index = move(new_index);
}

void SearchServer::AddQueriesStream(istream &query_input, ostream &search_results_output) {
    vector<pair<size_t, size_t>> search_results(50000);
    for (string current_query; getline(query_input, current_query);) {
        for_each(search_results.begin(), search_results.end(), [](auto &i) { i.second = 0; });
        for (const auto &word : SplitIntoWords(current_query)) {
            for (const auto&[docid, count] : index.Lookup(word)) {
                search_results[docid].first = docid;
                search_results[docid].second += count;
            }
        }
        partial_sort(begin(search_results), begin(search_results) + 5, end(search_results),
                     [](pair<size_t, size_t> lhs, pair<size_t, size_t> rhs) {
                         int64_t lhs_docid = lhs.first;
                         auto lhs_hit_count = lhs.second;
                         int64_t rhs_docid = rhs.first;
                         auto rhs_hit_count = rhs.second;
                         return make_pair(lhs_hit_count, -lhs_docid) > make_pair(rhs_hit_count, -rhs_docid);
                     });
        search_results_output << current_query << ':';
        for (auto[docid, hitcount] : Head(search_results, 5)) {
            if (hitcount) {
                search_results_output << " {" << "docid: " << docid << ", " << "hitcount: " << hitcount << '}';
            }
        }
        search_results_output << endl;
    }
}

void InvertedIndex::Add(const string &document) {
    docs.push_back(document);
    const size_t docid = docs.size() - 1;
    for (const auto &word : SplitIntoWords(document)) {
        if (!index[word].empty() && index[word].back().first == docid) {
            index[word].back().second += 1;
        } else {
            index[word].emplace_back(docid, 1);
        }
    }
}

vector<pair<size_t, size_t>> InvertedIndex::Lookup(const string &word) const {
    if (auto it = index.find(word); it != index.end()) {
        return it->second;
    } else {
        return {};
    }
}
