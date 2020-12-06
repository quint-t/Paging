#ifndef LRU_PAGING_H
#define LRU_PAGING_H

#include "abstract_paging.h"

class LruPaging : public AbstractPaging {
  public:
    // Конструктор с параметром
    LruPaging(int pageCount);
    // Передача на рассмотрение страницы page
    void refer(int page) override;
    // Получение списка страниц
    const std::list<int> getList() override;
    // Очистка данных, возврат к начальному состоянию
    void clear() override;

  private:
    // Список страниц
    std::list<int> mPages;
};

#endif // LRU_PAGING_H
