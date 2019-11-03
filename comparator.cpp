#include "comparator.h"

Comparator::Comparator(){}

bool Comparator::operator()(const QStringList &row1, const QStringList &row2){
    for(int i = 0; i < numberOfKeys; ++i){
        int column = keys[i];
        if(column != -1){
            if(ascendingOrder[i]){
                return row1[i] > row2[i];
            }else{
                return row1[i] < row2[i];
            }
        }
    }
    return false;

}
