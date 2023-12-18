#include "dragdropwidget.h"

void DragDropWidget::onbuttonBINClicked() {
    // Holen des Textes aus dem Textfeld
    QString text = textEdit->toPlainText();

    // Textfeld sichtbar machen
    textEdit->setVisible(true);

    // Umwandlung des Textes in Binärcode
    QString convertedText;
    for (QChar ch : text) {
        // Konvertierung jedes Zeichens in seinen Binärwert und Hinzufügen zu 'convertedText'
        convertedText += QString::number(ch.unicode(), 2) + " ";
    }

    // Setzen des umgewandelten Textes im Textfeld
    textEdit->setPlainText(convertedText);

    // Verbergen der Buttons für andere Modi
    buttonBIN->setVisible(false);
    buttonHEX->setVisible(false);
    buttonCHAR->setVisible(false);

    // Setzen des aktuellen Modus auf Binär
    currentMode = Mode::Binary;
}
