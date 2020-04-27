#include "level.h"
#include "graphics.h"
#include "tinyxml2.h"

#include <sstream>
#include <algorithm>
#include <cmath>

using namespace tinyxml2;

Level::Level() {}

Level::Level(std::string map_name, Vector2 spawn_point, Graphics& graphics):
_map_name(map_name),
_spawn_point(spawn_point),
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
                for (int i = 0; i != this->_tilesets.size(); i++) {
                    if (this->_tilesets[i].first_gid <= gid) {
                        tls = this->_tilesets[i];
                        break;
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
                int tileset_width, tileset_height;
                SDL_QueryTexture(tls.Texture, NULL, NULL, &tileset_width, &tileset_height);
                int tsxx = (gid % (tileset_width / tile_width) - 1) * tile_width;
                int tsyy = (gid / (tileset_width / tile_width)) * tile_height;
                Vector2 final_tileset_position(tsxx, tsyy);

                Tile tile(tls.Texture, Vector2(tile_width, tile_height), final_tileset_position, final_tile_position);
                this->_tile_list.push_back(tile);
                tile_counter++;

                p_tile = p_tile->NextSiblingElement("tile");
            }
            p_data = p_data->NextSiblingElement("data");
        }
        p_layer = p_layer->NextSiblingElement("layer");
    }
}

void Level::update(int elapsed_time) {

}

void Level::draw(Graphics &graphics) {
    for (int i = 0; i != this->_tile_list.size(); i++) {
        this->_tile_list[i].draw(graphics);
    }
}