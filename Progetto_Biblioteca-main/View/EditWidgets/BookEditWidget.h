#ifndef BOOKEDITWIDGET_H
#define BOOKEDITWIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <QSpinBox>
#include <QComboBox>

#include "AbstractItemEditWidget.h"

namespace View::Editors {

  class BookEditWidget : public AbstractItemEditWidget {
    Q_OBJECT

    private:
      QLineEdit* publisherInput;
      QLineEdit* languageInput;
      QSpinBox* releaseYearInput;
      QComboBox* genreInput;

    public:
      explicit BookEditWidget(QWidget *parent = nullptr);

      void setValues(const Items::Book& item);
      Items::AbstractItem* createNewItem(QString title, unsigned int id, QString author, QString image);

    signals:

  };

}


#endif // BOOKEDITWIDGET_H
