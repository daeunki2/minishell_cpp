/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeunki2 <daeunki2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 16:34:43 by daeunki2          #+#    #+#             */
/*   Updated: 2026/02/15 18:21:28 by daeunki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parser.hpp"

/* ************************************************************************** */
/*              															  */
/* CONSTRUCTOR & DESTRUCTOR                                                   */
/*																			  */
/* ************************************************************************** */
Parser::Parser() : _tokens(), _cmd_list() 
{
}

Parser::Parser(const std::vector<s_token>& tokens) : _tokens(tokens), _cmd_list() 
{
}

Parser::~Parser() 
{
    _cmd_list.clear();
}

Parser::Parser(const Parser& other) 
{
    *this = other;
}

Parser& Parser::operator=(const Parser& other) 
{
    if (this != &other) 
    {
        this->_tokens = other._tokens;
        this->_cmd_list = other._cmd_list;
	}
	return *this;
}
/* ************************************************************************** */
/*              															  */
/* SET & GET                                                                  */
/*																			  */
/* ************************************************************************** */
void Parser::set_tokens(const std::vector<s_token>& tokens)
{
    this->re_set();
    this->_tokens = tokens;
};

void Parser::re_set()
{
    _tokens.clear();
    _cmd_list.clear();
};
const std::vector<Cmd>& Parser::get_cmds() const
{
    return _cmd_list;
};


/* ************************************************************************** */
/*              															  */
/* CMD MAKER LOGIC                                                            */
/*																			  */
/* ************************************************************************** */
bool Parser::validate_buffer(const std::vector<s_token>& buffer)
{
    if (buffer.empty() || buffer[0].token_type == PIPE)
		return false;
    if (buffer[buffer.size() - 1].token_type != WORD)
    {
        std::cerr << "minishell: syntax error near unexpected token `newline'" << std::endl;
        return false;
    }
    for (size_t i = 0; i < buffer.size() - 1; i++)
    {
        if (buffer[i].token_type != WORD && buffer[i + 1].token_type != WORD)
        {
            std::cerr << "minishell: syntax error near unexpected token `" << buffer[i + 1].text << "'" << std::endl;
            return false;
        }
    }
    return true;
}

Cmd Parser::make_one_cmd(const std::vector<s_token>& buffer)
{
    Cmd cmd;
    
    cmd.append_mode = false;

    for (size_t i = 0; i < buffer.size(); i++)
    {
        if (buffer[i].token_type == WORD)
        {
            cmd.args.push_back(std::pair<std::string, QuoteState>(buffer[i].text, buffer[i].word_type));
        }
        else if (buffer[i].token_type == REDIRECT_IN)
        {
            cmd.infile_name = buffer[++i].text;
        }
        else if (buffer[i].token_type == REDIRECT_OUT)
        {
            cmd.outfile_name = buffer[++i].text;
            cmd.append_mode = false;
        }
        else if (buffer[i].token_type == APPEND)
        {
            cmd.outfile_name = buffer[++i].text;
            cmd.append_mode = true;
        }
        else if (buffer[i].token_type == HEREDOC)
        {
            cmd.limiter = buffer[++i].text;
        }
    }
    return (cmd);
}


std::vector<Cmd> Parser::cmd_maker()
{
    std::vector<s_token> buffer;
    
    for (size_t i = 0; i < _tokens.size(); i++)
    {
        if (_tokens[i].token_type != PIPE)
        {
            buffer.push_back(_tokens[i]);
        }
        else
        {
			if(buffer.empty())
			{
				_cmd_list.clear();
				return _cmd_list;
			}
            if (validate_buffer(buffer))
            {
                _cmd_list.push_back(make_one_cmd(buffer));
            }
			else
			{
				//추후에 오류처리 필수
			}
            buffer.clear();
        }
    }    
	if (buffer.empty())
	{
        std::cerr << "minishell: syntax error: unexpected end of file" << std::endl;
        _cmd_list.clear();
    }
    else if (validate_buffer(buffer))
	{
        _cmd_list.push_back(make_one_cmd(buffer));
    }
    else
	{
        _cmd_list.clear();
    }    
    return _cmd_list;
}

/* ************************************************************************** */
/*              															  */
/* EXPANSION & REDIRECT                                                       */
/*																			  */
/* ************************************************************************** */
void	Parser::handle_heredocs()
{
	
};
bool	Parser::setup_all_redirections()
{};
void	Parser::expand_cmd(Cmd& cmd)
{};

void Parser::check_builtin(Cmd& cmd)
{

    const std::string& first_arg = cmd.args[0].first;

    if (first_arg == "echo" || first_arg == "cd" || first_arg == "pwd" ||
        first_arg == "export" || first_arg == "unset" || first_arg == "env" ||
        first_arg == "exit") 
    {
        cmd.is_builtin = true;
    }
    else
    {
        cmd.is_builtin = false;
    }
};

/* ************************************************************************** */
/*              															  */
/* FINAL PARSER                                                               */
/*																			  */
/* ************************************************************************** */
std::vector<Cmd> Parser::parse()
{
	/* 커맨드 만들기 > 치환하기 > 리디렉션 & 히어독 > 빌트인 플래그 까지*/
};



/* ************************************************************************** */
/*              															  */
/* UNIT TEST                                                                  */
/*																			  */
/* ************************************************************************** */

void Parser::print_cmds() const
{
    std::cout << "==== Parser Debug (Cmd List) ====\n";

    if (_cmd_list.empty()) {
        std::cout << "(No commands parsed)" << std::endl;
        return;
    }

    for (size_t i = 0; i < _cmd_list.size(); ++i)
    {
        const Cmd& cmd = _cmd_list[i];
        std::cout << "Command [" << i << "]:\n";

        std::cout << "  - Args: ";
        if (cmd.args.empty())
		{
            std::cout << "(empty)";
        } 
		else
		{
            for (size_t j = 0; j < cmd.args.size(); ++j)
			{
                std::cout << "[" << cmd.args[j] << "] ";
            }
        }
        std::cout << "\n";
        std::cout << "  - Infile:  " << (cmd.infile_name.empty() ? "(none)" : cmd.infile_name) << "\n";
        std::cout << "  - Outfile: " << (cmd.outfile_name.empty() ? "(none)" : cmd.outfile_name);
        if (!cmd.outfile_name.empty())
		{
            std::cout << (cmd.append_mode ? " (Append Mode)" : " (Truncate Mode)");
        }
        std::cout << "\n";
        std::cout << "  - Is Builtin: " << (cmd.is_builtin ? "Yes" : "No") << "\n";
        std::cout << "  - Path:       " << (cmd.cmd_path.empty() ? "(not searched yet)" : cmd.cmd_path) << "\n";
        
        if (i < _cmd_list.size() - 1)
		{
            std::cout << "      | (Pipe) |      \n";
        }
    }
    std::cout << "================================\n";
}

void Parser::clear_cmds() 
{
    _cmd_list.clear();
}