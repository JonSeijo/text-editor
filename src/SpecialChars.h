#ifndef SPECIAL_CHARS_HPP
#define SPECIAL_CHARS_HPP

#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <string>

//-----Lower case accents VOWELS------//
#define A_LOWER_GRAVE 224
#define A_LOWER_ACUTE 225
#define A_LOWER_CIRCUMFLEX 226

#define E_LOWER_GRAVE 232
#define E_LOWER_ACUTE 233
#define E_LOWER_CIRCUMFLEX 234

#define I_LOWER_GRAVE 236
#define I_LOWER_ACUTE 237
#define I_LOWER_CIRCUMFLEX 238

#define N_LOWER_TILDE 241

#define O_LOWER_GRAVE 242
#define O_LOWER_ACUTE 243
#define O_LOWER_CIRCUMFLEX 244

#define U_LOWER_GRAVE 249
#define U_LOWER_ACUTE 250
#define U_LOWER_CIRCUMFLEX 251

//-----Upper case accents VOWELS------//
#define A_UPPER_GRAVE 192
#define A_UPPER_ACUTE 193
#define A_UPPER_CIRCUMFLEX 194

#define E_UPPER_GRAVE 200
#define E_UPPER_ACUTE 201
#define E_UPPER_CIRCUMFLEX 202

#define I_UPPER_GRAVE 204
#define I_UPPER_ACUTE 205
#define I_UPPER_CIRCUMFLEX 206

#define O_UPPER_GRAVE 210
#define O_UPPER_ACUTE 211
#define O_UPPER_CIRCUMFLEX 212

#define U_UPPER_GRAVE 217
#define U_UPPER_ACUTE 218
#define U_UPPER_CIRCUMFLEX 219

namespace SpecialChars {

std::string convertSpecialChar(sf::Uint32 c, std::ofstream &outputFile);

}  // namespace SpecialChars

#endif  //SPECIAL_CHARS_HPP
