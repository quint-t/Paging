#include "lru_paging.h"
#include <algorithm>

// Конструктор с параметром
LruPaging::LruPaging(int pageCount) : AbstractPaging(pageCount) {}

// Передача на рассмотрение страницы page
void LruPaging::refer(int page) {
    auto duplicate = std::find(mPages.begin(), mPages.end(), page);
    if (duplicate == mPages.end()) {
        ++mPageFault;
        if ((long)mPages.size() == (long)mPageCount) {
            mPages.pop_front();
        }
        mPages.emplace_back(page);
    } else {
        mPages.remove(page);
        mPages.emplace_back(page);
    }
}

// Получение списка страниц
const std::list<int> LruPaging::getList() { return mPages; }

// Очистка данных, возврат к начальному состоянию
void LruPaging::clear() {
    mPageFault = 0;
    mPages.clear();
}
