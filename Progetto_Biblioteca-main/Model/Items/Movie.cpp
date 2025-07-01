#include "Movie.h"

namespace Items {

  Movie::Movie(String title,
               unsigned int id,
               String author,
               unsigned int releaseYear,
               String image,
               String language,
               unsigned int duration,
               Enums::BookMovieGenres genre,
               Enums::AgeRatings ageRating)
  : AbstractItem(title, id, author, releaseYear, image),
    language(language),
    duration(duration),
    genre(genre),
    ageRating(ageRating) {}

  const String& Movie::getLanguage() const {
    return language;
  }

  unsigned int Movie::getDuration() const {
    return duration;
  }

  Enums::BookMovieGenres Movie::getGenre() const {
    return genre;
  }

  Enums::AgeRatings Movie::getAgeRating() const {
    return ageRating;
  }

  Movie& Movie::setLanguage(const String& language) {
    this->language = language;
    return *this;
  }

  Movie& Movie::setDuration(unsigned int duration) {
    this->duration = duration;
    return *this;
  }

  Movie& Movie::setGenre(Enums::BookMovieGenres genre) {
    this->genre = genre;
    return *this;
  }

  Movie& Movie::setAgeRating(Enums::AgeRatings ageRating) {
    this->ageRating = ageRating;
    return *this;
  }

  void Movie::accept(Visitor::ItemVisitor& visitor) {
    visitor.visit(*this);
  }

  void Movie::accept(Visitor::ConstItemVisitor& constVisitor) const {
    constVisitor.visit(*this);
  }

}
