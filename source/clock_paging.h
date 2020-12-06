#ifndef CLOCK_PAGING_H
#define CLOCK_PAGING_H

#include "abstract_paging.h"
#include <vector>

// Конкретный класс замещения страниц Clock
class ClockPaging : public AbstractPaging {
  public:
    // Конструктор с параметром
    ClockPaging(int pageCount);
    // Передача на рассмотрение страницы page
    void refer(int page) override;
    // Получение списка страниц
    const std::list<int> getList() override;
    // Очистка данных, возврат к начальному состоянию
    void clear() override;

  private:
    // Текущий индекс элемента
    int mCurrent = 0;
    // Вектор страниц
    std::vector<int> mPages;
    // Вектор состояний страниц
    std::vector<bool> mBits;
};

#endif // CLOCK_PAGING_H
