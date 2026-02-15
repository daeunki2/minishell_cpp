/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_test.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeunki2 <daeunki2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 14:46:25 by daeunki2          #+#    #+#             */
/*   Updated: 2026/02/12 23:23:54 by daeunki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Lexer.hpp"
#include <iostream>


#include "Lexer.hpp"
#include <vector>
#include <string>
#include <iostream>

int main()
{
    Lexer lx;

    std::vector<std::string> tests;
    tests.push_back("apple banana kiwi");
    tests.push_back("apple 'kiwi' \"banana\"");

    // quotes inside quotes (should be treated as normal chars)
    tests.push_back("'a\"b\"c'");
    tests.push_back("\"a'b'c\"");

    // empty quotes / adjacent quotes
    tests.push_back("''");
    tests.push_back("\"\"");
    tests.push_back("a''b");
    tests.push_back("a\"\"b");

    // unclosed quotes (should trigger your error handling)
    tests.push_back("'apple");
    tests.push_back("\"apple");

    // no spaces around quotes
    tests.push_back("echo\"hello\"world");
    tests.push_back("echo'hello'world");

    // spaces preserved inside quotes (useful for next token stage)
    tests.push_back("echo \"a  b   c\"");
    tests.push_back("echo 'a  b   c'");

    // mixed long input
    tests.push_back("aa \"bb cc\" dd 'ee ff' gg");

    for (size_t i = 0; i < tests.size(); ++i)
    {
        std::cout << "\n========== TEST " << i << " ==========\n";
        lx.set_line(tests[i]);
        lx.mask_line();
        lx.chunk_line();
        lx.print_tokens();
        lx.re_set();
    }
    return 0;
}
