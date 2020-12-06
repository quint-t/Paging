#ifndef FIFO_PAGING_H
#define FIFO_PAGING_H

#include "abstract_paging.h"

class FifoPaging : public AbstractPaging {
  public:
    // Конструктор с параметром
    FifoPaging(int pageCount);
    // Передача на рассмотрение страницы page
    void refer(int page) override;
    // Получение списка страниц
    const std::list<int> getList() override;
    // Очистка данных, возврат к начальному состоянию
    void clear() override;

  private:
    // Дек страниц
    std::list<int> mPages;
};

#endif // FIFO_PAGING_H
