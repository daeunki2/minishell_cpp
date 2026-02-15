/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_test.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeunki2 <daeunki2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 12:38:58 by daeunki2          #+#    #+#             */
/*   Updated: 2026/02/15 15:12:04 by daeunki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Lexer.hpp"
#include "Tokenizer.hpp"
#include <iostream>
#include <vector>
#include <string>

int main()
{
    Lexer lx;
    Tokenizer tk; 

    std::vector<std::string> tests;
    tests.push_back("ls -al | grep 'cpp'"); 
    tests.push_back("ls|grep|wc -l");        
    tests.push_back("echo \"hello\">>out.txt");
    tests.push_back("cat << EOF > file");
    tests.push_back("echo '|' \">\" '>>'");
    tests.push_back("    ls    -al    ");    // 과도한 공백
    tests.push_back("'unclosed quote");      // 에러 처리

    for (size_t i = 0; i < tests.size(); ++i)
    {
        std::cout << "\n========== TEST " << i << " ==========\n";
        
        lx.set_line(tests[i]);
        lx.mask_line();
        lx.chunk_line();
        //lx.print_tokens();
        std::cout << "\n--- Tokenizing Result ---\n";
		std::cout << "[input string] " << tests[i] << std::endl;
        tk.set_chunks(lx); 
        tk.tokenize();
        tk.print_tokens();
        lx.re_set();
        tk.re_set();
    }
    return 0;
}