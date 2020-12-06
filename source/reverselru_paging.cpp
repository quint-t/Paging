#include "reverselru_paging.h"

// Конструктор с параметром
ReverseLruPaging::ReverseLruPaging(int pageCount) : AbstractPaging(pageCount) {}

// Передача на рассмотрение страницы page
void ReverseLruPaging::refer(int page) {
    if (mRefMap.find(page) == mRefMap.end()) {
        ++mPageFault;
        if ((long)mPages.size() == (long)mPageCount) {
            mRefMap.erase(mPages.back());
            mPages.pop_back();
        }
    } else {
        mPages.erase(mRefMap[page]);
    }
    mPages.emplace_front(page);
    mRefMap[page] = mPages.begin();
}

// Получение списка страниц
const std::list<int> ReverseLruPaging::getList() { return mPages; }

// Очистка данных, возврат к начальному состоянию
void ReverseLruPaging::clear() {
    mPageFault = 0;
    mPages.clear();
    mRefMap.clear();
}
