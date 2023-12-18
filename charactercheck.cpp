#include "dragdropwidget.h"

bool DragDropWidget::isValidTextForCurrentMode() {
    QString text = textEdit->toPlainText();
    QRegularExpression re;

    if (currentMode == Mode::Binary) {
        re.setPattern("^[01 ]*$"); // Nur 0 und 1 erlaubt
    } else if (currentMode == Mode::Hexadecimal) {
        re.setPattern("^[0-9A-Fa-f ]*$"); // Nur hexadezimale Zeichen erlaubt
    } else {
        return true; // Im Normalmodus oder zeichenweiser Darstellung gibt es keine Einschränkungen
    }

    return re.match(text).hasMatch();
}
