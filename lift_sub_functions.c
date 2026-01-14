#include <stdlib.h>

char *endth(int);
char lift_name(int);
int smart_lift_allocation(int *, int, int);
int smart_managing(int *, int, int);

int smart_lift_allocation(int* lift_cur_pos,int TOTAL_LIFTs,int usr_current_pos){
    int allocated = 0;
    for(int i = 0 ; i< TOTAL_LIFTs ; i++){
        if(abs(usr_current_pos - lift_cur_pos[i])<abs(lift_cur_pos[allocated]-usr_current_pos))
            allocated = i;
    }
    return allocated;
}

int smart_managing(int *user_destination_paths, int lift_current_position ,int total_destination_paths ){
    int z = 0;
    for(int i = 0; i < total_destination_paths ; i++){
        int flag =0;
        for(int j =i+1 ; j< total_destination_paths; j++){
            if(user_destination_paths[i] == user_destination_paths[j]){
                flag++;
            }
        }
        if(flag == 0 && user_destination_paths[i] != lift_current_position){
           user_destination_paths[z++] =user_destination_paths[i];
        }
    }
    printf("\n\tLIFT SMART PATH : ");
    for(int i = 0 ; i < z ; i++ ){
        for(int j = i+1  ;j < z ; j++){
            if(abs(lift_current_position - user_destination_paths[i]) > abs(lift_current_position - user_destination_paths[j])){
                int temp = user_destination_paths[i];
                user_destination_paths[i] = user_destination_paths[j];
                user_destination_paths[j] = temp;
            }
        }
        lift_current_position = user_destination_paths[i];
        printf(" %d ",user_destination_paths[i]);
    }
    printf("\n\n");
    return z;
}

int lift_ui(int lift_cur_pos,int move_direction,char*status){
    int n = 21;
    int x = 0;
    for (int i = 1; i <= n; i++){
        printf("\n\t");
        for (int j = 1; j <= n; j++){
            if (i == 1 || (i == n / 4 && (j != 1 && j != n)))
            printf("%s", i == 1 ? "___" : "---");
            else if (i == n)
            printf("---");
            else if (j == 1 || j == n ||((j==n/2+1 || j == n/2 + 2 || j == n/2 ) && i>n/4))
            printf(" | ");
            else{
                if (i == n / 6 && j == n / 3){
                    printf("\bFLOOR -> %2d%s", lift_cur_pos,endth(lift_cur_pos));
                }else if (i == n / 6 && j == n - n / 3){
                    printf("%s", (move_direction==1)?"Moving   UP  /\\":(move_direction==0)?"Moving DOWN  \\/":status);
                }else{
                    (x < 3 && i == n / 6) ? x++ : (i == n / 6 && j >= n - n / 3) ? printf(" "): printf("   ");
                }
            }
        }
    }
    return 0;
}

void clear_lines(int l)
{
	for (int i = 1; i < l; i++)
	{
		printf("\033[2K");
		printf("\033[A");
	}
	printf("\r\033[2k");
	fflush(stdout);
}
char* endth(int d){
    switch(d){
        case 0 : return " G";
        case 1 : return "st";
        case 2 : return "nd";
        case 3 : return "rd";
        default :return "th";        
    }
}

char lift_name(int allocated){
    switch(allocated){
        case 0 : return 'A';
        case 1 : return 'B';
        case 2 : return 'C';
        case 3 : return 'D';
        default :return -1;        
    }
}
