#ifndef REVERSELRU_PAGING_H
#define REVERSELRU_PAGING_H

#include "abstract_paging.h"
#include <unordered_map>

class ReverseLruPaging : public AbstractPaging {
  public:
    // Конструктор с параметром
    ReverseLruPaging(int pageCount);
    // Передача на рассмотрение страницы page
    void refer(int page) override;
    // Получение списка страниц
    const std::list<int> getList() override;
    // Очистка данных, возврат к начальному состоянию
    void clear() override;

  private:
    // Список страниц
    std::list<int> mPages;
    // Ассоциативный массив (страница, положение в списке)
    std::unordered_map<int, std::list<int>::iterator> mRefMap;
};

#endif // REVERSELRU_PAGING_H
