#include "hist.h"
#include <string.h>

//FUNCTION IMPLEMENTATION:

void createEmptyList (tHist *list){
    *list = NULL_COMMAND; //condition: variable list (initial item), points to nothing
}

tCommand_pos first(tHist list){
    return list; //l points to the first item
}

tCommand_pos next (tCommand_pos pos, tHist list){
    return pos->next; //the next item is obtained
}

bool insertItem(struct tNode node, tHist *list){

    tCommand_pos n_pos, p_pos; //needed position variables, new node position and the position that will be its previous
    n_pos = malloc (sizeof(struct tNode)); //check if there is enough memory to insert the item

    if (n_pos == NULL_COMMAND) //if there is not enough space:
        return false; //the item can't be inserted
    else {
        //there is enough memory, n_pos = position of the new node
        strcpy(n_pos->data.command, node.data.command); //n_pos gets the given data
        n_pos->next = NULL_COMMAND; //the next position to n_pos is set to null

        if (*list == NULL_COMMAND) //list is empty
            *list = n_pos; //n_pos is the first position
        else {
            p_pos = *list; //set the following position at the beginning of the list
            while (p_pos->next != NULL_COMMAND)
                p_pos = p_pos->next;
            n_pos->next = p_pos->next; //set that the next of n_pos is the next of prev_pos
            p_pos->next = n_pos; //set n_pos to be the position following prev_pos
            //thus prev_pos is the position previous to n_pos
        }
        return true; //indeed, it is possible to insert the item
    }
}


void deleteAtPosition(tCommand_pos pos, tHist *list){

    tCommand_pos p_pos;
    if ( pos == *list ) //given position is set to be the first element
        *list = pos->next; //list points to the next item of given position, thus ignoring it
    else if (pos->next == NULL_COMMAND) { //given position is set to be the last element

        for ( p_pos=*list ; p_pos->next  != pos ; p_pos = p_pos->next); //q as l (first pos) advance though the list until the next to q is p
        //q is previous to p
        p_pos->next = NULL_COMMAND; //point the next of q to null, thus making it the last element in the list
    }
    else { //intermediate position
        for (p_pos=*list ; p_pos->next  != pos ; p_pos = p_pos->next);//prev_pos as first pos advance
        // though the list until the next to prev_pos is given position
        p_pos->next = pos->next; //once obtained previous position to given, we set the item that goes after
        // given position to go after previous position, thus skipping given pos
    }
    free(pos); // data in given position not needed anymore, thus freed
}


tCommand getItem(tCommand_pos pos, tHist list){
    return pos->data; //it gets the data of a given item at a given position
}