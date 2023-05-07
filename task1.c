/*
    Code written by:
	Panagiotis Karoutsos, 02034
	Olga Vasileiou, 01691
    Stefania Douliaka, 00974
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FNAME "db.txt" //filename for database
#include "task1.h"
#define SIZE 1024

//format in txt file: breed sex years months id , seperated by spaces
//different entries are seperated by newline(\n)
int main(int argc , char *argv[])

{
	
	int lines=0, k=0, a, foundID, count, i, idin/*input storage*/, idindex/*index of entry found*/;
	char c, years[SIZE], months[SIZE], ch, testch[100], input[SIZE], brin[64], brnIn[64]/*brnIn=breednameInput*/, brnIn2[64]/*brnIn=breednameInput2*/;
	FILE* fptr;
	lines=countLines(FNAME);
										//count lines in txt file, each entry will have its own line so (lines)==(num of entries) 
	
	if(lines==-1)
	{
		printf("Error: file pointer null (could not access file or file doesn't exist)\n");
		fptr=fopen(FNAME,"w");
		fclose(fptr);
		printf("file %s was created in current directory, continuing\n",FNAME);
										//open and close file in append mode, so if it doesnt exist it's created
	}
 	lines--;							//one less, because first line is gonna be entry count
 	
 	
	pet* pets=(pet*)malloc((lines)*sizeof(pet));		//creates dynamic array with space for (lines) pet structs
	fptr=fopen(FNAME,"r");
	
	//checking if file is empty, if yes setting lines=0 and putting in line count in first line
	//need to count instead of just checking for eof because 
	//if someone edits the file manually and deletes everything in it 
	//for some reason it still counts as having one extra character in it
	while((ch=fgetc(fptr))!=EOF & count<3) //doesn't need to go further than 3
		count++;
	if(count<2)
	{
		lines=0;
		fprintf(fptr,"0 dogs:\n");
	}
	fseek(fptr, 0, SEEK_SET);			//reset file pointer to start of file
	fgets(testch,100,fptr);				//read until newline is reached, 100 char max to make sure it reaches it
	for(i=0;i<=lines-1;i++) 			//reads txt file line by line and create a new entry for each line
	{  
		pets[i].breed=(char*)malloc(64*sizeof(char));
		pets[i].sex=(char*)malloc(32*sizeof(char));
		pets[i].pet_age=(age*)malloc(sizeof(age));
										//^allocate space for every structure member
		
		fscanf(fptr,"%s %s %d %d %d",pets[i].breed,pets[i].sex,&pets[i].pet_age->years,&pets[i].pet_age->months,&pets[i].id);
										//scans a line in the txt file and puts each characteristic into its corresponding variable	
	}
	fclose(fptr);
	a = 0;
	while(1)
{
	if (a == 0)
	{
	mainMenu();
	}
	bzero(input, sizeof(input));
	scanf("%s",input);
	if(strcmp(input, "1")==0)
	{
//"1.Insert information for a new pet\n"##########################
	a = 0;
		do
		{
			pets=(pet*)realloc(pets,(lines+1)*sizeof(pet)); //realloc whole array
			
										//allocate and init space for each element
			pets[lines].breed=(char*)malloc(64*sizeof(char));
			pets[lines].sex=(char*)malloc(32*sizeof(char));
			pets[lines].pet_age=(age*)malloc(sizeof(age));
			
										//input elements
			printf("\t|Creating new pet entry:|\n\n"
			"WARNING: For breed names that consist of more than one word, use underscores or connect the words,\n"
			"because spaces can cause bugs.\n");
			printf("\nEnter breed: ");
			scanf("%s", pets[lines].breed);
			printf("Enter sex: ");
			scanf("%s",pets[lines].sex);
			printf("Enter years of age: ");
			scanf("%s", years);
			while (strcmp(years, "9000") > 0 || strcmp(years, "0") < 0)
			{
				printf("Years of age can only be numbers, try again: ");
				bzero(years, sizeof(years));
				scanf("%s", years);
				printf("\n");

			}
			pets[lines].pet_age->years = atoi(years);
			printf("Enter months of age: ");
			scanf("%s", months);
			while (strcmp(months, "9000") > 0 || strcmp(months, "0") < 0)
			{
				printf("Years of age can only be numbers, try again: ");
				bzero(months, sizeof(months));
				scanf("%s", months);
				printf("\n");

			}
			pets[lines].pet_age->months = atoi(months);
			pets[lines].id=lines+1;		//linearly increasing id, starting from some random number (looks nicer)
			printf("Entry successfully created:\n");
			printf("Breed: %s \nSex: %s \nAge: %d years %d months \nID: #%d\n\n",pets[lines].breed, pets[lines].sex,pets[lines].pet_age->years,pets[lines].pet_age->months,pets[lines].id);
			
			printf("Sorting...\n");
			bubbleSort(pets,lines); 	//^^sorts entries in alphabetical order using bubble sort	
			printf("List sorted\n");
			printf("Press I to insert information for another pet, or press ENTER to return to main menu: \n");
			getchar();
			c = getchar();

			lines++; 					//update line/entry count
			
		}while(c == 'i' || c == 'I');		
	}
		
//"2.Delete a pet record based on pet\'s id\n"####################################
	else if(strcmp(input, "2")==0)
	{
			a = 0;
		do 
		{
			printf("\t|Deleting entry based on ID#|\n\n"
			"Enter ID number of entry to delete: #");
			foundID=0;					//1 if an entry with the input id was found, 0 if not
			scanf("%d",&idin);
			i=0;
			while(i<=lines-1)
			{
				if(idin==pets[i].id)	//check if input id matches any entry
				{
					foundID=1;
					idindex=i;			//store index
					break; 				//exit while loop
				}
				i++;
			}
			if(foundID==1)
			{
				printf("\nDeleting entry with ID #%d...\n\n",idin);
										//delete element by overwritting it with the next entry
										//and moving all entries one step back to fill the gap it left
                for(i=idindex;i<lines-1;i++)
                {
	                strcpy(pets[i].breed, pets[i+1].breed);
	                strcpy(pets[i].sex,pets[i+1].sex);
	                pets[i].id=pets[i+1].id;
					pets[i].pet_age->years = pets[i+1].pet_age->years;
					pets[i].pet_age->months = pets[i+1].pet_age->months;
          	 	}	
				bubbleSort(pets,lines);	
				lines--;														//remove element we just deleted from line count
				pets=(pet*)realloc(pets,(lines)*sizeof(pet));					//realloc array to new size
				printf("Entry with ID #%d successfully deleted.\n",idin);
				printf("Press D to delete another entry, or press ENTER to return to main menu: \n");
				getchar();
				c = getchar();
				
			}
			else
			{
				printf("\nNo entry found with ID number #%d\n",idin);
				printf("Press D to try again, or press ENTER to return to main menu: \n");
				getchar();
				c = getchar();
			}
		
			
		}
		while(c == 'd' || c == 'D');
	}
		
//"3.Search a pet record based on pet\'s breed\n"
	else if(strcmp(input, "3")==0)
	{
			a = 0;
		do
		{
			bubbleSort(pets,lines);
			printf("\t|Searching entries based on breed|\n\n"
			"Enter breed: ");
			scanf("%s",brin);
			if( binarySearch(pets,0,lines-1,brin) != -1 ) //check if breed exists
			{
					int low=lowerbd(pets,0,lines-1,brin);
					int high=upperbd(pets,0,lines-1,brin);//cache upper and lower bounds
					int i=low;
					//list all matches
				printf("Entries found matching breed \"%s\" :\n",brin);
				while(i<=high-1)
				{
					printf("%s , %s , %d years and %d months old , ID: #%d\n",pets[i].breed, pets[i].sex,
					pets[i].pet_age->years,pets[i].pet_age->months,pets[i].id);
					i++;
				}
				printf("Press S to search for another pet record, or press ENTER to return to main menu: \n");
				getchar();
				c = getchar();
			}
			else
			{
				printf("No entry with breed \"%s\" found\n"
				"Press S to search for another pet record, or press ENTER to return to main menu: \n",brin);
				getchar();
				c = getchar();
			}
		} while(c == 's' || c == 'S');	
	}
		
//"4.Update pet\'s breed name\n"
	else if(strcmp(input, "4")==0)
	{
			a = 0;
		do
		{
			printf("\t|Updating breed name|\n\n"
			"Enter breed name to update:");
			scanf("%s",brnIn);
			if( binarySearch(pets,0,lines,brnIn) != -1 ) //check if breed exists
			{
				printf("WARNING: For breed names that consist of more than one word, use underscores or connect the words,\n"
				"because spaces can cause bugs.\n"
				"\nEnter new breed name: ");
				scanf("%s",brnIn2);
				bubbleSort(pets,lines);
				int lowb=lowerbd(pets,0,lines-1,brnIn);
				int highb=upperbd(pets,0,lines-1,brnIn);//cache upper and lower bounds
				for(i=lowb;i<=highb-1;i++) 
				{
					strcpy(pets[i].breed,brnIn2); //copy breed from input to every entry in range
				}
				printf("Breed name updated successfully\n"
				"Press U to update another pet's breed name, or press ENTER to return to main menu: \n");
				getchar();
				c = getchar();
			}
			else
			{
				printf("No entry with breed \"%s\" found\n"
				"Press U to update another pet's breed name, or press ENTER to return to main menu: \n",brnIn);
				getchar();
				c = getchar();
			}
		} while(c == 'u' || c == 'U');	
	}
//"5.Exit\n"
		else if(strcmp(input, "5")==0)
		{
			printf("Sorting...\n");
			bubbleSort(pets,lines); 		
			printf("List sorted\n");
			printf("Writing changes to file...\n");
			FILE* fptr;
			fptr=fopen(FNAME,"w");
			if (lines == 1)
			{
				fprintf(fptr,"%d dog:\n",lines);
			} 
			else
			{
				fprintf(fptr,"%d dogs:\n",lines);
			}
			for(i=0;i<=lines-1;i++) //print each entry into its own line in the file
			{
		    	fprintf(fptr,"%s %s %d %d \t\t%d\n", pets[i].breed, pets[i].sex,pets[i].pet_age->years,pets[i].pet_age->months, pets[i].id);
			}
			fclose(fptr);
			printf("Exiting...\n");
			exit(0);
		
		}
		else
		{
		a = 1;
		bzero(input, sizeof(input));
		printf("\nInvalid input, try again: ");		
		}
	
}	
	return 0;
}



