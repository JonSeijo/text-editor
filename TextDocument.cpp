#include "TextDocument.h"

// La idea es leer el file y guardarlo en buffer (quiero cargarlo en la memoria)
// Para esto uso std::ifstream para levantar el archivo
bool TextDocument::init(string &filename) {
    std::ifstream inputFile(filename.c_str());
    if (!inputFile.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return false;
    }
    std::stringstream inputStringStream;
    inputStringStream << inputFile.rdbuf();

    // TODO: Ver si con esto no arruino encoding
    this->buffer = this->toUtf32(inputStringStream.str());
    // this->buffer = inputStringStream.str();
    this->length = buffer.getSize();  // Posiblemente no sea necesario

    inputFile.close();
    this->init_linebuffer();
    return true;
}

// TODO: Contar newlines mientras leo el archivo en el init
// TODO: Otros sistemas operativos manejan newlines de otras formas (ej \r)
bool TextDocument::init_linebuffer() {
    int lineStart = 0;
    this->lineBuffer.push_back(lineStart);

    int bufferSize = this->buffer.getSize();

    for (int i = 0; i < bufferSize; i++) {
        if (this->buffer[i] == '\n') {
            lineStart = i+1;
            this->lineBuffer.push_back(lineStart);
        }
    }
    return true;
}

// Devuelve una copia de la linea que esta en mi buffer
sf::String TextDocument::getLine(int lineNumber) {

    int lastLine = this->lineBuffer.size();

    if (lineNumber < 0 || lineNumber > lastLine) {
        std::cerr << "lineNumber " << lineNumber << " is not a valid number line. "
            << "Max is: " << this->lineBuffer.size()-1 << std::endl;
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

sf::String TextDocument::toUtf32(const std::string& inString) {
    sf::String outString = "";
    auto iterEnd = inString.cend();

    // Decode avanza el iterador
    for (auto iter = inString.cbegin(); iter != iterEnd; ) {
        sf::Uint32 out;
        iter = sf::Utf8::decode(iter, iterEnd, out);
        outString += out;
    }

    return outString;
}

void TextDocument::addToPos(sf::String text, int line, int charN) {
    int textSize = text.getSize();
    this->buffer.insert(this->getBufferPos(line, charN), text);

    int lineAmount = this->lineBuffer.size();
    for (int l = line + 1; l < lineAmount; l++) {
        this->lineBuffer[l] += textSize;
    }
}

int TextDocument::getBufferPos(int line, int charN) {
    return this->lineBuffer[line] + charN;
}


// TODO: Borrar esta funcion
// TODO: Crear funcion que inserte caracteres en posicion arbitraria
// TODO: Crear funcion que inserte enters en posicion arbitraria
// TODO: Crear funcion que borre caracteres en posiscion arbitraria
void TextDocument::addToLastLine(sf::String text) {
    this->buffer += text;
}

int TextDocument::charsInLine(int line) const {
    // Si es ultima linea, no puedo compararla con inicio de siguiente pues no hay siguiente
    if (line == this->lineBuffer.size() - 1) {
        return this->buffer.getSize() - this->lineBuffer[this->lineBuffer.size() - 1];
    } else {
        return this->lineBuffer[line+1] - this->lineBuffer[line] - 1;
    }
}

int TextDocument::getLineCount() const {
    return (int)this->lineBuffer.size();
}
