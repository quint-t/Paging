#include "mainwindow.h"
#include "abstract_paging.h"
#include "clock_paging.h"
#include "fifo_paging.h"
#include "lfu_paging.h"
#include "lru_paging.h"
#include "reverselru_paging.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <memory>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_startButton_clicked() {
    ui->statusBar->showMessage("");
    std::unique_ptr<AbstractPaging> paging;
    if (ui->clockButton->isChecked()) {
        paging = std::unique_ptr<AbstractPaging>(
            new ClockPaging(ui->frameCountSpin->value()));
    } else if (ui->fifoButton->isChecked()) {
        paging = std::unique_ptr<AbstractPaging>(
            new FifoPaging(ui->frameCountSpin->value()));
    } else if (ui->lfuButton->isChecked()) {
        paging = std::unique_ptr<AbstractPaging>(
            new LfuPaging(ui->frameCountSpin->value()));
    } else if (ui->lruButton->isChecked()) {
        paging = std::unique_ptr<AbstractPaging>(
            new LruPaging(ui->frameCountSpin->value()));
    } else {
        paging = std::unique_ptr<AbstractPaging>(
            new ReverseLruPaging(ui->frameCountSpin->value()));
    }
    QStringList stringList = ui->referLine->text().split(QRegExp("[.,;\\s]+"));
    ui->resultWidget->clear();
    for (QString string : stringList) {
        bool isOk = true;
        int page = string.toInt(&isOk);
        if (isOk == false) {
            QMessageBox::critical(this, "Ошибка",
                                  "Ошибка при чтении ссылочной строки");
            ui->resultWidget->clear();
            return;
        }
        int pageFaultCountBefore = paging->getPageFaultCount();
        paging->refer(page);
        int pageFaultCountAfter = paging->getPageFaultCount();
        QString resultLine = QString::number(page) + ": ";
        const std::list<int> list = paging->getList();
        for (auto page : list) {
            resultLine += QString::number(page) + ", ";
        }
        resultLine.chop(2);
        if (pageFaultCountBefore != pageFaultCountAfter) {
            resultLine += " [отказ страницы]";
        }
        ui->resultWidget->addItem(resultLine);
    };
    ui->statusBar->showMessage("Число отказов страниц: " +
                               QString::number(paging->getPageFaultCount()));
}

void MainWindow::on_infoButton_clicked() {
    QMessageBox::information(this, "Информация",
                             "Программа для моделирования стратегий замещения "
                             "страниц в оперативной памяти.\nАвтор: Коваленко "
                             "Леонид (ИКПИ-85).\n");
}
