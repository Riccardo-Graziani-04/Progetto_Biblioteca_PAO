#ifndef ITEMDETAILWIDGET_H
#define ITEMDETAILWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>

#include "../../Model/Utility/ConstItemVisitor.h"
#include "../../Model/Items/AbstractItem.h"

namespace View::Details {

  class ItemDetailWidget : public QWidget, public Visitor::ConstItemVisitor {
    Q_OBJECT

    private:
      QVBoxLayout* mainLayout;
      QHBoxLayout* topLayout;
      QVBoxLayout* detailsLayout;
      QLabel* titleLabel;
      QLabel* idLabel;
      QPushButton* editButton;
      QPushButton* deleteButton;

      unsigned int ID;

      void clearLayout(QLayout* layout);
      void onEditButtonClick();
      void onDeleteButtonClick();

    public:
      explicit ItemDetailWidget(QWidget* parent = nullptr);

      void visit(const Items::Book& book);
      void visit(const Items::Movie& movie);
      void visit(const Items::Music& music);

    public slots:
      void displayInfo(const Items::AbstractItem& item);

    signals:
      void showEditWindow(unsigned int id);
      void deleteItem(unsigned int id);

  };

}

#endif // ITEMDETAILWIDGET_H
