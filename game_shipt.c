#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
 
 typedef enum { FREE, SHIP,DONE } State;

 typedef struct point
{
    int x;
    int y;
}point;

typedef struct submarine
{
    point* start;
    point* end;
   int size;
}submarine;

 typedef struct Square {
    
    submarine* sub;
    State status;
    char sign;
} square;
 
 
 
 point* TranslateCoordinate(char* c)
{
    point *newpoint=(point*)malloc(sizeof(point));
    int row=c[0];
    int column;
    newpoint->x=row-'A';
    if(c[1]== 49 && c[2]==48)
    {
        column=9;
        newpoint->y=column;
        return newpoint;
    }
    column=c[1];
    newpoint->y=column-'1';;
    return newpoint;
}



   square** getsub(char filename[1000],  submarine *list, square **boardp1)
{
    
   
    int subcount=0;
    int i=0;
    char* token;
    char*p=NULL;
    char line[100];
    FILE *fptr;
    fptr=fopen("pb.txt","r");
   
    if(fptr==NULL)
    {
        printf("no file found");
        exit(-1);
    }
       
   boardp1 = (square **)malloc(10 * sizeof(square *)); 
    for (int i=0; i<10; i++) 
         {
         boardp1[i] = (square *)malloc(10 * sizeof(square)); 
         }
    for (int i = 0; i < 10; ++i)
        {
        for (int j = 0; j < 10; ++j) {
            
           
            boardp1[i][j].status = FREE;
            boardp1[i][j].sub = NULL;
            boardp1[i][j].sign='-';
        }   
        }
   


    

   for( i=0;fgets(line,100,fptr)!=NULL;i++)
    {
    printf("%s ",line);
      if(line[0]!='#')  
       { 
        list=(submarine*)malloc(sizeof(submarine));
        list[i].start=(point*)malloc(sizeof(point));
        token=strdup(strtok(line,"-"));
        list[i].start=TranslateCoordinate(token);
        list[i].end=(point*)malloc(sizeof(point));
        token=strdup(strtok(NULL,"\n"));
       
        list[i].end=TranslateCoordinate(token);
       
       if(list->end->x==list->start->x)
       {
            
           for(int start=list->start->y;start<=list->end->y;start++)
           {
             
             boardp1[list->start->x][start].status=SHIP;
             boardp1[list->start->x][start].sign='X';
             boardp1[list->start->x][start].sub->start->x=list->start->x;
             boardp1[list->start->x][start].sub->start->y=list->start->y;
             boardp1[list->start->x][start].sub->end->x=list->end->x;
             boardp1[list->start->x][start].sub->end->y=list->end->y;
             boardp1[list->start->x][start].sub->size=(list->end->y)-(list->start->y)+1;
           }
       }
      else
       {
           for(int start=list->start->x;start<=list->end->x;start++)
           {
             
        
             boardp1[start][list->start->y].status=SHIP;
             boardp1[start][list->start->y].sign='X';
             boardp1[start][list->start->y].sub=list;
             boardp1[start][list->start->y].sub->start->x=list->start->x;
             boardp1[start][list->start->y].sub->start->y=list->start->y;
             boardp1[start][list->start->y].sub->end->x=list->end->x;
             boardp1[start][list->start->y].sub->end->y=list->end->y;
             boardp1[start][list->start->y].sub->size=(list->end->x)-(list->start->x)+1;
             
            
           }       
      
       }
        
        
    }
    
    token=strdup(p);
    line[100]='\0';
   
    
   
    }


   free(boardp1);
    free(list->start);
    free(list->end);
    fclose(fptr);
    return boardp1;

}

