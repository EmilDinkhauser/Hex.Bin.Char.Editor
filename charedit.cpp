#include "dragdropwidget.h"

void DragDropWidget::onbuttonCHARClicked() {
    // Den Text aus dem Textfeld holen
    QString text = textEdit->toPlainText();

    // Das Textfeld sichtbar machen und den Text setzen
    textEdit->setVisible(true);
    textEdit->setPlainText(text);

    // Verbergen der Buttons für andere Modi
    buttonBIN->setVisible(false);
    buttonHEX->setVisible(false);
    buttonCHAR->setVisible(false);

    // Den aktuellen Modus auf Normal setzen
    currentMode = Mode::Normal;
}
