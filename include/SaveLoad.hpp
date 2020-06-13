#ifndef SAVELOAD_HPP_
#define SAVELOAD_HPP_

#include <fstream>
#include <iostream>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

namespace pt = boost::property_tree;

class SaveLoad
{
    public:
        SaveLoad() {};
        ~SaveLoad() {};

        std::string buildName(int x, int y) {
            std::string name = "Map_" + std::to_string(x) + "_" + std::to_string(y);
            return(name);
        };

        std::vector<std::pair<std::string, int>> prepCell(cell_t *cell) {
            std::vector<std::pair<std::string, int>> cellData;

            cellData.push_back(std::pair<std::string, int>("element", (cell->element)));
            cellData.push_back(std::pair<std::string, int>("bombSate", (cell->bombState)));
            cellData.push_back(std::pair<std::string, int>("player", (cell->player)));
            cellData.push_back(std::pair<std::string, int>("isBom", (cell->isBoom)));
            cellData.push_back(std::pair<std::string, int>("orient", (cell->orient)));
            cellData.push_back(std::pair<std::string, int>("isDeadBody", (cell->isDeadBody)));
            return (cellData);
        };

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
        };

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
                            matrix[x][y].player = (PlayerNb)std::stoul(animal.second.data(), nullptr, 0);
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
        };

        std::vector<unsigned int> getVector(pt::ptree *iroot, std::string key)
        {
            std::vector<unsigned int> times;

            for (pt::ptree::value_type &fruit : iroot->get_child(key)) {
                times.push_back(std::stoul (fruit.second.data(), nullptr, 0));
            }
            return (times);
        };

        std::vector<std::pair<std::string, std::string>> getPlayer(pt::ptree *iroot, std::string key)
        {
            std::vector<std::pair<std::string, std::string>> players;// = new std::vector<std::pair<std::string, std::string>>();

            for (pt::ptree::value_type &player : iroot->get_child(key)) {
                std::string name = player.first;
                std::string color = player.second.data();
                players.push_back(std::make_pair(name, color));
            }
            return (players);
        };

        int dumpPlayer(pt::ptree *oroot, std::vector<std::pair<std::string, std::string>> *players, std::string key)
        {
            pt::ptree players_node;

            for (auto &player : *players)
                players_node.put(player.first, player.second);
            oroot->add_child(key, players_node);
            return (0);
        };

        std::vector<std::pair<std::string, std::string>> *characterPrep(ICharacter *character)
        {
            std::vector<std::pair<std::string, std::string>> *player = new std::vector<std::pair<std::string, std::string>>();

            player->push_back(std::pair<std::string, std::string>("_getSpeed", std::to_string(character->getSpeed())));
            player->push_back(std::pair<std::string, std::string>("_bombRadius", std::to_string(character->getBombs()->getExplosionRadius())));
            player->push_back(std::pair<std::string, std::string>("_placed", std::to_string(character->getBombs()->isPlaced())));
            player->push_back(std::pair<std::string, std::string>("_time", std::to_string(character->getBombs()->getPassedTime())));
            auto pos = character->getPos();
            player->push_back(std::pair<std::string, std::string>("posX", std::to_string(pos.x)));
            player->push_back(std::pair<std::string, std::string>("posY", std::to_string(pos.y)));
            return (player);
        };

        void dumpNbPlayer(pt::ptree *oroot, bool multi_player)
        {
            pt::ptree nb_player_node;

            if (multi_player == true) {
                pt::ptree temp_node;
                temp_node.put("", "Player 2");
                nb_player_node.push_back(std::make_pair("", temp_node));
            } else {
                pt::ptree temp_node;
                temp_node.put("", "Player 2");
                nb_player_node.push_back(std::make_pair("", temp_node));
            }
            oroot->add_child("Nb_player", nb_player_node);
        };
}; // namespace libSave

#endif
