#include <QVBoxLayout>
#include <QFormLayout>

#include "MusicEditWidget.h"
#include "../../Model/Items/Music.h"
#include "../../Model/Utility/EnumsConvertions.h"

namespace View::Editors {
  MusicEditWidget::MusicEditWidget(QWidget *parent)
  : AbstractItemEditWidget{parent}
  {
    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    QFormLayout* specificInputsLayout = new QFormLayout();
    specificInputsLayout->setLabelAlignment(Qt::AlignLeft);
    mainLayout->addLayout(specificInputsLayout);

    albumInput = new QLineEdit();
    albumInput->setPlaceholderText("Song album");
    specificInputsLayout->addRow("Album", albumInput);

    releaseYearInput = new QSpinBox();
    releaseYearInput->setRange(1700, 2025);
    specificInputsLayout->addRow("Year", releaseYearInput);

    durationInput = new QSpinBox();
    durationInput->setRange(30, 300);
    specificInputsLayout->addRow("Duration (sec)", durationInput);

    explicitLanguageInput = new QCheckBox();
    specificInputsLayout->addRow("Explicit language", explicitLanguageInput);

    genreInput = new QComboBox();
    genreInput->addItems(QStringList() << "Classical"
                           << "Rap" << "Electronic"
                           << "Blues" << "Jazz"
                           << "Hip-Pop" << "Rock"
                           << "Metal");
    specificInputsLayout->addRow("Genre", genreInput);

    setLayout(mainLayout);
  }

  void MusicEditWidget::setValues(const Items::Music& item) {
    albumInput->setText(QString::fromStdString(item.getAlbum()));
    releaseYearInput->setValue(item.getReleaseYear());
    durationInput->setValue(item.getDuration());
    explicitLanguageInput->setChecked(item.isExplicit());
    genreInput->setCurrentText(QString::fromStdString(Enums::musicGenreToString(item.getGenre())));
  }

  Items::AbstractItem* MusicEditWidget::createNewItem(QString title, unsigned int id, QString author, QString image) {
    return new Items::Music(title.toStdString(),
                            id,
                            author.toStdString(),
                            static_cast<unsigned int>(releaseYearInput->value()),
                            image.toStdString(),
                            (albumInput->text()).toStdString(),
                            static_cast<unsigned int>(durationInput->value()),
                            explicitLanguageInput->isChecked(),
                            Enums::stringToMusicGenres((genreInput->currentText()).toStdString())
                            );
  }
}
