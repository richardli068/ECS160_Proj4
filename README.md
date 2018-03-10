# ECS160 Fuzzing Project
# 
# 
# Sanjana Rajasekar
# Richard Li
# 
# maxTweeter.c:
#   Usage:
#     ./maxTweeter.out <csv_file>
#   Prints <tweeter>:<count>
#   
#   mapCmp.cpp:
#     Usage:
#       ./mapCmp.out <my_map> <answer_map>
#     File format:
#        <tweeter>:<count>\n
#    Provide an easy way to test whether maxTweeter outputs correct map.
#    <answer_map> is generated from getPerTweeterCount from HW3.
#    mapCmp ignores quotes in key.
# 
# 
# 
# Testing files:
#   "cl-tweets-short.csv": original csv from HW3
#   "test.csv": first 2 line from "cl-tweets-short.csv"
#   "short.csv": first 100 line from "cl-tweets-short.csv". Used to fuzz test.
