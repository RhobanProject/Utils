#!/usr/bin/env python
# -*- coding: utf-8 -*-

import sys, os, re, codecs
from CppHeaderParser import CppHeaderParser3

class Template(object):
    def __init__(self, filename):
        self.content = open(os.path.join(os.path.dirname(__file__), 'templates', filename), 'r').read()
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
    def __init__(self, entry, name, propertyName, typing, default, description):
        self.entry = entry
        self.name = name
        self.propertyName = propertyName
        self.typing = typing
        self.default = default
        self.description = description

    def generateCode(self):
        code = '';
        # Command line
        if self.typing == 'bool':
            code += "if (options.getFlag(\"%s\") || options.getFlag(\"%s.%s\")) {\n" % (self.name, self.entry, self.name)
            code += "obj->%s = true;\n" % (self.propertyName)
            code += "} else if (options.getFlag(\"no-%s\") || options.getFlag(\"%s.no-%s\")) {\n" % (self.name, self.entry, self.name)
            code += "obj->%s = false;\n" % (self.propertyName)
        else:
            load = ''
            if self.typing == 'string':
                load += 'obj->%s = string(value);\n' % (self.propertyName)
            if self.typing == 'float' or self.typing == 'double':
                load += 'obj->%s = atof(value);\n' % (self.propertyName)
            if self.typing == 'int':
                load += 'obj->%s = atoi(value);\n' % (self.propertyName)

            code += "if (char *value = options.getValue(\"%s\")) {\n" % (self.name)
            code += load
            code += "} else if (char *value = options.getValue(\"%s.%s\")) {\n" % (self.entry, self.name)
            code += load

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
            init += "options.setFlag(\"%s.%s\");" % (self.entry, self.name)
            init += "options.setFlag(\"%s.no-%s\");" % (self.entry, self.name)
        else:
            init += "options.setOption(\"%s\");" % (self.name)
            init += "options.setOption(\"%s.%s\");" % (self.entry, self.name)
        return init

    def generateUsage(self):
        usage = ''
        usage += "cout << \"    %s: \" << %s << \" (%s, default: \" << %s << \")\" << endl;\n" % (self.name, self.description, self.typing, self.default)
        return usage

class Generator(object):
    def __init__(self, entry, directory, className, headerFile):
        self.entry = entry
        self.directory = directory
        self.className = className
        self.headerFile = headerFile
        self.properties = []

    def process(self, property):
        if 'doxygen' in property:
            comment = property['doxygen']
            matches = re.match(r"(.*)(Parameter\()(.+)(\)\w*\n)(.*)", comment, re.MULTILINE|re.DOTALL)

            if matches != None:
                data = matches.groups()[2].split(',', 2)
                data = list(map(lambda x: x.strip(), data))
                self.properties += [Parameter(self.entry, data[0], property['name'], property['type'], data[1], data[2])]

    def generate(self, outputDirectory, headerTemplate, cppTemplate, configClass):
        header = CppHeaderParser3.CppHeader(os.path.join(self.directory, self.headerFile))

        if self.className not in header.classes:
            raise Exception('Class '+self.className+' not found in header file')
        
        classHeader = header.classes[self.className]

        for property in classHeader['properties']['public']:
            self.process(property)

        # Header
        methodName = self.entry[0].capitalize() + self.entry[1:]
        headerTemplate.appendVariable('PROTOTYPES', "void load%s(%s *obj);\n" % (methodName, self.className))

        # Code
        code = "void %s::load%s(%s *obj) {\n" % (configClass, methodName, self.className)
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

        # Usage
        usage = 'cout << endl << "%s:" << endl;\n' % (self.entry)
        for property in self.properties:
            usage += property.generateUsage()

        cppTemplate.appendVariable('USAGE', usage)

