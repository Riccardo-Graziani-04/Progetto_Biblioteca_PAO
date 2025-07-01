#ifndef SEARCHWIDGET_H
#define SEARCHWIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <QTimer>

namespace View::List {

  class SearchWidget : public QWidget {
    Q_OBJECT

    private:
      QLineEdit* searchBar;
      QTimer* searchTimer;

    public:
      explicit SearchWidget(QWidget* parent = nullptr);

    signals:
      void searchQueryChanged(const QString& text);

  };

}

#endif // SEARCHWIDGET_H
