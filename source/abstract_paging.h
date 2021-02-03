#ifndef ABSTRACT_PAGING_H
#define ABSTRACT_PAGING_H

#include <list>
#include <stdexcept>

// Абстрактный класс замещения страниц
class AbstractPaging {
  public:
    // Конструктор с параметром
    AbstractPaging(int pageCount) : mPageCount(pageCount) {
        if (pageCount <= 0)
            throw std::invalid_argument("FrameCount <= 0");
    }
    // Передача на рассмотрение страницы page
    virtual void refer(int page) = 0;
    // Получение списка страниц
    virtual const std::list<int> getList() = 0;
    // Получение числа отказов страниц
    virtual int getPageFaultCount() { return mPageFault; }
    // Очистка данных, возврат к начальному состоянию
    virtual void clear() = 0;
    // Виртуальный деструктор (обязательно)
    virtual ~AbstractPaging() {}

  protected:
    // Максимальное число страниц в памяти
    int mPageCount;
    // Текущее число отказов страниц
    int mPageFault = 0;
};

#endif // ABSTRACT_PAGING_H
