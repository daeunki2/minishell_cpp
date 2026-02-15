/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cmd.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeunki2 <daeunki2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 15:22:42 by daeunki2          #+#    #+#             */
/*   Updated: 2026/02/15 18:00:22 by daeunki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_HPP
#define CMD_HPP

#include <iostream>
#include <vector>
#include <string>

class Cmd
{
public:
    int                                                 in_fd;
    int                                                 out_fd;
    std::string                                         cmd_path;
    std::vector<std::pair<std::string, QuoteState> >    args;
    bool                        is_builtin;
    std::string                 infile_name;
    std::string                 outfile_name;
    std::string                 heredoc_buffer;
    std::string                 limiter;
    bool                        append_mode;
    int                         pipe_fd[2];

    Cmd();
    ~Cmd();
    char** get_argv_for_exec() const;
    void   free_argv(char** argv) const;
    Cmd(const Cmd& other);
    Cmd& operator=(const Cmd& other);
};

#endif