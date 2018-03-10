# ECS160 Fuzzing Project
 
 
 Sanjana Rajasekar <br />
 Richard Li
 
### maxTweeter.c <br /> 
&nbsp;&nbsp; Usage: <br />
&nbsp;&nbsp;&nbsp;&nbsp; ./maxTweeter.out `<csv_file>` <br />
&nbsp;&nbsp; Prints `<tweeter>`:`<count>` <br />
   
### mapCmp.cpp <br />
&nbsp;&nbsp; Usage: <br />
&nbsp;&nbsp;&nbsp;&nbsp; ./mapCmp.out `<my_map>` `<answer_map>` <br />
&nbsp;&nbsp; File format: <br />
&nbsp;&nbsp;&nbsp;&nbsp; `<tweeter>`:`<count>` `\n` <br />
* Provide an easy way to test whether maxTweeter outputs the correct map. <br />
* `<answer_map>` is generated from `getPerTweeterCount` from HW3. <br />
* mapCmp` ignores quotes in key. <br />
 
 
 
 ### Testing files: <br />
   * **"cl-tweets-short.csv"**: original csv from HW3 <br />
   * **"test.csv"**: first 2 line from "cl-tweets-short.csv" <br />
   * **"short.csv"**: first 100 line from "cl-tweets-short.csv". Used to fuzz test.
