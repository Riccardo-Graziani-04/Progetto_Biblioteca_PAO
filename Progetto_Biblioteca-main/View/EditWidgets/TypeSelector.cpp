#include "TypeSelector.h"

namespace View::Editors {

  TypeSelector::TypeSelector(QComboBox* comboBox)
  : comboBox(comboBox) {}

  void TypeSelector::visit(const Items::Book& book) {
    (void) book;
    comboBox->setCurrentIndex(0);
  }

  void TypeSelector::visit(const Items::Movie& movie) {
    (void) movie;
    comboBox->setCurrentIndex(1);
  }

  void TypeSelector::visit(const Items::Music& music) {
    (void) music;
    comboBox->setCurrentIndex(2);
  }

  QComboBox* TypeSelector::getComboBox() {
    return comboBox;
  }

  TypeSelector& TypeSelector::setComboBox(QComboBox* comboBox) {
    this->comboBox = comboBox;
    return *this;
  }

}

