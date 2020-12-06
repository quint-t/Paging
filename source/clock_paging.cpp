#include "clock_paging.h"
#include <algorithm>

// Конструктор с параметром
ClockPaging::ClockPaging(int pageCount) : AbstractPaging(pageCount) {}

// Передача на рассмотрение страницы page
void ClockPaging::refer(int page) {
    auto duplicate = std::find(mPages.begin(), mPages.end(), page);
    if (duplicate != mPages.end()) {
        mBits[duplicate - mPages.begin()] = true;
        return;
    }
    ++mPageFault;
    if ((long)mPages.size() != (long)mPageCount) {
        mPages.emplace_back(page);
        mBits.emplace_back(false);
        return;
    }
    while (true) {
        if (!mBits[mCurrent]) {
            mPages[mCurrent] = page;
            mCurrent = (mCurrent + 1) % mPageCount;
            return;
        }
        mBits[mCurrent] = false;
        mCurrent = (mCurrent + 1) % mPageCount;
    }
}

// Получение списка страниц
const std::list<int> ClockPaging::getList() {
    return std::list<int>(mPages.begin(), mPages.end());
}

// Очистка данных, возврат к начальному состоянию
void ClockPaging::clear() {
    mPageFault = 0;
    mCurrent = 0;
    mPages.clear();
    mBits.clear();
}
