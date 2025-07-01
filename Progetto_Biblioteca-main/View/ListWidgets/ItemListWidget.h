#ifndef ITEMLISTWIDGET_H
#define ITEMLISTWIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>
#include <QScrollArea>
#include <QListWidget>

#include "../../Model/Items/AbstractItem.h"
#include "ItemCardWidget.h"
#include "SearchWidget.h"

namespace View::List {

  class ItemListWidget : public QWidget {
    Q_OBJECT

    private:
      QScrollArea* scrollArea;
      QListWidget* listWidget;
      SearchWidget* searchWidget;
      QList<ItemCardWidget*> items;
      QPushButton* filterButton;
      QComboBox* filterOptions;

      void filterList();
      void filterClear();

    public:
      explicit ItemListWidget(QWidget* parent = nullptr);

      void addItemCard(const Items::AbstractItem& item);

    public slots:
      void deleteItemWidget(unsigned int id);
      void clearList();
      void onItemClicked(QListWidgetItem* item);
      void onQueryTextChanged(const QString& query);

    signals:
      void itemSelected(unsigned int id);

  };

}

#endif // ITEMLISTWIDGET_H
