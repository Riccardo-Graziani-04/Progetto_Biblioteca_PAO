#ifndef MOVIEEDITWIDGET_H
#define MOVIEEDITWIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <QSpinBox>
#include <QComboBox>

#include "AbstractItemEditWidget.h"

namespace View::Editors {

  class MovieEditWidget : public AbstractItemEditWidget {
    Q_OBJECT

    private:
      QLineEdit* languageInput;
      QSpinBox* releaseYearInput;
      QSpinBox* durationInput;
      QComboBox* genreInput;
      QComboBox* ageRatingInput;

    public:
      explicit MovieEditWidget(QWidget *parent = nullptr);

      void setValues(const Items::Movie& item);
      Items::AbstractItem* createNewItem(QString title, unsigned int id, QString author, QString image);

  };

}

#endif // MOVIEEDITWIDGET_H
