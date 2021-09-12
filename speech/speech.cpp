// speech.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<math.h>


int _tmain(int argc, _TCHAR* argv[]){
	
   char inputFile[50]="yes3.txt";
	
	//part 1 
	//  first we will find the max positive and max negative value of sample from input file for normalization
	
	int xi=0,min=0,max=0;
	FILE *input=fopen(inputFile,"r");//enter your file name here in ".txt"
	
	// checking if file is accessible or not
	 if(input== NULL)
		  {
			  printf("file not accessed");
	          exit(0);
	       }
	 else
	     {    
	
			 char str[50];
	
			 // we will run the code until end of file is detected
			 while(!feof(input))
			 {
				// this will read input from file one string at a time
				 fscanf(input,"%s",str);
				// here we will convert string value to int value 
				 xi=atoi(str);
				// now we will get max positive and max negative values
				  if(max<xi)
					   max=xi;
				  if(min>xi)
					  min=xi;
				  
			 }
			 printf("min value and max value are :");
			 printf("min value is \t %d\n",min);
			 printf("max value is \t %d \n",max);
			
	     }	  
	
	
	 
	 //part 2:

	 // here we are doing normalization on the sample file
	 // we will read input file and write normalized value in a separate file 
 	 
	 input=fopen(inputFile,"r");// set input again to start of file
	 FILE * write=fopen("output_normalized.txt","w");
	 
	 //checking for accessibility
	 if(write==NULL||input==NULL)
		 printf("no such file\n");
	
	 else 
	   {  
			char str[100];
			while(!feof(input))
			{  
				fscanf(input,"%s",str);
				xi=atoi(str);
				
				// for postive value normalization
				if(xi>0)
				{  	
					xi=(xi*5000)/max;
				    
					fprintf(write,"%d\n",xi);
				}
				
				// for negative value normalization
				if(xi<0)
				{  
					xi=(xi*-(5000))/min;;
				    
					fprintf(write,"%d\n",xi);
				}
				else
					fprintf(write,"%d\n",xi);
			
			}
			
			printf(" part 2 :normalization success \n");
		
		}
	// end of while
	
	//now we will read the normalized sample and find the avg energy and avg zcr of noise that is fist 15 frames of 100 samples each
	//we will take ang noise energy and avg noise zcr in two variables
	int noise_thres_energy=0,noise_thres_zcr=0;
	 FILE *nor_input=fopen("output_normalized.txt","r");
	
	 if(nor_input==NULL)
		printf("normalized input file not accessible");
	
	 else{  
		   // here we will take only n=100 samples in each frame to calculate energy and zcr and we will take only 15 frames 
			char str[50];	
			int n=0,loop=0;
		   static int noise_e_arr[15],noise_z_arr[15];
		   int noise_energy=0;
		   int noise_zcr=0;
		   int prev=0;
		   int curr=0;
	
			while(!feof(nor_input))
			{ 
			   
				 //take input as a string and convert into int 
					fscanf(nor_input,"%s",str);
					xi=atoi(str);
					curr=xi; //set curr equal to xi
				   
					//if 100 samples are taken then set n to 0 and increament loop
				   if(n==100 && loop<15)
				    {  
					   noise_e_arr[loop]=noise_energy;
					   noise_z_arr[loop]=noise_zcr;
					   loop++;
					   n=0;
					   noise_energy=0;
					   noise_zcr=0;
					  }//end of inner if
				   
				    else
				    { 
					   noise_energy+=(curr*curr);
					   if(prev<0 && curr>0||prev>0 && curr<0)
						  noise_zcr++;
					  
					   n++;
				    }//end inner else
				   prev=curr;//set previous to current value
			       
				}//end while file has been read
		 // we have taken 15 frames now we will take avg of noise energy and noise zcr
			int avg_noise_energy=0;
			int avg_noise_zcr=0;

			      for(int i=0;i<15;i++)
				{	 avg_noise_energy+=noise_e_arr[i];
                     avg_noise_zcr+=noise_z_arr[i];
				  }
				  avg_noise_energy=avg_noise_energy/15;
				  avg_noise_zcr=avg_noise_zcr/15;
				  
			 printf("avg noise energy =\t %d \n ",avg_noise_energy);
		     
			printf("avg noise zcr =\t  %d \n ",avg_noise_zcr);
		     //set threshold energy and zcr of noise
			noise_thres_energy=(avg_noise_energy*120)/100;
			noise_thres_zcr=avg_noise_zcr;
			printf(" noise threshold energy =\t %d \n ",noise_thres_energy);
		     
			printf("noise threshold zcr =\t %d \n ",noise_thres_zcr);
		    printf("part 2 threshold calculation successul\n");
	 }//end else


	
	 //part  3 :
	 // now we will read normalized file output_normalized and our frame size is 100 samples and then we will store the energy and zcr of each frame in a file
	//we will maintain a count variable for later use which counts no of frames
	 int countFrames=0;
	 nor_input=fopen("output_normalized.txt","r");
	if(nor_input==NULL)
		printf("normalized file not accessible");
	
	else{ 
		  char readInput[100];
		  int nvalue, n=0,Energy=0,Zcr=0,prev=0,curr=0;
		  //create a file to store energy and zcr
		  FILE *EandZ=fopen("energy_zcr.txt","w");
		  while(!feof(nor_input))
		  {
		     fscanf(nor_input,"%s",readInput);//we have read normalized value
			 nvalue=atoi(readInput); //value is converted into int
			 curr=nvalue;
			 if(n==100)  //if n equals 100 then we will write energy and zcr into a file
			 {   
				 fprintf(EandZ,"%d \t\t\t %d \n",Energy,Zcr);
				 n=0;
				 Zcr=0;
				 Energy=0;
				 countFrames++;
			 }//end if
			 
			 else{
				 Energy+=curr*curr;
				 if(prev>0&&curr<0||prev<0&&curr>0)
					 Zcr++;
				      n++;
			     }//end else
			 prev=curr;
		  }//end while
	     	  fclose(EandZ);
	  } //end else

	
	
	//part 4: create array and store values from file in it
		int * energyArray,*zcrArray,i=0;
		energyArray=(int *)malloc((countFrames+1)*sizeof(int));//array created
		zcrArray=(int *)malloc((countFrames+1)*sizeof(int));
	
	//we will read the energy and zcr of frames and put in two separate arrays 
	
	FILE *readEZ=fopen("energy_zcr.txt","r");
	if(readEZ==NULL)
		printf("part 4 unsuccessful");
	
	else
	{    
	   //read energy and zcr in two variables
	   char ene[100],zc[100];
	   int energY=0,zcR=0,i=0;
		while(!feof(readEZ))
		{
		   fscanf(readEZ,"%s",ene);
	       fscanf(readEZ,"%s",zc);
		  energY=atoi(ene);
	      zcR=atoi(zc);
		//store all values in array 
		  energyArray[i]=energY;
		  zcrArray[i++]=zcR;
		 }
		
	}//end else
	//now we will run a loop in array to dectect start marker and end marker and store it in two variables
	int startFrame=0,endFrame=countFrames;
	for(int i=0;i<countFrames;i++)
	{
		if(energyArray[i]>noise_thres_energy)
		//first frame dected now see if 3 subsequent frames are also above threshold
		{ i++;
		  if(energyArray[i]>noise_thres_energy)
		    {   
				i++;
				if(energyArray[i]>noise_thres_energy)
		         //set start frames at index i
                    {
						startFrame =i;
						break;
			             	
				}
		     }
		}// start frames is detected
	}
	 	//now we will search for end of word 
	   // here loop start from that index where we set out start of word 
	for(int i=startFrame;i<countFrames;i++)
	{ //check for three consecutive frames which has lower energy than noise threshold energy
		if(energyArray[i]<noise_thres_energy)
		{ i++;
		  if(energyArray[i]<noise_thres_energy)
		    {   
				i++;
				if(energyArray[i]<noise_thres_energy)
		         //set start frames at index i
                    {
						endFrame =i;
			             	break;
				}
		     }
		}// start frames is 
	  }
	printf("total frames  is \t %d\n",countFrames);
	printf("start frame index is \t %d\n",startFrame);
	printf("end frame index is \t %d\n",endFrame);

	// now we will take 30 percent of word size and check the zcr of it 
	// if zcr crosses threshold_zcr means it has a fricatives at last and it is a yes else its a no

	int sizeofword=endFrame-startFrame;
    	printf(" size of word is \t %d\n",sizeofword);

	//now to get index of last 30 percent of word
	    int sumzcr=0,avgzcr=0;
		int index=(sizeofword*70)/100+startFrame;
	printf(" frame index is \t %d\n",index);
	for(int i=index;i<endFrame;i++)
		sumzcr+=zcrArray[i];

	avgzcr=sumzcr/(endFrame-index);
	printf("average zcr of word = \t %d\n",avgzcr);
	if(avgzcr>20)
		printf("\n\n\n conclusion: \n the word is YES\n\n\n\n");
	else
		 printf("\n\n\n\n conclusion: \n the word is NO\n\n\n\n");
	// free the calloc storage
	free(energyArray);
	free(zcrArray);
	//close all pointers
	fclose(input);
	fclose(readEZ);
    fclose(nor_input);	
	system("pause");
	return 0;
}