//####function definitions####


//binary search for range, returns index of first element in a range of array elements with the same breed
//(since the array is sorted, all the elements with the same breed are all next to each other,
//so we only need to find the first and last to know where to look)
int lowerbd(pet p[], int start, int end, char x[64])
{
   	if(start>end)
   		return start;
   		
   	int mid=start+((end-start)/2);//find middle
   	
   	if( strcmp(p[mid].breed,x) >= 0 ) //if x<=p[mid].breed alphabetically
	  	return lowerbd(p,start,mid-1,x); //go towards lower bound
	else
		return lowerbd(p,mid+1,end,x); //else go toward upper bound 
}
//binary search for range, returns index of last element in a range of array elements with the same breed
//(since the array is sorted, all the elements with the same breed are all next to each other,
//so we only need to find the first and last to know where to look)
int upperbd(pet p[], int start, int end, char x[64])
{
   	if(start>end)
   		return start;
   		
   	int mid=start+((end-start)/2);//find middle
   	
   	if(strcmp(p[mid].breed,x) > 0) //if x>p[mid].breed alphabetically
	   return upperbd(p,start,mid-1,x); //go towards upper bound
	else
		return upperbd(p,mid+1,end,x); //else go toward lower bound 
}

/*standard binary search, because the ranged binary searches above 
don't have an easy way to check for whether the element being searched for exists (as far as we can tell)*/
int binarySearch(pet p[], int l, int r, char x[64])
{
    if (r >= l) 
	{
        int mid = l + (r - l) / 2;
        
        if (strcmp(x,p[mid].breed) == 0)
            return mid;
            
        if (strcmp(x,p[mid].breed) < 0)
            return binarySearch(p, l, mid - 1, x);
            
        return binarySearch(p, mid + 1, r, x);
    }
    return -1;
}
    
