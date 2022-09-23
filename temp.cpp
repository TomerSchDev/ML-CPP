//
// Created by Tomer on 15/08/2022.
//
struct data_member {
    int value;
    int time;

};

class MyArray {
    data_member array[10];
    int time_tracker;
    int all_Value;
    int set_all_time;
public:
    MyArray() {
        set_all_time = -1;
        time_tracker = 0;
        for (int i = 0; i < 10; i++) {
            data_member d;
            d.time = -1;
            array[i] = d;
        }
    }

    int getValue(int index) {
        time_tracker++;
        data_member data = this->array[index];
        if (data.time > this->set_all_time) {
            return data.value;
        } else {
            return this->all_Value;
        }
    }

    int setValue(int index,int value){
        time_tracker++;
        this->array[index].value=value;
        this->array[index].time=this->time_tracker;
    }
    int setAll(int value){
        time_tracker++;
        this->all_Value=value;
        this->set_all_time=time_tracker;
    }
};