void game(square** board1, square ** board2, char turn[100], char result[100])
{
   
   printf("d");
    FILE* pt=fopen(turn, "r");
    FILE* ft=fopen(result, "w");
    printf("d");
    square**bord;
    printf("d");
    int player=0;
    char *pl;
    char line[100];
     int vectory1=1;
    int vectory2=1;
    int vectory=1;
   char nameplay1[100]="player 1";
   char nameplay2[100]="player 2";
    char *nameplayer;
    char hit[10]="hit";
    char miss[10]="mis";
      printf("d");
     struct point* point_player;
    point_player=(point*)malloc(sizeof(point));
     printf("d");
    while(fgets(line,100,pt))
    {
        if(isalpha(line[0]))
        {
            pl=strtok(line, " ");
            player= pl[6];
            if(player==1)
            {
              bord=board1;
              vectory=vectory1;
              nameplayer=strdup(nameplay1);
            }
            if(player==2)
            {
                bord=board2;
                vectory=vectory2;
                nameplayer=strdup(nameplay1);
            }
            }
            else
            {
                fprintf(ft,"there is not thise player\n");
            }
         pl=strtok(NULL,"\n");   
         point_player=TranslateCoordinate(pl);
         if(point_player->x<11 && point_player->y<11)
            {
               if(bord[point_player->x][point_player->y].status==SHIP)
               {  
                 strcat(hit,nameplayer);
                 fprintf(ft,"%s\n",miss);
                 bord[point_player->x][point_player->y].status=DONE;
                 bord[point_player->x][point_player->y].sub->size--;
                  
                if(bord[point_player->x][point_player->y].sub->size==0)
                   {   
                     fprintf(ft,"submarine is boom\n");
                      vectory++;
                      if(vectory==10)
                      {
                        fprintf(pt,"%s is win",player); 
                    
                      }
                   
                   }
                  for (int i = 0; i < 10; ++i)
                     {
                     for (int j = 0; j < 10; ++j) {
                         if(j=9)
                         {
                             fprintf(ft,"%c\n",bord[i][j].sign);
                         }
                         else
                         {
                             fprintf(ft,"%c",bord[i][j].sign);
                         }
                       }
                     
                     }
               }
              
               
               
                if(bord[point_player->x][point_player->y].status==FREE)
                {  
                   strcat(miss,nameplayer);
                   fprintf(pt,"%s\n",miss);
                    bord[point_player->x][point_player->y].status==DONE;
                    bord[point_player->x][point_player->y].sign='*';
                   for (int i = 0; i < 10; ++i)
                     {
                     for (int j = 0; j < 10; ++j) {
                         if(j=9)
                         {
                             
                             fprintf(ft,"%c\n",bord[i][j].sign);
                         }
                         else
                         {
                             fprintf(ft,"%c",bord[i][j].sign);
                         }
                       }
                     }
                
                
                
                }
               if(bord[point_player->x][point_player->y].status==DONE)
               {
                   fprintf(pt,"%s Someone has already selected this slot",player);
               }       
        

             }
       pl=strtok(NULL,"\n");
       }

   free(point_player);
   fclose(pt);
   fclose(ft);
   } 

int main()
{


char namefile[1000];
printf("Enter .txt file of the player 1 name\n");
scanf("%123s",namefile);
FILE *ptr;
//ptr=fopen(namefile,"r");
//if(ptr==NULL)
  //  {
    //    printf("no file found1");
      //  exit(-1);
 //}
char namefile1[1000];
printf("Enter .txt file of the player 2 name\n");
//scanf("%123s",namefile1);
char namefiler[1000];
printf("Enter .txt file of the result\n");
//scanf("%123s",namefiler);
char namefileturn[1000];
printf("Enter .txt file of the turns\n");
//scanf("%123s",namefileturn);
FILE *ptr1;
//ptr1=fopen(namefile1,"r");
//if(ptr1==NULL)
  //  {
    //    printf("no file found2");
      //  exit(-1);
    //}
//FILE*ptr2=fopen(namefileturn,"r");
//if(ptr2==NULL)
  //  {
    //    printf("no file found");
      //  exit(-1);
    //}
//FILE*ptr3=fopen(namefiler,"w");
//if(ptr3==NULL)
    //{
        //printf("no file found");
      //  exit(-1);
    //}
square** boardp1;
square** boardp2;
submarine *list1;
submarine *list2;
boardp1 =getsub(namefile,list1,boardp1);
//boardp2=getsub(namefile1,list2,boardp2);

game(boardp1,boardp2,namefileturn,namefiler);
//free(boardp1);
//free(boardp2);
//fclose(ptr);
//fclose(ptr1);
//fclose(ptr2);
//fclose(ptr3);
}

