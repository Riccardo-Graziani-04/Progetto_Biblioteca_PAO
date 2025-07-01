#ifndef BOOK_H
#define BOOK_H

#include "AbstractItem.h"
#include "../Utility/ItemsEnums.h"

namespace Items {

  class Book : public AbstractItem {

    private:
      String publisher;
      String language;
      Enums::BookMovieGenres genre;

    public:
      Book(String title,
           unsigned int id,
           String author,
           unsigned int releaseYear,
           String image,
           String publisher,
           String language,
           Enums::BookMovieGenres genre);

      virtual void accept(Visitor::ItemVisitor& visitor) final;
      virtual void accept(Visitor::ConstItemVisitor& constVisitor) const final;

      const String& getPublisher() const;
      const String& getLanguage() const;
      Enums::BookMovieGenres getGenre() const;

      Book& setPublisher(const String& publisher);
      Book& setLanguage(const String& language);
      Book& setGenre(Enums::BookMovieGenres genre);

  };

}

#endif // BOOK_H
