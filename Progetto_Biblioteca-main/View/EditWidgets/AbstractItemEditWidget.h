#ifndef ABSTRACTITEMEDITWIDGET_H
#define ABSTRACTITEMEDITWIDGET_H

#include <QWidget>

#include "../../Model/Items/AbstractItem.h"

namespace View::Editors {

  class AbstractItemEditWidget : public QWidget {
    Q_OBJECT

    public:
      explicit AbstractItemEditWidget(QWidget* parent = nullptr);
      virtual ~AbstractItemEditWidget() = default;

      virtual Items::AbstractItem* createNewItem(QString title,
                                                 unsigned int id,
                                                 QString author,
                                                 QString image) = 0;

  };

}

#endif // ABSTRACTITEMEDITWIDGET_H
