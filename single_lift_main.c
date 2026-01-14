#include <stdio.h>
#include <unistd.h>
#include "lift_sub_functions.c"
#define FREE 0
#define WAIT_LOW 2
#define WAIT_HIGH 3

typedef struct {
    int id;
    int status;
    int current_pos;
}LIFT;

int main(){
    LIFT l1 ={1 ,FREE ,0 };
    int user_destination_floor[10],user_current_floor,total_no_lift_users;
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
        total_no_lift_users = smart_managing(user_destination_floor, user_current_floor , total_no_lift_users);
        for(int i = -1 ;i< total_no_lift_users;i++){
            while(((lift_initial_flag)?user_destination_floor[i]:user_current_floor) != l1.current_pos){
                (l1.current_pos < ((lift_initial_flag)?user_destination_floor[i]:user_current_floor))?printf("\r\t----- Moving UP -----| %d%s |",l1.current_pos++,endth(l1.current_pos)):printf("\r\t-----Moving DOWN-----| %d%s |",l1.current_pos--,endth(l1.current_pos));
                fflush(stdout);
                sleep(WAIT_LOW);
            }
            printf("\n\n");
            for(int k = 0 ; k< 4;k++){
                printf("\rWaiting ->> %d%s Floor Doors %s <<-",l1.current_pos,endth(l1.current_pos),(k==0)?"Opening":(k==1)?" Open  ":(k==2)?"Closing":"Closed ");
                fflush(stdout);
                (k == 1)?sleep(WAIT_HIGH):sleep(WAIT_LOW);
            }
            lift_initial_flag++;
            printf("\n\n");
        }
    }
}
