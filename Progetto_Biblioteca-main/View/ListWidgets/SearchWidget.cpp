#include <QVBoxLayout>

#include "SearchWidget.h"

namespace View::List {

  SearchWidget::SearchWidget(QWidget *parent) : QWidget{parent}
  {
    QHBoxLayout* mainLayout = new QHBoxLayout(this);

    searchBar = new QLineEdit();
    searchBar->setPlaceholderText("Search...");
    mainLayout->addWidget(searchBar);

    searchTimer = new QTimer(this);
    searchTimer->setSingleShot(true);

    // 200ms buon delay nella ricerca
    connect(searchBar, &QLineEdit::textChanged, this, [this]() {
      searchTimer->start(200);
    });

    connect(searchTimer, &QTimer::timeout, this, [this]() {
      emit searchQueryChanged(searchBar->text());
    });
  }

}
