#ifndef MOVIE_H
#define MOVIE_H

#include "AbstractItem.h"
#include "../Utility/ItemsEnums.h"

namespace Items {

  class Movie : public AbstractItem {

    private:
      String language;
      unsigned int duration;
      Enums::BookMovieGenres genre;
      Enums::AgeRatings ageRating;

    public:
      Movie(String title,
            unsigned int id,
            String author,
            unsigned int releaseYear,
            String image,
            String language,
            unsigned int duration,
            Enums::BookMovieGenres genre,
            Enums::AgeRatings ageRating);

      virtual void accept(Visitor::ItemVisitor& visitor) final;
      virtual void accept(Visitor::ConstItemVisitor& constVisitor) const final;

      const String& getLanguage() const;
      unsigned int getDuration() const;
      Enums::BookMovieGenres getGenre() const;
      Enums::AgeRatings getAgeRating() const;

      Movie& setLanguage(const String& language);
      Movie& setDuration(unsigned int duration);
      Movie& setGenre(Enums::BookMovieGenres genre);
      Movie& setAgeRating(Enums::AgeRatings ageRating);

  };

}

#endif // MOVIE_H
