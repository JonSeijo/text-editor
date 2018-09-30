#include "SpecialChars.h"

namespace SpecialChars {
std::string convertSpecialChar(sf::Uint32 c, std::ofstream &outputFile) {
    switch (c) {
        case A_LOWER_ACUTE:
            return "á";
        case E_LOWER_ACUTE:
            return "é";
        case I_LOWER_ACUTE:
            return "í";
        case O_LOWER_ACUTE:
            return "ó";
        case U_LOWER_ACUTE:
            return "ú";
        case A_LOWER_GRAVE:
            return "à";
        case E_LOWER_GRAVE:
            return "è";
        case I_LOWER_GRAVE:
            return "ì";
        case O_LOWER_GRAVE:
            return "ò";
        case U_LOWER_GRAVE:
            return "ù";
        case A_LOWER_CIRCUMFLEX:
            return "â";
        case E_LOWER_CIRCUMFLEX:
            return "ê";
        case I_LOWER_CIRCUMFLEX:
            return "î";
        case O_LOWER_CIRCUMFLEX:
            return "ô";
        case U_LOWER_CIRCUMFLEX:
            return "û";
        case A_UPPER_ACUTE:
            return "Á";
        case E_UPPER_ACUTE:
            return "É";
        case I_UPPER_ACUTE:
            return "Í";
        case O_UPPER_ACUTE:
            return "Ó";
        case U_UPPER_ACUTE:
            return "Ú";
        case A_UPPER_GRAVE:
            return "À";
        case E_UPPER_GRAVE:
            return "È";
        case I_UPPER_GRAVE:
            return "Ì";
        case O_UPPER_GRAVE:
            return "Ò";
        case U_UPPER_GRAVE:
            return "Ù";
        case A_UPPER_CIRCUMFLEX:
            return "Â";
        case E_UPPER_CIRCUMFLEX:
            return "Ê";
        case I_UPPER_CIRCUMFLEX:
            return "Î";
        case O_UPPER_CIRCUMFLEX:
            return "Ô";
        case U_UPPER_CIRCUMFLEX:
            return "Û";
        case N_LOWER_TILDE:
            return "ñ";
    }
    if (c < 128) {
        return sf::String(c);
    } else {
        outputFile.close();
        std::cerr << "\nERROR: Can't save character: " << c << std::endl;
    }
    return "";
}
}  // namespace SpecialChars