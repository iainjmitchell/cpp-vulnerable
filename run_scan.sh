#!/usr/bin/env bash

git pull

~/parasoft/cpptest-standard/cpptestcli \
  -config "builtin://CWE Top 25 + On the Cusp 2023" -compiler gcc_11-64  \
  -module . -input  compile_commands.json \
  -property report.format=sarif 