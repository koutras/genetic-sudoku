/* generate a valid sudoku */
/* ti ginetai me tin free sto makeChildren*/
/* evala >= sto steady state*/
/* na peirazw to rythmo metalaxys*/

/* gia na lysw ena sudoku arkei i argi diastavrwsi*/


#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#include"displaySudoku.h"
#include"sudoku.h"
#define  FAIL -1
	

void mutate(int **sudoku,int **templateSudoku,int usingTemplate,int dimension);

int maxValue;
int found=0;
int t=0;
int best_pos=0,best_fitness=0;

void check(void *ptr)
{
	if(ptr==NULL){
		printf("NULL pointer\n");
		exit(FAIL);
	}

}


int a2b(int a,int b)

{
	int num;	
	num=a+rand()/(float)RAND_MAX*b;

	
	
	return num;

}


void printVector(int *ptr,int dimension)
{
	int i;

	for(i=0;i<dimension;i++)
		printf("%2d ",ptr[i]);

	printf("\n");

}


void printSudoku(int **sudoku,int dimension)
{
	int i;

	for(i=0;i<dimension;i++)
		printVector(sudoku[i],dimension);



	printf("\n\n\n");
}


void printPopulation(int ***sudokuList,int popSize,int dimension)
{

	int i;
	
	for(i=0;i<popSize;i++)
		printSudoku(sudokuList[i],dimension);


	
	printf("\n\n\n\n");

}	
	

void eraseCounter(int *counter,int dimension)
{
	int i;
	
	for(i=0;i<dimension;i++)
		counter[i]=1;

}

int evaluateCounter(int *counter,int dimension)
{
	int i,negSum=0;


	for(i=0;i<dimension;i++)
		if(counter[i]<0)
			negSum=negSum+counter[i];


	return negSum;
}
		

void sudokuEvaluate(int **sudoku,int cellSize,int *finalRes,int usingTemplate,int **templateSudoku)
{
	int i,j,k,m;

	/* to teleio sudoku exei fitness 2*dimension*dimension*/
	

	int maxValue;
	int penalty=0;
	int *counter;
	int dimension;


	dimension=cellSize*cellSize;


	
	*finalRes=maxValue=2*dimension*dimension; /*tyxaia max value  as elpisoume oti tha simperiferthei oraia*/
	
	counter=(int*)malloc(sizeof(int)*dimension);
	check(counter);
	
	eraseCounter(counter,dimension);

	



	/*tsekarisma ana grammi */
	/* den xreiazetai me tin parousa ylopoiisi*/
	
/*	
	for(i=0;i<dimension;i++){
		for(j=0;j<dimension;j++)
			counter[sudoku[i][j]-1]--;


		#ifdef DEBUG2
		printf("COUNTER---->");	
		printVector(counter,dimension);
		#endif


		penalty=evaluateCounter(counter,dimension);	
		*finalRes=*finalRes+penalty;
		eraseCounter(counter,dimension);


		#ifdef DEBUG2
		printf("LINE   ---->");
		printVector(sudoku[i],dimension);
		printf("penalty=%d\n\n",penalty);
		#endif
		
		#ifdef DEBUG
		printf("line %d,penalty %d\n",i,penalty);
		#endif

		
		
	

	
	}	
	*/

	
		#ifdef DEBUG
		printf("\n\n");
		#endif
		
		
	

	/*tsekarisma ana stili */


	eraseCounter(counter,dimension);

	
	for(i=0;i<dimension;i++){
		for(j=0;j<dimension;j++)
			counter[sudoku[j][i]-1]--;


		penalty=evaluateCounter(counter,dimension);	
		
		*finalRes=*finalRes+penalty;
		eraseCounter(counter,dimension);


	}	
	
	/* tsekarisma ana block */
	/*thewrw megalyteri tin varitita tou*/
	
	eraseCounter(counter,dimension);

	for(i=0;i<dimension;i+=cellSize)
		for(j=0;j<dimension;j+=cellSize){
			for(k=i;k<i+cellSize;k++)
				for(m=j;m<j+cellSize;m++)
					counter[sudoku[k][m]-1]--;
		
	
			penalty=evaluateCounter(counter,dimension);
//			penalty*=2; /*dinw megalyteri varitita*/

			
			*finalRes=*finalRes+penalty;
			eraseCounter(counter,dimension);
		}

			


	/*tsekarisma ana template*/
/*


	if(usingTemplate){
	penalty=0;
	for(i=0;i<dimension;i++)
		for(j=0;j<dimension;j++)
			if(templateSudoku[i][j]!=0 && templateSudoku[i][j]!=sudoku[i][j])
				penalty--;

	
	
	*finalRes=*finalRes+penalty;
	}

	*/
	
	
	#ifdef EXTRA
	 printf("FITNESS: %d\n",*finalRes);
	 printf("- - - - - - - - -\n");
	 printSudoku(sudoku,dimension);
	#endif	

			

	
	
	free(counter);
	

}	


