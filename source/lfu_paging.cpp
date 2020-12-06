#include "lfu_paging.h"
#include <algorithm>

// Конструктор с параметром
LfuPaging::LfuPaging(int pageCount) : AbstractPaging(pageCount) {}

// Передача на рассмотрение страницы page
void LfuPaging::refer(int page) {
    auto duplicate =
        std::find_if(mPages.begin(), mPages.end(),
                     [&page](auto pair) { return pair.second == page; });
    if (duplicate == mPages.end()) {
        ++mPageFault;
        if ((long)mPages.size() == (long)mPageCount) {
            mPages.erase(*mPages.begin());
        }
        mPages.insert({0, page});
    } else {
        int t = duplicate->first;
        mPages.erase(duplicate);
        mPages.insert({t + 1, page});
    }
}

// Получение списка страниц
const std::list<int> LfuPaging::getList() {
    std::list<int> list;
    for (auto &pair : mPages) {
        list.emplace_back(pair.second);
    }
    return list;
}

// Очистка данных, возврат к начальному состоянию
void LfuPaging::clear() {
    mPageFault = 0;
    mPages.clear();
}
