#!/bin/bash

rm -rf build-* release* html latex
(find . -name *.c & find . -name *.h) | xargs clang-format -i

# EOF