int selectCanditate(int *fitness, int tournamentSize, int popSize)
{
	
	int i;
	int maxx=0;
	int chair=-1;
	int person;
	
	
			
	for(i=0;i<tournamentSize;i++){
		person=a2b(0,popSize-1);
	
		if(fitness[person]>maxx){
			chair=person;
			maxx=fitness[person];
		}
	}

	return chair;
}


void columnToRow(int **A,int **B,int rowA,int colB,int dimension)
{
	int i;

	for(i=0;i<dimension;i++)
		A[rowA][i]=B[i][colB];
}
void columnCopy(int **A,int **B,int colA,int colB,int dimension)  //copy B's column to A
{
	int i;

	for(i=0;i<dimension;i++)
		A[i][colA]=B[i][colB];
}


void rowCopy(int **A,int **B,int rowA,int rowB,int dimension)  //copy B's row to A
{
	int i;


	for(i=0;i<dimension;i++)
		A[rowA][i]=B[rowB][i];
		
}

void crossoverRow(int **A,int **B,int rowA,int rowB,int dimension,int start,int finish)
{
	int i;

	for(i=start;i<finish;i++)
		A[rowA][i]=B[rowB][i];
	
}

void switchRows(int **A,int **B,int row,int ln,int dimension)
{
	int temp;
	int i;
		
	for(i=0;i<dimension;i++){
		temp=A[row][i];
		A[row][i]=B[ln][i];
		B[ln][i]=temp;
	}
}

void switchColumns(int **A,int **B,int col,int dimension)
{
	int temp;
	int i;
	
	for(i=0;i<dimension;i++){
		temp=A[i][col];
		A[i][col]=B[i][col];
		B[i][col]=temp;
	}
}

void sudokuCopy(int **A,int **B,int dimension)
{
	int i;

	for(i=0;i<dimension;i++)
		rowCopy(A,B,i,i,dimension);
}


/* options einai o pinakas twn dynatwn epilogwn
 * pernietai me anafora*/


int sudokuNumber(int **options,int dimension)
{
	int value;
		

	do{
	value=a2b(1,dimension);
	
	
	}while(!((*options)[value-1]));


	(*options)[value-1]--;
	
	

		
	return value;

	
}
		


	/*gia xrisi templateSudoku   usingTemplate=1, templateSudoku!=NULL*/

	/* to templateSudoku tha einai deiktis me anafora*/
int **generateNewSudoku(int dimension,int usingTemplate,int ***templateSudoku)
{
		int k;

		int **newSudoku;
		int *vector;
		int i;

		int *tempRow;
		int *number;



		tempRow=(int *)malloc(sizeof(int)*dimension);
		check(tempRow);
	
		/* na kanei arxikopoiisi olwn twn stoixeiwn me 0*/
		

		number=(int *)malloc(sizeof(int)*dimension);

//		printf("number-->%x\n",number);
		check(number);


		
				
		/* arxikopoiisi tou templateSudoku */
				
		
		if(usingTemplate && (*templateSudoku)==NULL ){

					

		

			getSudokuFromVisual(templateSudoku); 
			printf("printing Template\n");

			printSudoku(*templateSudoku,dimension);



				


			puts("to template prepei na dimiourgithikie");
		}

		
		
	newSudoku=(int**)malloc(sizeof(int *)*dimension);
	check(newSudoku);
		
	
		
		

	for(i=0;i<dimension;i++){ 
		for(k=0;k<dimension;k++){
			number[k]=1;                   
			tempRow[k]=0;
		}


		if(usingTemplate){
			for(k=0;k<dimension;k++){

				if((*templateSudoku)[i][k])
					number[(*templateSudoku)[i][k]-1]--; 
			}

		}


		
		for(k=0;k<dimension;k++){
			if(usingTemplate &&((*templateSudoku)[i][k]!=0)){
//				printf("mpike\n");
				
					tempRow[k]=(*templateSudoku)[i][k];
			}
			else
				tempRow[k]=sudokuNumber(&number,dimension);
		}

	


		

			vector=(int *)malloc(sizeof(int)*dimension);
			check(vector);
		
			for(k=0;k<dimension;k++) 
				vector[k]=tempRow[k];



			newSudoku[i]=vector;

	}


	//	printf("number=%x tempRow=%x\n",number,tempRow);


		
		free(number);
		free(tempRow);

		#ifdef DEBUG
		puts("termatise");
		#endif 

		return newSudoku;


}

