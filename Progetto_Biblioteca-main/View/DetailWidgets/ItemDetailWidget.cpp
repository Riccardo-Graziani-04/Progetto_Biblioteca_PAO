#include <QSlider>
#include <QMessageBox>

#include "ItemDetailWidget.h"
#include "../../Model/Utility/EnumsConvertions.h"
#include "../../Model/Items/Book.h"
#include "../../Model/Items/Movie.h"
#include "../../Model/Items/Music.h"

namespace View::Details {

  ItemDetailWidget::ItemDetailWidget(QWidget *parent)
    : QWidget{parent}
  {
    mainLayout = new QVBoxLayout(this);
    topLayout = new QHBoxLayout();
    detailsLayout = new QVBoxLayout();

    titleLabel = new QLabel();
    topLayout->addWidget(titleLabel);

    idLabel = new QLabel();
    topLayout->addWidget(idLabel);
    topLayout->addStretch();

    editButton = new QPushButton(QIcon(":icons/Resources/edit.png"), " Edit");
    deleteButton = new QPushButton(QIcon(":icons/Resources/delete.png"), " Delete");

    connect(editButton, &QPushButton::clicked, this, &ItemDetailWidget::onEditButtonClick);
    connect(deleteButton, &QPushButton::clicked, this, &ItemDetailWidget::onDeleteButtonClick);

    topLayout->addWidget(editButton);
    topLayout->addWidget(deleteButton);

    mainLayout->addLayout(topLayout);
    mainLayout->addLayout(detailsLayout);
    setLayout(mainLayout);
  }

  void ItemDetailWidget::clearLayout(QLayout* layout) {
    titleLabel->clear();
    idLabel->clear();

    if (!layout) {
      return;
    }

    // Ricorsivamente pulisco il layout precedente, controllo per ogni
    // elemento se sono presenti widget figli, elimino e poi infine
    // elimino il padre
    while (QLayoutItem* item = layout->takeAt(0)) {
      if (QWidget* widget = item->widget()) {
        delete widget;
      } else if (QLayout* childLayout = item->layout()) {
        clearLayout(childLayout);
      }
      delete item;
    }
  }

  void ItemDetailWidget::displayInfo(const Items::AbstractItem& item) {
    clearLayout(detailsLayout);
    titleLabel->setText("<b>Title:</b> " + QString::fromStdString(item.getTitle()) + "   ");
    idLabel->setText("<b>ID:</b> " + QString::number(item.getID()));
    ID = item.getID();
    item.accept(*this);
  }

  // Signals verso mainWindow
  void ItemDetailWidget::onEditButtonClick() {
    if (idLabel->text().isEmpty()) {
      QMessageBox::warning(this, "Error", "No item is currently selected.");
      return;
    }
    emit showEditWindow(ID);
  }

  void ItemDetailWidget::onDeleteButtonClick() {
    if (idLabel->text().isEmpty()) {
      QMessageBox::warning(this, "Error", "No item is currently selected.");
      return;
    }
    emit deleteItem(ID);
    clearLayout(detailsLayout);
    ID = -1;
  }

  // Visitor pattern per costruzione di layout personalizzati in base al tipo
  void ItemDetailWidget::visit(const Items::Book& book) {
    QVBoxLayout* mainBookLayout = new QVBoxLayout();
    mainBookLayout->setAlignment(Qt::AlignCenter);

    QHBoxLayout* contentLayout = new QHBoxLayout();
    contentLayout->setAlignment(Qt::AlignCenter);

    QLabel* imageLabel = new QLabel;
    if (!QString::fromStdString(book.getImage()).isEmpty()) {
      QPixmap image(QString::fromStdString(book.getImage()));

      if (!image.isNull()) {
        imageLabel->setPixmap(image.scaled(250, 400, Qt::KeepAspectRatio));
        imageLabel->setAlignment(Qt::AlignLeft);
      } else {
        imageLabel->setText("Image not found");
      }
    }
    contentLayout->addWidget(imageLabel);
    contentLayout->addStretch(1);

    QVBoxLayout* informationLayout = new QVBoxLayout();
    informationLayout->addWidget(new QLabel("<b>Author:</b> " + QString::fromStdString(book.getAuthor())));
    informationLayout->addWidget(new QLabel("<b>Release Year:</b> " + QString::number(book.getReleaseYear())));
    informationLayout->addWidget(new QLabel("<b>Publisher:</b> " + QString::fromStdString(book.getPublisher())));
    informationLayout->addWidget(new QLabel("<b>Language:</b> " + QString::fromStdString(book.getLanguage())));
    informationLayout->addWidget(new QLabel("<b>Genre:</b> " + QString::fromStdString(Enums::bookMovieGenresToString(book.getGenre()))));
    contentLayout->addLayout(informationLayout);
    contentLayout->addStretch(1);

    mainBookLayout->addLayout(contentLayout);
    mainBookLayout->addSpacing(20);

    QHBoxLayout* actionsLayout = new QHBoxLayout();
    actionsLayout->setAlignment(Qt::AlignCenter);
    QPushButton* readButton = new QPushButton("Read");
    QPushButton* chaptersButton = new QPushButton("Show Chapters");
    actionsLayout->addWidget(readButton);
    actionsLayout->addWidget(chaptersButton);

    mainBookLayout->addLayout(actionsLayout);
    detailsLayout->addLayout(mainBookLayout);
  }

