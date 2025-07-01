#include "ItemEditInjectior.h"

namespace View::Editors {

  ItemEditInjectior::ItemEditInjectior(View::Editors::BookEditWidget& bookEditWidget,
                                       View::Editors::MovieEditWidget& movieEditWidget,
                                       View::Editors::MusicEditWidget& musicEditWidget)
  : bookEditWidget(bookEditWidget),
    movieEditWidget(movieEditWidget),
    musicEditWidget(musicEditWidget) {}

  void ItemEditInjectior::visit(const Items::Book& book) {
    bookEditWidget.setValues(book);
  }

  void ItemEditInjectior::visit(const Items::Movie& movie) {
    movieEditWidget.setValues(movie);
  }

  void ItemEditInjectior::visit(const Items::Music& music) {
    musicEditWidget.setValues(music);
  }

}
