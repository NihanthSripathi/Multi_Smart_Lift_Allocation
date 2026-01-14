#include <stdio.h>
#include <unistd.h>
#include "lift_sub_functions.c"

#define BUZY 0
#define FREE 1
#define WAIT_LOW 2
#define WAIT_HIGH 4
#define TOTAL_LIFTs 3 

#define MOVING_UP 1
#define MOVING_DOWN 0
#define MOVING_NONE -1

typedef struct {
    int id;
    int status;
    int current_pos;
}LIFT;

int main(){
    int user_destination_floor[10],user_current_floor,total_no_lift_users,lift_cur_pos[TOTAL_LIFTs],allocated ;
    LIFT lift[TOTAL_LIFTs];
    for(int i = 0; i< TOTAL_LIFTs ; i++){
        lift[i].id = i;
        lift[i].status = FREE;
        lift[i].current_pos = i;
    }
    while(1){
        int lift_initial_flag=0;
        printf("\nEnter No of people : ");scanf("%d",&total_no_lift_users);
        if(total_no_lift_users<1||total_no_lift_users>10){
            printf(" Invalid Input check range (1 to 10) \n");
            continue;
        }
        printf("\nEnter the current Floor : "); scanf("%d",&user_current_floor);
        printf("\nEnter destination floor's : ");
        for(int i = 0; i < total_no_lift_users; i++)scanf("%d",&user_destination_floor[i]);
        for(int i = 0; i< TOTAL_LIFTs;i++)lift_cur_pos[i] = lift[i].current_pos;
        allocated = smart_lift_allocation(lift_cur_pos,TOTAL_LIFTs,user_current_floor);
        printf("\n\tLift Allocated  -> %c \n",lift_name(allocated));
        total_no_lift_users = smart_managing(user_destination_floor, user_current_floor , total_no_lift_users);
        for(int i = -1 ;i< total_no_lift_users;i++){
            while(((lift_initial_flag)?user_destination_floor[i]:user_current_floor) != lift[allocated].current_pos){
                (lift[allocated].current_pos < ((lift_initial_flag)?user_destination_floor[i]:user_current_floor))?lift_ui(lift[allocated].current_pos++,MOVING_UP," "):lift_ui(lift[allocated].current_pos--,MOVING_DOWN," ");
                fflush(stdout);
                sleep(WAIT_LOW);
                clear_lines(22);
            }
            for(int k = 0 ; k< 4;k++){
               lift_ui(lift[allocated].current_pos,MOVING_NONE,(k==0)?"Reached Opening":(k==1)?"Reached <Open> ":(k==2)?"Reached Closing":"Reached Closed ");
                fflush(stdout);
                (k == 1)?sleep(WAIT_HIGH):sleep(WAIT_LOW);
                clear_lines(22);
            }
            lift_initial_flag++;
        }
    }
}