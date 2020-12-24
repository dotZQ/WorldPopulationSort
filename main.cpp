#include <iostream>
#include <stdlib.h>

using namespace std;
class City{
public:
    int id;
    char city_name[90];
    char country[4];
    char district_name[90];
    long population;

};

City parse(char * buffer){
    City result;
    int i;
    int j=0;
    int len = strlen(buffer);
    int state =0;
    char temp[90];
    for(i=0;i<len;i++){
        if (buffer[i]==';' || i == len-1) {
            temp[j++]='\0';
            if(state == 0){
                result.id = atoi(temp);
            }
            if(state == 1){
                sprintf(result.city_name,"%s",temp);
            }
            if(state == 2){
                sprintf(result.country,"%s",temp);
            }
            if(state == 3){
                sprintf(result.district_name,"%s",temp);
            }
            if(state == 4){
                result.population = atol(temp);
                break;
            }
            state ++;
            j=0;
        }
        else{
            if(buffer[i] == '\"'){}
            else
            {
                temp[j++] = buffer[i] ;
            }
        }
        
    }
    return result;
}

void readline(FILE * f,char * buffer){
    int i=0;
    char c = fgetc(f);
    while (c != '\n'&& c!='\0') {
        buffer[i] = c;
        i++;
        c = fgetc(f);
    }
    buffer[i] = '\0';
}

void sortCity(City *allPointer,int len){
    for (int i=0; i<len; i++) {
        for (int j=0; j<len-1-i; j++) {
            if (allPointer[j].population >allPointer[j+1].population) {
                City t = allPointer[j];
                allPointer[j] = allPointer[j+1];
                allPointer[j+1] = t;
            }
        }
    }
    
}
int main(int argc, const char * argv[]) {
    FILE * f = fopen("--->file<---","r");      ////////////////////////input WorldPop.txt
    char buffer[150];
    City all[4000];
    for (int i=0; i<4000; i++) {
        readline(f, buffer);
        City city = parse(buffer);
        all[i] = city;
    }
    City *allpointer[4000];
    for (int i=0; i<4000; i++) {
        allpointer[i] = &all[i];
    }
    sortCity(*allpointer, 4000);
    for (int i=0; i<4000; i++) {
        cout<<allpointer[i]->id<<","<<allpointer[i]->city_name<<","<<allpointer[i]->population<<endl;;
    }
    fclose(f);
    return 0;
}
