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
   * **"no_header.csv"**: first 100 tweets from "cl-tweets-short.csv" w/o header.
   * **"incosis_field_num.csv"**: first 101 lines from "cl-tweets-short.csv". Tweet #97 has 1 less field.

### Current fuzzing progress: <br />
	* "short.csv": no crashes after 6 cycles. Implies no crush on "cl-tweets-short.csv" and "test.csv".