  void ItemDetailWidget::visit(const Items::Movie& movie) {
    QVBoxLayout* mainMovieLayout = new QVBoxLayout();
    mainMovieLayout->setAlignment(Qt::AlignCenter);

    QHBoxLayout* contentLayout = new QHBoxLayout();
    contentLayout->setAlignment(Qt::AlignCenter);

    QLabel* imageLabel = new QLabel;
    if (!QString::fromStdString(movie.getImage()).isEmpty()) {
      QPixmap image(QString::fromStdString(movie.getImage()));

      if (!image.isNull()) {
        imageLabel->setPixmap(image.scaled(250, 400, Qt::KeepAspectRatio));
        imageLabel->setAlignment(Qt::AlignLeft);
      } else {
        imageLabel->setText("Image not found");
      }
    }
    contentLayout->addWidget(imageLabel);
    contentLayout->addStretch(1);

    QVBoxLayout* informationLayout = new QVBoxLayout();
    informationLayout->addWidget(new QLabel("<b>Author:</b> " + QString::fromStdString(movie.getAuthor())));
    informationLayout->addWidget(new QLabel("<b>Release Year:</b> " + QString::number(movie.getReleaseYear())));
    informationLayout->addWidget(new QLabel("<b>Language:</b> " + QString::fromStdString(movie.getLanguage())));
    informationLayout->addWidget(new QLabel("<b>Duration (min):</b> " + QString::number(movie.getDuration())));
    informationLayout->addWidget(new QLabel("<b>Genre:</b> " + QString::fromStdString(Enums::bookMovieGenresToString(movie.getGenre()))));
    informationLayout->addWidget(new QLabel("<b>Age Rating:</b> " + QString::fromStdString(Enums::movieAgeRatingsToString(movie.getAgeRating()))));
    contentLayout->addLayout(informationLayout);
    contentLayout->addStretch(1);

    mainMovieLayout->addLayout(contentLayout);
    mainMovieLayout->addSpacing(20);

    QHBoxLayout* actionsLayout = new QHBoxLayout();
    actionsLayout->setAlignment(Qt::AlignCenter);
    QPushButton* watchButton = new QPushButton("Watch");
    actionsLayout->addWidget(watchButton);

    mainMovieLayout->addLayout(actionsLayout);
    detailsLayout->addLayout(mainMovieLayout);
  }

  void ItemDetailWidget::visit(const Items::Music& music) {
    QVBoxLayout* mainMusicLayout = new QVBoxLayout();
    mainMusicLayout->setAlignment(Qt::AlignCenter);

    QHBoxLayout* contentLayout = new QHBoxLayout();
    contentLayout->setAlignment(Qt::AlignCenter);

    QLabel* imageLabel = new QLabel;
    if (!QString::fromStdString(music.getImage()).isEmpty()) {
      QPixmap image(QString::fromStdString(music.getImage()));

      if (!image.isNull()) {
        imageLabel->setPixmap(image.scaled(250, 400, Qt::KeepAspectRatio));
        imageLabel->setAlignment(Qt::AlignLeft);
      } else {
        imageLabel->setText("Image not found");
      }
    }
    contentLayout->addWidget(imageLabel);
    contentLayout->addStretch(1);

    QVBoxLayout* informationLayout = new QVBoxLayout();
    informationLayout->addWidget(new QLabel("<b>Author:</b> " + QString::fromStdString(music.getAuthor())));
    informationLayout->addWidget(new QLabel("<b>Release Year:</b> " + QString::number(music.getReleaseYear())));
    informationLayout->addWidget(new QLabel("<b>Album:</b> " + QString::fromStdString(music.getAlbum())));
    informationLayout->addWidget(new QLabel("<b>Duration (sec):</b> " + QString::number(music.getDuration())));
    informationLayout->addWidget(new QLabel("<b>Explicit:</b> " + QString::fromStdString((music.isExplicit()) ? "Yes" : "No")));
    informationLayout->addWidget(new QLabel("<b>Genre:</b> " + QString::fromStdString(Enums::musicGenreToString(music.getGenre()))));
    contentLayout->addLayout(informationLayout);
    contentLayout->addStretch(1);

    mainMusicLayout->addLayout(contentLayout);

    QSlider* progressBar = new QSlider(Qt::Horizontal);
    progressBar->setRange(0, 100);
    progressBar->setValue(0);
    mainMusicLayout->addWidget(progressBar);

    QHBoxLayout* actionsLayout = new QHBoxLayout();
    actionsLayout->setAlignment(Qt::AlignCenter);
    QPushButton* previousButton = new QPushButton(QIcon(":icons/Resources/rewind.png"), "");
    previousButton->setIconSize(QSize(24, 24));
    QPushButton* playPauseButton = new QPushButton(QIcon(":icons/Resources/play_pause.png"), "");
    playPauseButton->setIconSize(QSize(24, 24));
    QPushButton* nextButton = new QPushButton(QIcon(":icons/Resources/forward.png"), "");
    nextButton->setIconSize(QSize(24, 24));
    actionsLayout->addWidget(previousButton);
    actionsLayout->addWidget(playPauseButton);
    actionsLayout->addWidget(nextButton);

    mainMusicLayout->addLayout(actionsLayout);
    detailsLayout->addLayout(mainMusicLayout);
  }

}
