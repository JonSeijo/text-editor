#include "TextDocument.h"

// La idea es leer el file y guardarlo en buffer (quiero cargarlo en la memoria)
// Para esto uso std::ifstream para levantar el archivo
bool TextDocument::init(string &filename) {
    std::ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return false;
    }
    std::stringstream inputStringStream;
    inputStringStream << inputFile.rdbuf();

    this->buffer = this->toUtf32(inputStringStream.str());
    this->length = buffer.getSize();  // Posiblemente no sea necesario

    inputFile.close();
    this->initLinebuffer();
    return true;
}

bool TextDocument::saveFile(string &filename) {
    std::ofstream outputFile(filename);
    if (!outputFile.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return false;
    }

    //It looks more straight-forward to me (Luca Errani)
    std::stringstream toBeSaved;
    for (sf::Uint32 ch : this->buffer) {
        toBeSaved << SpecialChars::convertSpecialChar(ch, outputFile);
    }
    outputFile << toBeSaved.str();

    outputFile.close();

    this->documentHasChanged = false;
    return true;
}

bool TextDocument::hasChanged() {
    return this->documentHasChanged;
}

// TODO: Contar newlines mientras leo el archivo en el init
// TODO: Otros sistemas operativos manejan newlines de otras formas (ej \r)
bool TextDocument::initLinebuffer() {
    int lineStart = 0;
    this->lineBuffer.clear();
    this->lineBuffer.push_back(lineStart);

    int bufferSize = this->buffer.getSize();

    for (int i = 0; i < bufferSize; i++) {
        if (this->buffer[i] == '\n' || this->buffer[i] == 13) {
            lineStart = i + 1;
            this->lineBuffer.push_back(lineStart);
        }
    }
    return true;
}

// Devuelve una copia de la linea que esta en mi buffer
sf::String TextDocument::getLine(int lineNumber) {
    int lastLine = this->lineBuffer.size() - 1;

    if (lineNumber < 0 || lineNumber > lastLine) {
        std::cerr << "lineNumber " << lineNumber << " is not a valid number line. "
                  << "Max is: " << this->lineBuffer.size() - 1 << std::endl;
        return "";
    }

    if (lineNumber == lastLine) {
        return this->buffer.substring(this->lineBuffer[lineNumber]);

    } else {
        int bufferStart = this->lineBuffer[lineNumber];
        int nextBufferStart = this->lineBuffer[lineNumber + 1];  // Final no inclusive
        int cantidad = nextBufferStart - bufferStart - 1;

        return this->buffer.substring(bufferStart, cantidad);
    }
}

sf::String TextDocument::toUtf32(const std::string &inString) {
    sf::String outString = "";
    auto iterEnd = inString.cend();

    // Decode avanza el iterador
    for (auto iter = inString.cbegin(); iter != iterEnd;) {
        sf::Uint32 out;
        iter = sf::Utf8::decode(iter, iterEnd, out);
        outString += out;
    }

    return outString;
}

void TextDocument::addTextToPos(sf::String text, int line, int charN) {
    this->documentHasChanged = true;

    int textSize = text.getSize();
    int bufferInsertPos = this->getBufferPos(line, charN);
    this->buffer.insert(bufferInsertPos, text);

    int lineAmount = this->lineBuffer.size();
    for (int l = line + 1; l < lineAmount; l++) {
        this->lineBuffer[l] += textSize;
    }

    for (int i = 0; i < (int)text.getSize(); i++) {
        if (text[i] == '\n' || text[i] == 13) {          // text[i] == \n
            int newLineStart = bufferInsertPos + i + 1;  // Nueva linea comienza despues del nuevo \n

            // Inserto O(#lineas) y uso busqueda binaria pues los inicios de lineas son crecientes
            this->lineBuffer.insert(
                std::lower_bound(this->lineBuffer.begin(), this->lineBuffer.end(), newLineStart),
                newLineStart);
        }
    }
}

// TODO: Optimizar
void TextDocument::removeTextFromPos(int amount, int lineN, int charN) {
    this->documentHasChanged = true;

    int bufferStartPos = this->getBufferPos(lineN, charN);
    this->buffer.erase(bufferStartPos, amount);

    // TODO: SUPER OVERKILL. Esto es O(#buffer) y podria ser O(#lineas)
    // Revisitar idea de correr los lineBuffers en amount, teniendo en cuenta la cantidad de newlines borradas
    this->initLinebuffer();
}

sf::String TextDocument::getTextFromPos(int amount, int line, int charN) {
    int bufferPos = this->getBufferPos(line, charN);
    return this->buffer.substring(bufferPos, amount);
}

int TextDocument::charAmountContained(int startLineN, int startCharN, int endLineN, int endCharN) {
    return this->getBufferPos(endLineN, endCharN) - this->getBufferPos(startLineN, startCharN) + 1;
}

void TextDocument::swapLines(int lineA, int lineB) {
    if (lineA == lineB) {
        return;
    }
    this->documentHasChanged = true;

    int minLine = std::min(lineA, lineB);
    int maxLine = std::max(lineA, lineB);
    int lastLine = this->getLineCount() - 1;

    if (minLine < 0) {
        std::cerr << "SwapLines: Line " << minLine << " does not exist"
                  << "\n";
    }
    if (maxLine > lastLine) {
        std::cerr << "SwapLines: Line " << lastLine << " does not exist"
                  << "\n";
    }
    if (minLine == maxLine - 1) {
        this->swapWithNextLine(minLine);
    } else {
        std::cerr << "Cant swap non-contiguous lines\n";
    }
}

void TextDocument::swapWithNextLine(int line) {
    if (line < 0 || line + 1 == this->getLineCount()) {
        std::cerr << "Cant swap with nonexisting line: " << line << "\n";
    }
    auto A = this->getLine(line);
    auto B = this->getLine(line + 1);
    int lenA = A.getSize();
    int lenB = B.getSize();

    sf::String Z = "";
    Z += B;
    Z += '\n';
    Z += A;

    int lineAStart = this->lineBuffer[line];

    // Counting the \n at the end of A
    int totalLen = lenA + 1 + lenB;

    for (int i = 0; i < totalLen; i++) {
        this->buffer[i + lineAStart] = Z[i];
    }
    this->lineBuffer[line + 1] = this->lineBuffer[line] + lenB + 1;
}

int TextDocument::getBufferPos(int line, int charN) {
    if (line >= (int)this->lineBuffer.size()) {
        std::cerr << "\nCan't get buffer pos of: " << line << "\n";
        std::cerr << "Buffer last line is: " << this->lineBuffer.size() - 1 << "\n\n";
    }
    return this->lineBuffer[line] + charN;
}

int TextDocument::charsInLine(int line) const {
    // Si es ultima linea, no puedo compararla con inicio de siguiente pues no hay siguiente
    int bufferSize = this->lineBuffer.size();

    if (line == bufferSize - 1) {
        return this->buffer.getSize() - this->lineBuffer[this->lineBuffer.size() - 1];
    } else {
        return this->lineBuffer[line + 1] - this->lineBuffer[line] - 1;
    }
}

int TextDocument::getLineCount() const {
    return (int)this->lineBuffer.size();
}
