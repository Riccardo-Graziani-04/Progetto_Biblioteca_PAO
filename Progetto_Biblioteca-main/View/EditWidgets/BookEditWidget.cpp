#include <QVBoxLayout>
#include <QFormLayout>

#include "BookEditWidget.h"
#include "../../Model/Items/Book.h"
#include "../../Model/Utility/EnumsConvertions.h"

namespace View::Editors {

  BookEditWidget::BookEditWidget(QWidget *parent)
  : AbstractItemEditWidget{parent}
  {
    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    QFormLayout* specificInputsLayout = new QFormLayout();
    specificInputsLayout->setLabelAlignment(Qt::AlignLeft);
    mainLayout->addLayout(specificInputsLayout);

    publisherInput = new QLineEdit();
    publisherInput->setPlaceholderText("Publishing house");
    specificInputsLayout->addRow("Publisher", publisherInput);

    languageInput = new QLineEdit();
    languageInput->setPlaceholderText("Book language");
    specificInputsLayout->addRow("Language", languageInput);

    releaseYearInput = new QSpinBox();
    releaseYearInput->setRange(0, 2025);
    specificInputsLayout->addRow("Year", releaseYearInput);

    genreInput = new QComboBox();
    genreInput->addItems(QStringList() << "Fantasy"
                           << "Thriller" << "Sci-Fi"
                           << "Action" << "Historical"
                           << "Romance" << "Mystery"
                           << "Horror" << "Classic");
    specificInputsLayout->addRow("Genre", genreInput);

    setLayout(mainLayout);
  }

  void BookEditWidget::setValues(const Items::Book& item) {
    publisherInput->setText(QString::fromStdString(item.getPublisher()));
    languageInput->setText(QString::fromStdString(item.getLanguage()));
    releaseYearInput->setValue(item.getReleaseYear());
    genreInput->setCurrentText(QString::fromStdString(Enums::bookMovieGenresToString(item.getGenre())));
  }

  Items::AbstractItem* BookEditWidget::createNewItem(QString title, unsigned int id, QString author, QString image) {
    return new Items::Book(title.toStdString(),
                           id,
                           author.toStdString(),
                           static_cast<unsigned int>(releaseYearInput->value()),
                           image.toStdString(),
                           (publisherInput->text()).toStdString(),
                           (languageInput->text()).toStdString(),
                           Enums::stringToBookMovieGenre((genreInput->currentText()).toStdString())
                           );
  }

}