int ***generatePopulation(int popSize,int dimension,int usingTemplate,int ***templateSudoku)
{
	int ***sudokuList;
	int i;
	

	sudokuList=(int ***)malloc(sizeof(int **)*popSize);
	check(sudokuList);
	
		
	for(i=0;i<popSize;i++) /*paragei ena atomo se kathe loop */
		sudokuList[i]=generateNewSudoku(dimension,usingTemplate,templateSudoku);



	return sudokuList;


	
}

			

int isSolution(int aFitness,int ***sudokuList)
{

	

	if(aFitness==maxValue)
		return 1;
	
	return 0;

}
		
		

 	
void makeChildren(int *pid ,int *fitness,int ***sudokuList,int dimension,int cellSize,int ***templateSudoku,int usingTemplate,int popSize)
{
	

	int ***child;
	int i;
	int j;
	int newFitness;
	int x;
	int crosspoint;

	#ifdef DEBUG2
	printf("parent 1=%d parent2=%d\n",pid[0],pid[1]);
	#endif
	
	
	child=(int ***)malloc(sizeof(int**)*2);
	check(child);


	for(i=0;i<2;i++){
		child[i]=generateNewSudoku(dimension,usingTemplate,templateSudoku);
		check(child[i]);
	
	}

				

/*
puts("father0");
printSudoku(sudokuList[pid[0]],dimension);

puts("father1");
printSudoku(sudokuList[pid[1]],dimension);
*/
		
		for(i=0;i<dimension;i++){
			
			/* an thelw tyxaiotita*
			x=a2b(0,dimension-1); 	
			
			

			#ifdef DEBUG2	
			printf("x=%d\n",x);
			#endif	
			*/

			/* to kathe paidi pairnei tin antoistoixi grammi
			 * tou enos goniou i tou allou me omoimorfi diastaurwsi*/

			crosspoint=a2b(0,dimension-1);

			

			if(a2b(1,10)<6){
				rowCopy(child[0],sudokuList[pid[0]],i,i,dimension);
				rowCopy(child[1],sudokuList[pid[1]],i,i,dimension);
			}

			else{
				rowCopy(child[1],sudokuList[pid[0]],i,i,dimension);
				rowCopy(child[0],sudokuList[pid[1]],i,i,dimension);
			}
			

/*			#ifdef slow
		if(a2b(1,10)<6){
				crossoverRow(child[0],sudokuList[pid[0]],i,i,dimension,0,crosspoint);
				crossoverRow(child[0],sudokuList[pid[1]],i,i,dimension,crosspoint,dimension);
				crossoverRow(child[1],sudokuList[pid[1]],i,i,dimension,0,crosspoint);
				crossoverRow(child[1],sudokuList[pid[0]],i,i,dimension,crosspoint,dimension);
			}

			else{
				crossoverRow(child[1],sudokuList[pid[0]],i,i,dimension,0,crosspoint);
				crossoverRow(child[1],sudokuList[pid[1]],i,i,dimension,crosspoint,dimension);
				crossoverRow(child[0],sudokuList[pid[1]],i,i,dimension,0,crosspoint);
				crossoverRow(child[0],sudokuList[pid[0]],i,i,dimension,crosspoint,dimension);
			}
			#endif*/
		}
	
		#ifdef showChildren 
		puts("children before mutation");	

		printf("child1\n");
		printSudoku(child[0],dimension);
		printf("child2\n");
		printSudoku(child[1],dimension);
		#endif

			
		for(i=0;i<2;i++)
			mutate(child[i],*templateSudoku,usingTemplate,dimension);



		#ifdef showChildren 
		puts("children after mutation");	

		printf("child1\n");
		printSudoku(child[0],dimension);
		printf("child2\n");
		printSudoku(child[1],dimension);

		#endif
	

	/* steady state*/

		
		for(i=0;i<2;i++){
			sudokuEvaluate(child[i],cellSize,&newFitness,usingTemplate,*templateSudoku);			
			/*
			printf("fitness=%d\n",newFitness);
			printSudoku(child[i],dimension);
			*/
		
			x=pid[i];		
			//x=a2b(0,popSize-1);
			if(newFitness>=fitness[x]){ /*EBALA >=*/
				sudokuCopy(sudokuList[x],child[i],dimension);
				fitness[x]=newFitness;
			}
			
		}
				
			

	/* swstos tropos???*/	


	



	for(i=0;i<2;i++)
		for(j=0;j<dimension;j++)
			free(child[i][j]);



	for(i=0;i<2;i++)
		free(child[i]);
	
	free(child);


}
		

