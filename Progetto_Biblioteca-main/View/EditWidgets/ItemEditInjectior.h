#ifndef ITEMEDITINJECTIOR_H
#define ITEMEDITINJECTIOR_H

#include "../../Model/Utility/ConstItemVisitor.h"
#include "BookEditWidget.h"
#include "MovieEditWidget.h"
#include "MusicEditWidget.h"

namespace View::Editors {

  class ItemEditInjectior : public Visitor::ConstItemVisitor {

    private:
      View::Editors::BookEditWidget& bookEditWidget;
      View::Editors::MovieEditWidget& movieEditWidget;
      View::Editors::MusicEditWidget& musicEditWidget;

    public:
      ItemEditInjectior(View::Editors::BookEditWidget& bookEditWidget,
                        View::Editors::MovieEditWidget& movieEditWidget,
                        View::Editors::MusicEditWidget& musicEditWidget);

      void visit(const Items::Book& book);
      void visit(const Items::Movie& movie);
      void visit(const Items::Music& music);

  };

}

#endif // ITEMEDITINJECTIOR_H
