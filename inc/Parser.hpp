/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeunki2 <daeunki2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 15:44:51 by daeunki2          #+#    #+#             */
/*   Updated: 2026/02/15 15:49:36 by daeunki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_HPP
#define PARSER_HPP

#include <vector>
#include <iostream>
#include "Tokenizer.hpp"
#include "Cmd.hpp"

class Parser
{
private:
    std::vector<s_token>    _tokens;
    std::vector<Cmd>       _cmd_list;

    bool    validate_buffer(const std::vector<s_token>& buffer);
    void    process_buffer(const std::vector<s_token>& buffer);
    void    clear_cmds();

public:
    Parser();
    Parser(const std::vector<s_token>& tokens);
    ~Parser();
    Parser(const Parser& other);
    Parser& operator=(const Parser& other);
    std::vector<Cmd> parse();
};

#endif