//prints main menu
void mainMenu()
{
	//system("cls");
	printf(
	"\nNOTE: New entries will not be saved to file until \"5.Exit\" is selected\n\n"
	"1.Insert information for a new pet\n"
	"2.Delete a pet record based on pet\'s id\n"
	"3.Search a pet record based on pet\'s breed\n"
	"4.Update pet\'s breed name\n"
	"5.Exit\n\n"
	"Enter the corresponding number to select an option: ");
	
}
//sorts structs within an array using bubble sort, alphabetically based on their breed
//input1 is array of structs, input 2 is size of array
void bubbleSort(pet p[], int n)
{
	//temporary variables for transferring elements of one struct to another
	char tempbreed[64];
	char tempsex[32];
	int tempyears, tempmonths, tempid;
    //bubble sort algorithm
    int i,j;
    for (j=0; j<=n-1; j++)
    {
        for (i=j+1; i<n; i++)
        {
			if (strcmp(p[j].breed, p[i].breed) > 0)
            {
            	//1.copy struct p[j] to temp element by element
                strcpy(tempbreed, p[j].breed);
                strcpy(tempsex,p[j].sex);
                tempid=p[j].id;
				tempyears = p[j].pet_age->years;
				tempmonths = p[j].pet_age->months;
                
                //2.copy struct p[i] to p[j] element by element
                strcpy(p[j].breed, p[i].breed);
                strcpy(p[j].sex,p[i].sex);
                p[j].id=p[i].id;
				p[j].pet_age->years = p[i].pet_age->years;
				p[j].pet_age->months = p[i].pet_age->months;
                
                //3.copy temp to p[i] element by element
                strcpy(p[i].breed, tempbreed);
                strcpy(p[i].sex,tempsex);
                p[i].id=tempid;
				p[i].pet_age->years = tempyears;
				p[i].pet_age->months = tempmonths;
            }
        }
    }
   	
}

//counts how many newlines("\n"s) there are in a text file, takes filename or path as input, returns number of lines
//returns -1 if file pointer is null, takes up to 256 character long paths
int countLines(char* FN)
{
	FILE *fp;
    int count = 0;  
    char c;  

    fp = fopen(FN, "r");
  
    if (fp == NULL)
    {
        return -1;
    }

    for (c = getc(fp); c != EOF; c = getc(fp))
        if (c == '\n') // increment count if this character is newline
            count = count + 1;

    fclose(fp);
    return count;
}
