#include "TextDocument.h"

// La idea es leer el file y guardarlo en buffer (quiero cargarlo en la memoria)
// Para esto uso std::ifstream para levantar el archivo
bool TextDocument::init(string &filename) {
    std::ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return false;
    }
    std::stringstream inputStringStream = inputFile.rdbuf();
    this->buffer = inputStringStream.str();
    this->length = buffer.size();  // Posiblemente no sea necesario

    inputFileStream.close();
    this->init_linebuffer();
    return true;
}

// TODO: Contar newlines mientras leo el archivo en el init
// TODO: Otros sistemas operativos manejan newlines de otras formas (ej \r)
bool init_linebuffer() {
    int lineStart = 0;
    int bufferSize = this->buffer.size();
    for (int i = 0; i < bufferSize; i++) {
        if (this->buffer[i] == '\n') {
            this->lineBuffer.push_back(lineStart);
            lineStart = i+1;
        }
    }
    this->lineBuffer.push_back(bufferSize); // Marco el final del archivo, quiza deberia ser la ultima lineStart ver
    return true;
}

// Devuelve una copia de la linea que esta en mi buffer
string getLine(int lineNumber) {
    if (lineNumber < 0 || lineNumber >= (int)this->lineBuffer.size()) {
        std::cerr << "lineNumber " << lineNumber << " is not a valid number line. " 
            << "Max is: " << this->lineBuffer.size() << std::endl;
        return "";
    }

    int bufferStart = this->lineBuffer[lineNumber];
    int nextBufferStart = this->lineBuffer[lineNumber + 1];  // Final no inclusive
    int cantidad = nextBufferStart - bufferStart;

    return this->buffer.substr(bufferStart, cantidad);
}