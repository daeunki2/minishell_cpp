/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cmd.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeunki2 <daeunki2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 15:31:54 by daeunki2          #+#    #+#             */
/*   Updated: 2026/02/15 15:38:56 by daeunki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cmd.hpp"
#include <cstdlib> // NULL을 위해 필요

Cmd::Cmd() 
    : in_fd(0), out_fd(1), is_builtin(false), append_mode(false) 
{
    pipe_fd[0] = -1;
    pipe_fd[1] = -1;
}

Cmd::~Cmd()
{
}

char** Cmd::get_argv_for_exec() const
{
	if (args.empty())
		return NULL;
    size_t size = args.size();
    char** argv = new char*[size + 1];

    for (size_t i = 0; i < size; ++i)
	{
        argv[i] = const_cast<char*>(args[i].c_str());
    }
    argv[size] = NULL;
    return argv;
}

void Cmd::free_argv(char** argv) const
{
    if (argv)
	{
        delete[] argv;
    }
}