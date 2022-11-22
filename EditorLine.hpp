#pragma once

#include <iostream>
#include "SFML/Graphics.hpp"

class EditorLine {
	

private:
    std::string content;
    static int instances_count;
    int line_number = 0;
    bool active;
    sf::Font* main_font;
    sf::Font* content_font;
    int size;
    float width = 0;

    sf::Color text_color = sf::Color(0, 0, 0);
    sf::Color content_color = sf::Color(0, 0, 0);

    sf::Text number_text;

    std::vector<sf::Text> line_chars;

	public:

		EditorLine();
		EditorLine(std::string text, sf::Font *font, sf::Font *cotext_font);

        void set_colors(sf::Color text_color, sf::Color content_color);

        sf::Text get_number_text();
        std::vector<sf::Text> get_content_chars();
        int get_size();
        std::string get_content();
        float get_width();

        void insert_char_at(char c, int col);
        void delete_char_at(int col);
        void insert_word(int col, std::string word);
        void delete_word(int start, int end);
        std::string break_at(int col);
        void merge_with(EditorLine line);

        void set_number(int n);

private:
    sf::Text draw_text(std::string content, int x, bool is_content);
    void draw_number();
    void draw_chars();
};