#include "search_server.h"
#include "iterator_range.h"

#include <algorithm>
#include <iterator>
#include <sstream>
#include <iostream>

vector<string_view> SplitIntoWords(string_view line) {
    vector<string_view> result;
    for (size_t after_space = line.find_first_not_of(' ', 0), space = line.find(' ', after_space);
         after_space != string_view::npos;
         after_space = line.find_first_not_of(' ', space), space = line.find(' ', after_space)) {
        result.emplace_back(line.substr(after_space, space - after_space));
    }
    return result;
}

SearchServer::SearchServer(istream &document_input) {
    UpdateDocumentBase(document_input);
}

void SearchServer::UpdateDocumentBase(istream &document_input) {
    InvertedIndex new_index;
    for (string current_document; getline(document_input, current_document);) {
        new_index.Add(move(current_document));
        new_index.countOfDocuments++;
    }
    m.lock();
    index = move(new_index);
    m.unlock();
}

void SearchServer::AddQueriesStream(istream &query_input, ostream &search_results_output) {
    futures.emplace_back(async([&query_input, &search_results_output, this]() {
        vector<pair<size_t, size_t>> search_results(index.countOfDocuments);
        for (string current_query; getline(query_input, current_query);) {
            for_each(search_results.begin(), search_results.end(), [](auto &i) { i.second = 0; });
            for (string_view word : SplitIntoWords(current_query)) {
                m.lock();
                auto currentIndex = index.Lookup(word);
                m.unlock();
                for (const auto&[docid, count] : currentIndex) {
                    search_results[docid].first = docid;
                    search_results[docid].second += count;
                }
            }
            partial_sort(begin(search_results),
                         begin(search_results) + min(5ul, search_results.size()),
                         end(search_results),
                         [](pair<size_t, size_t> lhs, pair<size_t, size_t> rhs) {
                             return make_pair(lhs.second, -static_cast<int64_t>(lhs.first)) >
                                    make_pair(rhs.second, -static_cast<int64_t>(rhs.first));
                         });
            search_results_output << current_query << ':';
            for (auto[docid, hitcount] : Head(search_results, 5)) {
                if (hitcount) {
                    search_results_output << " {" << "docid: " << docid << ", " << "hitcount: " << hitcount << '}';
                }
            }
            search_results_output << endl;
        }
    }));
}

SearchServer::~SearchServer() {
    for (auto &future : futures) {
        future.get();
    }
}

void InvertedIndex::Add(string &&document) {
    docs.emplace_back(move(document));
    size_t docid = docs.size() - 1;
    for (const auto &word : SplitIntoWords(docs.back())) {
        auto &currentIndex = index[word];
        if (!currentIndex.empty() && currentIndex.back().first == docid) {
            currentIndex.back().second += 1;
        } else {
            currentIndex.emplace_back(docid, 1);
        }
    }
}

vector<pair<size_t, size_t>> InvertedIndex::Lookup(string_view word) const {
    if (auto it = index.find(word); it != index.end()) {
        return it->second;
    } else {
        return {};
    }
}
