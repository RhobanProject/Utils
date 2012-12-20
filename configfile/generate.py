#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import sys, os, yaml
from generator import Generator, Template

if len(sys.argv) != 4:
    print("Usage: ./generate.py <inputDirectory> <configFile> <outputDirectory>")
    exit()

(directory, name, outputDirectory) = sys.argv[1:]
configFile = os.path.join(directory, name + '.yml')

targetDirectory = os.path.dirname(os.path.join(outputDirectory, name))

if not os.path.exists(targetDirectory):
    os.makedirs(targetDirectory)

config = yaml.load(open(configFile, 'r').read())

headerTemplate = Template('ConfigFile.h')
cppTemplate = Template('ConfigFile.cpp')

endName = name.split('/')[-1]
headerTemplate.setVariable('NAME', endName)
cppTemplate.setVariable('NAME', endName)

for entry, config in config.items():
    headerTemplate.appendVariable('INCLUDES', "#include \"%s\"\n"%config['header'])
    generator = Generator(entry, directory, config['class'], config['header'])
    generator.generate(outputDirectory, headerTemplate, cppTemplate, endName)

headerTemplate.render(os.path.join(outputDirectory, name+'.h'))
cppTemplate.render(os.path.join(outputDirectory, name+'.cpp'))
