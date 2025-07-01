#ifndef ABSTRACTITEM_H
#define ABSTRACTITEM_H

#include <string>

#include "../Utility/ItemVisitor.h"
#include "../Utility/ConstItemVisitor.h"

namespace Items {

  using String = std::string;

  class AbstractItem {

    private:
      String title;
      unsigned int id;
      String author;
      unsigned int releaseYear;
      // Path relativa al folder delle immagini
      String image;


    public:
      AbstractItem(String title,
                   unsigned int id,
                   String author,
                   unsigned int releaseYear,
                   String image);
      virtual ~AbstractItem() = default;

      virtual void accept(Visitor::ItemVisitor& visitor) = 0;
      virtual void accept(Visitor::ConstItemVisitor& constVisitor) const = 0;

      const String& getTitle() const;
      unsigned int getID() const;
      const String& getAuthor() const;
      unsigned int getReleaseYear() const;
      const String& getImage() const;

      AbstractItem& setTitle(const String& title);
      AbstractItem& setID(unsigned int id);
      AbstractItem& setAuthor(const String& author);
      AbstractItem& setReleaseYear(unsigned int releaseYear);
      AbstractItem& setImage(const String& image);

  };

}

#endif // ABSTRACTITEM_H
