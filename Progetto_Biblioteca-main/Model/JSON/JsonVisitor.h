#ifndef JSONVISITOR_H
#define JSONVISITOR_H

#include <QJsonObject>

#include "../Utility/ConstItemVisitor.h"
#include "../Items/Book.h"
#include "../Items/Movie.h"
#include "../Items/Music.h"

namespace JSON {

  class JsonVisitor : public Visitor::ConstItemVisitor {

    private:
      QJsonObject obj;

    public:
      JsonVisitor();

      QJsonObject getObj() const;
      void visit(const Items::Book& book);
      void visit(const Items::Movie& movie);
      void visit(const Items::Music& music);
};

}

#endif // JSONVISITOR_H
