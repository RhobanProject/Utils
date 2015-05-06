#include <fstream>
#include <cstdlib>
#include <cstdio>
#include <json/json.h>
#include <logging/Logger.h>
#include "Function.h"

static Rhoban::Logger out("function");

#define POINT_X(n) points[2*(n)]
#define POINT_Y(n) points[2*(n)+1]

Function::Function()
    : nbPoints(0)
{
}

void Function::clear()
{
    points.clear();
    ds.clear();
    nbPoints = 0;
}

static std::string file_get_contents(std::string path)
{
    std::ifstream ifs(path.c_str());
    std::string content((std::istreambuf_iterator<char>(ifs)),
            (std::istreambuf_iterator<char>()));
    return content;
}

std::map<std::string, Function> Function::fromFile(std::string filename)
{
    auto data = file_get_contents(filename);
    Json::Value json;
    Json::Reader reader;
    std::map<std::string, Function> result;

    if (reader.parse(data, json)) {
        if (json.isObject()) {
            for (auto name : json.getMemberNames()) {
                auto data = json[name];
                Function f;
                if (data.isArray()) {
                    for (unsigned int k=0; k<data.size(); k++) {
                        auto entry = data[k];
                        if (entry.isArray() && entry.size()==2) {
                            f.addPoint(entry[0].asDouble(), entry[1].asDouble());
                        }
                    }
                }
                result[name] = f;
            }
        }
    } else {
        out.error("Malformed file %s:\n %s", filename.c_str(), reader.getFormatedErrorMessages().c_str());
    }

    return result;
}

double Function::getXMax()
{
    if (nbPoints == 0) {
        return 0.0;
    }

    return POINT_X(nbPoints-1);
}

void Function::addPoint(double x, double y)
{
    points.push_back(x);
    points.push_back(y);

    if (nbPoints > 0) {
        float d = POINT_Y(nbPoints) - POINT_Y(nbPoints-1);
        d /= POINT_X(nbPoints) - POINT_X(nbPoints-1);
        ds.push_back(d);
    }

    nbPoints++;
}

double Function::get(double x)
{
    int i;
    
    if (nbPoints == 0) {
        return 0.0;
    }

    for (i=0; i<nbPoints; i++) {
        if (POINT_X(i) >= x) {
            break;
        }
    }

    if (i == 0) {
        return POINT_Y(0);
    }
    if (i == nbPoints) {
        return POINT_Y(nbPoints-1);
    }

    return POINT_Y(i-1)+ds[i-1]*(x-POINT_X(i-1));
}

double Function::getMod(double x)
{
    double maxX = getXMax();

    if (x < 0.0 || x > maxX) {
        x -= maxX*(int)(x/maxX);
    }

    return get(x);
}


#undef POINT_X
#undef POINT_Y
