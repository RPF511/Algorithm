#include <stdio.h>
#include <stdlib.h>


int tobitmask(char temp[200001], int * num){
    int result = 0;
    for(int i = 0; temp[i] != 0; i++){
        result <<= 1;
        (*num)++;
        if(temp[i] == 'M') result |= 1;
        // printf("%c result %d\n",temp[i],result);
    }
    return result;
}

int fanmeeting(void){
    char temp[200001];
    long long idol = 0;
    long long fan = 0;
    int idolnum = 0;
    int fannum = 0;
    int result = 0;
    scanf("%s",temp);
    idol = tobitmask(temp,&idolnum);

    scanf("%s",temp);
    fan = tobitmask(temp,&fannum);
    
    result = fannum-idolnum+1;

    printf("idol %lld : %d  / fan %lld : %d / result %d\n",idol,idolnum,fan, fannum, result);
    idol <<= fannum-idolnum;

    for(int i = 0; i < fannum-idolnum+1; i++, idol >>= 1){
        printf("idol %lld fan %lld and %lld\n",idol,fan,idol & fan);
        // printf("idol %s\nfan  %s\n",toBinary(idol,fannum),toBinary(fan,fannum));
        if(idol & fan) result--;
        printf("result %d\n",result);
    }

    
    return result;
}


int main(void){
    int casen =0;
    char temp;
    scanf("%d",&casen);
    
    for(int i =0; i< casen;i++){
        printf("%d\n",fanmeeting());
    }
}


// 181361704960
// 973078528