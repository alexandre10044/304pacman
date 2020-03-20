/*
** EPITECH PROJECT, 2019
** entry.hpp
** File description:
** entry
*/

#ifndef ENTRY_HPP_
    #define ENTRY_HPP_

    #include <string>
    #include <vector>

    enum entryType {
        Empty,
        Wall,
        Ghost,
        Pacman,
        Invalid,
        Value
    };

    class entry {
        public:
            entry();
            ~entry();

            int id;
            int x;
            int y;
            enum entryType type;
            int value = 0;
    };


#endif /* !ENTRY_HPP_ */