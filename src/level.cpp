#include "level.h"
#include "graphics.h"
#include "tinyxml2.h"
#include "utils.h"
#include "slope.h"

#include <sstream>
#include <algorithm>
#include <cmath>

using namespace tinyxml2;

Level::Level() {}

Level::Level(std::string map_name, Graphics& graphics):
_map_name(map_name),
_size(Vector2()) {

    this->load_map(map_name, graphics);
}

Level::~Level() {}

void Level::load_map(std::string map_name, Graphics &graphics) {
    XMLDocument doc;
    std::stringstream ss;
    ss << "../assets/maps/" << map_name << ".tmx";
    doc.LoadFile(ss.str().c_str());

    XMLElement* map_node = doc.FirstChildElement("map");
    int width, height;
    map_node->QueryIntAttribute("width", &width);   //in terms of number of tiles
    map_node->QueryIntAttribute("height", &height);
    this->_size = Vector2(width, height);

    int tile_width, tile_height;
    map_node->QueryIntAttribute("tilewidth", &tile_width);
    map_node->QueryIntAttribute("tileheight", &tile_height);
    this->_tile_size = Vector2(tile_width, tile_height);


    XMLElement* p_tile_set = map_node->FirstChildElement("tileset");
    while (p_tile_set) {
        const char* source = p_tile_set->FirstChildElement("image")->Attribute("source");
        int first_gid;
        p_tile_set->QueryIntAttribute("firstgid", &first_gid);

        std::stringstream ss;
        ss << "../assets/tilesets/" << source;
        SDL_Texture* tex = SDL_CreateTextureFromSurface(graphics.get_renderer(), graphics.load_image(ss.str()));
        this->_tilesets.push_back(Tileset(tex, first_gid));

        //handle animation for this tileset
        XMLElement* p_tile_a = p_tile_set->FirstChildElement("tile");
        while (p_tile_a) {
            AnimatedTileInfo ati;
            ati.start_tile_id = p_tile_a->IntAttribute("id") + first_gid;
            ati.tilesets_first_gid = first_gid;
            XMLElement* p_animation = p_tile_a->FirstChildElement("animation");
            while (p_animation) {
                XMLElement* p_frame = p_animation->FirstChildElement("frame");
                while (p_frame) {
                    ati.tile_ids.push_back(p_frame->IntAttribute("tileid") + first_gid);
                    ati.duration = p_frame->IntAttribute("duration");
                    p_frame = p_frame->NextSiblingElement("frame");
                }
                p_animation = p_animation->NextSiblingElement("animation");
            }
            this->_animated_tile_infos.push_back(ati);
            p_tile_a = p_tile_a->NextSiblingElement("tile");
        }

        p_tile_set = p_tile_set->NextSiblingElement("tileset");
    }

    XMLElement* p_layer = map_node->FirstChildElement("layer");
    while (p_layer) {
        XMLElement* p_data = p_layer->FirstChildElement("data");
        while (p_data) {
            XMLElement* p_tile = p_data->FirstChildElement("tile");
            int tile_counter = 0;
            while (p_tile) {
                if (p_tile->IntAttribute("gid") == 0) {
                    tile_counter++;
                    if (p_tile->NextSiblingElement("tile")) {
                        p_tile = p_tile->NextSiblingElement("tile");
                        continue;
                    } else  break;
                }

                int gid = p_tile->IntAttribute("gid");
                Tileset tls;
                int closest = 0;
                for (int i = 0; i != this->_tilesets.size(); i++) {
                    if (this->_tilesets[i].first_gid <= gid) {
                        if (this->_tilesets[i].first_gid > closest) {
                            closest = this->_tilesets[i].first_gid;
                            tls = this->_tilesets[i];
                        }
                    }
                }

                if (tls.first_gid == -1) {
                    tile_counter++;
                    if (p_tile->NextSiblingElement("tile")) {
                        p_tile = p_tile->NextSiblingElement("tile");
                        continue;
                    } else  break;
                }

                //current tile position
                int xx = (tile_counter % width) * tile_width;
                int yy = (tile_counter / width) * tile_height;
                Vector2 final_tile_position(xx, yy);

                //tile position in the tileset
                Vector2 final_tileset_position = this->get_tileset_position(tls, gid, tile_width, tile_height);

                bool is_animated = false;
                AnimatedTileInfo ati;
                for (int i = 0; i != this->_animated_tile_infos.size(); i++) {
                    if (this->_animated_tile_infos[i].start_tile_id == gid) {
                        ati = this->_animated_tile_infos[i];
                        is_animated = true;
                        break;
                    }
                }

                if (is_animated) {
                    std::vector<Vector2> tileset_positions;
                    for (int i = 0; i != ati.tile_ids.size(); i++) {
                        tileset_positions.push_back(this->get_tileset_position(tls, ati.tile_ids[i], tile_width, tile_height));
                    }
                    AnimatedTile tile(tileset_positions, ati.duration, tls.Texture, Vector2(tile_width, tile_height), final_tile_position);
                    this->_animated_tile_list.push_back(tile);

                } else  {
                    Tile tile(tls.Texture, Vector2(tile_width, tile_height), final_tileset_position, final_tile_position);
                    this->_tile_list.push_back(tile);
                }
                tile_counter++;

                p_tile = p_tile->NextSiblingElement("tile");
            }
            p_data = p_data->NextSiblingElement("data");
        }
        p_layer = p_layer->NextSiblingElement("layer");
    }
    //parse collisions
    XMLElement* p_objectgroup = map_node->FirstChildElement("objectgroup");
    while (p_objectgroup) {
        const char* name = p_objectgroup->Attribute("name");
        std::string group_name(name);

        if (group_name == "collisions") {
            XMLElement* p_object = p_objectgroup->FirstChildElement("object");
            while (p_object) {
                double x = p_object->DoubleAttribute("x");
                double y = p_object->DoubleAttribute("y");
                double width = p_object->DoubleAttribute("width");
                double height = p_object->DoubleAttribute("height");

                this->_collision_rects.push_back(Rectangle(
                    ceil(x) * globals::SPRITE_SCALE,
                    ceil(y) * globals::SPRITE_SCALE,
                    ceil(width) * globals::SPRITE_SCALE,
                    ceil(height) * globals::SPRITE_SCALE
                ));

                p_object = p_object->NextSiblingElement("object");
            }

        } else if (group_name == "slopes") {
            XMLElement* p_object = p_objectgroup->FirstChildElement("object");
            while (p_object) {
                XMLElement* p_polyline = p_object->FirstChildElement("polyline");
                std::vector<Vector2> points;
                Vector2 p1(ceil(p_object->DoubleAttribute("x")), ceil(p_object->DoubleAttribute("y")));;

                if (p_polyline) {
                    std::vector<std::string> pairs;
                    Utils::split(std::string(p_polyline->Attribute("points")), pairs, ' ');

                    for (auto p: pairs) {
                        std::vector<std::string> pairs_seperated;
                        Utils::split(p, pairs_seperated, ',');

                        points.push_back(Vector2(
                            std::stoi(pairs_seperated[0]),
                            std::stoi(pairs_seperated[1])));
                    }
                }

                for (int i = 0; i < points.size(); i += 2) {
                    this->_slopes.push_back(Slope(
                            Vector2((p1.x + points.at(i < 2 ? i : i - 1).x) * globals::SPRITE_SCALE,
                                    (p1.y + points.at(i < 2 ? i : i - 1).y) * globals::SPRITE_SCALE),
                            Vector2((p1.x + points.at(i < 2 ? i + 1 : i).x) * globals::SPRITE_SCALE,
                                    (p1.y + points.at(i < 2 ? i + 1 : i).y) * globals::SPRITE_SCALE)
                    ));
                }

                p_object = p_object->NextSiblingElement("object");
            }

        } else if (group_name == "spawn points") {
            XMLElement* p_object = p_objectgroup->FirstChildElement("object");
            while (p_object) {
                double x = p_object->DoubleAttribute("x");
                double y = p_object->DoubleAttribute("y");
                const char* name = p_object->Attribute("name");

                if (std::string(name) == "player") {
                    this->_spawn_point = Vector2(ceil(x) * globals::SPRITE_SCALE, ceil(y) * globals::SPRITE_SCALE);
                    break;
                }

                p_object = p_object->NextSiblingElement("object");
            }
        } else if (group_name == "doors") {
            XMLElement* p_object = p_objectgroup->FirstChildElement("object");
            while (p_object) {
                double x = p_object->DoubleAttribute("x");
                double y = p_object->DoubleAttribute("y");
                double w = p_object->DoubleAttribute("width");
                double h = p_object->DoubleAttribute("height");
                Rectangle rect(x, y, w, h);

                XMLElement* p_properties = p_object->FirstChildElement("properties");
                while (p_properties) {
                    XMLElement* p_property = p_properties->FirstChildElement("property");
                    while (p_property) {
                        const char* name = p_property->Attribute("name");
                        std::string p_name(name);
                        if (p_name == "destination") {
                            const char* value = p_property->Attribute("value");
                            std::string dest(value);
                            Door door(rect, dest);
                            this->_doors.push_back(door);
                        }

                        p_property = p_property->NextSiblingElement("property");
                    }

                    p_properties = p_properties->NextSiblingElement("properties");
                }
                p_object = p_object->NextSiblingElement("object");
            }
        }

        p_objectgroup = p_objectgroup->NextSiblingElement("objectgroup");
    }
}

