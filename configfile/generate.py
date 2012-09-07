#!/usr/bin/env python
# -*- coding: utf-8 -*-

import sys, os, yaml
from CppHeaderParser import CppHeaderParser
from generator import Generator, Template

if len(sys.argv) != 4:
    print "Usage: ./generate.py <inputDirectory> <configFile> <outputDirectory>"
    exit()

(directory, name, outputDirectory) = sys.argv[1:]
configFile = os.path.join(directory, name + '.yml')

if not os.path.exists(outputDirectory):
    os.mkdir(outputDirectory)

config = yaml.load(file(configFile, 'r').read())

headerTemplate = Template('ConfigFile.h')
cppTemplate = Template('ConfigFile.cpp')

headerTemplate.setVariable('NAME', name)
cppTemplate.setVariable('NAME', name)

for entry, className in config.items():
    headerTemplate.appendVariable('INCLUDES', "#include \"%s.h\"\n"%className)
    generator = Generator(entry, directory, className)
    generator.generate(outputDirectory, headerTemplate, cppTemplate, name)

headerTemplate.render(os.path.join(outputDirectory, name+'.h'))
cppTemplate.render(os.path.join(outputDirectory, name+'.cpp'))
