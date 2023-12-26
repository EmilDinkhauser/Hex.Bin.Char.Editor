#ifndef DRAGDROPWIDGET_H
#define DRAGDROPWIDGET_H

#include <QWidget>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>
#include <QLabel> // Brauch ic hdas noch?
#include <QPushButton>
#include <QLineEdit>
#include <QTextEdit>
#include <QFileInfo>
#include <QMessageBox>
#include <QFileDialog>
#include <QRegularExpression>
#include <QVBoxLayout>

class DragDropWidget : public QWidget {
    Q_OBJECT

public:
    explicit DragDropWidget(QWidget *parent = nullptr);

protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dropEvent(QDropEvent *event) override;
    void clearImportedFile();

private slots:
    void onbuttonBINClicked();
    void onbuttonHEXClicked();
    void onbuttonCHARClicked();
    void onbuttonSAVEClicked();
    void onbuttonCLEARClicked();
    bool isValidTextForCurrentMode();

private:
    QLabel *label; // Label zur Anzeige von Informationen
    QLabel *infoLabel; // Zusätzliches Label für ergänzende Informationen
    QLabel *werbungLabel;
    QPushButton *buttonBIN; // Button für Binärmodus
    QPushButton *buttonHEX; // Button für Hexadezimalmodus
    QPushButton *buttonCHAR; // Button für Zeichenmodus
    QPushButton *buttonSAVE; // Button zum Speichern
    QPushButton *buttonCLEAR; // Button zum zurücksetzen des UIs
    QTextEdit *textEdit; // Textfeld für Eingabe/Ausgabe
    QString originalFileExtension; // Ursprüngliche Dateierweiterung
    enum class Mode { Normal, Binary, Hexadecimal } currentMode = Mode::Normal; // Hier wird definiert in welchem Modus sich das Programm befindet zur Zeichenüberprüfung
};

#endif // DRAGDROPWIDGET_H
