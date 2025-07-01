#ifndef ENUMSCONVERTIONS_H
#define ENUMSCONVERTIONS_H

#include "ItemsEnums.h"
#include <string>

using std::string;

namespace Enums {

  using String = std::string;

  String bookMovieGenresToString(BookMovieGenres genre);
  String musicGenreToString(MusicGenres genre);
  String movieAgeRatingsToString(AgeRatings ageRating);

  BookMovieGenres stringToBookMovieGenre(String genre);
  MusicGenres stringToMusicGenres(String genre);
  AgeRatings stringToAgeRating(String ageRating);

}

#endif // ENUMSCONVERTIONS_H
