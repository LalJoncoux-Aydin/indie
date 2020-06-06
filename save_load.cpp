/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** save_load
*/

#include <fstream>
#include <iostream>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

#include "Map.hpp"
#include "Character.hpp"

namespace pt = boost::property_tree;

namespace libSave
{
    std::string buildName(int x, int y)
    {
        std::string name = "Map_" + std::to_string(x) + "_" + std::to_string(y);
        return(name);
    }

    std::vector<std::pair<std::string, int>> prepCell(cell_t *cell)
    {
        std::vector<std::pair<std::string, int>> cellData;

        cellData.push_back(std::pair<std::string, int>("element", (cell->element)));
        cellData.push_back(std::pair<std::string, int>("bombSate", (cell->bombState)));
        cellData.push_back(std::pair<std::string, int>("player", (cell->player)));
        cellData.push_back(std::pair<std::string, int>("isBom", (cell->isBoom)));
        cellData.push_back(std::pair<std::string, int>("orient", (cell->orient)));
        cellData.push_back(std::pair<std::string, int>("isDeadBody", (cell->isDeadBody)));
        return (cellData);
    }

    int dumpMatrix(pt::ptree *oroot, std::vector<std::vector<cell_t>> matrix)
    {
        int x = 0;
        int y = 0;

        for (auto &line : matrix) {
            y = 0;
            for (auto &cell : line) {
                pt::ptree animals_node;
                auto cells_data = prepCell(&cell);
                for (auto &cell_data : cells_data)
                    animals_node.put(cell_data.first, cell_data.second);
                oroot->add_child(buildName(x, y), animals_node);
                y++;
            }
            x++;
        }
        return (0);
    }

    std::vector<std::vector<cell_t>> getMatrix(pt::ptree *iroot)
    {
        std::vector<std::vector<cell_t>> matrix;
        int x = 0;
        int y = 0;

        matrix.resize(34);
        for (; x < 32; x++) {
            matrix[x].resize(34);
            for (int y = 0; y < 32; y++) {
                for (pt::ptree::value_type &animal : iroot->get_child(buildName(x,y))) {
                    std::string name = animal.first;
                    if (strcmp(name.c_str(), "element") == 0) {
                        matrix[x][y].element = (decor)std::stoul(animal.second.data(), nullptr, 0);
                    }
                    if (strcmp(name.c_str(), "bombSate") == 0) {
                        matrix[x][y].bombState = (mapBomb)std::stoul(animal.second.data(), nullptr, 0);
                    }
                    if (strcmp(name.c_str(), "player") == 0) {
                        matrix[x][y].player = (Player)std::stoul(animal.second.data(), nullptr, 0);
                    }
                    if (strcmp(name.c_str(), "isBom") == 0) {
                        matrix[x][y].isBoom = (int)std::stoul(animal.second.data(), nullptr, 0);
                    }
                    if (strcmp(name.c_str(), "orient") == 0) {
                        matrix[x][y].orient = (orientation)std::stoul(animal.second.data(), nullptr, 0);
                    }
                    if (strcmp(name.c_str(), "isDeadBody") == 0) {
                        matrix[x][y].isDeadBody = (int)std::stoul(animal.second.data(), nullptr, 0);
                    }
                }
            }
        }
        return (matrix);
    }

    std::vector<unsigned int> getVector(pt::ptree *iroot, std::string key)
    {
        std::vector<unsigned int> times;

        for (pt::ptree::value_type &fruit : iroot->get_child(key)) {
            times.push_back(std::stoul (fruit.second.data(), nullptr, 0));
        }
        return (times);
    }

    std::vector<std::pair<std::string, std::string>> getPlayer(pt::ptree *iroot, std::string key)
    {
        std::vector<std::pair<std::string, std::string>> players;// = new std::vector<std::pair<std::string, std::string>>();

        for (pt::ptree::value_type &player : iroot->get_child(key)) {
            std::string name = player.first;
            std::string color = player.second.data();
            players.push_back(std::make_pair(name, color));
        }
        return (players);
    }

    int dumpPlayer(pt::ptree *oroot, std::vector<std::pair<std::string, std::string>> *players, std::string key)
    {
        pt::ptree players_node;

        for (auto &player : *players)
            players_node.put(player.first, player.second);
        oroot->add_child(key, players_node);
        return (0);
    }

