/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Tokenizer.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeunki2 <daeunki2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 17:58:09 by daeunki2          #+#    #+#             */
/*   Updated: 2026/02/15 17:17:08 by daeunki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Tokenizer.hpp"


Tokenizer::Tokenizer() : _chunks(NULL)
{

};

Tokenizer::Tokenizer(const Tokenizer &other)
{
    *this = other;
}

Tokenizer::~Tokenizer()
{

}

Tokenizer &Tokenizer::operator=(const Tokenizer &other)
{
    if (this != &other) {
        this->_chunks = other._chunks;
        this->_tokens = other._tokens;
    }
    return *this;
}

void Tokenizer::set_chunks(const Lexer &lexer_obj)
{
    this->_chunks = &lexer_obj;
}

std::vector<s_token> Tokenizer::get_tokens()
{
    return this->_tokens;
}

std::string Tokenizer::quote_remover(std::string string)
{
    if (string.size() < 2)
        return "";
    return string.substr(1, string.size() - 2);
}

t_type	Tokenizer::meta_type_identifier(std::string string)
{
    if (string == "|")
        return PIPE;
    else if (string == "<")
        return REDIRECT_IN;
    else if (string == "<<")
        return HEREDOC;
    else if (string == ">")
        return REDIRECT_OUT;
    else if (string == ">>")
        return APPEND;
    else
        return WORD;
    
};

s_token Tokenizer::make_new_token(std::string token)
{
    s_token temp;
    temp.text = token;
    temp.token_type = meta_type_identifier(token);
    temp.word_type = NORMAL;

    return temp;
}

std::vector<s_token> Tokenizer::split(std::string normal_chunk)
{
    std::string temp = "";
    std::vector<s_token> temp_token;
    for(size_t i = 0; i < normal_chunk.size(); i++)
    {
        if (normal_chunk[i] != ' ' && normal_chunk[i] != '|' && normal_chunk[i] != '<' && normal_chunk[i] != '>')
            temp += normal_chunk[i];
        else if (normal_chunk[i] == ' ')
        {
            if (!temp.empty())
            {
            temp_token.push_back(make_new_token(temp));
            temp.clear();
            }
        }
        else if ((normal_chunk[i] == '|' && normal_chunk[i+1] != '|'))
        {
            if (!temp.empty())
            {
            temp_token.push_back(make_new_token(temp));
            temp.clear();
            }
            temp_token.push_back(make_new_token("|"));
        }
        else if ((normal_chunk[i] == '<' && normal_chunk[i+1] != '<'))
        {
            if (!temp.empty())
            {
            temp_token.push_back(make_new_token(temp));
            temp.clear();
            }
            temp_token.push_back(make_new_token("<"));
        }
        else if ((normal_chunk[i] == '<' && normal_chunk[i+1] == '<'))
        {
            if (!temp.empty())
            {
            temp_token.push_back(make_new_token(temp));
            temp.clear();
            }
            temp_token.push_back(make_new_token("<<"));
            i++;
        }
        else if ((normal_chunk[i] == '>' && normal_chunk[i+1] != '>'))
        {
            if (!temp.empty())
            {
            temp_token.push_back(make_new_token(temp));
            temp.clear();
            }
            temp_token.push_back(make_new_token(">"));
        }
        else if ((normal_chunk[i] == '>' && normal_chunk[i+1] == '>'))
        {
            if (!temp.empty())
            {
            temp_token.push_back(make_new_token(temp));
            temp.clear();
            }
            temp_token.push_back(make_new_token(">>"));
            i++;
        }
    }
    if (!temp.empty())
    {
        temp_token.push_back(make_new_token(temp));
    }
    return (temp_token);
};
void Tokenizer::tokenize()
{
    const std::vector<std::pair<std::string, QuoteState> > &list = this->_chunks->get_chunks();

    for (size_t i = 0; i < list.size(); ++i)
    {
        if (list[i].second == SINGLE_QUOTE || list[i].second == DOUBLE_QUOTE)
        {
            s_token temp;
            temp.text = quote_remover(list[i].first);
            temp.word_type = list[i].second;
            temp.token_type = WORD;
            this->_tokens.push_back(temp);
        }
        else if (list[i].second == ERROR)
        {
            //추후 오케스트라에서 예외처리 클래스 만들고 그거 활용
            std::cerr << "Syntax Error: Unclosed quote" << std::endl;
            return;
        }
        else
        {
            std::vector<s_token>splitted = split(list[i].first);
            this->_tokens.insert(this->_tokens.end(), splitted.begin(), splitted.end());
        }
    }
}

void Tokenizer::print_tokens() const
{
    std::cout << "==== Tokenizer Debug ====\n";

    if (_tokens.empty()) {
        std::cout << "(No tokens found)" << std::endl;
        return;
    }

    for (size_t i = 0; i < _tokens.size(); ++i)
    {
        std::string type_name;
        switch (_tokens[i].token_type)
        {
            case WORD:         type_name = "WORD"; break;
            case PIPE:         type_name = "PIPE"; break;
            case REDIRECT_IN:  type_name = "REDIRECT_IN"; break;
            case REDIRECT_OUT: type_name = "REDIRECT_OUT"; break;
            case HEREDOC:      type_name = "HEREDOC"; break;
            case APPEND:       type_name = "APPEND"; break;
            default:           type_name = "UNKNOWN"; break;
        }

        std::string state_name;
        switch (_tokens[i].word_type)
        {
            case NORMAL:       state_name = "NORMAL"; break;
            case SINGLE_QUOTE: state_name = "SINGLE_QUOTE"; break;
            case DOUBLE_QUOTE: state_name = "DOUBLE_QUOTE"; break;
            case ERROR:        state_name = "ERROR"; break;
            default:           state_name = "UNKNOWN"; break;
        }

        std::cout << i << ": [" << _tokens[i].text << "]\n";
        std::cout << "   - WordState: " << state_name;
        std::cout << " | TokenType: " << type_name << "\n";
    }
    std::cout << "==========================\n";
}

void Tokenizer::re_set()
{
    this->_chunks = NULL;
    this->_tokens.clear();
}