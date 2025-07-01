#include <stdexcept>

#include "EnumsConvertions.h"

namespace Enums {

  String bookMovieGenresToString(BookMovieGenres genre) {
    switch (genre) {
      case BookMovieGenres::Fantasy: return "Fantasy";
      case BookMovieGenres::SciFi: return "Sci-Fi";
      case BookMovieGenres::Thriller: return "Thriller";
      case BookMovieGenres::Action: return "Action";
      case BookMovieGenres::Historical: return "Historical";
      case BookMovieGenres::Romance: return "Romance";
      case BookMovieGenres::Mystery: return "Mystery";
      case BookMovieGenres::Horror: return "Horror";
      case BookMovieGenres::Classic: return "Classic";
      default: return "Error";
    }
  }

  String musicGenreToString(MusicGenres genre) {
    switch (genre) {
      case MusicGenres::Classical: return "Classical";
      case MusicGenres::Rap: return "Rap";
      case MusicGenres::Electronic: return "Electronic";
      case MusicGenres::Blues: return "Blues";
      case MusicGenres::Jazz: return "Jazz";
      case MusicGenres::HipPop: return "Hip-Pop";
      case MusicGenres::Rock: return "Rock";
      case MusicGenres::Metal: return "Metal";
      default: return "Error";
    }
  }

  String movieAgeRatingsToString(AgeRatings ageRating) {
    switch (ageRating) {
      case AgeRatings::Children: return "Children";
      case AgeRatings::Teens: return "Teens";
      case AgeRatings::AccompaniedTeens: return "Accompanied Teens";
      case AgeRatings::Adults: return "Adults";
      default: return "Error";
    }
  }

  BookMovieGenres stringToBookMovieGenre(String genre) {
    if (genre == "Fantasy") return BookMovieGenres::Fantasy;
    if (genre == "Sci-Fi") return BookMovieGenres::SciFi;
    if (genre == "Thriller") return BookMovieGenres::Thriller;
    if (genre == "Action") return BookMovieGenres::Action;
    if (genre == "Historical") return BookMovieGenres::Historical;
    if (genre == "Romance") return BookMovieGenres::Romance;
    if (genre == "Mystery") return BookMovieGenres::Mystery;
    if (genre == "Horror") return BookMovieGenres::Horror;
    if (genre == "Classic") return BookMovieGenres::Classic;
    throw std::invalid_argument("Invalid string");
  }

  MusicGenres stringToMusicGenres(String genre) {
    if (genre == "Classical") return MusicGenres::Classical;
    if (genre == "Rap") return MusicGenres::Rap;
    if (genre == "Electronic") return MusicGenres::Electronic;
    if (genre == "Blues") return MusicGenres::Blues;
    if (genre == "Jazz") return MusicGenres::Jazz;
    if (genre == "Hip-Pop") return MusicGenres::HipPop;
    if (genre == "Rock") return MusicGenres::Rock;
    if (genre == "Metal") return MusicGenres::Metal;
    throw std::invalid_argument("Invalid string");
  }

  AgeRatings stringToAgeRating(String ageRating) {
    if (ageRating == "Children") return AgeRatings::Children;
    if (ageRating == "Teens") return AgeRatings::Teens;
    if (ageRating == "Accompanied Teens") return AgeRatings::AccompaniedTeens;
    if (ageRating == "Adults") return AgeRatings::Adults;
    throw std::invalid_argument("Invalid string");
  }

}
