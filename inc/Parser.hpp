/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeunki2 <daeunki2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 15:44:51 by daeunki2          #+#    #+#             */
/*   Updated: 2026/02/15 18:15:33 by daeunki2         ###   ########.fr       */
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

    bool                validate_buffer(const std::vector<s_token>& buffer);
    Cmd                 make_one_cmd(const std::vector<s_token>& buffer);
    std::vector<Cmd>    cmd_maker();
    void                handle_heredocs();
    bool                setup_all_redirections();
    void                check_builtin(Cmd& cmd);
    void                expand_cmd(Cmd& cmd);
    void                clear_cmds();

public:
    Parser();
    Parser(const std::vector<s_token>& tokens);
    ~Parser();
    Parser(const Parser& other);
    Parser& operator=(const Parser& other);
    void    set_tokens(const std::vector<s_token>& tokens);
    const std::vector<Cmd>& get_cmds() const;
    void print_cmds() const;
    std::vector<Cmd> parse();
    void re_set(); 
};

#endif