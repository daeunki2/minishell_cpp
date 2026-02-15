/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Tokenizer.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeunki2 <daeunki2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 18:04:40 by daeunki2          #+#    #+#             */
/*   Updated: 2026/02/15 14:38:37 by daeunki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
basic idea
classify chunks.
normal chunk > make it in a smaller chunk and give a tag
single chunk > remove quote and give a tag
double quote > remove quote and give a tag
*/

#ifndef TOKENIZER_HPP
#define TOKENIZER_HPP

#include "Lexer.hpp"

enum t_type
{
	WORD,
	PIPE,
	REDIRECT_IN,
	REDIRECT_OUT,
	HEREDOC,
	APPEND
};

struct s_token {
    std::string text;
    QuoteState  word_type;  //given by lexer
    t_type      token_type; //given by tokenizer
};

class Tokenizer
{
	private:
    const Lexer				*_chunks;
    std::vector<s_token>	_tokens; 

	public:
    Tokenizer();
    Tokenizer(const Tokenizer &other);
    ~Tokenizer();
	Tokenizer&operator=(const Tokenizer &other);
	
	void set_chunks(const Lexer &Lexer);
	std::vector<s_token> get_tokens();
	
	std::string	quote_remover(std::string string);
	t_type	meta_type_identifier(std::string string);//identifiy the type
	std::vector<s_token> 	split(std::string normal_chunk);//cut it by identifier
	s_token make_new_token(std::string token);
	void	tokenize();//make the token with type

	
	void print_tokens() const;
	void re_set();
};

#endif
