#include <QToolBar>
#include <QMenu>
#include <QMessageBox>
#include <QScrollArea>
#include <QPushButton>
#include <QToolButton>
#include <QLabel>
#include <QFileDialog>
#include <QSplitter>
#include <QCloseEvent>

#include "MainWindow.h"

namespace View {

  MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent), jsonRepository(nullptr)
  {
    setupToolBar();
    setupCentralWidgets();
  }

  MainWindow::~MainWindow() {}

  void MainWindow::setupToolBar() {
    // Spazio nei text dei pulsanti per spaziare nella gui testo e icone
    fileToolButton = new QToolButton(this);
    fileToolButton->setText(" File");
    fileToolButton->setPopupMode(QToolButton::InstantPopup);
    fileToolButton->setStyleSheet("QToolButton::menu-indicator { image: none; }");
    fileToolButton->setIcon(QIcon(":/icons/Resources/file.png"));
    fileToolButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    createItem = new QAction(QIcon(":/icons/Resources/new_item.png"), " New Item");
    openFile = new QAction(QIcon(":/icons/Resources/open_file.png"), " Open");
    saveAction = new QAction(QIcon(":/icons/Resources/save_file.png"), " Save");
    shortcutsList = new QAction(QIcon(":/icons/Resources/info.png"), " Info");
    newFile = new QAction(QIcon(":/icons/Resources/new_file.png"), " New");

    fileMenu = new QMenu();
    fileMenu->addAction(newFile);
    fileMenu->addAction(openFile);
    fileMenu->addAction(saveAction);
    fileMenu->addSeparator();
    fileToolButton->setMenu(fileMenu);

    createItem->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_N));
    newFile->setShortcut(QKeySequence(Qt::CTRL | Qt::SHIFT | Qt::Key_N ));
    openFile->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_O));
    saveAction->setShortcut(QKeySequence(Qt::CTRL | Qt::SHIFT | Qt::Key_S));
    shortcutsList->setShortcut(QKeySequence(Qt::Key_F1));

    connect(createItem, &QAction::triggered, this, &MainWindow::createNewItem);
    connect(newFile, &QAction::triggered, this, &MainWindow::createNewFile);
    connect(openFile, &QAction::triggered, this, &MainWindow::openExistingFile);
    connect(saveAction, &QAction::triggered, this, &MainWindow::saveAllItems);
    connect(shortcutsList, &QAction::triggered, this, &MainWindow::displayShortcuts);

    toolBar = addToolBar("ToolBar");
    toolBar->addWidget(fileToolButton);
    toolBar->addAction(createItem);
    toolBar->addAction(shortcutsList);
    toolBar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    toolBar->setMovable(false);
  }

  void MainWindow::setupCentralWidgets() {
    QSplitter* horizontalSplitter = new QSplitter(Qt::Horizontal, this);
    horizontalSplitter->setHandleWidth(3);
    setCentralWidget(horizontalSplitter);

    // Widget sinistro si occupa di gestire card degli item esistenti ed ha
    // il widget di ricerca in tempo reale
    leftListWidget = new View::List::ItemListWidget(this);
    connect(this, &MainWindow::deleteItemWidget, leftListWidget, &View::List::ItemListWidget::deleteItemWidget);
    connect(this, &MainWindow::clearList, leftListWidget, &View::List::ItemListWidget::clearList);
    connect(leftListWidget, &View::List::ItemListWidget::itemSelected, this, &MainWindow::getItemDetails);
    horizontalSplitter->addWidget(leftListWidget);

    QWidget* stackedLayoutContainer = new QWidget();
    rightStackedLayout = new QStackedLayout();
    stackedLayoutContainer->setLayout(rightStackedLayout);
    horizontalSplitter->addWidget(stackedLayoutContainer);

    // Widget destro si occupa di gestire info dettagliate degli item, possiede buttons di
    // edit e delete
    rightDetailWidget = new View::Details::ItemDetailWidget(this);
    connect(this, &MainWindow::displayItemDetails, rightDetailWidget, &View::Details::ItemDetailWidget::displayInfo);
    connect(rightDetailWidget, &View::Details::ItemDetailWidget::showEditWindow, this, &MainWindow::editExistingItem);
    connect(rightDetailWidget, &View::Details::ItemDetailWidget::deleteItem, this, &MainWindow::deleteItem);
    rightStackedLayout->addWidget(rightDetailWidget);

    // Ratio ad occhio e resize on startup della mainWindow
    horizontalSplitter->setSizes({1200, 2800});
    resize(1000, 600);

    setWindowTitle("Virtual Library");
  }

  void MainWindow::createNewItem() {
    if (jsonRepository == nullptr) {
      QMessageBox::critical(this, "Error", "No file is selected, please create a new json file\n"
                                           "or open an existing one before creating an item");
      return;
    }

    // Creo item quindi non passo reference ad alcun item
    editWidget = new View::Editors::ItemEditWidget(nullptr, jsonRepository, this);
    rightStackedLayout->addWidget(editWidget);

    connect(editWidget, &View::Editors::ItemEditWidget::itemCreated, this, &MainWindow::addItemToList);
    connect(editWidget, &View::Editors::ItemEditWidget::closeEditWidget, this, &MainWindow::closeEditWindow);

    rightStackedLayout->setCurrentWidget(editWidget);
  }

  void MainWindow::editExistingItem(unsigned int id) {
    Memory::ItemRepository& itemRepo = Memory::ItemRepository::getInstance();

    if (jsonRepository == nullptr) {
      QMessageBox::critical(this, "Error", "No file is selected, please create a new json file\n"
                                           "or open an existing one before creating an item");
      return;
    }

    // Modifico item, passo reference e const_cast poiche' creo item modificato ex-novo e
    // elimino quello vecchio
    editWidget = new View::Editors::ItemEditWidget(const_cast<Items::AbstractItem*>(&(itemRepo.get(id))), jsonRepository, this);

    rightStackedLayout->addWidget(editWidget);

    connect(editWidget, &View::Editors::ItemEditWidget::itemCreated, this, &MainWindow::addItemToList);
    connect(editWidget, &View::Editors::ItemEditWidget::closeEditWidget, this, &MainWindow::closeEditWindow);
    connect(editWidget, &View::Editors::ItemEditWidget::deleteItemWidget, leftListWidget, &View::List::ItemListWidget::deleteItemWidget);
    connect(editWidget, &View::Editors::ItemEditWidget::updateDetailInformation, rightDetailWidget, &View::Details::ItemDetailWidget::displayInfo);

    rightStackedLayout->setCurrentWidget(editWidget);
  }

  // Utility per reimpostare lo stato della memoria json e interna
  void MainWindow::clearMemory() {
    Memory::ItemRepository& itemRepo = Memory::ItemRepository::getInstance();

    emit clearList();
    itemRepo.clear();
    jsonRepository = nullptr;
  }

  void MainWindow::deleteItem(unsigned int id) {
    Memory::ItemRepository& itemRepo = Memory::ItemRepository::getInstance();

    emit deleteItemWidget(id);

    if (jsonRepository != nullptr) {
      jsonRepository->remove(id);
    }

    unsavedChanges = true;
    itemRepo.remove(id);
  }

  // Impedire creazione nuovi oggetti se non esiste repo collegata (aperta o ex-novo)
  void MainWindow::createNewFile() {
    QString path = QFileDialog::getSaveFileName(this, "Create new JSON file", "./", "JSON files *.json");

    if (path.isEmpty()) {
      QMessageBox::information(this, "No selection", "No path was selected");
      return;
    }

    if (!path.endsWith(".json", Qt::CaseInsensitive)) {
      path += ".json";
    }

    QFile file(path);
    if (!file.exists()) {
      if (!file.open(QIODevice::WriteOnly)) {
        QMessageBox::critical(this, "Error", "Failed to create file: " + file.errorString());
        return;
      }
      file.write("{}");
      file.close();
    }

    clearMemory();

    JSON::JsonReader reader;
    JSON::Json converter(reader);
    JSON::JsonFile dataMapper(path.toStdString(), converter);
    jsonRepository = new JSON::JsonRepository(dataMapper);
  }

  // Evitare casini se non apro file e do OK
  void MainWindow::openExistingFile() {
    QString path = QFileDialog::getOpenFileName(this, "Open File", "", "JSON Files (*.json);;All Files (*)");

    if (path.isEmpty()) {
        QMessageBox::information(this, "No selection", "No file was selected");
        return;
    }

    clearMemory();

    JSON::JsonReader reader;
    JSON::Json converter(reader);
    JSON::JsonFile dataMapper(path.toStdString(), converter);
    jsonRepository = new JSON::JsonRepository(dataMapper);
    Memory::ItemRepository& itemRepo = Memory::ItemRepository::getInstance();

    const std::map<unsigned int, Items::AbstractItem*>& refMap = jsonRepository->getRepository();
    for (auto&[key, value] : refMap) {
      itemRepo.add(value);
      leftListWidget->addItemCard(*value);
    }
  }

  void MainWindow::saveAllItems() {
    if (jsonRepository == nullptr) {
      return;
    }

    unsavedChanges = false;
    jsonRepository->store();
  }

  void MainWindow::displayShortcuts() {
    QMessageBox info;
    info.setIcon(QMessageBox::Information);
    info.resize(400, 200);
    info.setText("Useful keyboard shortcuts");
    info.setInformativeText("Create new item: Ctrl + N\n"
                            "Create new file: Ctrl + Shift + N\n"
                            "Open file: Ctrl + O\n"
                            "Save: Ctrl + Shift + S\n"
                            "Info: F1");
    info.exec();
  }

  void MainWindow::addItemToList(const Items::AbstractItem& item) {
    unsavedChanges = true;
    leftListWidget->addItemCard(item);
  }

  void MainWindow::closeEditWindow() {
    delete editWidget;
    rightStackedLayout->setCurrentWidget(rightDetailWidget);
  }

  void MainWindow::getItemDetails(unsigned int id) {
    Memory::ItemRepository& itemRepo = Memory::ItemRepository::getInstance();

    const Items::AbstractItem& item = itemRepo.get(id);
    emit displayItemDetails(item);
  }

  // QoL per non far perdere modifiche non salvate
  void MainWindow::closeEvent(QCloseEvent* event) {
    if (unsavedChanges) {
      QMessageBox::StandardButton reply;
      reply = QMessageBox::question(this, "Unsaved changes", "You have unsaved changes, do you wish to exit?",
                            QMessageBox::Yes | QMessageBox::No);

      if (reply == QMessageBox::Yes) {
        event->accept();
      } else {
        event->ignore();
      }
    } else {
      event->accept();
    }
  }

}


