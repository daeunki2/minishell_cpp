/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lexer.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeunki2 <daeunki2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 14:31:10 by daeunki2          #+#    #+#             */
/*   Updated: 2026/02/15 14:12:35 by daeunki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Lexer.hpp"

/*
42 style
*/

Lexer::Lexer()
{
	this->_Line = ""; 
	this->_Mask.clear();
	this->_Chunk.clear();
}

Lexer::Lexer(const Lexer &other)
{
    *this = other;
}

Lexer::~Lexer()
{
}

Lexer &Lexer::operator=(const Lexer &other)
{
    if (this != &other)
    {
        this->_Line = other._Line;
        this->_Mask = other._Mask;
        this->_Chunk = other._Chunk;
    }
    return *this;
}


void Lexer::set_line(std::string input)
{
	this->_Line = input;
};

std::vector<std::pair<std::string, QuoteState> > Lexer::get_chunks() const
{
	return this->_Chunk;
};


bool Lexer::is_single_quote(char c)
{
	return ((c == '\'') ? true : false);
};

bool Lexer::is_double_quote(char c)
{
	return ((c == '\"') ? true : false);
};


void Lexer::mask_line()
{
	const std::string	input = this->_Line;
	this->_Mask.resize(this->_Line.size(), NORMAL); // Initialize the mask with NORMAL state QuoteState state = NORMAL;
	int status = NORMAL;

	for (size_t i = 0; i < this->_Line.size(); i++)
	{
		if (status == NORMAL && is_single_quote(input[i]) == true)//normal > single
		{
			this->_Mask[i] = SINGLE_QUOTE;
			status = SINGLE_QUOTE;
		}
		else if (status == NORMAL && is_double_quote(input[i]) == true)//normal >> double
		{
			this->_Mask[i] = DOUBLE_QUOTE;
			status = DOUBLE_QUOTE;
		}
		else if (status == SINGLE_QUOTE && is_single_quote(input[i]) == false) // in single quote
		{
			this->_Mask[i] = SINGLE_QUOTE;
			status = SINGLE_QUOTE;
		}
		else if (status == SINGLE_QUOTE && is_single_quote(input[i]) == true) // out single qoute
		{
			this->_Mask[i] = SINGLE_QUOTE;
			status = NORMAL;
		}
		else if (status == DOUBLE_QUOTE && is_double_quote(input[i]) == false) // in double qoute
		{
			this->_Mask[i] = DOUBLE_QUOTE;
			status = DOUBLE_QUOTE;
		}
		else if (status == DOUBLE_QUOTE && is_double_quote(input[i]) == true) // out double quote
		{
			this->_Mask[i] = DOUBLE_QUOTE;
			status = NORMAL;
		}
	}
};

QuoteState Lexer::define_chunk_type(std::string chunk, int start_index)
{
	QuoteState start_type = this->_Mask[start_index];
	int s_count =0;
	int d_count =0;

	for (size_t i =0; i < chunk.size(); i++)
	{
		if (start_type == SINGLE_QUOTE && is_single_quote(chunk[i]) == true)
		{
			s_count++;
		}
		else if (start_type == DOUBLE_QUOTE && is_double_quote(chunk[i]) == true)
		{
			d_count++;
		}
		if(start_type != this->_Mask[start_index])
			return ERROR;
	}
	if (start_type == SINGLE_QUOTE && s_count != 2)
		return ERROR;
	else if (start_type == DOUBLE_QUOTE && d_count != 2)
		return ERROR;
	else
		return start_type;
};

void Lexer::chunk_line()
{
	size_t i = 0;
	QuoteState  current_status;
	std::string temp;
	int start_index;
	while (i < this->_Line.size())
	{
		
		current_status = this->_Mask[i];
		start_index = i;
		while ( i < this->_Line.size() && this->_Mask[i] == current_status)
		{
			temp.push_back(this->_Line[i]);
			i++;
		}
		this->_Chunk.push_back(std::make_pair(temp, define_chunk_type(temp, start_index)));
		temp.clear();
	}
}


void Lexer::print_tokens() const
{
    std::cout << "==== Lexer Debug ====\n";

    std::cout << "[Line]\n" << _Line << "\n\n";

    std::cout << "[Mask]\n";
    for (size_t i = 0; i < _Mask.size(); ++i)
        std::cout << _Mask[i];
    std::cout << "\n";

    std::cout << "[Chunks]\n";
    for (size_t i = 0; i < _Chunk.size(); ++i)
    {
        std::cout << i << ": [" << _Chunk[i].first << "] (State: " << _Chunk[i].second << ")\n";
    }
}

void Lexer::re_set()
{
	this->_Line = ""; 
	this->_Mask.clear();
	this->_Chunk.clear();
}