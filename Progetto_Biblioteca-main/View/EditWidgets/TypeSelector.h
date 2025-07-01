#ifndef TYPESELECTOR_H
#define TYPESELECTOR_H

#include <QComboBox>

#include "../../Model/Utility/ConstItemVisitor.h"
#include "../../Model/Items/Book.h"
#include "../../Model/Items/Movie.h"
#include "../../Model/Items/Music.h"

namespace View::Editors {

  class TypeSelector : public Visitor::ConstItemVisitor {

    private:
      QComboBox* comboBox;

    public:
      TypeSelector(QComboBox* comboBox);

      void visit(const Items::Book& book) override;
      void visit(const Items::Movie& movie) override;
      void visit(const Items::Music& music) override;

      QComboBox* getComboBox();
      TypeSelector& setComboBox(QComboBox* comboBox);

  };

}


#endif // TYPESELECTOR_H
