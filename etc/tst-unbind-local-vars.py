#!/usr/bin/env python3
"""
This simple script adds the "Unbind" statements to the end of a GAP tst file.
"""
import os
import re
import sys
import textwrap

import yaml
from bs4 import BeautifulSoup


def main():
    if sys.version_info[0] < 3:
        raise Exception("Python 3 is required")
    args = sys.argv[1:]
    pattern1 = re.compile(r"(\w+)\s*:=")
    pattern2 = re.compile(r"for (\w+) in")
    for fname in args:
        lvars = []
        with open(fname, "r") as f:
            lines = f.read()
            lvars.extend([x.group(1) for x in re.finditer(pattern1, lines)])
            lvars.extend([x.group(1) for x in re.finditer(pattern2, lines)])
        lvars = sorted([*{*lvars}])
        lvars = [
            "# Unbind local variables, auto-generated by etc/tst-unbind-local-vars.py"
        ] + [f"gap> Unbind({lvar});" for lvar in lvars]
        lvars.append("")
        lines = lines.split("\n")
        pos1 = next(i for i in range(len(lines)) if "STOP_TEST" in lines[i]) - 1
        try:
            pos0 = next(
                i
                for i in range(len(lines))
                if "etc/tst-unbind-local-vars.py" in lines[i]
            )
        except StopIteration:
            pos0 = pos1
        lines = lines[:pos0] + lvars + lines[pos1:]
        lines = "\n".join(lines)
        with open(fname, "w") as f:
            print(f"Writing local variables to {fname}...")
            f.write(lines)


if __name__ == "__main__":
    main()