/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_test.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeunki2 <daeunki2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 16:39:57 by daeunki2          #+#    #+#             */
/*   Updated: 2026/02/15 16:45:35 by daeunki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Lexer.hpp"
#include "Tokenizer.hpp"
#include "Parser.hpp"
#include <iostream>
#include <vector>
#include <string>

int main()
{
    Lexer 		lx;
    Tokenizer 	tk; 
	Parser		ps;
    
	std::vector<std::string> tests;
    tests.push_back("ls -al | grep 'cpp'"); 
    tests.push_back("ls|grep|wc -l");        
    tests.push_back("echo \"hello\">>out.txt");
    tests.push_back("cat << EOF > file");
    tests.push_back("echo '|' \">\" '>>'");
    tests.push_back("    ls    -al    ");
    tests.push_back("'unclosed quote"); 

    for (size_t i = 0; i < tests.size(); ++i)
    {
        std::cout << "\n========== TEST " << i << " ==========\n";
        
        lx.set_line(tests[i]);
        lx.mask_line();
        lx.chunk_line();
        tk.set_chunks(lx); 
        tk.tokenize();
		ps.set_tokens(tk.get_tokens());
		ps.parse();
		ps.print_cmds();
        lx.re_set();
        tk.re_set();
		ps.re_set();
    }
    return 0;
}