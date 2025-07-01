#include "Book.h"

namespace Items {

  Book::Book(String title,
             unsigned int id,
             String author,
             unsigned int releaseYear,
             String image,
             String publisher,
             String language,
             Enums::BookMovieGenres genre)
  : AbstractItem(title, id, author, releaseYear, image),
    publisher(publisher),
    language(language),
    genre(genre) {}

  const String& Book::getPublisher() const {
    return publisher;
  }

  const String& Book::getLanguage() const {
    return language;
  }

  Enums::BookMovieGenres Book::getGenre() const {
    return genre;
  }

  Book& Book::setPublisher(const String& publisher) {
    this->publisher = publisher;
    return *this;
  }

  Book& Book::setLanguage(const String& language) {
    this->language = language;
    return *this;
  }

  Book& Book::setGenre(Enums::BookMovieGenres genre) {
    this->genre = genre;
    return *this;
  }

  void Book::accept(Visitor::ItemVisitor& visitor) {
    visitor.visit(*this);
  }

  void Book::accept(Visitor::ConstItemVisitor& constVisitor) const {
    constVisitor.visit(*this);
  }

}

