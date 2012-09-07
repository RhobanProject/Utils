#!/usr/bin/env python
# -*- coding: utf-8 -*-

import sys, os, re, codecs
from CppHeaderParser import CppHeaderParser

class Template(object):
    def __init__(self, filename):
        self.content = unicode(file(os.path.join(os.path.dirname(__file__), 'templates', filename), 'r').read(), 'utf-8')
        self.variables = {}

    def render(self, filename):
        data = self.content

        for name, value in self.variables.items():
            data = data.replace('%'+name+'%', value)

        outFile = codecs.open(filename, 'w', 'utf-8')
        outFile.write(data)
        outFile.close()

    def setVariable(self, variable, name):
        self.variables[variable] = name

    def appendVariable(self, variable, value):
        self.variables[variable] = self.variables.get(variable, '') + value

class Parameter(object):
    def __init__(self, name, propertyName, typing, default, description):
        self.name = name
        self.propertyName = propertyName
        self.typing = typing
        self.default = default
        self.description = description

    def generateCode(self):
        code = '';
        # Command line
        if self.typing == 'bool':
            code += "if (options.findFlag(\"%s\")) {\n"
            code += "obj->%s = true;\n" % (self.propertyName)
            code += "} else if (options.findFlag(\"no-%s\")) {\n"
            code += "obj->%s = false;\n" % (self.propertyName)
        else:
            code += "if (char *value = options.getValue(\"%s\")) {\n" % (self.name)
            if self.typing == 'string':
                code += 'obj->%s = string(value);\n' % (self.propertyName)
            if self.typing == 'float' or self.typing == 'double':
                code += 'obj->%s = atof(value);\n' % (self.propertyName)
            if self.typing == 'int':
                code += 'obj->%s = atoi(value);\n' % (self.propertyName)

        code += "} else {\n"
        # Yaml
        code += "if (yamlOk && (node = yaml->FindValue(\"%s\"))) {\n" % (self.name)
        code += "*node >> obj->%s;\n" % (self.propertyName)
        code += "} else {\n"
        # Default value
        code += "obj->%s = %s;\n" % (self.propertyName, self.default)
        code += "}\n"
        code += "}\n"
        return code

    def generateInit(self):
        init = ''
        if self.typing == 'bool':
            init += "options.setFlag(\"%s\");" % (self.name)
            init += "options.setFlag(\"no-%s\");" % (self.name)
        else:
            init += "options.setOption(\"%s\");" % (self.name)
        return init

class Generator(object):
    def __init__(self, entry, directory, className):
        self.entry = entry
        self.directory = directory
        self.className = className
        self.properties = []

    def process(self, property):
        if 'doxygen' in property:
            comment = property['doxygen']
            matches = re.match(r"(.*)(Parameter\()(.+?)(\))(.*)", comment, re.MULTILINE|re.DOTALL)

            if matches != None:
                data = matches.groups()[2].split(',')
                data = map(lambda x: x.strip(), data)
                self.properties += [Parameter(data[0], property['name'], property['type'], data[1], data[2])]

    def generate(self, outputDirectory, headerTemplate, cppTemplate, configClass):
        header = CppHeaderParser.CppHeader(os.path.join(self.directory, self.className + '.h'))

        if self.className not in header.classes:
            raise Exception('Class '+self.className+' not found in header file')
        
        classHeader = header.classes[self.className]

        for property in classHeader['properties']['public']:
            self.process(property)

        # Header
        headerTemplate.appendVariable('PROTOTYPES', "void load%s(%s *obj);\n" % (self.className, self.className))

        # Code
        code = "void %s::load%s(%s *obj) {\n" % (configClass, self.className, self.className)
        code += "const YAML::Node *yaml = NULL;\n"
        code += "const YAML::Node *node;\n"
        code += "bool yamlOk;"
        code += "if (doc.size()) {\n"
        code += "    yaml = doc.FindValue(\"%s\");" % (self.entry)
        code += "}\n"
        code += "yamlOk = (yaml != NULL) && (yaml->size()!=0);\n";
        for property in self.properties:
            code += property.generateCode();
        code += "}\n"

        cppTemplate.appendVariable('METHODS', code)

        # Init
        init = ''
        for property in self.properties:
            init += property.generateInit()

        cppTemplate.appendVariable('INIT', init)