void leftShift(int **sudoku,int **templateSudoku,int usingTemplate,int dimension,int line)
{
	int temp;
	int i;
	int j;
	int counter;


/* shift every number 1 position to the left excluding template's */
#ifdef showMutation
	printf("LEFT SHIFT %d\n",line);
#endif

		i=0;

		for(counter=0;counter<dimension-1;counter++){
		
	
			for(; usingTemplate && templateSudoku[line][i]!=0 ;i=(i+1)%dimension,counter++); 


			for(j=(i+1)%dimension;usingTemplate &&  templateSudoku[line][j]!=0;j=(j+1)%dimension);

	//	printf("i=%d j=%d\n",i,j);


			#ifdef showMutation
			printf("swap( pos[%d][%d]=%d,pos[%d][%d]=%d)\n",line,i,sudoku[line][i],line,j,sudoku[line][j]);
			#endif



			temp=sudoku[line][j];
			sudoku[line][j]=sudoku[line][i];
			sudoku[line][i]=temp;

			i=(i+1)%dimension;
			
		}
				

}

void rightShift(int **sudoku,int **templateSudoku,int usingTemplate,int dimension,int line)
{
	int temp,i,j,counter;

#ifdef showMutation
	printf("rightShift at %d\n",line);
#endif

		i=dimension-1;

		for(counter=0;counter<dimension-1;counter++){
			for(;usingTemplate && templateSudoku[line][i]!=0;i--);

			for(j=i-1;usingTemplate &&templateSudoku[line][j]!=0 && j!=-1 ;j--,counter++);

			if(j==-1)break;
				

			#ifdef showMutation
			printf("swap( pos[%d][%d]=%d,pos[%d][%d]=%d)\n",line,i,sudoku[line][i],line,j,sudoku[line][j]);
			#endif

			temp=sudoku[line][j];
			sudoku[line][j]=sudoku[line][i];
			sudoku[line][i]=temp;

			i--;
		}	
			
	



			/* edw stamatisa!!!*/

}

void mutate(int **sudoku,int **templateSudoku,int usingTemplate,int dimension)
{
	int x1;
	int x2; 
	int i,j;
	int t,f,r;

	


/* me tis malakies kathistereitai i metalaksi*/

	
	for(i=0;i<dimension;i++){
		for(j=0;j<dimension;j++)
			if((r=a2b(1,dimension*dimension))==1){
			
			
				r=a2b(1,3);//type of light mutation
			

				if(r==1){ /*simple swap mutation*/
				#ifdef showMutation 
				puts("simple mutation ");
				#endif 
				
				if(usingTemplate && templateSudoku[i][j]!=0 );

					else{
						do{
							t=a2b(0,dimension-1);
						}while( usingTemplate && templateSudoku[i][t]);

						#ifdef showMutation
						printf("swap %d %d at line %d\n",t,j,i);
						#endif

						f=sudoku[i][j];
						sudoku[i][j]=sudoku[i][t];
						sudoku[i][t]=f;
					}
			

	
				}
			

			
				

				

				if(r==2){// triple  mutation

					#ifdef showMutation 
					puts("triple mutation");
					#endif
					if(usingTemplate && templateSudoku[i][j]!=0);

					else{
						do{
							x1=a2b(0,dimension-1);
							x2=a2b(0,dimension-1);
					
						}while( usingTemplate && (templateSudoku[i][x1] || templateSudoku[i][x2])); //mporw an thelw na apofygw tin isita x1,x2 

						#ifdef showMutation
							printf("to stoixeio [%d][%d] tha ginei [%d][%d] kai auto me ti seira tou [%d][%d] kai auto meti seira tou [%d][%d]\n",i,j,i,x1,i,x2,i,j);
						#endif


						f=sudoku[i][j];
						sudoku[i][j]=sudoku[i][x1];
						r=sudoku[i][x1];
						sudoku[i][x1]=sudoku[i][x2];
						sudoku[i][x2]=f;
						
					}
				}



				if(r==3){//near swap
							#ifdef showMutation
							puts("near swap");
							#endif


								if(a2b(0,1)){
									x1=j-1;
									x2=j+1;
								}

								else{

									x2=j-1;
									x1=j+1;
								}
							
								//profanws ithela XOR edw
					
							if(!(templateSudoku[i][j]) && !(templateSudoku[i][x1] && templateSudoku[i][x2])){

								if(!(templateSudoku[i][x1])){	
								
									f=sudoku[i][x1];
									sudoku[i][x1]=sudoku[i][j];
									sudoku[i][j]=f;

									#ifdef showMutation
									printf("swap[%d][%d]=%d with [%d][%d]=%d\n",i,j,sudoku[i][j],i,x1,sudoku[i][x1]);
									#endif
										
				
								}

							else{
									#ifdef showMutation
									printf("swap[%d][%d]=%d with [%d][%d]=%d\n",i,j,sudoku[i][j],i,x2,sudoku[i][x2]);
									#endif
									f=sudoku[i][x2];
									sudoku[i][x2]=sudoku[i][j];
									sudoku[i][j]=f;
							}
				
					
							}	
				}


				

		}			

					
		
				
		//extra mutations	
#ifdef extraMutations	

		
				while((r=a2b(1,dimension*dimension))==1){


					r=a2b(1,2);
					
					if(r==1)
						leftShift(sudoku,templateSudoku,usingTemplate,dimension,i);


					if(r==2)
						rightShift(sudoku,templateSudoku,usingTemplate,dimension,i);

				}
#endif

				

	}

		

				

	
			
	
		

		

}

	
	