void Level::update(int elapsed_time) {
    for (int i = 0; i != this->_animated_tile_list.size(); i++) {
        this->_animated_tile_list[i].update(elapsed_time);
    }
}

void Level::draw(Graphics &graphics) {
    for (int i = 0; i != this->_tile_list.size(); i++) {
        this->_tile_list[i].draw(graphics);
    }

    for (int i = 0; i != this->_animated_tile_list.size(); i++) {
        this->_animated_tile_list[i].draw(graphics);
    }
}

std::vector<Rectangle> Level::check_tile_collisions(const Rectangle &other) {
    std::vector<Rectangle> others;
    for (auto rect: this->_collision_rects) {
        if (rect.collides_with(other)) {
            others.push_back(rect);
        }
    }
    return others;
}

std::vector<Slope> Level::check_slope_collisions(const Rectangle &other) {
    std::vector<Slope> others;
    for (auto slope: this->_slopes) {
        if (slope.collides_with(other)) {
            others.push_back(slope);
        }
    }
    return others;
}

std::vector<Door> Level::check_door_collisions(const Rectangle &other) {
    std::vector<Door> others;
    for (auto door: this->_doors) {
        if (door.collides_with(other)) {
            others.push_back(door);
        }
    }
    return others;
}

const Vector2 Level::get_player_spawn_point() const {
    return this->_spawn_point;
}

Vector2 Level::get_tileset_position(Tileset tls, int gid, int tile_width, int tile_height) {
    int tileset_width, tileset_height;
    SDL_QueryTexture(tls.Texture, NULL, NULL, &tileset_width, &tileset_height);
    int tsxx = ((gid - 1) % (tileset_width / tile_width)) * tile_width;
    int tsyy = ((gid - tls.first_gid) / (tileset_width / tile_width)) * tile_height;
    return Vector2(tsxx, tsyy);
}