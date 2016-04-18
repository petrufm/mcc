# MCC
Model Capture for C++

This reverse engineering tool extracts design information from C++ source code producing a set of text tables containing design facts. Next, the information from these tables can be used by other tools (e.g., iPlasma - http://loose.upt.ro/reengineering/research/iplasma, MOOSE -  http://moosetechnology.org/) to perform higher-level analysis for the investigated C++ code such as design metrics, design flaw detection, etc. More details about this program can be found at http://ieeexplore.ieee.org/xpl/articleDetails.jsp?arnumber=4438085.

Requirements
* C++ compiler (e.g., TDM-GCC compiler http://tdm-gcc.tdragon.net/)
* The system depents on a non-public third-party library that we do not distribute (!!!)
