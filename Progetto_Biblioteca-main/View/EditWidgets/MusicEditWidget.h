#ifndef MUSICEDITWIDGET_H
#define MUSICEDITWIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <QSpinBox>
#include <QComboBox>
#include <QCheckBox>

#include "AbstractItemEditWidget.h"

namespace View::Editors {

  class MusicEditWidget : public AbstractItemEditWidget {
    Q_OBJECT

    private:
      QLineEdit* albumInput;
      QSpinBox* releaseYearInput;
      QSpinBox* durationInput;
      QCheckBox* explicitLanguageInput;
      QComboBox* genreInput;

    public:
      explicit MusicEditWidget(QWidget *parent = nullptr);

      void setValues(const Items::Music& item);
      Items::AbstractItem* createNewItem(QString title, unsigned int id, QString author, QString image);

    signals:

  };

}

#endif // MUSICEDITWIDGET_H
