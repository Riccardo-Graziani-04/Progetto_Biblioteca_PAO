#ifndef ITEMCARDWIDGET_H
#define ITEMCARDWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPixmap>

#include "../../Model/Items/AbstractItem.h"
#include "../../Model/Utility/ConstItemVisitor.h"

namespace View::List {

  class ItemCardWidget : public QWidget, public Visitor::ConstItemVisitor {
    Q_OBJECT

    private:
      QLabel* iconLabel;
      QLabel* titleLabel;
      QLabel* authorLabel;
      const Items::AbstractItem& item;

    public:
      ItemCardWidget(const Items::AbstractItem& item, QWidget* parent = nullptr);

      void visit(const Items::Book& book);
      void visit(const Items::Movie& movie);
      void visit(const Items::Music& music);

      unsigned int getItemID() const;
      QString getTitle() const;
      const Items::AbstractItem& getItem() const;

  };

}

#endif // ITEMCARDWIDGET_H