    int dumpVector(pt::ptree *oroot, std::vector<unsigned int> time_vec, std::string key)
    {
        pt::ptree node;

        for (auto &time : time_vec) {
            pt::ptree node;
            node.put("", std::to_string(time));
            node.push_back(std::make_pair("", node));
        }
        oroot->add_child(key, node);
        return (0);
    }

    std::vector<unsigned int> getBombTime(Character *player)
    {
        std::vector<Bomb> bombs = player->getBombs();
        std::vector<unsigned int> tab;
 
        for (auto &bomb : bombs) {
            tab.push_back(bomb.getTimeBeforeExplosion());
        }
        return (tab);
    }

    std::vector<std::pair<std::string, std::string>> *characterPrep(Character *character)
    {
        std::vector<std::pair<std::string, std::string>> *player = new std::vector<std::pair<std::string, std::string>>();

        player->push_back(std::pair<std::string, std::string>("_maxBombs", std::to_string(character->getMaxBombs())));
        player->push_back(std::pair<std::string, std::string>("_bombRadius", std::to_string(character->getBombRadius())));
        player->push_back(std::pair<std::string, std::string>("_getSpeed", std::to_string(character->getSpeed())));
        auto pos = character->getPos();
        player->push_back(std::pair<std::string, std::string>("posX", std::to_string(pos.x)));
        player->push_back(std::pair<std::string, std::string>("posY", std::to_string(pos.y)));
        return (player);
    }
} // namespace libSave

std::pair<std::pair<std::vector<std::vector<std::pair<std::string, std::string>>>, std::vector<std::vector<cell_t>>>, std::vector<std::vector<unsigned int>>> readJson(std::string file_name)
{
    std::pair<std::pair<std::vector<std::vector<std::pair<std::string, std::string>>>, std::vector<std::vector<cell_t>>>, std::vector<std::vector<unsigned int>>> final;
    std::pair<std::vector<std::vector<std::pair<std::string, std::string>>>, std::vector<std::vector<cell_t>>> res_f;
    std::vector<std::vector<std::pair<std::string, std::string>>> res;
    std::vector<std::vector<unsigned int>> timer;
    pt::ptree iroot;
    pt::read_json(file_name, iroot);

    res.push_back(libSave::getPlayer(&iroot, "player1"));
    res.push_back(libSave::getPlayer(&iroot, "player2"));
    res.push_back(libSave::getPlayer(&iroot, "player3"));
    res.push_back(libSave::getPlayer(&iroot, "player2"));
    res_f.first = res;
    res_f.second = libSave::getMatrix(&iroot);
    timer.push_back(libSave::getVector(&iroot, "player1_bomb"));
    timer.push_back(libSave::getVector(&iroot, "player2_bomb"));
    timer.push_back(libSave::getVector(&iroot, "player3_bomb"));
    timer.push_back(libSave::getVector(&iroot, "player4_bomb"));
    final.first = res_f;
    final.second = timer;
    return (final);
}

int dumpJson(std::string file_name)
{
    pt::ptree oroot;
    Map map(32);
    std::vector<Character> players;
    players.push_back(Character(Vector<unsigned int>(1,1)));
    players.push_back(Character(Vector<unsigned int>(1,31)));
    players.push_back(Character(Vector<unsigned int>(31,1)));
    players.push_back(Character(Vector<unsigned int>(31,31)));

    map.dump();
    libSave::dumpPlayer(&oroot, libSave::characterPrep(&players[0]), "player1");
    libSave::dumpPlayer(&oroot, libSave::characterPrep(&players[1]), "player2");
    libSave::dumpPlayer(&oroot, libSave::characterPrep(&players[2]), "player3");
    libSave::dumpPlayer(&oroot, libSave::characterPrep(&players[3]), "player4");

    libSave::dumpVector(&oroot, libSave::getBombTime(&players[0]), "player1_bomb");
    libSave::dumpVector(&oroot, libSave::getBombTime(&players[1]), "player2_bomb");
    libSave::dumpVector(&oroot, libSave::getBombTime(&players[2]), "player3_bomb");
    libSave::dumpVector(&oroot, libSave::getBombTime(&players[3]), "player4_bomb");

    libSave::dumpMatrix(&oroot, map.getMap());
    std::ofstream my_output_file(file_name);
    pt::write_json(my_output_file, oroot);
    return (0);
}

int main()
{
    dumpJson("save.json");
    readJson("save.json");

    return 0;
}