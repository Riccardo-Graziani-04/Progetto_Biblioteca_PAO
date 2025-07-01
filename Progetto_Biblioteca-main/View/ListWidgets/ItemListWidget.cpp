#include <QVBoxLayout>

#include "ItemListWidget.h"
// Necessari per uso del typeid
#include "../../Model/Items/Book.h"
#include "../../Model/Items/Movie.h"
#include "../../Model/Items/Music.h"

namespace View::List {

  ItemListWidget::ItemListWidget(QWidget* parent)
  : QWidget{parent}
  {
    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    searchWidget = new SearchWidget();
    mainLayout->addWidget(searchWidget);

    QHBoxLayout* filterLayout = new QHBoxLayout();
    filterButton = new QPushButton(QIcon(":/icons/Resources/filter.png"), " Filter");
    filterOptions = new QComboBox();
    filterOptions->addItems({"None", "Book", "Movie", "Music"});
    filterLayout->addWidget(filterButton);
    filterLayout->addWidget(filterOptions);
    mainLayout->addLayout(filterLayout);

    listWidget = new QListWidget();

    connect(filterButton, &QPushButton::clicked, this, &ItemListWidget::filterList);
    connect(searchWidget, &SearchWidget::searchQueryChanged, this, &ItemListWidget::onQueryTextChanged);
    connect(listWidget, &QListWidget::itemClicked, this, &ItemListWidget::onItemClicked);

    mainLayout->addWidget(listWidget);
  }

  void ItemListWidget::addItemCard(const Items::AbstractItem& item) {
    ItemCardWidget* itemCard = new ItemCardWidget(item);
    items.append(itemCard);

    QListWidgetItem* listWidgetItem = new QListWidgetItem();
    listWidgetItem->setSizeHint(itemCard->sizeHint());
    listWidget->addItem(listWidgetItem);
    listWidget->setItemWidget(listWidgetItem, itemCard);
  }

  void ItemListWidget::deleteItemWidget(unsigned int id) {
    for (int i = 0; i < listWidget->count(); ++i) {
      QListWidgetItem* item = listWidget->item(i);
      // Cast sicuro da effettuare
      ItemCardWidget* cardItem = qobject_cast<ItemCardWidget*>(listWidget->itemWidget(item));

      if (cardItem->getItemID() == id) {
        delete cardItem;
        delete listWidget->takeItem(listWidget->row(item));
      }
    }
  }

  void ItemListWidget::clearList() {
    for (int i = listWidget->count() - 1; i >= 0; --i) {
      QListWidgetItem* item = listWidget->item(i);
      // Cast sicuro da effettuare
      ItemCardWidget* cardItem = qobject_cast<ItemCardWidget*>(listWidget->itemWidget(item));

      delete cardItem;
      delete listWidget->takeItem(i);
    }
  }

  void ItemListWidget::filterList() {
    // Pulizia del filtro preventiva, nel caso None siamo ok
    // negli altri casi il filtro funziona su tutta la lista
    filterClear();

    if (filterOptions->currentText() == "None") { return; }

    for (int i = 0; i < listWidget->count(); ++i) {
      QListWidgetItem* item = listWidget->item(i);
      ItemCardWidget* cardItem = qobject_cast<ItemCardWidget*>(listWidget->itemWidget(item));

      if (filterOptions->currentText() == "Book") {
        if (cardItem) {
          if (typeid(cardItem->getItem()) != typeid(Items::Book)) {
            item->setHidden(true);
          }
        }
      }
      else if (filterOptions->currentText() == "Movie") {
        if (cardItem) {
          if (typeid(cardItem->getItem()) != typeid(Items::Movie)) {
            item->setHidden(true);
          }
        }
      }
      else if (filterOptions->currentText() == "Music") {
        if (cardItem) {
          if (typeid(cardItem->getItem()) != typeid(Items::Music)) {
            item->setHidden(true);
          }
        }
      }
    }
  }

  void ItemListWidget::filterClear() {
    for (int i = 0; i < listWidget->count(); ++i) {
      QListWidgetItem* item = listWidget->item(i);
      ItemCardWidget* cardItem = qobject_cast<ItemCardWidget*>(listWidget->itemWidget(item));

      if (cardItem) {
        item->setHidden(false);
      }
    }
  }

  // Ricerca real time su base del titolo
  void ItemListWidget::onQueryTextChanged(const QString& query) {
    for (int i = 0; i < listWidget->count(); ++i) {
      QListWidgetItem* item = listWidget->item(i);
      ItemCardWidget* cardItem = qobject_cast<ItemCardWidget*>(listWidget->itemWidget(item));

      if (cardItem) {
        bool queryMatch = cardItem->getTitle().contains(query, Qt::CaseInsensitive);
        item->setHidden(!queryMatch);
      }
    }
  }

  void ItemListWidget::onItemClicked(QListWidgetItem* item) {
    ItemCardWidget* card = qobject_cast<ItemCardWidget*>(listWidget->itemWidget(item));

    if (card) {
      emit itemSelected(card->getItemID());
    }
  }
}
