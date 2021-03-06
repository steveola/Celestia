// parser.h
//
// Copyright (C) 2001-2009, the Celestia Development Team
// Original version by Chris Laurel <claurel@gmail.com>
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.

#ifndef _PARSER_H_
#define _PARSER_H_

#include <vector>
#include <map>
#include <celmath/mathlib.h>
#include <celutil/color.h>
#include <celcompat/filesystem.h>
#include <celengine/tokenizer.h>
#include <Eigen/Core>
#include <Eigen/Geometry>

class Value;

typedef map<string, Value*>::const_iterator HashIterator;

class AssociativeArray
{
 public:
    AssociativeArray() = default;
    ~AssociativeArray();

    Value* getValue(const std::string&) const;
    void addValue(const std::string&, Value&);

    bool getNumber(const std::string&, double&) const;
    bool getNumber(const std::string&, float&) const;
    bool getNumber(const std::string&, int&) const;
    bool getNumber(const std::string&, uint32_t&) const;
    bool getString(const std::string&, std::string&) const;
    bool getPath(const std::string&, fs::path&) const;
    bool getBoolean(const std::string&, bool&) const;
    bool getVector(const std::string&, Eigen::Vector3d&) const;
    bool getVector(const std::string&, Eigen::Vector3f&) const;
    bool getVector(const std::string&, Eigen::Vector4d&) const;
    bool getVector(const std::string&, Eigen::Vector4f&) const;
    bool getRotation(const std::string&, Eigen::Quaternionf&) const;
    bool getColor(const std::string&, Color&) const;
    bool getAngle(const std::string&, double&, double = 1.0, double = 0.0) const;
    bool getAngle(const std::string&, float&, double = 1.0, double = 0.0) const;
    bool getLength(const std::string&, double&, double = 1.0, double = 0.0) const;
    bool getLength(const std::string&, float&, double = 1.0, double = 0.0) const;
    bool getTime(const std::string&, double&, double = 1.0, double = 0.0) const;
    bool getTime(const std::string&, float&, double = 1.0, double = 0.0) const;
    bool getMass(const std::string&, double&, double = 1.0, double = 0.0) const;
    bool getMass(const std::string&, float&, double = 1.0, double = 0.0) const;
    bool getLengthVector(const std::string&, Eigen::Vector3d&, double = 1.0, double = 0.0) const;
    bool getLengthVector(const std::string&, Eigen::Vector3f&, double = 1.0, double = 0.0) const;
    bool getSphericalTuple(const std::string&, Eigen::Vector3d&) const;
    bool getSphericalTuple(const std::string&, Eigen::Vector3f&) const;
    bool getAngleScale(const std::string&, double&) const;
    bool getAngleScale(const std::string&, float&) const;
    bool getLengthScale(const std::string&, double&) const;
    bool getLengthScale(const std::string&, float&) const;
    bool getTimeScale(const std::string&, double&) const;
    bool getTimeScale(const std::string&, float&) const;
    bool getMassScale(const string&, double&) const;
    bool getMassScale(const string&, float&) const;

    HashIterator begin();
    HashIterator end();

 private:
    map<string, Value*> assoc;
};

typedef vector<Value*> Array;
typedef vector<Value*> ValueArray;
typedef AssociativeArray Hash;

class Value
{
public:
    enum ValueType {
        NumberType     = 0,
        StringType     = 1,
        ArrayType      = 2,
        HashType       = 3,
        BooleanType    = 4
    };

    Value(double);
    Value(const string&);
    Value(ValueArray*);
    Value(Hash*);
    Value(bool);
    ~Value();

    ValueType getType() const;

    double getNumber() const;
    string getString() const;
    ValueArray* getArray() const;
    Hash* getHash() const;
    bool getBoolean() const;

private:
    ValueType type;

    union {
        string* s;
        double d;
        ValueArray* a;
        Hash* h;
    } data;
};


class Parser
{
public:
    Parser(Tokenizer*);

    Value* readValue();

private:
    Tokenizer* tokenizer;

    bool readUnits(const std::string&, Hash*);
    ValueArray* readArray();
    Hash* readHash();
};

#endif // _PARSER_H_
