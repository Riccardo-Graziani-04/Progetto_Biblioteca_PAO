#ifndef ITEMEDITWIDGET_H
#define ITEMEDITWIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <QSpinBox>
#include <QStackedLayout>
#include <QPushButton>

#include "../../Model/Items/AbstractItem.h"
#include "../../Model/JSON/JsonRepository.h"
#include "AbstractItemEditWidget.h"

namespace View::Editors {

  class ItemEditWidget : public QWidget {
    Q_OBJECT

    private:
      // Eventuale item che sto modificando
      Items::AbstractItem* currentItem;
      QLineEdit* titleInput;
      QSpinBox* idInput;
      QLineEdit* authorInput;
      QStackedLayout* specificItemFields;
      QPushButton* imageSelection;
      QString selectedImage;
      QPushButton* confirmButton;
      QPushButton* closeButton;
      QVector<AbstractItemEditWidget*> editWidgetsObjs;
      JSON::JsonRepository* repository;
      // Gestione edge case
      bool modifiedItemFlag = false;

      void setupBaseInputs();
      void checkForEmptyInput();

    private slots:
      void imageLoaded();
      void confirmButtonPressed();
      void closeButtonPressed();
      void comboBoxTypeChanged(int index);

    public:
      ItemEditWidget(Items::AbstractItem* item,
                     JSON::JsonRepository* repository = nullptr, // Default non passo item
                     QWidget* parent = nullptr);

    signals:
      void deleteItemWidget(unsigned int id);
      void updateDetailInformation(const Items::AbstractItem& item);
      void itemCreated(const Items::AbstractItem& item);
      void closeEditWidget();

  };

}

#endif // ITEMEDITWIDGET_H
