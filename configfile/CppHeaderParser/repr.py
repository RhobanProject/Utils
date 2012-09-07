#!/usr/bin/python

import CppHeaderParser

f = CppHeaderParser.CppHeader("test/TestSampleClass.h")

print f

print "=" * 20

#print f.classes["SampleClass"]["methods"]["public"][2]["parameters"]
print f.classes["AlphaClass"]["enums"]["protected"][0]["values"]