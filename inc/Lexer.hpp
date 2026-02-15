/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lexer.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeunki2 <daeunki2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 14:33:42 by daeunki2          #+#    #+#             */
/*   Updated: 2026/02/15 14:12:26 by daeunki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_HPP
#define LEXER_HPP

#include <string>
#include <vector>
#include <iostream>

/*
basic idea
make an array of int and mark the statatus of each caracter. so tha i can tpkenize the string
*/

enum QuoteState
{
	NORMAL = 0,
	SINGLE_QUOTE = 1,
	DOUBLE_QUOTE = 2,
	ERROR = 3,
};	

class Lexer
{
	private:
    std::string         							_Line; //user's row input
    std::vector<QuoteState>    						_Mask; //array for marking
    std::vector<std::pair<std::string, QuoteState> > _Chunk; // the result of chunknization

	public:
    Lexer();
    Lexer(const Lexer &other);
    ~Lexer();
    Lexer &operator=(const Lexer &other);
	
	void set_line(std::string input); //take the user's row input and save it in the class
	std::vector<std::pair<std::string, QuoteState> > get_chunks() const;//return the result of chunkization
	
	
	bool is_single_quote(char c);
	bool is_double_quote(char c);
	void mask_line(); //mark the status of each character
	QuoteState define_chunk_type(std::string chunk, int start_index);
	void chunk_line(); // cut the row input into row chunks based on the mask

	
	void print_tokens() const;
	void re_set();
};

#endif
