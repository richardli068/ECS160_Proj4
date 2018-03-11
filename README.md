# ECS160 Fuzzing Project
 
 
 Sanjana Rajasekar <br />
 Richard Li
 
### maxTweeter.c 
&nbsp;&nbsp; Usage: ./maxTweeter.out `[-option]` `<file>` <br />
&nbsp;&nbsp;&nbsp;&nbsp; option: `-r` prints invalid reason. <br />
&nbsp;&nbsp; Prints `<tweeter>` `:` `<count>` <br />
   
### mapCmp.cpp 
&nbsp;&nbsp; Usage: ./mapCmp.out `<my_map>` `<answer_map>` <br />
&nbsp;&nbsp; File format: `<tweeter>` `:` `<count>` `\n` <br />
* Provide an easy way to test whether maxTweeter outputs the correct map. <br />
* `<answer_map>` is generated from `getPerTweeterCount` from HW3. <br />
* mapCmp` ignores quotes in key. <br />
 
 
 
### Testing files:
   * **"cl-tweets-short.csv"**: original csv from HW3 <br />
   * **"test.csv"**: first 2 line from "cl-tweets-short.csv" <br />
   * **"short.csv"**: first 100 line from "cl-tweets-short.csv". Used to fuzz test.
   * **"no_header.csv"**: first 100 tweets from "cl-tweets-short.csv" w/o header.
   * **"incosis_field_num.csv"**: first 101 lines from "cl-tweets-short.csv". Tweet #97 has 1 less field.
   * **"too_large.csv"**: 5 copies of "cl-tweets-short.csv".
   * **"empty.csv"**: empty file.


### Current fuzzing progress:
   * **"short.csv"**: (42 min, 45 sec) No crashes after 6 cycles. Implies no crashes on **"cl-tweets-short.csv"** and **"test.csv"**. <br />
   * **"no_header.csv"**: (26 sec) No crashes after 30 cycles. <br />
   * **"incosis_field_num.csv"**: (29 min, 19 sec) No crashes after 1 cycle.
	