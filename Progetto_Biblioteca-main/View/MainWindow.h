#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedLayout>

#include "../Model/Items/AbstractItem.h"
#include "../Model/JSON/JsonRepository.h"
#include "../Model/Memory/ItemRepository.h"
#include "EditWidgets/ItemEditWidget.h"
#include "ListWidgets/ItemListWidget.h"
#include "DetailWidgets/ItemDetailWidget.h"

namespace View {

  class MainWindow : public QMainWindow {
    Q_OBJECT

    private:
      QToolBar* toolBar;
      QMenu* fileMenu;
      QToolButton* fileToolButton;
      QAction* createItem;
      QAction* openFile;
      QAction* saveAction;
      QAction* shortcutsList;
      QAction* newFile;

      View::Editors::ItemEditWidget* editWidget;
      View::List::ItemListWidget* leftListWidget;
      View::Details::ItemDetailWidget* rightDetailWidget;
      QStackedLayout* rightStackedLayout;

      JSON::JsonRepository* jsonRepository;
      bool unsavedChanges = false;

      void setupToolBar();
      void setupCentralWidgets();
      void clearMemory();

    protected:
      void closeEvent(QCloseEvent* event) override;

    public:
      MainWindow(QWidget* parent = nullptr);
      ~MainWindow();

      MainWindow& reloadData();

    public slots:
      void createNewItem();
      void editExistingItem(unsigned int id);
      void createNewFile();
      void openExistingFile();
      void saveAllItems();
      void displayShortcuts();
      void closeEditWindow();
      void addItemToList(const Items::AbstractItem& item);
      void getItemDetails(unsigned int id);
      void deleteItem(unsigned int id);

    signals:
      void displayItemDetails(const Items::AbstractItem& item);
      void deleteItemWidget(unsigned int id);
      void clearList();
  };

}

#endif // MAINWINDOW_H
