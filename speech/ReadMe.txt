what logic is used:
1.This code will take input as a single word . either yes or no

2.First the input file will be corrected if there is a DC shift ,for my system it was close to zero so didn't used it.

3.Next as the sample input has values > 50000 in some cases so we have used NORMALIZATION and set the factor to 5000.
so each value in sample is adjusted accordingly and saved in a file output_normalization.

4. now we will use this new file .
5.As there is silence in first so i have calculated energy and zcr of 15 frames each of 100 samples of the file. And 
   calculated the avg energy and avg zcr of it.
6.Now i have calculated energy and zcr of each frame of 100 samples each and store it in a file energy_normalization.
7.then i have retrieved the values of energy and zcr of normalized sample and stored in two arrays energyArray and zcrArray
8. then i have put the starting and ending index of the word in two variables by comparing the energy of frame with the threshold noise energy which i calculated   in step 5.
9.Now i took last 30 percent of the word and checked its zcr as if its a YES then its zcr is high and if NO then  will have low zcr .


how to run:

simply put the input file name in line no 17 and also in line no 58 where we have first read the file 
*one thing to note that input file must not contain any thing other than samples values like sample rate , type of channel etc so when using a file directly saved from cool edit software kindly remove those thing manually.
*i have used voise sample that sir provided us