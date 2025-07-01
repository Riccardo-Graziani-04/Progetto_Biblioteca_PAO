#ifndef ITEMVISITOR_H
#define ITEMVISITOR_H

namespace Items {

  class Book; class Movie; class Music;

}

namespace Visitor {

  class ItemVisitor {

    public:
      virtual ~ItemVisitor() = default;

      virtual void visit(Items::Book& book) = 0;
      virtual void visit(Items::Movie& movie) = 0;
      virtual void visit(Items::Music& music) = 0;

  };

}

#endif // ITEMVISITOR_H
