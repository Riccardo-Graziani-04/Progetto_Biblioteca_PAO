#include <QVBoxLayout>
#include <QFormLayout>

#include "MovieEditWidget.h"
#include "../../Model/Items/Movie.h"
#include "../../Model/Utility/EnumsConvertions.h"

namespace View::Editors {

  MovieEditWidget::MovieEditWidget(QWidget *parent)
  : AbstractItemEditWidget{parent}
  {
    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    QFormLayout* specificInputsLayout = new QFormLayout();
    specificInputsLayout->setLabelAlignment(Qt::AlignLeft);
    mainLayout->addLayout(specificInputsLayout);

    languageInput = new QLineEdit();
    languageInput->setPlaceholderText("Movie language");
    specificInputsLayout->addRow("Language", languageInput);

    releaseYearInput = new QSpinBox();
    releaseYearInput->setRange(1900, 2025);
    specificInputsLayout->addRow("Year", releaseYearInput);

    durationInput = new QSpinBox();
    durationInput->setRange(60, 180);
    specificInputsLayout->addRow("Duration (min)", durationInput);

    genreInput = new QComboBox();
    genreInput->addItems(QStringList() << "Fantasy"
                           << "Thriller" << "Sci-Fi"
                           << "Action" << "Historical"
                           << "Romance" << "Mystery"
                           << "Horror" << "Classic");
    specificInputsLayout->addRow("Genre", genreInput);

    ageRatingInput = new QComboBox();
    ageRatingInput->addItems(QStringList() << "Children"
                               << "Teens" << "Accompanied Teens"
                               << "Adults");
    specificInputsLayout->addRow("Age rating", ageRatingInput);

    setLayout(mainLayout);
  }

  void MovieEditWidget::setValues(const Items::Movie& item) {
    languageInput->setText(QString::fromStdString(item.getLanguage()));
    releaseYearInput->setValue(item.getReleaseYear());
    durationInput->setValue(item.getDuration());
    genreInput->setCurrentText(QString::fromStdString(Enums::bookMovieGenresToString(item.getGenre())));
    ageRatingInput->setCurrentText(QString::fromStdString(Enums::movieAgeRatingsToString(item.getAgeRating())));
  }

  Items::AbstractItem* MovieEditWidget::createNewItem(QString title, unsigned int id, QString author, QString image) {
    return new Items::Movie(title.toStdString(),
                            id,
                            author.toStdString(),
                            static_cast<unsigned int>(releaseYearInput->value()),
                            image.toStdString(),
                            (languageInput->text()).toStdString(),
                            static_cast<unsigned int>(durationInput->value()),
                            Enums::stringToBookMovieGenre((genreInput->currentText()).toStdString()),
                            Enums::stringToAgeRating((ageRatingInput->currentText()).toStdString())
                            );
  }

}
