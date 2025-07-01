#include <QIcon>
#include <QVBoxLayout>

#include "ItemCardWidget.h"
#include "../../Model/Items/Book.h"
#include "../../Model/Items/Movie.h"
#include "../../Model/Items/Music.h"

namespace View::List {

  ItemCardWidget::ItemCardWidget(const Items::AbstractItem& item, QWidget* parent)
  : QWidget{parent}, item(item)
  {
    item.accept(*this);
  }

  // Pattern visitor per avere diverse icon in base al tipo
  void ItemCardWidget::visit(const Items::Book& book) {
    setFixedSize(250, 100);

    iconLabel = new QLabel();
    iconLabel->setPixmap(QIcon(":/icons/Resources/book.png").pixmap(70, 70));

    titleLabel = new QLabel(QString::fromStdString(book.getTitle()));
    titleLabel->setStyleSheet("font-weight: bold; font-size: 16px");
    titleLabel->setWordWrap(false);
    titleLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    QFontMetrics metrics(titleLabel->font());
    titleLabel->setText(metrics.elidedText(QString::fromStdString(book.getTitle()), Qt::ElideRight, 150));

    authorLabel = new QLabel(QString::fromStdString(book.getAuthor()));
    authorLabel->setStyleSheet("font-style: italic; font-size: 14px");

    QVBoxLayout* textLayout = new QVBoxLayout();
    textLayout->addWidget(titleLabel);
    textLayout->addWidget(authorLabel);

    QHBoxLayout* mainLayout = new QHBoxLayout(this);
    mainLayout->addWidget(iconLabel, 0, Qt::AlignCenter);
    mainLayout->addLayout(textLayout);

    setLayout(mainLayout);
  }

  void ItemCardWidget::visit(const Items::Movie& movie) {
    setFixedSize(250, 100);

    iconLabel = new QLabel();
    iconLabel->setPixmap(QIcon(":/icons/Resources/movie.png").pixmap(70, 70));

    titleLabel = new QLabel(QString::fromStdString(movie.getTitle()));
    titleLabel->setStyleSheet("font-weight: bold; font-size: 16px");
    titleLabel->setWordWrap(false);
    titleLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    QFontMetrics metrics(titleLabel->font());
    titleLabel->setText(metrics.elidedText(QString::fromStdString(movie.getTitle()), Qt::ElideRight, 150));

    authorLabel = new QLabel(QString::fromStdString(movie.getAuthor()));
    authorLabel->setStyleSheet("font-style: italic; font-size: 14px");

    QVBoxLayout* textLayout = new QVBoxLayout();
    textLayout->addWidget(titleLabel);
    textLayout->addWidget(authorLabel);

    QHBoxLayout* mainLayout = new QHBoxLayout(this);
    mainLayout->addWidget(iconLabel, 0, Qt::AlignCenter);
    mainLayout->addLayout(textLayout);

    setLayout(mainLayout);
  }

  void ItemCardWidget::visit(const Items::Music& music) {
    setFixedSize(250, 100);

    iconLabel = new QLabel();
    iconLabel->setPixmap(QIcon(":/icons/Resources/music.png").pixmap(70, 70));

    titleLabel = new QLabel(QString::fromStdString(music.getTitle()));
    titleLabel->setStyleSheet("font-weight: bold; font-size: 16px");
    titleLabel->setWordWrap(false);
    titleLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    QFontMetrics metrics(titleLabel->font());
    titleLabel->setText(metrics.elidedText(QString::fromStdString(music.getTitle()), Qt::ElideRight, 150));

    authorLabel = new QLabel(QString::fromStdString(music.getAuthor()));
    authorLabel->setStyleSheet("font-style: italic; font-size: 14px");

    QVBoxLayout* textLayout = new QVBoxLayout();
    textLayout->addWidget(titleLabel);
    textLayout->addWidget(authorLabel);

    QHBoxLayout* mainLayout = new QHBoxLayout(this);
    mainLayout->addWidget(iconLabel, 0, Qt::AlignCenter);
    mainLayout->addLayout(textLayout);

    setLayout(mainLayout);
  }

  unsigned int ItemCardWidget::getItemID() const {
    return item.getID();
  }

  QString ItemCardWidget::getTitle() const {
    return QString::fromStdString(item.getTitle());
  }

  const Items::AbstractItem& ItemCardWidget::getItem() const {
    return item;
  }

}
