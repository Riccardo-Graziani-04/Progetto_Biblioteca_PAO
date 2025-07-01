#ifndef CONSTITEMVISITOR_H
#define CONSTITEMVISITOR_H

namespace Items {

  class Book; class Movie; class Music;

}

namespace Visitor {

  class ConstItemVisitor {

    public:
      virtual ~ConstItemVisitor() = default;

      virtual void visit(const Items::Book& book) = 0;
      virtual void visit(const Items::Movie& movie) = 0;
      virtual void visit(const Items::Music& music) = 0;

  };

}

#endif // CONSTITEMVISITOR_H
