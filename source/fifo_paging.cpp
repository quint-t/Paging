#include "fifo_paging.h"
#include <algorithm>

// Конструктор с параметром
FifoPaging::FifoPaging(int pageCount) : AbstractPaging(pageCount) {}

// Передача на рассмотрение страницы page
void FifoPaging::refer(int page) {
    if (std::find(mPages.begin(), mPages.end(), page) == mPages.end()) {
        ++mPageFault;
        if ((long)mPages.size() == (long)mPageCount) {
            mPages.pop_front();
        }
        mPages.emplace_back(page);
    }
}

// Получение списка страниц
const std::list<int> FifoPaging::getList() { return mPages; }

// Очистка данных, возврат к начальному состоянию
void FifoPaging::clear() {
    mPageFault = 0;
    mPages.clear();
}
