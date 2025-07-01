#include <QVBoxLayout>
#include <QLabel>
#include <QFormLayout>
#include <QComboBox>
#include <QStackedLayout>
#include <QMessageBox>
#include <QFileDialog>

#include "../../Model/JSON/JsonRepository.h"
#include "../../Model/Memory/ItemRepository.h"
#include "ItemEditWidget.h"
#include "BookEditWidget.h"
#include "MovieEditWidget.h"
#include "MusicEditWidget.h"
#include "TypeSelector.h"
#include "ItemEditInjectior.h"

#include <QDebug>

namespace View::Editors {

  ItemEditWidget::ItemEditWidget(Items::AbstractItem* item, JSON::JsonRepository* repository, QWidget* parent)
  : QWidget{parent}, currentItem(item), repository(repository)
  {
      setupBaseInputs();
  }

  void ItemEditWidget::setupBaseInputs() {
    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    // Campi dati condivisi da tutti gli item
    QLabel* title = new QLabel("Editor");
    title->setAlignment(Qt::AlignCenter | Qt::AlignTop);
    mainLayout->addWidget(title);

    QFormLayout* baseInputsForm = new QFormLayout();
    baseInputsForm->setLabelAlignment(Qt::AlignLeft);
    mainLayout->addLayout(baseInputsForm);

    titleInput = new QLineEdit();
    titleInput->setPlaceholderText("Item title");

    // Check usati per impostare dati nel caso stia modificando item
    if (currentItem != nullptr) { titleInput->setText(QString::fromStdString(currentItem->getTitle())); }
    baseInputsForm->addRow("Title", titleInput);

    idInput = new QSpinBox();
    idInput->setRange(0, 9999);

    if (currentItem != nullptr) { idInput->setValue(currentItem->getID()); }
    baseInputsForm->addRow("ID", idInput);

    authorInput = new QLineEdit();
    authorInput->setPlaceholderText("Item author");

    imageSelection = new QPushButton();
    imageSelection->setText("Sfoglia");
    connect(imageSelection, &QPushButton::pressed, this, &ItemEditWidget::imageLoaded);

    if (currentItem != nullptr) { selectedImage = QString::fromStdString(currentItem->getImage()); }
    baseInputsForm->addRow("Image", imageSelection);

    if (currentItem != nullptr) { authorInput->setText(QString::fromStdString(currentItem->getAuthor())); }
    baseInputsForm->addRow("Author", authorInput);

    QComboBox* itemSelector = new QComboBox();
    itemSelector->addItems(QStringList() << "Book" << "Movie" << "Music");
    baseInputsForm->addRow("Item", itemSelector);

    // Se sto modificando item faccio apparire da subito i campi corretti
    if (currentItem != nullptr) {
      TypeSelector typeSelector(itemSelector);
      currentItem->accept(typeSelector);
    }

    specificItemFields = new QStackedLayout();
    mainLayout->addLayout(specificItemFields);

    // Widget per i campi specifici di ogni item

    // BOOK
    BookEditWidget* bookWidget = new BookEditWidget();
    specificItemFields->addWidget(bookWidget);
    editWidgetsObjs.push_back(bookWidget);

    // MOVIE
    MovieEditWidget* movieWidget = new MovieEditWidget();
    specificItemFields->addWidget(movieWidget);
    editWidgetsObjs.push_back(movieWidget);

    // MUSIC
    MusicEditWidget* musicWidget = new MusicEditWidget();
    specificItemFields->addWidget(musicWidget);
    editWidgetsObjs.push_back(musicWidget);

    if (currentItem != nullptr) {
      View::Editors::ItemEditInjectior injector(*bookWidget, *movieWidget, *musicWidget);
      currentItem->accept(injector);
    }
    comboBoxTypeChanged(itemSelector->currentIndex());

    QHBoxLayout* buttonsLayout = new QHBoxLayout();
    mainLayout->addLayout(buttonsLayout);

    // Pulsanti di conferma dei dati e chiusura della finestra
    confirmButton = new QPushButton("Ok");
    buttonsLayout->addWidget(confirmButton);

    closeButton = new QPushButton("Close");
    buttonsLayout->addWidget(closeButton);

    connect(confirmButton, &QPushButton::pressed, this, &ItemEditWidget::confirmButtonPressed);
    connect(closeButton, &QPushButton::pressed, this, &ItemEditWidget::closeButtonPressed);
    connect(itemSelector, SIGNAL(currentIndexChanged(int)), this, SLOT(comboBoxTypeChanged(int)));

    setLayout(mainLayout);
  }

  void ItemEditWidget::imageLoaded() {
    // Sembra che solo png funzioni non capisco perche' ;-;
    QString filePath = QFileDialog::getOpenFileName(this, "Open Image", "", "Images (*.png *.jpeg *.bmp *.jpg)");

    if (!filePath.isEmpty()) {
      QString folderPath = "Resources/Images";
      QDir dir;

      if (!dir.exists(folderPath)) {
        dir.mkpath(folderPath);
      }

      // Salvo immagini in un folder dedicato e le riuso
      QString fileSavePath = folderPath + "/" + QFileInfo(filePath).fileName();

      if (QFile::exists(fileSavePath)) {
        QMessageBox::information(this, "Notice", "Image already exists.");
        selectedImage = fileSavePath;
      } else {
        if (!QFile::copy(filePath, fileSavePath)) {
          QMessageBox::warning(this, "Error", "Failed to save image");
          return;
        }
        selectedImage = fileSavePath;
      }
    }
  }

  void ItemEditWidget::confirmButtonPressed() {
    Memory::ItemRepository& itemRepo = Memory::ItemRepository::getInstance();
    View::Editors::AbstractItemEditWidget* creator = editWidgetsObjs[specificItemFields->currentIndex()];

    // Se sto modificando, elimino da entrambe le repo
    if (currentItem != nullptr) {
      if (repository != nullptr) {
        repository->remove(currentItem->getID());
      }

      emit deleteItemWidget(currentItem->getID());
      itemRepo.remove(currentItem->getID());

      currentItem = nullptr;
    }

    // Creo nuovo item con i creator
    currentItem = creator->createNewItem(titleInput->text(), idInput->value(), authorInput->text(), selectedImage);

    if (itemRepo.find(idInput->value())) {
      modifiedItemFlag = true;
      QMessageBox::critical(this, "Error", "This ID is already being used");
      delete currentItem;
      currentItem = nullptr;
      return;
    }

    itemRepo.add(currentItem);

    if (repository != nullptr) {
      repository->update(currentItem);
    }

    emit updateDetailInformation(*currentItem);
    emit itemCreated(*currentItem);
    emit closeEditWidget();
  }

  void ItemEditWidget::closeButtonPressed() {
    if (modifiedItemFlag) {
      QMessageBox::StandardButton reply;
      reply = QMessageBox::question(this, "Deleted item", "If you modified an existing item with an ID that was already\n"
                                                          "in use, that item was deleted.\n To restore it, change the ID"
                                                          "field back to the previous value or choose an ID not currently in use.\n"
                                                          "Press Close to close this popup or Ignore to close the edit window.",
                                                          QMessageBox::Close | QMessageBox::Ignore);
      if (reply == QMessageBox::Close) {
        return;
      }
    }
    emit closeEditWidget();
  }

  void ItemEditWidget::comboBoxTypeChanged(int index) {
    specificItemFields->setCurrentIndex(index);
  }

}

