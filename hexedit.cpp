#include "dragdropwidget.h"

void DragDropWidget::onbuttonHEXClicked() {
    // Den Text aus dem Textfeld holen
    QString text = textEdit->toPlainText();

    // Das Textfeld sichtbar machen
    textEdit->setVisible(true);

    // Umwandlung des Textes in Hexadezimale Darstellung
    QString convertedText;
    for (QChar ch : text) {
        // Konvertierung jedes Zeichens in seinen Hexadezimalwert und Hinzufügen zu 'convertedText'
        convertedText += QString::number(ch.unicode(), 16) + " ";
    }

    // Setzen des umgewandelten Textes im Textfeld
    textEdit->setPlainText(convertedText);

    // Verbergen der Buttons für andere Modi
    buttonBIN->setVisible(false);
    buttonHEX->setVisible(false);
    buttonCHAR->setVisible(false);

    // Setzen des aktuellen Modus auf Hexadezimal
    currentMode = Mode::Hexadecimal;
}
