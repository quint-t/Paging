#ifndef LFU_PAGING_H
#define LFU_PAGING_H

#include "abstract_paging.h"
#include <set>

class LfuPaging : public AbstractPaging {
  public:
    // Конструктор с параметром
    LfuPaging(int pageCount);
    // Передача на рассмотрение страницы page
    void refer(int page) override;
    // Получение списка страниц
    const std::list<int> getList() override;
    // Очистка данных, возврат к начальному состоянию
    void clear() override;

  private:
    // Упорядоченное множество страниц
    std::set<std::pair<int, int>> mPages;
};

#endif // LFU_PAGING_H
