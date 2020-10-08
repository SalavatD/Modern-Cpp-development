#include "Common.h"

#include <list>
#include <mutex>
#include <utility>
#include <unordered_map>

using namespace std;

class LruCache : public ICache {
    mutex mMutex;
    pair<Settings, std::size_t> mSetting;
    shared_ptr<IBooksUnpacker> mBooksUnpacker;
    list<pair<string, shared_ptr<IBook>>> mCacheItem;
    unordered_map<string, list<pair<string, shared_ptr<IBook>>>::iterator> mCache;

public:
    LruCache(shared_ptr<IBooksUnpacker> books_unpacker, const Settings &settings) :
            mSetting(settings, settings.max_memory), mBooksUnpacker(move(books_unpacker)) {
        // реализуйте метод
    }

    BookPtr GetBook(const string &book_name) override {
        // реализуйте метод
        lock_guard<mutex> guard(mMutex);
        unique_ptr<IBook> book;
        size_t bookSize;
        if (mCache.count(book_name)) {
            mCacheItem.splice(mCacheItem.begin(), mCacheItem, mCache.at(book_name));
            return mCacheItem.front().second;
        }
        book = mBooksUnpacker->UnpackBook(book_name);
        bookSize = book->GetContent().size();
        if (bookSize > mSetting.first.max_memory) {
            return move(book);
        }
        if (bookSize > mSetting.second) {
            while (mSetting.second < bookSize) {
                auto deleted = mCacheItem.back();
                mCacheItem.pop_back();
                mSetting.second += deleted.second->GetContent().size();
                mCache.erase(deleted.first);
            }
        }
        shared_ptr<IBook> result;
        mCacheItem.push_front({book_name, move(book)});
        mCache[book_name] = mCacheItem.begin();
        mSetting.second -= bookSize;
        result = mCacheItem.front().second;
        return result;
    }
};

unique_ptr<ICache> MakeCache(shared_ptr<IBooksUnpacker> books_unpacker, const ICache::Settings &settings) {
    // реализуйте функцию
    return make_unique<LruCache>(books_unpacker, settings);
}