int sudokuGame(GtkWindow *window,int seed,int dimension,int tournamentSize,int popSize,float pc,int stoppingGen)
{

	int i,j;	
	int ***sudokuList;
	int *fitness;
	int newGenerationSz;
	int cellSize;
	int pid[2];
	int mean=0;;
	
	int usingTemplate=1;
	int **templateSudoku=NULL;
	

	//initiate globals
	found=t=0;
	

	maxValue=2*dimension*dimension;

	printf("seed=%d dimension=%d tournamentSize=%d popSize=%d pc=%f\n",seed,dimension,
		  tournamentSize,popSize,pc);	


/*GENERATE POPULATION*/	

	cellSize=sqrt(dimension);

	sudokuList=generatePopulation(popSize,dimension,usingTemplate,&templateSudoku);
	

	/*POPULATION CREATED ?????*/


#ifdef print

	printPopulation(sudokuList,popSize,dimension);
#endif
		

	/* FITNESS EVALUATION */


	fitness=(int*)malloc(sizeof(int)*popSize);
	check(fitness);

	for(i=0;i<popSize;i++)
		sudokuEvaluate(sudokuList[i],cellSize,&fitness[i],usingTemplate,templateSudoku);

			
			

	/*SELECTION */


	/*	

		printf("dose to pc,to pososto tou plithismou pou tha allazei kathe fora\
apo 0 eos 1\n");

		scanf("%f",&pc);
*/
		
		newGenerationSz=pc*popSize;

		printf("%d atoma tha allaxoun\n",newGenerationSz);
			


		while(t<stoppingGen && !found){	


		#ifdef DEBUG2 
		printf("kali arxi\n");
		printf("gen->%d\n",t);
		#endif

	

		/*MAKE CHILDREN */ 

		for(i=0;i<newGenerationSz/2;i++){
			for(j=0;j<2;j++)
				pid[j]=selectCanditate(fitness,tournamentSize,popSize);
			
			makeChildren(pid,fitness,sudokuList,dimension,cellSize,&templateSudoku,usingTemplate,popSize);
		}
	

		



	/*check for solution*/

		best_pos=0;
		best_fitness=0;
	for(i=0,mean=0;i<popSize;i++){
		mean+=fitness[i];
		if(fitness[i]>best_fitness)
		{
			best_fitness=fitness[i];
			best_pos=i;
		}

		if(isSolution(fitness[i],sudokuList)){
			printf("JUST FOUND THE SOLUTION\n");
			printSudoku(sudokuList[i],dimension);

			displaySolution(window,sudokuList[i],dimension);
			found=1;
		}
	}
	mean=(mean+0.0)/popSize;


		#ifdef print
		printf("%d: BEST =  %d GOAL = %d MEAN = %d\n",t,best_fitness,maxValue,mean);
		printSudoku(sudokuList[best_pos],dimension);
#endif
	t++;	
		
}

if(t==stoppingGen)
	displaySorry(window);


	/*KILL POPULATION*/


	for(i=0;i<popSize;i++){
		for(j=0;j<dimension;j++)
			free(sudokuList[i][j]);


		free(sudokuList[i]);


		
		
			
	}
			
		

	
	
	
	
	
	
	



	return 0;
	
}
