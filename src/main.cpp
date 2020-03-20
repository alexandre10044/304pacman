/*
** EPITECH PROJECT, 2019
** Work
** File description:
** main
*/

#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string.h>
#include <list>
#include <sstream>
#include <string>
#include <fstream>
#include <algorithm>

#include "entry.hpp"

enum direction {
    North,
    East,
    South,
    West
};

std::ifstream makefileStream;
std::ifstream fileStream;
std::vector<std::string> data;
std::vector<entry *> entries;
std::vector<entry *> shortestEntries;
bool found = false;
char wall;
char space;
int width;
int pos = 0;

entry *searchEntryById(int id)
{
    try {
        for (int i = 0; i < entries.size(); i++)
            if (entries[i]->id = id)
                return (entries[i]);
        return (NULL);
    } catch (...) { return (NULL); }
}

entry *searchEntryByCoordinates(int x, int y)
{
    try {
        for (int i = 0; i < entries.size(); i++)
            if (entries[i]->x == x && entries[i]->y == y)
                return (entries[i]);
        return (NULL);
    } catch (...) { return (NULL); }
}

entry *searchEntryByType(int type)
{
    try {
        for (int i = 0; i < entries.size(); i++)
            if ((int)entries[i]->type == type)
                return (entries[i]);
        return (NULL);
    } catch (...) { return (NULL); }
}

entry *searchEntryByDirection(int dir, entry *curr)
{
    try {
        switch(dir) {
            case North:
                return (searchEntryByCoordinates(curr->x, curr->y - 1));
            case East:
                return (searchEntryByCoordinates(curr->x + 1, curr->y));
            case South:
                return (searchEntryByCoordinates(curr->x, curr->y + 1));
            case West:
                return (searchEntryByCoordinates(curr->x - 1, curr->y));
            default:
            return (NULL);
        }
    } catch (...) { return (NULL); }
}

enum entryType checkChar(char c)
{
    try {
        switch(c) {
            case '1':
                return (Wall);
            case '0':
                return (Empty);
            case 'F':
                return (Ghost);
            case 'P':
                return (Pacman);
            default:
                return (Invalid);
        };
    } catch (...) { return (Invalid); }
}

char toChar(enum entryType type)
{
    try {
        switch(type) {
            case Wall:
                return (wall);
            case Empty:
                return (space);
            case Ghost:
                return ('F');
            case Pacman:
                return ('P');
        };
    } catch (...) { return (' '); }
}

bool parseLine(std::string line)
{
    try {
        if (pos != 0 && width != line.size()) {
            std::cout << "Invalid file size." << std::endl;
            return (false);
        }
        enum entryType type;
        width = line.size();
        for (int i = 0; i < line.size(); i++) {
            if (checkChar(line[i]) == Invalid)
                return (false);
            entry *ent = new entry();
            ent->id = pos * width + i;
            ent->type = checkChar(line[i]);
            ent->x = i;
            ent->y = pos;
            entries.push_back(ent);
        }
        return (true);
    } catch (...) { return (false); }
}

void debug()
{
    try {
        for (int i = 0; i < entries.size(); i++) {
            std::cout << "ID = " << entries[i]->id;
            std::cout << " TYPE = " << entries[i]->type;
            std::cout << " X = " << entries[i]->x;
            std::cout << " Y = " << entries[i]->y;
            std::cout << std::endl;
        }
    } catch (...) { return; }
}

bool displayMap()
{
    try {
        char c;

        for (int i = 0; i < entries.size(); i++) {
            if (i != 0 && entries[i - 1]->y != entries[i]->y)
                std::cout << std::endl;
            if (entries[i]->type == Value) {
                if (entries[i]->value >= 0 && entries[i]->value <= 9)
                    c = entries[i]->value + '0';
                else
                    c = '9';
            } else
                c = toChar(entries[i]->type);
            std::cout << c;
        }
        std::cout << std::endl;
        return (true);
    } catch (...) { return (false); }
}

bool check_if_arrived(entry *current)
{
    try {
        for (int i = 0; i < 4; i++) {
            entry *tmp = searchEntryByDirection(i, current);
            if (tmp->type == Pacman)
                return (true);
        }
        return (false);
    } catch (...) { return (false); }
}

bool process_entity(int distance)
{
    try {
        std::vector<entry *> next;
        if (!shortestEntries.size())
            return (false);
        // Update Values First cells
        for (int i = 0; i < shortestEntries.size(); i++) {
            for (int u = 0; u < 4; u++) {
                entry *tmp = searchEntryByDirection(u, shortestEntries[i]);
                if (tmp == NULL)
                    continue;
                if (tmp->type == Pacman)
                    return (true);
                if (tmp->type != Empty)
                    continue;
                tmp->type = Value;
                tmp->value = distance;
                next.push_back(tmp);
            }
        }
        shortestEntries = next;
        if (distance + 1 > 9)
            distance = -1;
        return (process_entity(distance + 1));
    } catch (...) { return (false); }
}

bool process_path()
{
    try {
        entry *end = searchEntryByType(Pacman);
        entry *current = searchEntryByType(Ghost);;
        int i = 0;

        if (current == NULL || end == NULL)
            return (false);
        shortestEntries.clear();
        shortestEntries.push_back(current);
        return (process_entity(1));
    } catch (...) { return (NULL); }
}

int main(int ac, char **av)
{
    std::string line;
    try {
        // Help
        if (ac >= 2 && (!strcmp(av[1], "-h") || !strcmp(av[1], "-help"))) {
            std::cout << "USAGE" << std::endl;
            std::cout << "\t" << av[0] << " file c1 c2" << std::endl;
            std::cout << "DESCRIPTION" << std::endl;
            std::cout << "\tfile\trepresent the gameboard" << std::endl;
            std::cout << "\tc1\tcharacter to display for a wall" << std::endl;
            std::cout << "\tc2\tcharacter to display for an empty space" << std::endl;
            return (0);
        }
        // ErrorHandling
        if (ac != 4 || strlen(av[2]) != 1 || strlen(av[3]) != 1 || av[2][0] == av[3][0]) {
            std::cerr << "Bad usage." << std::endl;
            return (84);
        }
        wall = av[2][0];
        space = av[3][0];
    } catch (...) { return (84); }
    try {
        makefileStream.open(av[1]);
        if (makefileStream.fail()) {
            std::cerr << "Bad input." << std::endl;
            return (84);
        }
        // Parsing
        for (pos = 0; std::getline(makefileStream, line); pos++)
        {
            std::string d(line.c_str());
            data.push_back(d);
            if (!parseLine(line)) {
                std::cerr << "Invalid file. line " << pos << std::endl;
                return (84);
            }
        }
        if (!process_path()) {
            std::cerr << "Error during the process of the path." << std::endl;
            return (84);
        }
        if (!displayMap())
            return (84);
    } catch (...) { return (84); }
    return (0);
}