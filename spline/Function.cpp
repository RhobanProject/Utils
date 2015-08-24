#include <fstream>
#include <cstdlib>
#include <cstdio>
#ifndef MSVC
#include <json/json.h>
#endif
#include <logging/Logger.h>
#include "Function.h"

static Rhoban::Logger out("function");

Function::Function()
    : nbPoints(0)
{
}

void Function::clear()
{
    points_x.clear();
    points_y.clear();
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
#ifndef MSVC
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
#else
	throw std::exception("Unimplemenetd");
#endif
}

double Function::getXMax()
{
    if (nbPoints == 0) {
        return 0.0;
    }

    return points_x[nbPoints-1];
}

void Function::addPoint(double x, double y)
{
    points_x.push_back(x);
    points_y.push_back(y);

    if (nbPoints > 0) {
        float d = points_y[nbPoints] - points_y[nbPoints-1];
        d /= points_x[nbPoints] - points_x[nbPoints-1];
        ds.push_back(d);
    }

    nbPoints++;
}

double Function::get(double x)
{ 
    if (nbPoints == 0) {
        return 0.0;
    }

    if (points_x[0] >= x) {
        return points_y[0];
    }
    if (points_x[nbPoints-1] <= x) {
        return points_y[nbPoints-1];
    }

    int a = 0, b = nbPoints-1;
    int i = (a+b)/2;
    while (a != b) {
        if (points_x[i] >= x) {
            if (i == 0 || points_x[i-1] <= x) {
                a = b;
            } else {
                b = i;
                i = (a+b)/2;
            }
        } else {
            if (a == i) {
                a++;
            } else {
                a = i;
            }
            i = (a+b)/2;
        }
    }

    return points_y[i-1]+ds[i-1]*(x-points_x[i-1]);
}

double Function::getMod(double x)
{
    double maxX = getXMax();

    if (x < 0.0 || x > maxX) {
        x -= maxX*(int)(x/maxX);
    }

    return get(x);
}
